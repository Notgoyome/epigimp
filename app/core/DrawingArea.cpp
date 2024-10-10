//
// Created by Guillaume Tran on 04/10/2024.
//

#include "DrawingArea.hpp"

DrawingArea::DrawingArea(QWidget *parent, LayerManager *layerManager)
    : QWidget(parent) {
    _layerManager = layerManager;
}

DrawingArea::~DrawingArea() {}

void DrawingArea::clear() {}

void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();
        is_drawing = true;
    }
}
//
void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && is_drawing) {
        Layer* activeLayer = _layerManager->getCurrentLayer();
        if (activeLayer) {
            QPainter painter(&activeLayer->getImage());
            painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(lastPoint, event->pos());
            lastPoint = event->pos();
        }
        update();
    }
}
//
void DrawingArea::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && is_drawing) {
        Layer* activeLayer = _layerManager->getCurrentLayer();
        if (activeLayer) {
                QPainter painter(&activeLayer->getImage());
            painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(lastPoint, event->pos());
        }
        is_drawing = false;
    }
}
//
void DrawingArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    std::cout << "paintEvent" << _layerManager->layerCount() << std::endl;
    for (int i = 0; i < _layerManager->layerCount(); i++) {
        Layer *layer = _layerManager->getLayer(i);
        if (layer) {
            painter.drawImage(0, 0, layer->getImage());
        }
    }
}