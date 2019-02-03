//TODO Add, edit; use prepopulated modal with textboxes
//TODO Remove, have confirmation box

#include "ResModel.h"

ResModel::ResModel(void){
     QSqlDatabase cartdb = QSqlDatabase::addDatabase("QSQLITE");
     cartdb.setDatabaseName("carts.db");

     if(!cartdb.open()){
         qDebug()<<"DB did not open";
     }
     else{
         qDebug()<<"DB has connected";
     }
     setQuery("SELECT * from reservations");
     setHeaderData(0, Qt::Horizontal, tr("Reservation ID"));
     setHeaderData(1, Qt::Horizontal, tr("Cart Number"));
     setHeaderData(2, Qt::Horizontal, tr("Location"));
     setHeaderData(3, Qt::Horizontal, tr("Date"));
     setHeaderData(4, Qt::Horizontal, tr("Time"));
     setHeaderData(5, Qt::Horizontal, tr("Comments"));

     /*QSqlQuery qry;
     if(qry.exec("SELECT * from computercarts")){
         while(qry.next()) {
             qDebug() << qry.value(0).toString() << qry.value(1).toString()<< qry.value(2).toString()<< qry.value(3).toString()<< qry.value(4).toString()<< qry.value(5).toString()<<qry.value(6).toString();
         }
     }*/

}


ResModel::~ResModel(){

}

void ResModel::addCart(Cart &cart) {
    QSqlQuery query;

    query.prepare("INSERT INTO reservations "
                "VALUES (?, ?, ?, ?, ?, ?)");
    query.bindValue(0, cart.cartNo);
    query.bindValue(1, cart.cartType);
    query.bindValue(2, cart.cRoom);
    query.bindValue(3, cart.cPeriod);
    query.bindValue(4, 1);
    query.bindValue(5, 1);
    query.bindValue(6, "None");
    //query.bindValue(8, "CURRENT_TIMESTAMP");

    bool res = query.exec();
    qDebug()<<res;
}

/*
void CartModel::editCart(Cart &cart) {
    QSqlQuery qry;

                cur.execute("UPDATE computercarts set CartNumber = ?, ComputerType = ?, CurrentLocation = ?,\
                        TimeAtLocation = ?, FutureLocation = ?, FutureTime = ?\
                        where CartNumber = ?",(self.ids.cart_id_e.text, cart_type_e, cart_crm_e, cart_cpd_e, cart_frm_e, cart_fpd_e, self.ids.cart_id_e.text))
}*/

/*int CartModel::rowCount(QModelIndex const& parent) const {
    Q_UNUSED(parent);
}

QVariant CartModel::data(QModelIndex const& index, int role) const {

}*/
