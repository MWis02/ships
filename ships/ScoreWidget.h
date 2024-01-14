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
	void read_data();

private:
	Ui::ScoreWidgetClass ui;
	string text;
};
