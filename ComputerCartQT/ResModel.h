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


class ResModel : public QSqlQueryModel {
    Q_OBJECT

    public:
        explicit ResModel(void);
        virtual ~ResModel();
    public slots:
    private slots:
    signals:
    private:
};
