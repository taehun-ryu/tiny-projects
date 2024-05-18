#include <MsTimer2.h>
#include <TimerFive.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <string.h>

#define ENC1_CHA 18 //Yellow //오른쪽 모터
#define ENC1_CHB 2 //Green
#define M1_DIR1 8
#define M1_DIR2 12
#define M1_PWM 10

#define ENC2_CHA 19 //Yellow //왼쪽 모터
#define ENC2_CHB 3 //Green
#define M2_DIR1 6
#define M2_DIR2 7
#define M2_PWM 9

#define TRIG1 30 //소나센서
#define ECHO1 31
#define TRIG2 32
#define ECHO2 33
#define TRIG3 34
#define ECHO3 35
#define TRIG4 36
#define ECHO4 37
#define TRIG5 38
#define ECHO5 39


#define ir1 A0 //ir센서
#define ir2 A1
#define ir3 A2
#define ir4 A3


#define RGB_R 46 //RGB
#define RGB_G 47
#define RGB_B 48


#define S_LED 13 //color센서 20 21 13


#define Tact_a 22 //tact 스위치a
#define Tact_b 23 //tact 스위치b



//for colror sensor
uint16_t r, g, b, c;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);


double sn[5]={0,0,0,0,0};
unsigned long nowMillis = millis();
unsigned long preMillis = 0;  //정목 변수

//PID제어
float Kp1 = 0.5;  //오른쪽 모터
float Ki1 = 0.3;
float Kd1 = 0.3;
float Kp2 = 0.5; //왼쪽모터
float Ki2 = 0.3;
float Kd2 = 0.3;
int e1cnt = 0;
int e1cnt_k = 0, e1cnt_k_1 = 0, d_e1cnt = 0;
float m1speed = 0;
float m1_ref_spd = 0;
float m1_err_spd = 0;
float m1_err_spd_k_1 = 0;
float m1_derr_spd = 0;
float m1_err_sum = 0;
float m1_ctrl_up = 0;
float m1_ctrl_ui = 0;
float m1_ctrl_ud = 0;
int m1_ctrl_u = 0;
int m1_ipwm_u = 0;
int e2cnt = 0;
int e2cnt_k = 0, e2cnt_k_1 = 0, d_e2cnt = 0;
float m2speed = 0;
float m2_ref_spd = 0;
float m2_err_spd = 0;
float m2_err_spd_k_1 = 0;
float m2_derr_spd = 0;
float m2_err_sum = 0;
float m2_ctrl_up = 0;
float m2_ctrl_ui = 0;
float m2_ctrl_ud = 0;
int m2_ctrl_u = 0;
int m2_ipwm_u = 0;





/////////////////////////////근우
int num_a = 0;
int num_b = 0;
int a = 0;
bool data_a = true;
bool data_b = true;




//********승학 변수***********//
int red =0;
int green =0; 
int blue =0;


int cl_red=50+3; //cl_red-90*
int cl_green=70+5;//90도 보다 커지면 -0 작으면 +5 (주의!! 90도보다클때 90도랑 차이 별로안날때는 -5도~-0도 비례하게 해주기!, 90도보다 작을때 90도랑 차이안날때는 +8도~+3도로 비례하게주기)
int cl_blue=90;

int flag=1;
int mode=0;
unsigned long timeline;
//**************************//
int IR1;
int IR2;
int IR3;
int IR4;

int sn_i = 0;

bool t5_flag = 0;
char sec = NULL;

bool u2_rcv_flag = false;
byte u2_rcv_data = '0';



/************************************************/

double diameter = 6.85; //바퀴 지름, cm
double deltaSL=0, deltaSR=0, deltaS=0, deltaSeta=0;
double SL_k=0, SL_k_1=0,SR_k=0, SR_k_1=0 ;
double SL=0,SR=0,d_deltaSLR=0;
double wheelbase = 21.4; //바퀴 중심 사이 거리, cm
double Seta = 0;
double x=0;
double y=0;
double pulseCount = 1320; // 바퀴 1회전 당 엔코더 펄스 수 1320
double circumference = 3.1415926535897932384626433832795 * diameter; //원주계산

