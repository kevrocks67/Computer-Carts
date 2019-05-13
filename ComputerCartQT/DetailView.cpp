#include "DetailView.h"
#include <QDebug>

DetailView::DetailView(QWidget * parent) :
    QDialog(parent) {

    mainLayout = new QVBoxLayout;
    tabWidget = new QTabWidget;
    cartWidget = new QWidget;
    resWidget = new QWidget;
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
    commentBox = new QTextEdit();

    //Cart Tab Widget Properties
    commentBox->setReadOnly(true);

    //Add widgets to Cart Widget
    cartLayout->addWidget(cartNumLabel);
    cartLayout->addWidget(compTypeLabel);
    cartLayout->addWidget(quantLabel);
    cartLayout->addWidget(cRoomLabel);
    cartLayout->addWidget(cPeriodLabel);
    cartLayout->addWidget(commentBox);

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
}

DetailView::~DetailView(){
}

void DetailView::getDetails(int cartNo) {
    qDebug()<<"Getting details for cert number: "<<cartNo;
    CartModel::Cart cart = cartModel->getCart(cartNo);

    cartNumLabel->setText("Cart No: "+QString::number(cartNo));
    compTypeLabel->setText("Cart Type: "+cart.compType);
    quantLabel->setText("Quantity: "+QString::number(cart.quantity));
    cRoomLabel->setText("Current Location: "+cart.cRoom);
    cPeriodLabel->setText("Needed For Period: "+QString::number(cart.cPeriod));
}
