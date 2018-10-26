#ifndef CARTS_H
#define CARTS_H

#include <QApplication>
#include <QWidget>
#include <QSize>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolBar>
#include <QToolButton>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlQueryModel>

class Carts : public QWidget {
    Q_OBJECT
    public:
        explicit Carts(QWidget *parent = 0);
    signals:
    public slots:
    private slots:
        //void initializeModel(QSqlQueryModel *model);
        //QTableView* createView(QSqlQueryModel *model, const QString &title="");
    private:
        QVBoxLayout *mainLayout;
        QToolBar *toolbar;
        QToolButton *addTool;
        QToolButton *removeTool;
        QToolButton *logoutTool; 
        QToolButton *editTool;
};

#endif //CARTS_H
