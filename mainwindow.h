#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QtSql>
#include <boost/thread.hpp>

#include "capture.hpp"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow , public Sniffing
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    public slots:
	    void startNetMonitor( );

    void stopMonitoring();

    //QSqlTableModel *mode;
    
private:
    Ui::MainWindow *ui;
     boost::thread sniffingThread;
};

#endif // MAINWINDOW_H
