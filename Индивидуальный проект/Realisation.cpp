#define _CRT_SECURE_NO_WARNINGS
#define Values_max 4536
#define Digits_max 4
#define Digits 10
#include "Realisation.h"

void Game_Mode_1()
{
	int values, random, guessed_number = 0, move_of_the_player = 0, move_of_the_computer = 0, game_end = 0, counter = 0, winner = 2;
	int original_number_array[Digits_max], fit_or_not[Values_max], all_possible_values[Values_max][Digits_max], unused_digits[Digits];
	char player[15];

	values = Values_max;

	for (int i = 0; i < Values_max; i++) fit_or_not[i] = 1;
	for (int i = 0; i < Digits; i++) unused_digits[i] = -1;

	for (int digit_1 = 1; digit_1 < 10; digit_1++)
	{
		for (int digit_2 = 0; digit_2 < 10; digit_2++)
		{
			for (int digit_3 = 0; digit_3 < 10; digit_3++)
			{
				for (int digit_4 = 0; digit_4 < 10; digit_4++)
				{
					if ((digit_1 != digit_2) && (digit_1 != digit_3) && (digit_1 != digit_4) && (digit_2 != digit_3) && (digit_2 != digit_4) && (digit_3 != digit_4))
					{
						all_possible_values[counter][0] = digit_1;
						all_possible_values[counter][1] = digit_2;
						all_possible_values[counter][2] = digit_3;
						all_possible_values[counter][3] = digit_4;
						counter += 1;
					}
				}
			}
		}
	}

	srand(time(NULL));
	random = rand() % ((Values_max - 1) - 0 + 1) + 0;
	original_number_array[0] = all_possible_values[random][0];
	original_number_array[1] = all_possible_values[random][1];
	original_number_array[2] = all_possible_values[random][2];
	original_number_array[3] = all_possible_values[random][3];

	printf("Введите имя игрока: ");   scanf("%s", &player);

	do
	{
		game_end = Move_of_the_player(original_number_array, player, move_of_the_player);
		if (game_end == 0) game_end = Move_of_the_computer(fit_or_not, unused_digits, all_possible_values, move_of_the_computer, guessed_number, values);
		else winner = 1;
	} while (game_end == 0);

	if (winner == 1) Winner(original_number_array, player);
	else Loser(guessed_number);
}

void Game_Mode_2()
{
	int first_original_number, second_original_number, number_type = 1, move_of_the_first_player = 0, move_of_the_second_player = 0, game_end = 0, winner = 2;
	int first_original_number_array[Digits_max], second_original_number_array[Digits_max];
	char first_player[15], second_player[15];

	printf("Введите имя первого игрока: ");   scanf("%s", &first_player);
	printf("Введите имя второго игрока: ");   scanf("%s", &second_player);

	printf("%s, введите задуманное вами число так, чтобы %s не увидел: ", first_player, second_player);
	while (!scanf("%d", &first_original_number))
	{
		scanf("%*[^\n]");
		printf("Пожалуйста, введите одно число!\n");
	}
	printf("\033[A\33[2K\r");
	Checking_the_number(first_original_number, number_type);
	for (int i = 0; i < Digits_max; i++)
	{
		first_original_number_array[Digits_max - 1 - i] = first_original_number % 10;
		first_original_number /= 10;
	}

	printf("%s, введите задуманное вами число так, чтобы %s не увидел: ", second_player, first_player);
	while (!scanf("%d", &second_original_number))
	{
		scanf("%*[^\n]");
		printf("Пожалуйста, введите одно число!\n");
	}
	printf("\033[A\33[2K\r");
	Checking_the_number(second_original_number, number_type);
	for (int i = 0; i < Digits_max; i++)
	{
		second_original_number_array[Digits_max - 1 - i] = second_original_number % 10;
		second_original_number /= 10;
	}

	do
	{
		game_end = Move_of_the_player (second_original_number_array, first_player, move_of_the_first_player);
		if (game_end == 0) game_end = Move_of_the_player(first_original_number_array, second_player, move_of_the_second_player);
		else winner = 1;
	} while (game_end == 0);

	if (winner == 2) Winner(first_original_number_array, second_player);
	else Winner(second_original_number_array, first_player);
}

