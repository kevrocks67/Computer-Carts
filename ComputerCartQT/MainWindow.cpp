#include "MainWindow.h"
#include "Palette.h"

MainWindow::MainWindow(CartModel& cModel) :
    cartModel(cModel) {
        //Load user preferences
        loadSettings();

        //Initialize layouts
        centralWidget = new QWidget(this);
        mainLayout = new QVBoxLayout(centralWidget);

        //Initialize and create widgets
        createToolbar();

        cView = new CartView();
        cView->setModel(&cModel);

        //Add widgets to layouts
        mainLayout->addWidget(toolbar);
        mainLayout->addWidget(cView);

        //Set MainWindow properties
        setCentralWidget(centralWidget);
        show();
        raise();


        //Initialize classes for signal/slot usage
        newCart = new AddCart();
        editCart = new EditCart();
        deleteCart = new DeleteCart();
        detailView = new DetailView();
        settingsView = new Settings();

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

        //Theme Picker Combobox Events
        connect(themePicker, SIGNAL(activated(int)),
                this, SLOT(changeTheme(int)));

        //DetailView dialog creation
        connect(cView, SIGNAL(showDetailsEvent(const QModelIndex)),
                this, SLOT(showDetails(const QModelIndex)));
}

void MainWindow::createToolbar() {
    //Initialize widgets
    toolbar = new QToolBar();
    addTool = new QToolButton();
    removeTool = new QToolButton();
    editTool = new QToolButton();
    logoutTool = new QToolButton();
    settingsTool = new QToolButton();
    themePicker = new QComboBox();

    //Set widget properties
    addTool->setText("Add");
    removeTool->setText("Remove");
    editTool->setText("Edit");
    logoutTool->setText("Logout");
    logoutTool->setEnabled(false);
    settingsTool->setText("Settings");

    //Phantom Style Picker
    themePicker->addItem("Default");
    themePicker->addItem("Carbon");
    themePicker->addItem("Polar");
    themePicker->addItem("Stealth");
    themePicker->addItem("Sakura");
    themePicker->setCurrentIndex(3);

    toolbar->setAllowedAreas(Qt::TopToolBarArea);
    toolbar->addWidget(addTool);
    toolbar->addWidget(removeTool);
    toolbar->addWidget(editTool);
    toolbar->addSeparator();
    toolbar->addWidget(settingsTool);
    toolbar->addWidget(logoutTool);
    toolbar->addSeparator();
    toolbar->addWidget(themePicker);
}

void MainWindow::changeTheme(int styleName) {
    switch (styleName) {
        case 0:
            QApplication::setPalette(namedColorSchemePalette(Stealth));
            break;
        case 1:
            QApplication::setPalette(namedColorSchemePalette(Carbon));
            break;
        case 2:
            QApplication::setPalette(namedColorSchemePalette(Polar));
            break;
        case 3:
            QApplication::setPalette(namedColorSchemePalette(Stealth));
            break;
        case 4:
            QApplication::setPalette(namedColorSchemePalette(Sakura));
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
        deleteCart->setCartNum(cart);
        deleteCart->exec();
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
        editCart->setCartNum(cart);
        editCart->exec();
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
}

void MainWindow::showDetails(const QModelIndex &index) {
    //Convert table row to cart number
    int row = index.row();
    QModelIndex cartIndex (cartModel.index(row, 0));
    int cart = cartModel.data(cartIndex).toInt();
    //Pass cart number to data fill function
    detailView->getDetails(cart);
    //Execute detailView
    detailView->exec();
}

void MainWindow::loadSettings() {
    //Eventually this will be replaced with NativeFile for OS standards compliance
    QSettings settings("config.ini", QSettings::IniFormat);
    auto theme = namedColorSchemePalette(getThemeType(settings.value("app/theme")));

    QApplication::setPalette(theme);
    this->setFont(settings.value("app/font").value<QFont>());
}

void MainWindow::saveSettings() {
    QSettings settings("config.ini", QSettings::IniFormat);

    //Settings menu: font = QFontDialog::getFont(...)
    this->repaint();
    updateTable();

    settings.setValue("app/font", this->font());
    settings.setValue("app/theme", themePicker->currentText());
}

MainWindow::~MainWindow(){
    saveSettings();
}
