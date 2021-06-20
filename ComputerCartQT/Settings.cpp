#include "Settings.h"

Settings::Settings(QWidget * parent) :
    QDialog(parent) {
    QSettings settings("config.ini", QSettings::IniFormat);
    //Initialize layouts
    mainLayout = new QVBoxLayout(this);
    //fieldLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    //Initialize widgets
    cancelButton = new QPushButton("Cancel", this);
    saveButton = new QPushButton("Save Settings", this);
    changeFontButton = new QPushButton("Change Font", this);
    themePicker = new QComboBox(this);
    driverPicker = new QComboBox(this);
    hostLabel = new QLabel("Hostname/IP Address", this);
    hostField = new QLineEdit(this);
    userLabel = new QLabel("Username", this);
    userField = new QLineEdit(this);
    passLabel = new QLabel("Password", this);
    passField = new QLineEdit(this);
    showPassCheck = new QCheckBox("Show Password", this);

    //Set widget properties
    themePicker->addItem("Carbon");
    themePicker->addItem("Polar");
    themePicker->addItem("Stealth");
    themePicker->addItem("Sakura");

    driverPicker->addItem("SQLite");
    driverPicker->addItem("MySQL");

    passField->setEchoMode(QLineEdit::Password);

    if(settings.value("db/db_type").toString() == "QMYSQL") {
        driverPicker->setCurrentText("MySQL");
        hostField->setText(settings.value("db/db_host").toString());
        userField->setText(settings.value("db/db_user").toString());
        passField->setText(settings.value("db/db_pass").toString());
    } else {
        driverPicker->setCurrentText("SQLite");
    }

    //Add widget to layouts
    mainLayout->addWidget(changeFontButton);
    mainLayout->addWidget(themePicker);
    mainLayout->addWidget(driverPicker);
    mainLayout->addWidget(hostLabel);
    mainLayout->addWidget(hostField);
    mainLayout->addWidget(userLabel);
    mainLayout->addWidget(userField);
    mainLayout->addWidget(passLabel);
    mainLayout->addWidget(passField);
    mainLayout->addWidget(showPassCheck);

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(saveButton);

    //mainLayout->addLayout(fieldLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setModal(true);

    checkDriver(driverPicker->currentIndex());

    //Signals and slots
    connect(cancelButton, SIGNAL(clicked()),
            SLOT(close()));
    connect(saveButton, SIGNAL(clicked()),
            SLOT(save()));
    connect(changeFontButton, SIGNAL(clicked()),
            SLOT(changeFontDialog()));
    connect(themePicker, SIGNAL(activated(int)),
            this, SIGNAL(themeChanged(int)));
    connect(driverPicker, SIGNAL(activated(int)),
            this, SLOT(checkDriver(int)));
    connect(showPassCheck, SIGNAL(stateChanged(int)),
            this, SLOT(showPassAction(int)));
}

void Settings::checkDriver(int choice) {
    if(choice == 0) {
        hostLabel->setEnabled(false);
        hostField->setEnabled(false);
        userLabel->setEnabled(false);
        userField->setEnabled(false);
        passLabel->setEnabled(false);
        passField->setEnabled(false);
        showPassCheck->setEnabled(false);
    } else {
        hostLabel->setEnabled(true);
        hostField->setEnabled(true);
        userField->setEnabled(true);
        userLabel->setEnabled(true);
        passField->setEnabled(true);
        passLabel->setEnabled(true);
        showPassCheck->setEnabled(true);
    }
}

void Settings::changeFontDialog() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this->font());
    //QFont orig_font = this->font();
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

/* Check if the Show Password checkbox is checked and toggle
 * between password and cleartext modes
*/
void Settings::showPassAction(int checked) {
    if (checked) {
        passField->setEchoMode(QLineEdit::Normal);
    } else {
        passField->setEchoMode(QLineEdit::Password);
    }
}

void Settings::save() {
    QSettings settings("config.ini", QSettings::IniFormat);
    QString driver = driverPicker->currentText();

    if(driver == "SQLite")
        settings.setValue("db/db_type", "QSQLITE");
    else
        settings.setValue("db/db_type", "QMYSQL");

    settings.setValue("db/db_host", hostField->text());
    settings.setValue("db/db_user", userField->text());
    settings.setValue("db/db_pass", passField->text());

    QDialog::done(QDialog::Accepted);
}

Settings::~Settings(){
    if(mainLayout != nullptr)
        delete mainLayout;
}
