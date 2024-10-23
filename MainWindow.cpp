#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QList>
#include <QFile>
#include <QTime>
#include "FileReadThread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_Choose_File, &QAction::triggered, this, &MainWindow::OnChooseActionTriggered);
    connect(ui->action_Choose_File_thread, &QAction::triggered, this, &MainWindow::OnChooseThreadActionTriggered);
    connect(&watch_timer, &QTimer::timeout, this, &MainWindow::OnTimerTimeOut);
    watch_timer.start(1000);
    OnTimerTimeOut();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnChooseActionTriggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Choose Files"));
    for(const QString& filename : files){
        auto info = GetFileInformation(filename);
        AddInTable(info);
    }
}

void MainWindow::OnChooseThreadActionTriggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Choose Files"));
    for(const QString& filename : files){
        FileReadThread* thread = new FileReadThread(filename, this);
        connect(thread, &FileReadThread::FileRead, this, &MainWindow::OnFileReadThreadFinished);
        thread->start();
    }
}

void MainWindow::OnTimerTimeOut()
{
    QString time_now = QDateTime::currentDateTime().toString(QString("hh:mm:ss"));
    ui->label->setText(time_now);
}

void MainWindow::OnFileReadThreadFinished(FileInformation info)
{
    AddInTable(info);
    FileReadThread* thread = qobject_cast<FileReadThread*>(sender());
    if(thread != nullptr){
        thread->deleteLater();
    }
}

FileInformation MainWindow::GetFileInformation(const QString &filename)
{
    QFile file(filename);
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
        info.filename = filename;
        info.num_of_line = count;
    }
    return info;
}

void MainWindow::AddInTable(const FileInformation &info)
{
    if(!info.filename.isEmpty()){
        int row_count = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row_count);
        QTableWidgetItem* filename_item = new QTableWidgetItem;
        filename_item->setText(info.filename);
        ui->tableWidget->setItem(row_count, 0, filename_item);
        QTableWidgetItem* num_of_line_item = new QTableWidgetItem;
        num_of_line_item->setText(QString::number(info.num_of_line));
        ui->tableWidget->setItem(row_count, 1, num_of_line_item);
        ui->tableWidget->resizeColumnsToContents();
    }
}
