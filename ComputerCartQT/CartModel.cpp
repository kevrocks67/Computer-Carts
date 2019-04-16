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
     /*
     setHeaderData(0, Qt::Horizontal, tr("Cart Number"));
     setHeaderData(1, Qt::Horizontal, tr("Cart Type"));
     setHeaderData(2, Qt::Horizontal, tr("Quantity"));
     setHeaderData(3, Qt::Horizontal, tr("Current Room"));
     setHeaderData(4, Qt::Horizontal, tr("Current Period"));
     setHeaderData(5, Qt::Horizontal, tr("Future Room"));
     setHeaderData(6, Qt::Horizontal, tr("Future Period"));
     setHeaderData(7, Qt::Horizontal, tr("Status")); */
     setHeaderData(0, Qt::Horizontal, tr("Cart Number"));
     setHeaderData(1, Qt::Horizontal, tr("Computer Type"));
     setHeaderData(2, Qt::Horizontal, tr("Quantity"));
     setHeaderData(3, Qt::Horizontal, tr("Current Room"));
     setHeaderData(4, Qt::Horizontal, tr("Current Period"));
     setHeaderData(5, Qt::Horizontal, tr("Future Reservation ID"));
     setHeaderData(6, Qt::Horizontal, tr("Cart Status"));
     setHeaderData(7, Qt::Horizontal, tr("Last Updated"));
     //QString test = "Test,something";
     //QStringList testlist = test.split(",");
     //qDebug()<<testlist[0];

     /*QSqlQuery qry;
     if(qry.exec("SELECT * from computercarts")){
         while(qry.next()) {
             qDebug() << qry.value(0).toString() << qry.value(1).toString()<< qry.value(2).toString()<< qry.value(3).toString()<< qry.value(4).toString()<< qry.value(5).toString()<<qry.value(6).toString();
         }
     }*/

}


CartModel::~CartModel(){

}

void CartModel::addCart(Cart &cart) {
    QSqlQuery query;
/*
    query.prepare("INSERT INTO computercarts "
                "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.bindValue(0, cart.cartNo);
    query.bindValue(1, cart.cartType);
    query.bindValue(2, cart.cRoom);
    query.bindValue(3, cart.cPeriod);
    query.bindValue(4, 1);
    query.bindValue(5, 1);
    query.bindValue(6, "None");
    //query.bindValue(8, "CURRENT_TIMESTAMP");
*/
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

    bool res = query.exec();
    //revert();
    //emit updateTable();
    /*if (query.exec()) {
        emit updateTable();
    }
    else {
        qDebug()<<query.lastError().text();
    }*/
    qDebug()<<"Add query resulted in: "<<res;
}


void CartModel::editCart(Cart &cart) {
    QSqlQuery query;

/*
cur.execute("UPDATE computercarts set CartNumber = ?, ComputerType = ?, CurrentLocation = ?,\
TimeAtLocation = ?, FutureLocation = ?, FutureTime = ?\
where CartNumber = ?",(self.ids.cart_id_e.text, cart_type_e, cart_crm_e,
cart_cpd_e, cart_frm_e, cart_fpd_e, self.ids.cart_id_e.text))*/

// SELECT data for cart to edit and populate edit modal,
//  possibly a separate function for that?

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


/*QVariant CartModel::data(QModelIndex const& index, int role) const {
return QVariant();
}*/
