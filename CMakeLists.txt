cmake_minimum_required(VERSION 3.27)
project(SurnameDictionary)

set(CMAKE_CXX_STANDARD 20)

add_executable(SurnameDictionary main.cpp
        UserProcessor.h
        UserProcessor.cpp
        User.h
        User.cpp)

## Исходный файл, который нужно скопировать
#set(INPUT_FILE ${CMAKE_SOURCE_DIR}/input.txt)


# Папка для сборки
set(OUTPUT_DIR ${CMAKE_BINARY_DIR})

## Добавляем кастомный таргет для копирования файла
#add_custom_target(CopyInputFile ALL
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${INPUT_FILE} ${OUTPUT_DIR}/input.txt
#        COMMENT "Обновление файла input.txt в папке сборки, если он изменился"
#)


#add_dependencies(SurnameDictionary CopyInputFile)