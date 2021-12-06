// 스위치로 LED제어  VR로 점등 속도 변경
// 1.1.1

#define SW1 digitalRead(9)
#define SW2 digitalRead(10)

#define BUZZER(x) digitalWrite(12, x)

#define VR analogRead(A1)     // 0...1023

void setup() {
  Serial.begin(9600);
  
  pinMode(2, OUTPUT);         // led1
  pinMode(3, OUTPUT);         // led2
  pinMode(4, OUTPUT);         // led3
  pinMode(5, OUTPUT);         // led4
  pinMode(6, OUTPUT);         // led5
  pinMode(7, OUTPUT);         // led6

  pinMode(12, OUTPUT);        // BUZZER
  
  pinMode(9, INPUT_PULLUP);   // SW1
  pinMode(10, INPUT_PULLUP);  // SW2
}
 
int led_control = 0;  // 0...6

int mode = 0;

int sec = 0;

int sw_mode;

void BUZ(int n, int c) {
  for (int i = 0; i < n; i++) {
    BUZZER(1);
    delay(c);
    BUZZER(0);
  }
}

void SW_Control(int *t) {
  if (SW1==0)   sw_mode = 1;
  if (SW2==0)   sw_mode = 2;
  
  if (SW1==1 && sw_mode==1) {
    BUZ(1, 100);
    sw_mode = 0;
    if (*t < 8)
      *t += 1;
    else
      BUZ(1,100);
  }
  if (SW2==1 && sw_mode==2) {
    BUZ(1, 100);
    sw_mode = 0;
    if (*t > 0)
      *t -= 1;
    else
      BUZ(1,100);
  }
}

void clock_check() {
  if (sec >= VR) {
    sec = 0;
    
    mode = mode==1 ? 0 : 1;
  }
  else  sec++;
}

void loop() {
  SW_Control(&led_control);
  Serial.println(String(sw_mode) + "\t" + String(SW1) + "\t" + String(SW2) + "\t" + "\t" + String(VR) + "\t" + String(sec) + "\t" + String(mode));
  
  delay(1);
  clock_check();
  
  if (mode == 0) {
    digitalWrite(2, led_control > 1);
    digitalWrite(3, led_control > 2);
    digitalWrite(4, led_control > 3);
    digitalWrite(5, led_control > 4);
    digitalWrite(6, led_control > 5);
    digitalWrite(7, led_control > 6);
  }
  
  if (mode == 1) {
    digitalWrite(2, led_control < 1);
    digitalWrite(3, led_control < 2);
    digitalWrite(4, led_control < 3);
    digitalWrite(5, led_control < 4);
    digitalWrite(6, led_control < 5);
    digitalWrite(7, led_control < 6);
  }
}
