#ifndef EDITCART_H
#define EDITCART_H

#include "CartModel.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPointer>
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
        int cartNo;
        CartModel::Cart cartDetails;

        QPointer<CartModel> cartModel;
        QPointer<QVBoxLayout> mainLayout;
        QPointer<QVBoxLayout> fieldLayout;
        QPointer<QHBoxLayout> buttonLayout;
        QPointer<QLabel> cNumLabel;
        QPointer<QLineEdit> typeField;
        QPointer<QLineEdit> quantField;
        QPointer<QLineEdit> cRoomField;
        QPointer<QLineEdit> cPeriodField;
        QPointer<QLineEdit> homeLocationField;
        QPointer<QComboBox> lockTypeSelect;
        QPointer<QComboBox> osSelect;
        QPointer<QLineEdit> commentsField;

        QPointer<QPushButton> cancelButton;
        QPointer<QPushButton> editButton;
};
#endif //EDITCART_H
