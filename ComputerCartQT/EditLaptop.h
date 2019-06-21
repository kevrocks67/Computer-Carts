#ifndef EDITLAPTOP_H
#define EDITLAPTOP_H

#include "LaptopModel.h"

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QStringList>
#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QDebug>

class LaptopModel;
class EditLaptop : public QDialog {
    Q_OBJECT

    public:
        explicit EditLaptop(LaptopModel &lapModel);
        explicit EditLaptop(LaptopModel &lapModel, int cartNo);
        virtual ~EditLaptop();
    public slots:
        void setLapDetails(QString asset, QString gName);
    private slots:
        void setWidgetProperties();
        void createWidgets();
        void editLaptopAction();
        void keyPressEvent(QKeyEvent *evt) override;
    signals:
    private:
        LaptopModel *model;
        int cartNum;
        LaptopModel::Laptop laptop;

        QVBoxLayout *mainLayout;
        QVBoxLayout *fieldLayout;
        QHBoxLayout *buttonLayout;

        QPushButton *editButton;
        QPushButton *cancelButton;

        QLabel    *cartNumLabel;
        QLineEdit *assetField;
        QLabel *brandLabel;
        QComboBox *brandField;
        QLabel * genericNLabel;
        QComboBox *genericNField;
        QLineEdit *modelField;
        QLineEdit *serialField;
        QLabel *osLabel;
        QComboBox *osSelect;
        QLabel *cartNumSelectLabel;
        QComboBox *cartNumberSelect;

        QGroupBox *statusGroup;
        QHBoxLayout *statusLayout;
        QRadioButton *workingStatusButton;
        QRadioButton *brokenStatusButton;

        QGroupBox *isDeployedGroup;
        QHBoxLayout *deployedLayout;
        QRadioButton *deployedButton;
        QRadioButton *notDeployedButton;

};
#endif //EDITLAPTOP_H
