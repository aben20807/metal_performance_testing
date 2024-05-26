cmake_minimum_required (VERSION 3.20)
# https://stackoverflow.com/a/70811546
project (metal_performance_testing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -DACCELERATE_NEW_LAPACK -O3 -ffast-math")

find_library(APPLE_FWK_FOUNDATION Foundation REQUIRED)
find_library(APPLE_FWK_QUARTZ_CORE QuartzCore REQUIRED)
find_library(APPLE_FWK_METAL Metal REQUIRED)
find_library(APPLE_FWK_ACCELERATE Accelerate REQUIRED)


add_library( LOAD_SEP INTERFACE )
set( LOAD_SEP_OPTS "" )
target_compile_options( LOAD_SEP BEFORE INTERFACE ${LOAD_SEP_OPTS} )
target_compile_definitions( LOAD_SEP INTERFACE -DLOAD_SEP )
target_link_options( LOAD_SEP BEFORE INTERFACE  ${LOAD_SEP_OPTS} )

add_executable(metal_performance_testing_sep
    Assertions.cpp
    Matrix.cpp
    MatrixMultiplier.cpp
    Utilities.cpp
    main.cpp
)

target_include_directories(metal_performance_testing_sep
  SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/metal-cpp
)

target_link_libraries(metal_performance_testing_sep
  ${APPLE_FWK_FOUNDATION}
  ${APPLE_FWK_QUARTZ_CORE}
  ${APPLE_FWK_METAL}
  ${APPLE_FWK_ACCELERATE}
  LOAD_SEP
)


add_library( LOAD_BATCH INTERFACE )
set( LOAD_BATCH_OPTS "" )
target_compile_options( LOAD_BATCH BEFORE INTERFACE ${LOAD_BATCH_OPTS} )
target_compile_definitions( LOAD_BATCH INTERFACE -DLOAD_BATCH )
target_link_options( LOAD_BATCH BEFORE INTERFACE  ${LOAD_BATCH_OPTS} )

add_executable(metal_performance_testing_batch
    Assertions.cpp
    Matrix.cpp
    MatrixMultiplier.cpp
    Utilities.cpp
    main.cpp
)

target_include_directories(metal_performance_testing_batch
  SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/metal-cpp
)

target_link_libraries(metal_performance_testing_batch
  ${APPLE_FWK_FOUNDATION}
  ${APPLE_FWK_QUARTZ_CORE}
  ${APPLE_FWK_METAL}
  ${APPLE_FWK_ACCELERATE}
  LOAD_BATCH
)
