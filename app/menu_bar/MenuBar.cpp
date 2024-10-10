//
// Created by Guillaume Tran on 27/09/2024.
//

#include "CustomMenuBar.hpp"
#include "edit/FileMenu.hpp"

#include <iostream>

CustomMenuBar::CustomMenuBar(QWidget *parent) : QMenuBar(parent)
{
    _fileMenu = new FileMenu(this);
    _editMenu = new QMenu("Edit", this);
    _viewMenu = new QMenu("View", this);
    _helpMenu = new QMenu("Help", this);

    addMenu(_fileMenu);
    addMenu(_editMenu);
    addMenu(_viewMenu);
    addMenu(_helpMenu);


}

CustomMenuBar::~CustomMenuBar() {
    std::cout << "removing bar" << std::endl;
}
