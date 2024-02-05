cmake_minimum_required(VERSION 3.15)
project(TAURI_INVICTUS VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(JUCE)
add_subdirectory(melatonin_perfetto)

add_subdirectory(Utilities)

add_subdirectory(Projects)
