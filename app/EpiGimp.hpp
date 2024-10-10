//
// Created by Guillaume Tran on 27/09/2024.
//

#ifndef UNTITLED2_EPIGIMP_HPP
#define UNTITLED2_EPIGIMP_HPP

#include "core/MainWindow.hpp"

class EpiGimp {
public:
    EpiGimp();
    ~EpiGimp();
    void run();

private:
    std::shared_ptr<MainWindow> mainWindow;
};


#endif //UNTITLED2_EPIGIMP_HPP
