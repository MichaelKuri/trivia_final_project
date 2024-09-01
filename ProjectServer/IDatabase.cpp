#include "IDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

bool IDatabase::open()
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db);

}
