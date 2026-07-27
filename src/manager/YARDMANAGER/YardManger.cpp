#include "YardManager.h"
#include "../../util/FILEHANDLER/FileHandler.h"
#include "../../util/TIME/Time.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

YardManager::YardManager(const std::string &dir) : dataDir(dir) {}

void YardManager::runConsole() {
    loadAll();
    loginMenu();
    saveAll();
}
Yard* YardManager::findYardById(const std::string& yardId) {
    for (auto& yard : yards) { 
        if (yard.getYardId() == yardId) {
            return &yard;
        }
    }
    return nullptr; 
}
void YardManager::loadAll() {
    std::string* lines = nullptr; int count = 0;
    count = FileHandler::readFile(dataDir + "accounts.csv", lines);
    for (int i = 0; i < count; ++i) { Account acc; acc.fromCSV(lines[i]); accounts.push_back(acc); }
    delete[] lines;
    count = FileHandler::readFile(dataDir + "yards.csv", lines);
    for (int i = 0; i < count; ++i) { Yard y; y.fromCSV(lines[i]); yards.push_back(y); }
    delete[] lines;
    count = FileHandler::readFile(dataDir + "customers.csv", lines);
    for (int i = 0; i < count; ++i) { Customer c; c.fromCSV(lines[i]); customers.push_back(c); }
    delete[] lines;
    count = FileHandler::readFile(dataDir + "employees.csv", lines);
    for (int i = 0; i < count; ++i) { Employee e; e.fromCSV(lines[i]); employees.push_back(e); }
    delete[] lines;
    count = FileHandler::readFile(dataDir + "invoices.csv", lines);
    for (int i = 0; i < count; ++i) { Invoice inv; inv.fromCSV(lines[i]); invoices.push_back(inv); }
    delete[] lines;
}

void YardManager::saveAll() const {
    std::string* lines = nullptr;
    lines = new std::string[accounts.size()];
    for (size_t i = 0; i < accounts.size(); ++i) lines[i] = accounts[i].toCSV();
    FileHandler::writeFile(dataDir + "accounts.csv", lines, accounts.size()); delete[] lines;
    lines = new std::string[yards.size()];
    for (size_t i = 0; i < yards.size(); ++i) lines[i] = yards[i].toCSV();
    FileHandler::writeFile(dataDir + "yards.csv", lines, yards.size()); delete[] lines;
    lines = new std::string[customers.size()];
    for (size_t i = 0; i < customers.size(); ++i) lines[i] = customers[i].toCSV();
    FileHandler::writeFile(dataDir + "customers.csv", lines, customers.size()); delete[] lines;
    lines = new std::string[employees.size()];
    for (size_t i = 0; i < employees.size(); ++i) lines[i] = employees[i].toCSV();
    FileHandler::writeFile(dataDir + "employees.csv", lines, employees.size()); delete[] lines;
    lines = new std::string[invoices.size()];
    for (size_t i = 0; i < invoices.size(); ++i) lines[i] = invoices[i].toCSV();
    FileHandler::writeFile(dataDir + "invoices.csv", lines, invoices.size()); delete[] lines;
}

