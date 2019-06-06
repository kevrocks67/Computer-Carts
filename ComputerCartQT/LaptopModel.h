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
    public slots:
        void getLaptops(int cartno);
    private slots:
    signals:
    private:
};

