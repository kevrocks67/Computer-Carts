#ifndef ADDCARTS_H
#define ADDCARTS_H

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

class AddCart : public QDialog {
    Q_OBJECT

    public:
        explicit AddCart(QWidget * parent=0);
        virtual ~AddCart();
    public slots:
        //void GetOptions(int Opt1);
    private slots:
        void addCartAction();
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
        QPushButton *addButton;
};
#endif //ADDCARTS_H
