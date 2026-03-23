#include <Arduino.h>
#include <cr7.h> // Gọi module CR7 vào sân

// 5 chân LED: Tiến(7), Lùi(8), Trái(9), Phải(10), Dừng(11)
const int led[] = {17, 18, 8, 3, 9};

void setup() {
  Serial.begin(115200);
  
  // 1. Cài đặt 5 chân LED là OUTPUT
  for (int i = 0; i < 5; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW); // Mặc định tắt hết đèn
  }
  
  // 2. Gọi hàm cài đặt ma trận từ file cr7.cpp
  setupMatrix();
  
  Serial.println("He thong CR7 san sang SIUUU!");
}

void loop() {
  // Liên tục hỏi module CR7: "Có ai nhấn nút không?"
  int ketQua = readMatrixValue(); 

  // Nếu ketQua > 0 nghĩa là có người nhấn nút
  if (ketQua > 0) {
    Serial.print("Da nhan nut: "); Serial.println(ketQua);

    // Bước A: Tắt tất cả các đèn cũ trước khi bật đèn mới
    for (int i = 0; i < 5; i++) digitalWrite(led[i], LOW);

    // Bước B: Nếu nhấn nút từ 1 đến 5, bật đèn tương ứng
    // Ví dụ: Nhấn nút 1 -> ketQua=1 -> bật led[0] (chân số 7)
    if (ketQua <= 5) {
      digitalWrite(led[ketQua - 1], HIGH); 
      Serial.print("Bat den so: "); Serial.println(ketQua);
    } else {
      Serial.println("Nut so 6 khong co LED tuong ung.");
    }
  }
}