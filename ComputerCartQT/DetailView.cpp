#include "DetailView.h"
#include <QDebug>

DetailView::DetailView(QWidget * parent) :
    QDialog(parent) {

    mainLayout = new QVBoxLayout(this);
    tabWidget = new QTabWidget(this);
    cartWidget = new QWidget(this);
    resWidget = new QWidget(this);
    //laptopWidget = new QWidget;
    cartLayout = new QVBoxLayout();
    resLayout = new QVBoxLayout();
    closeButton = new QPushButton("Close", this);

    closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    //Cart Tab Widgets
    cartNumLabel = new QLabel(this);
    compTypeLabel = new QLabel(this);
    quantLabel = new QLabel(this);
    cRoomLabel = new QLabel(this);
    cPeriodLabel = new QLabel(this);
    osLabel = new QLabel(this);
    homeLabel = new QLabel(this);
    lockTypeLabel = new QLabel(this);
    commentLabel = new QLabel("Comments", this);
    commentBox = new QTextEdit(this);
    laptopsButton = new QPushButton("View Laptops In This Cart", this);

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
    if (resLayout != nullptr)
        delete resLayout;
    if (cartModel != nullptr)
        delete cartModel;
    if (laptopView != nullptr)
        delete laptopView;
    if (laptopModel != nullptr)
        delete laptopModel;
}
