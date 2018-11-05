#pragma once

//#include <QAbstractListModel>
#include <QDebug>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QString>
#include <QStringList>

class CartModel : public QSqlQueryModel {
    Q_OBJECT

    public:
        CartModel(void);
        virtual ~CartModel();
        //virtual int rowCount(QModelIndex const& parent = QModelIndex()) const;
        //virtual QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const;
        /*
        struct cartDetails{
            int cartNo;
            QString cartType;
            int quantity;
            QString cRoom;
            int cPeriod;
            QString fRoom;
            QString fPeriod;
            bool status;
        }cart;
        */
    public slots:
    private slots:
        //addCart(cartDetails);
    private:
};
