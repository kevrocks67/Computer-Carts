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


class LaptopModel : public QSqlQueryModel {
    Q_OBJECT

    public:
        explicit LaptopModel(void);
        virtual ~LaptopModel();
        struct Laptop {
            QString AssetID;
            QString Brand;
            QString GenericName;
            QString Model;
            QString Serial;
            QString OS;
            int CartNumber;
            QString Status;
            bool IsDeployed;
        };
    public slots:
        void getLaptops(int cartno);
        void addLaptop(Laptop laptop);
        QStringList getBrands();
        QStringList getGNames();
    private slots:
    signals:
    private:
};

