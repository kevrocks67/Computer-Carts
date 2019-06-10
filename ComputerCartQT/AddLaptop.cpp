#include "AddLaptop.h"

AddLaptop::AddLaptop(LaptopModel &lapModel):
    model(&lapModel) {
        mainLayout = new QVBoxLayout();
        fieldLayout = new QVBoxLayout();
        buttonLayout = new QHBoxLayout();
        statusLayout = new QHBoxLayout();
        deployedLayout = new QHBoxLayout();

        cartNumLabel = new QLabel();
        assetField = new QLineEdit();
        brandLabel = new QLabel();
        brandField = new QComboBox();
        genericNLabel = new QLabel();
        genericNField = new QComboBox();
        modelField = new QLineEdit();
        osSelect = new QComboBox();
        //Only if all laptops view
        cartNumberSelect = new QComboBox();

        statusGroup = new QGroupBox(tr("Status"));
        workingStatusButton = new QRadioButton(tr("Working"));
        brokenStatusButton = new QRadioButton(tr("Broken"));

        isDeployedGroup = new QGroupBox(tr("Is Deployed"));
        deployedButton = new QRadioButton(tr("True"));
        notDeployedButton = new QRadioButton(tr("False"));

        addButton = new QPushButton("Add");
        cancelButton = new QPushButton("Cancel");

        assetField->setPlaceholderText("Asset Tag");
        brandLabel->setText("Brand");
        genericNLabel->setText("Generic Name");
        modelField->setPlaceholderText("Model (Optional)");

        brandField->setEditable(true);
        genericNField->setEditable(true);
        setComboItems();

        statusLayout->addWidget(workingStatusButton);
        statusLayout->addWidget(brokenStatusButton);
        statusGroup->setLayout(statusLayout);

        deployedLayout->addWidget(deployedButton);
        deployedLayout->addWidget(notDeployedButton);
        isDeployedGroup->setLayout(deployedLayout);

        fieldLayout->addWidget(cartNumLabel);
        fieldLayout->addWidget(assetField);
        fieldLayout->addWidget(brandField);
        fieldLayout->addWidget(genericNField);
        fieldLayout->addWidget(modelField);
        fieldLayout->addWidget(osSelect);
        //fieldLayout->addWidget(cartNumberSelect);
        fieldLayout->addWidget(statusGroup);
        fieldLayout->addWidget(isDeployedGroup);

        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(cancelButton);

        mainLayout->addLayout(fieldLayout);
        mainLayout->addLayout(buttonLayout);
        setLayout(mainLayout);
        setModal(true);
}

void AddLaptop::setComboItems() {
    QStringList brands = model->getBrands();
    QStringList gNames = model->getGNames();
    for(QString brand: brands) {
        brandField->addItem(brand);
    }
    osSelect->addItem("Windows");
    osSelect->addItem("Chrome OS");
    osSelect->addItem("Linux");
    osSelect->addItem("Mac OSX");
}

AddLaptop::~AddLaptop() {

}


