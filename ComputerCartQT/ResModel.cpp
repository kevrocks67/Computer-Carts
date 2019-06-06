#include "ResModel.h"
#include <QModelIndex>
#include <QSqlRecord>

ResModel::ResModel(void){
     QSqlDatabase cartdb = QSqlDatabase::addDatabase("QSQLITE", "ResModelConnection");

     //PLACEHOLDER DB AND TABLE
     cartdb.setDatabaseName("carts.db");

     if(!cartdb.open()){
         qDebug()<<"DB did not open";
     }
     else{
         qDebug()<<"DB has connected";
     }

     setQuery("SELECT * from reservations");

     setHeaderData(0, Qt::Horizontal, tr("Cart Number"));
     setHeaderData(1, Qt::Horizontal, tr("Computer Type"));
     setHeaderData(2, Qt::Horizontal, tr("Quantity"));
     setHeaderData(3, Qt::Horizontal, tr("Current Room"));
     setHeaderData(4, Qt::Horizontal, tr("Current Period"));
     setHeaderData(5, Qt::Horizontal, tr("Future Reservation ID"));
     setHeaderData(6, Qt::Horizontal, tr("Cart Status"));
     setHeaderData(7, Qt::Horizontal, tr("Last Updated"));
}


ResModel::~ResModel(){

}

