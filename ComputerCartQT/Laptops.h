#ifndef LAPTOPS_H
#define LAPTOPS_H

#include "LaptopModel.h"
#include "LaptopView.h"
#include "AddLaptop.h"
#include "DeleteLaptop.h"

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>

class Laptops : public QWidget {
    Q_OBJECT

    public:
        explicit Laptops(LaptopModel &laptopModel, LaptopView &laptopView);
        virtual ~Laptops();
    public slots:
        void setCartNum(int cartno);
        void setCartNum(QString label);
    private slots:
        void updateTable();
        void updateTableCart();
        void addAction();
        void addActionCart();
        void deleteAction();
        void deleteActionCart();
    private:
        LaptopModel& model;
        LaptopView& view;
        int cartNo;

        AddLaptop *addLaptop;
        DeleteLaptop *deleteLaptop;

        QVBoxLayout *mainLayout;
        QLabel *cartNum;
        QToolBar *toolbar;
        QToolButton *addTool;
        QToolButton *editTool;
        QToolButton *removeTool;
};
#endif //LAPTOPS_H
