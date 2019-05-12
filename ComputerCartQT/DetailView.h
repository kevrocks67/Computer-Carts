#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include "CartModel.h"

#include <QApplication>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

class CartModel;

class DetailView : public QDialog {
    Q_OBJECT

    public:
        explicit DetailView(QWidget * parent=0);
        virtual ~DetailView();
    public slots:
    private slots:
    private:
        CartModel *cartModel;

        QVBoxLayout *mainLayout;
        QTabWidget *tabWidget;
        QWidget *cartWidget;
        QWidget *resWidget;
        QVBoxLayout *cartLayout;
        QVBoxLayout *resLayout;
        QPushButton *closeButton;
};
#endif //DETAILVIEW_H
