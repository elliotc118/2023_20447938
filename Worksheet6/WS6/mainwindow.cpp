#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qmessagebox.h"
#include "qfiledialog.h"
#include "optiondialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::TreeClick);
    ui->treeView->addAction(ui->actionItem_Options);

    TreeView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    /*QMessageBox msgBox;
    msgBox.setText("Add button was clicked");
    msgBox.exec();*/

    emit statusUpdateMessage(QString("Add button was clicked"), 0);

}

void MainWindow::TreeView()
{

    /* Create/allocate the ModelList */
    this->partList = new ModelPartList("Parts List");

    /* Link it to the tree view in the GUI */
    ui->treeView->setModel(this->partList);

    /* Manually create a model tree - there are much better and more flexible ways of doing this,
       e.g. with nested functions. This is just a quick example as a starting point. */
    ModelPart* rootItem = this->partList->getRootItem();

    /* Add 3 top level items */
    for (int i = 0; i < 3; i++) {
        /* Create strings for both data columns */
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        /* Create child item */
        ModelPart* childItem = new ModelPart({ name, visible });

        /* Append to tree top-level */
        rootItem->appendChild(childItem);

        /* Add 5 sub-items */
        for (int j = 0; j < 5; j++) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart* childChildItem = new ModelPart({ name, visible });

            /* Append to parent */
            childItem->appendChild(childChildItem);
        }
    }

}

void MainWindow::TreeClick()
{
    /* Get the index of the selected item */
    QModelIndex index = ui->treeView->currentIndex();

    /* Get a pointer to the item from the index */
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    /* In this case, we will retrieve the name string from the internal QVariant data array */
    QString text = selectedPart->data(0).toString();

    emit statusUpdateMessage(QString("The selected item is: ") + text, 0);
}

void MainWindow::on_actionOpen_File_triggered() {
    // Add this line of code so you can see if the action is working
    emit statusUpdateMessage(QString("Open File action triggered"), 0);
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)")
        );

    if (fileName != "") {

        emit statusUpdateMessage(QString("File: " + fileName + "opened"), 0);
    }

}

void MainWindow::on_actionItem_Options_triggered() {
    //Option_Dialog dialog(this);

    QModelIndex index = ui->treeView->currentIndex();
    //Get a pointer to item from ModelPart index
    ModelPart* part = static_cast<ModelPart*>(index.internalPointer());

    if(part==nullptr)
    {
        return;
    }

    OptionDialog dialog(this);

    struct MenuData menuData;

    menuData.r= part->getColourR();
    menuData.g= part->getColourG();
    menuData.b= part->getColourB();

    menuData.name= part->data(0).toString();
    menuData.isVisible= part->data(1).toBool();

    dialog.setMenuData(menuData);

    if (dialog.exec() == QDialog::Accepted) {

        struct MenuData colour = dialog.getMenuData();

        part->r = colour.r;
        part->g = colour.g;
        part->b = colour.b;
        part->set(0, colour.name);
        part->set(1, QVariant(colour.isVisible).toString());
        emit statusUpdateMessage(QString("Dialog accepted"), 0);

    } else {
        emit statusUpdateMessage(QString("Dialog rejected"), 0);
    }



}
