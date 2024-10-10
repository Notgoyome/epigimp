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
//#include "../menu_bar/CustomMenuBar.hpp"
//#include "../layers/LayerManager.hpp"
//#include "./DrawingArea.hpp"

class CustomMenuBar;
class LayerManager;
class DrawingArea;

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
public:
    LayerManager *getLayerManager() const;

};


#endif //UNTITLED2_MAINWINDOW_HPP
