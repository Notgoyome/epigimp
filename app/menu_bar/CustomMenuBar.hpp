//
// Created by Guillaume Tran on 27/09/2024.
//

#ifndef UNTITLED2_CUSTOMMENUBAR_HPP
#define UNTITLED2_CUSTOMMENUBAR_HPP

#include <QMenuBar>

class FileMenu;

class CustomMenuBar : public QMenuBar
{
    Q_OBJECT

public:
    CustomMenuBar(QWidget* parent = nullptr);
    ~CustomMenuBar();

private:
    QMenu* _fileMenu;
    QMenu* _editMenu;
    QMenu* _viewMenu;
    QMenu* _helpMenu;
};


#endif //UNTITLED2_CUSTOMMENUBAR_HPP
