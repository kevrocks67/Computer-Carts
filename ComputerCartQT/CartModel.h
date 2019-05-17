#pragma once

#include <QDebug>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QVariant>
#include <QString>
#include <QStringList>
#include <QSqlError>
#include <QModelIndex>
#include <QFileInfo>


class CartModel : public QSqlQueryModel {
    Q_OBJECT

    public:
        explicit CartModel(void);
        virtual ~CartModel();
        struct Cart {
            int cartNo;
            QString compType;
            int quantity;
            QString cRoom;
            int cPeriod;
            int resId;
            bool status;
        } cart;

    public slots:
        void addCart(Cart &cart);
        void editCart(Cart &cart);
        void deleteCart(int cartNo);
        CartModel::Cart getCart(int cartNo);
    private slots:
    signals:
    private:
};
