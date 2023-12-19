#include "resources.h"

using namespace std;

resources::resources() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			gamespace[i][j] = 0;
	}
}

resources::resources(const resources& other) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			this->gamespace[j][i] = other.gamespace[j][i];
	}
}

void resources::set_to_defaults()/*Wyzerowanie wartoœci w tablicy*/ {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			gamespace[i][j] = 0;
		}
	}
	return;
}
 
void resources::set_gamespace(const char* x, int y, int value)/*funkcja s³u¿aca do ustawiania koordynat*/ {
	int x1 = cordsX_to_numbers(x);
	int y1 = cordsY_to_numbers(y);
	if (x1 == -1 || y1 == -1) {
		return;
	}
	gamespace[y1][x1] = value;
	return;
}

void resources::set_gamespace_after_shoot(const char* x, int y, int value)/*Ustawienie tablicy wartoœci po strzale*/ {

	int x1 = cordsX_to_numbers(x);
	int y1 = cordsY_to_numbers(y);

	int check_S = check_shot(x1, y1);

	switch (check_S)
	{
		case 0:
			set_gamespace(x, y, 3);
			break;
		case 1:
			set_gamespace(x, y, 2);
			break;
		case 2:
			set_gamespace(x, y, 2);
			break;
		default:
			break;
	}
}

int(&resources::reviev())[10][10]/*funkcja do sprawdzenia tablicy*/{
	return gamespace;
}

int resources::check_shot(int x, int y) const/*Funkcja sprawdzaj¹ca czy strza³ zosta³ trafiony*/ {
	if (gamespace[y][x] == 0) {
		return 0; //pustê miejsce 
	}
	else if (gamespace[y][x] == 1) {
		return 1; //statek  
	}
	else if (gamespace[y][x] == 2) {
		return 2; //trafiony statek
	}
	else if (gamespace[y][x] == 3) {
		return 3; //trafione puste pole
	}
}

int resources::cordsX_to_numbers(const char* x)/*Funkcja zmieniaj¹ca wartoœæ koordynat X, na liczby zgodne z tablic¹*/ {
	int x1 = 0;
	char value_of_x = *x;

	switch (value_of_x)
	{
	case 'A':
	case 'a':
		x1 = 0;
		break;

	case 'B':
	case 'b':
		x1 = 1;
		break;

	case 'C':
	case 'c':
		x1 = 2;
		break;

	case 'D':
	case 'd':
		x1 = 3;
		break;

	case 'E':
	case 'e':
		x1 = 4;
		break;

	case 'F':
	case 'f':
		x1 = 5;
		break;

	case 'G':
	case 'g':
		x1 = 6;
		break;

	case 'H':
	case 'h':
		x1 = 7;
		break;

	case 'I':
	case 'i':
		x1 = 8;
		break;
	case 'J':
	case 'j':
		x1 = 9;
		break;

	default:
		return x1 = -1;
		break;
	}

	return x1;
}

int resources::cordsY_to_numbers(int y)/*Funkcja zmieniaj¹ca wartoœæ koordynat Y, na liczby zgodne z tablic¹*/ {
	int value_of_y = y - 1;
	if (y >= 0 and y <= 10) return value_of_y;
	else return -1;

	/*int value_of_y = y;
	switch (value_of_y)
	{
	case 1:
		y = 0;
		break;
	case 2:
		y = 1;
		break;
	case 3:
		y = 2;
		break;
	case 4:
		y = 3;
		break;
	case 5:
		y = 4;
		break;
	case 6:
		y = 5;
		break;
	case 7:
		y = 6;
		break;
	case 8:
		y = 7;
		break;
	case 9:
		y = 8;
		break;
	case 10:
		y = 9;
		break;
	default:
		return y = -1;
		break;
	}
	return y;*/
}

bool resources :: check_the_ships(int x, int y)/*Funkcja sprawdzaj¹ca czy statek mo¿e zostaæ ustawiony w danym miejscu*/ {
	/*pêtla iteruje po komorkach 1 w gore, i w dó³ od podanych koordyntów, 
	w celu sprawdzenia czy na s¹siaduj¹cych polach znajduje siê statek*/
	for (int i = max(0, x - 1); i <= min(10, x + 1); ++i)/*max(...), min(...) unikniecie wyjscia poza tablicê*/ {
		for (int j = max(0, y - 1); j <= min(10, y + 1); ++j) {
			if (gamespace[j][i] == 1) {
				return false;  //Statek jest obecny w otaczaj¹cych komórkach
			}
		}
	}
	return true;  //Brak statku w otaczaj¹cych komórkach
}

bool resources :: test_correct_positioning(int x, int y, int x1, int y1)/*funkcja sprawdzj¹ca poprawnoœæ wpisywanych koordynat*/ {
	if (y == -1 or y1 == -1 or x == -1 or x1 == -1) {
		return false;
	}
	if (x == x1){
		if (y + 1 == y1 or y - 1 == y1) {
			return true; 
		}
	}
	else if (x + 1 == x1 or x == x1 + 1) {
		if (y == y1) {
			return true;
		}
	}
	return false;
}