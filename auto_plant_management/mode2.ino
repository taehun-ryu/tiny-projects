void mode2(int a) {//설정 선택창(식물 종류 선택 또는 custom 선택)
  lcd.noCursor();
  lcd.noBlink();
  if (mode_2[a] <= 4 && mode_2[a] >=1) {//여가서 mode_2[a]는 (a+1)째 모듈이 mode2에서 몇번째 칸을 보고있느냐(커서위치를 의미)를 나타냄
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dracaena stuckyi");
    lcd.setCursor(0, 1);
    lcd.print("Sansevieria");
    lcd.setCursor(0, 2);
    lcd.print("Lettuce");
    lcd.setCursor(0, 3);
    lcd.print("Cherry tomato");
  }
  else if (mode_2[a] <= 8 && mode_2[a] >4) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Monstera");
    lcd.setCursor(0, 1);
    lcd.print("custom1");
    lcd.setCursor(0, 2);
    lcd.print("custom2");
    lcd.setCursor(0, 3);
    lcd.print("custom3");
  }


  if (mode_2[a] == 1) {
    lcd.setCursor(16, 0);
    lcd.cursor();
    lcd.blink();
  }
  else if (mode_2[a] == 2) {
    lcd.setCursor(11, 1);
    lcd.cursor();
    lcd.blink();
  }
  else if (mode_2[a] == 3) {
    lcd.setCursor(7, 2);
    lcd.cursor();
    lcd.blink();
  }
  else if (mode_2[a] == 4) {
    lcd.setCursor(13, 3);
    lcd.cursor();
    lcd.blink();
  }
  else if (mode_2[a] == 5) {
    lcd.setCursor(8, 0);
    lcd.cursor();
    lcd.blink();
  }
  else if (mode_2[a] == 6) {
    lcd.setCursor(7, 1);
    lcd.cursor();
    lcd.blink();
  }
  else if (mode_2[a] == 7) {
    lcd.setCursor(7, 2);
    lcd.cursor();
    lcd.blink();
  }
  else if (mode_2[a] == 8) {
    lcd.setCursor(7, 3);
    lcd.cursor();
    lcd.blink();
  }



  while (1) {
    tact1_dp = tactswitch1;
    tact2_dp = tactswitch2;
    tact3_dp = tactswitch3;
    tact4_dp = tactswitch4;
    tact_1();
    tact_2();
    tact_3();
    tact_4();
    if (tact1_dp != tactswitch1) {//취소버튼
      mode_2[a] = 1;//모드1로 돌아갈 경우에는 초기화
      mode[a] = 1;
      lcd.clear();
      break;
    }
    if (tact2_dp != tactswitch2) {
      mode[a] = 3;//확인버튼을 눌렀을경우 모드3으로 이동
      break;
    }
    if (tact3_dp != tactswitch3) {//mode_2[a]를 감소시켜 칸(커서)이동
      mode_2[a]--;
      if (mode_2[a] == 0) {
        mode_2[a] = 8;
      }
      break;
    }
    if (tact4_dp != tactswitch4) {//mode_2[a]를 증가시켜 칸(커서)이동
      mode_2[a]++;
      if (mode_2[a] == 9) {
        mode_2[a] = 1;
      }
      break;
    }
  }
}
