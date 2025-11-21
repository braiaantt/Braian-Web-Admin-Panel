cmake_minimum_required(VERSION 3.16)

project(web_admin_panel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(web_admin_panel
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        #------ Pages ------
        portfoliopage.h portfoliopage.cpp portfoliopage.ui
        loginpage.h loginpage.cpp loginpage.ui

        #------ Custome Widgets ------
        custome_widgets/portfolioproject.h custome_widgets/portfolioproject.cpp custome_widgets/portfolioproject.ui

        #------ Resources ------
        images.qrc

        #------ Constants ------
        consts/page_names.h
        custome_widgets/technology.h custome_widgets/technology.cpp custome_widgets/technology.ui

        #------ Utils ------
        utils/utils.h utils/utils.cpp

        #------ Dialos ------
        dialogs/createtechnology.h dialogs/createtechnology.cpp dialogs/createtechnology.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET web_admin_panel APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(web_admin_panel SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(web_admin_panel
            ${PROJECT_SOURCES}
        )
    endif()
endif()
include_directories(
    consts
    custome_widgets
    utils
    dialogs
)
target_link_libraries(web_admin_panel PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.web_admin_panel)
endif()
set_target_properties(web_admin_panel PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS web_admin_panel
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(web_admin_panel)
endif()
