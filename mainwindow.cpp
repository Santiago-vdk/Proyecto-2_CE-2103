#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>

#include <QSplitter>

#include <QTreeView>
#include <QListView>
#include <QTableView>

#include <QFormLayout>
#include <QMessageBox>
#include "string"
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags( (windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    ui->output->setReadOnly(true);

    QTreeView *tree = new QTreeView();
    QListView *list = new QListView();
    QTableView *table = new QTableView();

    QFormLayout *layout = new QFormLayout();

    layout->addWidget( tree );
    layout->addWidget( list );
    //layout->addWidget( table );

    QStandardItemModel *model = new QStandardItemModel( 5, 2 );
    for( int r=0; r<5; r++ )
        for( int c=0; c<2; c++)
        {
            QStandardItem *item = new QStandardItem( QString("Row:%0, Column:%1").arg(r).arg(c) );

            if( c == 0 )
                for( int i=0; i<3; i++ )
                {
                    QStandardItem *child = new QStandardItem( QString("Item %0").arg(i) );
                    child->setEditable( false );
                    item->appendRow( child );
                }

            model->setItem(r, c, item);
        }


    tree->setModel( model );
    list->setModel( model );
    table->setModel( model );



    list->setSelectionModel( tree->selectionModel() );
    table->setSelectionModel( tree->selectionModel() );

    table->setSelectionBehavior( QAbstractItemView::SelectRows );
    table->setSelectionMode( QAbstractItemView::SingleSelection );

    ui->treeWidget->setLayout(layout);


    ui->tableView->setModel(model);
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(!(ui->input->text().isEmpty())){

        std::string comando = ui->input->text().toStdString();
        QString QComando = ui->input->text();
        /*Se llama al parser con el comando ingresado
         * if (parser(comando))
        */

        ui->output->append(ui->input->text());
        ui->input->clear();

    }
    else{
        QMessageBox *empty =  new QMessageBox();
        empty->setText("Error, por favor ingrese un comando.");
        empty->show();
    }

}

void MainWindow::on_input_textChanged(const QString &arg1)
{
    qDebug() << "Aqui";
    if (arg1 == "Test"){
        qDebug() << "COmando";

    }



}
