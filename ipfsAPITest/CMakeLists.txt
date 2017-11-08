cmake_minimum_required(VERSION 3.4)
project(ipfsAPITest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include/ /usr/include/)
link_directories(/usr/local/lib/ /usr/lib/ /usr/lib/x86_64-linux-gnu/)


#variable that contains third party libs that will be linkt to the project
set(THIRD_PARTY_LIBS "")

#ifps
set(THIRD_PARTY_LIBS "ipfs-api" "curl" "${THIRD_PARTY_LIBS}")

set(SOURCE_FILES
        main.cpp
        )

add_executable(ipfsAPITest ${SOURCE_FILES})
target_link_libraries(ipfsAPITest ${THIRD_PARTY_LIBS})
