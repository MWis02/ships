#pragma once
#include <iostream>


class resources
{
private:

	int gamespace[10][10]; //ustawienie pola gry
	int check_shot(int x, int y) const; //sprawdzenie gdzie trafi³ nasz strza³
	
public:
	resources();
	resources(const resources& other);
	resources& operator = (const resources& other);
	int(&reviev())[10][10]; //podgl¹d tablicy
	int cordsX_to_numbers(const char* x); //zmiana koordynatów X na dane zgodne z tablicami
	int cordsY_to_numbers(int y); //zmiana koordynatów Y na dane zgodne z tablicami
	const char* cordsX_for_Bot(int x); //zmiana koordynat liczbowych na wskaŸnik dla bota
	void set_to_defaults(); //funkcja przywracajaca tablice do wartosci podstawowych
	void set_gamespace(const char* x, int y, int value); //funkcja do ustawiania statków
	void set_gamespace_after_shoot(const char* x, int y, int value); //funkcja do zmienienia tablicy po wykonaniu ruchu
	bool test_correct_positioning(int x, int y, int x1, int y1); //sprawdzenie czy podane koordynaty statków 2 masztowych s¹ zgodne z zasadami gry 
	bool check_the_ships(int x, int y); //sprawdzenie czy trafiony statek nie zosta³ zatopiony
};
