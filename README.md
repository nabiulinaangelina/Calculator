# Описание
Пример индивидуального проекта на языке С++ для курса "Основы и методологии программирования". Проект "Расширенный консольный калькулятор".

# Техническое задание
[Software requirements](SoftwareRequirements.md)

# Этапы разработки
[Этапы разработки приложения](StagesOfDevelopment.md)

**Язык программирования:** С++20

**Copyright (c)** 2025 [Ольга Казанцева](https://github.com/avelana)

# Licence
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/2/2e/MIT_Logo_New.svg/330px-MIT_Logo_New.svg.png" width="5%" /> MIT License

# Description
The example of C++ individual project for the course "Fundamentals and Methodologies of Programming". The project is "Extended console calculator".

[Software requirements](SoftwareRequirements.md).

# Stages of development
[Stages of development](StagesOfDevelopment.md)

**Programming language:** C++20

**Copyright (c)** 2025 [Olga Kazantseva](https://github.com/avelana)

# Организация репозитория
Репозиторий содержит код проекта, который разрабатывается в IDE VS Code. В проектах используются современные инструменты разработки: библиотека модульного тестирования gtest и библиотека журналирования событий spdlog. Сборка проекта ведется под управлением CMake.

## Зависимости
- Google Test и spdlog загружаются с помощью FetchContent.
- Они хранятся в корневом каталоге сборки, в папке build.

## Цели запуска в проекте имеют следующие названия 
- app_calculator - приложение "Калькулятор".
- tests_calculator - приложение тестов.

## ## Структура проекта
Проект имеет следующую структуру:

```
cpp-calculator/
├── CMakeLists.txt           # Корневой конфигурационный файл проекта
├── cmake/
│   └── Dependencies.cmake   # подключение зависимостей gtest, spdlog 
├── data/                    # папка с исходными данными, *.txt и др.
│   └── input.txt
├── include/                 # Заголовочные файлы библиотек, *.hpp.
│   └── module.hpp
├── src/                     # Исходный код основного приложения *.cpp
│   ├── AppCalculator.hpp    # Класс приложения, Singleton
│   ├── AppCalculator.cpp
│   ├── CMakeLists.txt       # Конфигурация библиотек и цели app-calculator
│   ├── main.cpp             # Точка входа приложения
│   └── module.cpp           # Реализация функций/классов            
└── tests/                   # Модульные тесты (используют Google Test)
    ├── CMakeLists.txt       # Конфигурация цели tests-calculator
    └── tests-module.cpp     # Тесты для module.cpp
```

## Запуск проектов в VS Code
1) Откройте палитру команд (Cmd+Shift+P) → «CMake: Select a Kit» → выберите нужный компилятор (Clang, GCC и т.д.).
2) (Cmd+Shift+P) -> CMake: Configure
3) (Cmd+Shift+P) -> CMake: Build
4) (Cmd+Shift+P) -> CMake: Set Launch/Debug Target - выбираем цели запууска - приложение или тесты.
5) Запуск выбранного целевого объекта в окне терминала: внизу IDE с помощью панели CMake стрелка запуска ▶ .

В результате конфигурации и сборки будет создан каталог сборки build: исполняемые файлы — в `build/bin/`, а библиотеки — в `build/lib`.