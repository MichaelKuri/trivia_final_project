#include "SqliteDataBase.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "sqlite3.h"

//open and create new table
bool SqliteDataBase::open()
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	const char* sql;
	rc = sqlite3_open("triviaDb.db", &db);

	/* Create SQL statement */
	sql = "CREATE TABLE USER(" \
		"USER_NAME TEXT PRIMERY KEY NOT NULL ," \
		"PASSWORD TEXT NOT NULL," \
		"EMAIL TEXT NOT NULL);";

	rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (rc == SQLITE_OK)
	{
		return 1;
	}
}

//check if user name exsist in the table. return 0 if isnt exists
int SqliteDataBase::doesUserExist(std::string username) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	std::string sql;
	int userExists = 0;


	rc = sqlite3_open("triviaDb.db", &db);
	if (rc)
	{
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return 0;
	}


	sql = "SELECT * FROM USER WHERE USER_NAME = ?";


	rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return 0;
	}


	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW)
	{
		userExists = 1;
	}
	else if (rc != SQLITE_DONE)
	{
		std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return userExists;
}

int SqliteDataBase::doesPasswordMatch(std::string username, std::string password) {
	sqlite3* db = nullptr;
	sqlite3_stmt* stmt = nullptr;
	int rc;
	int passwordMatches = 0;


	rc = sqlite3_open("triviaDb.db", &db);
	if (rc != SQLITE_OK)
	{
		std::cerr << "Error: can't open database " << sqlite3_errmsg(db) << std::endl;
		return 0;
	}


	std::string sql = "SELECT * FROM USER WHERE USER_NAME = ? AND PASSWORD = ?";
	rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		std::cerr << "Error in Request " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return 0;
	}


	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);


	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW)
	{
		//the password correct
		passwordMatches = 1;
	}
	else if (rc != SQLITE_DONE)
	{
		std::cerr << "Error: not hetzliach" << sqlite3_errmsg(db) << std::endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return passwordMatches;
}


int SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{

	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	std::string sql;

	/* Open database */
	rc = sqlite3_open("triviaDb.db", &db);

	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else
	{
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create SQL statement */
	sql = "INSERT INTO USER (USER_NAME,PASSWORD,EMAIL) " \
		"VALUES ( '" + username + "', '" + password + "', '" + email + "' ); ";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Records created successfully\n");
	}
	sqlite3_close(db);

	return 0;
}


