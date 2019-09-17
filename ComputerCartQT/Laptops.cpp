#include "Laptops.h"
#include <QDebug>

Laptops::Laptops(LaptopModel &laptopModel, LaptopView &laptopView, bool isCart) :
    model(laptopModel), view(laptopView) {

        mainLayout = new QVBoxLayout(this);

        //Initialize widgets

        refreshTool = new QToolButton();
        addTool = new QToolButton();
        editTool = new QToolButton();
        removeTool = new QToolButton();
        cartNum = new QLabel();

        searchBar = new QLineEdit(this);
        columnSelect = new QComboBox(this);
        searchBar->setPlaceholderText("Search");
        searchBar->setClearButtonEnabled(true);
        columnSelect->addItems(QStringList()<<"All"<<"Asset Tag"<<"Serial Num"<<"OS");

        proxy = new QSortFilterProxyModel(this);
        proxy->setSourceModel(&model);
        proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        view.setModel(proxy);


        //refreshTool(new QToolButton());
        //addTool(new QToolButton());
        //editTool(new QToolButton());
        //removeTool(new QToolButton());
        //cartNum(new QLabel());

        refreshTool->setIcon(QIcon("res/refresh-button.png"));
        refreshTool->setIconSize(QSize(65, 65));
        addTool->setText("Add");
        editTool->setText("Edit");
        removeTool->setText("Remove");

        toolbar = new QToolBar();
        //toolbar(new QToolBar());

        toolbar->setAllowedAreas(Qt::TopToolBarArea);
        toolbar->addWidget(refreshTool);
        toolbar->addWidget(addTool);
        toolbar->addWidget(editTool);
        toolbar->addWidget(removeTool);
        toolbar->addWidget(searchBar);
        toolbar->addWidget(columnSelect);


        //mainLayout = new QVBoxLayout(this);
        //mainLayout(new QVBoxLayout());

        if(isCart) {
            mainLayout->addWidget(toolbar);
            mainLayout->addWidget(cartNum);
            mainLayout->addWidget(&laptopView);

            connect(addTool, SIGNAL(clicked()),
                    this, SLOT(addActionCart()));
            connect(editTool, SIGNAL(clicked()),
                    this, SLOT(editActionCart()));
            connect(removeTool, SIGNAL(clicked()),
                    this, SLOT(deleteActionCart()));
        } else {
            mainLayout->addWidget(toolbar);
            mainLayout->addWidget(&laptopView);

            connect(addTool, SIGNAL(clicked()),
                    this, SLOT(addAction()));
            connect(editTool, SIGNAL(clicked()),
                    this, SLOT(editAction()));
            connect(removeTool, SIGNAL(clicked()),
                    this, SLOT(deleteAction()));
        }
        connect(refreshTool, SIGNAL(clicked()),
                this, SLOT(updateTable()));
        connect(searchBar, SIGNAL(textChanged(QString)),
                this, SLOT(search(QString)));
        connect(columnSelect, SIGNAL(activated(int)),
                this, SLOT(setSearchColumn(int)));

        setLayout(mainLayout);
        updateTable();
}

void Laptops::updateTable() {
     model.clear();
     model.query().clear();
     model.getLaptops();
     view.clearUserSelections();

     model.setHeaderData(0, Qt::Horizontal, tr("Asset Tag"));
     model.setHeaderData(1, Qt::Horizontal, tr("Brand"));
     model.setHeaderData(2, Qt::Horizontal, tr("Generic Name"));
     model.setHeaderData(3, Qt::Horizontal, tr("Model"));
     model.setHeaderData(4, Qt::Horizontal, tr("Serial No"));
     model.setHeaderData(5, Qt::Horizontal, tr("OS"));
     model.setHeaderData(6, Qt::Horizontal, tr("Cart Number"));
     model.setHeaderData(7, Qt::Horizontal, tr("Status"));
     model.setHeaderData(8, Qt::Horizontal, tr("IsDeployed"));
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

    int row = view.getRow();
    if (row >= 0) {
        QModelIndex assetModelIndex(model.index(row, 0));
        QModelIndex gNameModelIndex(model.index(row, 2));
        QString asset = model.data(assetModelIndex).toString();
        QString gName = model.data(gNameModelIndex).toString();
        editLaptop->setLapDetails(asset, gName);
        editLaptop->exec();
    }  else {
        qDebug()<<"No cart selected";
    }
}

void Laptops::editActionCart() {
    editLaptop = new EditLaptop(model, cartNo);
    connect(editLaptop, SIGNAL(accepted()),
            this, SLOT(updateTableCart()));

    int row = view.getRow();
    if (row >= 0) {
        QModelIndex assetModelIndex(model.index(row, 0));
        QModelIndex gNameModelIndex(model.index(row, 2));
        QString asset = model.data(assetModelIndex).toString();
        QString gName = model.data(gNameModelIndex).toString();
        editLaptop->setLapDetails(asset, gName);
        editLaptop->exec();
    }  else {
        qDebug()<<"No cart selected";
    }
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

void Laptops::search(const QString &query) {
    proxy->setFilterFixedString(query);
}

void Laptops::setSearchColumn(int index) {
    if(index == 0) {
        proxy->setFilterKeyColumn(-1);
    } else if (index == 1) {
        proxy->setFilterKeyColumn(0);
    } else if (index == 2) {
        proxy->setFilterKeyColumn(4);
    } else if (index == 3) {
        proxy->setFilterKeyColumn(5);
    }
}

Laptops::~Laptops(){
    delete mainLayout;
}