double deltaX = 0, deltaY =0; // x,y 변화량

double final_x = 0, final_y =0; //최종 좌표
double final_x_k = 0, final_y_k =0,final_x_k_1 = 0,final_y_k_1 = 0;

double i_degree = 60;  // 출발각도
double i_radian = (i_degree * 3.1415926535897932384626433832795)/180;  // 출발각도 라디안 변환

double last_Seta; // 현재 로봇 주행 각도
double turn_Seta;
/************************************************/







void setup() {
  //RGB
  pinMode( RGB_R, OUTPUT);
  pinMode(RGB_G, OUTPUT);
  pinMode( RGB_B, OUTPUT);
  
  //COLOR센서
  pinMode(S_LED, OUTPUT);
  digitalWrite(S_LED, HIGH);
  tcs.begin();
  
  //ir센서
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);

  //소나센서
  pinMode(TRIG1, OUTPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(TRIG3, OUTPUT);
  pinMode(TRIG4, OUTPUT);
  pinMode(TRIG5, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(ECHO2, INPUT);
  pinMode(ECHO3, INPUT);
  pinMode(ECHO4, INPUT);
  pinMode(ECHO5, INPUT);

  //모터제어
  pinMode(ENC1_CHA, INPUT_PULLUP);
  pinMode(ENC1_CHB, INPUT_PULLUP);
  pinMode(M1_DIR1, OUTPUT);
  pinMode(M1_DIR2, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(ENC2_CHA, INPUT_PULLUP);
  pinMode(ENC2_CHB, INPUT_PULLUP);
  pinMode(M2_DIR1, OUTPUT);
  pinMode(M2_DIR2, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ENC1_CHA), Enc1chA_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC1_CHB), Enc1chB_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC2_CHA), Enc2chA_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC2_CHB), Enc2chB_ISR, CHANGE);
  digitalWrite(M1_DIR1, LOW);
  digitalWrite(M1_DIR2, HIGH);
  analogWrite(M1_PWM, 0);
  digitalWrite(M2_DIR1, LOW);
  digitalWrite(M2_DIR2, HIGH);
  analogWrite(M2_PWM, 0);
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial.setTimeout(50);
  Timer5.initialize(50000); //50msec,
  Timer5.attachInterrupt(T5ISR); //T5ISR
  

  pinMode(Tact_a, INPUT_PULLUP);
  pinMode(Tact_b, INPUT_PULLUP);

}

void trigLow() {//트리거 초기화
  digitalWrite(TRIG1, LOW);
  digitalWrite(TRIG2, LOW);
  digitalWrite(TRIG3, LOW);
  digitalWrite(TRIG4, LOW);
  digitalWrite(TRIG5, LOW);
}


