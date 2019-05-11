#pragma once
#include "AddCart.h"
#include "EditCart.h"
#include "DeleteCart.h"
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
#include <QComboBox>

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
        void addAction();
        void editAction();
        void removeAction();
    private slots:
        void update();
        void changeTheme(const QString& styleName);
    private:
        Session& mySession;
        CartModel& cartModel;
        CartView *cView;
        AddCart *newCart;
        EditCart *editCart;
        DeleteCart *deleteCart;
        QWidget *centralWidget;
        QVBoxLayout *mainLayout;
        QToolBar *toolbar;
        QToolButton *addTool;
        QToolButton *removeTool;
        QToolButton *logoutTool;
        QToolButton *editTool;
        QToolButton *addResTool;
        QToolButton *editResTool;
        QToolButton *detailsTool;
        QComboBox *themePicker;
};
