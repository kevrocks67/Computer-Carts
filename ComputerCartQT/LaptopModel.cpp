#include "LaptopModel.h"
#include <QModelIndex>
#include <QSqlRecord>

LaptopModel::LaptopModel(void){
     QSqlDatabase cartdb = QSqlDatabase::addDatabase("QSQLITE", "LaptopModelConnection");

     //PLACEHOLDER DB AND TABLE
     cartdb.setDatabaseName("carts.db");

     if(!cartdb.open()){
         qDebug()<<"DB did not open";
     }
     else{
         qDebug()<<"DB has connected";
     }

     setHeaderData(0, Qt::Horizontal, tr("AssetID"));
     setHeaderData(1, Qt::Horizontal, tr("Brand"));
     setHeaderData(2, Qt::Horizontal, tr("Generic Name"));
     setHeaderData(3, Qt::Horizontal, tr("Model"));
     setHeaderData(4, Qt::Horizontal, tr("OS"));
     setHeaderData(5, Qt::Horizontal, tr("Cart Number"));
     setHeaderData(6, Qt::Horizontal, tr("Status"));
     setHeaderData(7, Qt::Horizontal, tr("IsDeployed"));
}

void LaptopModel::getLaptops(int cartno) {
     QSqlQuery query;
     query.prepare("SELECT * from Laptops where CartNumber=?");
     query.bindValue(0, cartno);
     query.exec();
     setQuery(query);
}

LaptopModel::~LaptopModel(){

}


