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

int LaptopModel::getLaptopQuantity(int cartno) {
    QSqlQuery query;
    int quantity = -1;
    query.prepare("SELECT COUNT(*) from Laptops WHERE CartNumber=?");
    query.bindValue(0, cartno);
    query.exec();
    while(query.next()) {
        quantity = query.value(0).toInt();
    }
    return quantity;
}

void LaptopModel::addLaptop(LaptopModel::Laptop laptop) {
    QSqlQuery addQuery, updateCartQuery;
    addQuery.prepare("INSERT INTO Laptops "
                  "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?)");

    addQuery.bindValue(0, laptop.AssetID);
    addQuery.bindValue(1, laptop.Brand);
    addQuery.bindValue(2, laptop.GenericName);
    addQuery.bindValue(3, laptop.Model);
    addQuery.bindValue(4, laptop.Serial);
    addQuery.bindValue(5, laptop.OS);
    addQuery.bindValue(6, laptop.CartNumber);
    addQuery.bindValue(7, laptop.Status);
    addQuery.bindValue(8, laptop.IsDeployed);

    if (addQuery.exec()) {
        qDebug()<<"Add query success";

        int laptopQuant = getLaptopQuantity(laptop.CartNumber);

        //Update LastUpdate time for parent cart
        updateCartQuery.prepare("UPDATE ComputerCarts SET Quantity=?,LastUpdate=? WHERE CartNumber=?");
        updateCartQuery.bindValue(0, laptopQuant);
        updateCartQuery.bindValue(1, QDateTime::currentDateTime());
        updateCartQuery.bindValue(2, laptop.CartNumber);

        if (updateCartQuery.exec()) {
            qDebug() << "Updated cart LastUpdate";
        } else {
            qDebug()<<addQuery.lastError().text();
        }
    } else {
        qDebug()<<addQuery.lastError().text();
    }
    emit updateCart();
}

void LaptopModel::editLaptop(LaptopModel::Laptop laptop) {
    QSqlQuery editQuery, updateCartQuery, updateOldCartQuery;

    editQuery.prepare("UPDATE Laptops SET AssetID=?,\
                                      Brand=?,\
                                      GenericName=?,\
                                      Model=?,\
                                      Serial=?,\
                                      OS=?,\
                                      CartNumber=?,\
                                      Status=?,\
                                      IsDeployed=?\
                   WHERE AssetID=?");
    editQuery.bindValue(0, laptop.AssetID);
    editQuery.bindValue(1, laptop.Brand);
    editQuery.bindValue(2, laptop.GenericName);
    editQuery.bindValue(3, laptop.Model);
    editQuery.bindValue(4, laptop.Serial);
    editQuery.bindValue(5, laptop.OS);
    editQuery.bindValue(6, laptop.CartNumber);
    editQuery.bindValue(7, laptop.Status);
    editQuery.bindValue(8, laptop.IsDeployed);
    editQuery.bindValue(9, laptop.OldAssetID);

    if (editQuery.exec()) {
        qDebug()<<"Edit query success";

        //Update Quantity and LastUpdate time for parent cart
        int laptopQuant = getLaptopQuantity(laptop.CartNumber);

        updateCartQuery.prepare("UPDATE ComputerCarts SET Quantity=?,LastUpdate=? WHERE CartNumber=?");
        updateCartQuery.bindValue(0, laptopQuant);
        updateCartQuery.bindValue(1, QDateTime::currentDateTime());
        updateCartQuery.bindValue(2, laptop.CartNumber);
        updateCartQuery.exec();

        if (laptop.CartNumber != laptop.OldCartNumber) {
            int laptopQuantOld = getLaptopQuantity(laptop.OldCartNumber);
            updateOldCartQuery.prepare("UPDATE ComputerCarts SET Quantity=?,LastUpdate=? WHERE CartNumber=?");
            updateOldCartQuery.bindValue(0, laptopQuantOld);
            updateOldCartQuery.bindValue(1, QDateTime::currentDateTime());
            updateOldCartQuery.bindValue(2, laptop.OldCartNumber);
            updateOldCartQuery.exec();
        }
    } else {
        qDebug()<<editQuery.lastError().text();
    }
    emit updateCart();
}

void LaptopModel::deleteLaptop(QString asset, QString gName) {
    QSqlQuery deleteQuery, getCartQuery, updateCartQuery;
    int cartNum = -1;

    //Get cart number of laptop
    getCartQuery.prepare("SELECT CartNumber FROM Laptops WHERE AssetID=? AND GenericName=?");
    getCartQuery.bindValue(0, asset);
    getCartQuery.bindValue(1, gName);
    getCartQuery.exec();
    while(getCartQuery.next()) {
        cartNum = getCartQuery.value(0).toInt();
    }

    //Delete the laptop
    deleteQuery.prepare("DELETE FROM Laptops WHERE AssetID=? AND GenericName=?");
    deleteQuery.bindValue(0, asset);
    deleteQuery.bindValue(1, gName);
    deleteQuery.exec();

    //Update LastUpdate time for parent cart
    int laptopQuant = getLaptopQuantity(cartNum);

    updateCartQuery.prepare("UPDATE ComputerCarts SET Quantity=?,LastUpdate=? WHERE CartNumber=?");
    updateCartQuery.bindValue(0, laptopQuant);
    updateCartQuery.bindValue(1, QDateTime::currentDateTime());
    updateCartQuery.bindValue(2, cartNum);
    updateCartQuery.exec();

    qDebug()<<"Deleted laptop asset: "+asset;
    emit updateCart();
}

LaptopModel::~LaptopModel(){
    cartdb.close();
}


