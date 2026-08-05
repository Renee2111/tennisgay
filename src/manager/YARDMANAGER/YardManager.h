#ifndef YARDMANAGER_H
#define YARDMANAGER_H

#include <vector>
#include <string>

// Cập nhật lại đường dẫn tới các Model nếu cần thiết
#include "../../model/ACCOUNT/Account.h"
#include "../../model/CUSTOMER/Customer.h"
#include "../../model/EMPLOYEE/Employee.h"
#include "../../model/YARD/Yard.h"
#include "../../model/INVOICE/Invoice.h"

class YardManager {
private:
    std::string dataDir;
    std::vector<Account> accounts;
    std::vector<Customer> customers;
    std::vector<Employee> employees;
    std::vector<Yard> yards;
    std::vector<Invoice> invoices;

public:
    // Constructor
    YardManager(const std::string &dir);

    // File Handling
    void loadAll();
    void saveAll();

    // Getters
    std::vector<Account>& getAccounts();
    std::vector<Customer>& getCustomers();
    std::vector<Employee>& getEmployees();
    std::vector<Yard>& getYards();
    std::vector<Invoice>& getInvoices();

    // ================= CRUD Khách hàng =================
    bool addCustomer(const Customer &c);
    bool editCustomer(const Customer &c);
    bool deleteCustomer(const std::string& cccd);
    Customer* findCustomer(const std::string& cccd);

    // ================= CRUD Nhân viên =================
    bool addEmployee(const Employee &e);
    bool editEmployee(const Employee &e);
    bool deleteEmployee(const std::string &cccd);
    Employee* findEmployee(const std::string &cccd);

    // ================= CRUD Sân Tennis =================
    bool addYard(const Yard &y);
    bool editYard(const Yard &y);
    bool deleteYard(const std::string &id);
    Yard* findYardById(const std::string &id);

    // ================= Hóa đơn & Nghiệp vụ cho UI =================
    bool addInvoice(const Invoice &i);
    std::string sinhInvoice() const;

    // Các hàm tương tác với UI (Web/Mobile)
    bool bookYardFromUI(const std::string &customerCccd, const std::string &employeeCccd, 
                        const std::string &yardId, const std::string &fromDate, 
                        const std::string &toDate, int hours, double &outTotal, std::string &outInvoiceId);
                        
    bool returnYardFromUI(const std::string &yardId);
};

#endif // YARDMANAGER_H