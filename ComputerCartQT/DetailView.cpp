#include "DetailView.h"
#include <QDebug>

DetailView::DetailView(QWidget * parent) :
    QDialog(parent) {

    mainLayout = new QVBoxLayout;
    tabWidget = new QTabWidget;
    cartWidget = new QWidget;
    resWidget = new QWidget;
    //laptopWidget = new QWidget;
    cartLayout = new QVBoxLayout;
    resLayout = new QVBoxLayout;
    closeButton = new QPushButton("Close");

    closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    //Cart Tab Widgets
    cartNumLabel = new QLabel();
    compTypeLabel = new QLabel();
    quantLabel = new QLabel();
    cRoomLabel = new QLabel();
    cPeriodLabel = new QLabel();
    osLabel = new QLabel();
    homeLabel = new QLabel();
    lockTypeLabel = new QLabel();
    commentLabel = new QLabel("Comments");
    commentBox = new QTextEdit();
    laptopsButton = new QPushButton("View Laptops In This Cart");

    //Cart Tab Widget Properties
    commentBox->setReadOnly(true);

    laptopView = new LaptopView();
    laptopModel = new LaptopModel("DetailViewLaptops");
    laptopView->setModel(laptopModel);
    laptops = new Laptops(*laptopModel, *laptopView, true);

    //Add widgets to Cart Widget
    cartLayout->addWidget(cartNumLabel);
    cartLayout->addWidget(compTypeLabel);
    cartLayout->addWidget(quantLabel);
    cartLayout->addWidget(cRoomLabel);
    cartLayout->addWidget(cPeriodLabel);
    cartLayout->addWidget(osLabel);
    cartLayout->addWidget(homeLabel);
    cartLayout->addWidget(lockTypeLabel);
    cartLayout->addWidget(commentLabel);
    cartLayout->addWidget(commentBox);
    cartLayout->addWidget(laptopsButton);

    cartWidget->setLayout(cartLayout);

    //Add widgets to layouts
    tabWidget->addTab(cartWidget, tr("Cart Info"));
    tabWidget->addTab(resWidget, tr("Reservations"));

    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(closeButton,0,Qt::AlignRight);
    setLayout(mainLayout);
    setModal(true);

    //Slots and signals
    connect(closeButton, SIGNAL(clicked()),
            SLOT(close()));
    connect(laptopsButton, SIGNAL(clicked()),
            this, SLOT(close()));
    connect(laptopsButton, SIGNAL(clicked()),
            laptops, SLOT(show()));
}

void DetailView::getDetails(int cartNo) {
    qDebug()<<"Getting details for cert number: "<<cartNo;
    CartModel::Cart cart = cartModel->getCart(cartNo);

    cartNumLabel->setText("Cart No: "+QString::number(cartNo));
    compTypeLabel->setText("Cart Type: "+cart.compType);
    quantLabel->setText("Quantity: "+QString::number(cart.quantity));
    cRoomLabel->setText("Current Location: "+cart.cRoom);
    cPeriodLabel->setText("Needed For Periods: "+cart.cPeriod);
    osLabel->setText("OS: "+cart.os);
    homeLabel->setText("Home Location: "+cart.homeLoc);
    lockTypeLabel->setText("Lock Type: "+cart.lockType);
    commentBox->setText(cart.comments);


    laptopModel->getLaptops(cartNo);
    laptops->setCartNum(cartNo);
    laptops->setCartNum("Cart Number: "+QString::number(cartNo));
    laptopView->repaint();
    laptops->repaint();
}

DetailView::~DetailView(){
}
