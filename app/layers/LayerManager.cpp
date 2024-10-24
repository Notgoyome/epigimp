//
// Created by Guillaume Tran on 04/10/2024.
//

#include "LayerManager.hpp"

LayerManager::LayerManager(QObject *parent) :
    QObject(parent) {
    _currentLayer = 0;
    _width = 800;
    _height = 600;
    addLayer(Qt::GlobalColor::white);

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
    return _layers.size();
}

void LayerManager::addLayer(Qt::GlobalColor color)
{
    Layer *layer = new Layer(this,_width, _height, color);
    addLayer(layer);
}

void LayerManager::addLayer(Layer *layer)
{
    layer->setParent(this);
    _layers.push_back(layer);
    emit layersChanged();
}

void LayerManager::removeLayer(int index)
{
    if (index < 0 || index >= _layers.size())
        return;
    _layers.remove(index);
    emit layersChanged();
}

void LayerManager::setVisible(int index, bool visible) {
    if (index < 0 || index >= _layers.size())
        return;
    _layers[index]->setVisible(visible);
    emit layersChanged();
}

void LayerManager::setLayerBlendMode(int index, QPainter::CompositionMode mode)
{
    _layers[index]->setLayerBlendMode(mode);
    emit layersChanged();
}

Layer *LayerManager::getLayer(int index) const
{
    if (index < 0 || index >= _layers.size())
        return nullptr;
    return _layers.at(index);
}

void LayerManager::reset()
{
    for (Layer *layer : _layers)
        delete layer;
    _layers.clear();
    addLayer(Qt::GlobalColor::white);
    emit layersChanged();
}

void LayerManager::set_size(int width, int height) {
    _width = width;
    _height = height;
    emit layersChanged();
}

void LayerManager::saveHistory() {
    if (_history.size() >= maxHistory) {
        _history.pop_front();
    }
    std::cout << "Saving history " << _history.size() << std::endl;
    QVector<Layer*> copy;
    for (Layer* layer : _layers) {
        Layer* newLayer = new Layer(this, _width, _height, Qt::transparent);
        newLayer->setImage(layer->getImage());
        newLayer->setLayerBlendMode(layer->getLayerBlendMode());
        newLayer->setVisible(layer->isVisible());
        copy.push_back(newLayer);
    }
    _history.push_back(copy);
}


void LayerManager::undo() {
    if (!_history.empty()) {

        _layers = _history.back();
        _history.pop_back();
        std::cout << "Undo " << _history.size() << std::endl;
        emit layersChanged();
    }
}