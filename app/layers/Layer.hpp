//
// Created by Guillaume Tran on 27/09/2024.
//

#ifndef UNTITLED2_LAYER_HPP
#define UNTITLED2_LAYER_HPP

#include <iostream>
#include <QImage>
#include <QPainter>

class Layer : public QObject {
    Q_OBJECT
    public:
        Layer(QObject *parent = nullptr, int width = 800, int height = 600, Qt::GlobalColor color = Qt::transparent);
        ~Layer();

        void clear();
        void hide();
        void show();
    QImage& getImage();
    void setImage(QImage image);
    void setName(std::string name) { _name = name; }
    void setVisible(bool visible) {
        _visible = visible; }
    bool isVisible() { return _visible; }
    std::string getName() { return _name; }
    void setLayerBlendMode(QPainter::CompositionMode mode);
    QPainter::CompositionMode getLayerBlendMode() { return _layerBlendMode; }

    void serialize(QDataStream &stream);
    void deserialize(QDataStream &stream);
    private:
        std::string _name;
        QImage _image;
        bool _visible;
        QPainter::CompositionMode _layerBlendMode;
};
//
//QDataStream &operator<<(QDataStream &out, Layer &layer)
//{
//    layer.serialize(out);
//    return out;
//}
//
//QDataStream &operator>>(QDataStream &in, Layer &layer) {
//    layer.deserialize(in);
//    return in;
//}

#endif //UNTITLED2_LAYER_HPP
