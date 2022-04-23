#include <iostream>
#include <mysql.h>

using namespace std;

char serverdb[] = "localhost";
char userdb[] = "root";
char passworddb[] = "Magodeoz123@";
char database[] = "alumnos";
string sql;
const char* query;
int result;

void agregarAlu(MYSQL*);
bool buscarClave(MYSQL*, string);
void agregarGrado(MYSQL*);
void agregarSeccion(MYSQL*);
void agregarNota(MYSQL*);
void buscarAlu(MYSQL*);
void mostrarPromedioAl(MYSQL*);
void borrarAlumno(MYSQL*);
void mosAluGrado(MYSQL*);
void modificarAl(MYSQL*);
void mostrarGrados(MYSQL*);


int main(){
	
	MYSQL* connection;
	connection = mysql_init(0);
	int sel;

	
	if (connection){
		
		cout << "La biblioteca MySQL se ha iniciado correctamente" << endl;
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		
		if (connection){
			
			cout << "Conexion exitosa a la base de datos \n" << endl;
			
			do {
				
				cout << "*************************" << endl;
				cout << "*      Bienvenidos      *" << endl;
				cout << "************************* \n" << endl;
				cout << "Elija una opcion \n" << endl;
				cout << "1. Agregar Alumnos" << endl;
				cout << "2. Agregar grado" << endl;
				cout << "3. Agregar seccion" << endl;
				cout << "4. Agregar Nota" << endl;
				cout << "5. Buscar Alumno" << endl;
				cout << "6. Mostrar Promedio de Alumno" << endl;
				cout << "7. Borrar Alumno" << endl;
				cout << "8. Mostrar Alumnos de un Grado" << endl;
				cout << "9. Modificar datos de alumno" << endl;
				cout << "10. Mostrar grados" << endl;
				cout << "0. Salir\n" << endl;
				cin >> sel;
				
				switch(sel){
					
					case 1:
						system("cls");
						agregarAlu(connection);
						system("pause");
						system("cls");
						break;
					
					case 2:
						system("cls");
						agregarGrado(connection);
						system("pause");
						system("cls");
						break;
						
					case 3:
						system("cls");
						agregarSeccion(connection);
						system("pause");
						system("cls");
						break;
						
					case 4:
						system("cls");
						agregarNota(connection);
						system("pause");
						system("cls");
						break;
					
					case 5:
						system("cls");
						buscarAlu(connection);
						system("pause");
						system("cls");
						break;
						
					case 6:
						system("cls");
						mostrarPromedioAl(connection);
						system("pause");
						system("cls");
						break;
						
					case 7:
						system("cls");
						borrarAlumno(connection);
						system("pause");
						system("cls");
						break;
						
					case 8:
						system("cls");
						mosAluGrado(connection);
						system("pause");
						system("cls");
						break;
						
					case 9:
						system("cls");
						modificarAl(connection);
						system("pause");
						system("cls");
						break;
						
					case 10:
						system("cls");
						mostrarGrados(connection);
						system("pause");
						system("cls");
						break;
						
				}
				
			} while (sel !=0);
			
			
		} else {
			
			cout << "No fue posible conectar con la base de datos" << endl;
		}
		
	} else {
		
		cout << "No fue posible iniciar la biblioteca MySQL" << endl;
	}
}

void agregarAlu(MYSQL *connection){
	
	string id, edad, nombre, apellido, correo, telefono, grado, seccion;
	
	cout << "*************************************" << endl;
	cout << "*        Registro de Alumnos        *" << endl;
	cout << "************************************* \n" << endl;
	cout << "Clave de Alumno: ";
	cin.ignore(1, '\n');
	getline(cin, id);
	
	bool a = buscarClave(connection, id);
	
	while (a == 1) {
		
		cout << "La clave ingresada ya ha sido registrada!!" << endl;
		cout << "Clave de alumno: ";
		getline(cin, id);
		
		a = buscarClave(connection, id);
	
	}
	
	cout << "Nombre: ";
	getline(cin, nombre);
	cout << "Apellido: ";
	getline(cin, apellido);
	cout << "Edad: ";
	getline(cin, edad);
	cout << "Correo: ";
	getline(cin, correo);
	cout << "Telefono: ";
	getline(cin, telefono);
	cout << "Grado: ";
	getline(cin, grado);
	cout << "Seccion 1 = A, 2 = B, 3 = C: ";
	getline(cin, seccion); 
			
	sql = "insert into alumno (id_alumno, nombre, apellido, edad, correo, telefono, grado_id_grado, seccion_id_seccion) values ('" + id + "', '" + nombre + "', '" + apellido + "', '" + edad + "', '" + correo + "', '" + telefono + "', '" + grado + "', '" + seccion + "')";
			
	query = sql.c_str();
	result = mysql_query(connection, query);
			
	if (result == 0){
				
		cout << "\nRegistro guardado con exito!!\n" << endl;
		
	} else {
				
		cout << "\nNo fue posible guardar el registro!! \n" << mysql_error(connection) << endl;
	}
	
}

