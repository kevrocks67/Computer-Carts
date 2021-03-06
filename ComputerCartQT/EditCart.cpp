#include "EditCart.h"

EditCart::EditCart(QWidget * parent) :
    QDialog(parent) {
    //Initialize layouts
    mainLayout = new QVBoxLayout(this);
    fieldLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    //Initialize widgets
    cNumLabel = new QLabel(this);
    typeField = new QLineEdit(this);
    cRoomField = new QLineEdit(this);
    cPeriodField = new QLineEdit(this);
    homeLocationField = new QLineEdit(this);
    lockTypeSelect = new QComboBox(this);
    osSelect = new QComboBox(this);
    commentsField = new QTextEdit(this);

    cancelButton = new QPushButton("Cancel", this);
    editButton = new QPushButton("Edit Cart", this);

    //Set widget properties

    typeField->setPlaceholderText("Computer Type");
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
    cartDetails.cRoom = cRoomField->text();
    cartDetails.cPeriod = cPeriodField->text();
    cartDetails.homeLoc = homeLocationField->text();
    cartDetails.lockType = lockTypeSelect->currentText();
    cartDetails.os = osSelect->currentText();
    cartDetails.comments = commentsField->toPlainText();

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

     cartDetails.quantity = cartToEdit.quantity;
     typeField->setText(cartToEdit.compType);
     cRoomField->setText(cartToEdit.cRoom);
     cPeriodField->setText(cartToEdit.cPeriod);
     homeLocationField->setText(cartToEdit.homeLoc);
     lockTypeSelect->setCurrentText(cartToEdit.lockType);
     osSelect->setCurrentText(cartToEdit.os);
     commentsField->setText(cartToEdit.comments);
}

EditCart::~EditCart(){
}
