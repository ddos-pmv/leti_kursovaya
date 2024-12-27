cmake_minimum_required(VERSION 3.2)

project(leti_kursovaya VERSION 1.0 LANGUAGES CXX)

find_package(Qt5 COMPONENTS
        Core
        Widgets
        Sql
        Test
        Pdf
        REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(ENTITIES
        Entities/Driver.h
        Entities/Team.h
        Entities/Team.cpp
        Entities/Driver.cpp
        Entities/Race.cpp
        Entities/Race.h
)

set(EXCEPTIONS
    Exceptions/CustomExceptions.h
)

set(VIEW
        View/MainWindow.cpp
        View/MainWindow.h
        View/List.cpp
        View/List.h
        View/MainThemeVars.h
        View/StackedWidget.h
        View/DriversView/DriversView.h
        View/DriversView/DriversDelegate.h
        View/DriversView/DriversCard.h
        View/DriversView/DriversView.cpp
        View/DriversView/AddDriversDialog.h
        View/TeamView/TeamsView.cpp
        View/TeamView/TeamsCard.h
        View/TeamView/AddTeamsDialog.h
        View/TeamView/TeamsView.cpp
        View/RacesView/RaceView.cpp
        View/RacesView/RaceView.h
        Models/RacesModel.h
        View/RacesView/RacesDelegate.h
        View/RacesView/AddRaceDialog.h
        View/RacesView/RacesCard.h
)

set(MODELS
        Models/DriversModel.h
        Models/BaseListModel.h
        Models/TeamsModel.h
)

set(CONTROLLERS
        Controllers/DriverController.cpp
        Controllers/DriverController.h
        Controllers/TeamController.cpp
        Controllers/TeamController.h
        View/TeamView/TeamsView.h
        Controllers/RaceController.cpp
        Controllers/RaceController.h
)

set(DB
        src/database/DB.h
)

add_executable(leti_kursovaya
        main.cpp
        resources.qrc
        ${VIEW}
        ${CONTROLLERS}
        ${MODELS}
        ${EXCEPTIONS}
        ${ENTITIES}
        UpdateManager.cpp
        UpdateManager.h
)

target_link_libraries(leti_kursovaya PRIVATE
        Qt5::Widgets
        Qt5::Core
        Qt5::Sql
        Qt5::Pdf
)

# Тесты
set(TEST_SOURCES
        Tests/test_models.cpp
)
add_executable(tests ${TEST_SOURCES}
        ${MODELS}
        ${CONTROLLERS}
        ${MODELS}
        ${EXCEPTIONS}
        ${ENTITIES})
target_link_libraries(tests Qt5::Core Qt5::Test Qt5::Sql)
#add_custom_target(run_tests COMMAND DriversAppTests)