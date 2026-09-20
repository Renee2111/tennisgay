document.addEventListener("DOMContentLoaded", async function () {
  await loadUserDataFromFile();

  const forgotForm = document.getElementById("forgotPasswordForm");
  if (forgotForm) {
    forgotForm.addEventListener("submit", handleForgotPassword);
  }
});

// Hàm lấy dữ liệu từ file user.json và lưu vào LocalStorage nếu chưa có
async function loadUserDataFromFile() {
  if (!localStorage.getItem("USERS_DATA")) {
    try {
      const response = await fetch("/data/user.json");
      if (!response.ok) {
        throw new Error("Không thể tải file user.json");
      }
      const usersData = await response.json();
      localStorage.setItem("USERS_DATA", JSON.stringify(usersData));
    } catch (error) {
      console.error("Lỗi đọc file dữ liệu:", error);
    }
  }
}

async function handleForgotPassword(e) {
  e.preventDefault();

  const identifier = document
    .getElementById("username")
    .value.trim()
    .toLowerCase();
  const cccd = document.getElementById("cccd").value.trim();
  const newPassword = document.getElementById("newPassword").value;
  const confirmNewPassword =
    document.getElementById("confirmNewPassword").value;

  // 1. Kiểm tra mật khẩu xác nhận
  if (newPassword !== confirmNewPassword) {
    alert("Mật khẩu xác nhận không khớp!");
    return;
  }

  let users = JSON.parse(localStorage.getItem("USERS_DATA")) || [];

  // 2. Tìm tài khoản khớp Tên đăng nhập/Email VÀ Số CCCD
  const userIndex = users.findIndex((u) => {
    const matchIdentifier =
      (u.username && u.username.toLowerCase() === identifier) ||
      (u.email && u.email.toLowerCase() === identifier);
    const matchCCCD = u.cccd === cccd;

    return matchIdentifier && matchCCCD;
  });

  if (userIndex === -1) {
    alert("Thông tin Tên đăng nhập/Email hoặc Số CCCD không chính xác!");
    return;
  }

  // 3. Phân quyền: Chỉ tài khoản Khách hàng (role === 2) mới được đổi mật khẩu
  if (users[userIndex].role !== 2) {
    alert(
      "Chức năng quên mật khẩu chỉ áp dụng cho Khách hàng! Tài khoản Quản lý và Nhân viên vui lòng liên hệ Admin hệ thống.",
    );
    return;
  }

  const userId = users[userIndex].id;

  // 4. Gửi API tới Server Node.js để ghi đè mật khẩu mới vào file user.json
  try {
    const response = await fetch("/api/update-password", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        id: userId,
        newPassword: newPassword,
      }),
    });

    const result = await response.json();

    if (response.ok && result.success) {
      // 5. Cập nhật thành công ở Server -> Cập nhật tiếp vào LocalStorage
      users[userIndex].password = newPassword;
      localStorage.setItem("USERS_DATA", JSON.stringify(users));

      alert(
        "Cập nhật mật khẩu thành công! Dữ liệu đã lưu vào user.json. Vui lòng đăng nhập lại.",
      );
      window.location.href = "LoginFrame.html";
    } else {
      alert(result.message || "Đổi mật khẩu thất bại trên Server!");
    }
  } catch (error) {
    console.error("Lỗi kết nối Server:", error);
    alert("Không thể kết nối đến Server Node.js để lưu mật khẩu!");
  }
}
