#ifndef LAPTOPS_H
#define LAPTOPS_H

#include "LaptopModel.h"
#include "LaptopView.h"
#include "AddLaptop.h"
#include "EditLaptop.h"
#include "DeleteLaptop.h"

#include <QApplication>
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPointer>
#include <QString>
#include <QStringList>
#include <QSortFilterProxyModel>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>


class Laptops : public QWidget {
    Q_OBJECT

    public:
        explicit Laptops(LaptopModel &laptopModel, LaptopView &laptopView, bool isCart);
        virtual ~Laptops();
    public slots:
        void setCartNum(int cartno);
        void setCartNum(QString label);
        void displayError(QString);
    private slots:
        void updateTable();
        void updateTableCart();
        void addAction();
        void addActionCart();
        void editAction();
        void editActionCart();
        void deleteAction();
        void deleteActionCart();
        void search(const QString &query);
        void setSearchColumn(int index);
    private:
        LaptopModel& model;
        LaptopView& view;
        int cartNo;

        QPointer<AddLaptop> addLaptop;
        QPointer<EditLaptop> editLaptop;
        QPointer<DeleteLaptop> deleteLaptop;

        QPointer<QVBoxLayout> mainLayout;
        QPointer<QLabel> cartNum;
        QPointer<QToolBar> toolbar;
        QPointer<QToolButton> refreshTool;
        QPointer<QToolButton> addTool;
        QPointer<QToolButton> editTool;
        QPointer<QToolButton> removeTool;
        QPointer<QLineEdit> searchBar;
        QPointer<QSortFilterProxyModel> proxy;
        QPointer<QComboBox> columnSelect;
};
#endif //LAPTOPS_H
