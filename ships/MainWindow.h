#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "resources.h"
#include "ScoreBoard.h"
#include "ScoreWidget.h"
#include <vector>
#include <string>
#include <QVector>
#include <QButtonGroup>
#include <QLabel>
#include <QlineEdit>
#include <QpushButton>
#include <QSignalMapper>
#include <Qtimer>

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui:: MainWindow ui;
	resources* Resources;
	resources* Player_1;
	resources* Player_2;
	resources* Bot;
	ScoreBoard* score;
	QTimer* BotShot;
	QTimer* Delay;
	ScoreWidget* widget;
	QButtonGroup* radiogroup;
	int count, x, y, shot, shot_1, BotX, BotY;
	QLocale polishLng;
	int LastHitX, LastHitY, botcounter;
	int check_choise;
	bool lastShotHit;
	vector<pair<int, int >> vector_for_fields;
	string name_for_first_player;
	string name_for_second_player;
	int score_at_end;

	/*Zmienne do pobrania koordynatow*/
	QString CordsFromPlayer_1;
	QStringList CordsParts_1;
	QString CordsFromPlayer_2;
	QStringList CordsParts_2;
	QString CordsFromPlayer_3;
	QStringList CordsParts_3;
	QString CordsFromPlayer_4;
	QStringList CordsParts_4;
	QVector<QVector<QLabel*>> Board_Vector; /*wektor do zwizualizowania planszy do gry*/
	QVector<QLineEdit*> LineEdits_Vector; /*wektor do podejrzenia wygenerowanej planszy do gry*/
	QVector<QVector<QLabel*>> Board_Vector_GP; /*wektor do zwizualizowania planszy do gry*/
	QVector<QVector<QPushButton*>> Buttons_Vector_GP; /*wektor do zwizualizowania planszy do gry*/
	QVector<QVector<QLabel*>> Board_Vector_GP_1; /*wektor do zwizualizowania planszy do gry*/
	QVector<QVector<QPushButton*>> Buttons_Vector_GP_1; /*wektor do zwizualizowania planszy do gry*/
	void initialize_Border();
	void initialize_Labels();
	void initialize_Border_GP();
	void initialize_Buttons_GP();
	void initialize_Border_GP_1();
	void initialize_Buttons_GP_1();
	void resetGame();
	void cords_for_bot();
	void gen_Ships_for_players();
	void shot_for_player();
	void shot_for_second_player();
	void shot_for_bot();
	vector<pair<int, int>> check_fields(int xCord, int yCord, resources* object);
	bool check_ships();

private slots:
	void on_pushButton_Ch_1_clicked(); /*jednoosobowa gra*/
	void on_pushButton_Ch_2_clicked(); /*dwuoosobowa gra*/
	void on_pushButton_TB_clicked(); /*dwuoosobowa gra*/
	void on_pushButton_NS_1_clicked(); /*powrót*/
	void on_pushButton_NS_2_clicked(); /*dalej*/
	void on_pushButton_EG_1_clicked(); /*Zagraj jeszcze raz*/
	void on_pushButton_EG_2_clicked(); /*Tablica wyników*/
	void on_pushButton_EG_3_clicked(); /*Zamknij*/
	void on_pushButton_clicked(); /*Powrót*/
	void on_pushButton_3_clicked(); /*Graj*/
	void on_pushButton_4_clicked(); /*statek 1_1*/
	void on_pushButton_5_clicked(); /*statek 2_1*/
	void on_pushButton_6_clicked(); /*statek 3_1*/
	void on_pushButton_7_clicked(); /*statek 4_1*/
	void on_pushButton_8_clicked(); /*statek 1_2*/
	void on_pushButton_9_clicked(); /*statek 2_2*/
	void on_pushButton_10_clicked(); /*statek 3_2*/
	void on_pushButton_11_clicked(); /*statek 1_3*/
	void on_pushButton_12_clicked(); /*statek 2_3 */
	void on_pushButton_13_clicked(); /*statek 1_4 */
	void on_pushButton_14_clicked(); /*dodanie 2 gracza*/
	void on_pushButton_gen_clicked(); /*generowanie randomowo staków*/
	void on_pushButton_res_clicked(); /*resetowanie ustawienia*/
};
