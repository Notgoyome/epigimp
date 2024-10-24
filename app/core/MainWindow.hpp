//
// Created by Guillaume Tran on 27/09/2024.
//

#ifndef UNTITLED2_MAINWINDOW_HPP
#define UNTITLED2_MAINWINDOW_HPP

#include <iostream>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <memory>
#include <QComboBox>
#include <QListWidget>
#include "LayerList.hpp"
#include <QPushButton>
#include "Tools.hpp"
//#include "../menu_bar/CustomMenuBar.hpp"
//#include "../layers/LayerManager.hpp"
//#include "./DrawingArea.hpp"

class CustomMenuBar;
class LayerManager;
class DrawingArea;
class Tools;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    static std::shared_ptr<MainWindow> getInstance();

    ~MainWindow() = default;

    void init();
private:
    CustomMenuBar *_menuBar;
    LayerManager *_layerManager;
    DrawingArea *_drawingArea;
    LayerList *_layerList;
    Tools *_tools;

public:
    LayerManager *getLayerManager() const;
    Tools *getTools() const;

    void keyPressEvent(QKeyEvent *event);
};


#endif //UNTITLED2_MAINWINDOW_HPP