bool buscarClave(MYSQL *connection, string a){
	
	MYSQL_ROW row;
	MYSQL_RES* data;
	string id;
	bool res;
	
	sql = "select * from alumno where id_alumno = '" + a + "'";
	query = sql.c_str();
	result = mysql_query(connection, query);
	
	if (result == 0){
		
		data = mysql_store_result(connection);
		int countColumns = mysql_num_fields(data);
		
		while (row = mysql_fetch_row(data)){
			
			if (row[0] == a){
				
				res = true;
				
			} else {
				
				res = false;
			}
			
		}
		
		return res;
		
	} 
	
}

void agregarGrado(MYSQL *connection){
	
	string id, grado;
	
	cout << "*************************************" << endl;
	cout << "*        Registro de Grados         *" << endl;
	cout << "************************************* \n" << endl;
	cout << "Ingrese id: ";
	cin.ignore(1, '\n');
	getline(cin, id);
	cout << "ingrese grado: ";
	getline(cin, grado);
	
	sql = "insert into grado (id_grado, grado) values ('" + id + "', '" + grado + "')";
	query = sql.c_str();
	result = mysql_query(connection, query);
	
	if (result == 0){
		
		cout << "\nRegistro guardado con exito!!\n" << endl;
		
	} else {
		
		cout << "\nNo fue posible guardar el registro!!\n" << endl;
	}
	
	
}

void agregarSeccion(MYSQL *connection){
	
	string id, seccion;
	
	cout << "****************************************" << endl;
	cout << "*        Registro de Secciones         *" << endl;
	cout << "**************************************** \n" << endl;
	cout << "Ingrese id: ";
	cin.ignore(1, '\n');
	getline(cin, id);
	cout << "Ingrese seccion: ";
	getline(cin, seccion);
	
	sql = "insert into seccion (id_seccion, seccion) values ('" + id + "', '" + seccion + "')";
	query = sql.c_str();
	result = mysql_query(connection, query);
	
	if (result == 0){
		
		cout << "\nRegistro guardado exitosamente!!\n" << endl;
		
	} else {
		
		cout << "\nNo fue posible realizar el registro\n" << endl;
	}
	
}

void agregarNota(MYSQL *connection){
	
	string idAlu, idGra, idSec, nota; 
	
	cout << "****************************************" << endl;
	cout << "*          Registro de Notas           *" << endl;
	cout << "**************************************** \n" << endl;
	cout << "\nClave de alumno: ";
	cin.ignore(1, '\n');
	getline(cin, idAlu);
	cout << "Grado: ";
	getline(cin, idGra);
	cout << "Seccion 1 = A, 2 = B, 3 = C: ";
	getline(cin, idSec);
	cout << "Nota: ";
	getline(cin, nota);
	
	sql = "insert into notas (alumno_id_alumno, alumno_grado_id_grado, alumno_seccion_id_seccion, nota) values ('" + idAlu + "', '" + idGra+ "', '" + idSec + "', '" + nota + "')";
	query = sql.c_str();
	result = mysql_query(connection, query);
	
	if (result == 0){
		
		cout << "\nRegistro guardado exitosamente!!\n" << endl;
		
	} else {
		
		cout << "\nNo fue posible realizar el registro\n" << endl;
	}
	
}

void buscarAlu(MYSQL *connection){
	
	MYSQL_ROW row;
	MYSQL_RES* data;
	string id;
	
	cout << "****************************************" << endl;
	cout << "*            Buscar Alumno             *" << endl;
	cout << "**************************************** \n" << endl;
	cin.ignore(1, '\n');
	cout << "Ingrese clave de alumno: ";
	getline(cin, id);
	cout << "" << endl;
	
	sql = "select al.id_alumno, al.nombre, al.apellido, al.edad, al.correo, al.telefono, gr.grado, se.seccion from alumno as al join grado as gr on al.grado_id_grado = gr.id_grado join seccion as se on al.seccion_id_seccion = se.id_seccion where id_alumno = '" + id + "';";
	query = sql.c_str();
	result = mysql_query(connection, query);
	
	if (result == 0){
		
		data = mysql_store_result(connection);
		int countColumns = mysql_num_fields(data);
		
		while(row = mysql_fetch_row(data)){
			
			for (int i = 0; i < countColumns; i++){
				
				cout << row[i] << ", "; 
			}	
			
			cout << "\n" << endl;
			
		}
		
	} else {
		
		cout << "\nNo fue posible obtener los datos solicitados" << mysql_error(connection) << endl;
		
	}
}

