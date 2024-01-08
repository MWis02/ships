#pragma once
#include <iostream>
#include <string>


class resources
{
private:
	int gamespace[10][10]; //ustawienie pola gry

public:
	resources();
	resources(const resources& other);
	resources& operator = (const resources& other);
	int(&reviev())[10][10]; //podgl¹d tablicy
	int cordsX_to_numbers(const char* x); //zmiana koordynatów X na dane zgodne z tablicami
	int cordsY_to_numbers(int y); //zmiana koordynatów Y na dane zgodne z tablicami
	const char* cordsX_for_Bot(int x); //zmiana koordynat liczbowych na wskaŸnik dla bota
	void set_to_defaults(); //funkcja przywracajaca tablice do wartosci podstawowych
	void set_gamespace(const char* x, int y, int value, int pointer); //funkcja do ustawiania statków
	void set_gamespace_after_shoot(int x, int y, int value); //funkcja do zmienienia tablicy po wykonaniu ruchu
	bool check_for_other_ships(int x, int y); //funkcja sprawdzaj¹ca czy strafiony statek jest wiecej niz jedno masztowy
	bool test_correct_positioning(int x, int y, int x1, int y1, int height); //sprawdzenie czy podane koordynaty statków 2 masztowych s¹ zgodne z zasadami gry
	bool check_the_ships(int x, int y); //sprawdzenie czy statek mo¿e zostaæ postawiony w danym miejscu
	int check_cord_for_Bot(int x, int y); //sprawdzenie czy mo¿e byæ ustawiony statek dla bota
	int check_shot(int x, int y) const; //sprawdzenie gdzie trafi³ nasz strza³
	int counter;
	//string name;
};
