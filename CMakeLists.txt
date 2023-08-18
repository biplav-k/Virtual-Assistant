cmake_minimum_required(VERSION 3.5)

project(solon)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(SOURCES main.cpp deck/deck.cpp search/search.cpp)

#add_executable(solon ${SOURCES})
add_subdirectory(deck/)
add_subdirectory(search/)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} deck search )

