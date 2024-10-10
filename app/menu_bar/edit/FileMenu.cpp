//
// Created by Guillaume Tran on 10/10/2024.
//

#include "FileMenu.hpp"
#include <QAction>
#include "../../core/MainWindow.hpp"
#include "../../layers/Layer.hpp"
#include "../../layers/LayerManager.hpp"
FileMenu::FileMenu(QWidget *parent) : QMenu("File", parent)
{
    QAction* newAction = new QAction("New", this);
    addAction(newAction);

    QAction* openAction = new QAction("Open", this);
    connect(openAction, &QAction::triggered, this, &FileMenu::openImage);
    addAction(openAction);

    QAction* saveAction = new QAction("Save", this);
    addAction(saveAction);
}

void FileMenu::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir une image", "", "Images (*.png *.jpg *.jpeg)");
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        if (image.isNull())
        {
            QMessageBox::warning(this, "Erreur", "Impossible de charger l'image.");
            return;
        }

        std::shared_ptr<MainWindow> mainWindow = MainWindow::getInstance();
        LayerManager* layerManager = mainWindow->getLayerManager();
        if (mainWindow)
        {
            Layer* newLayer = new Layer(layerManager);
            newLayer->setImage(image);
            std::cout << "Image loaded" << std::endl;
            layerManager->addLayer(newLayer);
            newLayer->show();
        }
    }
}