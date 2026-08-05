#include "YardManager.h"
#include "../../util/FILEHANDLER/FileHandler.h"

YardManager::YardManager(const std::string &dir)
{
    dataDir = dir;
    if (!dataDir.empty() && dataDir.back() != '/' && dataDir.back() != '\\') {
        dataDir += "/";
    }
}

void YardManager::loadAll()
{
    customers.clear();
    employees.clear();
    yards.clear();
    invoices.clear();
    accounts.clear();

    std::string *lines = nullptr;
    int count = 0;

    count = FileHandler::readFile(dataDir + "accounts.csv", lines);
    for(int i = 0; i < count; i++) {
        Account a;
        a.fromCSV(lines[i]);
        accounts.push_back(a);
    }
    delete[] lines;

    count = FileHandler::readFile(dataDir + "customers.csv", lines);
    for(int i = 0; i < count; i++) {
        Customer c;
        c.fromCSV(lines[i]);
        customers.push_back(c);
    }
    delete[] lines;

    count = FileHandler::readFile(dataDir + "employees.csv", lines);
    for(int i = 0; i < count; i++) {
        Employee e;
        e.fromCSV(lines[i]);
        employees.push_back(e);
    }
    delete[] lines;

    count = FileHandler::readFile(dataDir + "yards.csv", lines);
    for(int i = 0; i < count; i++) {
        Yard y;
        y.fromCSV(lines[i]);
        yards.push_back(y);
    }
    delete[] lines;

    count = FileHandler::readFile(dataDir + "invoices.csv", lines);
    for(int i = 0; i < count; i++) {
        Invoice inv;
        inv.fromCSV(lines[i]);
        invoices.push_back(inv);
    }
    delete[] lines;
}

void YardManager::saveAll()
{
    std::string *lines;

    lines = new std::string[accounts.size()];
    for(size_t i = 0; i < accounts.size(); i++)
        lines[i] = accounts[i].toCSV();
    FileHandler::writeFile(dataDir + "accounts.csv", lines, accounts.size());
    delete[] lines;

    lines = new std::string[customers.size()];
    for(size_t i = 0; i < customers.size(); i++)
        lines[i] = customers[i].toCSV();
    FileHandler::writeFile(dataDir + "customers.csv", lines, customers.size());
    delete[] lines;

    lines = new std::string[employees.size()];
    for(size_t i = 0; i < employees.size(); i++)
        lines[i] = employees[i].toCSV();
    FileHandler::writeFile(dataDir + "employees.csv", lines, employees.size());
    delete[] lines;

    lines = new std::string[yards.size()];
    for(size_t i = 0; i < yards.size(); i++)
        lines[i] = yards[i].toCSV();
    FileHandler::writeFile(dataDir + "yards.csv", lines, yards.size());
    delete[] lines;

    lines = new std::string[invoices.size()];
    for(size_t i = 0; i < invoices.size(); i++)
        lines[i] = invoices[i].toCSV();
    FileHandler::writeFile(dataDir + "invoices.csv", lines, invoices.size());
    delete[] lines;
}

// Getters
std::vector<Account>& YardManager::getAccounts()
{
    return accounts;
}

std::vector<Customer>& YardManager::getCustomers()
{
    return customers;
}

std::vector<Employee>& YardManager::getEmployees()
{
    return employees;
}

std::vector<Yard>& YardManager::getYards()
{
    return yards;
}

std::vector<Invoice>& YardManager::getInvoices()
{
    return invoices;
}

// ================= Khách hàng (Customer) =================
bool YardManager::addCustomer(const Customer &c)
{
    if(findCustomer(c.getCccd()) != nullptr)
        return false;

    customers.push_back(c);
    saveAll();
    return true;
}

bool YardManager::editCustomer(const Customer &c)
{
    Customer *p = findCustomer(c.getCccd());
    if(p == nullptr)
        return false;

    *p = c;
    saveAll();
    return true;
}

