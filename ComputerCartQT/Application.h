#pragma once

#include <QApplication>
#include "MainWindow.h"
#include "Session.h"
#include "CartModel.h"

class MainWindow;
class Session;
class CartModel;

class Application : public QApplication {
    Q_OBJECT

    public:
        Application(int& argc, char** argv);
        virtual ~Application();
    signals:
    public slots:
    private slots:
    private:
        MainWindow *mainWindow;
        Session *mySession;
        CartModel *cModel;
};
