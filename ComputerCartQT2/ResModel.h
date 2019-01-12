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


class ResModel : public QSqlQueryModel {
    Q_OBJECT

    public:
        explicit ResModel(void);
        virtual ~ResModel();
        struct Cart{
            int cartNo;
            QString cartType;
            int quantity;
            QString cRoom;
            int cPeriod;
        }cart;

        //virtual int rowCount(QModelIndex const& parent = QModelIndex()) const;
        //virtual QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const;
    public slots:
        void addCart(Cart &cart);
    private slots:
    private:
};
