#include <QApplication>
#include "login.h"
#include <iostream>

int main(int argc, char ** argv){
    QApplication app (argc, argv);
    
    Login login;
    
    login.show();
    std::cout<<"test"<<std::endl;
    return app.exec();
}
