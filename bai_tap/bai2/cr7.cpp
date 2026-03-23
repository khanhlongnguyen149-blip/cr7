#include "cr7.h"

// Bạn hãy kiểm tra kỹ: dây Hàng cắm vào GPIO 2, 4. Dây Cột cắm vào 6, 15, 16.
const int hang[] = {4, 5};         // 2 Hàng
const int cot[] = {7, 15, 16};    // 3 Cột

void setupMatrix() {
  // Thiết lập Hàng là OUTPUT để "phát điện"
  for (int i = 0; i < 2; i++) {
    pinMode(hang[i], OUTPUT);
    digitalWrite(hang[i], HIGH); // Mặc định để mức cao
  }
  // Thiết lập Cột là INPUT_PULLUP để "nghe tín hiệu"
  for (int i = 0; i < 3; i++) {
    pinMode(cot[i], INPUT_PULLUP);
  }
}

int readMatrixValue() {
  for (int r = 0; r < 2; r++) {
    digitalWrite(hang[r], LOW); // Bước 1: Cho 1 hàng xuống Đất (GND tạm thời)

    for (int c = 0; c < 3; c++) {
      if (digitalRead(cot[c]) == LOW) { // Bước 2: Kiểm tra xem Cột nào bị kéo xuống Đất
        int nut = (r * 3) + c + 1;      // Bước 3: Tính số thứ tự nút (1 đến 6)
        
        while(digitalRead(cot[c]) == LOW); // Bước 4: Đợi bạn buông tay ra mới chạy tiếp
        delay(50);                         // Chống dội nút nhấn (Debounce)
        
        digitalWrite(hang[r], HIGH);    // Trả Hàng về mức cao trước khi thoát
        return nut;                     // Trả về số nút nhấn cho file main.cpp
      }
    }
    digitalWrite(hang[r], HIGH); // Đưa hàng lên cao lại để quét hàng tiếp theo
  }
  return 0; // Nếu không có nút nào nhấn thì trả về 0
}