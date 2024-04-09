#include "ScoreWidget.h"

ScoreWidget::ScoreWidget(QWidget *parent)
	: QMainWindow(parent),
	mysql(new MySQL)
{
	ui.setupUi(this);
	text = "";
}

ScoreWidget::~ScoreWidget() {
	delete mysql;
	ui.textBrowser->clear();
	text = "";
}

void ScoreWidget::read_data() {
	// Pobranie wyników z bazy danych
	ResultSet* res = mysql->return_score();

	// Tworzenie tekstu do wypisania
	QString output;

	int i = 1;
	
	// Przetwarzanie wyników zapytania
	while (res->next()) {
		// Pobranie wartości z kolumn
		QString column1 = QString::fromStdString(res->getString(1));
		QString column2 = QString::fromStdString(res->getString(2));
		QString column3 = QString::fromStdString(res->getString(3));
		QString column4 = QString::fromStdString(res->getString(4));
		QString column5 = QString::fromStdString(res->getString(5));

		// Dodanie wyniku do tekstu wyjściowego
		output += QString::number(i) + ". Gracz: " + column1 + "\n -zdobyte punkty: " + column2 + "\n -Liczba ruchów: " + column3 + "\n -Data: " + column5 + "\n -Czas rozgrywki: " + column4 + "\n\n";
		i++;
	}

	// Wstawienie tekstu do textBrowser
	ui.textBrowser->setText(output);


}