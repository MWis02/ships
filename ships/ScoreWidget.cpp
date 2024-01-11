#include "ScoreWidget.h"

ScoreWidget::ScoreWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

ScoreWidget::~ScoreWidget()
{
	ui.textBrowser->clear();
	text = " ";
}

void ScoreWidget::read_data() {
	fstream file;
	file.open("Data.txt", ios::in);
	if (file.good()) {
		ui.textBrowser->clear();
		while (getline(file, text)) {
			ui.textBrowser->append(QString::fromStdString(text));
		}
	}
}