#include "MainWindow.h"
#include "AddCart.h"

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

        //Set widget properties
        addTool->setText("Add");
        removeTool->setText("Remove");
        editTool->setText("Edit");
        logoutTool->setText("Logout");
    
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
        AddCart *newCart = new AddCart();
        connect(addTool, SIGNAL(clicked()),
                newCart, SLOT(exec())); 
}

MainWindow::~MainWindow(){
}
