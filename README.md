# Dirwalk

## Установка и запуск

1. **Клонирование репозитория:**

    ```bash
    git clone https://github.com/13dashaa/OSaSP_lab1.git
    ```

2. **Перейдите в директорию репозитория и выполните следующие команды:**

    ```bash
    cd OSaSP_lab1
    ```

3. **Соберите проект с помощью make:**

Для сборки в режиме отладки:

    
    make MODE=debug
    

Для сборки в режиме выпуска:

    
    make MODE=release
    
По умолчанию сборка происходит в режиме отладки:

    
    make 
   

4. **Запуск программы:**

После сборки Вы можете использовать команду dirwalk для обхода директорий.

Если сборка была выполнена в режиме выпуска:

        ./build/debug/dirwalk <directory_path> <options>
        

Если сборка была выполнена в режиме отладки:

        ./build/release/dirwalk <directory_path> <options>
           
    

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
- `make` для сборки проекта 

## Алиас zsh

Чтобы создать псевдоним для команды  `dirwalk` в zsh, добавьте следующее в Ваш файл `~/.zshrc`:

    
    function dirwalk() {
      /home/user/build/dirwalk "$1" "$2"
    }
    

Затем выполните:

    
    source ~/.zshrc
    
