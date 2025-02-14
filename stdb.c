#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_ADDRESS 100

typedef struct {
    char name[MAX_NAME];
    char birth_date[11]; 
    char address[MAX_ADDRESS];
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void save_to_file() {
    FILE *file = fopen("students.db", "w");
    if (!file) {
        printf("помилка\n");
        return;
    }
    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%s|%s|%s\n", students[i].name, students[i].birth_date, students[i].address);
    }
    fclose(file);
}

void load_from_file() {
    FILE *file = fopen("students.db", "r");
    if (!file) return;
    student_count = 0;
    while (fscanf(file, "%49[^|]|%10[^|]|%99[^\n]\n", students[student_count].name, 
                  students[student_count].birth_date, students[student_count].address) == 3) {
        student_count++;
    }
    fclose(file);
}

void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("База даних заповнена\n");
        return;
    }
    printf("Введіть ім'я: ");
    scanf(" %[^\n]", students[student_count].name);
    printf("Введіть дату народження (YYYY-MM-DD): ");
    scanf(" %10s", students[student_count].birth_date);
    printf("Введіть адресу: ");
    scanf(" %[^\n]", students[student_count].address);
    student_count++;
    save_to_file();
}

void edit_student() {
    char name[MAX_NAME];
    printf("Введіть ім'я студента для редагування: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < student_count; i++) {
        if (strstr(students[i].name, name)) {
            printf("Знайдено: %s | %s | %s\n", students[i].name, students[i].birth_date, students[i].address);
            printf("Введіть нове ім'я: ");
            scanf(" %[^\n]", students[i].name);
            printf("Введіть нову дату народження: ");
            scanf(" %10s", students[i].birth_date);
            printf("Введіть нову адресу: ");
            scanf(" %[^\n]", students[i].address);
            save_to_file();
            return;
        }
    }
    printf("Студента не знайдено!\n");
}

void delete_student() {
    char name[MAX_NAME];
    printf("Введіть ім'я студента для видалення: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < student_count; i++) {
        if (strstr(students[i].name, name)) {
            printf("Видалено: %s\n", students[i].name);
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            save_to_file();
            return;
        }
    }
    printf("Студента не знайдено\n");
}

void search_student() {
    char query[MAX_NAME];
    printf("Введіть ім'я для пошуку: ");
    scanf(" %[^\n]", query);
    for (int i = 0; i < student_count; i++) {
        if (strstr(students[i].name, query)) {
            printf("%s | %s | %s\n", students[i].name, students[i].birth_date, students[i].address);
        }
    }
}

void list_students() {
    if (student_count == 0) {
        printf("База даних пуста!\n");
        return;
    }
    for (int i = 0; i < student_count; i++) {
        printf("%s | %s | %s\n", students[i].name, students[i].birth_date, students[i].address);
    }
}

int main() {
    load_from_file();
    int choice;
    do {
        printf("\n1. Додати\n2. Редагувати\n3. Видалити\n4. Пошук\n5. Список\n0. Вихід\nВаш вибір: ");
        scanf(" %d", &choice);
        switch (choice) {
            case 1: add_student(); break;
            case 2: edit_student(); break;
            case 3: delete_student(); break;
            case 4: search_student(); break;
            case 5: list_students(); break;
            case 0: printf("Вихід...\n"); break;
            default: printf("Неправильний вибір!\n");
        }
    } while (choice != 0);
    return 0;
}
