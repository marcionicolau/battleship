/*
 * Battleship, classic battleship game
 * Copyright (C) 2014-2015 Pavel Dolgov
 *
 * See the LICENSE file for terms of use.
 */

#include "placeShips.hpp"
#include "startGame.hpp"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/battleship.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::settingOfBoards()
{
    ui->board1
    ->setSelectionMode(QAbstractItemView::NoSelection);
    ui->board1->horizontalHeader()
    ->setResizeMode(QHeaderView::Stretch);
    ui->board1->verticalHeader()
    ->setResizeMode(QHeaderView::Stretch);
    ui->board2
    ->setSelectionMode(QAbstractItemView::NoSelection);
    ui->board2->horizontalHeader()
    ->setResizeMode(QHeaderView::Stretch);
    ui->board2->verticalHeader()
    ->setResizeMode(QHeaderView::Stretch);
}

void MainWindow::errorHandling(std::exception& e)
{
    QString what = QString::fromStdString(e.what());
    QString error = "<b>The error occurred</b>."
                    "<br/><br/>Contact developers! "
                    "<b>pdolgov99@gmail.com</b>";
    what = what.replace("&", "&amp;");
    what = what.replace("'", "&apos;");
    what = what.replace("<", "&lt;");
    what = what.replace(">", "&gt;");
    what = what.replace("\"", "&quot;");
    QString m = error + "<br/><br/>" + what;
    QErrorMessage::qtHandler()->resize(400, 300);
    QErrorMessage::qtHandler()->showMessage(m);
}

void MainWindow::on_quitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_botVsBot_clicked()
{
    game_type_ = BOT_VS_BOT;
    ui->stackedWidget->setCurrentWidget(ui->inputpage);
}

void MainWindow::on_botVsHuman_clicked()
{
    game_type_ = BOT_VS_HUMAN;
    ui->stackedWidget->setCurrentWidget(ui->inputpage);
}

void MainWindow::on_humanVsHuman_clicked()
{
    game_type_ = HUMAN_VS_HUMAN;
    ui->stackedWidget->setCurrentWidget(ui->inputpage);
}

void MainWindow::on_playButton_clicked()
{
    try {
        ui->stackedWidget->setCurrentWidget(ui->gamepage);
        settingOfBoards();
        int width = ui->boardWidth->value();
        int length = ui->boardHeight->value();
        game_ = startGame(this, width, length);
        game_->controller->initialStateOfBoard();
        placeShips(*(game_->controller),
                   *(game_->desk), 1);
        placeShips(*(game_->controller),
                   *(game_->desk), 2);
        if (game_type_ == BOT_VS_HUMAN) {
            ui->board1->setModel(game_->t_model1.data());
            ui->board2->setModel(game_->t_model2.data());
        } else if (game_type_ == BOT_VS_BOT) {
            ui->board1->setModel(game_->t_model1.data());
            ui->board2->setModel(game_->t_model3.data());
        } else {
            ui->board1->setModel(game_->t_model1.data());
            ui->board2->setModel(game_->t_model2.data());
            ui->board3->setModel(game_->t_model3.data());
            ui->board4->setModel(game_->t_model4.data());
        }
    } catch (std::exception& e) {
        errorHandling(e);
    }
}
