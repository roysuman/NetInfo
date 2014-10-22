#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QtSql>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include "databaseManagement.hpp"
#include "capture.hpp"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow , public Sniffing , public database::DbManager
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
