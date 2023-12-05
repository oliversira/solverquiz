// solverquiz.cpp : Defines the entry point for the application.
//

#include "solverquiz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 10
#define MAX_OPTION_LEN 50
#define MAX_ANSWER_LEN 50

typedef struct {
    char question[256];
    char options[4][MAX_OPTION_LEN];
    char correct_option;
} Question;

typedef struct {
    char name[50];
    char surname[50];
    char gender;
    int age;
} UserInfo;

// Funkcia na zadanie osobných informácií používateľa
void askUserInfo(UserInfo* userInfo) {
    printf("\033[31mAhoj ! Vitaj v interaktivnom kvize \033[0m"); // \033[0m\n - escape sekvencia pre zmenu farby textu, Farebne kody : čierna[30], oranžova[38],
    printf(" \033[33m>>>SOLVER<<< \033\n "); // červená[31], zelená[32], žltá[33], modrá[34], purpurová[35], azurova[36], biela[37]

    printf("\033[0m");

    printf("Zadaj svoje meno: ");
    scanf("%s", userInfo->name);

    printf("Zadaj svoje priezvisko: ");
    scanf("%s", userInfo->surname);

    printf("Zadaj svoje pohlavie (M/Z): ");
    scanf(" %c", &userInfo->gender);

    printf("Zadaj svoj vek: ");
    scanf("%d", &userInfo->age);
}

// Funkcia na načítanie otázok zo súboru
void loadQuestions(Question questions[MAX_QUESTIONS], const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Chyba pri otvarani suboru.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_QUESTIONS; ++i) {
        fgets(questions[i].question, sizeof(questions[i].question), file);
        for (int j = 0; j < 4; ++j) {
            fgets(questions[i].options[j], sizeof(questions[i].options[j]), file);
        }
        fscanf(file, " Spravna odpoved: %c\n", &questions[i].correct_option);
    }

    fclose(file);
}

// Funkcia na uloženie štatistík do súboru
void saveStatistics(int score, double duration) {
    FILE* file = fopen("statistics.txt", "a");
    if (file == NULL) {
        printf("Chyba pri otvarani suboru pre statistiky.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Skore: %d, Doba trvania: %.2f sekundy\n", score, duration);

    fclose(file);
}

// Funkcia na zobrazenie štatistík
void displayStatistics(int score, double duration) {
    printf("\n\n=== Statistiky ===\n");
    printf("Skore: %d\n", score);
    printf("Doba trvania: %.2f sekundy\n", duration);
}

// Funkcia na vykonanie kvízu
void quiz(UserInfo* userInfo, const char* filename) {
    Question questions[MAX_QUESTIONS];
    loadQuestions(questions, filename);

    int score = 0;
    clock_t start_time = clock();

    for (int i = 0; i < MAX_QUESTIONS; ++i) {
        printf("\n%s", questions[i].question);
        for (int j = 0; j < 4; ++j) {
            printf("%c) %s", 'a' + j, questions[i].options[j]);
        }

        char user_answer[2];
        printf("Zadaj svoju odpoved (a, b, c, d): ");
        scanf("%s", user_answer);

        if (user_answer[0] == questions[i].correct_option) {
            printf("Spravne!\n");
            score++;
        }
        else {
            printf("Nespravne. Spravna odpoved je: %c\n", questions[i].correct_option);
        }
    }

    clock_t end_time = clock();
    double duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    displayStatistics(score, duration);
    saveStatistics(score, duration);
}

int main() {
    UserInfo userInfo;
    askUserInfo(&userInfo);

    int option;
    do {
        printf("\nVyber si kviz:\n");
        printf("\033[32m1. Jazykova bariera\033\n");
        printf("\033[33m2. Programovanie\033\n");
        printf("\033[34m3. Orientacia na VUT\033\n");
        printf("\033[35m4. Audio\033\n");
        printf("\033[0m");
        printf("5. Koniec\n");
        printf("Zadaj cislo vybraneho kvizu: ");
        scanf("%d", &option);

        switch (option) {
        case 1:
            quiz(&userInfo, "kviz1.txt");
            break;
        case 2:
            quiz(&userInfo, "kviz2.txt");
            break;
        case 3:
            quiz(&userInfo, "kviz3.txt");
            break;
        case 4:
            quiz(&userInfo, "kviz4.txt");
            break;
        case 5:
            printf("Dakujeme za hru!\n");
            break;
        default:
            printf("Neplatna volba.\n");
            break;
        }
    } while (option != 5);

    return 0;
}
