//
// Created by Guillaume Tran on 04/10/2024.
//

#include "LayerManager.hpp"

LayerManager::LayerManager(QObject *parent) :
    QObject(parent) {
    addLayer();
    _currentLayer = 0;
}

LayerManager::~LayerManager()
{

}

Layer *LayerManager::getCurrentLayer() const
{
    return getLayer(_currentLayer);
}

int LayerManager::layerCount() const
{
    std::cout << _layers.size() << std::endl;
    return _layers.size();
}

void LayerManager::addLayer()
{
    Layer *layer = new Layer(this);
    layer->setParent(this);
    _layers.push_back(layer);
}

void LayerManager::addLayer(Layer *layer)
{
    layer->setParent(this);
    _layers.push_back(layer);
}
Layer *LayerManager::getLayer(int index) const
{
    if (index < 0 || index >= _layers.size())
        return nullptr;
    return _layers.at(index);
}