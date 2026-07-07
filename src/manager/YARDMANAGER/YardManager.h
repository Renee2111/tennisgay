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
    void editYard();
    void deleteYard();
    void yardList() const;

    // Chức năng tìm kiếm theo đúng tiêu chuẩn
    void searchMenu() const;
    void searchYard() const;       // Tìm sân theo ID
    void searchCustomer() const;   // Tìm khách hàng theo CCCD
    void searchInvoice() const;    // Tìm hóa đơn theo ID

    // Chức năng thống kê
    void statsMenu() const;
    void statsRevenue() const;     // Thống kê doanh thu
    void statsTopCustomer() const; // Tìm khách hàng đứng đầu chi tiêu
    void statsEmployee() const;    // Thống kê hóa đơn theo nhân viên
};

#endif