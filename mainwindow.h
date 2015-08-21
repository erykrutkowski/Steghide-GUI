#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QHeaderView>
#include <dialog.h>
#include "FilesToAddListModel.h"

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

private:
    Ui::MainWindow *ui;
    Dialog     *dialog;
    QFileSystemModel *dirmodel;
    FilesToAddListModel* filesmodel;
    QHeaderView *files_v_header;
    QStringList filenames;
    QString sPath;
    QString passphrase;

};

#endif // MAINWINDOW_H
