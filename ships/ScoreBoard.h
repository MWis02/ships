#pragma once
#include <ctime>
#include <string>
#include <QTimer>
#include <fstream>

using namespace std;

class ScoreBoard : public QObject
{
	Q_OBJECT;

private:
	int sec, min, game_time, score_at_end;
public:
	ScoreBoard();

	int calculate_points(int moves);
	void Start_time();
	void Stop_time();
	int Return_time();
	void Update_time();
	QTimer* timer;
	string name;

	struct tm {
		int tm_mday; /*Dzieñ miesi¹ca 1-31*/
		int tm_mon; /*Numer miesi¹ca od 0-11*/
		int tm_year; /*Rok od 1900*/
	};
};

