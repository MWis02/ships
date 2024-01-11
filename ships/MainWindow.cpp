#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent),
	Resources(new resources),
	BotShot(new QTimer),
	Delay(new QTimer),
	score(new ScoreBoard)
{   
	count = 0;
	x = 0;
	y = 0;
	shot = 0;
	shot_1 = 0;
	LastHitX = 0;
	LastHitY = 0;
	lastShotHit = false;
	botcounter = 0;
	BotX = 0;
	BotY = 0;
	name_for_first_player = "";
	name_for_second_player = "";
	score_at_end = 0;

    ui.setupUi(this);
	ui.widget_GS->hide();
	ui.widget_blank->hide();
	ui.widget_GP->hide();
	ui.widget_GP_1->hide();
	ui.widget_NS->hide();
	ui.widget_EG->hide();
	initialize_Border();
	initialize_Labels();
	initialize_Border_GP();
	initialize_Buttons_GP();
	initialize_Border_GP_1();
	initialize_Buttons_GP_1();
	srand(time(NULL));
	connect(BotShot, &QTimer::timeout, this, &MainWindow::shot_for_bot);
}

MainWindow::~MainWindow()
{
	delete Resources;
	delete BotShot;

	count = 0;
	x = 0;
	y = 0;
	shot = 0;
	shot_1 = 0;
	LastHitX = 0;
	LastHitY = 0;
	lastShotHit = false;
	BotX = 0;
	BotY = 0;
}

void MainWindow::on_pushButton_Ch_1_clicked() {
	ui.widget_title->hide();
	ui.widget_NS->show();
	ui.label_17->hide();
	ui.Edit_name_2->hide();
	ui.label_15->setText("Wpisz nazwe dla gracza");
	ui.Edit_name_1->setPlaceholderText("Wpisz nazwę gracza");
	count = 0;
	resetGame();
}

void MainWindow::on_pushButton_Ch_2_clicked() {
	ui.widget_title->hide();
	ui.widget_NS->show();
	ui.pushButton_14->show();
	ui.label_17->show();
	ui.Edit_name_2->show();
	ui.label_15->setText("Wpisz nazwy dla graczy");
	ui.Edit_name_1->setPlaceholderText("Wpisz nazwe gracza");
	ui.Edit_name_2->setPlaceholderText("Wpisz nazwe gracza");
	count = 1;
	resetGame();
}

void MainWindow::on_pushButton_NS_1_clicked() {
	ui.widget_title->show();
	ui.widget_NS->hide();
	name_for_second_player = "";
	name_for_first_player = "";
	ui.Edit_name_1->setPlaceholderText("Wpisz nazwę gracza");
	ui.Edit_name_2->setPlaceholderText("Wpisz nazwę gracza");
}

void MainWindow::on_pushButton_NS_2_clicked() {
	if (count == 0) {

		name_for_first_player = ui.Edit_name_1->text().toStdString();
		if (name_for_first_player.empty()) {
			name_for_first_player = "Player 1";
		}

		ui.widget_NS->hide();
		ui.widget_GS->show();
		ui.pushButton_14->hide();
	}
	else {
		name_for_first_player = ui.Edit_name_1->text().toStdString();
		name_for_second_player = ui.Edit_name_2->text().toStdString();
		if (name_for_first_player.empty()) {
			name_for_first_player = "Player 1";
		}
		else if (name_for_second_player.empty()) {
			name_for_second_player = "Player 2";
		}
		ui.widget_NS->hide();
		ui.widget_GS->show();
		ui.Edit_name_2->show();
		
	}
}

void MainWindow::on_pushButton_clicked() {
	ui.widget_GS->hide();
	ui.widget_title->show();
	ui.pushButton_14->setEnabled(true);
	Resources->set_to_defaults();
	ui.Edit_name_1->clear();
	ui.Edit_name_2->clear();
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

		ui.widget_GS->hide();
		ui.widget_GP->show();
		ui.textBrowser->setText("Liczba oddanych strzalow: " + QString::number(shot));
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (Player_1->check_shot(i, j) == 1) {
					Board_Vector_GP[j][i]->setStyleSheet("background-image: url(:/ships/ship1.png)");
				}
			}
		}
		score->Start_time();
		return;
	}
	else {
		Player_2 = new resources(*Resources);
		ui.widget_GS->hide();
		ui.widget_GP->show();
		ui.textBrowser->setText("Liczba oddanych strzalow: " + QString::number(shot));
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (Player_1->check_shot(i, j) == 1) {
					Board_Vector_GP[j][i]->setStyleSheet("background-image: url(:/ships/ship1.png)");
				}
				if (Player_2->check_shot(i, j) == 1) {
					Board_Vector_GP_1[j][i]->setStyleSheet("background-image: url(:/ships/ship1.png)");
				}
			}
		}
		score->Start_time();
		return;
	}
	return;
}

void MainWindow::on_pushButton_EG_1_clicked() {
	resetGame();
	ui.widget_EG->hide();
	ui.widget_title->hide();
}

void MainWindow::on_pushButton_EG_2_clicked() {

}

void MainWindow::on_pushButton_EG_3_clicked() {
	QApplication::quit();
	return;
}

