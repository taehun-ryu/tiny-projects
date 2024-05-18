void mode3(int a) {
  lcd.clear();
  lcd.noCursor();
  lcd.noBlink();
  lcd.setCursor(0, 0);
  if (mode_2[a] >= 1 && mode_2[a] <= 5) {
    if(mode_2[a] == 1){
      lcd.print("Dracaena stuckyi");
    }
    else if(mode_2[a] == 2){
      lcd.print("Sansevieria");
    }
    else if(mode_2[a] == 3){
      lcd.print("Lettuce");
    }
    else if(mode_2[a] == 4){
      lcd.print("Cherry tomato");
    }
    else if(mode_2[a] == 5){
      lcd.print("Monstera");
    }

    lcd.setCursor(0, 1);
    lcd.print("H:");
    lcd.print(humi_save_low[(mode_2[a] - 1)]);
    lcd.print("%~");
    lcd.print(humi_save_high[(mode_2[a] - 1)]);
    lcd.print("%");

    lcd.setCursor(0, 2);
    lcd.print("C:");
    lcd.print(temp_save_low[(mode_2[a] - 1)]);
    lcd.print("*C~");
    lcd.print(temp_save_high[(mode_2[a] - 1)]);
    lcd.print("*C");

    lcd.setCursor(0, 3);
    lcd.print("Term:");
    lcd.print(term_save[(mode_2[a] - 1)]);

    while (1) {
      int end_constant = 0;//while문을 끝내주기 위해 만든 변수(lcd화면을 지속시켜주어야 하기에 반복문을 써주어야한다)
      tact1_dp = tactswitch1;
      tact2_dp = tactswitch2;
      tact_1();
      tact_2();
      if (tact1_dp != tactswitch1) {
        mode[a] = 2;
        break;
      }
      if (tact2_dp != tactswitch2) {
        while (1) {
          lcd.clear();
          lcd.noCursor();
          lcd.noBlink();
          lcd.setCursor(4, 1);
          lcd.print("Are you sure?");
          lcd.setCursor(4, 2);
          lcd.print("Yes");
          lcd.setCursor(14, 2);
          lcd.print("No");
          while (count == 0) {
            lcd.setCursor(7, 2);
            lcd.cursor();
            lcd.blink();
            tact2_dp = tactswitch2;
            tact3_dp = tactswitch3;
            tact4_dp = tactswitch4;
            tact_2();
            tact_3();
            tact_4();
            if (tact2_dp != tactswitch2) {
              humi_load_low[a] = humi_save_low[(mode_2[a] - 1)];
              humi_load_high[a] = humi_save_high[(mode_2[a] - 1)];
              temp_load_low[a] = temp_save_low[(mode_2[a] - 1)];
              temp_load_high[a] = temp_save_high[(mode_2[a] - 1)];
              term_load[a] = term_save[(mode_2[a] - 1)];
              daycount[a] = 0;
              end_constant = 1;
              settingflag[a] = 1;
              break;
            }
            if (tact3_dp != tactswitch3) {
              count++;
              if (count == 2) {
                count = 0;
                break;
              }
            }
            if (tact4_dp != tactswitch4) {
              count--;
              if (count == -1) {
                count = 1;
                break;
              }
            }
          }
          while (count == 1) {
            lcd.setCursor(16, 2);
            lcd.cursor();
            lcd.blink();
            tact2_dp = tactswitch2;
            tact3_dp = tactswitch3;
            tact4_dp = tactswitch4;
            tact_2();
            tact_3();
            tact_4();
            if (tact2_dp != tactswitch2) {
              end_constant = 1;
              break;
            }
            if (tact3_dp != tactswitch3) {
              count++;
              if (count == 2) {
                count = 0;
                break;
              }
            }
            if (tact4_dp != tactswitch4) {
              count--;
              if (count == -1) {
                count = 1;
                break;
              }
            }
          }
          if (end_constant) {
            break;
          }
        }
        if (end_constant) {
          break;
        }
      }
    }
    count = 0;
  }

  else if (mode_2[a] >= 6 && mode_2[a] <= 8) {
    lcd.clear();
    lcd.noCursor();
    lcd.noBlink();
    lcd.print("custom");
    lcd.print(mode_2[a] - 5);
    lcd.setCursor(0, 1);
    lcd.print("H:");
    lcd.print(humi_load_low[a]);
    lcd.print("%~");
    lcd.print(humi_load_high[a]);
    lcd.print("%");

    lcd.setCursor(0, 2);
    lcd.print("C:");
    lcd.print(temp_load_low[a]);
    lcd.print("*C~");
    lcd.print(temp_load_high[a]);
    lcd.print("*C");

    lcd.setCursor(0, 3);
    lcd.print("Term:");
    lcd.print(term_load[a]);

    while (1) {
      int end_constant = 0;
      lcd.noCursor();
      lcd.noBlink();
      tact1_dp = tactswitch1;
      tact2_dp = tactswitch2;
      tact_1();
      tact_2();
      if (tact1_dp != tactswitch1) {
        mode[a] = 2;
        break;
      }

      if (tact2_dp != tactswitch2) {
        for (int j = 5; j < 8; j++) {
          humi_save_low[j] = humi_ini;
          humi_save_high[j] = humi_ini;
          temp_save_low[j] = temp_ini;
          temp_save_high[j] = temp_ini;
          term_save[j] = term_ini;
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("custom");
        lcd.print(mode_2[a] - 5);
        lcd.setCursor(0, 1);
        lcd.print("H:");
        lcd.print(humi_save_low[(mode_2[a] - 1)]);
        lcd.print("%~");
        lcd.print(humi_save_high[(mode_2[a] - 1)]);
        lcd.print("%");

        lcd.setCursor(0, 2);
        lcd.print("C:");
        lcd.print(temp_save_low[(mode_2[a] - 1)]);
        lcd.print("*C~");
        lcd.print(temp_save_high[(mode_2[a] - 1)]);
        lcd.print("*C");

        lcd.setCursor(0, 3);
        lcd.print("Term:00");
        lcd.print(term_save[(mode_2[a] - 1)]);
        while (1) {
          tact1_dp = tactswitch1;
          tact2_dp = tactswitch2;
          tact3_dp = tactswitch3;
          tact4_dp = tactswitch4;
          tact_1();
          tact_2();
          tact_3();
          tact_4();
          if (tact1_dp != tactswitch1) {
            mode[a] = 2;
            break;
          }

          while (count == 0) {
            if (humi_save_low[(mode_2[a] - 1)] < 0) {
              humi_save_low[(mode_2[a] - 1)] = 0;
              lcd.setCursor(2, 1);
              lcd.print("0");
              lcd.print(humi_save_low[(mode_2[a] - 1)]);
              lcd.setCursor(3, 1);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  humi_save_low[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  humi_save_low[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  humi_load_low[a] = humi_save_low[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (humi_save_low[(mode_2[a] - 1)] > 99) {
              humi_save_low[(mode_2[a] - 1)] = 99;
              lcd.setCursor(2, 1);
              lcd.print(humi_save_low[(mode_2[a] - 1)]);
              lcd.setCursor(3, 1);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  humi_save_low[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  humi_save_low[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  humi_load_low[a] = humi_save_low[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (humi_save_low[(mode_2[a] - 1)] < 10) {
              lcd.setCursor(2, 1);
              lcd.print("0");
              lcd.print(humi_save_low[(mode_2[a] - 1)]);
              lcd.setCursor(3, 1);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  humi_save_low[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  humi_save_low[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  humi_load_low[a] = humi_save_low[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (humi_save_low[(mode_2[a] - 1)] >= 10 && humi_save_low[(mode_2[a] - 1)] <= 99) {
              lcd.setCursor(2, 1);
              lcd.print(humi_save_low[(mode_2[a] - 1)]);
              lcd.setCursor(3, 1);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  humi_save_low[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  humi_save_low[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  humi_load_low[a] = humi_save_low[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }
            if (end_constant == 1) {
              break;
            }
          }

          while (count == 1) {
            end_constant = 0;

            if (humi_save_high[(mode_2[a] - 1)] <= humi_save_low[(mode_2[a] - 1)]) {
              humi_save_high[(mode_2[a] - 1)] = humi_save_low[(mode_2[a] - 1)] + 1;
            }

            else if (humi_save_high[(mode_2[a] - 1)] < 0) {
              humi_save_high[(mode_2[a] - 1)] = 0;
              lcd.setCursor(9, 1);
              lcd.print("0");
              lcd.print(humi_save_high[(mode_2[a] - 1)]);
              lcd.setCursor(10, 1);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  humi_save_high[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  humi_save_high[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  humi_load_high[a] = humi_save_high[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (humi_save_high[(mode_2[a] - 1)] > 99) {
              humi_save_high[(mode_2[a] - 1)] = 99;
              lcd.setCursor(9, 1);
              lcd.print(humi_save_high[(mode_2[a] - 1)]);
              lcd.setCursor(10, 1);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  humi_save_high[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  humi_save_high[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  humi_load_high[a] = humi_save_high[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (humi_save_high[(mode_2[a] - 1)] < 10) {
              lcd.setCursor(9, 1);
              lcd.print("0");
              lcd.print(humi_save_high[(mode_2[a] - 1)]);
              lcd.setCursor(10, 1);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  humi_save_high[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  humi_save_high[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  humi_load_high[a] = humi_save_high[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }
            else if (humi_save_high[(mode_2[a] - 1)] >= 10 && humi_save_high[(mode_2[a] - 1)] <= 99) {
              lcd.setCursor(9, 1);
              lcd.print(humi_save_high[(mode_2[a] - 1)]);
              lcd.setCursor(10, 1);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  humi_save_high[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  humi_save_high[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  humi_load_high[a] = humi_save_high[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }
            if (end_constant == 1) {
              break;
            }
          }

          while (count == 2) {
            end_constant = 0;
            if (temp_save_low[(mode_2[a] - 1)] < 0) {
              temp_save_low[(mode_2[a] - 1)] = 0;
              lcd.setCursor(2, 2);
              lcd.print("0");
              lcd.print(temp_save_low[(mode_2[a] - 1)]);
              lcd.setCursor(3, 2);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  temp_save_low[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  temp_save_low[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  temp_load_low[a] = temp_save_low[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (temp_save_low[(mode_2[a] - 1)] > 99) {
              temp_save_low[(mode_2[a] - 1)] = 99;
              lcd.setCursor(2, 2);
              lcd.print(temp_save_low[(mode_2[a] - 1)]);
              lcd.setCursor(3, 2);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  temp_save_low[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  temp_save_low[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  temp_load_low[a] = temp_save_low[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (temp_save_low[(mode_2[a] - 1)] < 10) {
              lcd.setCursor(2, 2);
              lcd.print("0");
              lcd.print(temp_save_low[(mode_2[a] - 1)]);
              lcd.setCursor(3, 2);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  temp_save_low[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  temp_save_low[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  temp_load_low[a] = temp_save_low[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (temp_save_low[(mode_2[a] - 1)] >= 10 && temp_save_low[(mode_2[a] - 1)] <= 99) {
              lcd.setCursor(2, 2);
              lcd.print(temp_save_low[(mode_2[a] - 1)]);
              lcd.setCursor(3, 2);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  temp_save_low[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  temp_save_low[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  temp_load_low[a] = temp_save_low[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }
            if (end_constant == 1) {
              break;
            }
          }

          while (count == 3) {
            end_constant = 0;

            if (temp_save_high[(mode_2[a] - 1)] <= temp_save_low[(mode_2[a] - 1)]) {
              temp_save_high[(mode_2[a] - 1)] = temp_save_low[(mode_2[a] - 1)] + 1;
            }

            else if (temp_save_high[(mode_2[a] - 1)] < 0) {
              temp_save_high[(mode_2[a] - 1)] = 0;
              lcd.setCursor(10, 2);
              lcd.print("0");
              lcd.print(temp_save_high[(mode_2[a] - 1)]);
              lcd.setCursor(11, 2);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  temp_save_high[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  temp_save_high[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  temp_load_high[a] = temp_save_high[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (temp_save_high[(mode_2[a] - 1)] > 99) {
              temp_save_high[(mode_2[a] - 1)] = 99;
              lcd.setCursor(10, 2);
              lcd.print(temp_save_high[(mode_2[a] - 1)]);
              lcd.setCursor(11, 2);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  temp_save_high[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  temp_save_high[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  temp_load_high[a] = temp_save_high[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (temp_save_high[(mode_2[a] - 1)] < 10) {
              lcd.setCursor(10, 2);
              lcd.print("0");
              lcd.print(temp_save_high[(mode_2[a] - 1)]);
              lcd.setCursor(11, 2);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  temp_save_high[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  temp_save_high[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  temp_load_high[a] = temp_save_high[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (temp_save_high[(mode_2[a] - 1)] >= 10 && temp_save_high[(mode_2[a] - 1)] <= 999) {
              lcd.setCursor(10, 2);
              lcd.print(temp_save_high[(mode_2[a] - 1)]);
              lcd.setCursor(11, 2);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  temp_save_high[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  temp_save_high[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  temp_load_high[a] = temp_save_high[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }
            if (end_constant == 1) {
              break;
            }
          }

          while (count == 4) {
            end_constant = 0;

            if (term_save[(mode_2[a] - 1)] < 0) {
              term_save[(mode_2[a] - 1)] = 0;
              lcd.setCursor(5, 3);
              lcd.print("00");
              lcd.print(term_save[(mode_2[a] - 1)]);
              lcd.setCursor(7, 3);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  term_save[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  term_save[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  term_load[a] = term_save[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (term_save[(mode_2[a] - 1)] >= 100 && term_save[(mode_2[a] - 1)] <= 999) {
              lcd.setCursor(5, 3);
              lcd.print(term_save[(mode_2[a] - 1)]);
              lcd.setCursor(7, 3);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  term_save[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  term_save[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  term_load[a] = term_save[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (term_save[(mode_2[a] - 1)] < 10) {
              lcd.setCursor(5, 3);
              lcd.print("00");
              lcd.print(term_save[(mode_2[a] - 1)]);
              lcd.setCursor(7, 3);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  term_save[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  term_save[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  term_load[a] = term_save[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (term_save[(mode_2[a] - 1)] >= 10 && term_save[(mode_2[a] - 1)] <= 99) {
              lcd.setCursor(5, 3);
              lcd.print("0");
              lcd.print(term_save[(mode_2[a] - 1)]);
              lcd.setCursor(7, 3);
              while (1) {
                tact1_dp = tactswitch1;
                tact2_dp = tactswitch2;
                tact3_dp = tactswitch3;
                tact4_dp = tactswitch4;
                tact_1();
                tact_2();
                tact_3();
                tact_4();
                if (tact3_dp != tactswitch3) {
                  term_save[(mode_2[a] - 1)]++;
                  break;
                }
                if (tact4_dp != tactswitch4) {
                  term_save[(mode_2[a] - 1)]--;
                  break;
                }
                if (tact2_dp != tactswitch2) {
                  count++;
                  term_load[a] = term_save[(mode_2[a] - 1)];
                  break;
                }
                if (tact1_dp != tactswitch1) {
                  mode[a] = 2;
                  end_constant = 1;
                  break;
                }
                lcd.cursor();
                lcd.blink();
              }
            }

            else if (term_save[(mode_2[a] - 1)] > 999) {
              term_save[(mode_2[a] - 1)] = 999;
            }

            if (end_constant == 1) {
              break;
            }
          }

          if (count == 5) {
            count = 0;
            end_constant = 1;
            settingflag[a] = 1;
            daycount[a] = 0;
            break;
          }

          if (end_constant == 1) {
            break;
          }
        }
      }
      if (end_constant == 1) {
        break;
      }
    }
  }
}