bool YardManager::deleteCustomer(const std::string& cccd)
{
    for(auto it = customers.begin(); it != customers.end(); it++) {
        if(it->getCccd() == cccd) {
            customers.erase(it);
            saveAll();
            return true;
        }
    }
    return false;
}

Customer* YardManager::findCustomer(const std::string& cccd)
{
    for(auto &c : customers)
        if(c.getCccd() == cccd)
            return &c;

    return nullptr;
}

// ================= Nhân viên (Employee) =================
bool YardManager::addEmployee(const Employee &e)
{
    if(findEmployee(e.getCccd()) != nullptr)
        return false;

    employees.push_back(e);
    saveAll();
    return true;
}

bool YardManager::editEmployee(const Employee &e)
{
    Employee *p = findEmployee(e.getCccd());
    if(p == nullptr)
        return false;

    *p = e;
    saveAll();
    return true;
}

bool YardManager::deleteEmployee(const std::string &cccd)
{
    for(auto it = employees.begin(); it != employees.end(); it++) {
        if(it->getCccd() == cccd) {
            employees.erase(it);
            saveAll();
            return true;
        }
    }
    return false;
}

Employee* YardManager::findEmployee(const std::string &cccd)
{
    for(auto &e : employees)
        if(e.getCccd() == cccd)
            return &e;
    return nullptr;
}

// ================= Sân (Yard) =================
bool YardManager::addYard(const Yard &y)
{
    if(findYardById(y.getYardId()) != nullptr) 
        return false;

    yards.push_back(y);
    saveAll();
    return true;
}

bool YardManager::editYard(const Yard &y)
{
    Yard *p = findYardById(y.getYardId());
    if(p == nullptr)
        return false;

    *p = y;
    saveAll();
    return true;
}

bool YardManager::deleteYard(const std::string &id)
{
    for(auto it = yards.begin(); it != yards.end(); it++) {
        if(it->getYardId() == id) {
            yards.erase(it);
            saveAll();
            return true;
        }
    }
    return false;
}

Yard* YardManager::findYardById(const std::string &id)
{
    for(auto &y : yards)
        if(y.getYardId() == id)
            return &y;

    return nullptr;
}

// ================= Hóa đơn (Invoice) =================
bool YardManager::addInvoice(const Invoice &i)
{
    invoices.push_back(i);
    saveAll();
    return true;
}

std::string YardManager::sinhInvoice() const
{
    return "HD" + std::to_string(invoices.size() + 1);
}

// Thêm 2 hàm này vào YardManager.cpp (các hàm Load/Save/CRUD Customer, Yard giữ nguyên như Source 3)[cite: 3]

// Đặt sân từ UI: Truyền tham số thẳng từ Form[cite: 5]
bool YardManager::bookYardFromUI(const std::string &customerCccd, const std::string &employeeCccd, 
                                 const std::string &yardId, const std::string &fromDate, 
                                 const std::string &toDate, int hours, double &outTotal, std::string &outInvoiceId) 
{
    Yard *yard = findYardById(yardId);
    if (yard == nullptr || !yard->getAvailable()) {
        return false; // UI hiển thị: "Không tìm thấy sân hoặc sân đã bị đặt!"[cite: 5]
    }

    // Tính tổng tiền[cite: 5]
    outTotal = hours * yard->getPricePerHour();

    // Cập nhật trạng thái sân[cite: 5]
    yard->setAvailable(false);

    // Tạo hóa đơn[cite: 5]
    outInvoiceId = sinhInvoice(); 
    invoices.push_back(Invoice(outInvoiceId, customerCccd, employeeCccd, yardId, fromDate, toDate, outTotal));

    saveAll();
    return true; // Trả về true, UI sẽ render thông báo thành công kèm hóa đơn
}

// Trả sân từ UI[cite: 5]
bool YardManager::returnYardFromUI(const std::string &yardId) {
    Yard *yard = findYardById(yardId);
    if (yard == nullptr || yard->getAvailable()) {
        return false; // Sân không tồn tại hoặc đang trống[cite: 5]
    }
    
    yard->setAvailable(true); // Đổi lại thành trống[cite: 5]
    saveAll();
    return true;
}