void MainWindow::on_pushButton_4_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_0->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");


	QString x1 = CordsParts_1.at(0); /*Pobranie pierwszej wartości od użytkownika*/
	string X1 = x1.toStdString(); /*zmiana Qstring na string*/
	int Y1 = CordsParts_1.at(1).toInt(); /*Pobranie drugiej wartości od użytkownika */

	int X_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y1);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);
	if (flag and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X1.c_str(), Y1, 1, 1); /*X.c_str() wyłuskanie wskaźnika "const char*"*/
		ui.pushButton_4->setDisabled(true);
		ui.lineEdit_0->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_5_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_1->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x = CordsParts_1.at(0);
	string X = x.toStdString();
	int Y = CordsParts_1.at(1).toInt();

	int X_tmp = Resources->cordsX_to_numbers(X.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);

	if (flag and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X.c_str(), Y, 1, 1);
		ui.pushButton_5->setDisabled(true);
		ui.lineEdit_1->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_6_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_2->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x = CordsParts_1.at(0);
	string X = x.toStdString();
	int Y = CordsParts_1.at(1).toInt();

	int X_tmp = Resources->cordsX_to_numbers(X.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);
	if (flag and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X.c_str(), Y, 1, 1);
		ui.pushButton_6->setDisabled(true);
		ui.lineEdit_2->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_7_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_3->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x = CordsParts_1.at(0);
	string X = x.toStdString();
	int Y = CordsParts_1.at(1).toInt();

	int X_tmp = Resources->cordsX_to_numbers(X.c_str());
	int Y_tmp = Resources->cordsY_to_numbers(Y);

	bool flag = Resources->check_the_ships(X_tmp, Y_tmp);
	if (flag and X_tmp != -1 and Y_tmp != -1) {
		Resources->set_gamespace(X.c_str(), Y, 1, 1);
		ui.pushButton_7->setDisabled(true);
		ui.lineEdit_3->setDisabled(true);
		Board_Vector[Y_tmp][X_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_8_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_4->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(0);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_5->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(0);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(1).toInt();

	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp, 2);
	bool flag_1 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_2 = Resources->check_the_ships(X2_tmp, Y2_tmp);
	 
	if (flag and flag_1 and flag_2) {
		Resources->set_gamespace(X1.c_str(), Y1, 1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1, 1);
		ui.pushButton_8->setDisabled(true);
		ui.lineEdit_4->setDisabled(true);
		ui.lineEdit_5->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_9_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_6->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(0);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_7->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(0);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(1).toInt();

	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);


	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp, 2);
	bool flag_1 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_2 = Resources->check_the_ships(X2_tmp, Y2_tmp);

	if (flag and flag_1 and flag_2) {
		Resources->set_gamespace(X1.c_str(), Y1, 1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1, 1);
		ui.pushButton_9->setDisabled(true);
		ui.lineEdit_6->setDisabled(true);
		ui.lineEdit_7->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_10_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_8->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(0);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_9->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(0);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(1).toInt();

	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp, 2);
	bool flag_1 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_2 = Resources->check_the_ships(X2_tmp, Y2_tmp);

	if (flag and flag_1 and flag_2) {
		Resources->set_gamespace(X1.c_str(), Y1, 1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1, 1);
		ui.pushButton_10->setDisabled(true);
		ui.lineEdit_8->setDisabled(true);
		ui.lineEdit_9->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_11_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_10->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(0);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_11->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(0);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(1).toInt();

	CordsFromPlayer_3 = ui.lineEdit_12->text();
	CordsParts_3 = CordsFromPlayer_3.split(",");

	QString x3 = CordsParts_3.at(0);
	string X3 = x3.toStdString();
	int Y3 = CordsParts_3.at(1).toInt();

	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int X3_tmp = Resources->cordsX_to_numbers(X3.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);
	int Y3_tmp = Resources->cordsY_to_numbers(Y3);

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp, 2);
	bool flag_1 = Resources->test_correct_positioning(X2_tmp, Y2_tmp, X3_tmp, Y3_tmp, 2);
	bool flag_2 = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X3_tmp, Y3_tmp, 3);
	bool flag_3 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_4 = Resources->check_the_ships(X2_tmp, Y2_tmp);
	bool flag_5 = Resources->check_the_ships(X3_tmp, Y3_tmp);

	if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5) {
		Resources->set_gamespace(X1.c_str(), Y1, 1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1, 1);
		Resources->set_gamespace(X3.c_str(), Y3, 1, 1);
		ui.pushButton_11->setDisabled(true);
		ui.lineEdit_10->setDisabled(true);
		ui.lineEdit_11->setDisabled(true);
		ui.lineEdit_12->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y3_tmp][X3_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_12_clicked() {
	CordsFromPlayer_1 = ui.lineEdit_13->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(0);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_14->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(0);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(1).toInt();

	CordsFromPlayer_3 = ui.lineEdit_15->text();
	CordsParts_3 = CordsFromPlayer_3.split(",");

	QString x3 = CordsParts_3.at(0);
	string X3 = x3.toStdString();
	int Y3 = CordsParts_3.at(1).toInt();

	int X1_tmp = Resources->cordsX_to_numbers(X1.c_str());
	int X2_tmp = Resources->cordsX_to_numbers(X2.c_str());
	int X3_tmp = Resources->cordsX_to_numbers(X3.c_str());
	int Y1_tmp = Resources->cordsY_to_numbers(Y1);
	int Y2_tmp = Resources->cordsY_to_numbers(Y2);
	int Y3_tmp = Resources->cordsY_to_numbers(Y3);

	bool flag = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X2_tmp, Y2_tmp, 2);
	bool flag_1 = Resources->test_correct_positioning(X2_tmp, Y2_tmp, X3_tmp, Y3_tmp, 2);
	bool flag_2 = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X3_tmp, Y3_tmp, 3);
	bool flag_3 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_4 = Resources->check_the_ships(X2_tmp, Y2_tmp);
	bool flag_5 = Resources->check_the_ships(X3_tmp, Y3_tmp);

	if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5) {
		Resources->set_gamespace(X1.c_str(), Y1, 1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1, 1);
		Resources->set_gamespace(X3.c_str(), Y3, 1, 1);
		ui.pushButton_12->setDisabled(true);
		ui.lineEdit_13->setDisabled(true);
		ui.lineEdit_14->setDisabled(true);
		ui.lineEdit_15->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y3_tmp][X3_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_13_clicked() {

	CordsFromPlayer_1 = ui.lineEdit_16->text();
	CordsParts_1 = CordsFromPlayer_1.split(",");

	QString x1 = CordsParts_1.at(0);
	string X1 = x1.toStdString();
	int Y1 = CordsParts_1.at(1).toInt();

	CordsFromPlayer_2 = ui.lineEdit_17->text();
	CordsParts_2 = CordsFromPlayer_2.split(",");

	QString x2 = CordsParts_2.at(0);
	string X2 = x2.toStdString();
	int Y2 = CordsParts_2.at(1).toInt();

	CordsFromPlayer_3 = ui.lineEdit_18->text();
	CordsParts_3 = CordsFromPlayer_3.split(",");

	QString x3 = CordsParts_3.at(0);
	string X3 = x3.toStdString();
	int Y3 = CordsParts_3.at(1).toInt();

	CordsFromPlayer_4 = ui.lineEdit_19->text();
	CordsParts_4 = CordsFromPlayer_4.split(",");

	QString x4 = CordsParts_4.at(0);
	string X4 = x4.toStdString();
	int Y4 = CordsParts_4.at(1).toInt();

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
	bool flag_3 = Resources->test_correct_positioning(X1_tmp, Y1_tmp, X4_tmp, Y4_tmp, 4);
	bool flag_4 = Resources->check_the_ships(X1_tmp, Y1_tmp);
	bool flag_5 = Resources->check_the_ships(X2_tmp, Y2_tmp);
	bool flag_6 = Resources->check_the_ships(X3_tmp, Y3_tmp);
	bool flag_7 = Resources->check_the_ships(X4_tmp, Y4_tmp);
	

	if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5 and flag_6 and flag_7) {
		Resources->set_gamespace(X1.c_str(), Y1, 1, 1);
		Resources->set_gamespace(X2.c_str(), Y2, 1, 1);
		Resources->set_gamespace(X3.c_str(), Y3, 1, 1);
		Resources->set_gamespace(X4.c_str(), Y4, 1, 1);
		ui.pushButton_13->setDisabled(true); 
		ui.lineEdit_16->setDisabled(true);
		ui.lineEdit_17->setDisabled(true);
		ui.lineEdit_18->setDisabled(true);
		ui.lineEdit_19->setDisabled(true);
		Board_Vector[Y1_tmp][X1_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y2_tmp][X2_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y3_tmp][X3_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
		Board_Vector[Y4_tmp][X4_tmp]->setStyleSheet("background-image: url(:/ships/ship1.png);");
	}
	else return;
}

void MainWindow::on_pushButton_14_clicked() {
	ui.pushButton_14->setDisabled(true);
	Player_1 = new resources(*Resources);
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
}

void MainWindow::initialize_Labels() {
	for (int i = 0; i < 20; i++) {
		QString Line_N = "lineEdit_" + QString::number(i);
		QLineEdit* Line_S = findChild<QLineEdit*>(Line_N);
		LineEdits_Vector.push_back(Line_S);
	}
}

void MainWindow::initialize_Border_GP() {
	for (int i = 0; i < 10; i++) {
		QVector<QLabel*> columnLabel;
		for (int j = 0; j < 10; j++) {
			QString Label_N = "GP_2_" + QString::number(j) + QString::number(i);
			QLabel* Label_S = findChild<QLabel*>(Label_N);

			columnLabel.push_back(Label_S);
		}
		Board_Vector_GP.push_back(columnLabel);
	}
	return;
}

void MainWindow::initialize_Buttons_GP() {
	QSignalMapper* signalMapper = new QSignalMapper(this);
	for (int i = 0; i < 10; i++) {
		QVector<QPushButton*> columnLabel;
		for (int j = 0; j < 10; j++) {
			QString Button_N = "GP_1_" + QString::number(j) + QString::number(i);
			QPushButton* Button_S = findChild<QPushButton*>(Button_N);

			columnLabel.push_back(Button_S);
		}
		Buttons_Vector_GP.push_back(columnLabel);
	}
	/*Połączenie vectora z przyciskami 
	i przekazanie wartości który przycik został wciśnięty dalej*/
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			connect(Buttons_Vector_GP[j][i], &QPushButton::clicked, this, [this, j, i]() {
				x = i;
				y = j;
				shot_for_player();
			});
		}
	}
	return;
}

