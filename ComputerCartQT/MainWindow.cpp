#include "MainWindow.h"
#include "Palette.h"

MainWindow::MainWindow(CartModel& cModel, LaptopModel& lModel) :
    cartModel(cModel) {
        //Initialize classes for signal/slot usage
        newCart = new AddCart();
        editCart = new EditCart();
        deleteCart = new DeleteCart();
        detailView = new DetailView();
        settingsView = new Settings();

        //Initialize layouts
        centralWidget = new QWidget(this);
        mainLayout = new QVBoxLayout(centralWidget);

        //Initialize and create widgets
        createToolbar();

        cView = new CartView();
        cView->setModel(&cModel);
        cView->hideColumns();

        lView = new LaptopView();
        lView->setModel(&lModel);
        lModel.getLaptops();

        //Add widgets to layouts
        mainLayout->addWidget(toolbar);
        mainLayout->addWidget(cView);

        //Load user preferences
        loadSettings();

        //Tabbed view setup
        tabs = new QTabWidget();
        laptopWidget = new Laptops(lModel, *lView, false);
        tabs->addTab(centralWidget,tr("Carts"));
        tabs->addTab(laptopWidget, tr("Laptops"));

        //Set MainWindow properties
        setCentralWidget(tabs);
        setMinimumSize(1200, 800);
        show();
        raise();


        //Check for dialog open action
        connect(addTool, SIGNAL(clicked()),
                this, SLOT(addAction()));
        connect(editTool, SIGNAL(clicked()),
                this, SLOT(editAction()));
        connect(removeTool, SIGNAL(clicked()),
                this, SLOT(removeAction()));
        connect(settingsTool, SIGNAL(clicked()),
                settingsView, SLOT(exec()));

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
}

void MainWindow::createToolbar() {
    //Initialize widgets
    toolbar = new QToolBar();
    addTool = new QToolButton();
    removeTool = new QToolButton();
    editTool = new QToolButton();
    logoutTool = new QToolButton();
    settingsTool = new QToolButton();

    //Set widget properties
    addTool->setText("Add");
    removeTool->setText("Remove");
    editTool->setText("Edit");
    logoutTool->setText("Logout");
    logoutTool->setEnabled(false);
    settingsTool->setText("Settings");

    toolbar->setAllowedAreas(Qt::TopToolBarArea);
    toolbar->addWidget(addTool);
    toolbar->addWidget(removeTool);
    toolbar->addWidget(editTool);
    toolbar->addSeparator();
    toolbar->addWidget(settingsTool);
    toolbar->addWidget(logoutTool);
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
    settingsView->setSettingsTheme((int) theme);
    this->setFont(settings.value("app/font").value<QFont>());
}

void MainWindow::saveSettings() {
    QSettings settings("config.ini", QSettings::IniFormat);

    this->repaint();
    updateTable();

    settings.setValue("app/font", this->font());
    settings.setValue("app/theme", settingsView->getTheme());
}

MainWindow::~MainWindow(){
    saveSettings();
}
