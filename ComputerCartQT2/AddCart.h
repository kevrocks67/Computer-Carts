#ifndef ADDCARTS_H
#define ADDCARTS_H

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialog>

class AddCart : public QDialog {
    Q_OBJECT
    
    public:
        explicit AddCart(QWidget * parent = 0);
        virtual ~AddCart();
    public slots:
    private slots:
        void addCart();
    private:
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
        //insert table here
};
#endif //ADDCARTS_H
