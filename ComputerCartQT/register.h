#ifndef REGISTER_H
#define REGISTER_H

#include <QApplication>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialog>

class Register : public QDialog {
    Q_OBJECT
    public:
        explicit Register(QWidget *parent = 0);

    signals:
    public slots:
    private slots:
        void quit();
    private:
        QVBoxLayout *mainLayout;
        QVBoxLayout *fieldLayout;
        QHBoxLayout *buttonLayout;
        QPushButton *registerButton;
        QPushButton *cancelButton;
        QLineEdit *userField;
        QLineEdit *passField;
        QLineEdit *passVerField; 
};

#endif //REGISTER_H
