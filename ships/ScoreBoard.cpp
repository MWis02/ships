#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() : 
	timer(new QTimer){
	game_time = 0;
	score_at_end = 0;
	sec = 0;
	min = 0;
	game_time = 0;

	connect(timer, &QTimer::timeout, this, &ScoreBoard::Update_time);
}

int ScoreBoard::calculate_points(int moves) {
	if (moves == 20) {
		score_at_end = 10000;
	}
	else if (moves > 20 and moves < 36) {
		score_at_end += 10000 - (moves * game_time) / 6;
	}
	else if (moves >= 36 and moves < 56) {
		score_at_end += 10000 - (moves * game_time) / 4;
	}
	else if (moves >= 56 and moves < 99)
	{
		score_at_end += 10000 - (moves * game_time) / 2;
	}
	else return 0;

	time_t timenow = time(nullptr);
	tm* data = localtime(&timenow);

	int mon = data->tm_mon += 1;
	int day = data->tm_mday;
	int year = data->tm_year + 1900;
	fstream plik;
	plik.open("Data.txt", ios::out | ios::app);
	if (plik.good() == true) {
		plik << "Gracz: " + name +
			"\n -zdobyte punkty: " + to_string(score_at_end) +
			"\n -Liczba ruchów: " + to_string(moves) +
			"\n -Data: " + to_string(day) + "-" + to_string(mon) + "-" + to_string(year) +
			"\n -Czas rozgrywki: " + to_string(min) + " min " + to_string(sec) + " sec"
			<< endl;
		plik.close();
	}
	return score_at_end;
}

void ScoreBoard::Start_time() {
	sec = 0;
	timer->start(1000);
}

void ScoreBoard::Stop_time() {
	timer->stop();
}

void ScoreBoard::Update_time() {
	sec += 1;
	game_time = sec;
	if (sec == 60) {
		min += 1;
		sec = 0;
	}
}