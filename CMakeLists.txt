    cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

    project (3ddafrica_kinect_viewer)
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Qt/Qt5.7.0/5.7/msvc2015_64/lib/cmake/Qt5")
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Qt/Qt5.7.0/5.7/msvc2015_64/lib/cmake/Qt5Core")
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Qt/Qt5.7.0/5.7/msvc2015_64/lib/cmake/Qt5Widgets")
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Qt/Qt5.7.0/5.7/msvc2015_64/lib/cmake/Qt5Gui")
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Qt/Qt5.7.0/5.7/msvc2015_64/lib/cmake/Qt5OpenGL")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/opencv/build/include/opencv2")
    if(CMAKE_CONFIGURATION_TYPES)
        message("Multi-configuration generator")
        set(CMAKE_CONFIGURATION_TYPES "Debug;Release" 
        CACHE STRING "My multi config types" FORCE)
    else()
        message("Single-configuration generator")
    endif() 
    
    find_package (PCL 1.7.2 REQUIRED)


   #### Qt5
   find_package (Qt5 REQUIRED)
find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5OpenGL REQUIRED )

    SET(Kinect_DIR "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409")
    SET(OpenCV_DIR "C:/opencv/build")
    find_package( OpenCV REQUIRED )
    
    include_directories (${PCL_INCLUDE_DIRS} ${Kinect_DIR}/inc)
    link_directories    (${PCL_LIBRARY_DIRS})
    add_definitions     (${PCL_DEFINITIONS})

    find_package (VTK REQUIRED)
    include(${VTK_USE_FILE})

    file(GLOB project_SOURCES *.cpp)
    file(GLOB project_HEADERS *.h)
    file(GLOB project_FORMS *.ui)
    
    set   (VTK_LIBRARIES)

    QT5_WRAP_CPP (project_HEADERS_MOC mainwindow.h)
    QT5_WRAP_UI  (project_FORMS_HEADERS ${project_FORMS})

    ADD_DEFINITIONS (${QT_DEFINITIONS})

    ADD_EXECUTABLE  (3ddafrica_kinect_viewer 
    ${project_SOURCES} 
    ${project_HEADERS}
    ${project_FORMS_HEADERS}
    ${project_HEADERS_MOC})

    TARGET_LINK_LIBRARIES (3ddafrica_kinect_viewer ${PCL_LIBRARIES} ${VTK_LIBRARIES} ${OpenCV_LIBS} ${Kinect_DIR}/Lib/x64/Kinect20.lib)
    qt5_use_modules (3ddafrica_kinect_viewer Widgets)
