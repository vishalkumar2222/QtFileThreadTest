#ifndef FILEREADTHREAD_H
#define FILEREADTHREAD_H

#include <QThread>
#include "Global.h"

class FileReadThread : public QThread
{
    Q_OBJECT

public:
    FileReadThread(const QString& filename, QObject* parent = nullptr);

signals:
    void FileRead(FileInformation info);
private:
    void run() override;
    QString filename_;
};

#endif // FILEREADTHREAD_H
