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
        explicit LaptopModel(QString connString);
        virtual ~LaptopModel();
        struct Laptop {
            QString AssetID;
            QString OldAssetID;
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
        LaptopModel::Laptop getLaptop(QString asset, QString gName);
        void getLaptops();
        void getLaptops(int cartno);
        void addLaptop(Laptop laptop);
        void editLaptop(Laptop laptop);
        void deleteLaptop(QString asset, QString gName);
        QStringList getBrands();
        QStringList getGNames();
        QStringList getCarts();
    private slots:
    signals:
    private:
};

