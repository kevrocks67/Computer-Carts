#include "EditLaptop.h"

EditLaptop::EditLaptop(LaptopModel &lapModel):
    model(&lapModel) {
        createWidgets();
        setWidgetProperties();

        fieldLayout->addWidget(assetField);
        fieldLayout->addWidget(brandLabel);
        fieldLayout->addWidget(brandField);
        fieldLayout->addWidget(genericNLabel);
        fieldLayout->addWidget(genericNField);
        fieldLayout->addWidget(modelField);
        fieldLayout->addWidget(serialField);
        fieldLayout->addWidget(osLabel);
        fieldLayout->addWidget(osSelect);
        fieldLayout->addWidget(cartNumSelectLabel);
        fieldLayout->addWidget(cartNumberSelect);
        fieldLayout->addWidget(statusGroup);
        fieldLayout->addWidget(isDeployedGroup);

        //ButtonLayout Widgets
        buttonLayout->addWidget(editButton);
        buttonLayout->addWidget(cancelButton);

        //MainLayout setup
        mainLayout->addLayout(fieldLayout);
        mainLayout->addLayout(buttonLayout);

        //Parent properties
        setLayout(mainLayout);
        setModal(true);
        setAttribute(Qt::WA_DeleteOnClose, true);

        //Signals and Slots
        connect(cancelButton, SIGNAL(clicked()),
                SLOT(close()));
        connect(editButton, SIGNAL(clicked()),
                SLOT(editLaptopAction()));
}


EditLaptop::EditLaptop(LaptopModel &lapModel, int cartNo):
    model(&lapModel), cartNum(cartNo) {
        createWidgets();
        setWidgetProperties();

        cartNumLabel->setText("Cart No: "+QString::number(cartNum));

        fieldLayout->addWidget(cartNumLabel);
        fieldLayout->addWidget(assetField);
        fieldLayout->addWidget(brandLabel);
        fieldLayout->addWidget(brandField);
        fieldLayout->addWidget(genericNLabel);
        fieldLayout->addWidget(genericNField);
        fieldLayout->addWidget(modelField);
        fieldLayout->addWidget(serialField);
        fieldLayout->addWidget(osLabel);
        fieldLayout->addWidget(osSelect);
        fieldLayout->addWidget(cartNumSelectLabel);
        fieldLayout->addWidget(cartNumberSelect);
        fieldLayout->addWidget(statusGroup);
        fieldLayout->addWidget(isDeployedGroup);

        //ButtonLayout Widgets
        buttonLayout->addWidget(editButton);
        buttonLayout->addWidget(cancelButton);

        //MainLayout setup
        mainLayout->addLayout(fieldLayout);
        mainLayout->addLayout(buttonLayout);

        //Parent properties
        setLayout(mainLayout);
        setModal(true);
        setAttribute(Qt::WA_DeleteOnClose, true);

        //Signals and Slots
        connect(cancelButton, SIGNAL(clicked()),
                SLOT(close()));
        connect(editButton, SIGNAL(clicked()),
                SLOT(editLaptopAction()));
}

void EditLaptop::createWidgets() {
        mainLayout = new QVBoxLayout();
        fieldLayout = new QVBoxLayout();
        buttonLayout = new QHBoxLayout();
        statusLayout = new QHBoxLayout();
        deployedLayout = new QHBoxLayout();

        cartNumLabel = new QLabel();
        assetField = new QLineEdit();
        brandLabel = new QLabel("Brand");
        brandField = new QComboBox();
        genericNLabel = new QLabel("Generic Name");
        genericNField = new QComboBox();
        modelField = new QLineEdit();
        serialField = new QLineEdit();
        osLabel = new QLabel("OS");
        osSelect = new QComboBox();
        cartNumSelectLabel = new QLabel("Cart Number");
        cartNumberSelect = new QComboBox();

        statusGroup = new QGroupBox(tr("Status"));
        workingStatusButton = new QRadioButton(tr("Working"));
        brokenStatusButton = new QRadioButton(tr("Broken"));

        isDeployedGroup = new QGroupBox(tr("Is Deployed"));
        deployedButton = new QRadioButton(tr("True"));
        notDeployedButton = new QRadioButton(tr("False"));

        editButton = new QPushButton("Edit");
        cancelButton = new QPushButton("Cancel");
}

void EditLaptop::setWidgetProperties() {
    assetField->setPlaceholderText("Asset Tag");
    modelField->setPlaceholderText("Model (Optional)");
    serialField->setPlaceholderText("Serial Number (Optional)");

    brandField->setEditable(true);
    genericNField->setEditable(true);

    workingStatusButton->setChecked(true);
    deployedButton->setChecked(true);

    QStringList brands = model->getBrands();
    QStringList gNames = model->getGNames();
    QStringList carts = model->getCarts();

    for(QString brand: brands) {
        brandField->addItem(brand);
    }
    for(QString gName: gNames) {
        genericNField->addItem(gName);
    }
    for(QString cart: carts) {
        cartNumberSelect->addItem(cart);
    }

    osSelect->addItem("Win7");
    osSelect->addItem("Win10");
    osSelect->addItem("Chrome OS");
    osSelect->addItem("Linux");
    osSelect->addItem("Mac OSX");

    statusLayout->addWidget(workingStatusButton);
    statusLayout->addWidget(brokenStatusButton);
    statusGroup->setLayout(statusLayout);

    deployedLayout->addWidget(deployedButton);
    deployedLayout->addWidget(notDeployedButton);
    isDeployedGroup->setLayout(deployedLayout);
}

void EditLaptop::editLaptopAction() {
    qDebug()<<"EditLaptop::editLaptopAction";
    laptop.AssetID = assetField->text();
    laptop.Brand = brandField->currentText();
    laptop.GenericName = genericNField->currentText();
    laptop.Model = modelField->text();
    laptop.Serial = serialField->text();
    laptop.OS = osSelect->currentText();
    laptop.CartNumber = cartNumberSelect->currentText().toInt();
    if (workingStatusButton->isChecked()) {
        laptop.Status = "Working";
    }
    else {
        laptop.Status = "Broken";
    }

    if (deployedButton->isChecked()) {
        laptop.IsDeployed = true;
    }
    else {
        laptop.IsDeployed = false;
    }

    model->editLaptop(laptop);
    QDialog::done(QDialog::Accepted);
}

void EditLaptop::setLapDetails(QString asset, QString gName) {
    assetField->setText(asset);
    genericNField->setCurrentText(gName);

    LaptopModel::Laptop laptopToEdit = model->getLaptop(asset, gName);

    brandField->setCurrentText(laptopToEdit.Brand);
    modelField->setText(laptopToEdit.Model);
    serialField->setText(laptopToEdit.Serial);
    osSelect->setCurrentText(laptopToEdit.OS);
    cartNumberSelect->setCurrentText(QString::number(laptopToEdit.CartNumber));

    if (laptopToEdit.Status == "Working") {
        workingStatusButton->setChecked(true);
    } else {
        brokenStatusButton->setChecked(true);
    }

    if (laptopToEdit.IsDeployed) {
        deployedButton->setChecked(true);
    } else {
        notDeployedButton->setChecked(true);
    }
}

EditLaptop::~EditLaptop() {
}

