#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QStringListModel"
#include "QMessageBox"
#include "QInputDialog"
#include <QTextStream>
#include <QLabel>
#include <QTextBrowser>

void outcallback( const char* ptr, std::streamsize count, void* pString )
{
  (void) count;
  QString* p = static_cast< QString* >( pString );
  p->append(ptr);
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->FreeSpaceProgressBar->setFormat("Select file in left section.");
    ui->centralWidget->setLayout(ui->gridLayout);
    sPath="/home/rryk/Pulpit/Discotest";
    selected_file=NULL;
    dirmodel = new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    dirmodel->setNameFilters(QStringList() << "*.jpg" << "*.JPG" << "*.jpeg" << "*.JPEG" << "*.bmp" << "*.BMP" << "*.wav" << "*.WAV" << "*.au" << "*.AU");
    dirmodel->setRootPath(sPath);
    ui->FilesAndFoldersTreeView->setModel(dirmodel);
    ui->FilesAndFoldersTreeView->setRootIndex(dirmodel->index(sPath));

    filesmodel = new FilesToAddListModel(filenames);
    ui->FileTableView->setModel(filesmodel);
    files_v_header= ui->FileTableView->verticalHeader();
    connect(files_v_header, SIGNAL(sectionClicked(int)), this, SLOT(on_sectionClicked(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ReloadButton_clicked()
{
    sPath=ui->FilesAndFolders_MainPath->text();
    if(QDir(sPath).exists()){
        dirmodel->setRootPath(sPath);
        ui->FilesAndFoldersTreeView->setRootIndex(dirmodel->index(sPath));
    }
    else{
        QWidget tmp;
        QMessageBox::critical(&tmp,"Error","WRONG PATH!");
    }
}

void MainWindow::on_AddFilesButton_clicked()
{
    filenames.clear();
    filenames=QFileDialog::getOpenFileNames(this, tr("Open File"), "/", "All files *.*");
    filesmodel->setStringList(filenames);
    update_FreeSpaceProgressBar();
}

void MainWindow::on_sectionClicked ( int logicalIndex )
{
    filesmodel->removeRow(logicalIndex);
    update_FreeSpaceProgressBar();
}

void MainWindow::on_SettingsButton_clicked()
{
    dialog = new Dialog(this);
    dialog->setWindowTitle("Settings");
    dialog->setlabeltext("There will be some Settings.");
    dialog->setModal(true);
    dialog->show();
}

void MainWindow::on_HelpButton_clicked()
{
    dialog = new Dialog(this);
    dialog->setWindowTitle("Help");
    dialog->setlabeltext("There will be some Help.");
    dialog->setModal(true);
    dialog->show();
}

void MainWindow::on_EncodeButton_clicked()
{
    passphrase=QInputDialog::getText(this,"Specify passphrase","Enter passphrase:",QLineEdit::Password);
}

void MainWindow::on_FilesAndFoldersTreeView_clicked(const QModelIndex &index)
{
    if((ui->FilesAndFoldersTreeView->selectionModel()->isSelected(index))&&(QFileInfo(dirmodel->filePath(index)).isFile())){
        selected_file =  CvrStgFile::readFile ((dirmodel->filePath(index)).toUtf8().constData()) ;
        update_FreeSpaceProgressBar();
        ui->ExtractButton->setEnabled(true);
    }
    else
    {
        ui->ExtractButton->setEnabled(false);
        selected_file = NULL;
    }

}

void MainWindow::update_FreeSpaceProgressBar(){
    if(selected_file!=NULL){
        int temp=((filesmodel->get_sum_size())/(selected_file->getCapacity()))*100;
        ui->FreeSpaceProgressBar->setValue(temp);

        ui->FreeSpaceProgressBar->setFormat(QString::number(filesmodel->get_sum_size())+" / "+QString::number(selected_file->getCapacity()));
    }
}

void MainWindow::on_FilesAndFolders_MainPath_returnPressed()
{
    on_ReloadButton_clicked();
}

void MainWindow::on_ExtractButton_clicked()
{
    if(selected_file!=NULL){
        ExtractDialog *extract_dialog;
        extract_dialog=new ExtractDialog(this);
        extract_dialog->setModal(true);
        extract_dialog->show();
        passphrase=QInputDialog::getText(this,"Specify passphrase","Enter passphrase:",QLineEdit::Password);
        QModelIndex index=ui->FilesAndFoldersTreeView->selectionModel()->selectedIndexes().at(0);
        std::string dirmodel_path=(dirmodel->filePath(index)).toUtf8().constData();
        Extractor ext (dirmodel_path, passphrase.toUtf8().constData()) ;

        EmbData* embdata = ext.extract() ;

        // write data
        std::string fn ;
            // write extracted data to file with embedded file name
            fn = embdata->getFileName() ;
            if (fn.length() == 0) {
                fn=(QInputDialog::getText(this,"Please specify a file name for the extracted data (there is no name embedded in the stego file).","Enter filename:",QLineEdit::Normal)).toUtf8().constData();
            }

        extract_dialog->setlabeltext( QString::fromStdString("Writing extracted data to: "+fn));

        QString * myString = new QString();
        myString->clear();

         StdRedirector<>* myRedirector = new StdRedirector<>( std::cerr, outcallback, myString );
         BinaryIO *io;
         try{
         io = new BinaryIO (dirmodel_path.substr(0,dirmodel_path.find_last_of("//"))+"/"+fn, BinaryIO::WRITE) ;
         }
         catch(SteghideError e){
             QMessageBox::StandardButton reply = QMessageBox::question(this, "Existing file?", myString->toUtf8().constData(),
                                             QMessageBox::Yes|QMessageBox::No);
             if (reply == QMessageBox::Yes) {
                 Args.Force.setValue(true);
                 io = new BinaryIO (fn, BinaryIO::WRITE) ;
                 Args.Force.setValue(false);
             }
             delete myRedirector;
             myString->clear();
         }

         if(io->is_open()){
            std::vector<BYTE> data = embdata->getData() ;
            float progress=0;
            unsigned long k;
            unsigned long size=data.size();
            for (std::vector<BYTE>::iterator i = data.begin() ; i != data.end() ; i++) {
                io->write8 (*i) ;
                k=((i-data.begin())/100);
                progress=((k/(data.size()/100))*100);
                extract_dialog->setprogressbarvalue(progress);
            }
            io->close() ;
            extract_dialog->setlabeltext( QString::fromStdString("wrote extracted data to \""+fn+"\"."));
         }
         else{
             extract_dialog->setlabeltext( "ERROR" );
         }

    }
}
