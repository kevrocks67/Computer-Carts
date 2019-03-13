#ifndef DELETECART_H
#define DELETECART_H

#include "CartModel.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialog>

class CartModel;

class DeleteCart : public QDialog {
    Q_OBJECT

    public:
        explicit DeleteCart(QWidget * parent=0);
        virtual ~DeleteCart();
        void setRowNum(QString r);
    public slots:

    private slots:
        void delCartAction();
    private:
        CartModel *cartModel;
        QVBoxLayout *mainLayout;
        QHBoxLayout *buttonLayout;
        QLabel *deleteMessage;
        QLabel *rowNum;
        QPushButton *cancelButton;
        QPushButton *delButton;
        int row;
};
#endif //DELETECARTS_H
