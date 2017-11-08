cmake_minimum_required(VERSION 3.4)
project(pugiXML_Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include/ /usr/include/)
link_directories(/usr/local/lib/ /usr/lib/ /usr/lib/x86_64-linux-gnu/)


#variable that contains third party libs that will be linkt to the project
set(THIRD_PARTY_LIBS "")

#openssl
set(THIRD_PARTY_LIBS "pugixml" "${THIRD_PARTY_LIBS}")

set(SOURCE_FILES
        main.cpp
        )

add_executable(pugiXML_Test ${SOURCE_FILES})
target_link_libraries(pugiXML_Test ${THIRD_PARTY_LIBS})
