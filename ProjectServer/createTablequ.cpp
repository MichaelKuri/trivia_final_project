#include <iostream>
#include "sqlite3.h"

// Callback function to handle the results of the SQL query
static int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    std::cout << "\n";
    return 0;
}

int qustcreate() {
    sqlite3* db;
    char* errMsg = 0;

    // Open a database connection
    int rc = sqlite3_open("questions.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        return 1;
    }
    else {
        std::cout << "Opened database successfully\n";
    }

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
        );
    )";

    // Execute the SQL statement to create the table
    rc = sqlite3_exec(db, createTableSQL, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Table created successfully\n";
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
    rc = sqlite3_exec(db, insertSQL, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Records inserted successfully\n";
    }

    // Close the database connection
    sqlite3_close(db);
    return 0;
}
