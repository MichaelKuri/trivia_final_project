#include "LoginManager.h"

bool LoginManager::signup(std::string username, std::string password, std::string email)
{
    _m_database->addNewUser(username, password, email);
    return true;
}

bool LoginManager::login(std::string username, std::string password)
{
    int i = _m_database->doesUserExist(username);
    int j = _m_database->doesPasswordMatch(username, password);
    if (i && j) 
    {
        _m_loggedUsers.push_back(LoggedUser(username));
        return true;
    }
    return false;
}

bool LoginManager::logout(std::string username)
{

    for (auto itr = _m_loggedUsers.begin(); itr != _m_loggedUsers.end(); itr++)
    {
        if (itr->getUsername() == username) {
            _m_loggedUsers.erase(itr);
            return true;
        }
    }
    return false;
}
