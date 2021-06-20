#include "MainWindow.h"
#include "Palette.h"

MainWindow::MainWindow(CartModel& cModel, LaptopModel& lModel) :
    cartModel(cModel) {
        //Initialize classes for signal/slot usage
        newCart = new AddCart(this);
        editCart = new EditCart(this);
        deleteCart = new DeleteCart(this);
        detailView = new DetailView(this);
        settingsView = new Settings(this);


        //Initialize and create widgets
        tabs = new QTabWidget(this);
        cartWidget = new QWidget(this);

        createToolbar();

        cView = new CartView(this);
        //cView->setModel(&cModel);

        //Proxy model for searching
        proxy = new QSortFilterProxyModel(this);
        proxy->setSourceModel(&cModel);
        proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxy->setFilterKeyColumn(-1);

        cView->setModel(proxy);
        cView->hideColumns();

        lView = new LaptopView(this);
        lView->setModel(&lModel);
        lModel.getLaptops();

        //Initialize layouts
        mainLayout = new QVBoxLayout(cartWidget);

        //Add widgets to layouts
        mainLayout->addWidget(toolbar);
        mainLayout->addWidget(cView);

        //Load user preferences
        loadSettings();

        //Tabbed view setup
        laptopWidget = new Laptops(lModel, *lView, false);
        tabs->addTab(cartWidget,tr("Carts"));
        tabs->addTab(laptopWidget, tr("Laptops"));

        //Set MainWindow properties
        setCentralWidget(tabs);
        setMinimumSize(1200, 600);
        show();
        raise();

        //Check for dialog open action
        connect(refreshTool, SIGNAL(clicked()),
                this, SLOT(updateTable()));
        connect(addTool, SIGNAL(clicked()),
                this, SLOT(addAction()));
        connect(editTool, SIGNAL(clicked()),
                this, SLOT(editAction()));
        connect(removeTool, SIGNAL(clicked()),
                this, SLOT(removeAction()));
        connect(settingsTool, SIGNAL(clicked()),
                settingsView, SLOT(exec()));

        //Update table when laptop modified
        connect(&lModel, SIGNAL(updateCart()),
                this, SLOT(updateTable()));

        //Check for dialog close
        connect(newCart, SIGNAL(accepted()),
                this, SLOT(updateTable()));
        connect(editCart, SIGNAL(accepted()),
                this, SLOT(updateTable()));
        connect(deleteCart, SIGNAL(accepted()),
                this, SLOT(updateTable()));
        connect(deleteCart, SIGNAL(accepted()),
                this, SLOT(saveSettings()));

        //Theme Picker Combobox Events
        connect(settingsView, SIGNAL(themeChanged(int)),
                this, SLOT(changeTheme(int)));

        //DetailView dialog creation
        connect(cView, SIGNAL(showDetailsEvent(const QModelIndex)),
                this, SLOT(showDetails(const QModelIndex)));

        connect(settingsView, SIGNAL(fontChanged(const QFont)),
                this, SLOT(changeFont(const QFont)));
        //Search Bar
        connect(searchBar, SIGNAL(textChanged(QString)),
                SLOT(search(QString)));
        connect(columnSelect, SIGNAL(activated(int)),
                SLOT(setSearchColumn(int)));
}

void MainWindow::createToolbar() {
    //Initialize widgets
    toolbar = new QToolBar();
    refreshTool = new QToolButton();
    addTool = new QToolButton();
    removeTool = new QToolButton();
    editTool = new QToolButton();
    logoutTool = new QToolButton();
    settingsTool = new QToolButton();
    searchBar = new QLineEdit(this);
    columnSelect = new QComboBox(this);


    //Set widget properties
    refreshTool->setIcon(QIcon("res/refresh-button.png"));
    refreshTool->setIconSize(QSize(65, 65));
    addTool->setText("Add");
    removeTool->setText("Remove");
    editTool->setText("Edit");
    logoutTool->setText("Logout");
    logoutTool->setEnabled(false);
    settingsTool->setText("Settings");

    //Search Bar properties
    searchBar->setPlaceholderText("Search");
    searchBar->setClearButtonEnabled(true);
    columnSelect->addItems(QStringList()<<"All"<<"Cart Number"<<"Computer Type"
            <<"Current Room"<<"OS"<<"Home Location");

    toolbar->setAllowedAreas(Qt::TopToolBarArea);

    toolbar->addWidget(refreshTool);
    toolbar->addWidget(addTool);
    toolbar->addWidget(removeTool);
    toolbar->addWidget(editTool);
    toolbar->addSeparator();
    toolbar->addWidget(settingsTool);
    toolbar->addWidget(logoutTool);
    toolbar->addWidget(searchBar);
    toolbar->addWidget(columnSelect);
}