void Checking_the_number (int &number, int number_type)
{
	int number_to_check;
	int array_to_check[Digits_max];
	bool conditions;

	do
	{
		conditions = true;
		number_to_check = number;

		if ((number_to_check < 1000) || (number_to_check > 9999)) conditions = false;
		else
		{
			for (int i = 0; i < Digits_max; i++)
			{
				array_to_check[Digits_max - 1 - i] = number_to_check % 10;
				number_to_check /= 10;
			}
			for (int i = 0; i < Digits_max; i++)
			{
				for (int j = i + 1; j < Digits_max; j++)
				{
					if (array_to_check[i] == array_to_check[j]) conditions = false;
				}
			}
		}
		if ((conditions == false) && (number_type == 1))
		{
			printf("Введённое вами число не сооветствует требуемым правилам игры. Пожалуйста, повторите попытку: ");
			while (!scanf("%d", &number))
			{
				scanf("%*[^\n]");
				printf("Пожалуйста, введите одно число!\n");
			}
			printf("\033[A\33[2K\r");
		}
		if ((conditions == false) && (number_type == 2))
		{
			printf("Ошибка! Пожалуйста, повторите попытку: ");
			while (!scanf("%d", &number))
			{
				scanf("%*[^\n]");
				printf("Пожалуйста, введите одно число!\n");
			}
		}
	} while (conditions == false);
}

int Move_of_the_player(int *original_number_array, char *name, int &move_of_the_player)
{
	int attempt, bulls = 0, cows = 0, number_type = 2;
	int attempt_array[Digits_max];

	move_of_the_player += 1;

	printf("%s делает свой %d-й ход: ", name, move_of_the_player);
	while (!scanf("%d", &attempt))
	{
		scanf("%*[^\n]");
		printf("Пожалуйста, введите одно число!\n");
	}
	Checking_the_number(attempt, number_type);

	for (int i = 0; i < Digits_max; i++)
	{
		attempt_array[Digits_max - 1 - i] = attempt % 10;
		attempt /= 10;
	}

	for (int i = 0; i < Digits_max; i++) if (original_number_array[i] == attempt_array[i]) bulls += 1;
	for (int i = 0; i < Digits_max; i++) for (int j = 0; j < Digits_max; j++) if ((original_number_array[i] == attempt_array[j]) && (i != j)) cows += 1;

	printf("Количество быков: %d. Количество коров: %d.\n", bulls, cows);

	if (bulls == 4) return 1;
	return 0;
}

