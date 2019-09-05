#include "LaptopModel.h"
#include <QModelIndex>
#include <QSqlRecord>

LaptopModel::LaptopModel(QString connString){
     QSettings settings("config.ini", QSettings::IniFormat);
     QString dbDriver = settings.value("db/db_type").toString();
     QString dbHost = settings.value("db/db_host").toString();
     QString dbUser = settings.value("db/db_user").toString();
     QString dbPass = settings.value("db/db_pass").toString();

     if(dbDriver != "")
         cartdb = QSqlDatabase::addDatabase(dbDriver, connString);
     else
         cartdb = QSqlDatabase::addDatabase("QSQLITE", connString);

     if(dbDriver == "QMYSQL"){
         cartdb.setHostName(dbHost);
         cartdb.setDatabaseName("ComputerCarts");
         cartdb.setUserName(dbUser);
         cartdb.setPassword(dbPass);

         if(!cartdb.open()){
             qDebug()<<"DB did not open";
         }
         else{
             qDebug()<<"DB has connected";
         }
     } else {
         cartdb.setDatabaseName("carts.db");

         if(!cartdb.open()){
             qDebug()<<"DB did not open";
         }
         else{
             qDebug()<<"DB has connected";
         }
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

LaptopModel::Laptop LaptopModel::getLaptop(QString asset, QString gName) {
    QSqlQuery query;
    Laptop laptop;
    query.prepare("Select * from Laptops where AssetID=? AND GenericName=?");
    query.bindValue(0, asset);
    query.bindValue(1, gName);
    if (query.exec()) {
        query.first();
        laptop.AssetID = query.value(0).toString();
        laptop.Brand = query.value(1).toString();
        laptop.GenericName = query.value(2).toString();
        laptop.Model = query.value(3).toString();
        laptop.Serial = query.value(4).toString();
        laptop.OS = query.value(5).toString();
        laptop.CartNumber = query.value(6).toInt();
        laptop.Status = query.value(7).toString();
        laptop.IsDeployed = query.value(8).toBool();
    } else {
        qDebug()<<query.lastError().text();
    }
    return laptop;
}

void LaptopModel::getLaptops() {
     setQuery("SELECT * from Laptops");
}

void LaptopModel::getLaptops(int cartno) {
     QSqlQuery query;
     query.prepare("SELECT * from Laptops where CartNumber=?");
     query.bindValue(0, QString::number(cartno));
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

QStringList LaptopModel::getCarts() {
    QStringList carts;
    QSqlQuery query("SELECT Distinct CartNumber from ComputerCarts");
    while(query.next()) {
        carts << query.value(0).toString();
    }
    return carts;
}

void LaptopModel::addLaptop(Laptop laptop) {
    QSqlQuery query;
    query.prepare("INSERT INTO Laptops "
                  "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.bindValue(0, laptop.AssetID);
    query.bindValue(1, laptop.Brand);
    query.bindValue(2, laptop.GenericName);
    query.bindValue(3, laptop.Model);
    query.bindValue(4, laptop.Serial);
    query.bindValue(5, laptop.OS);
    query.bindValue(6, laptop.CartNumber);
    query.bindValue(7, laptop.Status);
    query.bindValue(8, laptop.IsDeployed);

    if (query.exec()) {
        qDebug()<<"Add query success";
    } else {
        qDebug()<<query.lastError().text();
    }
}

void LaptopModel::editLaptop(Laptop laptop) {
    QSqlQuery query;
    query.prepare("UPDATE Laptops SET AssetID=?,\
                                      Brand=?,\
                                      GenericName=?,\
                                      Model=?,\
                                      Serial=?,\
                                      OS=?,\
                                      CartNumber=?,\
                                      Status=?,\
                                      IsDeployed=?\
                   WHERE AssetID=?");
    query.bindValue(0, laptop.AssetID);
    query.bindValue(1, laptop.Brand);
    query.bindValue(2, laptop.GenericName);
    query.bindValue(3, laptop.Model);
    query.bindValue(4, laptop.Serial);
    query.bindValue(5, laptop.OS);
    query.bindValue(6, laptop.CartNumber);
    query.bindValue(7, laptop.Status);
    query.bindValue(8, laptop.IsDeployed);
    query.bindValue(9, laptop.OldAssetID);

    if (query.exec()) {
        qDebug()<<"Edit query success";
    } else {
        qDebug()<<query.lastError().text();
    }
}

void LaptopModel::deleteLaptop(QString asset, QString gName) {
    QSqlQuery query;
    query.prepare("DELETE FROM Laptops WHERE AssetID=? AND GenericName=?");
    query.bindValue(0, asset);
    query.bindValue(1, gName);
    query.exec();
    qDebug()<<"Deleted laptop asset: "+asset;
}

LaptopModel::~LaptopModel(){
    cartdb.close();
}


