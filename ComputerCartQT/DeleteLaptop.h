#ifndef DELETELAPTOP_H
#define DELETELAPTOP_H
#include "LaptopModel.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QPointer>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialog>

class LaptopModel;

class DeleteLaptop : public QDialog {
    Q_OBJECT

    public:
        explicit DeleteLaptop(LaptopModel &lapModel);
        virtual ~DeleteLaptop();
    public slots:
        void setLapDetails(QString asset, QString gName);
    private slots:
        void delLaptopAction();
    private:
        LaptopModel &model;
        QString asset;
        QString gName;

        QPointer<QVBoxLayout> mainLayout;
        QPointer<QVBoxLayout> textLayout;
        QPointer<QHBoxLayout> buttonLayout;
        QPointer<QLabel> deleteMessage;
        QPointer<QLabel> detailsLabel;
        QPointer<QPushButton> cancelButton;
        QPointer<QPushButton> delButton;
};
#endif //DELETELAPTOP_H
