#include "login.h"

Login::Login(QWidget * parent):
    QWidget(parent) {
        //Get app size
        QSize size = this->size();
        int h = size.height();
        int w = size.width();
        
        //Initialize layouts
        mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(4);
        mainLayout->setContentsMargins(w, h, w, h);

        fieldLayout = new QVBoxLayout();
        fieldLayout->setSpacing(4);
        
        buttonLayout = new QHBoxLayout();

        //Initialize widgets
        userField = new QLineEdit();
        passwordField = new QLineEdit();
        loginButton = new QPushButton("Login");
        registerButton = new QPushButton("Register");

        //Widget properties
        QFont sansFont("Helvetica [Cronyx]", 14);

        userField->setPlaceholderText("Username");
        userField->setMaxLength(32);
        userField->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        userField->setMaximumHeight(30);
        userField->setFont(sansFont);

        passwordField->setPlaceholderText("Password");
        passwordField->setEchoMode(QLineEdit::Password);
        passwordField->setMaxLength(32);
        passwordField->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        passwordField->setMaximumHeight(30);
        passwordField->setFont(sansFont);

        loginButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        loginButton->setMaximumHeight(35);
        loginButton->setMaximumWidth(50);
        loginButton->setFont(sansFont);
        
        registerButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        registerButton->setMaximumHeight(35);
        registerButton->setMaximumWidth(65);
        registerButton->setFont(sansFont);

        //Add widgets to layouts
        fieldLayout->addWidget(userField);
        fieldLayout->addWidget(passwordField);

        buttonLayout->addWidget(loginButton);  
        buttonLayout->addWidget(registerButton);

        mainLayout->addLayout(fieldLayout);
        mainLayout->addLayout(buttonLayout);
        setLayout(mainLayout);

        //Signals and slots
        connect(loginButton, SIGNAL(clicked()),
                SLOT(authenticate()));

        connect(registerButton, SIGNAL(clicked()),
                SLOT(registerNew()));

        /*connect(login, SIGNAL(destroyer()),
                mainView, SLOT(exec()));*/
    }

void Login::authenticate(){
    this->close();
}

void Login::registerNew(){

}

/*void Login::test(){
    QString user = userField->text();
    qDebug() << user;
}*/
