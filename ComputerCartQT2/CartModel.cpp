//TODO Add, edit; use prepopulated modal with textboxes
//TODO Remove, have confirmation box 

#include "CartModel.h"

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
     setHeaderData(1, Qt::Horizontal, tr("Cart Type"));
     setHeaderData(2, Qt::Horizontal, tr("Quantity"));
     setHeaderData(3, Qt::Horizontal, tr("Current Room"));
     setHeaderData(4, Qt::Horizontal, tr("Current Period"));
     setHeaderData(5, Qt::Horizontal, tr("Future Room"));
     setHeaderData(6, Qt::Horizontal, tr("Future Period"));
     setHeaderData(7, Qt::Horizontal, tr("Status"));
     
     QString test = "Test,something";
     QStringList testlist = test.split(",");
     qDebug()<<testlist[0];

     /*QSqlQuery qry;
     if(qry.exec("SELECT * from computercarts")){
         while(qry.next()) {
             qDebug() << qry.value(0).toString() << qry.value(1).toString()<< qry.value(2).toString()<< qry.value(3).toString()<< qry.value(4).toString()<< qry.value(5).toString()<<qry.value(6).toString();
         }
     }*/
         
}


CartModel::~CartModel(){
    
}

/*int CartModel::rowCount(QModelIndex const& parent) const {
    Q_UNUSED(parent);
}

QVariant CartModel::data(QModelIndex const& index, int role) const {

}*/
