
#include "Customer.h"
#include <sstream>

Customer::Customer(const std::string &cccd,
                const std::string &name,
                const std::string &phone,
                const std::string &email,
                const std::string &birthdate,
                const std::string &address)
:Person(cccd,name,phone,email),birthdate(birthdate), address(address){}

std::string Customer::getBirthdate() const{
    return birthdate;
}
std::string Customer::getAddress() const{
    return address;
}
void Customer::setBirthdate(const std::string &date){
    this->birthdate=date;
}

void Customer::setAddress(const std::string &addr){
    this->address=addr;
}
std::string Customer::toCSV() const {
    std::ostringstream oss;
    
    oss << cccd << "," << name << "," << phone << "," << email << "," << birthdate << "," << address;
    return oss.str();
}
