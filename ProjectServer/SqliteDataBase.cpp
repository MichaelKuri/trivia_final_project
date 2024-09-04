#include "SqliteDataBase.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "sqlite3.h"
#include "Question.h"

//open data base and create new tables: USER, Quiz, USERS_STATS
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
        "PASSWORD  TEXT NOT NULL," \
        "EMAIL     TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

     // Create table SQL statement
     const char* createTableSQL = R"(
     CREATE TABLE IF NOT EXISTS Quiz (
         id INTEGER PRIMARY KEY AUTOINCREMENT,
         question TEXT NOT NULL,
         answer1 TEXT NOT NULL,
         answer2 TEXT NOT NULL,
         answer3 TEXT NOT NULL,
         answer4 TEXT NOT NULL,
         correct_answer INTEGER NOT NULL
     );)";

     // Execute the SQL statement to create the table
     rc = sqlite3_exec(db, createTableSQL, NULL, 0, &zErrMsg);
     if (rc != SQLITE_OK) {
         std::cerr << "SQL error: " << zErrMsg << "\n";
         sqlite3_free(zErrMsg);
     }
     else {
         std::cout << "Table quiz created successfully\n";
     }

     // Insert questions into the table
     const char* insertSQL = R"(
     INSERT INTO Quiz (question, answer1, answer2, answer3, answer4, correct_answer) VALUES
     ('What is the capital of France?', 'Paris', 'London', 'Berlin', 'Madrid', 1),
     ('What is 2 + 2?', '3', '4', '5', '6', 2),
     ('What is the largest planet in our solar system?', 'Earth', 'Jupiter', 'Mars', 'Saturn', 2),
     ('What is the chemical symbol for water?', 'H2O', 'CO2', 'NaCl', 'O2', 1),
     ('Who wrote "To Kill a Mockingbird"?', 'Harper Lee', 'J.K. Rowling', 'Ernest Hemingway', 'F. Scott Fitzgerald', 1),
     ('What is the boiling point of water in Celsius?', '50', '75', '100', '125', 3),
     ('Which element has the chemical symbol "Au"?', 'Silver', 'Gold', 'Iron', 'Lead', 2),
     ('What is the square root of 16?', '2', '4', '6', '8', 2),
     ('Which planet is known as the Red Planet?', 'Venus', 'Mars', 'Jupiter', 'Mercury', 2),
     ('What is the hardest natural substance on Earth?', 'Gold', 'Diamond', 'Iron', 'Platinum', 2);
 )";

     // Execute the SQL statement to insert questions
     rc = sqlite3_exec(db, insertSQL, NULL, 0, &zErrMsg);
     if (rc != SQLITE_OK) {
         std::cerr << "SQL error: " << zErrMsg << "\n";
         sqlite3_free(zErrMsg);
     }
     else {
         std::cout << "Records inserted successfully\n";
     }

     //create usersStats
          // Create table SQL statement
     createTableSQL = R"(
     CREATE TABLE IF NOT EXISTS USERS_STATS (
         id INTEGER PRIMARY KEY AUTOINCREMENT,
         USERNAME         TEXT NOT NULL,
         AVREGE_TIME_ANS  REAL NOT NULL,
         CORRECT_ANS      INTEGER NOT NULL,
         TOTAL_ANS        INTEGER NOT NULL,
         NUM_OF_GAMES     INTEGER NOT NULL,
         SCORE            INTEGER NOT NULL
     );)";

     // Execute the SQL statement to create the table
     rc = sqlite3_exec(db, createTableSQL, NULL, 0, &zErrMsg);
     if (rc != SQLITE_OK) {
         std::cerr << "SQL error: " << zErrMsg << "\n";
         sqlite3_free(zErrMsg);
     }
     else {
         std::cout << "Table USERS_STATS created successfully\n";
         return true;
     }

     // Close the database connection
     sqlite3_close(db);

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

//check if user name exist in the table. return 0 if isn't exists
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

//check if password match to username
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

//add new user name, password, 
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

//callBack func for getQuestions quary
static int queryCallback(void* data, int argc, char** argv, char** azColName) {
	std::list<Question>* question = static_cast<std::list<Question> *>(data);;
	Question q(argv[1], argv[2], argv[3] , argv[4], argv[5], atoi(argv[2]));
	question->push_back(q);
	return 0;
}

