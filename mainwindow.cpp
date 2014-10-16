#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIconText("NetInfo");


    connect( ui->pshBttnStart , SIGNAL( clicked()) , SLOT( startNetMonitor() )) ;
    connect ( ui->pshBttnStop , SIGNAL ( clicked()) ,SLOT ( stopMonitoring() ));
    int localCount = noOfInterface;
    std::cout<<noOfInterface<<"::"<<interfaceList[ 0]<<std::endl;
    while ( localCount > 0 ){
        ui->cmbBxINterFaceList->addItem( QString( interfaceList[ localCount --] ));
    }
}



void MainWindow::startNetMonitor(){
    sniffingThread = boost::thread( boost::bind( &Sniffing::startSniffing, this , ui->cmbBxINterFaceList->currentText().toStdString() ) );


 //   if( startSniffing( ui->cmbBxINterFaceList->currentText().toStdString()));



}
void MainWindow::stopMonitoring(){
    stopSniffing();
    std::cout<<"DONR\n";
  //  sniffingThread.join();
}

MainWindow::~MainWindow()
{
    delete ui;
}
