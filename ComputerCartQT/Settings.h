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
#include <QComboBox>
#include <QString>
#include <QLineEdit>
#include <QPointer>
#include <QSettings>

class Settings : public QDialog {
    Q_OBJECT

    public:
        explicit Settings(QWidget * parent=nullptr);
        virtual ~Settings();
    public slots:
        void setSettingsTheme(int theme);
        QString getTheme();
    private slots:
        void save();
        void changeFontDialog();
        void checkDriver(int choice);
    signals:
        void fontChanged(const QFont &font);
        void themeChanged(int);
    private:
        QPointer<QVBoxLayout> mainLayout;
        QPointer<QHBoxLayout> buttonLayout;
        QPointer<QPushButton> cancelButton;
        QPointer<QPushButton> saveButton;

        QPointer<QPushButton> changeFontButton;
        QPointer<QComboBox> themePicker;
        QPointer<QComboBox> driverPicker;
        QPointer<QLabel> hostLabel;
        QPointer<QLineEdit> hostField;
        QPointer<QLabel> userLabel;
        QPointer<QLineEdit> userField;
        QPointer<QLabel> passLabel;
        QPointer<QLineEdit> passField;
};
#endif //SETTINGS_H
