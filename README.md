# 🎾 SÂN TENNIS VIỆT QUỐC - Quản Lý & Đặt Sân Tennis

Hệ thống quản lý và đặt sân Tennis trực tuyến được nâng cấp từ phiên bản Core C++ sang kiến trúc Web Application hiện đại với Giao diện người dùng (UI) tương tác trực quan và Backend Node.js / Express.

---

## 📌 1. Giới thiệu dự án

Ban đầu, dự án **Sân Tennis Việt Quốc** được phát triển nền tảng xử lý dữ liệu bằng **C++**. Để tối ưu trải nghiệm người dùng, mở rộng tính năng tương tác và phân quyền sử dụng linh hoạt, dự án đã được chuyển đổi & tái cấu trúc toàn bộ sang mô hình Web:
* **Frontend:** Giao diện người dùng dạng Web (HTML5, CSS3, JavaScript ES6+).
* **Backend:** Server Node.js sử dụng framework Express.js.
* **Cơ sở dữ liệu:** Quản lý và lưu trữ dữ liệu người dùng qua cấu trúc file JSON (`data/user.json`).

---

## 🏗️ 2. Cấu trúc thư mục dự án

```text
tennisgay/
├── data/
│   └── user.json          # File lưu trữ dữ liệu người dùng (JSON database)
├── src/
│   └── ui/
│       ├── LoginFrame/    # Giao diện Đăng nhập (HTML, CSS, JS)
│       ├── RegisterFrame/ # Giao diện Đăng ký tài khoản
│       ├── AdminUI/       # Giao diện dành cho Quản trị viên (Role 0)
│       ├── EmployeeUI/    # Giao diện dành cho Nhân viên (Role 1)
│       └── CustomerUI/    # Giao diện dành cho Khách hàng (Role 2)
├── server.js              # Entry point của Node.js / Express Backend Server
├── package.json           # Khai báo dependencies (express, cors, v.v.)
└── README.md              # Tài liệu hướng dẫn dự án
```

---

## 🔑 3. Các tính năng chính

* **Phân quyền người dùng (Role-based Authorization):**
  * `Role 0 (Admin)`: Quản lý toàn bộ hệ thống sân, nhân viên và thống kê.
  * `Role 1 (Employee)`: Quản lý lịch đặt sân, duyệt sân và hỗ trợ khách hàng.
  * `Role 2 (Customer)`: Đặt lịch sân tennis, xem trạng thái và lịch sử đặt sân.
* **Xác thực & Lưu trữ:**
  * Đăng ký/Đăng nhập hệ thống với kiểm tra trùng lặp (Username, Email, CCCD).
  * Tự động lưu thông tin phiên làm việc qua `localStorage`.
* **API RESTful & Static File Serving:**
  * Phục vụ static UI linh hoạt từ thư mục `src/ui`.
  * API kiểm tra, đọc/ghi file `user.json` an toàn từ Server Backend.

---

## 🚀 4. Hướng dẫn cài đặt và khởi chạy

### Yêu cầu tiên quyết
* Đã cài đặt [Node.js](https://nodejs.org/) (khuyên dùng bản LTS).

### Các bước khởi chạy Server

1. **Clone repository về máy:**
   ```bash
   git clone https://github.com/Renee2111/tennisgay.git
   cd tennisgay
   ```

2. **Cài đặt các thư viện cần thiết:**
   ```bash
   npm install
   ```
   *(Các thư viện chính bao gồm: `express`, `cors`)*

3. **Khởi chạy Server Node.js:**
   ```bash
   node server.js
   ```
   *(Hoặc file server của bạn như `node server_2.js`)*

4. **Truy cập ứng dụng:**
   * Mở trình duyệt web và truy cập: `http://localhost:3000`
   * Trang giao diện Đăng nhập (`LoginFrame.html`) sẽ tự động xuất hiện.

---

## 🛠️ 5. Công nghệ sử dụng

* **Languages:** JavaScript (ES6+), HTML5, CSS3
* **Runtime & Framework:** Node.js, Express.js
* **Data Storage:** JSON File Storage (`fs` module)
* **Dev Tools:** Visual Studio Code, Git, GitHub
