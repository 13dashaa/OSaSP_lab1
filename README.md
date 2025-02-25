# Dirwalk

## Установка

1. **Клонирование репозитория:**

    ```bash
    git clone https://github.com/13dashaa/dirwalk.git
    ```

2. **Перейдите в директорию репозитория и выполните следующие команды:**

    ```bash
    cd dirwalk
    mkdir build
    cd build
    ```

3. **Соберите проект с помощью CMake:**

    ```bash
    cmake ..
    make
    ```

После сборки Вы можете использовать команду dirwalk для обхода директорий:

    
    ./dirwalk <directory_path> <options>
    

## Аргументы

- `<directory_path>`: Путь к директории, которую вы хотите обойти.
- `<options>`: Опции для фильтрации и сортировки.

## Доступные опции

- `-l`: Показывать только символические ссылки (-type l).
- `-d`: Показывать только каталоги (-type d).
- `-f`: Показывать только файлы (-type f).
- `-s`: SСортировать вывод в соответствии с LC_COLLATE.

## Требования к среде

-  Операционная система на базе Linux/Unix 
-  Компилятор `gcc` или `clang` (`sudo apt install gcc`)
- `cmake` для сборки проекта (`sudo apt install cmake`)

## Алиас zsh

Чтобы создать псевдоним для команды  `dirwalk` в zsh, добавьте следующее в Ваш файл `~/.zshrc`:

    
    function dirwalk() {
      /home/user/build/dirwalk "$1" "$2"
    }
    

Затем выполните:

    
    source ~/.zshrc
    
