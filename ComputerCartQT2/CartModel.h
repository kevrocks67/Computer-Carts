#pragma once

//#include <QAbstractListModel>
#include <QVariant>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

class CartModel : public QSqlQueryModel {
    Q_OBJECT

    public:
        CartModel(void);
        virtual ~CartModel();
        //virtual int rowCount(QModelIndex const& parent = QModelIndex()) const;
        //virtual QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const;
    public slots:
    private slots:
    private:
};
