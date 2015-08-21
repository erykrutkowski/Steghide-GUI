#ifndef FILESTOADD_H
#define FILESTOADD_H

#include <QObject>
#include <QFileInfo>

class FilesToAdd
{
public:
    FilesToAdd(QString path);
    QString filepath;
    QString filename;
    double  filesize_byte;
    double  filesize_megabyte;
    QString filesize;
    QFileInfo *file;
};

#endif // FILESTOADD_H
