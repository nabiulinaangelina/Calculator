# Создаём исполняемый файл для тестов
add_executable(tests_calculator
    tests_Standart.cpp
)

# Линкуем с библиотекой проекта, это автоматически добавляет путь "../include"
# Связываем тесты с библиотекой complex и gtest
target_link_libraries(tests_calculator
    PRIVATE
        lib_calculator
        GTest::gtest_main
        spdlog::spdlog
)

# --- Обнаружение тестов CTest ---
# Автоматически находим и добавляем тесты из исполняемого файла
gtest_discover_tests(tests_calculator)
