cmake_minimum_required (VERSION 3.9.2)
project (ProjectName)
enable_testing()
add_subdirectory(tests)
include(Project.cmake)

#Project Sources
set (PROJECT_SOURCES 
    ${PROJECT_SOURCE_DIR}/hp.c
)

#Add the library as static
ADD_LIBRARY( ${PROJECT_LIB} STATIC ${PROJECT_SOURCES} )
TARGET_LINK_LIBRARIES(${PROJECT_LIB} m)
