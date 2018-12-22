#pragma once
#include "AddCart.h"
#include "Session.h"
#include "CartModel.h"
#include "CartView.h"

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolBar>
#include <QToolButton>
#include <QDebug>

class Session;
class CartModel;
class CartView;

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(Session&, CartModel&);
        virtual ~MainWindow();
    signals:
    public slots:
        //void GetDialogOutput();
    private slots:
    private:
        Session& mySession;
        CartModel& cartModel;
        CartView *cView;
        AddCart *newCart;
        QWidget *centralWidget;
        QVBoxLayout *mainLayout;
        QToolBar *toolbar;
        QToolButton *addTool;
        QToolButton *removeTool;
        QToolButton *logoutTool;
        QToolButton *editTool;
};
