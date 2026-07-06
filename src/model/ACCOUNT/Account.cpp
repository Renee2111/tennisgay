#include "Account.h"
#include <sstream>

Account::Account(const std::string &username,
                 const std::string &password,
                 int role,
                 const std::string &cccd)
    : username(username), password(password), role(role), cccd(cccd) {}

std::string Account::getUsername() const {
    return username;
}
void Account::setUsername(const std::string &username) {
    this->username = username;
}
std::string Account::getPassword() const {
    return password;
}
void Account::setPassword(const std::string &password) {
    this->password = password;
}
int Account::getRole() const {
    return role;
}
void Account::setRole(int role) {
    this->role = role;
}
std::string Account::getCccd() const {
    return cccd;
}
void Account::setCccd(const std::string &cccd) {
    this->cccd = cccd;
}
std::string Account::toCSV() const {
    std::ostringstream oss;
    oss << username << "," 
        << password << "," 
        << role << "," 
        << cccd;
    return oss.str();
}