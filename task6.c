#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

struct Student {
    char surname[50];
    int id;
    char faculty[50];
    int group;
};
// Функция считывания студентов из файла
int read_students(struct Student students[], int max_size, const char* filename) {
    int count = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        exit(1);
    }

    while (!feof(file) && count < max_size) {
        fscanf(file, "%s %d %s %d", students[count].surname, &students[count].id, students[count].faculty, &students[count].group);
        count++;
    }

    fclose(file);

    return count;
}
// Функция добавления студента
void add_student(struct Student students[], int max_size, char* filename) {
    if (max_size == 0) {
        printf("Список уже полный\n");
        return;
    }

    printf("Ведите фамилию студента: ");
    scanf("%s", students[max_size].surname);

    printf("Введите номер зачетной книжки студента: ");
    scanf("%d", &students[max_size].id);

    printf("Введите факультет: ");
    scanf("%s", students[max_size].faculty);

    printf("Введите номер группы: ");
    scanf("%d", &students[max_size].group);

    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
            printf("Ошибка открытия файла %s\n", filename);
            return;
    }

    for (int i = 0; i < max_size + 1; i++) {
        fprintf(fp, "%s %d %s %d\n", students[i].surname, students[i].id, students[i].faculty, students[i].group);
    }

        fclose(fp);

    printf("Студент успешно добавлен\n");
}
// Вывод структуры на экран
void print_students(struct Student students[], int count) {
    // printf("Фамилия\tЗачетка\tФакультет\tГруппа\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t%d\t%s\t%d\n", students[i].surname, students[i].id, students[i].faculty, students[i].group);
    }
}

// Сортировка по заданному полю
void sort_students(struct Student students[], int count, int field, char* filename) {
    for (int i = 0; i < count - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < count; j++) {
            if (field == 1 && strcmp(students[j].surname, students[min_index].surname) < 0) {
                min_index = j;
            } else if (field == 2 && students[j].id < students[min_index].id) {
                min_index = j;
            } else if (field == 3 && strcmp(students[j].faculty, students[min_index].faculty) < 0) {
                min_index = j;
            } else if (field == 4 && students[j].group < students[min_index].group) {
                min_index = j;
            }
        }
        if (min_index != i) {
            struct Student temp = students[i];
            students[i] = students[min_index];
            students[min_index] = temp;
        }
    }
    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
            printf("Ошибка открытия файла %s\n", filename);
            return;
    }

    for (int i = 0; i < count + 1; i++) {
        fprintf(fp, "%s %d %s %d\n", students[i].surname, students[i].id, students[i].faculty, students[i].group);
    }

        fclose(fp);

}
// Поиск студента по фамилии
void find_student(struct Student students[], int count) {
    char family[50];
    printf("Введите фамилию: ");
    scanf("%s", family);
    for (int i = 0; i < count; i++) {
            if (strcmp(students[i].surname, family) == 0) {
                printf("Найден студент:\n");
                printf("Фамилия: %s\n", students[i].surname);
                printf("Зачетка: %d\n", students[i].id);
                printf("Факультет: %s\n", students[i].faculty);
                printf("Группа: %d\n", students[i].group);
                return;
            }
        }


    printf("Таких студентов нет.\n");
}

// Удаление студента по фамилии
void remove_student(struct Student students[], int* count, char* filename) {
    char family[50];
    printf("Введите фамилию: ");
    scanf("%s", family);

    int index = -1;

    for (int i = 0; i < *count; i++) {
        if (strcmp(students[i].surname, family) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Таких студентов нет.\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }

    (*count)--;
    
    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
            printf("Ошибка открытия файла %s\n", filename);
            return;
    }

    for (int i = 0; i < count + 1; i++) {
        fprintf(fp, "%s %d %s %d\n", students[i].surname, students[i].id, students[i].faculty, students[i].group);
    }

        fclose(fp);
    printf("Студент удален.\n");
    
}

// Редактирование информации о студенте
void edit_student(struct Student students[], int count, char* filename) {
    char family[50];
    printf("Введите фамилию: ");
    scanf("%s", family);

    int index = -1;

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].surname, family) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Таких студентов нет.\n");
        return;
    }

    printf("Фамилия: ");
    scanf("%s", students[index].surname);

    printf("Зачетка: ");
    scanf("%d", &students[index].id);

    printf("Факультет: ");
    scanf("%s", &students[index].faculty);
    
    printf("Группа: ");
    scanf("%d", &students[index].group);
    
    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
            printf("Ошибка открытия файла %s\n", filename);
            return;
    }

    for (int i = 0; i < count + 1; i++) {
        fprintf(fp, "%s %d %s %d\n", students[i].surname, students[i].id, students[i].faculty, students[i].group);
    }

        fclose(fp);
    
    printf("Информация о стундента обновлена.\n");
}
// Вывод студентов по номеру группы
void print_by_group(struct Student students[], int count) {
    int grp;
    printf("Введите номер группы: ");
    scanf("%d", &grp);

    printf("Все студенты из группы %d:\n", grp);

    for (int i = 0; i < count; i++) {
        if (students[i].group == grp) {
            printf("%s %d %s %d\n", students[i].surname, students[i].id, students[i].faculty, students[i].group);
        }
    }
}

int main() {
    struct Student students[MAX_SIZE];
    int count = read_students(students, MAX_SIZE, "students.txt");
// добавление студента
  // add_student(students, count, "students.txt");
     // count++;
// Вывод на экран
    print_students(students, count);
// Сортировка
   // sort_students(students, count, 1, "students.txt");
// Поиск по фамилии
  // find_student(students, count);
// Удаление студента
    // remove_student(students, count, "students.txt");
// Редактирование сьудента
   // edit_student(students, count, "students.txt");
// Вывод по группе
    // print_by_group(students, count);
    return 0;
}


