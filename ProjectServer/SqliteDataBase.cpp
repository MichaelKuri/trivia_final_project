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
        return true;
    }
}

//check if user name exsist in the table TO DO: check if work
int SqliteDataBase::doesUserExist(std::string username)
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    std::string sql;

    /* Open database */
    rc = sqlite3_open("triviaDb.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }
    sql = "Select * from COMPANY where USER_NAME = " + username + '"';
    struct sqlite3_stmt* selectstmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &selectstmt, NULL);
    if (result == SQLITE_OK)
    {
        if (sqlite3_step(selectstmt) == SQLITE_ROW)
        {
            std::cout << "find the user";
        }
        else
        {
            std::cout << "user dosent exsist";
        }
    }
    sqlite3_finalize(selectstmt);
}

int SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    std::string sql;

    /* Open database */
    rc = sqlite3_open("triviaDb.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }
    sql = "Select * from COMPANY where USER_NAME = " + username +"AND PASSWORD = " + password + '"';
    struct sqlite3_stmt* selectstmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &selectstmt, NULL);
    if (result == SQLITE_OK)
    {
        if (sqlite3_step(selectstmt) == SQLITE_ROW)
        {
            std::cout << "password match";
        }
        else
        {
            std::cout << "incorect password";
        }
    }
    sqlite3_finalize(selectstmt);
}

int SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{

    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    std::string sql;

    /* Open database */
    rc = sqlite3_open("triviaDb.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sql = "INSERT INTO USER (USER_NAME,PASSWORD,EMAIL) " \
        "VALUES ( '"+ username +"', '"+password +"', '"+email+"' ); ";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);

    return 0;
}


