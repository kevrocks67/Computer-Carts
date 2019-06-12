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

void LaptopModel::getLaptops() {
     setQuery("SELECT * from Laptops");
}

void LaptopModel::getLaptops(int cartno) {
     QSqlQuery query;
     query.prepare("SELECT * from Laptops where CartNumber=?");
     query.bindValue(0, cartno);
     query.exec();
     setQuery(query);
}

QStringList LaptopModel::getBrands() {
    QStringList brands;
    QSqlQuery query("SELECT DISTINCT Brand from Laptops");
    while(query.next()) {
        brands << query.value(0).toString();
    }
    return brands;
}

QStringList LaptopModel::getGNames() {
    QStringList names;
    QSqlQuery query("SELECT DISTINCT GenericName from Laptops");
    while(query.next()) {
        names << query.value(0).toString();
    }
    return names;
}

void LaptopModel::addLaptop(Laptop laptop) {
    QSqlQuery query;
    query.prepare("INSERT INTO Laptops "
                  "VALUES(?, ?, ?, ?, ?, ?, ?, ?)");
    query.bindValue(0, laptop.AssetID);
    query.bindValue(1, laptop.Brand);
    query.bindValue(2, laptop.GenericName);
    query.bindValue(3, laptop.Model);
    //query.bindValue(4, laptop.Serial);
    query.bindValue(4, laptop.OS);
    query.bindValue(5, laptop.CartNumber);
    query.bindValue(6, laptop.Status);
    query.bindValue(7, laptop.IsDeployed);
    /*
    query.bindValue(5, laptop.OS);
    query.bindValue(6, laptop.CartNumber);
    query.bindValue(7, laptop.Status);
    query.bindValue(8, laptop.IsDeployed);
    */
    if (query.exec()) {
        qDebug()<<"Add query success";
    } else {
        qDebug()<<query.lastError().text();
    }
}

void LaptopModel::deleteLaptop(QString asset, QString gName) {

}

LaptopModel::~LaptopModel(){

}


