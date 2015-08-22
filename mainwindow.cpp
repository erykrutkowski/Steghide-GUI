#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QStringListModel"
#include "QMessageBox"
#include "QInputDialog"
//#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->FreeSpaceProgressBar->setFormat("Select file in left section.");

    sPath="";
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
    }
    else
    {
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