int Move_of_the_computer(int *fit_or_not, int *unused_digits, int all_possible_values[][Digits_max], int &move_of_the_computer, int &guessed_number, int &values)
{
	int attempt, glass, sum, counter, bulls = 0, cows = 0;

	move_of_the_computer += 1;

	printf("Компьютер делает свой %d ход: ", move_of_the_computer);
	do
	{
		srand(time(NULL));
		attempt = rand() % ((values - 1) - 0 + 1) + 0;
	} while (fit_or_not[attempt] != 1);
	for (int i = 0; i < Digits_max; i++) printf("%d", all_possible_values[attempt][i]);
	printf("\n");

	printf("Какое количество быков и коров содержится в названном компьютером числе? ");
	if (move_of_the_computer == 1) printf("\n(вводите только два числа - количество быков, а затем количество коров) ");
	do
	{
		while (!scanf("%d %d", &bulls, &cows))
		{
			scanf("%*[^\n]");
			printf("Пожалуйста, введите два числа!\n");
		}
		if ((bulls < 0) || (bulls > 4) || (cows < 0) || (cows > 4) || (bulls + cows > 4)) printf("Ошибка! Пожалуйста, проверьте правильность введённых вами значений и попробуйте ввести числа ещё раз: ");
	} while ((bulls < 0) || (bulls > 4) || (cows < 0) || (cows > 4) || (bulls + cows > 4));

	if (bulls == 4)
	{
		for (int i = 0; i < Digits_max; i++) guessed_number = guessed_number * 10 + all_possible_values[attempt][i];
		return 1;
	}
	
	if ((bulls + cows == 4) || (bulls + cows == 0))
	{
		if ((bulls + cows == 4))
		{
			for (int i = 0; i < Digits_max; i++)
			{
				unused_digits[all_possible_values[attempt][i]] = 1;
			}
			for (int i = 0; i < Digits; i++) if (unused_digits[i] == -1) unused_digits[i] = 0;
		}
		else
		{
			for (int i = 0; i < Digits_max; i++)
			{
				unused_digits[all_possible_values[attempt][i]] = 0;
			}
		}

		for (int digit = 0; digit < Digits; digit++)
		{
			if (unused_digits[digit] == 0)
			{
				for (int i = 0; i < values; i++)
				{
					if (fit_or_not[i] == 1)
					{
						for (int j = 0; j < Digits_max; j++)
						{
							if (all_possible_values[i][j] == digit) fit_or_not[i] = 0;
						}
					}
				}
			}
		}

		for (int i = 0; i < Values_max; i++)
		{
			if (fit_or_not[i] == 0)
			{
				counter = 0;
				for (int j = i + 1; j < Values_max; j++)
				{
					if ((fit_or_not[j] == 1) && (counter == 0))
					{
						fit_or_not[i] = 1;
						fit_or_not[j] = 0;
						for (int digit = 0; digit < Digits_max; digit++)
						{
							glass = all_possible_values[i][digit];
							all_possible_values[i][digit] = all_possible_values[j][digit];
							all_possible_values[j][digit] = glass;
						}
						counter += 1;
					}
				}
			}
		}

		sum = 0;
		for (int i = 0; i < Values_max; i++) sum += fit_or_not[i];
		values = sum;
	}
	
	return 0;
}

void Winner(int* original_number_array, char* name)
{
	int original_number = 0;

	for (int i = 0; i < Digits_max; i++) original_number = original_number * 10 + original_number_array[i];

	printf("\n");
	printf("\t\t\t\t@@@@@   @@@   @@@@@  @@@@@    @@      @@    @\n");
	printf("\t\t\t\t@   @  @   @  @      @       @  @    @  @   @\n");
	printf("\t\t\t\t@   @  @   @  @@@@   @@@@@   @  @    @@@@   @\n");
	printf("\t\t\t\t@   @  @   @  @   @  @      @@@@@@  @    @   \n");
	printf("\t\t\t\t@   @   @@@   @@@@   @@@@@  @    @  @    @  @\n");
	printf("\n\t\t\t\t%s одержал(а) победу в игре, отгадав число %d!\n\n\n", name, original_number);
}

void Loser(int guessed_number)
{
	printf("\n");
	printf("\t\t\t@@@@@   @@@   @@@@@    @@    @ @ @  @@@@@  @   @  @   @  @@@@@  @\n");
	printf("\t\t\t@   @  @   @  @   @   @  @   @ @ @  @      @   @  @  @@  @      @\n");
	printf("\t\t\t@   @  @   @  @@@@@   @@@@    @@@   @@@@@  @@@@@  @ @ @  @@@@@  @\n");
	printf("\t\t\t@   @  @   @  @      @    @  @ @ @  @      @   @  @@  @  @       \n");
	printf("\t\t\t@   @   @@@   @      @    @  @ @ @  @@@@@  @   @  @   @  @@@@@  @\n");
	printf("\n\t\t\t\tКомпьютер смог отгадать задуманное вами число %d.\n\n\n", guessed_number);
}