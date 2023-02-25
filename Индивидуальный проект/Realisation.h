#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#define Digits_max 4


void Game_Mode_1();
void Game_Mode_2();
void Checking_the_number (int &number, int number_type);
int Move_of_the_player (int *original_number_array, char *name, int &move_of_the_player);
int Move_of_the_computer(int *fit_or_not, int *unused_digits, int all_possible_values[][Digits_max], int &move_of_the_computer, int &guessed_number, int &values);
void Winner (int *original_number_array, char *name);
void Loser(int guessed_number);