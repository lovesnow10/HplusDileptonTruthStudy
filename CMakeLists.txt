cmake_minimum_required(VERSION 3.3)

project(HplusDileptonTruthStudy)


set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)

find_package(ROOT)
include_directories(${ROOT_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_CXX_FLAGS ${ROOT_CXX_FLAGS})

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
aux_source_directory(${PROJECT_SOURCE_DIR}/src LIBSRC)
#foreach(FULL_LIB_NAME ${LIBSRC})
#    get_filename_component(LIB_NAME ${FULL_LIB_NAME} NAME_WE)
#    list(APPEND OWNLIBS ${LIB_NAME})
#    add_library(${LIB_NAME} SHARED ${FULL_LIB_NAME})
#    target_link_libraries(${LIB_NAME} ${ROOT_LIBRARIES})
#endforeach()
add_library("TruthStudy" SHARED ${LIBSRC})
target_link_libraries("TruthStudy" ${ROOT_LIBRARIES})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
aux_source_directory(${PROJECT_SOURCE_DIR}/utils MAINSRC)
foreach(FULL_MAIN_NAME ${MAINSRC})
    get_filename_component(MAIN_NAME ${FULL_MAIN_NAME} NAME_WE)
    add_executable(${MAIN_NAME} ${FULL_MAIN_NAME})
#    target_link_libraries(${MAIN_NAME} ${ROOT_LIBRARIES} ${OWNLIBS})
    target_link_libraries(${MAIN_NAME} ${ROOT_LIBRARIES} "TruthStudy")
endforeach()
