#pragma once

#include <QWidget>
#include <QImage>
#include <QPainter>
#include "../layers/LayerManager.hpp"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QComboBox>

class DrawingArea : public QWidget {
    Q_OBJECT

public:
    DrawingArea(QWidget* parent = nullptr, LayerManager* layerManager = nullptr);
    ~DrawingArea();

    void clear();
//    void setPenColor(const QColor& color) { _pen.setColor(color); }
    void wheelEvent(QWheelEvent* event) override;
    QPoint mapToImage(const QPoint& pos);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void draw(QPainter *painter, QPoint pos);
    void eraser(QPainter *painter);


    // TODO penser à créer une classe à part pour le pen
private:
    QImage _image;
    LayerManager* _layerManager;
    QPoint _lastPoint;
    bool _isDrawing;
    QPen _pen;
    QPoint _panOffset = QPoint(0, 0);
    qreal _zoomFactor = 1.0;


};
