#include "Game.h"

using namespace std;

Game::Game(QWidget* parent)
	: QMainWindow(parent),
	Resources(new resources), Player_1(new resources), Player_2(new resources), Bot(new resources),
	mainWindow(nullptr)
{
	ui.setupUi(this);
	initialize_Border();

}

Game::~Game()
{
	delete Resources;
}

void Game::on_pushButton_clicked() {
	mainWindow = new MainWindow;
	close();
	mainWindow->show();
	return;
}

void Game::on_pushButton_2_clicked() {
	QApplication::quit();
	return;
}

void Game::on_pushButton_3_clicked() {
	if (count == 1) {
		*Player_1 = *Resources;
		Resources->set_to_defaults();
		cords_for_bot();
		*Bot = *Resources;
		
	}
	else {
		if (clicks == 0) {
			*Player_1 = *Resources;
			resetGame();
		}
		else {
			*Player_2 = *Resources;
		}
		clicks += 1;
	}
	return;
}

void Game::on_pushButton_4_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_1->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(i); /*Pobranie pierwszej wartoœci od u¿ytkownika*/
	string X1 = x1.toStdString(); /*zmiana Qstring na string*/
	int Y1 = CordsParts_1.at(i + 1).toInt(); /*Pobranie drugiej wartoœci od u¿ytkownika */

	int X_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y1);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);
	if (flag == true and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X1.c_str(), Y1, 1); /*X.c_str() wy³uskanie wskaŸnika "const char*"*/
		ui.pushButton_4->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("Background-color: yellow;");
	}
	else return;
}

void Game::on_pushButton_5_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_2->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x = CordsParts_1.at(i);
	string X = x.toStdString();
	int Y = CordsParts_1.at(i + 1).toInt();

	int X_tmp = Resources->cordsX_to_numbers(X.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);

	if (flag == true and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X.c_str(), Y, 1);
		ui.pushButton_5->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("Background-color: yellow;");
	}
	else return;
}

void Game::on_pushButton_6_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_3->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x = CordsParts_1.at(i);
	string X = x.toStdString();
	int Y = CordsParts_1.at(i + 1).toInt();

	int X_tmp = Resources->cordsX_to_numbers(X.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);
	if (flag == true and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X.c_str(), Y, 1);
		ui.pushButton_6->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("Background-color: yellow;");
	}
	else return;
}

void Game::on_pushButton_7_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_4->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x = CordsParts_1.at(i);
	string X = x.toStdString();
	int Y = CordsParts_1.at(i + 1).toInt();

	int X_tmp = Resources->cordsX_to_numbers(X.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);
	if (flag == true and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X.c_str(), Y, 1);
		ui.pushButton_7->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("Background-color: yellow;");
	}
	else return;
}

void Game::on_pushButton_8_clicked() {
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

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp);
	bool flag_1 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_2 = Resources->check_the_ships(X2_tmp, Y2_tmp);

	if (flag == true and flag_1 == true and flag_2 == true) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		ui.pushButton_8->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("Background-color: yellow;");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("Background-color: yellow;");
	}
	else return;
}

void Game::on_pushButton_9_clicked() {
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


	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp);
	bool flag_1 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_2 = Resources->check_the_ships(X2_tmp, Y2_tmp);

	if (flag == true and flag_1 == true and flag_2 == true) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		ui.pushButton_9->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("Background-color: yellow;");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("Background-color: yellow;");
	}
	else return;
}

void Game::on_pushButton_10_clicked() {
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

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp);
	bool flag_1 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_2 = Resources->check_the_ships(X2_tmp, Y2_tmp);

	if (flag == true and flag_1 == true and flag_2 == true) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		ui.pushButton_10->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("Background-color: yellow;");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("Background-color: yellow;");
	}
	else return;
}

void Game::on_pushButton_11_clicked() {
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

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp);
	bool flag_1 = Resources->test_correct_positioning(X2_tmp, Y2_tmp, X3_tmp, Y3_tmp);
	bool flag_2 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_3 = Resources->check_the_ships(X2_tmp, Y2_tmp);
	bool flag_4 = Resources->check_the_ships(X3_tmp, Y3_tmp);

	if (flag == true and flag_1 == true and flag_2 == true and flag_3 == true and flag_4 == true) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		Resources->set_gamespace(X3.c_str(), Y3, 1);
		ui.pushButton_11->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("Background-color: yellow;");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("Background-color: yellow;");
		Board_Vector[Y3_tmp][X3_tmp]->setStyleSheet("Background-color: yellow;");
	}
	else return;
}

void Game::on_pushButton_12_clicked() {
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

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp);
	bool flag_1 = Resources->test_correct_positioning(X2_tmp, Y2_tmp, X3_tmp, Y3_tmp);
	bool flag_2 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_3 = Resources->check_the_ships(X2_tmp, Y2_tmp);
	bool flag_4 = Resources->check_the_ships(X3_tmp, Y3_tmp);

	if (flag == true and flag_1 == true and flag_2 == true and flag_3 == true and flag_4 == true) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		Resources->set_gamespace(X3.c_str(), Y3, 1);
		ui.pushButton_12->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("Background-color: yellow;");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("Background-color: yellow;");
		Board_Vector[Y3_tmp][X3_tmp]->setStyleSheet("Background-color: yellow;");
	}
	else return;
}

void Game::on_pushButton_13_clicked() {

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

	if (CordsFromPlayer_1.isEmpty() or CordsFromPlayer_2.isEmpty() or CordsFromPlayer_3.isEmpty() or CordsFromPlayer_4.isEmpty()) {
		QMessageBox::critical(this, "B³¹d", "Pole tekstowe nie mo¿e byæ puste. WprowadŸ dane.");
		return;
	}
	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int X3_tmp = Resources->cordsX_to_numbers(X3.c_str());
	int X4_tmp = Resources->cordsX_to_numbers(X4.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);
	int Y3_tmp = Resources->cordsY_to_numbers(Y3);
	int Y4_tmp = Resources->cordsY_to_numbers(Y4);

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp);
	bool flag_1 = Resources->test_correct_positioning(X2_tmp, Y2_tmp, X3_tmp, Y3_tmp);
	bool flag_2 = Resources->test_correct_positioning(X3_tmp, Y3_tmp, X4_tmp, Y4_tmp);
	bool flag_3 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_4 = Resources->check_the_ships(X2_tmp, Y2_tmp);
	bool flag_5 = Resources->check_the_ships(X3_tmp, Y3_tmp);
	bool flag_6 = Resources->check_the_ships(X4_tmp, Y4_tmp);

	if (flag == true and flag_1 == true and flag_2 == true and flag_3 == true and flag_4 == true and flag_5 == true and flag_6 == true) {
		Resources->set_gamespace(X1.c_str(), Y1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1);
		Resources->set_gamespace(X3.c_str(), Y3, 1);
		Resources->set_gamespace(X4.c_str(), Y4, 1);
		ui.pushButton_13->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("Background-color: yellow;");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("Background-color: yellow;");
		Board_Vector[Y3_tmp][X3_tmp]->setStyleSheet("Background-color: yellow;");
		Board_Vector[Y4_tmp][X4_tmp]->setStyleSheet("Background-color: yellow;");
	}
	else return;
}

void Game::initialize_Border() {
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

void Game::resetGame() {
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
	//return;
}

void Game::cords_for_bot() {

	return;
}