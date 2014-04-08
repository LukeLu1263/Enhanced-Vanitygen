/*
 * =====================================================================================
 *
 *       Filename:  sqlite_db.c
 *
 *    Description:  A test for sqlite3 database in C/C++
 *
 *        Version:  1.0
 *        Created:  2013/11/12 09时41分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luke Lu(lzf824446@gmail.com), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

/** 
 *  If above callback is provided in sqlite_exec() routine as the third argument, 
 *	SQLite will call the this callback function for each record processed in each 
 *  SELECT statement executed within the SQL argument. 
 */
static int callback(void *data, int argc, char **argv, char **azColName) {
	int i; 
	fprintf(stdout, "%s: ", (const char*)data);
	for (i=0; i<argc; i++) {
		fprintf(stdout, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(int argc, char* argv[])
{
	sqlite3 *db;
	char *zErrMsg = NULL;
	int rc;
	char *sql;
	const char* data = "Callback function called";

	/* Open database */
	rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	} else {
		fprintf(stdout, "Opened database successfully\n");
	}


	/* Create Table */
	sql =  "CREATE TABLE COMPANY("				\
		   "ID INT PRIMARY KEY	NOT NULL," 		\
		   "NAME		   TXT	NOT NULL," 		\
		   "AGE            INT  NOT NULL," 		\
		   "ADDRESS		   CHAR(50)," 			\
		   "SALARY		   REAL);";

	/* Execute Create Table*/
	rc = sqlite3_exec(db, sql, callback, NULL, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "CREATE TABLE SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "CREATE TABLE successfully\n");
	}


	/* Insert */
	sql	= "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
	      "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " 	\
		  "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
          "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "  	\
		  "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" 	\
		  "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" 		\
		  "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" 	\
		  "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

	/* Execute Insert */
	rc = sqlite3_exec(db, sql, callback, NULL, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "INSERT SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "INSERT records created successfully\n");
	}


	/* Select */
	sql = "SELECT * from COMPANY";

	/* Execute Select */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SELECT SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "SELECT Operation done successfully\n");
	}


	/* Update */
	sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
		  "SELECT * from COMPANY";

	/* Execute Update */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "UPDATE SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "UPDATE Operation done successfully\n");
	}

	/* Delete */
	sql = "DELETE from COMPANY where ID=2; " \
		  "SELECT * from COMPANY";

	/* Execute Delete */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "DELETE SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "DELETE Operation done successfully\n");
	}

	sqlite3_close(db);
	return EXIT_SUCCESS;
}

