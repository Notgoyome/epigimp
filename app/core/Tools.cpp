//
// Created by Guillaume Tran on 14/11/2024.
//

#include "Tools.hpp"

Tools::Tools(QWidget *parent) : QWidget(parent)
{

    _pen = QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* button = new QPushButton("Pen", this);
    QPushButton* button2 = new QPushButton("Eraser", this);
    QPushButton* button3 = new QPushButton("Fill", this);

    QLabel* sizeLabel = new QLabel("Size:", this);
    QSlider* sizeSlider = new QSlider(Qt::Horizontal, this);
    QSpinBox* sizeSpinBox = new QSpinBox(this);

    QHBoxLayout* sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(sizeLabel);
    sizeLayout->addWidget(sizeSlider);
    sizeLayout->addWidget(sizeSpinBox);

    layout->addLayout(sizeLayout);
    layout->addWidget(button);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addStretch();

    connect(sizeSlider, &QSlider::valueChanged, sizeSpinBox, &QSpinBox::setValue);
    connect(sizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), sizeSlider, &QSlider::setValue);
    connect(sizeSlider, &QSlider::valueChanged, this, &Tools::setPenSize);

    connect(button, &QPushButton::clicked, this, &Tools::pickPen);
    connect(button2, &QPushButton::clicked, this, &Tools::pickEraser);
    connect(button3, &QPushButton::clicked, this, &Tools::pickFill);

    setLayout(layout);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(43,45,48));
    setAutoFillBackground(true);
    setPalette(pal);
}

void Tools::pickPen()
{
    _pen.setColor(_penColor);
    _currentTool = PEN;
}

void Tools::pickEraser()
{
    _pen.setColor(QColor(0, 0, 0, 0));
    _currentTool = ERASER;
}

void Tools::pickFill()
{
    _currentTool = FILL;
}