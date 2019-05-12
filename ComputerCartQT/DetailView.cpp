#include "DetailView.h"

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
