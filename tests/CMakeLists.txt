# Создаём исполняемый файл для тестов
add_executable(tests_calculator
    tests_Standard.cpp
    tests_Calculator.cpp
    tests_Scientific.cpp
)

# Линкуем с библиотекой проекта, это автоматически добавляет путь "../include"
# Связываем тесты с библиотекой complex и gtest
target_link_libraries(tests_calculator
    PRIVATE
        lib_calculator
        GTest::gtest_main
        spdlog::spdlog
)

target_include_directories(tests_calculator
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/data_structures
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/commands
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/commands/arithmetic
)

# --- Обнаружение тестов CTest ---
# Автоматически находим и добавляем тесты из исполняемого файла
gtest_discover_tests(tests_calculator)
