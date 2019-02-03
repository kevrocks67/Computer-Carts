#include "MainWindow.h"
#include "AddCart.h"
#include "EditCart.h"

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
        connect(addTool, SIGNAL(clicked()),
                newCart, SLOT(exec()));
        connect(editTool, SIGNAL(clicked()),
                editCart, SLOT(exec()));
        /*connect(removeTool, SIGNAL(clicked()),
                delCart, SLOT(exec()));*/

        //Check for AddCart modal close
        //connect(newCart, SIGNAL(accepted()), SLOT(GetDialogOutput()));
}

/*
void MainWindow::GetDialogOutput() {
    int Opt1;
    newCart->GetOptions(Opt1);
    qDebug()<<Opt1;
    qDebug()<<"dialog closed";
}*/

MainWindow::~MainWindow(){
}
