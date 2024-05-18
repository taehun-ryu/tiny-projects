#include <Wire.h>                     // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>        // LCD 2004 I2C용 라이브러리
#include "RTClib.h"//real time clock모듈을 사용하기위한 헤더파일(zip_)
#include <DHT11.h>//(온습도센서 헤더파일)


//tact switch
#define tact1 30
#define tact2 31
#define tact3 32
#define tact4 33

//humidity
#define DHTPIN1 11
#define DHTPIN2 12
#define DHTPIN3 13

//LED
#define led1 45
#define led2 46
#define led3 47

//toyang humidity sensor
#define toyang1 A3
#define toyang2 A4
#define toyang3 A5

//수위센서
#define sen0204 7

//모터
#define motor1 2
#define motor2 3
#define motor3 4

//초기값
#define humi_ini 50
#define temp_ini 20
#define term_ini 5

//온습도센서 클래스지정
DHT11 dht1(DHTPIN1);
DHT11 dht2(DHTPIN2);
DHT11 dht3(DHTPIN3);

//리얼타임시계모듈 클래스지정
RTC_DS3231 RTC;

//LCDI2C클래스지정 및 크기조정
LiquidCrystal_I2C lcd(0x27, 20, 4);   //  0x3F or 0x27를 선택하여 주세요. 작동이 되지 않는 경우 0x27로 바꾸어주세요. 확인결과 0x3f가 작동하지 않을 수 있습니다.

//시간 클래스지정
DateTime now_time = RTC.now();

//시간변수
int preday[3] = {now_time.day(), now_time.day(), now_time.day()};
int prehour = now_time.hour();
int nowhour;
int daycount[3] = {0, 0, 0};

//토양습도센서 변수
int toyang[3] = {1023, 1023, 1023};

//릴레이 변수
int motor = 10; //모터 릴레이 핀
///////////////////////////////////tact////////////////////////////
int tact1_num = 0;
int tact2_num = 0;
int tact3_num = 0;
int tact4_num = 0;

int tactswitch1 = 0; // 필요없을지도 복붙하면서 넣은거라
int tactswitch2 = 0;
int tactswitch3 = 0;
int tactswitch4 = 0;

bool data_tact1 = true;
bool data_tact2 = true;
bool data_tact3 = true;
bool data_tact4 = true;

int tact1_dp = 0; //tact스위치 값 tact_1();함수 돌리기이전 tactswitch1값으로 저장후 값이 바뀌면 눌린거임
int tact2_dp = 0;
int tact3_dp = 0;
int tact4_dp = 0;
/////////////////////////////////////////////////////////////////////

//습도,온도시간 저장 배열(read:현재 읽어온값, save:5,6,7은 커스텀이므로 본체에서 설정가능하고 0,1,2,3,4는 미리저장한 설정값, load:1,2,3번 모듈에 설정이후 저장되어 불러올 값)
float humi_read[3] = {}; //습도 읽는값
float temp_read[3] = {}; //온도 읽는값
float humi_save_low[8] = {30, 30, 30, 30, 30,}; //습도 저장된값(최소)
float temp_save_low[8] = {18, 17, 15, 20, 18,}; //온도 저장된값(최소)
float humi_save_high[8] = {80, 80, 80, 80, 80,}; //습도 저장된값(최대)
float temp_save_high[8] = {25, 25, 22, 25, 27,}; //온도 저장된값(최대)
int term_save[8] = {30, 28, 3, 3, 7,}; //주기 저장된값
float humi_load_low[3] = {0, 0, 0}; //습도 로드한 값(최소)
float temp_load_low[3] = {0, 0, 0}; //온도 로드한 값(최소)
float humi_load_high[3] = {0, 0, 0}; //습도 로드한 값(최대)
float temp_load_high[3] = {0, 0, 0}; //온도 로드한 값(최대)
int term_load[3] = {0, 0, 0}; //주기 로드한 값
/////////////////////////////////////////////////////////////////////
unsigned long preMillis = millis();

