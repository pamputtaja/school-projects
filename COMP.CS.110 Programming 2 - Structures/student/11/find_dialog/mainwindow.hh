#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <fstream>

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
    void on_closePushButton_clicked();

    void on_fileLineEdit_editingFinished();

    void on_keyLineEdit_editingFinished();

    void on_findPushButton_clicked();

private:
    Ui::MainWindow *ui;

    std::string file;
    std::string key;

    std::string to_upper_case(std::string line);
};
#endif // MAINWINDOW_HH
