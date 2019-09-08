#ifndef ADDCART_H
#define ADDCART_H

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

class AddCart : public QDialog {
    Q_OBJECT

    public:
        explicit AddCart(QWidget * parent=nullptr);
        virtual ~AddCart();
    public slots:
        void setCartNum(int c);
    private slots:
        void addCartAction();
    private:
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
        QPointer<QPushButton> addButton;
};
#endif //ADDCART_H
