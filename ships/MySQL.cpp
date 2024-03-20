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
        // Obs�uga b��d�w
        cout << "SQLException: " << e.what() << endl;
    }
    catch (std::runtime_error& e) {
        // Obs�uga b��d�w
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