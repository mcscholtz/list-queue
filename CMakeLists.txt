cmake_minimum_required (VERSION 3.10.2)
project (LinkedList)

#compiler warnings
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()


#where to move output files
set (PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set (LL_SOURCES 
    ${PROJECT_SOURCE_DIR}/sll.c
)

set (TESTLIB_SOURCE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/cutest)
set (TESTLIB_SOURCES 
    ${TESTLIB_SOURCE_DIR}/cutest.c
)

set (TEST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/tests)
set (TEST_SOURCES 
    ${TEST_SOURCE_DIR}/tests.c
    ${TEST_SOURCE_DIR}/ll_suite.c
)

# These are the corresponding output paths
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set (LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

#Add the cutest library as static
SET( TEST_LIB cutest )
ADD_LIBRARY( ${TEST_LIB} STATIC ${TESTLIB_SOURCES} )

#Add the linked list library as static
SET( LL_LIB ll )
ADD_LIBRARY( ${LL_LIB} STATIC ${LL_SOURCES} )

#Create the test binary
SET( TEST_EXE tests )
ADD_EXECUTABLE( ${TEST_EXE} ${TEST_SOURCES} ) 

#Add headers from the cutest and from the ll libraries
TARGET_INCLUDE_DIRECTORIES(${TEST_EXE} PRIVATE 
    ${TESTLIB_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
)

#Link to the static libraries built above
TARGET_LINK_LIBRARIES( ${TEST_EXE} ${LL_LIB} ${TEST_LIB} )