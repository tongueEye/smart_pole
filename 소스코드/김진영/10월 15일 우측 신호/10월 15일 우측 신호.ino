// 아두이노 1 : 전송 받은 code를 판단하여 신호 조정

// 신호등 1
const byte traffic1[3] = {11,12,13}; // R, Y, L 순서

// 신호등 2
const byte traffic2[4] = {6,7,8,9}; // R, Y, L, G 순서

// 신호등 3
const byte traffic3[3] = {2,3,4}; // R, Y, G 순서
/*
Green = 5sec
Yellow = 1sec
Left = 3sec
*/
const byte T1[6] = {11, 11, 11, 12, 13, 12}; // R R R Y L Y
const byte T2[6] = {9, 7, 8, 7, 6, 6}; // G Y L Y R R
const byte T3[6] = {4, 3, 2, 2, 2, 2}; // G Y R R R R

int LightTime[6] = {5, 1, 3, 1, 3, 1}; // R 시간은 G,L,Y 시간에 종속


unsigned long timeVal = 0; // 이전 시간
int indexVal = 0; // 신호등 위치

// 좌 -> 우 직진 신호 연장
void code_1() {
  // TotalLT[9] = 3;
  
  LightTime[0] = LightTime[0] + 2;
}

// 우 -> 좌 직진 신호 연장
void code_2() {
  
  LightTime[0] = LightTime[0] + 2;
}
// 전체 직진 신호 연장
void code_3() {
  
  LightTime[0] = LightTime[0] + 4;
}

// 기존 신호 유지 (겸 신호 시간 초기화) 
void code_0() {
  
  LightTime[0] = 5;
}



void setup(){
  Serial.begin(9600);
  
  for(int i=0; i<3; i++){
    pinMode(traffic1[i], OUTPUT);
    pinMode(traffic2[i], OUTPUT);
    pinMode(traffic3[i], OUTPUT);
  }
  
  // 부팅 시 신호등 적색 점등
  digitalWrite(T1[0], HIGH);
  digitalWrite(T2[0], HIGH);
  digitalWrite(T3[0], HIGH);
}

void loop()
{  
  if(millis()-timeVal>=LightTime[indexVal]*1000){ //신호등 동작 trafficLight[3]순서대로
    digitalWrite(T1[indexVal], LOW);
    digitalWrite(T2[indexVal], LOW);
    digitalWrite(T3[indexVal], LOW); //이전등 끄기
    indexVal++; //신호등위치 증가
    if(indexVal==6)indexVal=0; // 신호등위치가 3이 되면 다시 0으로 처음위치로 돌아감
    digitalWrite(T1[indexVal], HIGH);
    digitalWrite(T2[indexVal], HIGH);
    digitalWrite(T3[indexVal], HIGH);//새로운등 켜기
    /*
    Serial.print("Traffic : (");
    Serial.print(T1[indexVal]);
    Serial.print(", ");
    Serial.print(T2[indexVal]);
    Serial.print(", ");
    Serial.print(T3[indexVal]);
    Serial.println(")");
    */
    timeVal=millis();
  }
  
  if(Serial.available()){
   char c = (char)Serial.read();
    if(c == '1') {
      code_1();
    } 
    else if (c == '2') {
      code_2();
    }
    else if (c == '3') {
   	  code_3();
    }
    else {code_0();
    }
    
    Serial.print("loop1 / code : ");
    Serial.println(c);
  } 
}


/*
void loop(){
  if(Serial.available()){
   char c = (char)Serial.read();
    if(c == '1') {
      code_1();
    } 
    else if (c == '2') {
      code_2();
    }
    else if (c == '3') {
   	  code_3();
    }
    else {code_0();}
    
    Serial.print("loop1 / code : ");
    Serial.println(c);
  }  
  unsigned long Time = millis();
  Serial.print("Time : ");
  Serial.println(Time);
}
*/