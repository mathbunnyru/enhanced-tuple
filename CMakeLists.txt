cmake_minimum_required(VERSION 3.2)

project(mamba)

add_executable(main_tuple main.cpp)
target_compile_features(main_tuple PUBLIC cxx_std_20)

option(ENABLE_ASAN "Enable Address-Sanitizer" OFF)
if(ENABLE_ASAN)
    message("Enabling Asan")
    add_compile_options(-fno-omit-frame-pointer  -fsanitize=address)
    add_link_options(-fno-omit-frame-pointer  -fsanitize=address)
endif()

option(ENABLE_UBSAN "Enable UndefinedBehavior-Sanitizer" OFF)
if(ENABLE_UBSAN)
    message("Enabling UBsan")
    add_compile_options(-fno-omit-frame-pointer  -fsanitize=undefined)
    add_link_options(-fno-omit-frame-pointer  -fsanitize=undefined)
endif()
