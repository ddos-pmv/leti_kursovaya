cmake_minimum_required(VERSION 3.16)

project(OOP VERSION 1.0 LANGUAGES CXX)

find_package(Qt6 6.2 COMPONENTS Quick Gui Core Widgets Sql Pdf REQUIRED)

qt_standard_project_setup()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENTITIES
        src/Entities/Driver.h
        src/Entities/Mechanic.h
        src/Entities/Person.h
        src/Entities/Race.h
        src/Entities/TeamManager.h
        src/Entities/Track.h
)

set(MODELS
    src/Models/DriverModel.cpp
    src/Models/DriverModel.h
    src/Models/IModel.h
    src/Models/MechanicModel.h
    src/Models/RaceModel.h
    src/Models/TrackModel.h
)
set(QML_MODELS
        src/DriverListModel.cpp
        src/DriverListModel.h
)
set(CONTROLLERS
        src/Controllers/IController.h
        src/Controllers/DriverController.cpp
        src/Controllers/DriverController.h
)

set(DB
        src/database/DB.h
)
qt_add_executable(OOP
        src/main.cpp

        ${QML_MODELS}
        ${ENTITIES}
        ${CONTROLLERS}
        ${MODELS}
        ${DB}

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

target_link_libraries(OOP PRIVATE Qt6::Gui Qt6::Quick Qt6::Core Qt6::Widgets Qt6::Sql Qt::Pdf)
