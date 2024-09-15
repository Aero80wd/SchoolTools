cmake_minimum_required(VERSION 3.5)

project(SchoolTools VERSION 3.5 LANGUAGES CXX)

file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "ui")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/msvc2019_64/lib/cmake/")
set(QRC_SOURCE_FILES res.qrc)
set(CMAKE_BUILD_PARALLEL_LEVEL 16)
find_package(Qt6 COMPONENTS Core Sql Network Gui Widgets WebEngineWidgets REQUIRED)
qt6_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

SOURCE_GROUP("Resource Files" FILES ${QRC_SOURCE_FILES})
set(PROJECT_SOURCES
        cpp/animationlabelup.cpp
        cpp/clicklabel.cpp
        cpp/getstartwidget.cpp
        main.cpp
        cpp/maintablewidget.cpp
        cpp/mainwindow.cpp
        cpp/rolling_label.cpp
        cpp/tableeditwidget.cpp
        cpp/toolbox.cpp
        cpp/twtodowidget.cpp
        cpp/yiyandialog.cpp
        headers/API.h
        headers/animationlabelup.h
        headers/clicklabel.h
        headers/getstartwidget.h
        headers/maintablewidget.h
        headers/mainwindow.h
        headers/rolling_label.h
        headers/tableeditwidget.h
        headers/toolbox.h
        headers/twtodowidget.h
        headers/yiyandialog.h
        ui/getstartwidget.ui
        ui/maintablewidget.ui
        ui/mainwindow.ui
        ui/tableeditwidget.ui
        ui/toolbox.ui
        ui/twtodowidget.ui
        ui/yiyandialog.ui
        cpp/AppLog.cpp
        headers/AppLog.h
        cpp/daytimerwidget.cpp
        headers/daytimerwidget.h
        ui/daytimerwidget.ui
)
set(useWin32 TRUE)
qt_add_executable(SchoolTools WIN32
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${QRC_FILES}
        icon.rc
)
target_link_libraries(SchoolTools PRIVATE Qt6::Widgets Qt6::Core Qt6::Sql Qt6::Network Qt6::WebEngineWidgets)
include_directories(${Qt6Gui_PRIVATE_INCLUDE_DIRS})
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.Aero8m.SchoolTools)
set_target_properties(SchoolTools PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SchoolTools
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SchoolTools)
endif()
