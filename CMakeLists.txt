cmake_minimum_required(VERSION 3.16)

project(LanguageSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick LinguistTools)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appLanguageSystem
    src/main.cpp
    src/features/language/LanguageController.cpp
    src/features/language/LanguageController.h
    src/features/language/LanguageEnum.cpp
    src/features/language/LanguageEnum.h
)

qt_add_qml_module(appLanguageSystem
    URI LanguageSystem
    VERSION 1.0
    QML_FILES
        src/Main.qml
        RESOURCES .giattributes
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appLanguageSystem PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appLanguageSystem
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appLanguageSystem
    PRIVATE Qt6::Quick
)

# Add translation support
set(TS_FILES
    translations/app_en.ts
    translations/app_es.ts
    translations/app_fr.ts
)

qt_add_translations(appLanguageSystem TS_FILES ${TS_FILES} RESOURCE_PREFIX "/translations")

include(GNUInstallDirs)
install(TARGETS appLanguageSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
