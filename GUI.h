#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QAction>


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
//    void on_pushButton_clicked();
    void crearBaseDeDatos();
    void cambiarModoCMD();
    void cambiarModoSQL();

    void on_botonEnviar_clicked();

    void on_limpiarOutput_clicked();


private:
    Ui::GUI *ui;
//    QAction *ventananuevaBase;
//    QAction *ventanacmd;
//    QAction *ventanasql;
};

#endif // GUI_H
