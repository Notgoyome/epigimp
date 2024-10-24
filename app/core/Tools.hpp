//
// Created by Guillaume Tran on 14/11/2024.
//

#ifndef UNTITLED2_TOOLS_HPP
#define UNTITLED2_TOOLS_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QPen>

enum Tool {
    PEN,
    ERASER,
    FILL
};

class Tools : public QWidget {
    Q_OBJECT
public:
    Tools(QWidget *parent = nullptr);
    ~Tools() = default;

    void pickPen();
    void pickEraser();
    void pickFill();
    void setPenSize(int size) {
        penSize = size;
        _pen.setWidth(size);
    }

    Tool getCurrentTool() const { return _currentTool; }
    int getPenSize() const { return penSize; }
    void setPenColor(const QColor& color) {
        _pen.setColor(color);
        _penColor = color;
    }
    QPen getPen() const { return _pen; }
private:
    Tool _currentTool;
    int penSize;
    QColor _penColor;

    QPen _pen;

};


#endif //UNTITLED2_TOOLS_HPP
