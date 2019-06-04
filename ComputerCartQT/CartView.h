#ifndef CARTVIEW_H
#define CARTVIEW_H

#include <QTableView>
#include <QMouseEvent>

class CartView : public QTableView {
    Q_OBJECT

    signals:
        void showDetailsEvent(const QModelIndex &index);
    public:
        CartView(QWidget * parent = nullptr);
        void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
        void mouseDoubleClickEvent(QMouseEvent* event) override;
        int getRow();
        void clearUserSelections();
    public slots:
    private slots:
    private:
        int currentRow;
        int previousRow;
};

#endif //CARTVIEW_H
