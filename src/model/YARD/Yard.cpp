#include "Yard.h"
#include <sstream>
#include <iomanip>

Yard::Yard(const std::string &yardId, const std::string &yardType, double pricePerHour, bool available)
    : yardId(yardId), yardType(yardType), pricePerHour(pricePerHour), available(available) {}

std::string Yard::getYardId() const {
    return yardId;
}
std::string Yard::getYardType() const {
    return yardType;
}
double Yard::getPricePerHour() const {
    return pricePerHour;
}
bool Yard::getAvailable() const {
    return available;
}

void Yard::setYardType(const std::string &type) {
    this->yardType = type;
}
void Yard::setPricePerHour(double price) {
    this->pricePerHour = price;
}
void Yard::setAvailable(bool avail) {
    this->available = avail;
}
std::string Yard::toCSV() const {
    std::ostringstream oss;
    oss << yardId << "," 
        << yardType << "," 
        << std::fixed << std::setprecision(2) << pricePerHour << "," 
        << (available ? "1" : "0");
    return oss.str();
}