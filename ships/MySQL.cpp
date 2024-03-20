#include "MySQL.h"

MySQL::MySQL() {
    try {
        // Po³¹czenie z baz¹ danych
        driver = get_driver_instance();
        con = driver->connect(IP, user, password);
        con->setSchema(database);
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

}

void MySQL::connect_to_database(){
    
	return;
}