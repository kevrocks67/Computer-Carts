#pragma once

#include "AddCart.h"
#include "CartModel.h"
#include "CartView.h"
#include "EditCart.h"
#include "DeleteCart.h"
#include "DetailView.h"
#include "Laptops.h"
#include "LaptopModel.h"
#include "LaptopView.h"
#include "Settings.h"

#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QSettings>
#include <QTabWidget>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

class CartModel;
class CartView;
class LaptopModel;
class LaptopView;

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(CartModel&, LaptopModel&);
        virtual ~MainWindow();
    signals:
    public slots:
        void addAction();
        void editAction();
        void removeAction();
    private slots:
        void createToolbar();
        void updateTable();
        void changeTheme(int styleName);
        void showDetails(const QModelIndex &index);
        void changeFont(const QFont &font);
        void loadSettings();
        void saveSettings();
    private:
        //Class declarations
        CartModel& cartModel;
        CartView *cView;
        LaptopView *lView;
        AddCart *newCart;
        EditCart *editCart;
        DeleteCart *deleteCart;
        DetailView *detailView;
        Settings *settingsView;

        //Widget declarations
        QWidget *centralWidget;
        Laptops *laptopWidget;
        QVBoxLayout *mainLayout;
        QTabWidget *tabs;
        QToolBar *toolbar;
        QToolButton *addTool;
        QToolButton *editTool;
        QToolButton *removeTool;
        QToolButton *logoutTool;
        QToolButton *settingsTool;

        QToolButton *addResTool;
        QToolButton *editResTool;
};
