#include "CartModel.h"

CartModel::CartModel(void) {
    QSqlDatabase cartdb = QSqlDatabase::addDatabase("QSQLITE");
    cartdb.setDatabaseName("carts.db");

    if(QFileInfo("carts.db").exists()){
        if(!cartdb.open()){
            qDebug()<<"DB did not open";
        }
        else{
            qDebug()<<"DB has connected";
        }
    }
    else{
        qDebug()<<"Could not find database";

        if(!cartdb.open()){
            qDebug()<<"DB did not open";
        }
        else{
            qDebug()<<"DB has connected";
            qDebug()<<"Creating carts.db with proper schema";

            QSqlQuery query;

            qDebug()<<"Creating table 'ComputerCarts'";
            query.exec("CREATE TABLE ComputerCarts (\n "
                           "\tCartNumber INTEGER PRIMARY KEY,\n"
                           "\tComputerType TEXT NOT NULL,\n"
                           "\tQuantity INTEGER DEFAULT NULL,\n"
                           "\tCurrentLocation TEXT DEFAULT NULL,\n"
                           "\tCurrentLocTime TEXT DEFAULT NULL,\n"
                           "\tFutureResId INTEGER DEFAULT NULL,\n"
                           "\tCartStatus BOOLEAN DEFAULT NULL,\n"
                           "\tOS TEXT NOT NULL,\n"
                           "\tLockType TEXT DEFAULT NULL,\n"
                           "\tHomeLocation TEXT DEFAULT NULL,\n"
                           "\tLastUpdate DATETIME,\n"
                           "\tComments TEXT DEFAULT NULL\n);");
            qDebug()<<"Table 'ComputerCarts' has been created";

            qDebug()<<"Creating table 'Reservations'";
            query.exec("CREATE TABLE Reservations (\n"
                            "\tResId INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\n"
                            "\tCartNumber INTEGER DEFAULT NULL,\n"
                            "\tLocation TEXT NOT NULL,\n"
                            "\tDate TEXT NOT NULL,\n"
                            "\tTime INTEGER NOT NULL,\n"
                            "\tComments TEXT DEFAULT NULL\n);");
            qDebug()<<"Table 'reservations' has been created";

            qDebug()<<"Creating table 'Laptops'";
            query.exec("CREATE TABLE Laptops (\n"
                            "\tAssetID TEXT type UNIQUE DEFAULT NULL,\n"
                            "\tBrand TEXT NOT NULL,\n"
                            "\tGenericName TEXT NOT NULL,\n"
                            "\tModel TEXT DEFAULT NULL,\n"
                            "\tSerial TEXT DEFAULT NULL,\n"
                            "\tOS TEXT NOT NULL,\n"
                            "\tCartNumber INTEGER DEFAULT NULL,\n"
                            "\tStatus TEXT,\n"
                            "\tIsDeployed BOOLEAN NOT NULL,\n"
                            "\tFOREIGN KEY(CartNumber) REFERENCES ComputerCarts(CartNumber)\n);");
            qDebug()<<"Table 'Laptops' has been created";

            qDebug()<<"Enabling properties";
            query.exec("PRAGMA foreign_keys = ON;");

            qDebug()<<"Adding Cart Number 0";
            query.exec("INSERT INTO ComputerCarts (CartNumber, ComputerType, OS) VALUES (0, \"Several\", \"Several\")");

            qDebug()<<"carts.db is ready for use";
        }
    }

    setQuery("SELECT * from computercarts");

    setHeaderData(0, Qt::Horizontal, tr("Cart Number"));
    setHeaderData(1, Qt::Horizontal, tr("Computer Type"));
    setHeaderData(2, Qt::Horizontal, tr("Quantity"));
    setHeaderData(3, Qt::Horizontal, tr("Current Room"));
    setHeaderData(4, Qt::Horizontal, tr("Current Periods"));
    setHeaderData(7, Qt::Horizontal, tr("OS"));
    setHeaderData(9, Qt::Horizontal, tr("Home Location"));
    setHeaderData(10, Qt::Horizontal, tr("Last Updated"));
}


CartModel::~CartModel(){

}

void CartModel::addCart(Cart &cart) {
    QSqlQuery query;

    query.prepare("INSERT INTO computercarts "
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.bindValue(0, QVariant(QVariant::Int));
    query.bindValue(1, cart.compType);
    query.bindValue(2, cart.quantity);
    query.bindValue(3, cart.cRoom);
    query.bindValue(4, cart.cPeriod);
    query.bindValue(5, QVariant(QVariant::Int));
    query.bindValue(6, QVariant(QVariant::Bool));
    query.bindValue(7, cart.os);
    query.bindValue(8, cart.lockType);
    query.bindValue(9, cart.homeLoc);
    query.bindValue(10, QDateTime::currentDateTime());
    query.bindValue(11, cart.comments);

    if (query.exec()) {
        qDebug()<<"Add query success";
    }
    else {
        qDebug()<<query.lastError().text();
    }

}

void CartModel::editCart(Cart &cart) {
    QSqlQuery query;

    if(cart.cartNo) {
        query.prepare("UPDATE ComputerCarts SET ComputerType=?,\
                                                Quantity=?,\
                                                CurrentLocation=?,\
                                                CurrentLocTime=?,\
                                                OS=?,\
                                                LockType=?,\
                                                HomeLocation=?,\
                                                LastUpdate=?,\
                                                Comments=?\
                       where CartNumber=?");

        query.bindValue(0, cart.compType);
        query.bindValue(1, cart.quantity);
        query.bindValue(2, cart.cRoom);
        query.bindValue(3, cart.cPeriod);
        query.bindValue(4, cart.os);
        query.bindValue(5, cart.lockType);
        query.bindValue(6, cart.homeLoc);
        query.bindValue(7, QDateTime::currentDateTime());
        query.bindValue(8, cart.comments);
        query.bindValue(9, cart.cartNo);
    }

    if (query.exec()) {
        qDebug()<<"Edited cart no: "<<cart.cartNo;
    }
    else {
        qDebug()<<query.lastError().text();
    }
}

CartModel::Cart CartModel::getCart(int cartNo) {
    QSqlQuery query;
    Cart cartDetails;

    if(cartNo) {
        query.prepare("SELECT * FROM computercarts where CartNumber=?");
        query.bindValue(0, cartNo);
    }

    if (query.exec()) {
        query.first();
        cartDetails.compType  = query.value(1).toString();
        cartDetails.quantity = query.value(2).toInt();
        cartDetails.cRoom = query.value(3).toString();
        cartDetails.cPeriod = query.value(4).toString();
        cartDetails.os = query.value(7).toString();
        cartDetails.lockType = query.value(8).toString();
        cartDetails.homeLoc = query.value(9).toString();
        cartDetails.comments = query.value(11).toString();
    }
    else {
        qDebug()<<query.lastError().text();
    }
    return cartDetails;
}

void CartModel::deleteCart(int cartNo) {
    QSqlQuery query;

    if(cartNo) {
        query.prepare("DELETE FROM computercarts where CartNumber=?");
        query.bindValue(0, cartNo);
    }

    if (query.exec()) {
        qDebug()<<"Deleted cart number: "<<cartNo;
    }
    else {
        qDebug()<<query.lastError().text();
    }
}