//모드 변수(이해하기 어려움!)
int mode[3] = {1, 1, 1}; //3개의 모듈의 각각 모드
int mode_2[3] = {1, 1, 1}; //3개의 모듈의 각각 세팅에서 저장된 식물들
int mode_2_1[3] = {1, 1, 1};
int count = 0; //세팅 값을 저장할때 물어보는 창에서 "yes" , "no" 위치를 세는 연산자
int i = 1; //모듈의 번호(초기 상태에서 위아래버튼을 누르면 i가 증가 또는 감소하여 지정하는 모듈의 번호가 바뀐다.)

//수위센서 값(디지털)
int sen0204_value = 1;

//설정에서 설정한 경우 플래그증가
int settingflag[3] = {0, 0, 0};

void setup() {
  Serial.begin(115200);
  Wire.begin();
  RTC.begin();
  //RTC.adjust(DateTime(__DATE__,__TIME__)); //최초 업로드하고 주석처리할것!!
  lcd.init();
  lcd.backlight();
  lcd.leftToRight();
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(toyang1, INPUT);
  pinMode(toyang2, INPUT);
  pinMode(toyang3, INPUT);
  pinMode(DHTPIN1, INPUT);
  pinMode(DHTPIN2, INPUT);
  pinMode(DHTPIN3, INPUT);
  /////////////////////////////////////////////////////////////////////////////
  DateTime now_time = RTC.now();
  //////////////////////////////////////////////////////////////////////////////
  pinMode(tact1, INPUT_PULLUP);
  pinMode(tact2, INPUT_PULLUP);
  pinMode(tact3, INPUT_PULLUP);
  pinMode(tact4, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(sen0204, INPUT);
}


void loop() {

  /*
    toyang[0] = analogRead(toyang1);
    Serial.println(toyang[0]);
    preMillis = millis();
    if (toyang[0] > 600) {
      Serial.println("물 더줘!");
      while (millis() - preMillis <= 2000) {}
    }
    else {
      Serial.println("그만!");
      while (millis() - preMillis <= 2000) {}
    }
  */
  nowhour = now_time.hour();//한시간마다 물이 부족한지 확인
  if (nowhour != prehour) {
    water_check();
  }

  for (int j = 0; j < 3; j++) {
    if (preday[j] != now_time.day()) { //날짜세주기(물주는 주기때문에)

      daycount[j]++;
      preday[j] = now_time.day();//예를 들어 30일 이후 1일이 되면  단순 날짜차이로 계산하면 오류가 생기므로 daycount라는 변수를 선언하여 증가시키면서 날짜의 흐름을 파악
    }
  }



  if (mode[i - 1] == 1) {//여기서 i는 모듈 번호를 의미함
    mode1(i - 1);
  }
  else if (mode[i - 1] == 2) {
    mode2(i - 1);
  }
  else if (mode[i - 1] == 3) {
    mode3(i - 1);
  }
  for (int j = 0; j < 3; j++) {
    if (settingflag[j] == 1 && daycount[j] == term_load[j] && term_load[j] != 0) {//한번이라도 설정하지 않았거나 설장한 주기가 0이라면 물을 주지않음!! 날짜의흐름이 주기와 같으면 물을 줌
      water_pump(j);//펌프(모터)를 작동시킴(j번째 모터)
      daycount[j] = 0;//물을주고 시간흐름 초기화
    }
    if ((humi_read[j] < humi_load_low[j]) || (humi_read[j] > humi_load_high[j]) || (temp_read[j] < temp_load_low[j]) || (temp_read[j] > temp_load_high[j])) {
      digitalWrite(led1 + j, HIGH);//온습도 범위에서 벗어나면 LED등 켜기
    }
    else if ((humi_read[j] >= humi_load_low[j]) && (humi_read[j] <= humi_load_high[j]) && (temp_read[j] >= temp_load_low[j]) && (temp_read[j] <= temp_load_high[j])) {
      digitalWrite(led1 + j, LOW);//온습도 범위 안 일경우 LED끄기
    }
  }

  /*
    tact_1();
    tact_2();
    tact_3();
    tact_4();
    Serial.print("tact1: ");
    Serial.print(tactswitch1);
    Serial.print(" / ");
    Serial.print("tact2: ");
    Serial.print(tactswitch2);
    Serial.print(" / ");
    Serial.print("tact3: ");
    Serial.print(tactswitch3);
    Serial.print(" / ");
    Serial.print("tact4: ");
    Serial.print(tactswitch4);
    Serial.println(" / ");*/
}
