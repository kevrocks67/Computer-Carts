//TODO Add, edit, remove functions
//TODO Link to view

#include "CartModel.h"
#include <iostream>
#include <QDebug>

CartModel::CartModel(void){
     QSqlDatabase cartdb = QSqlDatabase::addDatabase("QSQLITE");
     cartdb.setDatabaseName("carts.db");

     if(!cartdb.open()){
         std::cout<<"DB did not open"<<std::endl;
     }
     else{
         std::cout<<"DB has connected"<<std::endl;
     }

     QSqlQuery qry;
     if(qry.exec("SELECT * from computercarts")){
         while(qry.next()) {
             qDebug() << qry.value(0).toString() << qry.value(1).toString()<< qry.value(2).toString()<< qry.value(3).toString()<< qry.value(4).toString()<< qry.value(5).toString()<<qry.value(6).toString();
         }
     }
         
}


CartModel::~CartModel(){
    
}

/*int CartModel::rowCount(QModelIndex const& parent) const {
    Q_UNUSED(parent);
}

QVariant CartModel::data(QModelIndex const& index, int role) const {

}*/
