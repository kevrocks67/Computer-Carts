#ifndef LOGIN_H
#define LOGIN_H

#include "carts.h"
#include "register.h"
#include <iostream>
#include <QApplication>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSize>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QStackedWidget>

class Login : public QWidget {
    Q_OBJECT
    public:
        explicit Login(QWidget *parent = 0);

    signals:
    public slots:
    private slots:
        void authenticate();
        void registerNew();
    private:
        QPushButton *loginButton;
        QPushButton *registerButton;
        QLineEdit *userField;
        QLineEdit *passwordField;
        QVBoxLayout *mainLayout;
        QVBoxLayout *fieldLayout;
        QHBoxLayout *buttonLayout;
        QSize *fieldsize;
        QStackedWidget *stack;
        Carts *cartView;
        Register *registerView;
};

#endif //WINDOW_H
