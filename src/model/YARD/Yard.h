#ifndef YARD_H
#define YARD_H

#include <string>

class Yard {
private:
    std::string yardId;
    std::string yardType;
    double pricePerHour;
    bool available;

public:
    Yard(const std::string &yardId = "", const std::string &yardType = "", 
         double pricePerHour = 0.0, bool available = true);

    std::string getYardId() const;
    std::string getYardType() const;
    double getPricePerHour() const;
    bool getAvailable() const;

    void setYardType(const std::string &type);
    void setPricePerHour(double price);
    void setAvailable(bool avail);

    std::string toCSV() const;
};

#endif