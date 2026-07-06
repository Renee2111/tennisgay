#ifndef INVOICE_H
#define INVOICE_H
#include<string>

class Invoice{

    private:
        std::string invoiceId;
        std::string customerCccd;
        std::string employeeCccd;
        std::string yardId;
        std::string dateFrom;
        std::string dateTo;
        double total=0.0;

    public:
        Invoice()= default;
        Invoice(const std::string &invoiceId,
                const std::string &customerCccd,
                const std::string &employeeCccd,
                const std::string &yardId,
                const std::string &dateFrom,
                const std::string &dateTo,
                double total);

        std::string getInvoiceId() const;
        std::string getCustomerCccd() const;
        std::string getEmployeeCccd() const;
        std::string getYardId() const;
        std::string getDateFrom() const;
        std::string getDateTo() const;
        double getTotal() const;
    
        void setInvoiceId(const std::string &id);
        void setCustomerCccd(const std::string &cccd);
        void setEmployeeCccd(const std::string &cccd);
        void setYardId(const std::string &id);
        void setDateFrom(const std::string &date);
        void setDateTo(const std::string &date);
        void setTotal(double amount);
        std::string toCSV() const;

};

#endif 

