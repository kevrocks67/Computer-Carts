#include "CartView.h"
#include <QHeaderView>
#include <QDebug>

CartView::CartView(QWidget * parent):
    QTableView(parent) {
        QFont sansFont("Helvetica [Cronyx]", 14);
        this->setFont(sansFont);
        this->setAlternatingRowColors(true);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);
        //this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        this->setSelectionMode(QAbstractItemView::SingleSelection);
        this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void CartView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    currentRow = current.row();
    previousRow = previous.row();
}

void CartView::mouseDoubleClickEvent(QMouseEvent* event) {
    //Checks if item is selected before performing action
    QModelIndex index = indexAt(event->pos());

    if(index.isValid()) {
        emit showDetailsEvent(index);
    }
    else {
        qDebug()<<"No item under cursor pos";
        this->clearSelection();
    }
}

int CartView::getRow() {
    return currentRow;
}

