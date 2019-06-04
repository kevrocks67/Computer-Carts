#pragma once

#include "AddCart.h"
#include "CartModel.h"
#include "CartView.h"
#include "EditCart.h"
#include "DeleteCart.h"
#include "DetailView.h"

#include <QComboBox>
#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QSettings>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

class CartModel;
class CartView;

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(CartModel&);
        virtual ~MainWindow();
    signals:
    public slots:
        void addAction();
        void editAction();
        void removeAction();
    private slots:
        void updateTable();
        void changeTheme(int styleName);
        void showDetails(const QModelIndex &index);
        void loadSettings();
        void saveSettings();
    private:
        //Class declarations
        CartModel& cartModel;
        CartView *cView;
        AddCart *newCart;
        EditCart *editCart;
        DeleteCart *deleteCart;
        DetailView *detailView;

        //Widget declarations
        QWidget *centralWidget;
        QVBoxLayout *mainLayout;
        QToolBar *toolbar;
        QToolButton *addTool;
        QToolButton *removeTool;
        QToolButton *logoutTool;
        QToolButton *settingsTool;

        QToolButton *editTool;
        QToolButton *addResTool;
        QToolButton *editResTool;
        QToolButton *detailsTool;
        QComboBox *themePicker;
};