void mostrarPromedioAl(MYSQL *connection){
	
	MYSQL_ROW row;
	MYSQL_RES* data;
	string id;
	int suma, cont, a;
	float promedio;
	
	cout << "****************************************" << endl;
	cout << "*           Promedio Alumno            *" << endl;
	cout << "**************************************** \n" << endl;
	cout << "Clave de alumno: ";
	cin.ignore(1, '\n');
	getline(cin, id);
	cout << "\n" << endl;
	
	sql = "select al.id_alumno, al.nombre, al.apellido, al.edad, al.correo, al.telefono, gr.grado, se.seccion, nas.nota from alumno as al join grado as gr on al.grado_id_grado = gr.id_grado join seccion as se on al.seccion_id_seccion = se.id_seccion join notas as nas on al.id_alumno = nas.alumno_id_alumno where id_alumno = '" + id + "';";
	query = sql.c_str();
	result = mysql_query(connection, query);
	
	if (result == 0){
		
		data = mysql_store_result(connection);
		int countColumns = mysql_num_fields(data);
		
		while(row = mysql_fetch_row(data)){
			
			for (int i = 0; i < countColumns; i++){
				
				cout << row[i] << " ";
				 
			}	
			
			cout << "\n" << endl;
			
		}
		
		sql = "select avg(nota) from notas where alumno_id_alumno = '" + id + "';";
		query = sql.c_str();
		result = mysql_query(connection, query);
		
		if (result == 0){
			
			data = mysql_store_result(connection);
			int countColumns = mysql_num_fields(data);
		
			while(row = mysql_fetch_row(data)){
			
				for (int i = 0; i < countColumns; i++){
				
					cout << "Promedio: " << row[i] << endl;
				 
				}	
			
				cout << "\n" << endl;
			
			}
			
		} else {
			
			cout << "\nNo fue posible obtener los datos solicitados" << mysql_error(connection) << endl;
			
		}
		
	} else {
		
		cout << "\nNo fue posible obtener los datos solicitados" << mysql_error(connection) << endl;
		
	}
		
}

void borrarAlumno(MYSQL *connection){
	
	string id, sqlII;
	int sel, res; 
	
	cout << "****************************************" << endl;
	cout << "*           Eliminar Alumno            *" << endl;
	cout << "**************************************** \n" << endl;
	cout << "Clave del alumno: ";
	cin.ignore(1, '\n');
	getline(cin, id);
	
	cout << "\nConfirma eliminar alumno? 1. Si, 0. No: ";
	cin >> sel;
	
	if (sel == 1){
		
		sql = "delete from notas where alumno_id_alumno = '" + id + "'";
		query = sql.c_str();
		result = mysql_query(connection, query);
		
		sqlII = "delete from alumno where id_alumno = '" + id + "'";
		query = sqlII.c_str();
		res = mysql_query(connection, query);
		
		if (result == 0 && res == 0){
		
			cout << "\nRegistro eliminado con exito!!\n" << endl;
		
		} else {
		
			cout << "\nNo fue posible eliminar el registro!!\n" << mysql_error(connection) << endl;
		}
				
	} else {
		
		cout << "No se hicieron cambios!!" << endl;
	}
	
}

void mosAluGrado(MYSQL *connection){
	
	MYSQL_ROW row;
	MYSQL_RES* data;
	string id;
	
	cout << "****************************************" << endl;
	cout << "*         Alumnos de un grado          *" << endl;
	cout << "**************************************** \n" << endl;
	cout << "Grado: ";
	cin.ignore(1, '\n');
	getline(cin, id);
	cout << "\n";
	
	sql = "select al.id_alumno, al.nombre, al.apellido, gr.grado, sec.seccion from alumno as al join grado as gr on al.grado_id_grado = gr.id_grado join seccion as sec on al.seccion_id_seccion = sec.id_seccion where grado_id_grado = '" + id + "'";
	query =sql.c_str();
	result = mysql_query(connection, query);
	
	if (result == 0){
		
		data = mysql_store_result(connection);
		int countColumns = mysql_num_fields(data);
		
		while(row = mysql_fetch_row(data)){
			
			for (int i = 0; i < countColumns; i++){
				
				cout << row[i] << " -- ";
				 
			}	
			
			cout << "\n";
			
		}
		
	} else {
		
		cout << "\nNo fue posible obtener los datos requeridos!!\n" << mysql_error(connection) << endl;
		
	}
	
	cout << "\n";
}

