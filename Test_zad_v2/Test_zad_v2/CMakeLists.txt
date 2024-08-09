# CMakeList.txt: проект CMake для Test_zad_v2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Test_zad_v2 "Test_zad_v2.cpp" "Test_zad_v2.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Test_zad_v2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