//get list of quastions in size of numofQu 
std::list<Question> SqliteDataBase::getQuestions(int numOfQu)
{
	sqlite3* db;
	char* errMsg = 0;

	// Open a database connection
	int rc = sqlite3_open("questions.db", &db);
	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
		exit;
	}
	else {
		std::cout << "Opened database successfully\n";
	}

	// Query to retrieve 3 questions
	std::string querySQL = "SELECT * FROM Quiz LIMIT " + std::to_string(numOfQu) + ";";

	// Vector to hold the results
	std::list<Question> questions;

	// Execute the query
	rc = sqlite3_exec(db, querySQL.c_str(), queryCallback, &questions, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << "\n";
		sqlite3_free(errMsg);
	}
	else {
		std::cout << "Query executed successfully\n";
	}
	
	// Close the database connection
	sqlite3_close(db);
	return questions;
}

//get spesific player avrage answer time
float SqliteDataBase::getPlayerAverageAnswerTime(std::string userName)
{

    sqlite3* db;
    sqlite3_open("triviaDb.db", &db);

    float avregeTime = -1;
    std::string querySQL = "SELECT AVREGE_TIME_ANS FROM USERS_STATS WHERE USERNAME = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, querySQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return avregeTime;
    }

    // Bind the question text to the query
    sqlite3_bind_text(stmt, 1, userName.c_str(), -1, SQLITE_STATIC);

    // Execute the query and fetch the result
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        avregeTime = (float)(sqlite3_column_double(stmt, 0));
    }
    else {
        std::cerr << "No matching question found.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return avregeTime;
}

//get spesific player num of correct answer
int SqliteDataBase::getNumOfCorrectAnswers(std::string userName)
{
    sqlite3* db;
    sqlite3_open("triviaDb.db", &db);

    int correctAns = -1;
    std::string querySQL = "SELECT CORRECT_ANS FROM USERS_STATS WHERE USERNAME = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, querySQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return correctAns;
    }

    // Bind the question text to the query
    sqlite3_bind_text(stmt, 1, userName.c_str(), -1, SQLITE_STATIC);

    // Execute the query and fetch the result
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        correctAns = (int)(sqlite3_column_int(stmt, 0));
    }
    else {
        std::cerr << "No matching question found.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return correctAns;
}

//get spesific player num of total answer
int SqliteDataBase::getNumOfTotalAnswers(std::string userName)
{
    sqlite3* db;
    sqlite3_open("triviaDb.db", &db);

    int correctAns = -1;
    std::string querySQL = "SELECT TOTAL_ANS FROM USERS_STATS WHERE USERNAME = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, querySQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return correctAns;
    }

    // Bind the question text to the query
    sqlite3_bind_text(stmt, 1, userName.c_str(), -1, SQLITE_STATIC);

    // Execute the query and fetch the result
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        correctAns = (int)(sqlite3_column_int(stmt, 0));
    }
    else {
        std::cerr << "No matching question found.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return correctAns;
}

//get spesific player num of games
int SqliteDataBase::getNumOfPlayerGames(std::string userName)
{
    sqlite3* db;
    sqlite3_open("triviaDb.db", &db);

    int correctAns = -1;
    std::string querySQL = "SELECT NUM_OF_GAMES FROM USERS_STATS WHERE USERNAME = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, querySQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return correctAns;
    }

    // Bind the question text to the query
    sqlite3_bind_text(stmt, 1, userName.c_str(), -1, SQLITE_STATIC);

    // Execute the query and fetch the result
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        correctAns = (int)(sqlite3_column_int(stmt, 0));
    }
    else {
        std::cerr << "No matching question found.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return correctAns;
}

//get spesific player total score
int SqliteDataBase::getPlayerScore(std::string userName)
{
    sqlite3* db;
    sqlite3_open("triviaDb.db", &db);

    int correctAns = -1;
    std::string querySQL = "SELECT SCORE FROM USERS_STATS WHERE USERNAME = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, querySQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return correctAns;
    }

    // Bind the question text to the query
    sqlite3_bind_text(stmt, 1, userName.c_str(), -1, SQLITE_STATIC);

    // Execute the query and fetch the result
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        correctAns = (int)(sqlite3_column_int(stmt, 0));
    }
    else {
        std::cerr << "No matching question found.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return correctAns;
}

//get 3 high scores
std::vector<std::string> SqliteDataBase::getHighScores()
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::vector<std::string> topScores;

    // Open the database
    if (sqlite3_open("triviaDb.db", &db) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        return topScores; // Return an empty vector on error
    }

    // SQL query to get the top 3 scores
    const char* query = "SELECT score FROM USERS_STATS ORDER BY SCORE DESC LIMIT 3";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return topScores; // Return an empty vector on error
    }

    // Execute the statement and retrieve results
    while (true) {
        int rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            // Get the score from the first column
            int score = sqlite3_column_int(stmt, 0);
            topScores.push_back(std::to_string(score));
        }
        else if (rc == SQLITE_DONE) {
            // No more rows to process
            break;
        }
        else {
            std::cerr << "Execution error: " << sqlite3_errmsg(db) << "\n";
            break;
        }
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return topScores;
}
