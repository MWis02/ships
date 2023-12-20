#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent),
	Resources(new resources)
{   
    ui.setupUi(this);
	ui.widget_GS->hide();
	ui.widget_blank->hide();
	initialize_Border();
}

MainWindow::~MainWindow()
{
	delete Resources;
}

void MainWindow::on_pushButton_Ch_1_clicked() {
	ui.widget_title->hide();
	ui.widget_GS->show();
	ui.pushButton_14->hide();
	resetGame();
}

void MainWindow::on_pushButton_Ch_2_clicked() {
	ui.widget_title->hide();
	ui.widget_GS->show();
	ui.pushButton_14->show();
	resetGame();
}

void MainWindow::on_pushButton_clicked() {
	ui.widget_GS->hide();
	ui.widget_title->show();
	return;
}

void MainWindow::on_pushButton_2_clicked() {
	QApplication::quit();
	return;
}

void MainWindow::on_pushButton_3_clicked() {
	if (count == 0) {
		Player_1 = new resources(*Resources);
		cords_for_bot();
		Bot = new resources(*Resources);
	}
	else {
		Player_2 = new resources(*Resources);
	}
	return;
}

void MainWindow::on_pushButton_4_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_1->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");


	QString x1 = CordsParts_1.at(0); /*Pobranie pierwszej wartoœci od u¿ytkownika*/
	string X1 = x1.toStdString(); /*zmiana Qstring na string*/
	int Y1 = CordsParts_1.at(1).toInt(); /*Pobranie drugiej wartoœci od u¿ytkownika */

	int X_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y1);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);
	if (flag and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X1.c_str(), Y1, 1); /*X.c_str() wy³uskanie wskaŸnika "const char*"*/
		ui.pushButton_4->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_5_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_2->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x = CordsParts_1.at(i);
	string X = x.toStdString();
	int Y = CordsParts_1.at(i + 1).toInt();

	int X_tmp = Resources->cordsX_to_numbers(X.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);

	if (flag and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X.c_str(), Y, 1);
		ui.pushButton_5->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_6_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_3->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x = CordsParts_1.at(i);
	string X = x.toStdString();
	int Y = CordsParts_1.at(i + 1).toInt();

	int X_tmp = Resources->cordsX_to_numbers(X.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);
	if (flag and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X.c_str(), Y, 1);
		ui.pushButton_6->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_7_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_4->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x = CordsParts_1.at(i);
	string X = x.toStdString();
	int Y = CordsParts_1.at(i + 1).toInt();

	int X_tmp = Resources->cordsX_to_numbers(X.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);
	if (flag and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X.c_str(), Y, 1);
		ui.pushButton_7->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_8_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_5->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(i);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(i + 1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_6->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(i);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(i + 1).toInt();

	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp, 2);
	bool flag_1 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_2 = Resources->check_the_ships(X2_tmp, Y2_tmp);

	if (flag and flag_1 and flag_2) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		ui.pushButton_8->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_9_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_7->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(i);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(i + 1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_8->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(i);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(i + 1).toInt();

	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);


	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp, 2);
	bool flag_1 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_2 = Resources->check_the_ships(X2_tmp, Y2_tmp);

	if (flag and flag_1 and flag_2) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		ui.pushButton_9->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_10_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_9->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(i);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(i + 1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_10->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(i);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(i + 1).toInt();

	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp, 2);
	bool flag_1 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_2 = Resources->check_the_ships(X2_tmp, Y2_tmp);

	if (flag and flag_1 and flag_2) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		ui.pushButton_10->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_11_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_11->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(i);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(i + 1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_12->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(i);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(i + 1).toInt();

	CordsFromPlayer_3 = ui.lineEdit_13->text();
	CordsParts_3 = CordsFromPlayer_3.split(",");

	QString x3 = CordsParts_3.at(i);
	string X3 = x3.toStdString();
	int Y3 = CordsParts_3.at(i + 1).toInt();

	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int X3_tmp = Resources->cordsX_to_numbers(X3.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);
	int Y3_tmp = Resources->cordsY_to_numbers(Y3);

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp, 2);
	bool flag_1 = Resources->test_correct_positioning(X2_tmp, Y2_tmp, X3_tmp, Y3_tmp, 2);
	bool flag_5 = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X3_tmp, Y3_tmp, 3);
	bool flag_2 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_3 = Resources->check_the_ships(X2_tmp, Y2_tmp);
	bool flag_4 = Resources->check_the_ships(X3_tmp, Y3_tmp);

	if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		Resources->set_gamespace(X3.c_str(), Y3, 1);
		ui.pushButton_11->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y3_tmp][X3_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_12_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_14->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(i);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(i + 1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_15->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(i);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(i + 1).toInt();

	CordsFromPlayer_3 = ui.lineEdit_16->text();
	CordsParts_3 = CordsFromPlayer_3.split(",");

	QString x3 = CordsParts_3.at(i);
	string X3 = x3.toStdString();
	int Y3 = CordsParts_3.at(i + 1).toInt();

	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int X3_tmp = Resources->cordsX_to_numbers(X3.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);
	int Y3_tmp = Resources->cordsY_to_numbers(Y3);

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp, 2);
	bool flag_1 = Resources->test_correct_positioning(X2_tmp, Y2_tmp, X3_tmp, Y3_tmp, 2);
	bool flag_5 = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X3_tmp, Y3_tmp, 3);
	bool flag_2 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_3 = Resources->check_the_ships(X2_tmp, Y2_tmp);
	bool flag_4 = Resources->check_the_ships(X3_tmp, Y3_tmp);

	if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		Resources->set_gamespace(X3.c_str(), Y3, 1);
		ui.pushButton_12->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y3_tmp][X3_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_13_clicked() {

	CordsFromPlayer_1 = ui.lineEdit_17->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(i);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(i + 1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_18->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(i);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(i + 1).toInt();

	CordsFromPlayer_3 = ui.lineEdit_19->text();
	CordsParts_3 = CordsFromPlayer_3.split(",");

	QString x3 = CordsParts_3.at(i);
	string X3 = x3.toStdString();
	int Y3 = CordsParts_3.at(i + 1).toInt();

	CordsFromPlayer_4 = ui.lineEdit_20->text();
	CordsParts_4 = CordsFromPlayer_4.split(",");

	QString x4 = CordsParts_4.at(i);
	string X4 = x4.toStdString();
	int Y4 = CordsParts_4.at(i + 1).toInt();

	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int X3_tmp = Resources->cordsX_to_numbers(X3.c_str());
	int X4_tmp = Resources->cordsX_to_numbers(X4.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);
	int Y3_tmp = Resources->cordsY_to_numbers(Y3);
	int Y4_tmp = Resources->cordsY_to_numbers(Y4);

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp, 2);
	bool flag_1 = Resources->test_correct_positioning(X2_tmp, Y2_tmp, X3_tmp, Y3_tmp, 2);
	bool flag_2 = Resources->test_correct_positioning(X3_tmp, Y3_tmp, X4_tmp, Y4_tmp, 2);
	bool flag_7 = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X4_tmp, Y4_tmp, 4);
	bool flag_3 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_4 = Resources->check_the_ships(X2_tmp, Y2_tmp);
	bool flag_5 = Resources->check_the_ships(X3_tmp, Y3_tmp);
	bool flag_6 = Resources->check_the_ships(X4_tmp, Y4_tmp);
	

	if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5 and flag_6 and flag_7) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		Resources->set_gamespace(X3.c_str(), Y3, 1);
		Resources->set_gamespace(X4.c_str(), Y4, 1);
		ui.pushButton_13->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y3_tmp][X3_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y4_tmp][X4_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_14_clicked() {
	//ui.pushButton_14->setDisabled(true);
	Player_1 = new resources(*Resources);
	count = 1;
	resetGame();
}

void MainWindow::initialize_Border() {
	for (int i = 0; i < 10; i++) {
		QVector<QLabel*> columnLabel;
		for (int j = 0; j < 10; j++) {
			QString Label_N = "GS_" + QString::number(j) + QString::number(i);
			QLabel* Label_S = findChild<QLabel*>(Label_N);

			columnLabel.push_back(Label_S);
		}
		Board_Vector.push_back(columnLabel);
	}
	return;
}

void MainWindow::resetGame() {
	/*Resetowanie planszy*/
	Resources->set_to_defaults();

	/*Resetowanie przycisków*/
	ui.pushButton_4->setEnabled(true);
	ui.pushButton_5->setEnabled(true);
	ui.pushButton_6->setEnabled(true);
	ui.pushButton_7->setEnabled(true);
	ui.pushButton_8->setEnabled(true);
	ui.pushButton_9->setEnabled(true);
	ui.pushButton_10->setEnabled(true);
	ui.pushButton_11->setEnabled(true);
	ui.pushButton_12->setEnabled(true);
	ui.pushButton_13->setEnabled(true);

	/*Resetowanie pól*/
	ui.lineEdit_1->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.lineEdit_4->clear();
	ui.lineEdit_5->clear();
	ui.lineEdit_6->clear();
	ui.lineEdit_7->clear();
	ui.lineEdit_8->clear();
	ui.lineEdit_9->clear();
	ui.lineEdit_10->clear();
	ui.lineEdit_11->clear();
	ui.lineEdit_12->clear();
	ui.lineEdit_13->clear();
	ui.lineEdit_14->clear();
	ui.lineEdit_15->clear();
	ui.lineEdit_16->clear();
	ui.lineEdit_17->clear();
	ui.lineEdit_18->clear();
	ui.lineEdit_19->clear();
	ui.lineEdit_20->clear();

	/*Resetowanie t³a dla pokazania statków*/
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Board_Vector[j][i]->setStyleSheet("");
		}
	}
}

