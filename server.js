const express = require("express");
const fs = require("fs");
const path = require("path");
const cors = require("cors");

const app = express();
const PORT = 3000;

app.use(cors());
app.use(express.json());

// 1. Phục vụ toàn bộ các file tĩnh trong thư mục "src/ui"
app.use(express.static(path.join(__dirname, "src", "ui")));

// 2. Cho phép truy cập công khai file user.json (để frontend fetch dữ liệu)
app.use("/data", express.static(path.join(__dirname, "data")));

const USER_FILE_PATH = path.join(__dirname, "data", "user.json");

// Chuyển hướng đến URL thật để các đường dẫn tương đối của CSS và JS hoạt động.
app.get("/", (req, res) => {
  res.redirect("/LoginFrame/LoginFrame.html");
});

function readUsersFromFile() {
  if (!fs.existsSync(USER_FILE_PATH)) {
    return [];
  }
  const data = fs.readFileSync(USER_FILE_PATH, "utf-8");
  return data ? JSON.parse(data) : [];
}

// API Đăng ký
app.post("/api/register", (req, res) => {
  try {
    const newUser = req.body;
    const users = readUsersFromFile();

    const isExist = users.some(
      (u) =>
        (u.username &&
          u.username.toLowerCase() === newUser.username.toLowerCase()) ||
        (u.email && u.email.toLowerCase() === newUser.email.toLowerCase()) ||
        (u.cccd && u.cccd === newUser.cccd),
    );

    if (isExist) {
      return res.status(400).json({
        success: false,
        message:
          "Tên đăng nhập, Email hoặc số CCCD này đã tồn tại trên hệ thống!",
      });
    }

    users.push(newUser);
    fs.writeFileSync(USER_FILE_PATH, JSON.stringify(users, null, 2), "utf-8");

    return res.status(200).json({
      success: true,
      message: "Đăng ký tài khoản thành công!",
    });
  } catch (error) {
    console.error("Lỗi khi ghi dữ liệu vào file:", error);
    return res.status(500).json({
      success: false,
      message: "Lỗi hệ thống, không thể lưu dữ liệu!",
    });
  }
});

app.listen(PORT, () => {
  console.log(`Server Backend đang chạy tại http://localhost:${PORT}`);
});
