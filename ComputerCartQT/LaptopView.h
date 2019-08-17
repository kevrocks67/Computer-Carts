#ifndef LAPTOPVIEW_H
#define LAPTOPVIEW_H

#include <QTableView>
#include <QHeaderView>
#include <QMouseEvent>
#include <QModelIndex>


class LaptopView : public QTableView {
    Q_OBJECT

    public:
        LaptopView(QWidget * parent = nullptr);
        void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
        void mouseDoubleClickEvent(QMouseEvent *event) override;
    signals:
    public slots:
        int getRow();
        void clearUserSelections();
    private slots:
    private:
        int currentRow;
        int previousRow;
};

#endif //LAPTOPVIEW_H

