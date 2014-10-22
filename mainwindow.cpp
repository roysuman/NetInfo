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
    if ( !createDb (  ) ){//popup message
	    std::cerr<<"Cant able tocreate db\n";
    }
    if ( !createTable( ) ){ // popup message
	    std::cerr<<"cant ableto create tables\n";
    }
    

    int localCount = noOfInterface;
    std::cout<<noOfInterface<<"::"<<interfaceList[ 0]<<std::endl;
    while ( localCount > 0 ){
        ui->cmbBxINterFaceList->addItem( QString( interfaceList[ localCount --] ));
    }
}



void MainWindow::startNetMonitor(){

	//start the timer
	boost::asio::deadline_timer t(io, boost::posix_time::seconds( 60 ));
	t.async_wait ( boost::bind ( &Sniffing::swapBufferIndex , this ,boost::asio::placeholders::error, &t ) );
	
	sniffingThread = boost::thread( boost::bind( &Sniffing::startSniffing, this , ui->cmbBxINterFaceList->currentText().toStdString() ) );
       // startSniffing(ui->cmbBxINterFaceList->currentText().toStdString() );

	io.run();


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
