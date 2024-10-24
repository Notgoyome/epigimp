//
// Created by Guillaume Tran on 27/09/2024.
//

#include "Layer.hpp"
#include "../core/MainWindow.hpp"

Layer::Layer(QObject *parent, int width, int height, Qt::GlobalColor color) : QObject(parent)
{
    _image =QImage(width, height, QImage::Format_ARGB32);
    _image.fill(color);
    _visible = true;
    _name = "Layer";
    _layerBlendMode = QPainter::CompositionMode_SourceOver;
}

Layer::~Layer()
{
}

void Layer::clear()
{
    _image.fill(Qt::GlobalColor::transparent);
}

void Layer::hide()
{
    _visible = false;
}

void Layer::show()
{
    _visible = true;
}

QImage& Layer::getImage() {
    return _image;
}

void Layer::setLayerBlendMode(QPainter::CompositionMode mode) {
    _layerBlendMode = mode;
}

void Layer::setImage(QImage image) {
    _image = image;
}

void Layer::serialize(QDataStream &stream) {
    QString name = QString::fromStdString(_name);
    stream << name;
    stream << _image;
    stream << _visible;
    stream << _layerBlendMode;
}

void Layer::deserialize(QDataStream &stream) {
    QString name;
    stream >> name;
    _name = name.toStdString();
    stream >> _image;
    stream >> _visible;
    stream >> _layerBlendMode;
}