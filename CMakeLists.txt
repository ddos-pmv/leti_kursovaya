cmake_minimum_required(VERSION 3.16)

project(OOP VERSION 1.0 LANGUAGES CXX)

find_package(Qt6 6.2 COMPONENTS Quick Gui Core Widgets Sql Pdf REQUIRED)

qt_standard_project_setup()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_executable(OOP
        src/main.cpp
        src/Entities/Driver.h
        src/DriverListModel.cpp
        src/DriverListModel.h
)

qt_add_qml_module(OOP
        URI hello
        VERSION 1.0
        QML_FILES
        src/qml/main.qml
        src/qml/TextWhite.qml
        src/qml/DriverTableDelegate.qml

        RESOURCES
        src/public/bg.png
)

target_link_libraries(OOP PRIVATE Qt6::Gui Qt6::Quick Qt6::Core Qt6::Widgets Qt::Pdf)