void modificarAl(MYSQL *connection){
	
	string id, nuDato;
	int sel;
	
	cout << "****************************************" << endl;
	cout << "*      Modificar datos de Alumno       *" << endl;
	cout << "**************************************** \n" << endl;
	cout << "Clave Alumno: ";
	cin.ignore(1, '\n');
	getline(cin, id);
	
	cout << "Que dato desea modificar?\n " << endl;
	cout << "1. Nombre" << endl;
	cout << "2. Apellido" << endl;
	cout << "3. Edad" << endl;
	cout << "4. Correo" << endl;
	cout << "5. Telefono" << endl;
	cout << "6. Grado" << endl;
	cout << "7. Seccion" << endl;
	cin >> sel;
	
	switch (sel){
		
		case 1:
			//system("cls");
			cout << "\nNuevo nombre: ";
			cin.ignore(1, '\n');
			getline(cin, nuDato);
			sql = "update alumno set nombre = '" + nuDato + "' where id_alumno = '" + id + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
		
			if (result == 0){
			
				cout << "\nDato actualizado correctamente\n" << endl;
			
			} else {
			
				cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
			}
			break;
			
		case 2:
			//system("cls");
			cout << "\nNuevo apellido: ";
			cin.ignore(1, '\n');
			getline(cin, nuDato);
			sql = "update alumno set apellido = '" + nuDato + "' where id_alumno = '" + id + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
		
			if (result == 0){
			
				cout << "\nDato actualizado correctamente\n" << endl;
			
			} else {
			
				cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
			}
			break;
		
		case 3:
			//system("cls");
			cout << "\nNueva edad: ";
			cin.ignore(1, '\n');
			getline(cin, nuDato);
			sql = "update alumno set edad = '" + nuDato + "' where id_alumno = '" + id + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
		
			if (result == 0){
			
				cout << "\nDato actualizado correctamente\n" << endl;
			
			} else {
			
				cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
			}
			break;
			
		case 4:
			//system("cls");
			cout << "\nNuevo correo: ";
			getline(cin, nuDato);
			sql = "update alumno set correo = '" + nuDato + "' where id_alumno = '" + id + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
		
			if (result == 0){
			
				cout << "\nDato actualizado correctamente\n" << endl;
			
			} else {
			
				cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
			}
			break;
			
		case 5:
			//system("cls");
			cout << "\nNuevo telefono: ";
			cin.ignore(1, '\n');
			getline(cin, nuDato);
			sql = "update alumno set telefono = '" + nuDato + "' where id_alumno = '" + id + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
		
			if (result == 0){
			
				cout << "\nDato actualizado correctamente\n" << endl;
			
			} else {
			
				cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
			}
			break;
			
		case 6:
			//system("cls");
			cout << "\nNuevo grado: ";
			cin.ignore(1, '\n');
			getline(cin, nuDato);
			sql = "update alumno set grado_id_grado = '" + nuDato + "' where id_alumno = '" + id + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
		
			if (result == 0){
			
				cout << "\nDato actualizado correctamente\n" << endl;
			
			} else {
			
				cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
			}
			break;
			
		case 7:
			//system("cls");
			cout << "\nNueva seccion: ";
			cin.ignore(1, '\n');
			getline(cin, nuDato);
			sql = "update alumno set seccion_id_seccion = '" + nuDato + "' where id_alumno = '" + id + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
		
			if (result == 0){
			
				cout << "\nDato actualizado correctamente\n" << endl;
			
			} else {
			
				cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
			}
			break;
			
	}
	
}

void mostrarGrados(MYSQL *connection){
	
	MYSQL_ROW row;
	MYSQL_RES* data;
	
	cout << "****************************************" << endl;
	cout << "*      Mostrar grados existentes       *" << endl;
	cout << "**************************************** \n" << endl;
	
	sql = "select * from grado";
	query = sql.c_str();
	result = mysql_query(connection, query);
	
	if (result == 0){
		
		data = mysql_store_result(connection);
		int countColumns = mysql_num_fields(data);
		
		while(row = mysql_fetch_row(data)){
			
			for (int i = 0; i < countColumns; i++){
				
				cout << row[i] << " -- ";
				 
			}	
			
			cout << "\n";
			
		}
		
	} else {
		
		cout << "\nNo fue posible obtener los datos requeridos!!\n" << mysql_error(connection) << endl;
		
	}	
	
	cout << "\n";
}
