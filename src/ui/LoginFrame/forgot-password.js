document.addEventListener("DOMContentLoaded", async function () {
  await loadUserDataFromFile();

  const forgotForm = document.getElementById("forgotPasswordForm");
  if (forgotForm) {
    forgotForm.addEventListener("submit", handleForgotPassword);
  }
});

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

function handleForgotPassword(e) {
  e.preventDefault();

  const identifier = document
    .getElementById("username")
    .value.trim()
    .toLowerCase();
  const cccd = document.getElementById("cccd").value.trim();
  const newPassword = document.getElementById("newPassword").value;
  const confirmNewPassword =
    document.getElementById("confirmNewPassword").value;

  if (newPassword !== confirmNewPassword) {
    alert("Mật khẩu xác nhận không khớp!");
    return;
  }

  let users = JSON.parse(localStorage.getItem("USERS_DATA")) || [];

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

  // CHẶN: Chỉ tài khoản Khách hàng (role === 2) mới được đổi mật khẩu
  if (users[userIndex].role !== 2) {
    alert(
      "Chức năng quên mật khẩu chỉ áp dụng cho Khách hàng! Tài khoản Quản lý và Nhân viên vui lòng liên hệ Admin hệ thống.",
    );
    return;
  }

  users[userIndex].password = newPassword;
  localStorage.setItem("USERS_DATA", JSON.stringify(users));

  alert("Cập nhật mật khẩu thành công! Vui lòng đăng nhập lại.");
  window.location.href = "LoginFrame.html";
}
