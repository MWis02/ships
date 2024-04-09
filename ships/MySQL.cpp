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

bool MySQL::insert_player(const string& login, const string& pswd) {
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

ResultSet* MySQL::return_pswd(const string& login) {
    // Tworzenie zapytania SELECT
    stringstream query;
    query << "SELECT password FROM players where name LIKE '" << login << "'";
    res = stmt->executeQuery(query.str());
    return res;
}

bool MySQL::insert_points(const string& login, int points, int moves, int min, int sec, int day, int mon, int year) {
    try {
        stringstream query;
        int id = return_ID(login);

        /*setw ustawienie szerokosci pola na 2, setfill je¿eli nie bêdzie 2 cyfr automatycznie wypelni do 2*/
        query << "INSERT INTO scoreboard (player_id, points, moves, time, date) VALUES ("
            << id << "," << points << ", " << moves << ", '"
            << setw(2) << setfill('0') << ":" << setw(2) << setfill('0') << min << ":" << setw(2) << setfill('0') << sec
            << "', '" << year << "-" << setw(2) << setfill('0') << mon << "-" << setw(2) << setfill('0') << day << "')";

        res = stmt->executeQuery(query.str());

        return true;
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

int MySQL::return_ID(const std::string& login) {
    // Tworzenie zapytania SQL
    stringstream query;
    query << "SELECT Id FROM players WHERE name LIKE '" << login << "'";

    // Wykonanie zapytania
    res = stmt->executeQuery(query.str());

    // Sprawdzenie, czy wynik zapytania jest poprawny
    if (res && res->next()) {
        // Pobranie ID gracza
        int playerId = res->getInt("Id");

        // Zwolnienie zasobów ResultSet
        delete res;

        // Zwrócenie ID gracza
        return playerId;
    }
    else {
        // W przypadku braku wyniku lub b³êdu, zwróæ -1 (lub inn¹ wartoœæ oznaczaj¹c¹ b³¹d)
        cout << "Nie znaleziono gracza o nazwie: " << login << endl;
        delete res; // Zwolnienie zasobów ResultSet
        return -1;
    }
}

ResultSet* MySQL::return_score() {
    stringstream query;
	query << "SELECT name, points, time, moves, date FROM players INNER JOIN scoreboard on players.Id = scoreboard.player_id ORDER BY points DESC LIMIT 10";
    res = stmt->executeQuery(query.str());
	return res;
}