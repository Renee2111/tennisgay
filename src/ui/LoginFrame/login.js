document.addEventListener("DOMContentLoaded", async function () {
  await loadUserDataFromFile();

  const loginForm = document.getElementById("loginForm");
  if (loginForm) {
    loginForm.addEventListener("submit", handleLogin);
  }
});

// Hàm chỉ lấy dữ liệu từ file user.json
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

function handleLogin(e) {
  e.preventDefault();

  const usernameInput = document
    .getElementById("username")
    .value.trim()
    .toLowerCase();
  const passwordInput = document.getElementById("password").value;

  const usersList = JSON.parse(localStorage.getItem("USERS_DATA")) || [];

  const userFound = usersList.find(
    (u) =>
      ((u.username && u.username.toLowerCase() === usernameInput) ||
        (u.email && u.email.toLowerCase() === usernameInput)) &&
      u.password === passwordInput,
  );

  if (userFound) {
    localStorage.setItem("currentUser", JSON.stringify(userFound));
    alert(`Đăng nhập thành công! Xin chào ${userFound.fullname}`);

    switch (userFound.role) {
      case 0:
        window.location.href = "../AdminUI/AdMinUI.html";
        break;
      case 1:
        window.location.href = "../EmployeeUI/EmployeeUI.html";
        break;
      case 2:
        window.location.href = "../CustomerUI/CustomerUI.html";
        break;
      default:
        alert("Tài khoản chưa được phân quyền hợp lệ!");
    }
  } else {
    alert("Tên đăng nhập/Email hoặc mật khẩu không chính xác!");
  }
}