//He thong xac thuc
void YardManager::loginMenu(){
    int lc;
    do{
        std::cout<<"\n==== TENNIS MANAGER ====\n";
        std::cout<<"1.Dang nhap\n2.Dang ky\n3.Quen Mat Khau\n0.Luu va Thoat\nLua chon cua ban la: ";
        if (!(std::cin >> lc)) {
            std::cout << "Lua chon khong hop le!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (lc)
        {
            case 1:  
                login();
                break;
            case 2:
                dangkyAccount();
                break;
            case 3:
                forgotPassword();
                break;
            case 0: 
                std::cout<<"Da luu va Thoat...!\n";
                break;
            default:
                std::cout<<"Lua chon khong hop le. Vui long nhap lai!\n";
                break;
        }
    }while(lc != 0 );
}
void YardManager::login() {
    std::string username, password;

    while (true) {
        std::cout << "\n==== DANG NHAP ====\n";
        std::cout << "Nhap ten dang nhap (hoac nhap 'exit' de quay lai): "; 
        std::cin >> username;
        
        if (username == "exit") {
            return; 
        }

        std::cout << "Password: "; 
        std::cin >> password;

        bool success = false;
        for (const auto &acc : accounts) {
            if (acc.getUsername() == username && acc.getPassword() == password) {
                User = acc; 
                success = true;
                std::cout << "\nDang nhap thanh cong! Xin chao " << username << ".\n";

                if (acc.getRole() == 0) {
                    adminMenu();
                } else if (acc.getRole() == 1) {
                    employeeMenu();
                } else if (acc.getRole() == 2) {
                    customerMenu();
                }
                return; 
            }
        }

        if (!success) {
            std::cout << "\nSai tai khoan hoac mat khau. Hay thuc hien lai!\n";
        }
    }
}
void YardManager::dangkyAccount(){
    std::string username, password,cccd;
    std::cout<<"\nDANG KY TAI KHOAN KHACH HANG\n";
    while(true){
        std::cout<<"Nhap ten dang nhap: ";
        std::cin>>username;
        bool kt=false;
        for(const auto &acc : accounts){
            if(acc.getUsername() == username){
                std::cout<<"Ten dang nhap da ton tai. Hay chon ten khac!\n";
                kt=true;
                return;
            }
        }
        if(kt == false) break;
    }
    std::cout<<"Nhap mat khau: ";
    std::cin>>password;
    std::cout<<"Nhap so Cccd cua ban: ";
    std::cin>>cccd;

    bool hasProfile = false;
    for(const auto &c : customers){
        if(c.getCccd() == cccd){
            hasProfile=true;
            break;
        }
    }
    if (!hasProfile) {
        std::string name, phone, email, birth, addr;
        if (std::cin.peek() == '\n') {
        std::cin.ignore();
        }
        std::cout << "Nhap thong tin ca nhan cua ban:\nHo ten: "; 
        std::getline(std::cin, name);
        std::cout << "So dien thoai: "; std::getline(std::cin,phone);
        std::cout << "Email: "; std::getline(std::cin,email);
        std::cout << "Ngay sinh (YYYY-MM-DD): "; std::getline(std::cin,birth);
        std::cout << "Dia chi: "; std::getline(std::cin, addr);
        
        customers.push_back(Customer(cccd, name, phone, email, birth, addr));
    }

    accounts.push_back(Account(username, password, 2, cccd));
    saveAll();
    std::cout << "-> Dang ky tai khoan Khach hang thanh cong!\n";
    
}

void YardManager::adminMenu() {
    int choice;
    do {
        std::cout << "\n===== MENU QUAN TRI (ADMIN) =====\n";
        std::cout << "1. Quan ly khach hang\n2. Quan ly nhan vien\n3. Quan ly san tennis\n4. Cong cu tim kiem\n5. Bao cao thong ke\n6. Cap tai khoan cho Nhan vien\n0. Dang xuat\nLua chon: ";
        if (!(std::cin >> choice)) {
            std::cout << "Lua chon khong hop le!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: customerManagerMenu(); break;
            case 2: employeeManagerMenu(); break;
            case 3: yardManagerMenu(); break;
            case 4: searchMenu(); break;
            case 5: statsMenu(); break;
            case 6: dangkyEmployeeAccount(); break;
             case 0:
                std::cout << "Thoat...\n";
                break;
            default:
                std::cout << "Lua chon khong hop le. Vui long nhap lai!\n";
                break;
        }
    } while (choice != 0);
}
void YardManager::employeeMenu() {
    int choice;
    do {
        std::cout << "===== GIAO DIEN NHAN VIEN =====\n";
        std::cout << "1. Xem danh sach san Tennis hien tai va Dat san cho Khach hang\n";
        std::cout << "2. Trả sân\n";
        std::cout << "3. Xem danh sach Khach hang\n";
        std::cout << "4. Them moi ho so Khach hang (Khi co khach moi)\n";
        std::cout << "5. Cong cu tim kiem nhanh (San/Khach hang/Hoa don)\n";
        std::cout << "6. Khach hang quen mat khat\n";
        std::cout << "0. Dang xuat (Quay lai man hinh chinh)\n";
        std::cout << "=========================================\n";
        std::cout << "Lua chon cua ban: ";

        if (!(std::cin >> choice)) {
            std::cout << "Lua chon khong hop le!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                yardList();
                char ch;
                std::cout << "\nBan co muon dat san cho khach khong? (Y/N): ";
                std::cin >> ch;
                if (ch == 'Y' || ch == 'y') {
                    bookYard();
                }
                break;
            case 2:
                returnYard();
                break;
            case 3:
                customerList();
                break;
            case 4:
                addCustomer();
                break;
            case 5:
                searchMenu(); 
                break;
            case 6:
                forgotPassword();
                break;
            case 0:
                std::cout << "Nhan vien da dang xuat an toan.\n";
                break;
            default:
                std::cout << "Lua chon khong hop le. Vui long nhap lai!\n";
                break;
        }
    } while (choice != 0);
}
void YardManager::customerMenu() {
    int choice;
    do {
        std::cout << "===== GIAO DIEN KHACH HANG =====\n";
        std::cout << "1. Xem danh sach san va gia thue (Tim san trong)\n";
        std::cout << "2. Xem thong tin ca nhan \n";
        std::cout << "3. Xem hoa don ca nhan\n";
        std::cout << "4. Doi mat khau\n";
        std::cout << "0. Dang xuat (Quay lai man hinh chinh)\n";
        std::cout << "Lua chon cua ban: ";

        if (!(std::cin >> choice)) {
            std::cout << "Lua chon khong hop le!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "\n==== TINH TRANG CAC SAN TENNIS CO THE THUE ====\n";
                yardList(); 
                bookYard();
                break;
            case 2:
                viewCustomerInfo();
                break;
            case 3:
                viewCustomerInvoice();
                break;
            case 4:
                changePassword();
                break;
            case 0:
                std::cout << "Khach hang da thoat tai khoan.\n";
                break;
            default:
                std::cout << "Lua chon khong hop le. Vui long nhap lai!\n";
                break;
        }
    } while (choice != 0);
}
void YardManager:: viewCustomerInfo() const {
    std::string cccd = User.getCccd();

    std::cout << "\n===== THONG TIN CA NHAN =====\n";

    for (const auto &c : customers) {
        if (c.getCccd() == cccd) {
            std::cout << "CCCD: " << c.getCccd() << '\n';
            std::cout << "Ho ten: " << c.getName() << '\n';
            std::cout << "So dien thoai: " << c.getPhone() << '\n';
            std::cout << "Email: " << c.getEmail() << '\n';
            std::cout << "Ngay sinh: " << c.getBirthdate() << '\n';
            std::cout << "Dia chi: " << c.getAddress() << '\n';
            return;
        }
    }

    std::cout << "Khong tim thay thong tin khach hang!\n";
}
void YardManager::viewCustomerInvoice() const {
    std::string cccd = User.getCccd();

    std::cout << "\n===== HOA DON CUA BAN =====\n";

    bool found = false;

    for (const auto &i : invoices) {
        if (i.getCustomerCccd() == cccd) {
            std::cout << i.toCSV() << '\n';
            found = true;
        }
    }

    if (!found) {
        std::cout << "Ban chua co hoa don nao!\n";
    }
}
std::string YardManager::sinhInvoice() const {
    int id = invoices.size() + 1;

    std::ostringstream oss;
    oss << "HD" << std::setw(3) << std::setfill('0') << id;

    return oss.str();
}
void YardManager::changePassword() {
    std::string oldPass, newPass, confirmPass;
    std::cout << "\n===== DOI MAT KHAU =====\n";
    std::cout << "Nhap mat khau hien tai: ";
    std::cin >> oldPass;
    if (oldPass != User.getPassword()) {
        std::cout << "Mat khau hien tai khong dung!\n";
        return;
    }
    std::cout << "Nhap mat khau moi: ";
    std::cin >> newPass;

    std::cout << "Nhap lai mat khau moi: ";
    std::cin >> confirmPass;

    if (newPass != confirmPass) {
        std::cout << "Hai mat khau khong khop!\n";
        return;
    }

    for (auto &acc : accounts) {
        if (acc.getUsername() == User.getUsername()) {
            acc.setPassword(newPass);
            User.setPassword(newPass);
            saveAll();
            std::cout << "Doi mat khau thanh cong!\n";
            return;
        }
    }
}
void YardManager::forgotPassword() {
    std::string username, cccd, newPass;

    std::cout << "\n===== QUEN MAT KHAU =====\n";
    std::cout << "Nhap ten dang nhap: ";
    std::cin >> username;

    std::cout << "Nhap CCCD: ";
    std::cin >> cccd;

    for (auto &acc : accounts) {

        if (acc.getUsername() == username && acc.getCccd() == cccd) {
            // Chỉ khách hàng mới được sử dụng
            if (acc.getRole() != 2) {
                std::cout << "Chuc nang nay chi ap dung cho tai khoan Khach hang!\n";
                return;
            }
            std::cout << "Nhap mat khau moi: ";
            std::cin >> newPass;
            acc.setPassword(newPass);
            std::cout << "Dat lai mat khau thanh cong!\n";
            return;
        }
    }
    std::cout << "Sai ten dang nhap hoac CCCD!\n";
}


void YardManager::dangkyEmployeeAccount(){
    std::string u, p, cccd;
    std::cout << "\n--- ADMIN: CAP TAI KHOAN CHO NHAN VIEN MOI ---\n";
    std::cout << "Nhap Ten dang nhap cap cho NV: "; std::cin >> u;
    bool check=false;
    while(true){
        for (const auto &acc : accounts) {
            if (acc.getUsername() == u) {
                std::cout << "Ten dang nhap da ton tai tren he thong!\n";
                check =true;
                return;
            }
        }
        if(check==false) break;
    }
    std::cout << "Nhap Mat khau cap cho NV: "; std::cin >> p;
    std::cout << "Nhap dung so CCCD cua Nhan vien: "; std::cin >> cccd;
    bool hasProfile = false;
    for (const auto &e : employees) {
        if (e.getCccd() == cccd) { 
            hasProfile = true; 
            break; 
        }
    }

    if (!hasProfile) {
        std::cout << "CCCD nay chua co trong danh sach quản lý. Vui long vao muc 'Quan ly nhan vien' de tao ho so truoc!\n";
        return;
    }
    accounts.push_back(Account(u, p, 1, cccd));
    saveAll();
    std::cout << "Cap tai khoan Nhan vien thanh cong. Nhan vien co the dang nhap ngay!\n";
}


void YardManager::customerManagerMenu(){
    int choice;
    do{
        std::cout<<"\n==== QUAN LY KHACH HANG ====\n";
        std::cout<<"1.Them khanh hang\n";
        std::cout<<"2.Sua thong tin\n";
        std::cout<<"3.Xoa\n";
        std::cout<<"4.Xem danh sach Khach Hang\n";
        std::cout<<"0.Quay lai \nLua chon: ";

        if (!(std::cin >> choice)) {
            std::cout << "Lua chon khong hop le!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            addCustomer();
            break;
        case 2:
            editCustomer();
            break;
        case 3:
            deleteCustomer();
            break;
        case 4:
            customerList();
            break;
        case 0:
            std::cout<<"Quay lai...\n";
            break;
        default:
            std::cout<<"Lua chon khong hop le. Vui long nhap lai!\n";
            break;
        }
    }while(choice != 0);
}

void YardManager:: addCustomer(){
    std::string cccd, name, phone, email,birth,addr;
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::cout<<"CCCD: "; std::getline(std::cin,cccd);
    std::cout<<"Ho ten: "; std::getline(std::cin,name);
    std::cout<<"So dien thoai: "; std::getline(std::cin,phone);
    std::cout<<"Email: "; std::getline(std::cin,email);
    std::cout<<"Ngay sinh(YYYY-MM-DD): ";std::getline(std::cin,birth);
    std::cout<<"Dia chi: "; std::getline(std::cin,addr);
    customers.push_back(Customer(cccd,name,phone,email,birth,addr));
    std::cout << "Them thanh cong!\n";
    std::cout << "So khach hien tai: " << customers.size() << '\n';
    saveAll();
}

void YardManager::editCustomer(){
    std::string cccd;
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::cout<<"CCCD can sua: "; std::getline(std::cin,cccd);
    for(auto &c : customers){
        if( c.getCccd() == cccd){
            std::string nName,nPhone;
            std::cout<<"Ten moi: "; std::getline(std::cin,nName);
            std::cout<<"So dien thoai moi: "; std::getline(std::cin,nPhone);
            c.setName(nName); c.setPhone(nPhone);
            saveAll();
            return;
        }
    }
    std::cout<<"Khong tim thay cccd!\n";
}

void YardManager::deleteCustomer() {
    std::string cccd;
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::cout << "CCCD can xoa: "; 
    std::getline(std::cin, cccd);

    bool found = false;
    for (auto it = customers.begin(); it != customers.end(); ) {
        if (it->getCccd() == cccd) {
            it = customers.erase(it); 
            found = true;
            break; 
        } else {
            ++it; 
        }
    }
    if (found) {
        for (auto itAcc = accounts.begin(); itAcc != accounts.end(); ) {
            if (itAcc->getCccd() == cccd) {
                itAcc = accounts.erase(itAcc);
            } else {
                ++itAcc;
            }
        }
        std::cout << "Da xoa thanh cong ho so va tai khoan lien quan!\n";
        saveAll();
    } else {
        std::cout << "Khong tim thay khach hang voi so CCCD tren!\n";
    }
}
void YardManager::customerList() const {
    std::cout << "\n===== DANH SACH KHACH HANG =====\n";

    if (customers.empty()) {
        std::cout << "Khong co Khach hang nao!\n";
        return;
    }
    std::cout << "Size = " << customers.size() << '\n';
    for (const auto &c : customers) std::cout << c.toCSV() << "\n";
}
void YardManager::employeeManagerMenu() {
    int choice;

    do {
        std::cout << "\n===== QUAN LY NHAN VIEN =====\n";
        std::cout << "1. Them Nhan vien\n";
        std::cout << "2. Sua thong tin Nhan vien\n";
        std::cout << "3. Xoa Nhan vien\n";
        std::cout << "4. Danh sach Nhan vien\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Lua chon: ";
        if (!(std::cin >> choice)) {
            std::cout << "Lua chon khong hop le!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                editEmployee();
                break;
            case 3:
                deleteEmployee();
                break;
            case 4:
                employeeList();
                break;
            case 0:
                std::cout << "Quay lai...\n";
                break;
            default:
                std::cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}
void YardManager::addEmployee() {

    std::string cccd;
    std::string name;
    std::string phone;
    std::string email;
    std::string position;
    double salary;

    if (std::cin.peek() == '\n')
        std::cin.ignore();

    std::cout << "CCCD: ";
    std::getline(std::cin, cccd);

    for (const auto &e : employees) {
        if (e.getCccd() == cccd) {
            std::cout << "Nhan vien da ton tai!\n";
            return;
        }
    }

    std::cout << "Ho ten: ";
    std::getline(std::cin, name);

    std::cout << "So dien thoai: ";
    std::getline(std::cin, phone);

    std::cout << "Email: ";
    std::getline(std::cin, email);

    std::cout << "Chuc vu: ";
    std::getline(std::cin, position);

    std::cout << "Luong: ";
    std::cin >> salary;

    employees.push_back(
        Employee(
            cccd,
            name,
            phone,
            email,
            position,
            salary
        )
    );
    saveAll();
    std::cout << "Them Nhan vien thanh cong!\n";
}
void YardManager::editEmployee() {

    std::string cccd;

    if (std::cin.peek() == '\n')
        std::cin.ignore();

    std::cout << "Nhap CCCD Nhan vien can sua: ";
    std::getline(std::cin, cccd);

    for (auto &e : employees) {

        if (e.getCccd() == cccd) {

            std::string name;
            std::string phone;
            std::string email;
            std::string position;
            double salary;

            std::cout << "Ho ten moi: ";
            std::getline(std::cin, name);

            std::cout << "SDT moi: ";
            std::getline(std::cin, phone);

            std::cout << "Email moi: ";
            std::getline(std::cin, email);

            std::cout << "Chuc vu moi: ";
            std::getline(std::cin, position);

            std::cout << "Luong moi: ";
            std::cin >> salary;

            e.setName(name);
            e.setPhone(phone);
            e.setEmail(email);
            e.setPosition(position);
            e.setSalary(salary);
            saveAll();
            std::cout << "Cap nhat thanh cong!\n";
            return;
        }
    }
    std::cout << "Khong tim thay Nhan vien!\n";
}
void YardManager::deleteEmployee() {

    std::string cccd;

    if (std::cin.peek() == '\n')
        std::cin.ignore();

    std::cout << "Nhap CCCD Nhan vien can xoa: ";
    std::getline(std::cin, cccd);

    bool found = false;

    for (auto it = employees.begin(); it != employees.end();) {

        if (it->getCccd() == cccd) {

            it = employees.erase(it);
            found = true;
            break;
        }
        else
            ++it;
    }

    if (!found) {

        std::cout << "Khong tim thay Nhan vien!\n";
        return;
    }

    for (auto it = accounts.begin(); it != accounts.end();) {

        if (it->getCccd() == cccd)
            it = accounts.erase(it);
        else
            ++it;
    }

    std::cout << "Da xoa Nhan vien va tai khoan!\n";
    saveAll();
}
void YardManager::employeeList() const {

    std::cout << "\n===== DANH SACH NHAN VIEN =====\n";

    if (employees.empty()) {
        std::cout << "Khong co Nhan vien nao!\n";
        return;
    }

    for (const auto &e : employees) {
        std::cout << e.toCSV() << '\n';
    }
}
void YardManager::yardManagerMenu() {
    int choice;
    do {
        std::cout << "\n===== QUAN LY SAN TENNIS =====\n";
        std::cout << "1. Them san\n";
        std::cout << "2. Sua san\n";
        std::cout << "3. Xoa san\n";
        std::cout << "4. Danh sach san\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Lua chon: ";
        if (!(std::cin >> choice)) {
            std::cout << "Lua chon khong hop le!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            addYard();
            break;
        case 2:
            editYard();
            break;
        case 3:
            deleteYard();
            break;
        case 4:
            yardList();
            break;
        case 0:
            std::cout << "Quay lai...\n";
            break;
        default:
            std::cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}
void YardManager::addYard() {
    std::string id;
    std::string type;
    double price;
    std::cout << "\n===== THEM SAN =====\n";
    std::cout << "Ma san: ";
    std::cin >> id;

    for (const auto &y : yards) {
        if (y.getYardId() == id) {
            std::cout << "Ma san da ton tai!\n";
            return;
        }
    }
    std::cin.ignore();
    std::cout << "Loai san: ";
    std::getline(std::cin, type);
    std::cout << "Gia theo gio: ";
    std::cin >> price;

    yards.push_back(
        Yard(id, type, price, true)
    );
    saveAll();
    std::cout << "Them san thanh cong!\n";
}
void YardManager::bookYard() {

    std::string yardId;
    std::string customerCccd;
    std::string employeeCccd;
    std::string fromDate;
    std::string toDate;
    std::cout << "\n===== DAT SAN =====\n";
    // Nếu khách tự đặt
    if(User.getRole()==2){
        customerCccd = User.getCccd();
        employeeCccd = "";
    }
    else{
        std::cout<<"Nhap CCCD khach hang: ";
        std::cin>>customerCccd;
        employeeCccd = User.getCccd();
    }
    std::cout<<"Nhap ma san: ";
    std::cin>>yardId;
    Yard *yard = findYardById(yardId);
    if(yard==nullptr){
        std::cout<<"Khong tim thay san!\n";
        return;
    }
    if(!yard->getAvailable()){
        std::cout<<"San da duoc dat!\n";
        return;
    }
    std::cin.ignore();
    std::cout<<"Nhap thoi gian bat dau (YYYY-MM-DD HH:MM): ";
    fromDate = Time::inputDateTime();
    std::cout<<"Nhap thoi gian ket thuc (YYYY-MM-DD HH:MM): ";
    toDate = Time::inputDateTime();
    int hours;

    std::cout<<"Nhap so gio thue: ";
    std::cin>>hours;

    double total = hours * yard->getPricePerHour();

    yard->setAvailable(false);
    std::string invoiceId = sinhInvoice();
    invoices.push_back(
        Invoice(
            invoiceId,
            customerCccd,
            employeeCccd,
            yardId,
            fromDate,
            toDate,
            total
        )
    );
    std::cout<<"\n===== HOA DON =====\n";
    std::cout<<"Ma HD: "<<invoiceId<<'\n';
    std::cout<<"Khach hang: "<<customerCccd<<'\n';
    std::cout<<"San: "<<yardId<<'\n';
    std::cout<<"Tong tien: "<<total<<'\n';
    saveAll();
}
void YardManager::returnYard(){

    std::string yardId;

    std::cout<<"\n===== TRA SAN =====\n";

    std::cout<<"Nhap ma san: ";
    std::cin>>yardId;

    Yard *yard = findYardById(yardId);
    if(yard==nullptr){
        std::cout<<"Khong tim thay san!\n";
        return;
    }
    if(yard->getAvailable()){

        std::cout<<"San nay dang trong!\n";
        return;
    }
    yard->setAvailable(true);
    std::cout<<"Tra san thanh cong!\n";
    saveAll();
}
void YardManager::editYard() {

    std::string id;

    std::cout << "\nNhap ma san can sua: ";
    std::cin >> id;
    for (auto &y : yards) {
        if (y.getYardId() == id) {
            std::string type;
            double price;
            std::cin.ignore();
            std::cout << "Loai san moi: ";
            std::getline(std::cin, type);
            std::cout << "Gia moi: ";
            std::cin >> price;
            y.setYardType(type);
            y.setPricePerHour(price);
            saveAll();
            std::cout << "Cap nhat thanh cong!\n";
            return;
        }
    }
    std::cout << "Khong tim thay san!\n";
}
void YardManager::deleteYard() {

    std::string id;

    std::cout << "\nNhap ma san can xoa: ";
    std::cin >> id;

    for (auto it = yards.begin(); it != yards.end(); ++it) {

        if (it->getYardId() == id) {

            yards.erase(it);
            saveAll();
            std::cout << "Da xoa san!\n";
            return;
        }
    }
    std::cout << "Khong tim thay san!\n";
}
void YardManager::yardList() const {

    std::cout << "\n==== DANH SACH SAN ====\n";

    std::cout
        << std::left
        << std::setw(10) << "Ma"
        << std::setw(20) << "Loai san"
        << std::setw(15) << "Gia"
        << std::setw(15) << "Trang thai"
        << '\n';

    for (const auto &y : yards) {

        std::cout
            << std::left
            << std::setw(10) << y.getYardId()
            << std::setw(20) << y.getYardType()
            << std::setw(15) << y.getPricePerHour()
            << std::setw(15)
            << (y.getAvailable() ? "Con trong" : "Da dat")
            << '\n';
    }
}
void YardManager::searchMenu() const {

    int choice;

    do{
        std::cout<<"\n========== TIM KIEM ==========\n";
        std::cout<<"1. Tim san\n";
        std::cout<<"2. Tim khach hang\n";
        std::cout<<"3. Tim hoa don\n";
        std::cout<<"0. Quay lai\n";
        std::cout<<"Lua chon: ";
        if (!(std::cin >> choice)) {
            std::cout << "Lua chon khong hop le!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch(choice){
        case 1:
            searchYard();
            break;

        case 2:
            searchCustomer();
            break;

        case 3:
            searchInvoice();
            break;

        case 0:
            break;

        default:
            std::cout<<"Lua chon khong hop le!\n";
        }

    }while(choice!=0);
}
void YardManager::searchYard() const {

    std::string id;
    std::cout<<"\nNhap ma san: ";
    std::cin>>id;

    bool found=false;

    for(const auto &y:yards){

        if(y.getYardId()==id){

            std::cout<<"\n===== THONG TIN SAN =====\n";
            std::cout<<"Ma san: "<<y.getYardId()<<'\n';
            std::cout<<"Loai san: "<<y.getYardType()<<'\n';
            std::cout<<"Gia: "<<y.getPricePerHour()<<'\n';
            std::cout<<"Trang thai: "
                     <<(y.getAvailable()?"Con trong":"Da dat")
                     <<'\n';

            found=true;
            break;
        }
    }

    if(!found)
        std::cout<<"Khong tim thay san!\n";
}
void YardManager::searchCustomer() const {

    std::string cccd;

    std::cout<<"\nNhap CCCD khach hang: ";
    std::cin>>cccd;

    bool found=false;

    for(const auto &c:customers){

        if(c.getCccd()==cccd){

            std::cout<<"\n===== THONG TIN KHACH HANG =====\n";
            std::cout<<"CCCD: "<<c.getCccd()<<'\n';
            std::cout<<"Ho ten: "<<c.getName()<<'\n';
            std::cout<<"SDT: "<<c.getPhone()<<'\n';
            std::cout<<"Email: "<<c.getEmail()<<'\n';
            std::cout<<"Ngay sinh: "<<c.getBirthdate()<<'\n';
            std::cout<<"Dia chi: "<<c.getAddress()<<'\n';

            found=true;
            break;
        }
    }

    if(!found)
        std::cout<<"Khong tim thay khach hang!\n";
}
void YardManager::searchInvoice() const {

    std::string id;

    std::cout<<"\nNhap ma hoa don: ";
    std::cin>>id;

    bool found=false;

    for(const auto &i:invoices){

        if(i.getInvoiceId()==id){

            std::cout<<"\n========== HOA DON ==========\n";

            std::cout<<"Ma HD: "<<i.getInvoiceId()<<'\n';
            std::cout<<"CCCD KH: "<<i.getCustomerCccd()<<'\n';
            std::cout<<"CCCD NV: "<<i.getEmployeeCccd()<<'\n';
            std::cout<<"Ma san: "<<i.getYardId()<<'\n';
            std::cout<<"Ngay bat dau: "<<i.getDateFrom()<<'\n';
            std::cout<<"Ngay ket thuc: "<<i.getDateTo()<<'\n';
            std::cout<<"Tong tien: "<<i.getTotal()<<'\n';

            found=true;
            break;
        }
    }

    if(!found)
        std::cout<<"Khong tim thay hoa don!\n";
}
void YardManager::statsMenu() const {
    int choice;
    do{
        std::cout<<"\n========== THONG KE ==========\n";
        std::cout<<"1. Tong doanh thu\n";
        std::cout<<"2. Khach hang dat san nhieu nhat\n";
        std::cout<<"3. Thong ke nhan vien\n";
        std::cout<<"0. Quay lai\n";
        std::cout<<"Lua chon: ";
        if (!(std::cin >> choice)) {
            std::cout << "Lua chon khong hop le!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch(choice){

        case 1:
            statsRevenue();
            break;

        case 2:
            statsTopCustomer();
            break;

        case 3:
            statsEmployee();
            break;

        case 0:
            break;

        default:
            std::cout<<"Lua chon khong hop le!\n";
        }

    }while(choice!=0);
}
void YardManager::statsRevenue() const {

    double total = 0;
    for(const auto &i : invoices)
        total += i.getTotal();
    std::cout<<"\n===== DOANH THU =====\n";
    std::cout<<"Tong hoa don: "<<invoices.size()<<'\n';
    std::cout<<"Tong doanh thu: "<<total<<" VND\n";
}
void YardManager::statsTopCustomer() const {

    if(customers.empty()){
        std::cout<<"Chua co khach hang!\n";
        return;
    }

    int maxCount = 0;
    Customer topCustomer = customers[0];
    for(const auto &c : customers){
        int count = 0;
        for(const auto &i : invoices){
            if(i.getCustomerCccd() == c.getCccd())
                count++;
        }
        if(count > maxCount){
            maxCount = count;
            topCustomer = c;
        }
    }
    std::cout<<"\n===== KHACH HANG DAT SAN NHIEU NHAT =====\n";
    std::cout<<"CCCD: "<<topCustomer.getCccd()<<'\n';
    std::cout<<"Ho ten: "<<topCustomer.getName()<<'\n';
    std::cout<<"SDT: "<<topCustomer.getPhone()<<'\n';
    std::cout<<"Email: "<<topCustomer.getEmail()<<'\n';
    std::cout<<"So lan dat: "<<maxCount<<'\n';
}
void YardManager::statsEmployee() const {

    std::cout<<"\n===== THONG KE NHAN VIEN =====\n";

    for(const auto &e : employees){

        int count = 0;

        for(const auto &i : invoices){

            if(i.getEmployeeCccd() == e.getCccd())
                count++;
        }

        std::cout<<"\nNhan vien: "<<e.getName()<<'\n';
        std::cout<<"CCCD: "<<e.getCccd()<<'\n';
        std::cout<<"Chuc vu: "<<e.getPosition()<<'\n';
        std::cout<<"Luong: "<<e.getSalary()<<'\n';
        std::cout<<"So hoa don lap: "<<count<<'\n';
    }
}
void YardManager::statsUsingYard() const{
    int usingYard=0;
    for(const auto &y:yards){
        if(!y.getAvailable())
            usingYard++;
    }
    std::cout<<"Tong san: "<<yards.size()<<'\n';
    std::cout<<"Dang su dung: "<<usingYard<<'\n';
    std::cout<<"Con trong: "<<yards.size()-usingYard<<'\n';
}
void YardManager::statsTopYard() const {
    if(yards.empty()){
        std::cout << "Chua co san nao!\n";
        return;
    }
    int maxCount = 0;
    Yard topYard = yards[0];
    for(const auto &y : yards){
        int count = 0;
        for(const auto &i : invoices){
            if(i.getYardId() == y.getYardId())
                count++;
        }
        if(count > maxCount){
            maxCount = count;
            topYard = y;
        }
    }
    std::cout << "\n===== SAN DUOC DAT NHIEU NHAT =====\n";
    std::cout << "Ma san: " << topYard.getYardId() << '\n';
    std::cout << "Loai san: " << topYard.getYardType() << '\n';
    std::cout << "Gia theo gio: " << topYard.getPricePerHour() << '\n';
    std::cout << "So lan dat: " << maxCount << '\n';
}
