document.addEventListener("DOMContentLoaded", function () {
  // 1. Lấy thông tin user đăng nhập từ localStorage
  const user = JSON.parse(localStorage.getItem("currentUser"));

  // 2. Kiểm tra quyền Admin (role = 0)
  if (!user || user.role !== 0) {
    alert("Bạn chưa đăng nhập hoặc không có quyền truy cập!");
    window.location.href = "../LoginFrame/LoginFrame.html"; // Đá về trang login
    return;
  }

  // 3. Hiển thị tên Admin lên Header
  const headerNameEl = document.getElementById("headerAdminName");
  if (headerNameEl) {
    headerNameEl.textContent = user.fullname;
  }

  // 4. Xử lý Đăng xuất (nếu có nút đăng xuất)
  const logoutBtn = document.querySelector(".btn-logout");
  if (logoutBtn) {
    logoutBtn.addEventListener("click", function () {
      localStorage.removeItem("currentUser");
      window.location.href = "../LoginFrame/LoginFrame.html";
    });
  }
});
