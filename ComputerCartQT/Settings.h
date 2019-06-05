#ifndef SETTINGS_H
#define SETTINGS_H

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialog>
#include <QDebug>

class Settings : public QDialog {
    Q_OBJECT

    public:
        explicit Settings(QWidget * parent=0);
        virtual ~Settings();
    public slots:
    private slots:
        void save();
    private:
        QVBoxLayout *mainLayout;
        QHBoxLayout *buttonLayout;
        QPushButton *cancelButton;
        QPushButton *saveButton;
};
#endif //SETTINGS_H
