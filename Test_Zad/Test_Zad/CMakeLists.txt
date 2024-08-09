# CMakeList.txt: проект CMake для Test_Zad; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Test_Zad "Test_Zad.cpp" "Test_Zad.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Test_Zad PROPERTY CXX_STANDARD 20)
endif()

project (Test_Zad)
# Указываем CMake, где искать Boost (относительно корня проекта)
set(BOOST_ROOT "C:/include")
set(BOOST_INCLUDEDIR "C:/include/boost-1_85/")
set(Boost_USE_STATIC_RUNTIME ON)

# Находим Boost (указывая нужный компонент)
find_package(boost REQUIRED COMPONENTS atomic)

# Проверяем, что Boost найден (необязательно)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost.Thread не найден! Проверьте BOOST_ROOT.")
endif()
if(Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    message(STATUS "Found BOOST ${Boost_VERSION_STRING}")
else()
    message(STATUS "WEBSOCKET BOOST Not Found")
endif()
# Добавляем пути include
#include_directories(${Boost_INCLUDE_DIR})



# Линкуем Boost.Thread к исполняемому файлу
#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
