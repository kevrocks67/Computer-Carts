#ifndef ADDLAPTOP_H
#define ADDLAPTOP_H

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

class LaptopModel;

class AddLaptop : public QDialog {
    Q_OBJECT

    public:
        explicit AddLaptop(LaptopModel &lapModel);
        virtual ~AddLaptop();
    public slots:
    private slots:
        void setComboItems();
    signals:
    private:
        LaptopModel *model;
        int cartNum;

        QVBoxLayout *mainLayout;
        QVBoxLayout *fieldLayout;
        QHBoxLayout *buttonLayout;

        QPushButton *addButton;
        QPushButton *cancelButton;

        QLabel    *cartNumLabel;
        QLineEdit *assetField;
        QLabel *brandLabel;
        QComboBox *brandField;
        QLabel * genericNLabel;
        QComboBox *genericNField;
        QLineEdit *modelField;

        QComboBox *osSelect;
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
#endif //ADDLAPTOP_H