void MainWindow::initialize_Border_GP_1(){
	for (int i = 0; i < 10; i++) {
		QVector<QLabel*> columnLabel;
		for (int j = 0; j < 10; j++) {
			QString Label_N = "GP_4_" + QString::number(j) + QString::number(i);
			QLabel* Label_S = findChild<QLabel*>(Label_N);

			columnLabel.push_back(Label_S);
		}
		Board_Vector_GP_1.push_back(columnLabel);
	}
	return;
}

void MainWindow::initialize_Buttons_GP_1(){
	QSignalMapper* signalMapper = new QSignalMapper(this);
	for (int i = 0; i < 10; i++) {
		QVector<QPushButton*> columnLabel;
		for (int j = 0; j < 10; j++) {
			QString Button_N = "GP_3_" + QString::number(j) + QString::number(i);
			QPushButton* Button_S = findChild<QPushButton*>(Button_N);

			columnLabel.push_back(Button_S);
		}
		Buttons_Vector_GP_1.push_back(columnLabel);
	}
	/*Połączenie vectora z przyciskami
	i przekazanie wartości który przycik został wciśnięty dalej*/
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			connect(Buttons_Vector_GP_1[j][i], &QPushButton::clicked, this, [this, j, i]() {
				x = i;
				y = j;
				shot_for_second_player();
				});
		}
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

	/*Resetowanie tła dla pokazania statków*/
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Board_Vector[j][i]->setStyleSheet("");
		}
	}

	for (int i = 0; i < 20; i++) {
		LineEdits_Vector[i]->clear();
		LineEdits_Vector[i]->setEnabled(true);
	}
}

