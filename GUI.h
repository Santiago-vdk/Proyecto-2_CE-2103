#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QAction>
#include <QTextEdit>
#include <QTextCursor>
#include <QList>
#include <QString>
#include "facade.h"


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
    void on_pushButton_clicked();
    void crearPalabrasReservadas();

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





};

#endif // GUI_H
