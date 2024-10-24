//
// Created by Guillaume Tran on 24/10/2024.
//

#ifndef UNTITLED2_LAYERLIST_HPP
#define UNTITLED2_LAYERLIST_HPP

#include <QListWidget>
#include <QVector>
#include <memory>
#include "../layers/LayerManager.hpp"
#include <QHBoxLayout>
#include <QLabel>

class LayerList : public QListWidget {
Q_OBJECT
public:
    explicit LayerList(QWidget *parent = nullptr);
    void init(LayerManager* layerManager);
    QWidget* createLayerItemWidget(const QString& layerName);
public slots:
    void updateLayerList();
    void onLayerSelected(QListWidgetItem* current);
private:
    LayerManager* _layerManager;

};


#endif //UNTITLED2_LAYERLIST_HPP