void MainWindow::cords_for_bot() {
	Resources->set_to_defaults();

	for (int i = 0; i < 10; ) {
		if (i < 4) {
			int X = rand() % 10;
			int Y = rand() % 10;
			const char* tmp = Resources->cordsX_for_Bot(X);
			bool flag = Resources->check_the_ships(X, Y);
			if (flag) {

				if (Resources->check_cord_for_Bot(Y, X) == 0) {
					Resources->set_gamespace(tmp, Y, 1, 2);
					i += 1;
				}
				else if (Resources->check_cord_for_Bot(Y, X) == 1) {}
			}
		}
		else if (i < 7) {
			int X1 = rand() % 10;
			int Y1 = rand() % 10;
			int X2 = rand() % 10;
			int Y2 = rand() % 10;

			bool flag = Resources->check_the_ships(X1, Y1);
			bool flag_1 = Resources->check_the_ships(X2, Y2);
			bool flag_2 = Resources->test_correct_positioning(X1, Y1, X2, Y2, 2);

			if (flag and flag_1 and flag_2) {
				if (Resources->check_cord_for_Bot(Y1, X1) == 0 and Resources->check_cord_for_Bot(Y2, X2) == 0) {
					const char* tmp = Resources->cordsX_for_Bot(X1);
					const char* tmp_1 = Resources->cordsX_for_Bot(X2);
					Resources->set_gamespace(tmp, Y1, 1, 2);
					Resources->set_gamespace(tmp_1, Y2, 1, 2);
					i += 1;
				}
			}
		}
		else if (i < 9) {
			int X1 = rand() % 10;
			int Y1 = rand() % 10;
			int X2 = rand() % 10;
			int Y2 = rand() % 10;
			int X3 = rand() % 10;
			int Y3 = rand() % 10;

			bool flag = Resources->check_the_ships(X1, Y1);
			bool flag_1 = Resources->check_the_ships(X2, Y2);
			bool flag_2 = Resources->check_the_ships(X3, Y3);
			bool flag_3 = Resources->test_correct_positioning(X1, Y1, X2, Y2, 2);
			bool flag_4 = Resources->test_correct_positioning(X2, Y2, X3, Y3, 2);
			bool flag_5 = Resources->test_correct_positioning(X1, Y1, X3, Y3, 3);

			if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5) {
				if (Resources->check_cord_for_Bot(Y1, X1) == 0 and Resources->check_cord_for_Bot(Y2, X2) == 0 and Resources->check_cord_for_Bot(Y3, X3) == 0) {
					const char* tmp = Resources->cordsX_for_Bot(X1);
					const char* tmp_1 = Resources->cordsX_for_Bot(X2);
					const char* tmp_2 = Resources->cordsX_for_Bot(X3);
					Resources->set_gamespace(tmp, Y1, 1, 2);
					Resources->set_gamespace(tmp_1, Y2, 1, 2);
					Resources->set_gamespace(tmp_2, Y3, 1, 2);
					i += 1;
				}
			}
		}
		else if (i == 9) {
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
			bool flag_4 = Resources->test_correct_positioning(X1, Y1, X2, Y2, 2);
			bool flag_5 = Resources->test_correct_positioning(X2, Y2, X3, Y3, 2);
			bool flag_6 = Resources->test_correct_positioning(X3, Y3, X4, Y4, 2);
			bool flag_7 = Resources->test_correct_positioning(X1, Y1, X4, Y4, 4);

			if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5 and flag_6 and flag_7) {
				if (Resources->check_cord_for_Bot(Y1, X1) == 0 and Resources->check_cord_for_Bot(Y2, X2) == 0 and Resources->check_cord_for_Bot(Y3, X3) == 0 and Resources->check_cord_for_Bot(Y4, X4) == 0) {
					const char* tmp = Resources->cordsX_for_Bot(X1);
					const char* tmp_1 = Resources->cordsX_for_Bot(X2);
					const char* tmp_2 = Resources->cordsX_for_Bot(X3);
					const char* tmp_3 = Resources->cordsX_for_Bot(X4);
					Resources->set_gamespace(tmp, Y1, 1, 2);
					Resources->set_gamespace(tmp_1, Y2, 1, 2);
					Resources->set_gamespace(tmp_2, Y3, 1, 2);
					Resources->set_gamespace(tmp_3, Y4, 1, 2);
					i += 1;
				}
			}
		}
	}
	return;
}

