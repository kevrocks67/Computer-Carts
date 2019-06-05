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
#include <QFont>
#include <QFontDialog>

class Settings : public QDialog {
    Q_OBJECT

    public:
        explicit Settings(QWidget * parent=0);
        virtual ~Settings();
    public slots:
    private slots:
        void save();
        void changeFontDialog();
    signals:
        void fontChanged(const QFont &font);
    private:
        QVBoxLayout *mainLayout;
        QHBoxLayout *buttonLayout;
        QPushButton *cancelButton;
        QPushButton *saveButton;

        QPushButton *changeFontButton;
};
#endif //SETTINGS_H
