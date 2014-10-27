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
#include "objecttreemodel.h"

#include "listaTabla.h"
#include "tabla.h"

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
    setIconSize(QSize(40,40));

    QAction *fsql = toolbar->addAction("FSQL");
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
    ui->output->setReadOnly(true);
    cursorOutput = ui->output->textCursor();

    //Set' arbol
    root= new QObject();
    root->setObjectName( "root" );
    ui->arbolLayout->addWidget( ui->vistaArbol );
    ui->arbolWidget->setLayout(ui->arbolLayout);
    vistaArbol();
    //Fin de propiedades de las ventanas

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
        QObject *base = new QObject(root);
        base->setObjectName(text);
        vistaArbol();
        //Insertar en lista con bases
    }
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

void GUI::on_botonEnviar_clicked()
{
    if(!(ui->input->text().isEmpty())){
        std::string comando = ui->input->text().toStdString();
        /*Se llama al parser con el comando ingresado
            * if (parser(comando))
            * Luego implementar el comando grafico
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



void GUI::on_input_textChanged(const QString &arg1)
{

}

void GUI::on_output_textChanged()
{
    selectionsOutput.clear();
    ui->output->extraSelections().clear();


    //Formato para tipos de datos
    QTextCharFormat fmt3;
    fmt3.setForeground(QColor("#808BED"));
    fmt3.setFontWeight(QFont::Bold);


    //Formato palabras reservadas
    QTextCharFormat fmt;
    fmt.setForeground(QColor("#028885"));
    fmt.setFontWeight(QFont::Bold);


    //Formato Texto Entre Parentesis
    QTextCharFormat fmt2;
    fmt2.setForeground(QColor("Black"));
    fmt2.setFontWeight(QFont::Bold);

    //Texto entre parentesis
    while( !(cursorOutput = ui->output->document()->find(QRegExp("("), cursorOutput)).isNull()) {
        QTextEdit::ExtraSelection sel = { cursorOutput, fmt2 };
        selectionsOutput.append(sel);
    }

    //Obtener palabras reservadas por facade
    while( !(cursorOutput = ui->output->document()->find(QRegExp("CREATE TABLE"), cursorOutput)).isNull()) {
        QTextEdit::ExtraSelection sel = { cursorOutput, fmt };
        selectionsOutput.append(sel);
    }

    //Palabras reservadas
    while( !(cursorOutput = ui->output->document()->find(QRegExp("String"), cursorOutput)).isNull()) {
        QTextEdit::ExtraSelection sel = { cursorOutput, fmt3 };
        selectionsOutput.append(sel);
    }
    ui->output->setExtraSelections(selectionsOutput);
    ui->output->extraSelections().clear();
}

void GUI::on_input_returnPressed()
{
    if(!(ui->input->text().isEmpty())){
        std::string comando = ui->input->text().toStdString();
        /*Se llama al parser con el comando ingresado
            * if (parser(comando))
           */
        ui->output->append(ui->input->text());
        ui->input->clear();


        //Insercion de tabla nueva dentro arbol de tablas, deberia insertar dentro de una base de datos seleccionada
//        QObject *tabla1 = new QObject( tablas );
//        tabla1->setObjectName( "Tabla #1" );
//        ui->vistaArbol->expandAll();



    }
    else{
        QMessageBox *empty =  new QMessageBox();
        empty->setText("Error, por favor ingrese un comando.");
        empty->show();
    }
}

void GUI::on_copyClipboard_clicked()
{
    ui->output->selectAll();
    ui->output->copy();

}

void GUI::vistaArbol()
{


    ObjectTreeModel *model = new ObjectTreeModel(root);
    ui->vistaArbol->setModel( model );


}

void GUI::on_pushButton_clicked()
{

//    child = new QObject( tabla1 );
//    child->setObjectName( "Mark" );
//    child = new QObject( tabla1 );
//    child->setObjectName( "Bob" );
//    child = new QObject( tabla1 );
//    child->setObjectName( "Kent" );

    ui->vistaArbol->expandAll();

}


GUI::~GUI()
{
    delete ui;
}
