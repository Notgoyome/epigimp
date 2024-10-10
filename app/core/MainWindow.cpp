#include "MainWindow.hpp"
#include "../menu_bar/CustomMenuBar.hpp"
#include "../layers/LayerManager.hpp"
#include "./DrawingArea.hpp"
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
{
    init();
}

void MainWindow::init()
{
    setWindowTitle("EpiGimp");
    resize(800, 600);

    _menuBar = new CustomMenuBar(this);
    setMenuBar(_menuBar);

    _layerManager = new LayerManager(this);
    _drawingArea = new DrawingArea(this, _layerManager);
    setCentralWidget(_drawingArea);
}

std::shared_ptr<MainWindow> MainWindow::getInstance()
{
    static std::shared_ptr<MainWindow> instance;
    if (!instance)
    {
        instance = std::make_shared<MainWindow>();
        instance->init();
    }
    return instance;
}

LayerManager *MainWindow::getLayerManager() const {
    return _layerManager;
}
