#include "Laptops.h"
#include <QDebug>

Laptops::Laptops(LaptopModel &laptopModel, LaptopView &laptopView) :
    model(laptopModel), view(laptopView) {
        addLaptop = new AddLaptop(model);

        mainLayout = new QVBoxLayout;

        //Initialize widgets
        addTool = new QToolButton();
        editTool = new QToolButton();
        removeTool = new QToolButton();

        addTool->setText("Add");
        editTool->setText("Edit");
        removeTool->setText("Remove");

        toolbar = new QToolBar();
        toolbar->setAllowedAreas(Qt::TopToolBarArea);
        toolbar->addWidget(addTool);
        toolbar->addWidget(editTool);
        toolbar->addWidget(removeTool);

        cartNum = new QLabel();

        mainLayout = new QVBoxLayout();
        mainLayout->addWidget(toolbar);
        mainLayout->addWidget(cartNum);
        mainLayout->addWidget(&laptopView);

        setLayout(mainLayout);


        //Slots and signals
        connect(addTool, SIGNAL(clicked()),
                this, SLOT(updateTable()));
        connect(addTool, SIGNAL(clicked()),
                this, SLOT(addAction()));
}

void Laptops::updateTable() {
     QString queryStr = model.query().executedQuery();
     model.clear();
     model.query().clear();
     model.setQuery(queryStr);
     view.clearUserSelections();
}

void Laptops::setCartNum(QString label) {
    cartNum->setText(label);
}

void Laptops::addAction() {
    addLaptop->exec();
}

Laptops::~Laptops(){
}
