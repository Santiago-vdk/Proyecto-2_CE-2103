#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QAction>
#include <QTextEdit>
#include <QTextCursor>
#include <QList>
#include <QString>
#include "facade.h"
#include <tabla.h>
#include <QStandardItemModel>
#include <QHeaderView>
#include <MatrizDato.h>
#include <ListaMetaDato.h>
#include <metaDato.h>



namespace Ui {
class GUI;
}

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit GUI(QWidget *parent = 0);
    ~GUI();

private slots:
    void crearBaseDeDatos();
    void cambiarModoCMD();
    void cambiarModoSQL();
    void on_botonEnviar_clicked();
    void on_limpiarOutput_clicked();
    void on_input_textChanged(const QString &arg1);
    void on_output_textChanged();
    void on_input_returnPressed();
    void on_copyClipboard_clicked();
    void vistaArbol();
    void crearPalabrasReservadas();
    void refrescaTabla();

private:
    Ui::GUI *ui;
    QObject *root;
    //QObject *tablas;
    QObject *child;
    QList<QTextEdit::ExtraSelection> selectionsOutput;
    QTextCursor cursorOutput;
    QList<QString> listaPalabrasReservadas;
    QList<QString> listaTiposReservados;
    Facade *facade;
    tabla *tablaVisual;

    //Tabla Visual
    QStandardItemModel model;
    QModelIndex modelIndex;
    QStringList horizontalHeader;

    ListaMetaDato *_header;
    MatrizDato *_infoTabla;

};

#endif // GUI_H
