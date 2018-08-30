cmake_minimum_required (VERSION 3.9.2)
project (LinkedList)
enable_testing()
add_subdirectory(tests)
include(LinkedList.cmake)

#LinkedList Sources
set (LL_SOURCES 
    ${PROJECT_SOURCE_DIR}/sll.c
    ${PROJECT_SOURCE_DIR}/dll.c
    ${PROJECT_SOURCE_DIR}/ll.c
)

#Add the linked list library as static
ADD_LIBRARY( ${LL_LIB} STATIC ${LL_SOURCES} )