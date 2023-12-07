#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBoxN_valueChanged(int arg1);
    void on_spinBoxG_valueChanged(int arg1);
    void on_spinBoxP_valueChanged(int arg1);
    void on_spinBoxE_valueChanged(int arg1);

    void on_calculatePushButton_clicked();

private:
    Ui::MainWindow *ui;

    int N_ = 0;
    int G_ = 0;
    int P_ = 0;
    int E_ = 0;

};
#endif // MAINWINDOW_HH
