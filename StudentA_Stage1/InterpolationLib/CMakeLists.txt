add_library(InterpolationStatic STATIC
    src/Interpolation.cpp
)

target_include_directories(InterpolationStatic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(InterpolationStatic PUBLIC cxx_std_20)