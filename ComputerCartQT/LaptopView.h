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
        void mouseDoubleClickEvent(QMouseEvent *event) override;
    signals:
    public slots:
        void clearUserSelections();
    private slots:
    private:
};

#endif //LAPTOPVIEW_H

