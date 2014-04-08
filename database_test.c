/*
 * =====================================================================================
 *
 *       Filename:  database.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/13/2013 11:34:45 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>


static int callback(void *data, int argc, char **argv, char **azColName);
void open_database(sqlite3 *db, char *path);
void close_database(sqlite3 *db);
void create_table(sqlite3 *db, char* sql);
void insert_records(sqlite3 *db, char *sql, void *data);
void select_records(sqlite3 *db, char *sql, void *data);
void delete_records(sqlite3 *db, char *sql, void *data);
void update_records(sqlite3 *db, char *sql, void *data);

int main(int argc, char* argv[])
{
    sqlite3 *db;
    char *sql;
	char *data = "Callback function called";

    /* Open database */
	char *path = "test.db";
	open_database(db, path);

    /* Create Table */
    sql =  "CREATE TABLE COMPANY("              \
           "ID INT PRIMARY KEY  NOT NULL,"      \
           "NAME           TXT  NOT NULL,"      \
           "AGE            INT  NOT NULL,"      \
           "ADDRESS        CHAR(50),"           \
           "SALARY         REAL);";
	create_table(db, sql);


    /* Insert */
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "   \
          "VALUES (1, 'Paul', 32, 'California', 20000.00 ); "   \
          "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "   \
          "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "       \
          "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"    \
          "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );"       \
          "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"    \
          "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
	insert_records(db, sql, NULL);


    /* Select */
    sql = "SELECT * from COMPANY";
	select_records(db, sql, data);


    /* Update */
    sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
          "SELECT * from COMPANY";
	update_records(db, sql, data);


    /* Delete */
    sql = "DELETE from COMPANY where ID=2; " \
          "SELECT * from COMPANY";
	delete_records(db, sql, data);

	/* Close database */
	close_database(db);

    return EXIT_SUCCESS;
}                     

/** 
 *  If above callback is provided in sqlite_exec() routine as the third argument, 
 *  SQLite will call the this callback function for each record processed in each 
 *  SELECT statement executed within the SQL argument. 
 */
static int callback(void *data, int argc, char **argv, char **azColName) 
{
    int i; 
    data = "Callback function called";
    fprintf(stdout, "%s: ", (const char*)data);
    for (i=0; i<argc; i++) {
        fprintf(stdout, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

/* Open database */
void open_database(sqlite3 *db, char *path)
{
	int rc;
    rc = sqlite3_open(path, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }
}

/* Close database */
void close_database(sqlite3 *db)
{
	sqlite3_close(db);
}

/* Execute Create Table*/
void create_table(sqlite3 *db, char *sql)
{
	int rc;
    char *zErrMsg = NULL;
    rc = sqlite3_exec(db, sql, callback, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "CREATE TABLE SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "CREATE TABLE successfully\n");
    }
}

/* Execute Insert */
void insert_records(sqlite3 *db, char *sql, void *data) 
{
	int rc;
    char *zErrMsg = NULL;
    rc = sqlite3_exec(db, sql, callback, data, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "INSERT SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "INSERT records created successfully\n");
    }
}

/* Execute Select */
void select_records(sqlite3 *db, char *sql, void *data) 
{
	int rc;
    char *zErrMsg = NULL;
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SELECT SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "SELECT Operation done successfully\n");
    }
}

/* Execute Delete */
void delete_records(sqlite3 *db, char *sql, void *data) 
{
	int rc;
    char *zErrMsg = NULL;
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "DELETE SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "DELETE Operation done successfully\n");
    }
}

/* Execute Update */
void update_records(sqlite3 *db, char *sql, void *data)
{
	int rc;
    char *zErrMsg = NULL;
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "UPDATE SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "UPDATE Operation done successfully\n");
    }
}
