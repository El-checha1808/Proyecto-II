#include <iostream>
#include <mysql.h>

using namespace std;

char serverdb[] = "localhost";
char userdb[] = "root";
char passworddb[] = "Magodeoz123@";
char database[] = "alumnos";

int main(){
	
	MYSQL* connection;
	string sql;
	const char* query;
	int result;
	connection = mysql_init(0);
	
	if (connection){
		
		cout << "La biblioteca MySQL se ha iniciado correctamente" << endl;
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		
		if (connection){
			
			cout << "Conexion exitosa a la base de datos" << endl;

		}
	}
}
