
  




  //       검    흰
  //1      500  100
  //2      617  100
  //3      550  100
  //4      605  90





void irRead(){
  IR1 = analogRead(ir1);//왼쪽부터 1번 ir센서
  IR2 = analogRead(ir2);//왼쪽부터 2번 ir센서
  IR3 = analogRead(ir3);//왼쪽부터 3번 ir센서
  IR4 = analogRead(ir4);//왼쪽부터 4번 ir센서
}




void line_ff(int value){//교차로
  int start_constant = 1;
  while(start_constant){
    start_constant = 0;
    irRead();
    while(IR1>300 || IR4>450){ //이미 교차로를 인식하고 있는 경우 벗어 날 때까지 움직여줌
      irRead();
      go(value,value);
    }
    while(IR1<200 && IR4<200){//교차로를 인식하기 전까지 라인트레이싱
      line_trace(value);
    }
    while(IR1>300 && IR4>450){//교차로를 인식하고 멈춤
      irRead();
      go(0,0);
      break; 
    }
  }
}

void line_fl(int value){//왼쪽교차로만
  int start_constant = 1;
  
  while(start_constant){
    start_constant = 0;
    irRead();
    while(IR1>300 || IR4>450){//이미 교차로를 인식하고 있는 경우 벗어 날 때까지 움직여줌
      irRead();
      go(value,value);
      }
    while(IR1<200 && IR4<200){//교차로를 인식하기 전까지 라인트레이싱
      irRead();
      line_trace(value);
    }
    while(IR1>300 && IR4<200){// ir1센서가 검정색을 인식되고 ir4센서는 검정색을 인식하지 않는 경우 멈춤
      irRead();
      go(0,0);
      break; 
    } 
  }
}

void line_fr(int value){//오른쪽교차로만
  int start_constant = 1;
  
  while(start_constant){
    start_constant = 0;
    irRead();
    while(IR1>300 || IR4>450){//이미 교차로를 인식하고 있는 경우 벗어 날 때까지 움직여줌
      irRead();
      go(value,value);
      }
    while(IR1<200 && IR4<200){//교차로를 인식하기 전까지 라인트레이싱
      line_trace(value);
    }
    while(IR1<200 && IR4>450){ //ir4센서가 검정색을 인식하고, ir1센서는 검정색을 인식하지 않는 경우 멈춤
        irRead();
        go(0,0);
        break;
    } 
  }
}


void linedelay(int value, int t){//시간만큼 라인트레이싱
  preMillis = millis();
  while(millis() - preMillis <= t){
    line_trace(value);
  }
}


void motor(int value_1, int value_2, int t){//시간만큼 양쪽모터 속도제어
  preMillis = millis();
  while(millis() - preMillis <= t){
    go(value_1,value_2);
  }
}




void line_trace(int value){//라인트레이싱
  irRead();
  if(IR2<250 && IR3<250){//ir2,3센서가 검정색을 인지하지 않은경우 앞으로 직진
    go(value,value);
  }
  else if(IR2>450 && IR3>400){//ir2,3번 센서 둘다 검정색을 인식할 경우 직진 
    go(value,value);
  }
  else if(IR2>450 && IR3<250){//ir2번 센서만 검정색을 인식할 경우 좌회전
    go(-10,30);
  }
  else if(IR2<250 && IR3>400){//ir3번 센서만 검정색을 인식할 경우 우회전
    go(30,-10);
  }
}

void line_trace_r(int value){//라인트레이싱 뒤로
  irRead();
  if(IR2<250 && IR3<250){
    go(value,value);
  }
  else if(IR2>450 && IR3>400){
    go(value,value);
  }
  else if(IR2>450 && IR3<250){//ir2번 센서만 검정색을 인식할 경우 뒤로 좌회전
    go(-30,10);
  }
  else if(IR2<250 && IR3>400){//ir3번 센서만 검정색을 인식할 경우 뒤로 우회전
    go(10,-30);
  }
}

void line_rr(int value){//뒤로가기전용오른쪽교차로만
  int start_constant = 1;
  
  while(start_constant){
    start_constant = 0;
    irRead();
    while(IR1>300 || IR4>450){
      irRead();
      go(value,value);
      }
    while(IR1<200 && IR4<200){//ir센서에 아무것도 걸리지 않을 경우 뒤로 라인트레이싱
      line_trace_r(value);
    }
    while(IR1<200 && IR4>450){//ir4번 센서가 검정색을 인식하는 경우 정지
        irRead();
        go(0,0);
        break;
    } 
  }
}

void exlinedelay(int value, int t){//교차로인식후 라인딜레이
  int start_constant = 1;
  
  while(start_constant){
    start_constant = 0;
    irRead();
    while(IR1>300 || IR4>450){
      irRead();
      go(value,value);
      }
    while(IR1<200 && IR4<200){//ir1,4번 센서 검정색 인식 안하면 시간만큼 라인트레이싱하고 정지
      irRead();
      linedelay(value,t); //시간 만큼 라인트레이싱
      go(0,0);
      break;
    } 
  }
}

                                                                                          
void meomcheo(){//2초동안 멈추기
  preMillis = millis();
  while(millis() - preMillis <= 2000){
    go(0,0);
  }
}

void mode2(){
  motor(0,0,5000); //장애물 회피구간 지나서 5초 정지
  RGB_OFF(); //led불 끄기
  motor(20,20,1500); // 1.5초 동안 ir센서 인식되는거 막아주고 밀어주기
  motor(0,0,500);//0.5초 정지
  line_fr(20);//오른쪽 교차로 만날 때까지 라인트레이싱하고 만나면 정지
  motor(20,20,1050); // 교차로 인식하고 1.05초동안 직진
  turn(30,-85); // 30rpm으로 시계방향으로 85도 회전
  linedelay(20,7000); //7초동안 라인트레이싱
  line_fl(20); //첫번 째 왼쪽 교차로 만날 때까지 라인트레이싱하고 만나면 정지
  motor(20,20,800); //0.8초동안 직진
  turn(30,65); //30rpm으로 반시계 방향으로 65도 회전
  line_fl(20);//두번 째 왼쪽 교차로 만날 때까지 라인트레이싱하고 만나면 정지
  motor(20,20,1650); //1.65초 동안 직진
  turn(30,115); // 30rpm으로 반시계 방향으로 115도 회전
  line_fr(20); // 오른쪽 교차로 만날 때까지 라인트레이싱하고 만나면 정지
  motor(20,20,1050); // 1.05초동안 직진
  turn(30,-83); //30rpm으로 시계방향으로 83도 회전
  linedelay(20,400); //0.4초동안 라인트레이싱
  line_rr(-20);// 뒤로 오른쪽 교차로 인식 될 때까지 후진으로 라인트레이싱
  exlinedelay(20,700); //교차로 벗어나고 0.7초동안 직진하고 정지
  meomcheo();//2초동안 정지
}
