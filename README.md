# RpGame
Программа / игра по моделированию родового поместья.

Проект находится на ранней стадии разработки.



## Зависимости от библиотек
| Библиотека    | Версия  | Лицензия                   | Связывание | Описание |
| ------------- | ------- | -------------------------- | ---------- | -------- |
| dear imgui    | 1.89.8  | MIT                        | встроена   | Интерфейс пользователя. |
| SDL           | 2.0.10  | zlib                       | общая      | Обобщение управления окнами, вводом, изображениями, графикой (OpenGl). |
| GLM           | 0.9.9.8 | MIT                        | встроена   | 3d математика. |
| libc++        | 15      | APACHE-2-LLVM-EXCEPTIONS   | общая      | Реализация С++ std библиотеки от LLVM. |
| GNU C Library | 2.35    | GNU lgpl-2.1               | общая      | Реализация С библиотеки от GNU. |



## Используемые инструменты
| Программа  | Версия  | Лицензия                                 | Описание    |
| ---------- | ------- | ---------------------------------------- | ----------- |
| Clang      | 15      | Apache License v2.0 with LLVM Exceptions | Компилятор C, С++ (открытый, качественный). |
| SCons      | 3.1.2-2 | MIT                                      | Система сборки (простая, мульти-платформенная). |



## Инструкция по сборке
Возможно придётся поменять пути до системных библиотек в файле SConstruct.

В терминале перейти в каталог с исходниками, и выполнить:

### Установка зависимостей в Linux (Mint 21.2 Cinnamon)
```
sudo apt install clang-15 libc++-15-dev libc++abi-15-dev libsdl2-dev scons
```

### Сборка
```
scons
```

### Запуск
```
./RpGame
```

### Очистка (при пересборке)
```
scons -c
```



## License
Программа находится в общественном достоянии. Либо доступна по лицензии MIT - на ваш выбор.

### Небольшие пояснения
Автор не накладывает никаких ограничений.
Но ограничения могут возникнут при изменении исходного кода и публикации.
Автор старался сделать программу (и исходный код) максимально доступной и открытой.
Поэтому, использованы библиотеки и инструменты только с максимально разрешительными лицензиями (MIT и аналоги).
Лицензии MIT (и аналоги) дают все права использовать, кроме удаления файла лицензии.
Но системная библиотека С имеет лицензию LGPL, запрещающая включать её статически в закрытый исходный код.