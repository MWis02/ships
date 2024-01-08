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
	int(&reviev())[10][10]; //podgl�d tablicy
	int cordsX_to_numbers(const char* x); //zmiana koordynat�w X na dane zgodne z tablicami
	int cordsY_to_numbers(int y); //zmiana koordynat�w Y na dane zgodne z tablicami
	const char* cordsX_for_Bot(int x); //zmiana koordynat liczbowych na wska�nik dla bota
	void set_to_defaults(); //funkcja przywracajaca tablice do wartosci podstawowych
	void set_gamespace(const char* x, int y, int value, int pointer); //funkcja do ustawiania statk�w
	void set_gamespace_after_shoot(int x, int y, int value); //funkcja do zmienienia tablicy po wykonaniu ruchu
	bool check_for_other_ships(int x, int y); //funkcja sprawdzaj�ca czy strafiony statek jest wiecej niz jedno masztowy
	bool test_correct_positioning(int x, int y, int x1, int y1, int height); //sprawdzenie czy podane koordynaty statk�w 2 masztowych s� zgodne z zasadami gry
	bool check_the_ships(int x, int y); //sprawdzenie czy statek mo�e zosta� postawiony w danym miejscu
	int check_cord_for_Bot(int x, int y); //sprawdzenie czy mo�e by� ustawiony statek dla bota
	int check_shot(int x, int y) const; //sprawdzenie gdzie trafi� nasz strza�
	int counter;
	//string name;
};
