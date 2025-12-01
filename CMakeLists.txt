cmake_minimum_required(VERSION 3.16)

project(web_admin_panel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "D:/Braian/Desarrollo/LocalLibs/BasicRequests")
list(APPEND CMAKE_PREFIX_PATH "D:/Braian/Desarrollo/LocalLibs/CommonUtils")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(BasicRequests REQUIRED)
find_package(CommonUtils REQUIRED)

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

        #------ Core ------
        core/configmanager.h core/configmanager.cpp

        #------ Constants ------
        consts/page_names.h

        #------ Models ------
        models/portfolio.h models/portfolio.cpp
        models/project.h models/project.cpp
        models/technology.h models/technology.cpp

        #------ Network ------
        network/apiclient.h network/apiclient.cpp

        #------ Pages ------
        pages/portfolio_page/portfoliopage.h pages/portfolio_page/portfoliopage.cpp pages/portfolio_page/portfoliopage.ui
        pages/login_page/loginpage.h pages/login_page/loginpage.cpp pages/login_page/loginpage.ui
        pages/project_page/projectpage.h pages/project_page/projectpage.cpp pages/project_page/projectpage.ui

        #------ Custome Widgets ------
        pages/portfolio_page/custome_widgets/portfolioproject.h pages/portfolio_page/custome_widgets/portfolioproject.cpp pages/portfolio_page/custome_widgets/portfolioproject.ui
        pages/portfolio_page/custome_widgets/technologywidget.h pages/portfolio_page/custome_widgets/technologywidget.cpp pages/portfolio_page/custome_widgets/technologywidget.ui
        pages/portfolio_page/custome_widgets/technologiesview.h pages/portfolio_page/custome_widgets/technologiesview.cpp

        #------ Resources ------
        images.qrc

        #------ Dialogs ------
        pages/portfolio_page/dialogs/createtechnology.h pages/portfolio_page/dialogs/createtechnology.cpp pages/portfolio_page/dialogs/createtechnology.ui
        pages/portfolio_page/dialogs/createproject.h pages/portfolio_page/dialogs/createproject.cpp pages/portfolio_page/dialogs/createproject.ui
        pages/portfolio_page/dialogs/technologyhandler.h pages/portfolio_page/dialogs/technologyhandler.cpp pages/portfolio_page/dialogs/technologyhandler.ui
        pages/portfolio_page/dialogs/technologyrelation.h pages/portfolio_page/dialogs/technologyrelation.cpp pages/portfolio_page/dialogs/technologyrelation.ui
        #------ Services ------
        services/authservice.h services/authservice.cpp
        services/portfolioservice.h services/portfolioservice.cpp
        services/technologyservice.h services/technologyservice.cpp
        services/entitytechservice.h services/entitytechservice.cpp
        services/projectservice.h services/projectservice.cpp

        #------ Utils ------
        utils/utils.h utils/utils.cpp
        utils/networkutils.h utils/networkutils.cpp
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
    core
    models
    network

    pages/login_page
    pages/portfolio_page
    pages/project_page

    pages/portfolio_page/custome_widgets
    pages/portfolio_page/dialogs

    services
    utils
)
target_link_libraries(web_admin_panel PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(web_admin_panel PRIVATE BasicRequests::BasicRequests)
target_link_libraries(web_admin_panel PRIVATE CommonUtils::CommonUtils)
target_link_libraries(web_admin_panel PRIVATE Qt6::Core)

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
