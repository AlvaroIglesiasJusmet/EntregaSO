#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
	
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	//Creamos una conexion al servidor MYSQL
	conn= mysql_init(NULL);
	if(conn==NULL){
		printf("Error al crear la conexion: %u %s\n", mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	//inicializar la conexion 
	conn= mysql_real_connect (conn, "localhost","root","mysql","juego",0,NULL,0);
	if (conn==NULL){
		printf ("Error al inicializar la conexion: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	int puntos;
	char consulta[80];
	strcpy (consulta,"SELECT sum(PUNTUACIONES.PUNTOS) FROM (JUGADOR,PARTIDA,PUNTUACIONES) WHERE (JUGADOR.NICK = 'JUAN') AND (PARTIDA.GANADOR=JUGADOR.NICK) AND (PUNTUACIONES.PLAYER = JUGADOR.NICK) AND (PUNTUACIONES.IDPARTIDA = PARTIDA.ID)");
	err=mysql_query(conn,consulta);
	if (err!=0){
		printf ("Error al consultar datos de la base %u %s\n",mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	resultado= mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	if (row==NULL){
		printf ("No se han obtenido datos en la consulta\n");
	}
	else{
		while(row!=NULL){
			printf("%s\n", row[0]);
			row = mysql_fetch_row(resultado);
		}
	}
	mysql_close(conn);
	exit(0);
}

