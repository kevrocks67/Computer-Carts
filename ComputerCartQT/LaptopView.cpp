#include "LaptopView.h"

LaptopView::LaptopView(QWidget * parent):
    QTableView(parent) {
        this->setAlternatingRowColors(true);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->setSelectionMode(QAbstractItemView::SingleSelection);
        this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void LaptopView::mouseDoubleClickEvent(QMouseEvent* event) {
    //Checks if item is selected before performing action
    QModelIndex index = indexAt(event->pos());

    if(!index.isValid()) {
        clearUserSelections();
    }
}

void LaptopView::clearUserSelections() {
    this->clearSelection();
    QModelIndex nullpos = indexAt(QPoint(-1, -1));
    this->setCurrentIndex(nullpos);
}
