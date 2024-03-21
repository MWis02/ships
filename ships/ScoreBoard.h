#pragma once
#include <ctime>
#include <string>
#include <QTimer>
#include <fstream>
#include <QString>
#include "MySQL.h"

using namespace std;


class ScoreBoard : public QObject
{
	Q_OBJECT;

private:
	int sec, min, game_time, score_at_end;
	MySQL* mysql;
public:
	ScoreBoard();
	~ScoreBoard();
	int calculate_points(int moves);
	void Start_time();
	void Stop_time();
	void Update_time();
	QTimer* timer;
	string name;
};

