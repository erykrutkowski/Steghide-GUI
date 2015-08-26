#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QHeaderView>
#include <dialog.h>
#include <extractdialog.h>
#include "FilesToAddListModel.h"
#include "steghide-src/CvrStgFile.h"
#include "steghide-src/Session.h"
#include "steghide-src/EmbData.h"
#include "steghide-src/Extractor.h"
#include "steghide-src/Selector.h"
#include "steghide-src/error.h"
#include "steghide-src/common.h"
#include "StdRedirection.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sectionClicked ( int logicalIndex );

    void on_ReloadButton_clicked();

    void on_AddFilesButton_clicked();

    void on_SettingsButton_clicked();

    void on_HelpButton_clicked();

    void on_EncodeButton_clicked();

    void on_FilesAndFoldersTreeView_clicked(const QModelIndex &index);

    void update_FreeSpaceProgressBar();

    void on_FilesAndFolders_MainPath_returnPressed();

    void on_ExtractButton_clicked();

private:
    Ui::MainWindow *ui;
    Dialog     *dialog;
    QFileSystemModel *dirmodel;
    FilesToAddListModel* filesmodel;
    QHeaderView *files_v_header;
    QStringList filenames;
    QString sPath;
    QString passphrase;
    CvrStgFile *selected_file;
};

#endif // MAINWINDOW_H
