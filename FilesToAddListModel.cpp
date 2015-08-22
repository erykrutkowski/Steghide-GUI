#include "FilesToAddListModel.h"

FilesToAddListModel::FilesToAddListModel(QStringList filepaths, QObject *parent) : QAbstractListModel(parent) {
    sum_size=0;
    filepaths.clear();
    setStringList(filepaths);
}

void FilesToAddListModel::setStringList(QStringList filepaths, const QModelIndex &parent) {
    for(int i=0; i<filepaths.size(); i++){
        beginInsertRows(parent, (int)FilesToAdd_.size(), (int)FilesToAdd_.size());
        FilesToAdd_.push_back(FilesToAdd(filepaths.at(i)));
        sum_size+=FilesToAdd_.back().filesize_byte;
        endInsertRows();

    }
}

int FilesToAddListModel::rowCount(const QModelIndex& parent) const {
    return FilesToAdd_.size();
}

int FilesToAddListModel::columnCount(const QModelIndex& parent) const {
    return 2;
}

QVariant FilesToAddListModel::data(const QModelIndex& index, int role) const {
    // Check that the index is valid and within the correct range first:
    if (!index.isValid()) return QVariant();
    if (role == Qt::DisplayRole)
    {
        if(index.column()==0){ return QVariant(FilesToAdd_.at(index.row()).filename);}
        if(index.column()==1){ return QVariant(FilesToAdd_.at(index.row()).filesize);}

    }
    else {
        return QVariant();
    }
    return QVariant();
}
QVariant FilesToAddListModel::headerData(int section, Qt::Orientation orientation,int role) const
    {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal){
        if(section==0) return QString("Secret file name");
        if(section==1) return QString("Size in MB");
        else           return QString("Column %1").arg(section);
        }
        else
            return QString("X");
    }

void FilesToAddListModel::removeRow(int row, const QModelIndex &parent)
{
     beginRemoveRows(parent, row, row);
     FilesToAdd_.erase(FilesToAdd_.begin()+row);
     endRemoveRows();
}

unsigned long FilesToAddListModel::get_sum_size(){
    return sum_size;
}
