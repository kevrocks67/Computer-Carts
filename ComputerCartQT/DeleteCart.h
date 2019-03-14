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
        void setCartNum(int c);
    public slots:

    private slots:
        void delCartAction();
    private:
        CartModel *cartModel;
        QVBoxLayout *mainLayout;
        QHBoxLayout *textLayout;
        QHBoxLayout *buttonLayout;
        QLabel *deleteMessage;
        QLabel *cartNum;
        QPushButton *cancelButton;
        QPushButton *delButton;
        int cartNo;
};
#endif //DELETECARTS_H
