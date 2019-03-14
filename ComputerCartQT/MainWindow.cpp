#include "MainWindow.h"

MainWindow::MainWindow(Session& session, CartModel& cModel) :
    mySession(session),
    cartModel(cModel) {
        //Initialize layouts
        centralWidget = new QWidget(this);
        mainLayout = new QVBoxLayout(centralWidget);

        //Initialize widgets
        toolbar = new QToolBar();
        addTool = new QToolButton();
        removeTool = new QToolButton();
        editTool = new QToolButton();
        logoutTool = new QToolButton();
        cView = new CartView();
        QFont sansFont("Helvetica [Cronyx]", 14);
//Set widget properties
        addTool->setText("Add");
        addTool->setFont(sansFont);
        removeTool->setText("Remove");
        removeTool->setFont(sansFont);
        editTool->setText("Edit");
        editTool->setFont(sansFont);
        logoutTool->setText("Logout");
        logoutTool->setFont(sansFont);

        toolbar->setAllowedAreas(Qt::TopToolBarArea);
        toolbar->addWidget(addTool);
        toolbar->addWidget(removeTool);
        toolbar->addWidget(editTool);
        toolbar->addSeparator();
        toolbar->addWidget(logoutTool);

        cView->setModel(&cModel);

        //Add widgets to layouts
        mainLayout->addWidget(toolbar);
        mainLayout->addWidget(cView);
        setCentralWidget(centralWidget);
        show();
        raise();

        //Slots and signals
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
                this, SLOT(update()));
        connect(editCart, SIGNAL(accepted()),
                this, SLOT(update()));
        connect(deleteCart, SIGNAL(accepted()),
                this, SLOT(update()));

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

/*
void MainWindow::GetDialogOutput() {
    int Opt1;
    newCart->GetOptions(Opt1);
    qDebug()<<Opt1;
    qDebug()<<"dialog closed";
}*/

void MainWindow::update() {
    QString queryStr = cartModel.query().executedQuery();
    cartModel.clear();
    cartModel.query().clear();
    cartModel.setQuery(queryStr);
}
MainWindow::~MainWindow(){
}
