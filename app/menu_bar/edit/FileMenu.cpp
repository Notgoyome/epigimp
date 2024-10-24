//
// Created by Guillaume Tran on 10/10/2024.
//

#include "FileMenu.hpp"
#include <QAction>
#include <QPainter>
#include "../../core/MainWindow.hpp"
#include "../../layers/Layer.hpp"
#include "../../layers/LayerManager.hpp"
FileMenu::FileMenu(QWidget *parent) : QMenu("File", parent)
{
    QAction* newAction = new QAction("New", this);
    connect(newAction, &QAction::triggered, this, &FileMenu::newImage);
    addAction(newAction);

    QAction* openAction = new QAction("Open", this);
    connect(openAction, &QAction::triggered, this, &FileMenu::openImage);
    addAction(openAction);

    QAction* saveAction = new QAction("Save", this);
    addAction(saveAction);

    QAction* exportAction = new QAction("Export", this);
    connect(exportAction, &QAction::triggered, this, &FileMenu::exportImage);
    addAction(exportAction);
}

void FileMenu::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "open an image", "", "Images (*.png *.jpg *.jpeg)");
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        if (image.isNull())
        {
            QMessageBox::warning(this, "error", "couldn't load an image");
            return;
        }

        std::shared_ptr<MainWindow> mainWindow = MainWindow::getInstance();
        LayerManager* layerManager = mainWindow->getLayerManager();
        if (mainWindow)
        {
            Layer* newLayer = new Layer(layerManager);
            newLayer->setImage(image);
            layerManager->addLayer(newLayer);
            newLayer->show();
        }
    }
}
void FileMenu::exportImage() {
    QString filePath = QFileDialog::getSaveFileName(this, "Export", "", "Images (*.png)");
    if (!filePath.isEmpty())
    {
        LayerManager* layerManager = MainWindow::getInstance()->getLayerManager();
        QImage combinedImage(layerManager->getWidth(), layerManager->getHeight(), QImage::QImage::Format_ARGB32);
        std::cout << layerManager->getWidth() << " " << layerManager->getHeight() << std::endl;
        QVector<Layer*> _layers = layerManager->getLayers();
        combinedImage.fill(Qt::transparent);
        QPainter painter(&combinedImage);
        for (int i = 0; i < _layers.size(); i++) {
            QImage layerImage = _layers[i]->getImage();
            if (layerImage.isNull()) {
                QMessageBox::warning(this, "error", "layer image is null");
                return;
            }
            painter.drawImage(0, 0, layerImage);
        }
        if (combinedImage.isNull()) {
            QMessageBox::warning(this, "error", "combined image is null");
            return;
        }
        bool result = combinedImage.save(filePath);
        if (!result) {
            QMessageBox::warning(this, "error", "couldn't save an image");
            return;
        }
    }
}

#include <QSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>

void FileMenu::newImage()
{
    QDialog dialog;
    dialog.setWindowTitle("New Image");
    QSpinBox *widthBox = new QSpinBox(&dialog);
    QSpinBox *heightBox = new QSpinBox(&dialog);

    widthBox->setMinimum(1);
    heightBox->setMinimum(1);
    widthBox->setMaximum(10000);
    heightBox->setMaximum(10000);
    widthBox->setValue(100);
    heightBox->setValue(100);

    QFormLayout *layout = new QFormLayout;
    layout->addRow("Width:", widthBox);
    layout->addRow("Height:", heightBox);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
            QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);
    dialog.setLayout(layout);

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);


    if (dialog.exec() == QDialog::Accepted) {
        std::cout << "accepted" << std::endl;
        std::shared_ptr<MainWindow> mainWindow = MainWindow::getInstance();
        LayerManager* layerManager = mainWindow->getLayerManager();
        if (mainWindow) {
            std::cout << "main" << std::endl;
            layerManager->set_size(widthBox->value(), heightBox->value());
            layerManager->reset();
        }
    }
}