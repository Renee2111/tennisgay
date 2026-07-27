#include "Employee.h"
#include <iomanip>
#include <sstream>
#include <limits>
#include <fstream>


Employee::Employee(const std::string &cccd,
                const std::string &name,
                const std::string &phone,
                const std::string &email,
                const std::string &position,
                double salary)
    : Person(cccd, name, phone, email),
    position(position),
    salary(salary) {

    }

std::string Employee::getPosition() const {
    return position;
}

void Employee::setPosition(const std::string &pos) {
    this->position = pos;
}

double Employee::getSalary() const {
    return salary;
}

void Employee::setSalary(double sal) {
    this->salary = sal;
}

std::string Employee::toCSV() const {
    std::ostringstream oss;
    
    oss << cccd << "," << name << "," << phone << "," << email << ","
        << position << "," 
        <<std::fixed<< std::setprecision(2) << salary;
    return oss.str();
}
void Employee::fromCSV(const std::string &line){
        std::stringstream ss(line);
        std::string temp;
        getline(ss, cccd, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, position, ',');
        getline(ss, temp);
        salary = std::stod(temp);
}