void go(float spdB, float spdA) {
  //시리얼 플로터 PID확인

  m1_ref_spd = spdA;
  m2_ref_spd = spdB;
  //m2_ref_spd = map(spdB, -255, 255, -311, 311);
  if (t5_flag) {

    t5_flag = 0;

    m1speed = d_e1cnt * 10 / 11; // *500/11/50
    m2speed = d_e2cnt * 10 / 11; // *500/11/50

    //Error
    m1_err_spd = -m1_ref_spd - m1speed;
    m1_derr_spd = m1_err_spd - m1_err_spd_k_1;
    m1_err_sum = m1_err_sum + m1_err_spd;
    m1_err_spd_k_1 = m1_err_spd;

    m2_err_spd = m2_ref_spd - m2speed;
    m2_derr_spd = m2_err_spd - m2_err_spd_k_1;
    m2_err_sum = m2_err_sum + m2_err_spd;
    m2_err_spd_k_1 = m2_err_spd;

    //PID-Controller
    m1_ctrl_up = Kp1 * m1_err_spd;
    m1_ctrl_ui = Ki1 * m1_err_sum;
    m1_ctrl_ud = Kd1 * m1_derr_spd;
    m1_ctrl_u = (int)(m1_ctrl_up + m1_ctrl_ud + m1_ctrl_ui);
    m2_ctrl_up = Kp2 * m2_err_spd;
    m2_ctrl_ui = Ki2 * m2_err_sum;
    m2_ctrl_ud = Kd2 * m2_derr_spd;
    m2_ctrl_u = (int)(m2_ctrl_up + m2_ctrl_ud + m2_ctrl_ui);

    if (m1_ctrl_u >= 0) {
      digitalWrite(M1_DIR1, LOW);
      digitalWrite(M1_DIR2, HIGH); //ccw
      if (m1_ctrl_u > 255) m1_ipwm_u = 255;
      else m1_ipwm_u = (int)m1_ctrl_u;
    }
    else {
      digitalWrite(M1_DIR1, HIGH);
      digitalWrite(M1_DIR2, LOW); //cw
      if (m1_ctrl_u < -255) m1_ipwm_u = 255;
      else m1_ipwm_u = (int)m1_ctrl_u * (-1);
    }
    if (m2_ctrl_u >= 0) {
      digitalWrite(M2_DIR1, LOW);
      digitalWrite(M2_DIR2, HIGH); //ccw
      if (m2_ctrl_u > 255) m2_ipwm_u = 255;
      else m2_ipwm_u = (int)m2_ctrl_u;
    }
    else {
      digitalWrite(M2_DIR1, HIGH);
      digitalWrite(M2_DIR2, LOW); //cw
      if (m2_ctrl_u < -255) m2_ipwm_u = 255;
      else m2_ipwm_u = (int)m2_ctrl_u * (-1);
    }
    analogWrite(M1_PWM, m1_ipwm_u);
    analogWrite(M2_PWM, m2_ipwm_u);
  }

}

void T5ISR() {//인터럽트 발생시 실행되는 함수
  t5_flag = 1;

  odometry();//인터럽트로 인코더값을 읽을때마다 좌표값을 계산
  e1cnt_k = e1cnt;//인코더값을 저장
  d_e1cnt = e1cnt_k - e1cnt_k_1; //delta_error
  e1cnt_k_1 = e1cnt_k;

  e2cnt_k = e2cnt;//인코더값을 저장
  d_e2cnt = e2cnt_k - e2cnt_k_1; //delta_error
  e2cnt_k_1 = e2cnt_k;
}

void Enc1chA_ISR() {
  if (digitalRead(ENC1_CHA) == HIGH) {
    if (digitalRead(ENC1_CHB) == LOW) e1cnt--;
    else e1cnt++;
  }
  else {
    if (digitalRead(ENC1_CHB) == HIGH) e1cnt--;
    else e1cnt++;
  }
}

void Enc1chB_ISR() {
  if (digitalRead(ENC1_CHB) == HIGH) {
    if (digitalRead(ENC1_CHA) == HIGH) e1cnt--;
    else e1cnt++;
  }
  else {
    if (digitalRead(ENC1_CHA) == LOW) e1cnt--;
    else e1cnt++;
  }
}

void Enc2chA_ISR() {
  if (digitalRead(ENC2_CHA) == HIGH) {
    if (digitalRead(ENC2_CHB) == LOW) e2cnt--;
    else e2cnt++;
  }
  else {
    if (digitalRead(ENC2_CHB) == HIGH) e2cnt--;
    else e2cnt++;
  }
}

void Enc2chB_ISR() {
  if (digitalRead(ENC2_CHB) == HIGH) {
    if (digitalRead(ENC2_CHA) == HIGH) e2cnt--;
    else e2cnt++;
  }
  else {
    if (digitalRead(ENC2_CHA) == LOW) e2cnt--;
    else e2cnt++;
  }
}

