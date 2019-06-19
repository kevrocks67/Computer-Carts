#include "DeleteLaptop.h"

DeleteLaptop::DeleteLaptop(LaptopModel &lapModel) :
    model(lapModel) {

    //Initialize layouts
    mainLayout = new QVBoxLayout(this);
    textLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    //Initialize widgets
    cancelButton = new QPushButton("Cancel");
    delButton = new QPushButton("Delete Laptop");
    deleteMessage = new QLabel("Are you sure you want to delete this laptop?");
    detailsLabel = new QLabel();

    //ButtonLayout Widgets
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(delButton);

    //TextLayout Widgets
    textLayout->addWidget(deleteMessage);
    textLayout->addWidget(detailsLabel);

    //MainLayout setup
    mainLayout->addLayout(textLayout);
    mainLayout->addLayout(buttonLayout);

    //Parent properties
    setLayout(mainLayout);
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose, true);

    //Signals and slots
    connect(cancelButton, SIGNAL(clicked()),
            SLOT(close()));
    connect(delButton, SIGNAL(clicked()),
            SLOT(delLaptopAction()));
}

void DeleteLaptop::delLaptopAction() {
    qDebug()<<"DeleteLaptop::delLaptopAction";
    model.deleteLaptop(asset, gName);
    QDialog::done(QDialog::Accepted);
}

void DeleteLaptop::setLapDetails(QString asset, QString gName) {
    this->asset = asset;
    this->gName = gName;
    detailsLabel->setText("Asset: "+asset+"\tName: "+gName);
}

DeleteLaptop::~DeleteLaptop(){
}
