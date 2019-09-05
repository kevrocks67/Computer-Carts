#ifndef DELETECART_H
#define DELETECART_H

#include "CartModel.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPointer>
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
        void setCartNum(int c);
    public slots:

    private slots:
        void delCartAction();
    private:
        int cartNo;

        QPointer<CartModel> cartModel;
        QPointer<QVBoxLayout> mainLayout;
        QPointer<QHBoxLayout> textLayout;
        QPointer<QHBoxLayout> buttonLayout;
        QPointer<QLabel> deleteMessage;
        QPointer<QLabel> cartNum;
        QPointer<QPushButton> cancelButton;
        QPointer<QPushButton> delButton;
};
#endif //DELETECART_H
