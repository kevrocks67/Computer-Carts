#include "DeleteCart.h"

DeleteCart::DeleteCart(QWidget * parent) :
    QDialog(parent) {
    //Initialize layouts
    mainLayout = new QVBoxLayout(this);
    buttonLayout = new QHBoxLayout();

    //Initialize widgets
    cancelButton = new QPushButton("Cancel");
    delButton = new QPushButton("Delete Cart");
    deleteMessage = new QLabel("Are you sure you want to delete cart no: ");
    //rowNum = new QLabel(row);
    rowNum = new QLabel("NULL");

    //Set widget properties
    QFont sansFont("Helvetica [Cronyx]", 14);

    cancelButton->setFont(sansFont);
    delButton->setFont(sansFont);

    //Add widget to layouts
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(delButton);

    mainLayout->addWidget(deleteMessage);
    mainLayout->addWidget(rowNum);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setModal(true);

    //Signals and slots
    /*connect(addButton, SIGNAL(clicked()),
            CartModel, SLOT(add()));*/
    connect(cancelButton, SIGNAL(clicked()),
            SLOT(close()));
    connect(delButton, SIGNAL(clicked()),
            SLOT(delCartAction()));
}

void DeleteCart::delCartAction() {
    qDebug()<<"DeleteCart::delCartAction";
    cartModel->deleteCart(row);
    QDialog::done(QDialog::Accepted);

}

void DeleteCart::setRowNum(QString r) {
    rowNum->setText(r);
    row = r.toInt();
}

DeleteCart::~DeleteCart(){
}
