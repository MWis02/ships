#pragma once

#include <QMainWindow>
#include "ui_ScoreWidget.h"
#include <fstream>
#include <string> 

using namespace std;

class ScoreWidget : public QMainWindow
{
	Q_OBJECT

public:
	ScoreWidget(QWidget *parent = nullptr);
	~ScoreWidget();

private:
	Ui::ScoreWidgetClass ui;
	string text;

public:
	void read_data();
};
