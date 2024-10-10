//
// Created by Guillaume Tran on 27/09/2024.
//

#ifndef UNTITLED2_LAYER_HPP
#define UNTITLED2_LAYER_HPP

#include <iostream>
#include <QImage>

class Layer : public QObject {
    Q_OBJECT
    public:
        Layer(QObject *parent = nullptr);
        ~Layer();

        void clear();
        void hide();
        void show();
    QImage& getImage();
    void setImage(QImage image);

    private:
        QImage _image;
        bool _visible;
};


#endif //UNTITLED2_LAYER_HPP
