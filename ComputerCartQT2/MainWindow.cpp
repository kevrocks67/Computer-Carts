#include "MainWindow.h"

MainWindow::MainWindow(Session& session, CartModel& cModel) :
    mySession(session),
    cartModel(cModel) {
        //UI shit goes here, either manually code or use .ui file
        centralWidget = new QWidget(this);
        mainLayout = new QVBoxLayout(centralWidget);
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

        //Add CartView to layout
        mainLayout->addWidget(toolbar);
        mainLayout->addWidget(cView);
        setCentralWidget(centralWidget);
        show();
        raise();
    }
