#include "FilesToAdd.h"
FilesToAdd::FilesToAdd(QString path){
    filepath=path;
    file=new QFileInfo(filepath);
    filesize_byte=file->size();
    filesize_megabyte=filesize_byte/(1000*1000);
    filesize=QString::number(filesize_megabyte, 'f', 3 );
    filename=file->fileName().section("/",-1,-1);
}
