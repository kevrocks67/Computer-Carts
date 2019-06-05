#include "Settings.h"

Settings::Settings(QWidget * parent) :
    QDialog(parent) {
    //Initialize layouts
    mainLayout = new QVBoxLayout(this);
    //fieldLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    //Initialize widgets
    cancelButton = new QPushButton("Cancel");
    saveButton = new QPushButton("Save Settings");

    //Set widget properties

    //Add widget to layouts
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(saveButton);

    //mainLayout->addLayout(fieldLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setModal(true);

    //Signals and slots
    connect(cancelButton, SIGNAL(clicked()),
            SLOT(close()));
    connect(saveButton, SIGNAL(clicked()),
            SLOT(save()));
}

void Settings::save() {
    QDialog::done(QDialog::Accepted);
}

Settings::~Settings(){
}
