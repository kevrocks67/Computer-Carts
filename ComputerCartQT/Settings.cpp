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

    themePicker = new QComboBox();
    themePicker->addItem("Carbon");
    themePicker->addItem("Polar");
    themePicker->addItem("Stealth");
    themePicker->addItem("Sakura");

    //Set widget properties

    //Add widget to layouts
    mainLayout->addWidget(changeFontButton);
    mainLayout->addWidget(themePicker);
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
    connect(themePicker, SIGNAL(activated(int)),
            this, SIGNAL(themeChanged(int)));
}

void Settings::changeFontDialog() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this->font());
    QFont orig_font = this->font();
    if (ok) {
        emit fontChanged(font);
    } else {
        qDebug()<<"Font change cancelled";
    }
}

void Settings::setSettingsTheme(int theme) {
    themePicker->setCurrentIndex(theme);
}

QString Settings::getTheme() {
    return themePicker->currentText();
}

void Settings::save() {
    QDialog::done(QDialog::Accepted);
}

Settings::~Settings(){
}
