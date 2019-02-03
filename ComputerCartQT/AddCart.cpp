#include "AddCart.h"

AddCart::AddCart(QWidget * parent) :
    QDialog(parent) {
    //Initialize layouts
    mainLayout = new QVBoxLayout(this);
    fieldLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    //Initialize widgets
    cNumLabel = new QLabel("Cart Number: 1");
    typeField = new QLineEdit();
    quantField = new QLineEdit();
    cRoomField = new QLineEdit();
    cPeriodField = new QLineEdit();

    cancelButton = new QPushButton("Cancel");
    addButton = new QPushButton("Add Cart");

    //Set widget properties
    QFont sansFont("Helvetica [Cronyx]", 14);

    cNumLabel->setFont(sansFont);
    typeField->setPlaceholderText("Computer Type");
    typeField->setFont(sansFont);
    quantField->setPlaceholderText("Quantity");
    quantField->setFont(sansFont);
    cRoomField->setPlaceholderText("Current Room");
    cRoomField->setFont(sansFont);
    cPeriodField->setPlaceholderText("Current Period(s)");
    cPeriodField->setFont(sansFont);
    cancelButton->setFont(sansFont);
    addButton->setFont(sansFont);

    //Add widget to layouts
    fieldLayout->addWidget(cNumLabel);
    fieldLayout->addWidget(typeField);
    fieldLayout->addWidget(quantField);
    fieldLayout->addWidget(cRoomField);
    fieldLayout->addWidget(cPeriodField);

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(addButton);

    mainLayout->addLayout(fieldLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setModal(true);

    //Signals and slots
    /*connect(addButton, SIGNAL(clicked()),
            CartModel, SLOT(add()));*/
    connect(cancelButton, SIGNAL(clicked()),
            SLOT(close()));
    connect(addButton, SIGNAL(clicked()),
            SLOT(addCartAction()));
}

void AddCart::addCartAction() {
    qDebug()<<"AddCart::addCartAction";
    QDialog::done(QDialog::Accepted);

//    cartDetails.cartNo = cNumLabel->text().toInt();
    cartDetails.compType = typeField->text();
    cartDetails.quantity = quantField->text().toInt();
    cartDetails.cRoom = cRoomField->text();
    cartDetails.cPeriod = cPeriodField->text().toInt();

    cartModel->addCart(cartDetails);
}

/*
void AddCart::GetOptions(int Opt1) {
    Opt1 = 1337;
}*/

AddCart::~AddCart(){
}
