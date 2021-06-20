#include "AddCart.h"

AddCart::AddCart(QWidget * parent) :
    QDialog(parent) {
    //Initialize layouts
    mainLayout = new QVBoxLayout(this);
    fieldLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    //Initialize widgets
    cNumLabel = new QLabel("Cart Number: 1", this);
    typeField = new QLineEdit(this);
    quantField = new QLineEdit(this);
    cRoomField = new QLineEdit(this);
    cPeriodField = new QLineEdit(this);
    homeLocationField = new QLineEdit(this);
    lockTypeSelect = new QComboBox(this);
    osSelect = new QComboBox(this);
    commentsField = new QLineEdit(this);

    cancelButton = new QPushButton("Cancel", this);
    addButton = new QPushButton("Add Cart", this);

    //Set widget properties
    typeField->setPlaceholderText("Computer Type");
    quantField->setPlaceholderText("Quantity");
    cRoomField->setPlaceholderText("Current Room");
    cPeriodField->setPlaceholderText("Current Period(s)");
    homeLocationField->setPlaceholderText("Home Location");
    commentsField->setPlaceholderText("Comments");
    lockTypeSelect->addItem("Key");
    lockTypeSelect->addItem("Circular Key");
    lockTypeSelect->addItem("Combination");
    osSelect->addItem("Windows");
    osSelect->addItem("Chrome OS");
    osSelect->addItem("Linux");
    osSelect->addItem("Mac OSX");

    //Add widget to layouts
    fieldLayout->addWidget(cNumLabel);
    fieldLayout->addWidget(typeField);
    fieldLayout->addWidget(quantField);
    fieldLayout->addWidget(cRoomField);
    fieldLayout->addWidget(cPeriodField);
    fieldLayout->addWidget(homeLocationField);
    fieldLayout->addWidget(lockTypeSelect);
    fieldLayout->addWidget(osSelect);
    fieldLayout->addWidget(commentsField);

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(addButton);

    mainLayout->addLayout(fieldLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setModal(true);

    //Signals and slots
    connect(cancelButton, SIGNAL(clicked()),
            SLOT(close()));
    connect(addButton, SIGNAL(clicked()),
            SLOT(addCartAction()));
}

void AddCart::addCartAction() {
    qDebug()<<"AddCart::addCartAction";

    CartModel::Cart cart;
    cart.cartNo = cNumLabel->text().toInt();
    cart.compType = typeField->text();
    cart.quantity = quantField->text().toInt();
    cart.cRoom = cRoomField->text();
    cart.cPeriod = cPeriodField->text();
    cart.homeLoc = homeLocationField->text();
    cart.lockType = lockTypeSelect->currentText();
    cart.os = osSelect->currentText();
    cart.comments = commentsField->text();

    cartModel->addCart(cart);
    QDialog::done(QDialog::Accepted);
}

void AddCart::setCartNum(int c) {
    //Set modal text
    cNumLabel->setText(QString::number(c));
    typeField->clear();
    quantField->clear();
    cRoomField->clear();
    cPeriodField->clear();
    homeLocationField->clear();
    lockTypeSelect->setCurrentIndex(0);
    osSelect->setCurrentIndex(0);
    commentsField->clear();
}

AddCart::~AddCart(){
}
