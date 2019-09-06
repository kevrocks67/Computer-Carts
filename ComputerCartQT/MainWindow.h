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

#include <QComboBox>
#include <QDebug>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QPointer>
#include <QPushButton>
#include <QSettings>
#include <QSortFilterProxyModel>
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
        void search(const QString &query);
        void changeFont(const QFont &font);
        void loadSettings();
        void saveSettings();
    private:
        //Class declarations
        CartModel& cartModel;

        QPointer<CartView> cView;
        QPointer<LaptopView> lView;
        QPointer<AddCart> newCart;
        QPointer<EditCart> editCart;
        QPointer<DeleteCart> deleteCart;
        QPointer<DetailView> detailView;
        QPointer<Settings> settingsView;

        //Widget declarations
        QPointer<QWidget> cartWidget;
        QPointer<Laptops> laptopWidget;
        QPointer<QVBoxLayout> mainLayout;
        QPointer<QTabWidget> tabs;
        QPointer<QToolBar> toolbar;

        QPointer<QToolButton> refreshTool;

        QPointer<QToolButton> addTool;
        QPointer<QToolButton> editTool;
        QPointer<QToolButton> removeTool;
        QPointer<QToolButton> logoutTool;
        QPointer<QToolButton> settingsTool;

        QPointer<QToolButton> addResTool;
        QPointer<QToolButton> editResTool;

        QPointer<QLineEdit> searchBar;
        QPointer<QSortFilterProxyModel> proxy;
        QPointer<QComboBox> columnSelect;
};
