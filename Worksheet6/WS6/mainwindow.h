#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TreeModel/ModelPartList.h"
#include "TreeModel/ModelPart.h"
#include "optiondialog.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void handleButton();
    void ClickedTree();
    void on_actionOpen_File_triggered();
    void on_actionItem_Options_triggered();


signals:
    void statusUpdateMessage(const QString& message, int timeout);

private:
    Ui::MainWindow *ui;
    void SetupTreeView();
    ModelPartList* partList;
};
#endif // MAINWINDOW_H
