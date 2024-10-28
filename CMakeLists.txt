cmake_minimum_required(VERSION 3.29)
project(OOPQt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        Quick
        REQUIRED)

qt5_add_resources(QT_RESOURCES
        src/qml.qrc
)

add_executable(OOPQt
        src/main.cpp

        ${QT_RESOURCES}

)

target_link_libraries(OOPQt
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::Quick
)

