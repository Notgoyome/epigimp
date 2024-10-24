//
// Created by Guillaume Tran on 04/10/2024.
//

#include "DrawingArea.hpp"
#include "../core/MainWindow.hpp"

DrawingArea::DrawingArea(QWidget *parent, LayerManager *layerManager)
    : QWidget(parent) {
    _layerManager = layerManager;
    connect(_layerManager, &LayerManager::layersChanged, this, qOverload<>(&QWidget::update));
    _layerManager->saveHistory();
}

DrawingArea::~DrawingArea() {}

void DrawingArea::clear() {}

void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    _layerManager->saveHistory();

    if (event->button() == Qt::LeftButton)
    {
        _lastPoint = mapToImage(event->pos());
        _isDrawing = true;
    }
}
//r
void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && _isDrawing) {
        Layer* activeLayer = _layerManager->getCurrentLayer();
        if (activeLayer) {
            QPainter painter(&activeLayer->getImage());
            std::shared_ptr<MainWindow> mainWindow = MainWindow::getInstance();
            Tools *tools = mainWindow->getTools();
            QPen pen = tools->getPen();
            if (tools->getCurrentTool() == PEN) {
                painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
                painter.setPen(pen);
                draw(&painter, event->pos());
            }
            if (tools->getCurrentTool() == ERASER) {
                painter.setCompositionMode(QPainter::CompositionMode_Clear);
                painter.setPen(pen);
                draw(&painter, event->pos());
            }
        }
        _lastPoint = mapToImage(event->pos());
    }
    update();
}

void DrawingArea::draw(QPainter *painter, QPoint pos) {
    painter->drawLine(_lastPoint, mapToImage(pos));
    _lastPoint = mapToImage(pos);
}
//    painter.setPen(QPen(_pen.color(), 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//    painter.drawLine(_lastPoint, _lastPoint);



void DrawingArea::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && _isDrawing) {
//        Layer* activeLayer = _layerManager->getCurrentLayer();
//        if (activeLayer) {
//                QPainter painter(&activeLayer->getImage());
////            painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
////            painter.drawLine(lastPoint, event->pos());
//        }
        _isDrawing = false;
    }
}
//
void DrawingArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.translate(_panOffset);
    painter.scale(_zoomFactor, _zoomFactor);
    for (int i = 0; i < _layerManager->layerCount(); i++) {
        Layer *layer = _layerManager->getLayer(i);
        if (layer && layer->isVisible()) {
            painter.setCompositionMode(layer->getLayerBlendMode());
            painter.drawImage(0, 0, layer->getImage());
        }
    }
}

void DrawingArea::wheelEvent(QWheelEvent* event) {
    QPoint mousePos = event->position().toPoint();
    QPointF oldPos = (mousePos - _panOffset) / _zoomFactor;
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->angleDelta().y() > 0)
            _zoomFactor *= 1.1;
        else
            _zoomFactor /= 1.1;

        _zoomFactor = qBound(0.1, _zoomFactor, 15.0);
    }

    QPointF newPos = (mousePos - _panOffset) / _zoomFactor;
    _panOffset += (newPos - oldPos).toPoint() * _zoomFactor;
    update();
}

QPoint DrawingArea::mapToImage(const QPoint& pos) {
    return (pos - _panOffset) / _zoomFactor;
}