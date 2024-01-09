#pragma once
#include <ctime>

class ScoreBoard
{
private:

public:
	ScoreBoard();

	int game_time;
	int score_at_end;
	int calculate_points(int moves);

	struct tm {
		int tm_mday; /*Dzieñ miesi¹ca 1-31*/
		int tm_mon; /*Numer miesi¹ca od 0-11*/
		int tm_year; /*Rok od 1900*/
	};
};

