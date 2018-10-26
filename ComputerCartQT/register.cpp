#include "register.h"

Register::Register(QWidget * parent):
    QDialog(parent) {
        //Initialize layouts
        mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(4);

        fieldLayout = new QVBoxLayout();
        fieldLayout->setSpacing(4);

        buttonLayout = new QHBoxLayout();
       
        //Initialize widgets
        registerButton = new QPushButton("Register");
        cancelButton = new QPushButton("Cancel");
        userField = new QLineEdit();
        passField = new QLineEdit();
        passVerField = new QLineEdit();

        //Widget properties
        QFont sansFont("Helvetica [Cronyx]", 14);
        
        registerButton->setFont(sansFont);
        cancelButton->setFont(sansFont);

        userField->setPlaceholderText("Username");
        userField->setMaxLength(32);
        userField->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        userField->setMaximumHeight(30);
        userField->setFont(sansFont);

        passField->setPlaceholderText("Password");
        passField->setMaxLength(32);
        passField->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        passField->setMaximumHeight(30);
        passField->setFont(sansFont);

        passVerField->setPlaceholderText("Verify Password");
        passVerField->setMaxLength(32);
        passVerField->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        passVerField->setMaximumHeight(30);
        passVerField->setFont(sansFont);

        //Add widgets to layouts
        fieldLayout->addWidget(userField);
        fieldLayout->addWidget(passField);
        fieldLayout->addWidget(passVerField);
        buttonLayout->addWidget(registerButton);
        buttonLayout->addWidget(cancelButton); 
        
        mainLayout->addLayout(fieldLayout);
        mainLayout->addLayout(buttonLayout);
        setLayout(mainLayout);

        //Signals and slots
        connect(cancelButton, SIGNAL(clicked()),
                SLOT(quit()));
    }

void Register::quit(){
    this->close();
}
