#pragma once
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace sql;

class MySQL
{
private:
	Driver *driver;
	Connection* con;

	Statement* stmt;
	ResultSet* res;

	string IP = "tcp://127.0.0.1:3306";
	string user = "root";
	string password = "";
	string database = "project_data_base";

public:
	MySQL();
	~MySQL();
	ResultSet* select_querry();
	bool insert_player(const string& login, const string& pswd);
	bool insert_points(const string& login, int points, int moves, int min, int sec, int day, int mon, int year);
	ResultSet* return_pswd(const string& login);
	int return_ID(const string& login);
};

