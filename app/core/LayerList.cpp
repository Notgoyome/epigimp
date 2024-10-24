#include "LayerList.hpp"
#include "MainWindow.hpp"

LayerList::LayerList(QWidget *parent) : QListWidget(parent), _layerManager(nullptr) {
    connect(this, &QListWidget::itemClicked, this, &LayerList::onLayerSelected);
}

void LayerList::init(LayerManager* layerManager) {
    _layerManager = MainWindow::getInstance()->getLayerManager();
    connect(_layerManager, &LayerManager::layersChanged, this, &LayerList::updateLayerList);
    updateLayerList();
}

void LayerList::updateLayerList() {
    clear();

    //TODO a mettre autre part le dict
    std::vector<std::pair<QPainter::CompositionMode, QString>> blendModeDict = {
        {QPainter::CompositionMode::CompositionMode_SourceOver, "normal"},
        {QPainter::CompositionMode::CompositionMode_Multiply, "multiply"},
        {QPainter::CompositionMode::CompositionMode_Xor, "xor"},
        {QPainter::CompositionMode::CompositionMode_Plus, "plus"},
        {QPainter::CompositionMode::CompositionMode_Screen, "screen"},
        {QPainter::CompositionMode::CompositionMode_Darken, "darken"},
        {QPainter::CompositionMode::CompositionMode_Lighten, "lighten"},
        };

    for (size_t i = 0; i < _layerManager->getLayers().size(); i++) {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(widget);
        layout->setContentsMargins(5, 2, 5, 2);

        QLabel* label = new QLabel(QString("Layer %1").arg(i + 1));
        layout->addWidget(label);
        layout->addStretch();

        QPushButton* deleteButton = new QPushButton("X");
        QPushButton* visibleButton = new QPushButton("V");
        QComboBox* blendMode = new QComboBox();
        for (auto& [key, value] : blendModeDict) {
            blendMode->addItem(value);
        }


        deleteButton->setFixedSize(20, 20);
        visibleButton->setFixedSize(20, 20);

        layout->addWidget(visibleButton);
        layout->addWidget(deleteButton);
        layout->addWidget(blendMode);

        connect(deleteButton, &QPushButton::clicked, [this, i]() {
            _layerManager->removeLayer(i);
            updateLayerList();
        });

        connect(blendMode, qOverload<int>(&QComboBox::activated), [this, i, blendMode, blendModeDict](int index) {
            _layerManager->setLayerBlendMode(i, blendModeDict[index].first);
            updateLayerList();
        });

        connect(visibleButton, &QPushButton::clicked, [this, i]() {
            _layerManager->setVisible(i, !_layerManager->getLayer(i)->isVisible());
            updateLayerList();
        });

        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(widget->sizeHint());
        addItem(item);
        setItemWidget(item, widget);
    }
}

void LayerList::onLayerSelected(QListWidgetItem* current) {
    if (current && _layerManager) {
        int index = row(current);
        _layerManager->setCurrentLayer(index);
    }
}