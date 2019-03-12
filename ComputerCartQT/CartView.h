#ifndef CARTVIEW_H
#define CARTVIEW_H

#include <QTableView>

class CartView : public QTableView {
    Q_OBJECT

    public:
        CartView(QWidget * parent = nullptr);
        //void test(const QItemSelection &selected, const QItemSelection &deselected);
    public slots:
    private slots:
    private:
};

#endif //CARTVIEW_H
