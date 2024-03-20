#pragma once
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>

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
	string user = "admin";
	string password = "";
	string database = "project_data_base";

public:
	MySQL();
	~MySQL();
	void connect_to_database();
};

