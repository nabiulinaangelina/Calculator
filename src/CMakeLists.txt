# ============================================
# Исполняемый файл - логика приложения
# ============================================
add_executable(app_calculator
    main.cpp
    AppCalculator.cpp #  App здесь, в приложении!
    Menu.cpp
)

# ============================================
# Библиотека приложения - country population
# ============================================
add_library(lib_calculator 
    Standard.cpp
    Calculator.cpp
)

# Объявляем, что заголовочные файлы находятся в ../include.
# 'PUBLIC' означает, что этот путь будет наследоваться любым другим target,
# который будет линковаться с lib_calculator. 
# ИСПОЛЬЗУЙТЕ CMAKE_CURRENT_SOURCE_DIR
# CMAKE_CURRENT_SOURCE_DIR - это путь к текущему каталогу.
# CMAKE_CURRENT_SOURCE_DIR/../include - это абсолютный путь.
# Это устраняет ошибку 'Found relative path'.
target_include_directories(lib_calculator
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/commands>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/utils>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/programmer>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/scientific>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/data_structures>
)

# ПРАВИЛЬНО: PUBLIC для библиотеки
target_link_libraries(lib_calculator
    PUBLIC
        spdlog::spdlog   # Логирование нужно везде
)


# ============================================
# Подключение библиотеки к Исполняемому файлу
# ============================================

target_link_libraries(app_calculator
    PRIVATE
        # Автоматически получит spdlog благодаря PUBLIC линковке в библиотеке
        lib_calculator  # Получаем Calculator
)

# Если у App есть свой заголовок (.hpp), добавляем:
target_include_directories(app_calculator
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)




