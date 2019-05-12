#include "CartModel.h"
#include <QModelIndex>
#include <QSqlRecord>

CartModel::CartModel(void){
     QSqlDatabase cartdb = QSqlDatabase::addDatabase("QSQLITE");
     cartdb.setDatabaseName("carts.db");

     if(!cartdb.open()){
         qDebug()<<"DB did not open";
     }
     else{
         qDebug()<<"DB has connected";
     }

     setQuery("SELECT * from computercarts");

     setHeaderData(0, Qt::Horizontal, tr("Cart Number"));
     setHeaderData(1, Qt::Horizontal, tr("Computer Type"));
     setHeaderData(2, Qt::Horizontal, tr("Quantity"));
     setHeaderData(3, Qt::Horizontal, tr("Current Room"));
     setHeaderData(4, Qt::Horizontal, tr("Current Period"));
     setHeaderData(5, Qt::Horizontal, tr("Future Reservation ID"));
     setHeaderData(6, Qt::Horizontal, tr("Cart Status"));
     setHeaderData(7, Qt::Horizontal, tr("Last Updated"));
}


CartModel::~CartModel(){

}

void CartModel::addCart(Cart &cart) {
    QSqlQuery query;

    query.prepare("INSERT INTO computercarts "
                "VALUES ( ?, ?, ?, ?, ?, ?, ?, ?)");
    query.bindValue(0, QVariant(QVariant::Int));
    query.bindValue(1, cart.compType);
    query.bindValue(2, cart.quantity);
    query.bindValue(3, cart.cRoom);
    query.bindValue(4, cart.cPeriod);
    query.bindValue(5, QVariant(QVariant::Int));
    query.bindValue(6, QVariant(QVariant::Bool));
    query.bindValue(7, QDateTime::currentDateTime());

    if (query.exec()) {
        qDebug()<<"Add query success";
    }
    else {
        qDebug()<<query.lastError().text();
    }

}


void CartModel::editCart(Cart &cart) {
    QSqlQuery query;

    query.prepare("UPDATE computercarts set ComputerType=?,\
                                            Quantity=?,\
                                            CurrentLocation=?,\
                                            CurrentLocTime=?,\
                                            LastUpdate=?\
                   where CartNumber=?");

    query.bindValue(0, cart.compType);
    query.bindValue(1, cart.quantity);
    query.bindValue(2, cart.cRoom);
    query.bindValue(3, cart.cPeriod);
    query.bindValue(4, QDateTime::currentDateTime());
    query.bindValue(5, cart.cartNo);

    if (query.exec()) {
        qDebug()<<"Edited cart no: "<<cart.cartNo;
    }
    else {
        qDebug()<<query.lastError().text();
    }
}

CartModel::Cart CartModel::getEditCart(int cartNo) {
    QSqlQuery query;

    query.prepare("SELECT * FROM computercarts where CartNumber=?");
    query.bindValue(0, cartNo);

    Cart cartDetails;

    if (query.exec()) {
        query.first();
        cartDetails.compType  = query.value(1).toString();
        cartDetails.quantity = query.value(2).toInt();
        cartDetails.cRoom = query.value(3).toString();
        cartDetails.cPeriod = query.value(4).toInt();
    }
    else {
        qDebug()<<query.lastError().text();
    }
    return cartDetails;
}

void CartModel::deleteCart(int cartNo) {
    QSqlQuery query;

    query.prepare("DELETE FROM computercarts where CartNumber=?");
    query.bindValue(0, cartNo);

    if (query.exec()) {
        qDebug()<<"Deleted cart number: "<<cartNo;
    }
    else {
        qDebug()<<query.lastError().text();
    }
}
