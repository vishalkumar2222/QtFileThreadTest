#include "FileReadThread.h"
#include <QFile>

FileReadThread::FileReadThread(const QString &filename, QObject *parent)
    :QThread(parent), filename_(filename){}

void FileReadThread::run()
{
    QFile file(filename_);
    int count = 0;
    if(file.open(QIODevice::ReadOnly)){
        while (!file.atEnd()) {
            QString line = file.readLine();
            ++count;
        }
        file.close();
    }
    FileInformation info;
    if(count != 0){
        info.filename = filename_;
        info.num_of_line = count;
    }
    emit FileRead(info);
    exit();
}
