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
#include <QPointer>
#include <QPushButton>
#include <QKeyEvent>

class LaptopModel;

class AddLaptop : public QDialog {
    Q_OBJECT

    public:
        explicit AddLaptop(LaptopModel &lapModel);
        explicit AddLaptop(LaptopModel &lapModel, int cartNo);
        virtual ~AddLaptop();
    public slots:
    private slots:
        void keyPressEvent(QKeyEvent *evt) override;
        void setWidgetProperties();
        void createWidgets();
        void addLaptopAction();
    signals:
    private:
        QPointer<LaptopModel> model;

        int cartNum;
        LaptopModel::Laptop laptop;

        QPointer<QVBoxLayout> mainLayout;
        QPointer<QVBoxLayout> fieldLayout;
        QPointer<QHBoxLayout> buttonLayout;

        QPointer<QPushButton> addButton;
        QPointer<QPushButton> cancelButton;

        QPointer<QLabel> cartNumLabel;
        QPointer<QLineEdit> assetField;
        QPointer<QLabel> brandLabel;
        QPointer<QComboBox> brandField;
        QPointer<QLabel>  genericNLabel;
        QPointer<QComboBox> genericNField;
        QPointer<QLineEdit> modelField;
        QPointer<QLineEdit> serialField;
        QPointer<QLabel>  osLabel;
        QPointer<QComboBox> osSelect;
        QPointer<QLabel> cartNumSelectLabel;
        QPointer<QComboBox> cartNumberSelect;

        QPointer<QGroupBox> statusGroup;
        QPointer<QHBoxLayout> statusLayout;
        QPointer<QRadioButton> workingStatusButton;
        QPointer<QRadioButton> brokenStatusButton;

        QPointer<QGroupBox> isDeployedGroup;
        QPointer<QHBoxLayout> deployedLayout;
        QPointer<QRadioButton> deployedButton;
        QPointer<QRadioButton> notDeployedButton;

};
#endif //ADDLAPTOP_H
