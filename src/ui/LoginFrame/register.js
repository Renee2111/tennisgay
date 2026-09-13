// Tự động dọn dẹp data cũ ở localStorage khi trang được tải
localStorage.removeItem("USERS_DATA");
document.addEventListener("DOMContentLoaded", function () {
  const registerForm = document.getElementById("registerForm");
  if (registerForm) {
    registerForm.addEventListener("submit", handleRegister);
  }
});

async function handleRegister(e) {
  e.preventDefault();

  // 1. Reset các thông báo lỗi cũ
  const errorElements = document.querySelectorAll(".error-msg");
  errorElements.forEach((el) => (el.innerText = ""));

  // 2. Lấy dữ liệu từ ô nhập
  const username = document.getElementById("username").value.trim();
  const fullname = document.getElementById("fullname").value.trim();
  const email = document.getElementById("email").value.trim();
  const phone = document.getElementById("phone").value.trim();
  const cccd = document.getElementById("cccd").value.trim();
  const password = document.getElementById("password").value;
  const confirmPassword = document.getElementById("confirmPassword").value;

  let hasError = false;
  const phoneRegex = /^0\d{9}$/;

  // 3. Validation dữ liệu
  if (username === "") {
    document.getElementById("usernameError").innerText =
      "Vui lòng nhập tên đăng nhập!";
    hasError = true;
  }
  if (password === "") {
    document.getElementById("passwordError").innerText =
      "Vui lòng nhập mật khẩu!";
    hasError = true;
  }
  if (confirmPassword === "") {
    document.getElementById("confirmPasswordError").innerText =
      "Vui lòng nhập lại mật khẩu!";
    hasError = true;
  } else if (password !== confirmPassword) {
    document.getElementById("confirmPasswordError").innerText =
      "Mật khẩu xác nhận không khớp!";
    hasError = true;
  }
  if (cccd === "") {
    document.getElementById("cccdError").innerText = "Vui lòng nhập số CCCD!";
    hasError = true;
  }
  if (fullname === "") {
    document.getElementById("fullnameError").innerText =
      "Vui lòng nhập họ tên!";
    hasError = true;
  }
  if (phone === "") {
    document.getElementById("phoneError").innerText =
      "Vui lòng nhập số điện thoại!";
    hasError = true;
  } else if (!phoneRegex.test(phone)) {
    document.getElementById("phoneError").innerText =
      "Số điện thoại không đúng định dạng!";
    hasError = true;
  }
  if (email === "") {
    document.getElementById("emailError").innerText =
      "Vui lòng nhập địa chỉ email!";
    hasError = true;
  }

  if (hasError) return; // Dừng lại nếu có lỗi

  // 4. Tạo đối tượng người dùng mới
  const newUser = {
    id: "KH" + Math.floor(1000 + Math.random() * 9000),
    username: username,
    password: password,
    fullname: fullname,
    email: email,
    phone: phone,
    cccd: cccd,
    role: 2,
  };

  // 5. Gửi dữ liệu về Server Node.js để ghi vào file user.json
  try {
    const response = await fetch("/api/register", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(newUser),
    });

    const result = await response.json();

    if (response.ok && result.success) {
      alert("Đăng ký tài khoản thành công! Dữ liệu đã lưu vào user.json");
      window.location.href = "LoginFrame.html";
    } else {
      alert(result.message || "Đăng ký thất bại!");
    }
  } catch (error) {
    console.error("Lỗi kết nối Server:", error);
    alert("Không thể kết nối đến Server Node.js! Vui lòng bật server.js");
  }
}
