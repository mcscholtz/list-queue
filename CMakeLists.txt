cmake_minimum_required (VERSION 3.9.2)
project (Queue)
enable_testing()
add_subdirectory(tests)
include(Project.cmake)

#LinkedList Sources
set (Q_SOURCES 
    ${PROJECT_SOURCE_DIR}/queue.c
)

#Add the linked list library as static
ADD_LIBRARY( ${Q_LIB} STATIC ${Q_SOURCES} )