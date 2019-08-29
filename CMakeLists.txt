cmake_minimum_required(VERSION 3.10)
project(SCC)

set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(CMAKE_CXX_FLAGS "-fopenmp")
find_package(Boost)
if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS} snap/glib-adv snap/glib-core snap/snap-adv snap/snap-core snap/snap-exp)
        file(GLOB glob "*.h" "*.cpp")
        add_executable(SCC ${glob} snap/snap-core/Snap.o)
        link_directories(snap/glib-adv snap/glib-core snap/snap-adv snap/snap-core snap/snap-exp)
        target_link_libraries(SCC ${Boost_LIBRARIES})
endif()