void MainWindow::changeTheme(int styleName) {
    switch (styleName) {
        case 0:
            QApplication::setPalette(namedColorSchemePalette(Carbon));
            break;
        case 1:
            QApplication::setPalette(namedColorSchemePalette(Polar));
            break;
        case 2:
            QApplication::setPalette(namedColorSchemePalette(Stealth));
            break;
        case 3:
            QApplication::setPalette(namedColorSchemePalette(Sakura));
            break;
        default:
            QApplication::setPalette(namedColorSchemePalette(Stealth));
            break;
    }
    saveSettings();
}

void MainWindow::removeAction() {
    //Get selected row
    int row = cView->getRow();
    if (row >= 0) {
        //Convert row number to cart number
        QModelIndex modelIndex (cartModel.index(row, 0));
        int cart = cartModel.data(modelIndex).toInt();
        //Send cart number to modal for display and action
        if(cart > 0) {
            deleteCart->setCartNum(cart);
            deleteCart->exec();
        }
    } else {
        qDebug()<<"No cart selected";
    }
}

void MainWindow::editAction() {
    //Get selected row
    int row = cView->getRow();
    if (row >= 0) {
        //Convert row number to cart number
        QModelIndex modelIndex (cartModel.index(row, 0));
        int cart = cartModel.data(modelIndex).toInt();
        //Send cart number to modal for display and action
        if(cart > 0) {
            editCart->setCartNum(cart);
            editCart->exec();
        }
    } else {
        qDebug()<<"No cart selected";
    }
}

void MainWindow::addAction() {
    int lastRow = cartModel.rowCount();
    //Account for 0 index
    lastRow--;
    //Convert row number to cart number
    QModelIndex modelIndex (cartModel.index(lastRow, 0));
    int cart = cartModel.data(modelIndex).toInt();
    //Get next cart number
    cart++;
    //Send cart number to modal for display and action
    newCart->setCartNum(cart);
    newCart->exec();
}

void MainWindow::updateTable() {
    QString queryStr = cartModel.query().executedQuery();
    cartModel.clear();
    cartModel.query().clear();
    cartModel.setQuery(queryStr);
    cView->clearUserSelections();
    cView->hideColumns();
    cartModel.setHeaderData(0, Qt::Horizontal, tr("Cart Number"));
    cartModel.setHeaderData(1, Qt::Horizontal, tr("Computer Type"));
    cartModel.setHeaderData(2, Qt::Horizontal, tr("Quantity"));
    cartModel.setHeaderData(3, Qt::Horizontal, tr("Current Room"));
    cartModel.setHeaderData(4, Qt::Horizontal, tr("Current Periods"));
    cartModel.setHeaderData(7, Qt::Horizontal, tr("OS"));
    cartModel.setHeaderData(9, Qt::Horizontal, tr("Home Location"));
    cartModel.setHeaderData(10, Qt::Horizontal, tr("Last Updated"));

}

void MainWindow::changeFont(const QFont &font) {
    qApp->setFont(font);
    this->setFont(font);
}

void MainWindow::showDetails(const QModelIndex &index) {
    //Convert table row to cart number
    int row = index.row();
    QModelIndex cartIndex (cartModel.index(row, 0));
    int cart = cartModel.data(cartIndex).toInt();
    if (cart > 0) {
        //Pass cart number to data fill function
        detailView->getDetails(cart);
        //Execute detailView
        detailView->exec();
    } else {
        QMessageBox::information(
            this,
            tr("Cart 0"),
            tr("This cart is reserved for laptops with no assigned cart") );
    }
}

void MainWindow::loadSettings() {
    //Eventually this will be replaced with NativeFile for OS standards compliance
    QSettings settings("config.ini", QSettings::IniFormat);
    auto theme = getThemeType(settings.value("app/theme"));

    QApplication::setPalette(namedColorSchemePalette(theme));
    //settingsView->setSettingsTheme(getThemeValue(theme));
    settingsView->setSettingsTheme(static_cast<int>(theme));
    this->setFont(settings.value("app/font").value<QFont>());
}

void MainWindow::saveSettings() {
    QSettings settings("config.ini", QSettings::IniFormat);

    this->repaint();
    updateTable();

    settings.setValue("app/font", this->font());
    settings.setValue("app/theme", settingsView->getTheme());
}

void MainWindow::search(const QString &query) {
    proxy->setFilterFixedString(query);
}

void MainWindow::setSearchColumn(int index) {
    if(index == 0) {
        proxy->setFilterKeyColumn(-1);
    } else if (index == 1) {
        proxy->setFilterKeyColumn(0);
    } else if (index == 2) {
        proxy->setFilterKeyColumn(1);
    } else if (index == 3) {
        proxy->setFilterKeyColumn(3);
    } else if (index == 4) {
        proxy->setFilterKeyColumn(7);
    } else if (index == 5) {
        proxy->setFilterKeyColumn(9);
    }
}

MainWindow::~MainWindow(){
}