void MainWindow::gen_Ships_for_players() {
	/*Resetowanie wartośći oraz planszy dla każdego generowania układu*/
	Resources->set_to_defaults();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Board_Vector[j][i]->setStyleSheet("");
		}
	}
	for (int i = 0; i < 20; i++) {
		LineEdits_Vector[i]->clear();
		LineEdits_Vector[i]->setDisabled(true);
	}
	int j = 0;
	/*Generowanie losowych koordynatów*/
	for (int i = 0; i < 10; ) {
		if (i < 4) {
			int X = rand() % 10;
			int Y = rand() % 10;
			const char* tmp = Resources->cordsX_for_Bot(X);
			bool flag = Resources->check_the_ships(X, Y);
			if (flag) {
				if (Resources->check_cord_for_Bot(Y, X) == 0) {
					Resources->set_gamespace(tmp, Y, 1, 2);
					Board_Vector[Y][X]->setStyleSheet("background-image: url(:/ships/ship1.png);");
					LineEdits_Vector[i]->setText(QString(tmp) + "," + QString::number(Y + 1));
					i += 1;
					j += 1;
				}
			}
		}
		else if (i < 7) {
			int X1 = rand() % 10;
			int Y1 = rand() % 10;
			int X2 = rand() % 10;
			int Y2 = rand() % 10;
			bool flag = Resources->check_the_ships(X1, Y1);
			bool flag_1 = Resources->check_the_ships(X2, Y2);
			bool flag_2 = Resources->test_correct_positioning(X1, Y1, X2, Y2, 2);

			if (flag and flag_1 and flag_2) {
				if (Resources->check_cord_for_Bot(Y1, X1) == 0 and Resources->check_cord_for_Bot(Y2, X2) == 0) {
					const char* tmp = Resources->cordsX_for_Bot(X1);
					const char* tmp_1 = Resources->cordsX_for_Bot(X2);
					Resources->set_gamespace(tmp, Y1, 1, 2);
					Resources->set_gamespace(tmp_1, Y2, 1, 2);
					Board_Vector[Y1][X1]->setStyleSheet("background-image: url(:/ships/ship1.png);");
					Board_Vector[Y2][X2]->setStyleSheet("background-image: url(:/ships/ship1.png);");
					LineEdits_Vector[j]->setText(QString(tmp) + "," + QString::number(Y1 + 1));
					LineEdits_Vector[j + 1]->setText(QString(tmp_1) + "," + QString::number(Y2 + 1));
					i += 1;
					j += 2;
				}
			}
		}
		else if (i < 9) {
			int X1 = rand() % 10;
			int Y1 = rand() % 10;
			int X2 = rand() % 10;
			int Y2 = rand() % 10;
			int X3 = rand() % 10;
			int Y3 = rand() % 10;

			bool flag = Resources->check_the_ships(X1, Y1);
			bool flag_1 = Resources->check_the_ships(X2, Y2);
			bool flag_2 = Resources->check_the_ships(X3, Y3);
			bool flag_3 = Resources->test_correct_positioning(X1, Y1, X2, Y2, 2);
			bool flag_4 = Resources->test_correct_positioning(X2, Y2, X3, Y3, 2);
			bool flag_5 = Resources->test_correct_positioning(X1, Y1, X3, Y3, 3);

			if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5) {
				if (Resources->check_cord_for_Bot(Y1, X1) == 0 and Resources->check_cord_for_Bot(Y2, X2) == 0 and Resources->check_cord_for_Bot(Y3, X3) == 0) {
					const char* tmp = Resources->cordsX_for_Bot(X1);
					const char* tmp_1 = Resources->cordsX_for_Bot(X2);
					const char* tmp_2 = Resources->cordsX_for_Bot(X3);
					Resources->set_gamespace(tmp, Y1, 1, 2);
					Resources->set_gamespace(tmp_1, Y2, 1, 2);
					Resources->set_gamespace(tmp_2, Y3, 1, 2);
					Board_Vector[Y1][X1]->setStyleSheet("background-image: url(:/ships/ship1.png);");
					Board_Vector[Y2][X2]->setStyleSheet("background-image: url(:/ships/ship1.png);");
					Board_Vector[Y3][X3]->setStyleSheet("background-image: url(:/ships/ship1.png);");
					LineEdits_Vector[j]->setText(QString(tmp) + "," + QString::number(Y1 + 1));
					LineEdits_Vector[j + 1]->setText(QString(tmp_1) + "," + QString::number(Y2 + 1));
					LineEdits_Vector[j + 2]->setText(QString(tmp_2) + "," + QString::number(Y3 + 1));
					i += 1;
					j += 3;
				}
			}
		}
		else if (i == 9) {
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
			bool flag_4 = Resources->test_correct_positioning(X1, Y1, X2, Y2, 2);
			bool flag_5 = Resources->test_correct_positioning(X2, Y2, X3, Y3, 2);
			bool flag_6 = Resources->test_correct_positioning(X3, Y3, X4, Y4, 2);
			bool flag_7 = Resources->test_correct_positioning(X1, Y1, X4, Y4, 4);

			if (flag and flag_1 and flag_2 and flag_3 and flag_4 and flag_5 and flag_6 and flag_7) {
				if (Resources->check_cord_for_Bot(Y1, X1) == 0 and Resources->check_cord_for_Bot(Y2, X2) == 0 and Resources->check_cord_for_Bot(Y3, X3) == 0 and Resources->check_cord_for_Bot(Y4, X4) == 0) {
					const char* tmp = Resources->cordsX_for_Bot(X1);
					const char* tmp_1 = Resources->cordsX_for_Bot(X2);
					const char* tmp_2 = Resources->cordsX_for_Bot(X3);
					const char* tmp_3 = Resources->cordsX_for_Bot(X4);
					Resources->set_gamespace(tmp, Y1, 1, 2);
					Resources->set_gamespace(tmp_1, Y2, 1, 2);
					Resources->set_gamespace(tmp_2, Y3, 1, 2);
					Resources->set_gamespace(tmp_3, Y4, 1, 2);
					Board_Vector[Y1][X1]->setStyleSheet("background-image: url(:/ships/ship1.png);");
					Board_Vector[Y2][X2]->setStyleSheet("background-image: url(:/ships/ship1.png);");
					Board_Vector[Y3][X3]->setStyleSheet("background-image: url(:/ships/ship1.png);");
					Board_Vector[Y4][X4]->setStyleSheet("background-image: url(:/ships/ship1.png);");
					LineEdits_Vector[j]->setText(QString(tmp) + "," + QString::number(Y1 + 1));
					LineEdits_Vector[j + 1]->setText(QString(tmp_1) + "," + QString::number(Y2 + 1));
					LineEdits_Vector[j + 2]->setText(QString(tmp_2) + "," + QString::number(Y3 + 1));
					LineEdits_Vector[j + 3]->setText(QString(tmp_3) + "," + QString::number(Y4 + 1));
					i += 1;
				}
			}
		}
	}
	return;
}

