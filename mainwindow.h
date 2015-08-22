#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QHeaderView>
#include <dialog.h>
#include "FilesToAddListModel.h"
#include "steghide-src/CvrStgFile.h"

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
