#include "IDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

bool IDatabase::open()
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    const char *sql;
    rc = sqlite3_open("test.db", &db);
    
    /* Create SQL statement */
    sql = "CREATE TABLE WORDS(" \
          "USER_NAME TEXT PRIMERY KEY NOT NULL ," \
          "PASSWORD INT NOT NULL," \
          "EMAIL TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
    if (rc == SQLITE_OK)
    {
        return true;
    }
}