void MainWindow::on_pushButton_gen_clicked() {
	ui.pushButton_4->setDisabled(true);
	ui.pushButton_5->setDisabled(true);
	ui.pushButton_6->setDisabled(true);
	ui.pushButton_7->setDisabled(true);
	ui.pushButton_8->setDisabled(true);
	ui.pushButton_9->setDisabled(true);
	ui.pushButton_10->setDisabled(true);
	ui.pushButton_11->setDisabled(true);
	ui.pushButton_12->setDisabled(true);
	ui.pushButton_13->setDisabled(true);
	gen_Ships_for_players();

	return;
}

void MainWindow::on_pushButton_res_clicked() {
	resetGame();
}

void MainWindow::shot_for_player() {
	if (count == 0) {
		BotShot->stop();
		int check = Bot->check_shot(x, y);
		if (check == 0) {
			Buttons_Vector_GP[y][x]->setStyleSheet("Background-color: grey;");
			BotShot->start(1500);
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					Buttons_Vector_GP[j][i]->setDisabled(true);
				}
			}
			Bot->set_gamespace_after_shoot(x, y, 2);
		}
		else if (check == 1){	
			Bot->set_gamespace_after_shoot(x, y, 3);
			Buttons_Vector_GP[y][x]->setStyleSheet("background-image: url(:/ships/hitted-ship_1.png);");
			Buttons_Vector_GP[y][x]->setDisabled(true);
			vector_for_fields = check_fields(x, y, Bot);
			if (vector_for_fields.size() != 0) {
				for (int i = 0; i < vector_for_fields.size(); i++) {
					int GPX = vector_for_fields[i].first;
					int GPY = vector_for_fields[i].second;

					for (int i = max(0, GPX - 1); i <= min(9, GPX + 1); i++) {
						for (int j = max(0, GPY - 1); j <= min(9, GPY + 1); j++) {
							if(check = Bot->check_shot(i, j) == 0){
								Buttons_Vector_GP[j][i]->setStyleSheet("background-color: grey");
								Buttons_Vector_GP[j][i]->setDisabled(true);
								Bot->set_gamespace_after_shoot(i, j, 2);
							}
						}
					}
				}
			}
		}

		Player_1->counter += 1;
		if (Player_1->counter == 20) {
			ui.widget_GP->hide();
			ui.widget_EG->show();
			ui.widget_EG->setStyleSheet("QWidget {background-image: url(:/ships/EG_Win_1.png);} QLabel {background: none; background-color: rgba(225, 225, 225, 0.85);}");
			ui.label_11->setText("Gratulacje wygrales");
			score->name = name_for_first_player;
			score->Stop_time();
			score_at_end = score->calculate_points(shot+=1);
			ui.textBrowser_2->setText("Liczba zgromadzonych punktów: " + QString::number(score_at_end));
			return;
		}

		shot += 1;
		ui.textBrowser->setText("Liczba oddanych strzałów: " + QString::number(shot) + "\n Tura gracza");
		
	}
	else {
		Delay->stop();
		int check = Player_2->check_shot(x, y);
		if (check == 0) {
			Buttons_Vector_GP[y][x]->setStyleSheet("Background-color: grey;");
			Player_2->set_gamespace_after_shoot(x, y, 2);
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (Player_2->check_shot(i, j) == 1) {
						Board_Vector_GP_1[j][i]->setStyleSheet("background-image: url(:/ships/ship1.png)");
					}
					else if (Player_2->check_shot(i, j) == 2) {
						Board_Vector_GP_1[j][i]->setStyleSheet("background-color: grey");
					}
					else if (Player_2->check_shot(i, j) == 3) {
						Board_Vector_GP_1[j][i]->setStyleSheet("background-image: url(:/ships/hitted-ship_1.png)");
					}
					if (Player_1->check_shot(i, j) == 3) {
						Buttons_Vector_GP_1[j][i]->setStyleSheet("background-image: url(:/ships/hitted-ship_1.png)");
						Buttons_Vector_GP_1[j][i]->setEnabled(false);
					}
					else if (Player_1->check_shot(i, j) == 2) {
						Buttons_Vector_GP_1[j][i]->setStyleSheet("background-color: grey");
						Buttons_Vector_GP_1[j][i]->setEnabled(false);
					}
					else Buttons_Vector_GP_1[j][i]->setEnabled(true);
					
					Buttons_Vector_GP[j][i]->setDisabled(true);
				}
			}
			Delay->start(2000);
			connect(Delay, &QTimer::timeout, [this]() {
				ui.widget_GP->hide();
				ui.widget_GP_1->show();
			});
		}
		else if (check == 1) {
			Player_1->counter += 1;		
			Player_2->set_gamespace_after_shoot(x, y, 3);
			Buttons_Vector_GP[y][x]->setStyleSheet("background-image: url(:/ships/hitted-ship_1.png)");
			Buttons_Vector_GP[y][x]->setDisabled(true);
			vector_for_fields = check_fields(x, y, Player_2);
			if (vector_for_fields.size() != 0) {
				for (int i = 0; i < vector_for_fields.size(); i++) {
					int GPX = vector_for_fields[i].first;
					int GPY = vector_for_fields[i].second;

					for (int i = max(0, GPX - 1); i <= min(9, GPX + 1); i++) {
						for (int j = max(0, GPY - 1); j <= min(9, GPY + 1); j++) {
							if (check = Player_2->check_shot(i, j) == 0) {
								Buttons_Vector_GP[j][i]->setStyleSheet("background-color: grey");
								Buttons_Vector_GP[j][i]->setDisabled(true);
								Player_2->set_gamespace_after_shoot(i, j, 2);
							}
						}
					}
				}
			}
			if (Player_1->counter == 20) {
				ui.widget_GP->hide();
				ui.widget_EG->show();
				ui.widget_EG->setStyleSheet("QWidget {background-image: url(:/ships/EG_Win_1.png);} QLabel {background: none; background-color: rgba(225, 225, 225, 0.85);}");
				ui.label_11->setText("Gratulacje wygrales");
				score->name = name_for_first_player;
				score->Stop_time();
				score_at_end = score->calculate_points(shot += 1);
				return;
			}
		}
		shot += 1;
		ui.textBrowser->setText("Liczba oddanych strzalow: " + QString::number(shot));
	}
}

