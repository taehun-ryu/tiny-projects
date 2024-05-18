void water_check() {//수위 체크
  sen0204_value = digitalRead(sen0204);//수위센서 값을 불러옴
  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.print("water check...");
  delay(2000);//응답속도가 존재하여 (약 1.5s~1.8s)필수적으로 delay사용
  if (sen0204_value == 1) {//물이 있다고 인식하면 그냥 넘어감
    lcd.clear();
    prehour = now_time.hour();//1시간 차이날때마다 실행되므로 한번 실행 후 무조건 초기화 시켜주어야함!
  }
  else if (sen0204_value == 0) {//물이 없다고 인식될 경우 "물부족!"이라고 LCD에 알린 후 초기로 돌아감
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("water shortage!!");
    delay(5000);
    lcd.clear();
    prehour = now_time.hour();
  }
}
