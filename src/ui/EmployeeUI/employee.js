document.addEventListener("DOMContentLoaded", function () {
  // 1. Lấy thông tin user
  const user = JSON.parse(localStorage.getItem("currentUser"));

  // 2. Kiểm tra quyền Nhân viên (role = 1)
  if (!user || user.role !== 1) {
    alert("Bạn chưa đăng nhập hoặc không có quyền truy cập!");
    window.location.href = "../LoginFrame/LoginFrame.html";
    return;
  }

  // 3. Hiển thị tên Nhân viên lên Header
  const headerNameEl = document.getElementById("headerEmployeeName");
  if (headerNameEl) {
    headerNameEl.textContent = user.fullname;
  }

  // 4. Bắt sự kiện nút Đăng xuất ở Sidebar
  const logoutBtn = document.querySelector(".btn-logout");
  if (logoutBtn) {
    logoutBtn.addEventListener("click", function () {
      localStorage.removeItem("currentUser");
      window.location.href = "../LoginFrame/LoginFrame.html";
    });
  }
});
