#include "ResView.h"

ResView::ResView(QWidget * parent):
    QTableView(parent) {
        QFont sansFont("Helvetica [Cronyx]", 14);
        this->setFont(sansFont);
    }
