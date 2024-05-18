void mode1(int a) {//초기상태(시간과 온습도,주기를 표시)
  DateTime now_time = RTC.now();
  dht1.read(humi_read[0], temp_read[0]);//1번 모듈 온습도 읽은값을 저장
  //dht2.read(humi_read[1], temp_read[1]);//2번 모듈 온습도 읽은값을 저장
  //dht3.read(humi_read[2], temp_read[2]);//3번 모듈 온습도 읽은값을 저장

  if (now_time.second() == 0 || now_time.second() == 1) {//60초에서 0초로 갈경우 60->00이 아닌 60->0으로 가므로 LCD에서 전 60에서 0이 남으므로 00다음 10 이런식으로 된다. 그러므로 LCD초기화 시킨다. 1의경우 delay가1000이므로 0을 뛰어넘는 경우가 간혹 발생하므로 1도 포함
    lcd.clear();
  }

  lcd.noCursor();//cursor안보이게
  lcd.noBlink();//blink없음
  lcd.setCursor(0, 0);
  lcd.print(now_time.year());
  lcd.print("/");
  lcd.print(now_time.month());
  lcd.print("/");
  lcd.print(now_time.day());
  lcd.print(" ");
  lcd.print(now_time.hour());
  lcd.print(":");
  lcd.print(now_time.minute());
  lcd.print(":");
  lcd.print(now_time.second());

  lcd.setCursor(19, 0);
  lcd.print(i);

  lcd.setCursor(0, 1);
  lcd.print("C:");
  lcd.print(temp_read[a]);
  lcd.print("*C");

  lcd.setCursor(0, 2);
  lcd.print("H:");
  lcd.print(humi_read[a]);
  lcd.print("%");

  lcd.setCursor(0, 3);
  lcd.print("Time:");
  lcd.print(term_load[a]-daycount[a]);//주기 - 날짜흐름 = 물주기까지 남은 날짜
  preMillis = millis();
  while (millis() - preMillis <= 1000) {//버튼을 누르면 break를 줘서 바로 응답하게 설정
    tact1_dp = tactswitch1;
    tact2_dp = tactswitch2;
    tact3_dp = tactswitch3;
    tact4_dp = tactswitch4;
    tact_1();
    tact_2();
    tact_3();
    tact_4();
    if (tact1_dp != tactswitch1) {
      mode[a] = 2;//모드2(설정 선택창으로 넘어감)
      break;
    }
    if (tact3_dp != tactswitch3) {//그 다음 모듈 status창을 띄움
      i++;
      if (i == 4) {
        i = 1;
      }
      lcd.clear();
      break;
    }
    if (tact4_dp != tactswitch4) {//그 전 모듈 status창을 띄움
      i--;
      if (i == 0) {
        i = 3;
      }
      lcd.clear();
      break;
    }
  }
}
