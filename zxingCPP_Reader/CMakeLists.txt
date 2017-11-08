cmake_minimum_required(VERSION 3.4)
project(zxingCPP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option (ENABLE_TESTS
        "Enable the tests suite" ON)

include_directories(/usr/local/include/ /usr/include/)
link_directories(/usr/local/lib/ /usr/lib/ /usr/lib/x86_64-linux-gnu/)

#variable that contains third party libs that will be linkt to the project
set(THIRD_PARTY_LIBS "")

#zxing
set(THIRD_PARTY_LIBS "zxing" "${THIRD_PARTY_LIBS}")

#openCV
FIND_PACKAGE(OpenCV COMPONENTS core highgui imgproc REQUIRED)
set(THIRD_PARTY_LIBS ${OpenCV_LIBS} ${THIRD_PARTY_LIBS})

set(SOURCE_FILES
        main.cpp
        )


add_executable(zxingCpp ${SOURCE_FILES})

target_link_libraries(zxingCpp ${THIRD_PARTY_LIBS})
