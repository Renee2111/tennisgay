document.addEventListener("DOMContentLoaded", function () {
  // 1. Lấy thông tin user
  const user = JSON.parse(localStorage.getItem("currentUser"));

  // 2. Kiểm tra quyền Khách hàng (role = 2)
  if (!user || user.role !== 2) {
    alert("Bạn chưa đăng nhập hoặc không có quyền truy cập!");
    window.location.href = "../LoginFrame/LoginFrame.html";
    return;
  }

  // 3. Hiển thị tên Khách hàng lên Header
  const headerUsernameEl = document.getElementById("headerUsername");
  if (headerUsernameEl) {
    headerUsernameEl.textContent = user.fullname;
  }

  // 4. Điền sẵn thông tin Khách hàng vào Tab "Thông Tin Cá Nhân"
  const usernameInput = document.getElementById("username");
  const fullnameInput = document.getElementById("fullname");
  const phoneInput = document.getElementById("phone");
  const emailInput = document.getElementById("email");
  const addressInput = document.getElementById("address");

  if (usernameInput) usernameInput.value = user.username || user.cccd || "";
  if (fullnameInput) fullnameInput.value = user.fullname || "";
  if (phoneInput) phoneInput.value = user.phone || "";
  if (emailInput) emailInput.value = user.email || "";
  if (addressInput) addressInput.value = user.address || "";

  // 5. Bắt sự kiện nút Đăng xuất ở Sidebar
  const logoutBtn = document.querySelector(".btn-logout");
  if (logoutBtn) {
    logoutBtn.addEventListener("click", function () {
      localStorage.removeItem("currentUser");
      window.location.href = "../LoginFrame/LoginFrame.html";
    });
  }
});
