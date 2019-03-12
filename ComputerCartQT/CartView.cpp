#include "CartView.h"
#include "QHeaderView"
#include "QDebug"

CartView::CartView(QWidget * parent):
    QTableView(parent) {
        QFont sansFont("Helvetica [Cronyx]", 14);
        this->setFont(sansFont);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);
        //this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

