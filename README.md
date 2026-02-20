# Робота с файлами

## Файл
Файл — это именованная область данных на носителе информации (например, жёстком диске, SSD, флеш-накопителе и т.д.), которая используется для хранения и организации информации.\
Файлы могут содержать различные типы данных: тексты, изображения, аудио, видео, программы и многое другое.

**Основные характеристики файла:**
 - Имя файла — уникальное название, по которому можно идентифицировать файл.
 - Расширение — часть имени файла, которая указывает на его тип (например, .txt, .jpg, .mp3). Расширение помогает операционной системе и программам понять, как работать с файлом.
 - Размер — объём данных, которые хранятся в файле (измеряется в байтах, килобайтах, мегабайтах и т.д.).
 - Расположение — путь к файлу на диске или в файловой системе (например, C:\Documents\file.txt).

Примеры файлов:\
Текстовый файл: document.txt\
Изображение: photo.jpg\
Аудиофайл: song.mp3\
Программа: app.exe

Файлы организуются в папки (директории), что позволяет упорядочивать данные на устройстве.\
Операционная система управляет файлами, предоставляя пользователю доступ к ним через файловый менеджер или другие программы.

## Библиотека stdio.h

Библиотека stdio.h (Standard Input/Output) — это стандартная библиотека языка C, которая предоставляет функции для работы с файлами и потоками ввода-вывода.\
В C++ она также доступна для совместимости.

** Основные функции для работы с файлами в stdio.h:**

 - fopen_s:

   Синтаксис: errno_t fopen_s(FILE** file, const char* filename, const char* mode);

   Открывает файл и возвращает код ошибки.

  Пример:
  
```
FILE* file;
errno_t err = fopen_s(&file, "example.txt", "r");
if (err != 0) {
    // Обработка ошибки
}
```
  
 - fclose() — закрывает файл.

   Синтаксис: int fclose(FILE* file);

   Закрывает файл и освобождает ресурсы.
   
 - fprintf_s:

    Синтаксис: errno_t fprintf_s(FILE* file, const char* format, ...);

    Записывает форматированные данные в файл с проверкой безопасности.

    Пример:

   ```
   errno_t err = fprintf_s(file, "Значение: %d\n", 42);
   if (err != 0) {
          // Обработка ошибки
    }
   ```
   
 - scanf_s:

   Синтаксис: errno_t fscanf_s(FILE* file, const char* format, ...);

   Читает форматированные данные из файла с проверкой безопасности.

   Пример:
   
```
   int value;
   errno_t err = fscanf_s(file, "%d", &value);
   if (err != 0) {
     // Обработка ошибки
   }
```

- fgets_s:

  Синтаксис: char* fgets_s(char* buffer, size_t bufferSize, FILE* file);

  Читает строку из файла с ограничением по размеру буфера.

  Пример:

```
char buffer[100];
if (fgets_s(buffer, sizeof(buffer), file)) {
    std::cout << "Прочитанная строка: " << buffer << std::endl;
}
```

 - fwrite():

  Синтаксис: size_t fwrite(const void* buffer, size_t size, size_t count, FILE* file);

  Записывает бинарные данные в файл.


 - fread() — fread():

    Синтаксис: size_t fread(void* buffer, size_t size, size_t count, FILE* file);

    Читает бинарные данные из файла.


 - fseek() — fseek():

    Синтаксис: int fseek(FILE* file, long offset, int whence);

    Перемещает указатель в файле.

    whence:
      - SEEK_SET — от начала файла.
      - SEEK_CUR — от текущей позиции.
      - SEEK_END — от конца файла.

 - ftell()

    Синтаксис: long ftell(FILE* file);

    Возвращает текущую позицию указателя в файле.

 - feof() — проверяет, достигнут ли конец файла.

   интаксис: int feof(FILE* file);

   Проверяет, достигнут ли конец файла.

**Использование fseek и ftell**

```
#include <iostream>
#include <cstdio>

int main() {
    const char* filename = "example.txt";
    FILE* file = nullptr;
    
    // Открываем файл для записи
    errno_t err = fopen_s(&file, filename, "w");
    if (err != 0 || !file) {
        std::cerr << "Ошибка открытия файла! Код ошибки: " << err << std::endl;
        return 1;
    }

    // Записываем данные в файл
    fprintf(file, "Пример использования fseek и ftell.\n");

    // Получаем текущую позицию указателя
    long position = ftell(file);
    std::cout << "Текущая позиция: " << position << std::endl;

    // Перемещаем указатель на 10 байт от начала файла
    fseek(file, 10, SEEK_SET);

    // Записываем данные в новую позицию
    fprintf(file, "Новые данные.");

    // Закрываем файл
    fclose(file);

    return 0;
}
```

**Пример использования fscanf_s и fprintf_s**

```
#include <iostream>
#include <cstdio>

int main() {
    const char* filename = "data.txt";
    FILE* file = nullptr;

    // Открываем файл для записи
    errno_t err = fopen_s(&file, filename, "w");
    if (err != 0 || !file) {
        std::cerr << "Ошибка открытия файла! Код ошибки: " << err << std::endl;
        return 1;
    }

    // Записываем данные в файл
    int value = 42;
    err = fprintf_s(file, "%d\n", value);
    if (err != 0) {
        std::cerr << "Ошибка записи в файл!" << std::endl;
        fclose(file);
        return 1;
    }

    // Закрываем файл
    fclose(file);

    // Открываем файл для чтения
    err = fopen_s(&file, filename, "r");
    if (err != 0 || !file) {
        std::cerr << "Ошибка открытия файла для чтения! Код ошибки: " << err << std::endl;
        return 1;
    }

    // Читаем данные из файла
    int readValue;
    err = fscanf_s(file, "%d", &readValue);
    if (err != 0) {
        std::cerr << "Ошибка чтения из файла!" << std::endl;
        fclose(file);
        return 1;
    }

    std::cout << "Прочитанное значение: " << readValue << std::endl;

    // Закрываем файл
    fclose(file);

    return 0;
}
```

**Использование fseek и ftell**

```
#include <iostream>
#include <cstdio>

int main() {
    const char* filename = "example.txt";

 FILE* file = nullptr;

    // Открываем файл для записи
    errno_t err = fopen_s(&file, filename, "w");
    if (err != 0 || !file) {
        std::cerr << "Ошибка открытия файла! Код ошибки: " << err << std::endl;
        return 1;
    }

    // Записываем данные в файл
    fprintf(file, "Пример использования fseek и ftell.\n");

    // Получаем текущую позицию указателя
    long position = ftell(file);
    std::cout << "Текущая позиция: " << position << std::endl;

    // Перемещаем указатель на 10 байт от начала файла
    fseek(file, 10, SEEK_SET);

    // Записываем данные в новую позицию
    fprintf(file, "Новые данные.");

    // Закрываем файл
    fclose(file);

    return 0;
}
```
## Домашнее задание 
Задание 1. \
Дан текстовый файл. Подсчитать количество \
слов, начинающихся с символа, который задаёт пользователь. \
 \
Задание 2. \
Дан текстовый файл. Необходимо создать новый файл, \
в который переписать из исходного файла все слова, \
состоящие не менее чем из семи букв.

