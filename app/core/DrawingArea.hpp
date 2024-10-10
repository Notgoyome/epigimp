#pragma once

#include <QWidget>
#include <QImage>
#include <QPainter>
#include "../layers/LayerManager.hpp"
#include <QMouseEvent>
#include <QPaintEvent>

class DrawingArea : public QWidget {
    Q_OBJECT

public:
    DrawingArea(QWidget* parent = nullptr, LayerManager* layerManager = nullptr);
    ~DrawingArea();

    void clear();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
private:
    QImage image;
    LayerManager* _layerManager;
    QPoint lastPoint;
    bool is_drawing;
};
