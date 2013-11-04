#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&m_Scene);

    m_Barcode = new Code128Item();
    m_Barcode->setWidth( 300 );
    m_Barcode->setHeight( 80 );
    m_Barcode->setPos(0,0);
    m_Scene.addItem( m_Barcode );
    ui->lineEdit->setText("Promixis");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    m_Barcode->setText(arg1);
    m_Barcode->update();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
