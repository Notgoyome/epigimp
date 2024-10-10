//
// Created by Guillaume Tran on 27/09/2024.
//

#include "Layer.hpp"

Layer::Layer(QObject *parent) : QObject(parent)
{
    _image =QImage(800, 600, QImage::Format_RGB32);
    _visible = true;
}

Layer::~Layer()
{
}

void Layer::clear()
{
    _image.fill(Qt::white);
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

void Layer::setImage(QImage image) {
    _image = image;
}