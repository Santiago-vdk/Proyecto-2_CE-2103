#include "GUI.h"
#include "ui_GUI.h"

#include <QStandardItemModel>

#include <QSplitter>

#include <QTreeView>
#include <QListView>
#include <QTableView>

#include <QFormLayout>
#include <QMessageBox>
#include "string"
#include <QDebug>
#include <QToolBar>
#include <QPropertyAnimation>
#include <QInputDialog>
#include <QDir>

#include <QModelIndex>

using namespace std;

GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
    this->setWindowFlags( (windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);

    //Barra de Menu
    QPixmap nuevaBasePix(":/recursos/database.png");
    QPixmap cmdPix(":/recursos/cmd.png");
    QPixmap sqlPix(":/recursos/sql.png");

    QToolBar *toolbar = addToolBar("ToolBar");
    setIconSize(QSize(32,32));

    QAction *ventananuevaBase = toolbar->addAction(QIcon(nuevaBasePix),"Nueva Base de Datos");
    QAction *ventanacmd = toolbar->addAction(QIcon(cmdPix),"Cambiar a Modo CMD");
    QAction *ventanasql = toolbar->addAction(QIcon(sqlPix),"Ejecutar Busqueda");

    toolbar->addSeparator();

    connect(ventananuevaBase,SIGNAL(triggered()), this, SLOT(crearBaseDeDatos()));
    connect(ventanacmd,SIGNAL(triggered()), this, SLOT(cambiarModoCMD()));
    connect(ventanasql,SIGNAL(triggered()), this, SLOT(cambiarModoSQL()));

    this->addToolBar(toolbar);
    //Fin barra menu

    //Propiedades de las ventanas, botones y iconos

    ui->output->setReadOnly(true);
    ui->vistaArbol->setDisabled(true);
    ui->input->setDisabled(true);



    //Fin de propiedades de las ventanas


    //QTreeView
    //    QTreeView *tree = new QTreeView();
    //    QListView *list = new QListView();
    //    QTableView *table = new QTableView();

    //    QFormLayout *layout = new QFormLayout();

    //    layout->addWidget( tree );
    //    layout->addWidget( list );
    //    //layout->addWidget( table );

    //    QStandardItemModel *model = new QStandardItemModel( 5, 2 );
    //    for( int r=0; r<5; r++ )
    //        for( int c=0; c<2; c++)
    //        {
    //            QStandardItem *item = new QStandardItem( QString("Row:%0, Column:%1").arg(r).arg(c) );

    //            if( c == 0 )
    //                for( int i=0; i<3; i++ )
    //                {
    //                    QStandardItem *child = new QStandardItem( QString("Item %0").arg(i) );
    //                    child->setEditable( false );
    //                    item->appendRow( child );
    //                }

    //            model->setItem(r, c, item);
    //        }


    //    tree->setModel( model );
    //    list->setModel( model );
    //    table->setModel( model );



    //    list->setSelectionModel( tree->selectionModel() );
    //    table->setSelectionModel( tree->selectionModel() );

    //    table->setSelectionBehavior( QAbstractItemView::SelectRows );
    //    table->setSelectionMode( QAbstractItemView::SingleSelection );

    //    ui->treeWidget->setLayout(layout);


    //    ui->tableView->setModel(model);
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


}



void GUI::crearBaseDeDatos()
{
    qDebug() << "Creo una nueva base de datos";

    bool ok;
    QInputDialog* inputDialog = new QInputDialog();
    inputDialog->setOptions(QInputDialog::NoButtons);

    QString text =  inputDialog->getText(NULL ,"QInputDialog::getText() Example",
                                         "Nombre Base de Datos:", QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);

    if (ok && !text.isEmpty())
    {
        qDebug() << text;
        QModelIndex* index = new QModelIndex();
        ui->vistaArbol->setRootIndex(*index);
    }



    ui->output->setReadOnly(false);
    ui->vistaArbol->setDisabled(false);
    ui->input->setDisabled(false);






}

void GUI::cambiarModoCMD()
{
    qDebug() << "Modo CMD";
    ui->stackedWidget->setCurrentIndex(0);

}

void GUI::cambiarModoSQL()
{
    qDebug() << "Modo SQL";
    ui->stackedWidget->setCurrentIndex(1);
}


GUI::~GUI()
{
    delete ui;
}

void GUI::on_botonEnviar_clicked()
{
    if(!(ui->input->text().isEmpty())){

        std::string comando = ui->input->text().toStdString();

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

void GUI::on_limpiarOutput_clicked()
{
    ui->output->clear();
}


