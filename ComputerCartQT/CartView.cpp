#include "CartView.h"
#include <QDebug>

CartView::CartView(QWidget * parent):
    QTableView(parent) {
        QFont sansFont("Helvetica [Cronyx]", 14);
        this->setFont(sansFont);
    }

void CartView::updateTable(){
    this->repaint();
    qDebug()<<"Updating view";
}
