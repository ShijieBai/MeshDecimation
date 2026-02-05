file(GLOB src_list *.cpp include/*.h)

set(include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(OpenMesh_test ${src_list})

target_include_directories(OpenMesh_test PUBLIC ${include_dir})