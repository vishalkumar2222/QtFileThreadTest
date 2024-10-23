#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Global.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnChooseActionTriggered();
    void OnChooseThreadActionTriggered();
    void OnTimerTimeOut();
    void OnFileReadThreadFinished(FileInformation info);
private:
    Ui::MainWindow *ui;
    QTimer watch_timer;
    FileInformation GetFileInformation(const QString& filename);
    void AddInTable(const FileInformation& info);
};
#endif // MAINWINDOW_H
