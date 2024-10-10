//
// Created by Guillaume Tran on 27/09/2024.
//

#include "EpiGimp.hpp"


EpiGimp::EpiGimp()
{
    mainWindow = MainWindow::getInstance();
}

EpiGimp::~EpiGimp()
{

}

void EpiGimp::run()
{
    mainWindow->show();
}