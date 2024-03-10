#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = nullptr);
    ~OptionDialog();
    struct MenuData getMenuData();
    void setMenuData(MenuData data);
    void SliderUpdate();

private:
    Ui::OptionDialog *ui;
};

struct MenuData{
    QString name;
    bool isVisible;
    unsigned int r;
    unsigned int b;
    unsigned int g;
};

#endif // OPTIONDIALOG_H
