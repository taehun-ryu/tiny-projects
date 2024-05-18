void water_pump(int j) {//물주기
  toyang[j] = analogRead(toyang1 + j);//토양습도센서 값을 불러옴
  lcd.clear();
  lcd.setCursor(4,1);
  lcd.print("The plant is");
  lcd.setCursor(3,2);
  lcd.print("being watered!");
  delay(1500);
  while ( toyang[j] > 800)   // 토양 습도 체크 800보다 높으면 모터 동작 시켜 물공급 아니면 정지(높을 수록 건조함,최대:1023)
  {
    digitalWrite(motor1 + j, HIGH);
    delay(500);//토양센서가 응답속도가 0.3s이므로 delay추가
    toyang[j] = analogRead(toyang1 + j);//반복문 안에서 값을 계속 받아옴
  }
  digitalWrite(motor1 + j, LOW);//800미만이 되면 어느정도 물을 주었다고 판단 후 모터작동 중지
  lcd.clear();
}
