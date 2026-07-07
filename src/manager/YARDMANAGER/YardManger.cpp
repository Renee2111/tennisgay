#include "YardManager.h"
//#include "../../utils/FileHandler.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>


YardManager::YardManager(const std::string &dir) : dataDir(dir) {}

void YardManager::runConsole() {
    loadAll();
    loginMenu();
    saveAll();
}

//He thong xac thuc
void YardManager::loginMenu(){
    int lc;
    do{
        std::cout<<"\n==== TENNIS MANAGER ====\n";
        std::cout<<"1.Dang nhap\n2.Dang ky\n0.Luu va Thoat\nLua chon cua ban la: ";
        std::cin>>lc;
        switch (lc)
        {
            case 1:  
                login();
                break;
            case 2:
                dangkyAccount();
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
        std::cout << "Nhap thong tin ca nhan cua ban:\nHo ten: ";
        std::cin.ignore(); 
        std::getline(std::cin, name);
        std::cout << "So dien thoai: "; 
        std::cin >> phone;
        std::cout << "Email: "; 
        std::cin >> email;
        std::cout << "Ngay sinh (YYYY-MM-DD): "; 
        std::cin >> birth;
        std::cout << "Dia chi: "; 
        std::cin.ignore(); 
        std::getline(std::cin, addr);
        
        customers.push_back(Customer(cccd, name, phone, email, birth, addr));
    }

    accounts.push_back(Account(username, password, 2, cccd));
    std::cout << "-> Dang ky tai khoan Khach hang thanh cong!\n";
    
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
    std::cout << "Cap tai khoan Nhan vien thanh cong. Nhan vien co the dang nhap ngay!\n";
}
void YardManager::adminMenu() {
    int choice;
    do {
        std::cout << "\n===== MENU QUAN TRI (ADMIN) =====\n";
        std::cout << "1. Quan ly khach hang\n2. Quan ly nhan vien\n3. Quan ly san tennis\n4. Cong cu tim kiem\n5. Bao cao thong ke\n6. Cap tai khoan cho Nhan vien\n0. Dang xuat\nLua chon: ";
        std::cin >> choice;
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
        std::cout << "1. Xem danh sach san Tennis hien tai\n";
        std::cout << "2. Xem danh sach Khach hang\n";
        std::cout << "3. Them moi ho so Khach hang (Khi co khach moi)\n";
        std::cout << "4. Cong cu tim kiem nhanh (San/Khach hang/Hoa don)\n";
        std::cout << "0. Dang xuat (Quay lai man hinh chinh)\n";
        std::cout << "=========================================\n";
        std::cout << "Lua chon cua ban: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                yardList();
                break;
            case 2:
                customerList();
                break;
            case 3:
                addCustomer();
                break;
            case 4:
                searchMenu(); 
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
        std::cout << "2. Tra cuu thong tin ca nhan (Qua so CCCD)\n";
        std::cout << "0. Dang xuat (Quay lai man hinh chinh)\n";
        std::cout << "Lua chon cua ban: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "\n==== TINH TRANG CAC SAN TENNIS CO THE THUE ====\n";
                yardList(); 
                break;
            case 2:
                searchCustomer();
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
