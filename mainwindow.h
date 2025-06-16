
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_outButton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton* Buttons[3][3];
    bool xTurn;
    int moveCount;

    void handleButtonClick(int row, int col);
    bool checkWin();
    bool checkDraw();
    void resetGame();
};

