cmake_minimum_required(VERSION 3.16)

project(MReader VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Resource/resource.qrc)
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/app.rc")

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(VTK 9.0 )

qt_add_executable(appMReader
    main.cpp
    ${RESOURCE_FILES}
    ${APP_ICON_RESOURCE_WINDOWS}
)

qt_add_qml_module(appMReader
    URI MReader
    VERSION 1.0
    QML_FILES main.qml 
)

target_compile_definitions(appMReader
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appMReader
    PRIVATE Qt6::Quick
    ${VTK_LIBRARIES})
