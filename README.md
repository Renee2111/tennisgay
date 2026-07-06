# HỆ THỐNG QUẢN LÝ SÂN TENNIS

## 1.Phát biểu bài toán
**Tổng quan về đề tài**
-Xây dựng hệ thống phần mềm quản lý đặt sân tennis cho phép quản lý thông tin: nhân viên, khách hàng, sân và hoá đơn. Hệ thống hỗ trợ thao tác thêm, sửa, xoá, danh sách, tìm kiếm, lưu/đọc dữ liệu từ file và thống kê doanh thu.

### CÁC TÍNH NĂNG CHÍNH

- **Hệ thống xác thực theo vai trò**: Đăng nhập/ Đăng ký với ba vai trò là (Admin, Nhân viên, Khách hàng).
- **Quản lý khách hàng**: Thêm, sửa, xoá thông tin khách hàng.
- **Quản lý nhân viên**: Quản lý nhân viên theo vị trí và lương.
- **Quản lý sân**: Quản lý sân, giá và trạng thái có hay không.
- **Chức năng tìm kiếm**: Tìm kiếm sân theo ID, khách hàng theo tên/ngày sinh, hoá đơn theo ID.
- **Thống kê**: Thống kê doanh thu, khách hàng đứng đầu, hoá đơn theo nhân viên.
- **Lưu trữ dữ liệu**: Tất cả các tệp tự động lưu vào các tệp CSV trong thư mục data.

---
## 2.Cấu trúc dữ liệu

###Phân tích các lớp và mối quan hệ

  Person (Lớp Cơ Sở Trừu Tượng)
  ├── Customer (Khách Hàng)
  └── Employee (Nhân Viên)
  
  Yard (sân - Độc Lập)
  
  Invoice (Hóa Đơn - Độc Lập)
  
  YardManager (Lớp Quản Lý Chính - Độc Lập)
  
  Account (Tài Khoản - Độc Lập)
  
  AuthManager (Quản Lý Xác Thực - Độc Lập)

### Mô tả chi tiết các lớp
####**Person**(Lớp Cơ Sở)
Lớp cơ sở cho tất cả người dùng của hệ thống.

**Thuộc tính**
- `cccd`(string):số cccd
- `name`(string):tên
- `phone`(string):số điện thoại
- `email`(string):địa chỉ email
**Phương thức**
- `getCccd()`,`getName()`,`getPhone()`,`getEmail()`:Hàm lấy dữ liệu.
- `setName()`,`setPhone()`,`setEmail()`:Hàm đặt dữ liệu.
- `toCSV()`: Chuyển đổi sang định dạng CSV (thuẩn ảo)
- `fromCSV()`: Phân tích từ định dạng CSV (thuần ảo)

#### **Customer** (Kế Thừa từ Person)
Đại diện cho một khách hàng khách sạn.

**Được kế thức toàn bộ thuộc tính và phương thức lấy từ person(Lớp cha)**

**Thuộc Tính Bổ Sung:**
- `birthdate` (string): Ngày sinh (định dạng YYYY-MM-DD)
- `address` (string): Địa chỉ cư trú

**Phương Thức Mới:**
- `getBirthdate()`, `getAddress()`: Các hàm lấy dữ liệu
- `toCSV()`, `fromCSV()`: Tuần tự hóa CSV

#### **Employee** (Kế Thừa từ Person)
Đại diện cho một nhân viên khách sạn.

**Được kế thức toàn bộ thuộc tính và phương thức lấy từ person(Lớp cha)**

**Thuộc Tính Bổ Sung:**
- `position` (string): Vị trí công việc (ví dụ: Quản lý, Nhân Viên)
- `salary` (double): Lương hàng tháng

**Phương Thức Mới:**
- `getPosition()`, `getSalary()`: Các hàm lấy dữ liệu
- `toCSV()`, `fromCSV()`: Tuần tự hóa CSV

#### **Yard** (Sân)
Đại diện cho một sân Tennis.

**Thuộc Tính:**
- `roomId` (string): Mã phòng duy nhất (ví dụ: R101, R202)
- `type` (string): Loại phòng (ví dụ: Đơn, Đôi, Gia Đình)
- `price` (double): Giá mỗi đêm
- `available` (boolean): Trạng thái sẵn có (true = có sẵn, false = đã đặt)

**Phương Thức:**
- `getYardId()`, `getType()`, `getPrice()`, `isAvailable()`: Các hàm lấy dữ liệu
- `setAvailable()`: Đặt trạng thái sẵn có
- `toCSV()`, `fromCSV()`: Tuần tự hóa CSV

#### **Invoice** (Hóa Đơn)
Đại diện cho một đơn đặt sân/hóa đơn khách hàng.

**Thuộc Tính:**
- `invoiceId` (chuỗi): Mã hóa đơn duy nhất
- `customerCccd` (chuỗi): Tham chiếu đến CCCD khách hàng
- `employeeCccd` (chuỗi): Tham chiếu đến CCCD nhân viên tạo hóa đơn
- `yardId` (chuỗi): Tham chiếu đến phòng được đặt
- `dateFrom` (chuỗi): Ngày nhận phòng (YYYY-MM-DD)
- `dateTo` (chuỗi): Ngày trả phòng (YYYY-MM-DD)
- `total` (số thực): Tổng số tiền tính phí

**Phương Thức:**
- `getInvoiceId()`, `getCustomerCccd()`, `getEmployeeCccd()`, `getyardId()`, `getDateFrom()`, `getDateTo()`, `getTotal()`: Các hàm lấy dữ liệu
- `toCSV()`, `fromCSV()`: Tuần tự hóa CSV

#### **Account** (Tài Khoản)
Đại diện cho một tài khoản người dùng trong hệ thống xác thực.

**Thuộc Tính:**
- `username` (chuỗi): Tên đăng nhập duy nhất
- `password` (chuỗi): Mật khẩu (lưu trữ dạng văn bản cho mục đích demo)
- `role` (số nguyên): Vai trò người dùng (0 = Admin, 1 = Nhân Viên, 2 = Khách Hàng)
- `cccd` (chuỗi): CCCD liên kết (trống cho Admin)

**Phương Thức:**
- `getUsername()`, `getPassword()`, `getRole()`, `getCccd()`: Các hàm lấy dữ liệu
- `toCSV()`, `fromCSV()`: Tuần tự hóa CSV

#### **HotelManager** (Lớp Quản Lý Chính)
Lớp quản lý trung tâm điều phối tất cả các hoạt động của chương trình.

**Thuộc Tính:**
- `dataDir` (chuỗi): Đường dẫn đến thư mục dữ liệu
- `customers` (vector<Customer>): Tất cả khách hàng
- `employees` (vector<Employee>): Tất cả nhân viên
- `rooms` (vector<Room>): Tất cả phòng
- `invoices` (vector<Invoice>): Tất cả hóa đơn
- `currentUser` (Account): Tài khoản người dùng hiện tại đã đăng nhập

**Phương Thức Chính:**
- `loadAll()`, `saveAll()`: Tải/lưu tất cả dữ liệu
- `homeMenu()`: Menu đăng nhập/đăng ký
- `adminMenu()`, `staffMenu()`, `customerMenu()`: Các menu dựa trên vai trò
- `employeeMenu()`, `roomMenu()`, `invoiceMenu()`: Các hàm menu quản lý
- `searchMenu()`, `statsMenu()`: Các hàm tìm kiếm và thống kê
- `runConsole()`: Vòng lặp bảng điều khiển chính

  

  
