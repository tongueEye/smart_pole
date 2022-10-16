//가로등 기능 변수
int cds = A0; //A0핀-조도센서
int led = 6; //~6핀-LED

//비상벨 변수
int buzzer=13;
int button=11;
int btnState=0;
int numTones = 7;
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};

void setup() {

  //가로등
  pinMode(led,OUTPUT); //9번포트-LED(출력)

  //비상벨
  pinMode(buzzer,OUTPUT);
  pinMode(button,INPUT);

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

  //exit(0);
}