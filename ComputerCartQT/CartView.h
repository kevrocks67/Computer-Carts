#ifndef CARTVIEW_H
#define CARTVIEW_H

#include <QTableView>
#include <QMouseEvent>
#include <QHeaderView>
#include <QPoint>
#include <QDebug>

class CartView : public QTableView {
    Q_OBJECT

    public:
        CartView(QWidget * parent = nullptr);
        void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
        void mouseDoubleClickEvent(QMouseEvent* event) override;
        void clearUserSelections();
    signals:
        void showDetailsEvent(const QModelIndex &index);
    public slots:
        int getRow();
    private slots:
    private:
        int currentRow;
        int previousRow;
};

#endif //CARTVIEW_H
