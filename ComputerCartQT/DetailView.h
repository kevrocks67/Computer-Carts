#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include "CartModel.h"

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class CartModel;

class DetailView : public QDialog {
    Q_OBJECT

    public:
        explicit DetailView(QWidget * parent=0);
        virtual ~DetailView();
    public slots:
        void getDetails(int cartNo);
    private slots:
    private:
        CartModel *cartModel;

        //Main Widgets
        QVBoxLayout *mainLayout;
        QTabWidget *tabWidget;
        QWidget *cartWidget;
        QWidget *resWidget;
        QVBoxLayout *cartLayout;
        QVBoxLayout *resLayout;
        QPushButton *closeButton;

        //Cart Tab Widgets
        QLabel *cartNumLabel;
        QLabel *compTypeLabel;
        QLabel *quantLabel;
        QLabel *cRoomLabel;
        QLabel *cPeriodLabel;
        QTextEdit *commentBox;
};
#endif //DETAILVIEW_H
