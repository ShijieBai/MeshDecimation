cmake_minimum_required(VERSION 3.16)

set(proj_name "MeshDecimation")
project(${proj_name}
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

if(MSVC)
    add_definitions(/D_USE_MATH_DEFINES)  # for Pi
endif ()

set(Eigen3_DIR D:/soft/eigen-prefix/share/eigen3/cmake)
set(CGAL_DIR D:/soft/cgal-6.1.1/lib/cmake/CGAL)
#set(Boost_DIR D:/soft/boost-1.90/lib/cmake/Boost-1.90.0)
set(BOOST_ROOT D:/soft/boost-1.90)
set(OpenMesh_DIR D:/soft/OpenMesh/share/OpenMesh/cmake)
set(pmp_DIR D:/soft/pmp/lib/cmake/pmp)

add_library(Third_library_interface INTERFACE)
# Use Eigen
find_package(Eigen3 REQUIRED NO_MODULE)
target_link_libraries(Third_library_interface INTERFACE Eigen3::Eigen)

# Use Boost as CGAL dependencies
# find_package(Boost REQUIRED)
# target_link_libraries(Third_library_interface INTERFACE Boost::boost)

# Use CGAL, internal it find_package(Boost) 
find_package(CGAL REQUIRED NO_MODULE)
target_link_libraries(Third_library_interface INTERFACE CGAL::CGAL)

add_subdirectory(src/CGAL)
target_link_libraries(CGAL_test PUBLIC Third_library_interface)

# Use OpenMesh
find_package(OpenMesh REQUIRED NO_MODULE)
target_link_libraries(Third_library_interface INTERFACE OpenMeshCore OpenMeshTools )

add_subdirectory(src/OpenMesh)
target_link_libraries(OpenMesh_test PUBLIC Third_library_interface)

# Use OpenMP as pmp dependencies
find_package(OpenMP REQUIRED)

# Use pmp
find_package(pmp REQUIRED NO_MODULE)
target_link_libraries(Third_library_interface INTERFACE pmp)

add_subdirectory(src/pmp)
target_link_libraries(pmp_test PUBLIC Third_library_interface)

add_executable(MeshDecimation main.cpp)
target_link_libraries(MeshDecimation PUBLIC CGAL_test OpenMesh_test)