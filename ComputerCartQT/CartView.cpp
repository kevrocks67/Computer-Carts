#include "CartView.h"
#include <QHeaderView>
#include <QDebug>

CartView::CartView(QWidget * parent):
    QTableView(parent) {
        this->setAlternatingRowColors(true);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->setSelectionMode(QAbstractItemView::SingleSelection);
        this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        this->verticalHeader()->setVisible(false);
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

