#define _CRT_SECURE_NO_WARNINGS
#include "Realisation.h"

int main()
{
    SetConsoleTitle(L"Игра \"Быки и коровы\"");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int game_mode;
    char rules[50], continuation[50];

    printf("\t\t@@@@@  @     @  @   @  @     @      @     @      @   @   @@@   @@@@    @@@   @@@@   @     @\n");
    printf("\t\t@      @     @  @  @   @    @@      @    @@      @  @   @   @  @   @  @   @  @   @  @     @\n");
    printf("\t\t@      @     @  @ @    @   @ @      @   @ @      @ @    @   @  @   @  @   @  @   @  @     @\n");
    printf("\t\t@@@@   @@@@@ @  @@     @  @  @      @  @  @      @@     @   @  @@@@   @   @  @@@@   @@@@@ @\n");
    printf("\t\t@   @  @   @ @  @ @    @ @   @      @ @   @      @ @    @   @  @      @   @  @   @  @   @ @\n");
    printf("\t\t@   @  @   @ @  @  @   @@    @      @@    @      @  @   @   @  @      @   @  @   @  @   @ @\n");
    printf("\t\t@@@@   @@@@@ @  @   @  @     @      @     @      @   @   @@@   @       @@@   @@@@   @@@@@ @\n");
    printf("\n\n");

    do
    {
        printf("Хотели бы вы ознакомиться с правилами игры? ");   scanf("%s", &rules);
        if ((strcmp("Да", rules) == 0) || (strcmp("да", rules) == 0)) printf("Каждый из противников задумывает четырехзначное число, все цифры которого различны (первая цифра отлична от нуля).\nНеобходимо разгадать задуманное число. Противники по очереди называют друг другу числа и сообщают о количестве «быков»\nи «коров» в названном числе («бык» — цифра есть в записи задуманного числа и стоит в той же позиции, что и в задуманном\nчисле; «корова» — цифра есть в записи задуманного числа, но не стоит в той же позиции, что и в задуманном числе).\nНапример, если задумано число 3275 и названо число 1234, получаем в названном числе одного «быка» и одну «корову».\nОчевидно, что число отгадано в том случае, если имеем 4 «быка». Выигрывает тот, кто отгадает первым.\n");
        else if ((strcmp("Нет", rules) != 0) && (strcmp("нет", rules) != 0)) printf("Пожалуйста, введите только да или нет!\n");
    } while ((strcmp("Да", rules) != 0) && (strcmp("Нет", rules) != 0) && (strcmp("да", rules) != 0) && (strcmp("нет", rules) != 0));
    printf("\n");

    do
    {
        do
        {
            printf("Введите количество игроков: ");
            while (!scanf("%d", &game_mode))
            {
                scanf("%*[^\n]");
                printf("Пожалуйста, введите одно число: ");
            }
            if ((game_mode != 1) && (game_mode != 2)) printf("В игре может участвовать от 1 до 2 игроков!\n");
        } while ((game_mode != 1) && (game_mode != 2));

        if (game_mode == 1) Game_Mode_1();
        else Game_Mode_2();

        do
        {
            printf("Хотите сыграть ещё раз? ");   scanf("%s", &continuation);
            if ((strcmp("Да", continuation) != 0) && (strcmp("да", continuation) != 0) && (strcmp("Нет", continuation) != 0) && (strcmp("нет", continuation) != 0)) printf("Пожалуйста, введите только да или нет!\n");
        } while ((strcmp("Да", continuation) != 0) && (strcmp("Нет", continuation) != 0) && (strcmp("да", continuation) != 0) && (strcmp("нет", continuation) != 0));
        printf("\n");

    } while ((strcmp("Да", continuation) == 0) || (strcmp("да", continuation) == 0));

    system("pause");

    return 0;
}