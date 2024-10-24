#ifndef LAYERMANAGER_HPP
#define LAYERMANAGER_HPP

#include <QObject>

#include <QVector>
#import <QPainter>
#include "Layer.hpp"

class LayerManager : public QObject {
Q_OBJECT

public:
    explicit LayerManager(QObject* parent = nullptr);
    ~LayerManager();

    void removeLayer(int index);
    void set_size(int width, int height);
    void reset();
    Layer *getLayer(int index) const;
    int layerCount() const;
    Layer *getCurrentLayer() const;
    void setCurrentLayer(int index) { _currentLayer = index; }
    int getWidth() { return _width; }
    int getHeight() { return _height; }
    QVector<Layer*> getLayers() { return _layers; }
    QPainter::CompositionMode getLayerBlendMode(int index) { return _layers[index]->getLayerBlendMode(); }

public slots:
    void addLayer(Layer *layer);
    void addLayer(Qt::GlobalColor color = Qt::transparent);
    void setVisible(int index, bool visible);
    void setLayerBlendMode(int index, QPainter::CompositionMode mode);
    void saveHistory();
    void undo();
    signals:
    void layersChanged();


private:
    QVector<Layer*> _layers;
    QVector<QVector<Layer*>> _history;
    int maxHistory = 10;
    int _currentLayer;
    int _width;
    int _height;
    QObject* _parent;
};

#endif // LAYERMANAGER_HPP