void MainWindow::shot_for_second_player() {
	Delay->stop();
	int check = Player_1->check_shot(x, y);
	if (check == 0) {
		Buttons_Vector_GP_1[y][x]->setStyleSheet("Background-color: grey;");
		Player_1->set_gamespace_after_shoot(x, y, 2);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (Player_1->check_shot(i, j) == 1) {
					Board_Vector_GP[j][i]->setStyleSheet("background-image: url(:/ships/ship1.png)");
				}
				else if (Player_1->check_shot(i, j) == 2) {
					Board_Vector_GP[j][i]->setStyleSheet("background-color: grey");
				}
				else if (Player_1->check_shot(i, j) == 3) {
					Board_Vector_GP[j][i]->setStyleSheet("background-image: url(:/ships/hitted-ship_1.png)");
				}
				if (Player_2->check_shot(i, j) == 3) {
					Buttons_Vector_GP[j][i]->setStyleSheet("background-image: url(:/ships/hitted-ship_1.png)");
					Buttons_Vector_GP[j][i]->setEnabled(false);
				}
				else if (Player_2->check_shot(i, j) == 2) {
					Buttons_Vector_GP[j][i]->setStyleSheet("background-color: grey");
					Buttons_Vector_GP[j][i]->setEnabled(false);
				}
				else Buttons_Vector_GP[j][i]->setEnabled(true);

				Buttons_Vector_GP_1[j][i]->setDisabled(true);
			}
		}
		Delay->start(2000);
		connect(Delay, &QTimer::timeout, [this]() {
			ui.widget_GP_1->hide();
			ui.widget_GP->show();
		});
	}
	else if (check == 1) {
		Player_2->counter += 1;
		Player_1->set_gamespace_after_shoot(x, y, 3);
		Buttons_Vector_GP_1[y][x]->setStyleSheet("background-image: url(:/ships/hitted-ship_1.png)");
		Buttons_Vector_GP_1[y][x]->setDisabled(true);
		vector_for_fields = check_fields(x, y, Player_1);
		if (vector_for_fields.size() != 0) {
			for (int i = 0; i < vector_for_fields.size(); i++) {
				int GPX = vector_for_fields[i].first;
				int GPY = vector_for_fields[i].second;

				for (int i = max(0, GPX - 1); i <= min(9, GPX + 1); i++) {
					for (int j = max(0, GPY - 1); j <= min(9, GPY + 1); j++) {
						if (check = Player_1->check_shot(i, j) == 0) {
							Buttons_Vector_GP_1[j][i]->setStyleSheet("background-color: grey");
							Buttons_Vector_GP_1[j][i]->setDisabled(true);
							Player_1->set_gamespace_after_shoot(i, j, 2);
						}
					}
				}
			}
		}
		if (Player_2->counter == 20) {
			ui.widget_GP->hide();
			ui.widget_EG->show();
			ui.widget_EG->setStyleSheet("QWidget {background-image: url(:/ships/EG_Win_1.png);} QLabel {background: none; background-color: rgba(225, 225, 225, 0.85);}");
			ui.label_11->setText("Gratulacje wygrałeś ");
			score->name = name_for_second_player;
			score->Stop_time();
			score_at_end = score->calculate_points(shot_1 += 1);
	
			return;
		}

	}
	shot_1 += 1;
	ui.textBrowser_1->setText("Liczba oddanych strzalow : " + QString::number(shot_1));
}

