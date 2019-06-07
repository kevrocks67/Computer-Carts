#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include "CartModel.h"
#include "Laptops.h"
#include "LaptopView.h"
#include "LaptopModel.h"

#include <QApplication>
#include <QDialog>
#include <QLabel>
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
        explicit DetailView(QWidget * parent=0);
        virtual ~DetailView();
    public slots:
        void getDetails(int cartNo);
    private slots:
    private:
        CartModel *cartModel;
        LaptopView *laptopView;
        LaptopModel *laptopModel;

        //Main Widgets
        QVBoxLayout *mainLayout;
        QTabWidget *tabWidget;
        QWidget *cartWidget;
        QWidget *resWidget;
        //QWidget *laptopWidget;
        QVBoxLayout *cartLayout;
        QVBoxLayout *resLayout;
        QPushButton *closeButton;
        Laptops *laptops;

        //Cart Tab Widgets
        QLabel *cartNumLabel;
        QLabel *compTypeLabel;
        QLabel *quantLabel;
        QLabel *cRoomLabel;
        QLabel *cPeriodLabel;
        QLabel *homeLabel;
        QLabel *lockTypeLabel;
        QTextEdit *commentBox;
        QPushButton *laptopsButton;

        //Laptop Widget widgets
        /*QVBoxLayout *lapMainLayout;
        QLabel *cartNum;
        QToolBar *laptopToolbar;
        QToolButton *addLapTool;
        QToolButton *editLapTool;
        QToolButton *removeLapTool;*/
};
#endif //DETAILVIEW_H
