#include "CartView.h"

CartView::CartView(QWidget * parent):
    QTableView(parent) {
        this->setAlternatingRowColors(true);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->setSelectionMode(QAbstractItemView::SingleSelection);
        this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        this->verticalHeader()->setVisible(false);
        this->setSortingEnabled(true);
        this->sortByColumn(0, Qt::AscendingOrder);
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
        clearUserSelections();
    }
}

void CartView::clearUserSelections() {
    this->clearSelection();
    QModelIndex nullpos = indexAt(QPoint(-1, -1));
    this->setCurrentIndex(nullpos);
}

int CartView::getRow() {
    return currentRow;
}

void CartView::hideColumns(){
    this->setColumnHidden(5,true);
    this->setColumnHidden(6,true);
    this->setColumnHidden(8,true);
    this->setColumnHidden(11,true);
}
