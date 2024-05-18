unsigned long mode1Mi=0;

void escape()
{
  TS_c();
  if(num_b>1){
  
  mode = 2;
    analogWrite(RGB_R ,255);
    analogWrite(RGB_G ,255);
    analogWrite(RGB_B ,255);
  }
  
 }

void mode1(){
  escape();
  motor(20,20,500);//500밀리초만큼 각 모터 20rpm으로 감
  motor(0,0,200);//멈춤
  sn_distance();//소나센서값읽기
  sonor_in_check();//소나값읽힐때 조건
  line_out_check();//코스밖으로 나가기직전에 조건
  

  Serial.print(final_x);
  Serial.print(" , ");
  Serial.print(final_y);
  Serial.print(" , ");
  Serial.println(last_Seta);
}
  
  //종점 x 140, y 95
  //전체 맵 크기 x: 155,  y: 95
  

  //인터럽트 코드 안해치는 한에서 최대한으로 불러올수 있는 시간 노가다 하기

void sonor_in_check(){//소나센서로 장애물 인식할경우 조건
  
  if(sn[1] <= 10 && sn[2] <= 10 && sn[3] <= 10 ){//3개 모두 장애물 탐지했을경우
    motor(-30,-30,500);
    if(sn[1] == max(sn[1],sn[3])) turn(30,-45);//왼쪽이 가장클경우 우회전
    else if(sn[3] == max(sn[1],sn[3])) turn(30,45);//오른쪽이 클경우 좌회전
    }
  else if(sn[1] > 10 && sn[2] <= 10 && sn[3] > 10 ){//중앙소나센서만 인식할경우 우회전
    turn(30,-45);
    }
  else if(sn[1] <= 10 && sn[2] > 10 && sn[3] > 10 ){//좌측 소나센서만 인식할경우 뒤로갔다가 우회전
    motor(-30,-30,300);
    turn(30,-45);
    }
  else if(sn[1] > 10 && sn[2] > 10 && sn[3] <= 10 ){//우측 소나센서만 인식할경우 뒤로갔다가 좌회전
    motor(-30,-30,300);
    turn(30,45);
    }
}



void line_out_check(){//코스밖으로 나가기직전 오도메트리활용 조건
  if(final_x>=143 && final_y>=60){ //(143,60)에 왔을경우 교차로방향 바라보게 회전하고 교차로인식할때까지 직진(대신 이 좌표까지 왔을때 직진하고있는 사이 장애물이 있을경우 밀어버림;;)
    analogWrite(RGB_R ,255);
    analogWrite(RGB_G ,255);
    analogWrite(RGB_B ,255);
    turn_Seta = last_Seta;//last_seta는 odometry에서 인터럽트로 불러오면서 좌표변화로 계산한 각도(라디안)값이다(그래서 초기 각도 값이 매우 중요함)
    if(turn_Seta>=0) turn(30,-90+turn_Seta);
    else turn(30,turn_Seta-90);
    go(0,0);
    line_ff(20);//교차로 인식하기전까지 직진
    motor(0,0,1000);
    mode=2;
  }
  if(final_y>=90 && final_x<145){//우측코스밖나가기직전
    rightcorner();
    motor(10,10,1000);
  }
  if(final_x>=146 && final_y<95){//위쪽코스밖나가기직전
    overcorner();
    motor(10,10,1000);
    analogWrite(RGB_R ,255);
    analogWrite(RGB_G ,255);
    analogWrite(RGB_B ,255);
    go(0,0);
    line_ff(20);
    motor(0,0,1000);
    mode=2;
  }
  if(final_x<=-2 && final_y<95){//아래쪽코스밖나가기직전
    undercorner();
    motor(10,10,1000);
  }
  if(final_y<=-2 && final_x<145){//좌측코스밖나가기직전
    leftcorner();
    motor(10,10,1000);
  }
  
}



void leftcorner(){//좌측코스밖나가기직전에서 뒤로 갔다가 좌측코스와 평행한 선과 시계방향으로 5도 차이나게 돌아줌
  turn_Seta = last_Seta;
  if(turn_Seta>=0){
    go(0,0);
    motor(-10,-10,1000);
    turn(30,turn_Seta+5);
  }
  if(turn_Seta<0){
    go(0,0);
    motor(-10,-10,1000);
    turn(30,turn_Seta-5);
  }
}
void rightcorner(){//우측코스밖나가기직전에서 뒤로 갔다가 우측코스와 평행한 선과 반시계방향으로 5도 차이나게 돌아줌
  turn_Seta = last_Seta;
  if(turn_Seta>=0){
    //motor(0,0,2000);
    motor(-10,-10,1000);
    //turn_Seta +=5;    
    turn(30,turn_Seta+5);
  }
  if(turn_Seta<0){
    go(0,0);
    motor(-10,-10,1000);
    turn(30,-185+turn_Seta);
  }
}
void overcorner(){//위쪽코스밖나가기직전에서 위쪽코스와 평행한 선에서 교차로를 바로보게 돌아줌
  turn_Seta = last_Seta;
  if(turn_Seta>=0){
    go(0,0);
    turn(30,-90+turn_Seta);
  }
  if(turn_Seta<0){
    go(0,0);
    turn(30,turn_Seta-90);
  }
}
void undercorner(){//아래쪽코스밖나가기직전에서 아래쪽코스와 평행한 선에서 우측코스 수직방향을 바라보게 돌아줌
  turn_Seta = last_Seta;
  if(turn_Seta>=0){
    go(0,0);
    motor(-10,-10,1000);
    turn(30,-90-turn_Seta);
  }
  if(turn_Seta<0){
    go(0,0);
    motor(-10,-10,1000);
    turn(30,90-turn_Seta);
  }
}

void callingbaby(){//소나센서 값을 최신화함(serialprint로 while,for문 안에서 최신화가 가능하더라구요)
  for(int i =0; i<5; i++){
    Serial.println(sn[i]);
  }
}
