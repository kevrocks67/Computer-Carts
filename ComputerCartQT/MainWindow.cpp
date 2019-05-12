#include "MainWindow.h"
#include "Palette.h"

MainWindow::MainWindow(Session& session, CartModel& cModel) :
    mySession(session),
    cartModel(cModel) {
        //Set look and feel
        QApplication::setPalette(namedColorSchemePalette(Stealth));
        QFont sansFont("Helvetica [Cronyx]", 14);

        //Initialize layouts
        centralWidget = new QWidget(this);
        mainLayout = new QVBoxLayout(centralWidget);

        //Initialize widgets
        toolbar = new QToolBar();
        addTool = new QToolButton();
        removeTool = new QToolButton();
        editTool = new QToolButton();
        logoutTool = new QToolButton();
        themePicker = new QComboBox();
        cView = new CartView();

		//Set widget properties
        addTool->setText("Add");
        addTool->setFont(sansFont);
        removeTool->setText("Remove");
        removeTool->setFont(sansFont);
        editTool->setText("Edit");
        editTool->setFont(sansFont);
        logoutTool->setText("Logout");
        logoutTool->setFont(sansFont);
        logoutTool->setEnabled(false);

        //Phantom Style Picker
        themePicker->setFont(sansFont);
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
        toolbar->addWidget(logoutTool);
        toolbar->addSeparator();
        toolbar->addWidget(themePicker);

        cView->setModel(&cModel);

        //Add widgets to layouts
        mainLayout->addWidget(toolbar);
        mainLayout->addWidget(cView);
        setCentralWidget(centralWidget);
        show();
        raise();


        //Signals and slots

        newCart = new AddCart();
        editCart = new EditCart();
        deleteCart = new DeleteCart();

        //Check for dialog open
        connect(addTool, SIGNAL(clicked()),
                this, SLOT(addAction()));
        connect(editTool, SIGNAL(clicked()),
                this, SLOT(editAction()));
        connect(removeTool, SIGNAL(clicked()),
                this, SLOT(removeAction()));

        //Exec dialogs
        connect(addTool, SIGNAL(clicked()),
                newCart, SLOT(exec()));
        connect(editTool, SIGNAL(clicked()),
                editCart, SLOT(exec()));
        connect(removeTool, SIGNAL(clicked()),
            deleteCart, SLOT(exec()));

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
}

void MainWindow::removeAction() {
    //Get selected row
    int row = cView->getRow();
    //Convert row number to cart number
    QModelIndex modelIndex (cartModel.index(row, 0));
    int cart = cartModel.data(modelIndex).toInt();
    //Send cart number to modal for display and action
    deleteCart->setCartNum(cart);
}

void MainWindow::editAction() {
    //Get selected row
    int row = cView->getRow();
    //Convert row number to cart number
    QModelIndex modelIndex (cartModel.index(row, 0));
    int cart = cartModel.data(modelIndex).toInt();
    //Send cart number to modal for display and action
    editCart->setCartNum(cart);
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
}

void MainWindow::updateTable() {
    QString queryStr = cartModel.query().executedQuery();
    cartModel.clear();
    cartModel.query().clear();
    cartModel.setQuery(queryStr);
}

MainWindow::~MainWindow(){
}
