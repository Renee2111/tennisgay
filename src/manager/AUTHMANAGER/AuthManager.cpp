#include "AuthManager.h"

AuthManager::AuthManager(YardManager &mgr) : yardManager(mgr) {}

// 1. Đăng nhập: Gọi từ UI khi ấn nút Login[cite: 2, 5]
bool AuthManager::login(const std::string &username, const std::string &password, Account &outAccount) {
    const auto &accounts = yardManager.getAccounts();
    for (const auto &acc : accounts) {
        if (acc.getUsername() == username && acc.getPassword() == password) {
            outAccount = acc;
            return true;
        }
    }
    return false; // Sai tài khoản hoặc mật khẩu
}

// 2. Kiểm tra Username tồn tại[cite: 2]
bool AuthManager::isUsernameTaken(const std::string &username) const {
    const auto &accounts = yardManager.getAccounts();
    for (const auto &acc : accounts) {
        if (acc.getUsername() == username) return true;
    }
    return false;
}

// 3. Đăng ký tài khoản từ UI (Logic giống dangkyAccount của file cuối)
// UI cần gửi đủ form bao gồm thông tin cá nhân phòng trường hợp CCCD chưa có hồ sơ
bool AuthManager::registerCustomerFromUI(
    const std::string &username, const std::string &password, const std::string &cccd,
    const std::string &name, const std::string &phone, const std::string &email, 
    const std::string &birth, const std::string &addr) 
{
    if (isUsernameTaken(username)) {
        return false; // Báo lỗi UI: Tên đăng nhập đã tồn tại
    }

    // Kiểm tra CCCD đã có hồ sơ Customer chưa, nếu chưa thì tạo mới[cite: 5]
    if (yardManager.findCustomer(cccd) == nullptr) {
        Customer newCustomer(cccd, name, phone, email, birth, addr);
        yardManager.addCustomer(newCustomer); // Hàm này đã có sẵn saveAll() bên trong[cite: 3]
    }

    // Tạo Account với Role = 2 (Khách hàng)[cite: 5]
    Account newAcc(username, password, 2, cccd);
    yardManager.getAccounts().push_back(newAcc);
    yardManager.saveAll(); // Lưu file accounts.csv[cite: 3, 5]

    return true;
}

// 4. Quên mật khẩu (Logic từ file cuối: Chỉ cho phép khách hàng - Role 2)[cite: 5]
bool AuthManager::forgotPasswordFromUI(const std::string &username, const std::string &cccd, const std::string &newPassword) {
    auto &accounts = yardManager.getAccounts();

    for (auto &acc : accounts) {
        if (acc.getUsername() == username && acc.getCccd() == cccd) {
            // Ràng buộc từ file cuối: Chỉ áp dụng cho tài khoản Khách hàng (Role 2)[cite: 5]
            if (acc.getRole() != 2) {
                return false; 
            }
            acc.setPassword(newPassword);
            yardManager.saveAll();
            return true;
        }
    }
    return false; // Sai thông tin
}

// 5. Đổi mật khẩu trong lúc đang đăng nhập[cite: 2, 5]
bool AuthManager::changePassword(const std::string &username, const std::string &oldPassword, const std::string &newPassword) {
    auto &accounts = yardManager.getAccounts();
    for (auto &acc : accounts) {
        if (acc.getUsername() == username && acc.getPassword() == oldPassword) {
            acc.setPassword(newPassword);
            yardManager.saveAll(); 
            return true;
        }
    }
    return false;
}