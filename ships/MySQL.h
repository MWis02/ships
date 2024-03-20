#pragma once
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <sstream>

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
	bool insert_player(string login, string pswd);
	ResultSet* return_pswd(string login);
};

