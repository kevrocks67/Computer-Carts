#include "Laptops.h"
#include <QDebug>

Laptops::Laptops(LaptopModel &laptopModel, LaptopView &laptopView) :
    model(laptopModel), view(laptopView) {

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
                this, SLOT(addActionCart()));
        connect(editTool, SIGNAL(clicked()),
                this, SLOT(editActionCart()));
        connect(removeTool, SIGNAL(clicked()),
                this, SLOT(deleteActionCart()));
}

void Laptops::updateTable() {
     model.clear();
     model.query().clear();
     model.getLaptops();
     view.clearUserSelections();
}

void Laptops::updateTableCart() {
     model.clear();
     model.query().clear();
     model.getLaptops(cartNo);
     view.clearUserSelections();
}

void Laptops::setCartNum(int cartno) {
    cartNo = cartno;
}

void Laptops::setCartNum(QString label) {
    cartNum->setText(label);
}

void Laptops::addAction() {
    addLaptop = new AddLaptop(model);
    connect(addLaptop, SIGNAL(accepted()),
            this, SLOT(updateTable()));
    addLaptop->exec();
}

void Laptops::addActionCart() {
    addLaptop = new AddLaptop(model, cartNo);
    connect(addLaptop, SIGNAL(accepted()),
            this, SLOT(updateTableCart()));
    addLaptop->exec();
}

void Laptops::editAction() {
    editLaptop = new EditLaptop(model);
    connect(editLaptop, SIGNAL(accepted()),
            this, SLOT(updateTable()));
    editLaptop->exec();
}

void Laptops::editActionCart() {
    editLaptop = new EditLaptop(model, cartNo);
    connect(editLaptop, SIGNAL(accepted()),
            this, SLOT(updateTableCart()));
    editLaptop->exec();
}

void Laptops::deleteAction() {
    deleteLaptop = new DeleteLaptop(model);
    connect(deleteLaptop, SIGNAL(accepted()),
            this, SLOT(updateTable()));

    int row = view.getRow();
    if (row >= 0) {
        QModelIndex assetModelIndex(model.index(row, 0));
        QModelIndex gNameModelIndex(model.index(row, 2));
        QString asset = model.data(assetModelIndex).toString();
        QString gName = model.data(gNameModelIndex).toString();
        deleteLaptop->setLapDetails(asset, gName);
        deleteLaptop->exec();
    }  else {
        qDebug()<<"No cart selected";
    }
}

void Laptops::deleteActionCart() {
    deleteLaptop = new DeleteLaptop(model);
    connect(deleteLaptop, SIGNAL(accepted()),
            this, SLOT(updateTableCart()));

    int row = view.getRow();
    if (row >= 0) {
        QModelIndex assetModelIndex(model.index(row, 0));
        QModelIndex gNameModelIndex(model.index(row, 2));
        QString asset = model.data(assetModelIndex).toString();
        QString gName = model.data(gNameModelIndex).toString();
        deleteLaptop->setLapDetails(asset, gName);
        deleteLaptop->exec();
    }  else {
        qDebug()<<"No cart selected";
    }
}

Laptops::~Laptops(){
}