void MainWindow::shot_for_bot() {
	if (lastShotHit) {
		/*Zawężenie obszaru strzału do pola 3x3 i iteracja po elementach w poszukiwaniu statku*/
		/*Wartości min(...) i max(...) nie pozwalają wyjść pętli poza zakres tablice*/
		for (int i = max(0, LastHitX - 1); i <= min(9, LastHitX + 1); i++) {
			for (int j = max(0, LastHitY - 1); j <= min(9, LastHitY + 1); j++) {
				int tmp = Player_1->check_shot(i, j);
				if (tmp == 1) {
					BotX = i;
					BotY = j;
					break;
				}
			}
		}
		lastShotHit = false;
		BotShot->start(1500);
		/*Jeżeli zostanie znaleziony statek pętla i if się przerywa i bot przechodzi do strzału,
		jeżeli nie zostanie znaleziony strzał jest resetowany do wartości tablicy 9x9*/
	}
	else
	{
		BotX = rand() % 10;
		BotY = rand() % 10;
	}
	int check = Player_1->check_shot(BotX, BotY);
	ui.textBrowser->setText("Tura bota");
	if (check == 0) {
		Board_Vector_GP[BotY][BotX]->setStyleSheet("Background-color: grey;");
		Player_1->set_gamespace_after_shoot(BotX, BotY, 2);
		lastShotHit = false;
		ui.textBrowser->setText("Tura gracza");
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				int tmp = Bot->check_shot(i, j);
				if (tmp == 2 or tmp == 3) {
					Buttons_Vector_GP[j][i]->setDisabled(true);
				}
				else {
					Buttons_Vector_GP[j][i]->setDisabled(false);
				}
				
			}
		}
		shot_1 += 1;
		BotShot->stop();
		return;
	}
	else if (check == 1){
		Board_Vector_GP[BotY][BotX]->setStyleSheet("background-image: url(:/ships/hitted-ship_1.png);");
		Bot->counter += 1;
		botcounter += 1;
		LastHitX = BotX;
		LastHitY = BotY;
		lastShotHit = true;
		
		Player_1->set_gamespace_after_shoot(BotX, BotY, 3);
		vector_for_fields = check_fields(BotX, BotY, Player_1);
		if (vector_for_fields.size() != 0) {
			for (int i = 0; i < vector_for_fields.size(); i++) {
				int GPX = vector_for_fields[i].first;
				int GPY = vector_for_fields[i].second;

				for (int i = max(0, GPX - 1); i <= min(9, GPX + 1); i++) {
					for (int j = max(0, GPY - 1); j <= min(9, GPY + 1); j++) {
						if (check = Player_1->check_shot(i, j) == 0) {
							Board_Vector_GP[j][i]->setStyleSheet("background-color: grey");
							Board_Vector_GP[j][i]->setDisabled(true);
							Player_1->set_gamespace_after_shoot(i, j, 2);
						}
					}
				}
			}
		}

		if (Bot->counter == 20) {
			ui.widget_GP->hide();
			ui.widget_EG->show();
			ui.widget_EG->setStyleSheet("background-image: url(:/ships/EG_Lose_2.png);");
			ui.label_11->setText("Niestety tym razem przegrales");
			score->name = "Bot";
			score->Stop_time();
			score_at_end = score->calculate_points(shot_1 += 1);
			ui.textBrowser_2->setText("Wygrał bot \n Liczba zgromadzonych punktów: " + QString::number(score_at_end));
			return;
		}
		shot_1 += 1;
		BotShot->start(1500);
	}
	else if (check == 2 or check == 3) {
		BotShot->start(1500);
	}
}

vector<pair<int, int>> MainWindow::check_fields(int xCord, int yCord, resources* object) {
	vector<pair<int, int>> vector_to_return;

	/*---Sprawdzenie na lewo---*/
	for (int x = xCord - 1; x >= 0; x--) {
		int tmp = object->check_shot(x, yCord);
		if (tmp == 3) vector_to_return.push_back({ x, yCord });
		else if (tmp == 1) {
			vector_to_return.clear();
			return vector_to_return;
		}
		else break;
	}

	/*---Sprawdzenie na prawo---*/
	for (int x = xCord + 1; x < 10; x++) {
		int tmp = object->check_shot(x, yCord);
		if (tmp == 3) vector_to_return.push_back({ x, yCord });
		else if (tmp == 1) {
			vector_to_return.clear();
			return vector_to_return;
		}
		else break;
	}

	/*---Sprawdzenie do góry---*/
	for (int y = yCord - 1; y >= 0; y--) {
		int tmp = object->check_shot(xCord, y);
		if (tmp == 3) vector_to_return.push_back({ xCord, y });
		else if (tmp == 1) {
			vector_to_return.clear();
			return vector_to_return;
		}
		else break;
	}

	/*---Sprawdzenie w dół---*/
	for (int y = yCord + 1; y < 10; y++) {
		int tmp = object->check_shot(xCord, y);
		if (tmp == 3) vector_to_return.push_back({ xCord, y });
		else if (tmp == 1) {
			vector_to_return.clear();
			return vector_to_return;
		}
		else break;
	}

	/*---Wyelminowanie powtórzeń---*/
	if (std::find(vector_to_return.begin(), vector_to_return.end(), make_pair(xCord, yCord)) == vector_to_return.end()) {
		vector_to_return.push_back({ xCord, yCord });
	}
	/*---.begin() i .end() wskazują na początek i koniec vectora, tworząc pare kordynatów sprawdzamy czy 
	znajdują się już one w środku vectora jeżeli nie to dodajemy je na koniec*/

	return vector_to_return;
}