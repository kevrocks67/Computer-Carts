#pragma once

//#include <QAbstractListModel>
#include <QDebug>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDateTime>
#include <QVariant>
#include <QString>
#include <QStringList>
#include <QSqlError>


class CartModel : public QSqlTableModel {
    Q_OBJECT

    public:
        //explicit CartModel(QObject *parent, QSqlDatabase cartd);
        explicit CartModel(QObject *parent = 0);
        virtual ~CartModel();
        struct Cart{
            int cartNo;
            QString compType;
            int quantity;
            QString cRoom;
            int cPeriod;
            int resId;
            bool status;
        }cart;

    public slots:
        void addCart(Cart &cart);
        void editCart(Cart &cart);
        void deleteCart(int cartNo);

    private slots:
    signals:
        void updateTable();
    private:
       // virtual QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const;
};