void sn_distance(){//소나센서 거리계산 및 값 저장함수
  unsigned long duration[5];
  for(int i =0; i<5; i++){
    digitalWrite(ECHO1+(2*i),LOW);//에코센서 핀 31,33,35,37,39
    delayMicroseconds(2);
    digitalWrite(TRIG1+(2*i), HIGH);//트리거핀 30,32,34,36,38
    delayMicroseconds(10);
    digitalWrite(TRIG1+(2*i), LOW);
    duration[i] = pulseIn(ECHO1+(2*i), HIGH, 4000);
    sn[i] = (double)340 * duration[i] / 20000;//배열로저장
    for(int i=0; i<5; i++){
      if(sn[i]==0){
        sn[i] = 15;//타임아웃을 주었기 때문에 너무 먼 거리는 0으로 저장되었으므로 그럴경우 15로 다시 저장
      }
    }
  }
}

void turn(int value, float turn_degree) {//속도(속도는 양수만 쳐넣으세용), 각도(거리계산을 이용하며 호의길이를 구해 각도결정) (양수:CCW,음수:CW)

  float TL = 0;
  float TR = 0;
  float torc = (3.1415926535897932384626433832795*wheelbase*turn_degree)/360;//지름이 로봇의 양쪽바퀴사이의 거리인 호의길이
  if(turn_degree<=0){//우회전
    float rotation_1 = e1cnt;
    float rotation_2 = e2cnt;
    
    while((abs(TL)+abs(TR))/2 <= abs(torc)){//왼쪽바퀴가 돈 거리와 오른쪽바퀴가 돈 거리의 평균 <= 호의길이
      float gap_1 = rotation_1;
      float gap_2 = rotation_2;
      Serial.print(e1cnt);
      Serial.println(e2cnt);
      gap_1 = e1cnt - rotation_1;//인터럽트를 이용해서 인코더값이 변하므로 인코더 값의 차를 계산하여 펄스값과 바퀴원주를 곱해주면 거리나옴
      gap_2 = e2cnt - rotation_2;
      go(value,-value);
      TR = circumference * (gap_1 / pulseCount);//오른쪽바퀴가 돈 거리
      TL = circumference * (gap_2 / pulseCount);//왼쪽바퀴가 돈거리
    }
    go(0,0);
  }
  else if(turn_degree>0){//좌회전
    float rotation_1 = e1cnt;
    float rotation_2 = e2cnt;
    
    while((abs(TL)+abs(TR))/2 <= abs(torc)){
      float gap_1 = rotation_1;
      float gap_2 = rotation_2;
      Serial.print(e1cnt);
      Serial.println(e2cnt);
      gap_1 = e1cnt - rotation_1;
      gap_2 = e2cnt - rotation_2;
      go(-value,value);
      TR = circumference * (gap_1 / pulseCount);
      TL = circumference * (gap_2 / pulseCount);
    }
    go(0,0);
  }
  //정목이가 '유일'하게 만든 걸작
}


void getRawData_noDelay(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c){
  *c = tcs.read16(TCS34725_CDATAL);
  *r = tcs.read16(TCS34725_RDATAL);
  *g = tcs.read16(TCS34725_GDATAL);
  *b = tcs.read16(TCS34725_BDATAL);
}

void red_on(){//빨간색LED켜기
  analogWrite(RGB_R ,255);
  analogWrite(RGB_G ,0);
  analogWrite(RGB_B ,0);
  preMillis = millis();
  while(millis() - preMillis <= 2000){
    go(0,0);
    }
  RGB_OFF();
  }

void green_on(){//초록색LED켜기
  analogWrite(RGB_R ,0);
  analogWrite(RGB_G ,255);
  analogWrite(RGB_B ,0);
  preMillis = millis();
  while(millis() - preMillis <= 2000){
    go(0,0);
    }
  RGB_OFF();
  }

