# Зайцев Д.Е.

Лабораторная работа представляет собой программу для работы с самописной базой данных с сущностью студента
> При запуске программы открывается меню выбора с подробной инструкцией \
> Каждая инструкция имеет описание и параметры, подаваемые на вход \
> База данных меняется в режиме реального времени (то есть при добавлении/удалении пользователя исходный файл перезаписывается)

Запуск основной программы
>- `make` - компиляция всех файлов программы в дерикотрии out
>- `make main FILE=data/database.txt` - запуск основной программы с текстовой базой данных

Запуск программы генерации рандомной базы данных
> `make generation FILE=data/файл_базы.txt COUNT=количество_пользователей`
 
> Запуск  конвертации
> `make`, затем `make convertation FILE1=data/файл_до.(txt/bin) FILE2=data/файл_после.(txt/bin)`
> Программа сама определяет нужную конвертацию, исходя из расширения входного файла
