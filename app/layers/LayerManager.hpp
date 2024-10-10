#ifndef LAYERMANAGER_HPP
#define LAYERMANAGER_HPP

#include <QObject>

#include <QVector>
#include "Layer.hpp"

class LayerManager : public QObject {
Q_OBJECT

public:
    explicit LayerManager(QObject* parent = nullptr);
    ~LayerManager();

    void addLayer(Layer *layer);
    void addLayer();
    void removeLayer(int index);
    Layer *getLayer(int index) const;
    int layerCount() const;
    Layer *getCurrentLayer() const;
private:
    QVector<Layer*> _layers;
    int _currentLayer;
    int width;
    int height;
    QObject* _parent;
};

#endif // LAYERMANAGER_HPP
