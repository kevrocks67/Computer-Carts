#include "DeleteCart.h"

DeleteCart::DeleteCart(QWidget * parent) :
    QDialog(parent) {
    //Initialize layouts
    mainLayout = new QVBoxLayout(this);
    textLayout = new QHBoxLayout();
    buttonLayout = new QHBoxLayout();

    //Initialize widgets
    cancelButton = new QPushButton("Cancel", this);
    delButton = new QPushButton("Delete Cart", this);
    deleteMessage = new QLabel("Are you sure you want to delete cart no: ", this);
    cartNum = new QLabel("NULL", this);

    //Add widget to layouts
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(delButton);


    textLayout->addWidget(deleteMessage);
    textLayout->addWidget(cartNum);
    //mainLayout->addWidget(deleteMessage);
    //mainLayout->addWidget(rowNum);
    mainLayout->addLayout(textLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setModal(true);

    //Signals and slots
    connect(cancelButton, SIGNAL(clicked()),
            SLOT(close()));
    connect(delButton, SIGNAL(clicked()),
            SLOT(delCartAction()));
}

void DeleteCart::delCartAction() {
    qDebug()<<"DeleteCart::delCartAction";
    cartModel->deleteCart(cartNo);
    QDialog::done(QDialog::Accepted);

}

void DeleteCart::setCartNum(int c) {
    //Set modal text
    cartNum->setText(QString::number(c));
    //Set variable for action
    cartNo = c;
}

DeleteCart::~DeleteCart(){
}
