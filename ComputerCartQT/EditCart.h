#ifndef EDITCART_H
#define EDITCART_H

#include "CartModel.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialog>
#include <QDebug>

class CartModel;

class EditCart : public QDialog {
    Q_OBJECT

    public:
        explicit EditCart(QWidget * parent=0);
        virtual ~EditCart();
    public slots:
        void setCartNum(int c);
    private slots:
        void editCartAction();
    private:
        CartModel  *cartModel;
        CartModel::Cart cartDetails;
        QVBoxLayout *mainLayout;
        QVBoxLayout *fieldLayout;
        QHBoxLayout *buttonLayout;
        QLabel *cNumLabel;
        QLineEdit *typeField;
        QLineEdit *quantField;
        QLineEdit *cRoomField;
        QLineEdit *cPeriodField;
        QPushButton *cancelButton;
        QPushButton *editButton;
        int cartNo;
};
#endif //ADDCART_H
