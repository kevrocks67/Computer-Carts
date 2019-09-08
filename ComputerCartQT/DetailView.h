#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include "CartModel.h"
#include "Laptops.h"
#include "LaptopView.h"
#include "LaptopModel.h"

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QPointer>
#include <QPushButton>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QToolBar>
#include <QToolButton>

class CartModel;

class DetailView : public QDialog {
    Q_OBJECT

    public:
        explicit DetailView(QWidget * parent=nullptr);
        virtual ~DetailView();
    public slots:
        void getDetails(int cartNo);
    private slots:
    private:
        QPointer<CartModel> cartModel;
        QPointer<LaptopView> laptopView;
        QPointer<LaptopModel> laptopModel;

        //Main Widgets
         //QWidget *laptopWidget;
        QPointer<QVBoxLayout> mainLayout;
        QPointer<QTabWidget> tabWidget;
        QPointer<QWidget> cartWidget;
        QPointer<QWidget> resWidget;

        QPointer<QVBoxLayout> cartLayout;
        QPointer<QVBoxLayout> resLayout;
        QPointer<QPushButton> closeButton;
        QPointer<Laptops> laptops;

        //Cart Tab Widgets
        QPointer<QLabel> cartNumLabel;
        QPointer<QLabel> compTypeLabel;
        QPointer<QLabel> quantLabel;
        QPointer<QLabel> cRoomLabel;
        QPointer<QLabel> cPeriodLabel;
        QPointer<QLabel> osLabel;
        QPointer<QLabel> homeLabel;
        QPointer<QLabel> lockTypeLabel;
        QPointer<QLabel> commentLabel;
        QPointer<QTextEdit> commentBox;
        QPointer<QPushButton> laptopsButton;
};
#endif //DETAILVIEW_H
