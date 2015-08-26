#ifndef EXTRACTDIALOG_H
#define EXTRACTDIALOG_H

#include <QDialog>

namespace Ui {
class ExtractDialog;
}

class ExtractDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExtractDialog(QWidget *parent = 0);
    void setlabeltext(QString new_text);
    void setprogressbarvalue(int k);
    ~ExtractDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ExtractDialog *ui;
};

#endif // EXTRACTDIALOG_H
