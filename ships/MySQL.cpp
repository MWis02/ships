#include "MySQL.h"

MySQL::MySQL() {
    try {
        // Po��czenie z baz� danych
        driver = get_driver_instance();
        con = driver->connect(IP, user, password);
        con->setSchema(database);
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

}

void MySQL::connect_to_database(){
    
	return;
}