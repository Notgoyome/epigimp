//
// Created by Guillaume Tran on 10/10/2024.
//

#ifndef UNTITLED2_FILEMENU_HPP
#define UNTITLED2_FILEMENU_HPP


#include <QMenu>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
class FileMenu : public QMenu
{
    Q_OBJECT
public:

    FileMenu(QWidget *parent = nullptr);
    ~FileMenu() = default;

    void openImage();
    void exportImage();
    void newImage();
};



#endif //UNTITLED2_FILEMENU_HPP
