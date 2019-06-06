#include "LaptopView.h"

LaptopView::LaptopView(QWidget * parent):
    QTableView(parent) {
        this->setAlternatingRowColors(true);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->setSelectionMode(QAbstractItemView::SingleSelection);
        this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
