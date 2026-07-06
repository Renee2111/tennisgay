// Person.h
#ifndef PERSON_H
#define PERSON_H
#include <string>

class Person {
protected:
    std::string cccd;
    std::string name;
    std::string phone;
    std::string email;
public:
    Person( const std::string &cccd, 
            const std::string &name,
            const std::string &phone,
            const std::string &email);
            
    virtual ~Person() = default;

    std::string getCccd() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;

    void setName(const std::string &name);
    void setPhone(const std::string &phone);
    void setEmail(const std::string &email);
    virtual std::string toCSV() const = 0;
};
#endif

