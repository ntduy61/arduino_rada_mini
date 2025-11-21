#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Servo servo;

int trigPin = 8;
int echoPin = 9;

// Lưu điểm vật cản để fade dần (Store detected points for fading)
#define MAX_POINTS 30
int pointX[MAX_POINTS];
int pointY[MAX_POINTS];
int pointLife[MAX_POINTS];

// ─────────────────────────────────────────────
// 📏 Đo khoảng cách bằng ultrasonic (Ultrasonic distance reading)
// ─────────────────────────────────────────────
long getDistance() { 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000); // timeout 20ms
  long distance = duration * 0.034 / 2; // mm to cm conversion
  return distance; // cm
}

// ─────────────────────────────────────────────
void setup() {
  servo.attach(6);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  display.begin(0x3C, true);
  display.clearDisplay();
  display.display();

  // Khởi tạo bảng fade (Init fade table)
  for (int i = 0; i < MAX_POINTS; i++) {
    pointLife[i] = 0;
  }
}

// ─────────────────────────────────────────────
// 🔁 Quét qua lại 0 → 180 → 0 (Full sweep)
// ─────────────────────────────────────────────
void loop() {
  for (int angle = 0; angle <= 180; angle++) scanAndDraw(angle);
  for (int angle = 180; angle >= 0; angle--) scanAndDraw(angle);
}

// ─────────────────────────────────────────────
// ➕ Thêm 1 điểm vật cản vào mảng fade (Add fading point)
// ─────────────────────────────────────────────
void addPoint(int x, int y) {
  for (int i = 0; i < MAX_POINTS; i++) {
    if (pointLife[i] == 0) {
      pointX[i] = x;
      pointY[i] = y;
      pointLife[i] = 10; // tồn tại 10 frame (lasts 10 frames)
      return;
    }
  }
}

// ─────────────────────────────────────────────
// 📡 Quét & vẽ radar (Scanning + drawing radar)
// ─────────────────────────────────────────────
void scanAndDraw(int angle) {
  servo.write(angle);
  delay(15);

  long d = getDistance(); // cm

  // 🎯 Chỉ nhận khoảng cách ≤ 30cm (Only detect ≤ 30cm)
  if (d > 30) d = -1;

  display.clearDisplay();

  int cx = SCREEN_WIDTH / 2;
  int cy = SCREEN_HEIGHT - 1;

  // 🎯 Vẽ 3 vòng radar (Draw 3 radar rings)
  display.drawCircle(cx, cy, 20, 1);
  display.drawCircle(cx, cy, 35, 1);
  display.drawCircle(cx, cy, 50, 1);

  // 🎯 Vẽ đuôi quét mờ dần (Draw fading scan tail)
  for (int t = 0; t < 3; t++) {
    float rad = (angle - t * 2) * 0.0174533;
    int x = cx + cos(rad) * 50;
    int y = cy - sin(rad) * 50;
    display.drawLine(cx, cy, x, y, 1);
  }

  // 🎯 Nếu có vật cản trong 30cm (If object detected)
  if (d > 0) {
    float rad = angle * 0.0174533;

    // Tỷ lệ 30cm = bán kính 50px (Scale: 30cm → 50px)
    float scale = 50.0 / 30.0;
    int px = cx + cos(rad) * (d * scale);
    int py = cy - sin(rad) * (d * scale);

    addPoint(px, py);
  }

  // 🎯 Vẽ các điểm cũ (Draw fading points)
  for (int i = 0; i < MAX_POINTS; i++) {
    if (pointLife[i] > 0) {
      display.fillCircle(pointX[i], pointY[i], 2, 1);
      pointLife[i]--;
    }
  }

  display.display();
}
