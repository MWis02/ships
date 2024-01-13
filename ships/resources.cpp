
#include "resources.h"

resources::resources() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			gamespace[i][j] = 0;
	}
	counter = 0;
}
resources::~resources() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			gamespace[i][j] = 0;
	}
	counter = 0;
}

resources::resources(const resources& other) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			this->gamespace[j][i] = other.gamespace[j][i];
	}
	this->counter = other.counter;
}

void resources::set_to_defaults()/*Wyzerowanie wartoœci w tablicy*/ {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			gamespace[i][j] = 0;
		}
	}
	return;
}
 
void resources::set_gamespace(const char* x, int y, int value, int pointer)/*funkcja s³u¿aca do ustawiania koordynat*/ {
	if (pointer == 1) {
		int x1 = cordsX_to_numbers(x);
		int y1 = cordsY_to_numbers(y);
		if (x1 == -1 or y1 == -1) {
			return;
		}
		gamespace[y1][x1] = value;
	}
	else if (pointer == 2)
	{
		int x1 = cordsX_to_numbers(x);
		gamespace[y][x1] = value;
	}
	return;
}

void resources::set_gamespace_after_shoot(int x, int y, int value)/*Ustawienie tablicy wartoœci po strzale*/ {
	gamespace[y][x] = value;
}

int resources::check_shot(int x, int y) const/*Funkcja sprawdzaj¹ca czy strza³ zosta³ trafiony*/ {
	if (gamespace[y][x] == 0) {
		return 0; //pustê miejsce 
	}
	else if (gamespace[y][x] == 1) {
		return 1; //statek  
	}
	else if (gamespace[y][x] == 2) {
		return 2; //trafione puste miejsce
	}
	else if (gamespace[y][x] == 3) {
		return 3; //trafiony statek
	}
	return -1;
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
}

const char* resources::cordsX_for_Bot(int x)/*Funkcja zmieniaj¹ca wartoœæ koordynat Y, na liczby zgodne z tablic¹*/ 
{	
	const char* Char;
	switch (x)
	{
	case 0:
		Char = "A";
		break;
	case 1:
		Char = "B";
		break;
	case 2:
		Char = "C";
		break;
	case 3:
		Char = "D";
		break;
	case 4:
		Char = "E";
		break;
	case 5:
		Char = "F";
		break;
	case 6:
		Char = "G";
		break;
	case 7:
		Char = "H";
		break;
	case 8:
		Char = "I";
		break;
	case 9:
		Char = "J";
		break;
	}
	return Char;
}

bool resources :: check_the_ships(int x, int y)/*Funkcja sprawdzaj¹ca czy statek mo¿e zostaæ ustawiony w danym miejscu*/ {
	/*pêtla iteruje po komorkach 1 w gore, i w dó³ od podanych koordyntów, 
	w celu sprawdzenia czy na s¹siaduj¹cych polach znajduje siê statek*/
	for (int i = max(0, x - 1); i <= min(9, x + 1); ++i)/*max(...), min(...) unikniecie wyjscia poza tablicê*/ {
		for (int j = max(0, y - 1); j <= min(9, y + 1); ++j) {
			if (gamespace[j][i] == 1) {
				return false;  //Statek jest obecny w otaczaj¹cych komórkach
			}
		}
	}
	return true;  //Brak statku w otaczaj¹cych komórkach
}

bool resources :: test_correct_positioning(int x, int y, int x1, int y1, int height)/*funkcja sprawdzj¹ca poprawnoœæ wpisywanych koordynat*/ {
	if (y == -1 or y1 == -1 or x == -1 or x1 == -1) {
		return false;
	}
	if (x == x1) {
		int y_diff = abs(y - y1);
		if (height == 2 and y_diff == 1) return true;
		if (height == 3 and y_diff == 2) return true;
		if (height == 4 and y_diff == 3) return true;
		if (y == y1) return false;
	}
	else if (y == y1) {
		int x_diff = abs(x - x1);
		if (height == 2 and x_diff == 1) return true;
		if (height == 3 and x_diff == 2) return true;
		if (height == 4 and x_diff == 3) return true;
		if (x == x1) return false;
	}
	return false;
}

int resources::check_cord_for_Bot(int x, int y) {
	if (gamespace[y][x] == 0) {
		return 0; //pustê miejsce 
	}
	else if (gamespace[y][x] == 1) {
		return 1; //statek  
	}
}