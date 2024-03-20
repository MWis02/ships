#include "MySQL.h"

MySQL::MySQL() {
    try {
        driver = get_driver_instance();
        con = driver->connect(IP, user, password);
        con->setSchema(database);
        stmt = con->createStatement();
        res = nullptr;
    }
    catch (SQLException& e) {
        // Obs³uga b³êdów
        cout << "SQLException: " << e.what() << endl;
    }
    catch (std::runtime_error& e) {
        // Obs³uga b³êdów
        cout << "RuntimeError: " << e.what() << endl;
    }
}

MySQL::~MySQL() {
    delete stmt;
    delete con;
    if (res != nullptr) {
        delete res;
    }
}

ResultSet* MySQL::select_querry(){
    res = stmt->executeQuery("SELECT * FROM players");
	return res;
}

bool MySQL::insert_player(string login, string pswd) {
    try {
        // Tworzenie zapytania INSERT INTO
        std::stringstream query;
        query << "INSERT INTO players (name, password) VALUES ('" << login << "', '" << pswd << "')";

        // Wykonanie zapytania
        stmt = con->createStatement();
        stmt->executeUpdate(query.str());

        // Zwolnienie zasobów
        delete stmt;
        delete con;

        return true; // Powodzenie operacji
    }
    catch (SQLException& e) {
        // Obs³uga b³êdów
        cout << "SQLException: " << e.what() << endl;
    }
    catch (std::runtime_error& e) {
        // Obs³uga b³êdów
        cout << "RuntimeError: " << e.what() << endl;
    }

    return false;
}

ResultSet* MySQL::return_pswd(string login) {
    // Tworzenie zapytania INSERT INTO
    stringstream query;
    query << "SELECT password FROM players where name LIKE '" << login << "'";
    res = stmt->executeQuery(query.str());
    return res;
}