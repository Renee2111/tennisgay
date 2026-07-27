#include "Invoice.h"
#include <sstream>
#include <iomanip>

Invoice::Invoice(const std::string &invoiceId,
                 const std::string &customerCccd,
                 const std::string &employeeCccd,
                 const std::string &yardId,
                 const std::string &dateFrom,
                 const std::string &dateTo,
                 double total)
    : invoiceId(invoiceId), customerCccd(customerCccd), employeeCccd(employeeCccd),
      yardId(yardId), dateFrom(dateFrom), dateTo(dateTo), total(total) {} 

std::string Invoice::getInvoiceId() const { 
    return invoiceId; 
}
std::string Invoice::getCustomerCccd() const { 
    return customerCccd; 
}
std::string Invoice::getEmployeeCccd() const { 
    return employeeCccd; 
}
std::string Invoice::getYardId() const { 
    return yardId; 
}
std::string Invoice::getDateFrom() const { 
    return dateFrom; 
}
std::string Invoice::getDateTo() const { 
    return dateTo; 
}
double Invoice::getTotal() const { 
    return total; 
}

void Invoice::setInvoiceId(const std::string &id) { 
    this->invoiceId = id; 
}
void Invoice::setCustomerCccd(const std::string &cccd) { 
    this->customerCccd = cccd; 
}
void Invoice::setEmployeeCccd(const std::string &cccd) { 
    this->employeeCccd = cccd; 
}
void Invoice::setYardId(const std::string &id) { 
    this->yardId = id; 
}
void Invoice::setDateFrom(const std::string &date) {    
    this->dateFrom = date; 
}
void Invoice::setDateTo(const std::string &date) {
    this->dateTo = date; 
}
void Invoice::setTotal(double amount) { 
    this->total = amount; 
}

std::string Invoice::toCSV() const {
    std::ostringstream oss;
    oss << invoiceId << "," << customerCccd << "," << employeeCccd << ","
        << yardId << "," << dateFrom << "," << dateTo << ","
        << std::fixed << std::setprecision(2) << total;
    return oss.str();
}
void Invoice::fromCSV(const std::string &line){
        std::stringstream ss(line);
        std::string temp;
        getline(ss, invoiceId, ',');
        getline(ss, customerCccd, ',');
        getline(ss, employeeCccd, ',');
        getline(ss, yardId, ',');
        getline(ss, dateFrom, ',');
        getline(ss, dateTo, ',');
        getline(ss, temp);
        total = std::stod(temp);
}