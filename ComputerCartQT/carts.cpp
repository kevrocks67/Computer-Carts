#include "carts.h"

Carts::Carts(QWidget * parent):
    QWidget(parent) {
        //Get size of screen
        QSize size = this->size();
        int h = size.height();
        int w = size.width();
        
        //Instantiate layouts
        mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(2);
        mainLayout->setContentsMargins(0, 0, 0, 0);

        //Instantiate widgets
        toolbar = new QToolBar();
        addTool = new QToolButton();
        removeTool = new QToolButton();
        editTool = new QToolButton();
        logoutTool = new QToolButton();
        
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


        /*QSqlTableModel model;
        initializeModel(&model);
        createView(&model, QObject::tr("Query Model"));*/

        //Add widgets to layouts
        mainLayout->addWidget(toolbar);
        setLayout(mainLayout);
    }
/*
void initializeModel(QSqlQueryModel *model) {
    model->setQuery("SELECT * FROM computercarts");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cart Number"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cart Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("C Room"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("C Period"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("F Room"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("F Period"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Status"));
}

QTableView* createView(QSqlQueryModel *model, const QString &title = "") {
    QTableView *view = new QTableView;
    view->setModel(model);
    static int offset = 0;

    view->setWindowTitle(title);
    view->move(100 + offset, 100 + offset);
    offset += 20;
    view->show();

    return view;
}
Carts::queryDB(){
    QSqlDatabase db = QSqlDatabase::addDatabase("carts.db");
    db.setHostName("localhost");
    db.setDatabaseName("data.db");
    if (!db.open()) {
      raise ...
    }

    QSqlQuery query = runQuery("SELECT * FROM user;", db);
    while (query.next()) {
    }
}*/