void blue_on(){//파란색LED켜기
  analogWrite(RGB_R ,0);
  analogWrite(RGB_G ,0);
  analogWrite(RGB_B ,255);
  preMillis = millis();
  while(millis() - preMillis <= 2000){
    go(0,0);
    }
  RGB_OFF();
  }
  
void RGB_OFF(){//불좀꺼줄래?
  analogWrite(RGB_R ,0);
  analogWrite(RGB_G ,0);
  analogWrite(RGB_B ,0);
    }

void serialEvent2(){//serial event를 발생시켜 블루투스로 값을 받아올때마다 그 값을 저장
 if(Serial2.available()) {
  u2_rcv_flag = true;
  u2_rcv_data=Serial2.read();
 }
}

void odometry(){

  SL = circumference * (e2cnt / pulseCount); // 왼쪽모터가 움직인 거리
  SR = circumference * (-e1cnt / pulseCount); // 오른쪽모터가 움직인 거리

  SL_k = SL; 
  SR_k = SR;

  deltaSL = SL_k - SL_k_1; //왼쪽모터가 움직인 거리변화량
  deltaSR = SR_k - SR_k_1; //오른쪽모터가 움직인 거리변화량

  SL_k_1 = SL_k;
  SR_k_1 = SR_k;

  deltaS = (deltaSL+deltaSR)/2; //로봇 중심이 움직인 거리 변화량

  
  deltaSeta =(deltaSL-deltaSR)/wheelbase; // 각도 변화량

  x = x + deltaS * cos(Seta+deltaSeta/2); // x 좌표 계산 
  y = y + deltaS * sin(Seta+deltaSeta/2); // y 좌표 계산 

  Seta += deltaSeta;

  // 출발각도 만큼 돌아간 축의 좌표를 이용해 절대 좌표로 얻어옴.
  // 회전행렬을 곱해서 축 변환
  final_x = cos(i_radian) * x - sin(i_radian) * y;
  final_y = sin(i_radian) * x + cos(i_radian) * y;

  // 좌표 변화량 계산.
  final_x_k = final_x;
  final_y_k = final_y;
 
  deltaX = (final_x_k - final_x_k_1) * 10000 ;  // 증감을 확실히 알기위해 
  deltaY = (final_y_k - final_y_k_1) * 10000 ;  // 10000을 곱해서 증폭시켜줌.

  final_x_k_1 = final_x_k ;
  final_y_k_1 = final_y_k ;

   last_Seta = atan(deltaY/deltaX)*180/3.1415926535897932384626433832795; //로봇의 현재 주행 각도 계산
}



void lightcheck(){//흰색LED켜기
  analogWrite(RGB_R ,255);
  analogWrite(RGB_G ,200);
  analogWrite(RGB_B ,200);
}



void TS_a() //한번 텍트스위치a를 누르면 숫자 1올라가고 0.3초동안 led에 불이 들어옴
{
  if (!data_a)
  {
     if (digitalRead(Tact_a) != data_a)
    {
      lightcheck();
      delay(300);
      RGB_OFF();
      num_a++;
    }
  } 
  data_a = digitalRead(Tact_a);
  a = num_a;
}



void TS_b() //한번 텍트스위치b를 누르면 숫자 1올라가고 0.3초동안 led에 불이 들어옴
{
  if (!data_b)
  {
     if (digitalRead(Tact_b) != data_b)
    {
      lightcheck();
      delay(300);
      RGB_OFF();
      num_b++;
    }
  } 
  data_b = digitalRead(Tact_b);
}

void TS_c() //텍트스위치b를 누르면 숫자가 1씩 올라가고 num_에 저장함
{
  if (!data_b)
  {
     if (digitalRead(Tact_b) != data_b)
    {
      num_b++;
    }
  } 
  data_b = digitalRead(Tact_b);
}
