#include "optiondialog.h"
#include "ui_optiondialog.h"
#include "QSlider"

OptionDialog::OptionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
    /*connect(ui->horizontalSlider, &QSlider::sliderMoved, this , &OptionDialog::SliderUpdate);
    connect(ui->horizontalSlider_2, &QSlider::sliderMoved, this , &OptionDialog::SliderUpdate);
    connect(ui->horizontalSlider_3, &QSlider::sliderMoved, this , &OptionDialog::SliderUpdate);*/
    connect(ui->horizontalSlider, &QSlider::sliderReleased, this , &OptionDialog::SliderUpdate);
    connect(ui->horizontalSlider_2, &QSlider::sliderReleased, this , &OptionDialog::SliderUpdate);
    connect(ui->horizontalSlider_3, &QSlider::sliderReleased, this , &OptionDialog::SliderUpdate);
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

struct MenuData OptionDialog::getMenuData()
{
    struct MenuData menuData;
    menuData.r = ui->horizontalSlider->value();
    menuData.g = ui->horizontalSlider_2->value();
    menuData.b = ui->horizontalSlider_3->value();
    menuData.isVisible = ui->checkBox->isChecked();
    menuData.name = ui->plainTextEdit->toPlainText();

    return menuData;
}

void OptionDialog::setMenuData(MenuData data)
{
    ui->horizontalSlider->setValue(data.r);
    ui->horizontalSlider_2->setValue(data.g);
    ui->horizontalSlider_3->setValue(data.b);
    ui->plainTextEdit->setPlainText(data.name);
    ui->checkBox->setChecked(data.isVisible);
    ui->label_2->setText(QString("R: %1, G: %2, B: %3").arg(data.r).arg(data.g).arg(data.b));

}

void OptionDialog::SliderUpdate()
{
    struct MenuData colorData = getMenuData();
    ui->label_2->setText(QString("R: %1, G: %2, B: %3").arg(colorData.r).arg(colorData.g).arg(colorData.b));
}
