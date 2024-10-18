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
        REQUIRED)

add_executable(OOPQt src/main.cpp
        src/Entities/Driver.h
        src/Entities/Mechanic.h
        src/Entities/Person.h
        src/Entities/TeamManager.h
        src/Models/DriverModel.h
        src/Models/IModel.h
        src/Models/MechanicModel.h
        src/Entities/Track.h
        src/Models/TrackModel.h
        src/Entities/Race.h
        src/Models/RaceModel.h
        src/MainWindow.h
        src/Models/DriverModel.cpp
        src/Controllers/IController.h
        src/Views/DriversListView.h
        src/Views/CustomTableWidget.h
        src/Views/DriverCartView.h
        src/Views/Modals/DriverModal.h

)
target_link_libraries(OOPQt
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
)

