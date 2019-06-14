#include "EditCart.h"

EditCart::EditCart(QWidget * parent) :
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
    homeLocationField = new QLineEdit();
    lockTypeSelect = new QComboBox();
    osSelect = new QComboBox();
    commentsField = new QLineEdit();

    cancelButton = new QPushButton("Cancel");
    editButton = new QPushButton("Edit Cart");

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
    buttonLayout->addWidget(editButton);

    mainLayout->addLayout(fieldLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setModal(true);

    //Signals and slots
    /*connect(addButton, SIGNAL(clicked()),
            CartModel, SLOT(add()));*/
    connect(cancelButton, SIGNAL(clicked()),
            SLOT(close()));
    connect(editButton, SIGNAL(clicked()),
            SLOT(editCartAction()));
}

void EditCart::editCartAction() {
    qDebug()<<"EditCart::editCartAction";

    cartDetails.cartNo = cNumLabel->text().toInt();
    cartDetails.compType = typeField->text();
    cartDetails.quantity = quantField->text().toInt();
    cartDetails.cRoom = cRoomField->text();
    cartDetails.cPeriod = cPeriodField->text().toInt();
    cartDetails.homeLoc = homeLocationField->text();
    cartDetails.lockType = lockTypeSelect->currentText();
    cartDetails.os = osSelect->currentText();
    cartDetails.comments = commentsField->text();


    cartModel->editCart(cartDetails);
    QDialog::done(QDialog::Accepted);
}

void EditCart::setCartNum(int c) {
    //Set modal text
     cNumLabel->setText(QString::number(c));

	//Check if no cart is selected
     if (c == 0) {
        QDialog::done(QDialog::Rejected);
        close();
     }

     CartModel::Cart cartToEdit = cartModel->getCart(c);

     typeField->setText(cartToEdit.compType);
     quantField->setText(QString::number(cartToEdit.quantity));
     cRoomField->setText(cartToEdit.cRoom);
     cPeriodField->setText(QString::number(cartToEdit.cPeriod));
}

EditCart::~EditCart(){
}
