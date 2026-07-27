#ifndef YARDMANAGER_H
#define YARDMANAGER_H

#include <string>
#include <vector>

#include "../../model/ACCOUNT/Account.h"
#include "../../model/YARD/Yard.h"
#include "../../model/INVOICE/Invoice.h"
#include "../../model/CUSTOMER/Customer.h"
#include "../../model/EMPLOYEE/Employee.h"

class YardManager {
private:
    std::string dataDir;
    std::vector<Customer> customers;
    std::vector<Employee> employees;
    std::vector<Yard> yards;
    std::vector<Invoice> invoices;
    std::vector<Account> accounts;
    
    Account User;

public:
    YardManager(const std::string &dir = "data/");
    ~YardManager() = default;
    Yard* findYardById(const std::string &yardId);

    void loadAll();
    void saveAll() const;
    void runConsole();

    // Hệ thống xác thực và Menus điều hướng
    void loginMenu();
    void login();
    void dangkyAccount(); // Khách hàng tự đăng ký (Role = 2)
    void adminMenu();
    void employeeMenu();
    void customerMenu();
    void dangkyEmployeeAccount(); // Admin cấp tài khoản cho nhân viên (Role = 1)
    void changePassword();
    void forgotPassword();
    void viewCustomerInfo() const;
    void viewCustomerInvoice() const;
    std::string sinhInvoice() const; 

    // Quản lý khách hàng
    void customerManagerMenu();
    void addCustomer();
    void editCustomer();
    void deleteCustomer();
    void customerList() const;
    

    // Quản lý nhân viên
    void employeeManagerMenu();
    void addEmployee();
    void editEmployee();
    void deleteEmployee();
    void employeeList() const;

    // Quản lý sân
    void yardManagerMenu();
    void addYard();
    void bookYard();
    void returnYard();
    void editYard();
    void deleteYard();
    void yardList() const;

    //Tìm kiếm 
    void searchMenu() const;
    void searchYard() const;      
    void searchCustomer() const;  
    void searchInvoice() const;    

    // Thống kê
    void statsMenu() const;
    void statsRevenue() const;    
    void statsTopCustomer() const; 
    void statsEmployee() const; 
    void statsUsingYard() const;
    void statsTopYard() const;  
};
#endif