void MainWindow::cords_for_bot() {
	Resources->set_to_defaults();
	srand(time(NULL));

	for (int i = 0; i < 4; ) {
		int X = rand() % 10;
		int Y = rand() % 10;

		bool flag = Resources->check_the_ships(X, Y);
		if (flag) {
			const char* tmp = Resources->cordsX_for_Bot(X);
			if (Resources->check_cord_for_Bot(Y, X) == 0) {
				Resources->set_gamespace(tmp, Y, 1);
				i += 1;
			}
		}
	}
	for (int i = 0; i < 3; ) {
		int X1 = rand() % 10;
		int Y1 = rand() % 10; 
		int X2 = rand() % 10;
		int Y2 = rand() % 10;

		bool flag = Resources->check_the_ships(X1, Y1);
		bool flag_1 = Resources->check_the_ships(X2, Y2);
		bool flag_2 = Resources->test_correct_positioning(X1, Y1, X2, Y2, 2);

		if (flag and flag_1 and flag_2) {
			const char* tmp = Resources->cordsX_for_Bot(X1);
			const char* tmp_1 = Resources->cordsX_for_Bot(X2);

			if (Resources->check_cord_for_Bot(Y1, X1) == 0 and Resources->check_cord_for_Bot(Y2, X2) == 0) {
				Resources->set_gamespace(tmp, Y1, 1);
				Resources->set_gamespace(tmp_1, Y2, 1);
				i += 1;
			}
		}
	}
	for (int i = 0; i < 2; ) {
		int X1 = rand() % 10;
		int Y1 = rand() % 10;
		int X2 = rand() % 10;
		int Y2 = rand() % 10;
		int X3 = rand() % 10;
		int Y3 = rand() % 10;

		bool flag = Resources->check_the_ships(X1, Y1);
		bool flag_1 = Resources->check_the_ships(X2, Y2);
		bool flag_2 = Resources->check_the_ships(X3, Y3);
		bool flag_3 = Resources->test_correct_positioning(X1, Y1, X2, Y2, 3);
		bool flag_4 = Resources->test_correct_positioning(X2, Y2, X3, Y3, 3);
		bool flag_5 = Resources->test_correct_positioning(X1, Y1, X3, Y3, 3);

		if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5) {
			const char* tmp = Resources->cordsX_for_Bot(X1);
			const char* tmp_1 = Resources->cordsX_for_Bot(X2);
			const char* tmp_2 = Resources->cordsX_for_Bot(X3);

			if (Resources->check_cord_for_Bot(Y1, X1) == 0 and Resources->check_cord_for_Bot(Y2, X2) == 0 and Resources->check_cord_for_Bot(Y3, X3) == 0) {
				Resources->set_gamespace(tmp, Y1, 1);
				Resources->set_gamespace(tmp_1, Y2, 1);
				Resources->set_gamespace(tmp_2, Y3, 1);
				i += 1;
			}
		}
	}
	for (int i = 0; i < 1; ) {
		int X1 = rand() % 10;
		int Y1 = rand() % 10;
		int X2 = rand() % 10;
		int Y2 = rand() % 10;
		int X3 = rand() % 10;
		int Y3 = rand() % 10;
		int X4 = rand() % 10;
		int Y4 = rand() % 10;

		bool flag = Resources->check_the_ships(X1, Y1);
		bool flag_1 = Resources->check_the_ships(X2, Y2);
		bool flag_2 = Resources->check_the_ships(X3, Y3);
		bool flag_3 = Resources->check_the_ships(X4, Y4);
		bool flag_4 = Resources->test_correct_positioning(X1, Y1, X2, Y2, 4);
		bool flag_5 = Resources->test_correct_positioning(X2, Y2, X3, Y3, 4);
		bool flag_6 = Resources->test_correct_positioning(X3, Y3, X4, Y4, 4);
		bool flag_7 = Resources->test_correct_positioning(X1, Y1, X4, Y4, 4);

		if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5 and flag_6 and flag_7) {
			const char* tmp = Resources->cordsX_for_Bot(X1);
			const char* tmp_1 = Resources->cordsX_for_Bot(X2);
			const char* tmp_2 = Resources->cordsX_for_Bot(X3);
			const char* tmp_3 = Resources->cordsX_for_Bot(X4);

			if (Resources->check_cord_for_Bot(Y1, X1) == 0 and Resources->check_cord_for_Bot(Y2, X2) == 0 and Resources->check_cord_for_Bot(Y3, X3) == 0 and Resources->check_cord_for_Bot(Y4, X4) == 0) {
				Resources->set_gamespace(tmp, Y1, 1);
				Resources->set_gamespace(tmp_1, Y2, 1);
				Resources->set_gamespace(tmp_2, Y3, 1);
				Resources->set_gamespace(tmp_3, Y4, 1);
				i += 1;
			}
		}
	}
	return;
}