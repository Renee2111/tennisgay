#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>
#include "YardManager.h"
// Lưu ý: Đường dẫn include Account.h có thể thay đổi tùy cấu trúc thư mục của bạn
#include "../../model/ACCOUNT/Account.h" 

class AuthManager {
private:
    YardManager &yardManager;

public:
    // Constructor
    AuthManager(YardManager &mgr);

    // Xác thực cơ bản
    bool login(const std::string &username, const std::string &password, Account &outAccount);
    bool isUsernameTaken(const std::string &username) const;
    bool hasPermission(const Account &acc, int requiredRole) const;

    // Các hàm xử lý gọi từ giao diện UI / API
    bool registerCustomerFromUI(const std::string &username, const std::string &password, const std::string &cccd,
                                const std::string &name, const std::string &phone, const std::string &email, 
                                const std::string &birth, const std::string &addr);
                                
    bool forgotPasswordFromUI(const std::string &username, const std::string &cccd, const std::string &newPassword);
    
    bool changePassword(const std::string &username, const std::string &oldPassword, const std::string &newPassword);
};

#endif // AUTHMANAGER_H