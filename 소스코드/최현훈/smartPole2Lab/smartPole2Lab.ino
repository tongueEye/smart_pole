//온습도센서 라이브러리
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN A1

// LCD 라이브러리
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
// 0x27 I2C 주소를 가지고 있는 16x2 LCD객체를 생성합니다.(I2C 주소는 LCD에 맞게 수정)
LiquidCrystal_I2C lcd(0x27, 16, 2);
//특수문자 라이브러리
#include <LiquidCrystal.h>

//먼지량 측정 변수
unsigned long pulse=0;
float ugm3=0;

//가로등 기능 변수
int cds = A0; //A0핀-조도센서
int led = 9; //~9핀-LED

//비상벨 변수
int buzzer=12;
int button=10;
int btnState=0;
int numTones = 7;
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};

//먼지량 측정 함수
float pulse2ugm3(unsigned long pulse){
  float value=(pulse-1400)/14.0;
  if(value>300){ //값이 300보다 크면(이상값의 경우)
    value=0; //값을 0으로 설정(예외처리)
  }
  return value; //측정 먼지량 반환
}

//온도계기호
byte SpecialChar1[8] = {
        B01110,
        B01010,
        B01010,
        B01110,
        B01110,
        B11111,
        B11111,
        B01110
};

//섭씨문자
byte SpecialChar2[8] = {
        B10000,
        B00110,
        B01001,
        B01000,
        B01000,
        B01001,
        B00110,
        B00000
};

//습도기호
byte SpecialChar3[8] = {
        B00100,
        B00100,
        B01110,
        B01110,
        B11111,
        B11111,
        B11111,
        B01110
};


//먼지단위기호
byte SpecialChar4[8]={
  		B00000,
        B00000,
        B00000,
        B00101,
        B00101,
        B00111,
        B00100,
  		B00000
};
byte SpecialChar5[8]={ 
        B00000,
        B00000,
        B00000,
        B11100,
        B10100,
        B11100,
        B00100,
        B11100
};
byte SpecialChar6[8]={
   		B00000,
        B00000,
        B00000,
        B00010,
        B00100,
        B01000,
        B10000,
        B00000
};
byte SpecialChar7[8]={
  		B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B10101,
        B10101,
  		B00000
};
byte SpecialChar8[8]={
        B11000,
        B01000,
        B11000,
        B01000,
        B11000,
        B00000,
        B00000,
        B00000
};


void setup() {
  //먼지측정
  pinMode(8,INPUT); //8번포트-먼지센서(입력)
  Serial.begin(9600);

  //가로등
  pinMode(9,OUTPUT); //9번포트-LED(출력)

  //비상벨
  pinMode(buzzer,OUTPUT);
  pinMode(button,INPUT);

  //lcd 출력
  lcd.init(); // I2C LCD를 초기화
  lcd.backlight(); // I2C LCD의 백라이트를 켜줌
  
  //특수문자 저장
  lcd.createChar(1,SpecialChar1);
  lcd.createChar(2,SpecialChar2);
  lcd.createChar(3,SpecialChar3);
  
  lcd.createChar(4,SpecialChar4);
  lcd.createChar(5,SpecialChar5);
  lcd.createChar(6,SpecialChar6);
  lcd.createChar(7,SpecialChar7);
  lcd.createChar(8,SpecialChar8);
  
  lcd.begin(16,2);
}

void loop() {
  //비상벨 기능
  btnState=digitalRead(button);
  if(btnState==1){
    //digitalWrite(buzzer,HIGH);
    tone(buzzer, tones[numTones]);
  }
  else{
    //digitalWrite(buzzer,LOW);
    noTone(buzzer);
  }
  delay(10);
  
  DHT.read(DHT11_PIN); //A1번 포트-온습도센서
  
  //온습도 측정
  Serial.print("hum: ");
  Serial.print(DHT.humidity);
  Serial.println("%");
  Serial.print("tmp: ");
  Serial.print(DHT.temperature);
  Serial.println("*C");
  delay(1000);

  //먼지량 측정
  pulse=pulseIn(8,LOW,20000);
  ugm3=pulse2ugm3(pulse);
  Serial.print("dust: ");
  Serial.print(ugm3,2);
  Serial.println(" ug/m3");
  delay(100);

  // 조도센서로 부터 밝기 값 측정
	// 조도센서로 부터 입력되어지는 전압의 크기 (0~5V)에 따라 0~1023 범위의 값으로 변환되어 반환
	int cdsValue = analogRead(cds);
	Serial.print("cds =  ");
	Serial.println(cdsValue);

  //가로등 기능
  if (cdsValue < 450) { //밝기 값이 해당 수치보다 작으면
		digitalWrite(led, HIGH); //LED를 키고
	}
	else { //밝기 값이 해당 수치보다 크면
		digitalWrite(led, LOW); //LED를 끈다
	}
	delay(200);

  //LCD 출력
  lcd.setCursor(0,0);// 0번째 줄 0번째 셀부터 입력하게 합니다.
  lcd.write(byte(1));
  lcd.print(": ");
  lcd.print(DHT.temperature);
  lcd.setCursor(6,0);
  lcd.write(byte(2));
  
  lcd.setCursor(9,0);
  lcd.write(byte(3));
  lcd.print(": ");
  lcd.print(DHT.humidity);
  lcd.print(" %");
  
  lcd.setCursor(2,1);
  lcd.print("dust");
  lcd.print(": ");
  lcd.print(ugm3,2);
  
  lcd.setCursor(10,1);
  lcd.write(byte(4));
  lcd.setCursor(11,1);
  lcd.write(byte(5));
  lcd.setCursor(12,1);
  lcd.write(byte(6));
  
  lcd.setCursor(13,1);
  lcd.write(byte(7));
  lcd.setCursor(14,1);
  lcd.write(byte(8));

  //exit(0);
}