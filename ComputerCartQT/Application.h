#pragma once

#include <QApplication>
#include "MainWindow.h"
#include "CartModel.h"

class MainWindow;
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
        CartModel *cModel;
};
