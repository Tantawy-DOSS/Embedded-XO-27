#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , xTurn(true)
    , moveCount(0)
{
    ui->setupUi(this);

    Buttons[0][0] = ui->b11;
    Buttons[0][1] = ui->b12;
    Buttons[0][2] = ui->b13;
    Buttons[1][0] = ui->b21;
    Buttons[1][1] = ui->b22;
    Buttons[1][2] = ui->b23;
    Buttons[2][0] = ui->b31;
    Buttons[2][1] = ui->b32;
    Buttons[2][2] = ui->b33;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            connect(Buttons[i][j], &QPushButton::clicked, [=]() {
                handleButtonClick(i, j);
            });
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::handleButtonClick(int row, int col) {
    if (!Buttons[row][col]->text().isEmpty()) return;

    Buttons[row][col]->setText(xTurn ? "X" : "O");
    moveCount++;

    if (checkWin()) {
        QMessageBox::information(this, "Game Over", QString("%1 كسب").arg(xTurn ? "X" : "O"));
        resetGame();
        return;
    }

    if (checkDraw()) {
        QMessageBox::information(this, "Game Over", "تعادل يخواتي");
        resetGame();
        return;
    }

    xTurn = !xTurn;
}

bool MainWindow::checkWin() {
    for (int i = 0; i < 3; ++i) {
        if (!Buttons[i][0]->text().isEmpty() &&
            Buttons[i][0]->text() == Buttons[i][1]->text() &&
            Buttons[i][1]->text() == Buttons[i][2]->text())
            return true;

        if (!Buttons[0][i]->text().isEmpty() &&
            Buttons[0][i]->text() == Buttons[1][i]->text() &&
            Buttons[1][i]->text() == Buttons[2][i]->text())
            return true;
    }

    if (!Buttons[0][0]->text().isEmpty() &&
        Buttons[0][0]->text() == Buttons[1][1]->text() &&
        Buttons[1][1]->text() == Buttons[2][2]->text())
        return true;

    if (!Buttons[0][2]->text().isEmpty() &&
        Buttons[0][2]->text() == Buttons[1][1]->text() &&
        Buttons[1][1]->text() == Buttons[2][0]->text())
        return true;

    return false;
}

bool MainWindow::checkDraw() {
    return moveCount == 9;
}

void MainWindow::resetGame() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            Buttons[i][j]->setText("");

    xTurn = true;
    moveCount = 0;
}

void MainWindow::on_startButton_clicked() {
    resetGame();
}

void MainWindow::on_outButton_clicked() {
    QApplication::quit();
}
