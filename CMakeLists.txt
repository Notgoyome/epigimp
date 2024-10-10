cmake_minimum_required(VERSION 3.28)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(untitled2 main.cpp
        app/EpiGimp.cpp
        app/core/MainWindow.hpp
        app/core/MainWindow.cpp
        app/menu_bar/CustomMenuBar.hpp
        app/menu_bar/MenuBar.cpp
        app/layers/Layer.hpp
        app/layers/Layer.cpp
        app/layers/LayerManager.hpp
        app/layers/LayerManager.cpp
        app/core/DrawingArea.hpp
        app/core/DrawingArea.cpp
        app/menu_bar/edit/FileMenu.hpp
        app/menu_bar/edit/FileMenu.cpp)
target_link_libraries(untitled2
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

