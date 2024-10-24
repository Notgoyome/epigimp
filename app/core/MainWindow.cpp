#include <QHBoxLayout>
#include <QSplitter>
#include <QListWidgetItem>
#include "MainWindow.hpp"
#include "../menu_bar/CustomMenuBar.hpp"
#include "../layers/LayerManager.hpp"
#include "./DrawingArea.hpp"
#include "Tools.hpp"
#include "QColorDialog"
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
{
    this->setAttribute(Qt::WA_KeyCompression);
    this->setFocusPolicy(Qt::StrongFocus);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z && event->modifiers() & Qt::ControlModifier) {
        std::cout << "Undo!" << std::endl;
        _layerManager->undo();
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::init()
{
    setWindowTitle("EpiGimp");
    resize(1920, 1080);

    _menuBar = new CustomMenuBar(this);
    setMenuBar(_menuBar);

    _layerManager = new LayerManager(this);
    _drawingArea = new DrawingArea(this, _layerManager);

    _layerList = new LayerList(this);
    _layerList->init(_layerManager);

    _tools = new Tools(this);
//    _tools->init();


    // TO MOVE
    QVBoxLayout* layersLayout = new QVBoxLayout;
    QPushButton* addButton = new QPushButton("+", this);
    QPushButton* colorButton = new QPushButton("Couleur", this);
    connect(colorButton, &QPushButton::clicked, [this]() {
    QColor color = QColorDialog::getColor();
    _tools->setPenColor(color);

    });
    layersLayout->addWidget(colorButton);
    layersLayout->addWidget(addButton);
    layersLayout->addWidget(_layerList);

    QWidget* layersPanel = new QWidget(this);
    layersPanel->setLayout(layersLayout);


    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(_tools);
    splitter->addWidget(_drawingArea);
    splitter->addWidget(layersPanel);

    splitter->setStretchFactor(0, 3); //tools
    splitter->setStretchFactor(1, 6); //drawing area (index 0)
    splitter->setStretchFactor(2, 1); //layer panel

    _drawingArea->setMinimumWidth(200);
    layersPanel->setMinimumWidth(150);

    connect(_layerManager, &LayerManager::layersChanged, _layerList, &LayerList::updateLayerList);
    connect(_layerList, &QListWidget::itemClicked, _layerList, &LayerList::onLayerSelected);

    connect(addButton, &QPushButton::clicked, _layerList, &LayerList::updateLayerList);
    connect(addButton, &QPushButton::clicked, this, [this]() {
        _layerManager->addLayer();
    });

    setCentralWidget(splitter);
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

Tools *MainWindow::getTools() const {
    return _tools;
}