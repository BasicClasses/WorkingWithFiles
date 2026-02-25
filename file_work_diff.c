#include <iostream>
#include <stdio.h>


struct Result {
    FILE* file{};
    int status{};
};

void print_error(int err) {

    switch (err) {
    case 2:
        std::cout << "Отсутствует такой файл или каталог. " << "\n";
        break;
    case 13:
        std::cout << "в разрешении отказано.  " << "\n";
        break;
    default:
        std::cout << "Ошибка неизвестна!  " << "\n";
        break;
    }
}

Result open_file(const char* path, const char* mode) {

    Result res;
    res.status = fopen(&(res.file), path, mode);

    if (err != 0) {
        std::cout << "Ошибка открытия файла " << path <<  "\n"; 
        print_error(err);
    }
    return res;
}

void read_file_as_str(FILE* in) {

    const size_t kSizeBuff = 1000;
    char buf[kSizeBuff];
    while (!feof(in)) {
       if (fgets(buf, kSizeBuff, in))
           std::cout << buf;
     }
}

void write_file_v1(FILE* in) {

    const size_t kSizeBuff = 1000;
    char buf[kSizeBuff];

    while (true) {
        std::cout << "Enter string:";
        std::cin.getline(buf, kSizeBuff);

        if (strcmp(buf, "0") == 0)
            break;

        fputs(buf, in);
        fputs("\n", in);
    }
}

int main() {

    setlocale(LC_ALL, "Ru");

    char str[]{ "My Message! \n" };
    const char* path = "data2.txt";
    Result file = open_file(path, "w");

    if (file.file) {
        write_file_v1(file.file);
        fclose(file.file);
    }

    file = open_file(path, "r");

    if (file.file) {
        read_file_as_str(file.file);
        fclose(file.file);
    }


    /*const size_t kSizeBuff = 1000;
    char buf[kSizeBuff];


    const char* path = "data.txt";
   

    FILE* in = open_file(path, "r");

    if (in){
        read_file_as_str(in);
        fclose(in);
    }*/
}



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <errno.h>
#include <string.h>

static void print_fopen_error(const char* path, const char* mode, errno_t err)
{
    // Текстовое описание ошибки по коду err
    char msg[256] = {0};
    // strerror_s в MSVC: безопасная версия strerror
    strerror_s(msg, sizeof(msg), (int)err);

    fprintf(stderr, "Не удалось открыть файл.\n");
    fprintf(stderr, "  path: \"%s\"\n", path ? path : "(null)");
    fprintf(stderr, "  mode: \"%s\"\n", mode ? mode : "(null)");
    fprintf(stderr, "  err : %d (%s)\n", (int)err, msg);

    // Детальная логика по наиболее частым ошибкам
    switch (err)
    {
        case EINVAL:
            fprintf(stderr, "Причина: неверный аргумент (NULL/неверный режим/битые параметры).\n");
            fprintf(stderr, "Что делать: проверьте указатели, строку mode (например \"r\", \"rb\", \"w\" и т.п.).\n");
            break;

        case ENOENT:
            fprintf(stderr, "Причина: файл или путь не существует.\n");
            fprintf(stderr, "Что делать: проверьте имя файла, текущую директорию, абсолютный/относительный путь.\n");
            break;

        case EACCES:
            fprintf(stderr, "Причина: нет прав доступа или файл заблокирован.\n");
            fprintf(stderr, "Что делать: проверьте права, атрибут 'read-only', не открыт ли файл другим процессом.\n");
            break;

        case EMFILE:
            fprintf(stderr, "Причина: слишком много открытых файлов в процессе.\n");
            fprintf(stderr, "Что делать: закройте ненужные FILE* через fclose(), проверьте утечки.\n");
            break;

        case ENFILE:
            fprintf(stderr, "Причина: достигнут системный лимит открытых файлов.\n");
            fprintf(stderr, "Что делать: закройте файлы, проверьте лимиты ОС.\n");
            break;

        default:
            fprintf(stderr, "Причина: другая ошибка (код %d).\n", (int)err);
            fprintf(stderr, "Что делать: ориентируйтесь по тексту ошибки выше.\n");
            break;
    }
}

int main(void)
{
    const char* filename = "data.txt";

    FILE* f = NULL;
    errno_t err = fopen_s(&f, filename, "r");   // попробуем открыть на чтение

    if (err != 0 || f == NULL)
    {
        print_fopen_error(filename, "r", err);
        return 1;
    }

    // Если всё хорошо — работаем с файлом
    printf("Файл \"%s\" успешно открыт.\n", filename);

    // Пример чтения первой строки
    char line[128];
    if (fgets(line, sizeof(line), f))
        printf("Первая строка: %s\n", line);
    else
        printf("Файл пустой или ошибка чтения.\n");

    fclose(f);
    return 0;
}



