#ifndef CARTVIEW_H
#define CARTVIEW_H

#include <QTableView>

class CartView : public QTableView {
    Q_OBJECT

    public:
        CartView(QWidget * parent = nullptr);
        //void test(const QItemSelection &selected, const QItemSelection &deselected);
        void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
        int getRow();
    public slots:
        void updateTable();
    private slots:
    private:
        int currentRow;
        int previousRow;
};

#endif //CARTVIEW_H
