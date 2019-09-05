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
#include <QPointer>
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
        QPointer<LaptopModel> model;

        int cartNum;
        LaptopModel::Laptop laptop;


        QPointer<QVBoxLayout> mainLayout;
        QPointer<QVBoxLayout> fieldLayout;
        QPointer<QHBoxLayout> buttonLayout;

        QPointer<QPushButton> editButton;
        QPointer<QPushButton> cancelButton;

        QPointer<QLabel> cartNumLabel;
        QPointer<QLineEdit> assetField;
        QPointer<QLabel> brandLabel;
        QPointer<QComboBox> brandField;
        QPointer<QLabel>  genericNLabel;
        QPointer<QComboBox> genericNField;
        QPointer<QLineEdit> modelField;
        QPointer<QLineEdit> serialField;
        QPointer<QLabel> osLabel;
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
#endif //EDITLAPTOP_H
