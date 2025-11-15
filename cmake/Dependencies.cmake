# Директива предотвращает повторное включение одного и 
# того же файла несколько раз в процессе конфигурации проекта.
include_guard()

include(FetchContent)

# Переопределяемые версии
if(NOT DEPS_GTEST_TAG)
    set(DEPS_GTEST_TAG v1.14.0 CACHE STRING "googletest version")
endif()
if(NOT DEPS_SPDLOG_TAG)
    set(DEPS_SPDLOG_TAG v1.12.0 CACHE STRING "spdlog version")
endif()

# Настройки GTest
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Git clone вместо ZIP
#FetchContent_Declare(
#    googletest
#    GIT_REPOSITORY https://github.com/google/googletest.git
#    GIT_TAG ${DEPS_GTEST_TAG}
#)

#FetchContent_Declare(
#    spdlog
#    GIT_REPOSITORY https://github.com/gabime/spdlog.git
#    GIT_TAG ${DEPS_SPDLOG_TAG}
#)

# Директива, которая загружает встроенный модуль CMake под 
# названием FetchContent
include(FetchContent)

# Объявляем, где найти зависимость 
# spdlog - библиотека для логирования (~1 MB),
# а если https://github.com/gabime/spdlog.git, то это
# git clone → весь репозиторий с историей (~10+ MB)
# spdlog v1.14.1 от мая 2024
# gtest - фреймворк для модульного тестирования (~3 MB), 
# а если https://github.com/google/googletest.git, то это 
# git clone → весь репозиторий с историей (~50+ MB)
# gtest v1.15.0 от октября 2024
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.14.1.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Загрузка
FetchContent_MakeAvailable(googletest spdlog)

# Включение тестов 
enable_testing()
include(GoogleTest)

# Диагностика
message(STATUS "Dependencies: googletest=${DEPS_GTEST_TAG}, spdlog=${DEPS_SPDLOG_TAG}")
