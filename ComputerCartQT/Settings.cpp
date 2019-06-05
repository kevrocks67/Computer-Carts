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
    changeFontButton = new QPushButton("Change Font");

    //Set widget properties

    //Add widget to layouts
    mainLayout->addWidget(changeFontButton);
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
    connect(changeFontButton, SIGNAL(clicked()),
            SLOT(changeFontDialog()));
}

void Settings::changeFontDialog() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this->font());
    if (ok) {
        emit fontChanged(font);
    } else {
        qDebug()<<"Font change cancelled";
    }
}

void Settings::save() {
    QDialog::done(QDialog::Accepted);
}

Settings::~Settings(){
}
