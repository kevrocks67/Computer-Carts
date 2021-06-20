#pragma once

#include <QDebug>
#include <QSettings>
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
            QString cPeriod;
            int resId;
            bool cartStatus;
            QString homeLoc;
            QString lockType;
            QString os;
            QString comments;
        };

    public slots:
        void addCart(CartModel::Cart &cart);
        void editCart(CartModel::Cart &cart);
        void deleteCart(int cartNo);
        CartModel::Cart getCart(int cartNo);
    private slots:
    signals:
    private:
        QSqlDatabase cartdb;
};
