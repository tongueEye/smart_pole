// 아두이노 1 : 전송 받은 flag를 판단하여 신호 조정

// 신호등 1
int LED_RED_1 = 11;
int LED_YELLOW_1 = 12;
int LED_GREEN_1 = 13;

// 신호등 2
int LED_RED_2 = 6;
int LED_YELLOW_2 = 7;
int LED_LEFT_2 = 8;
int LED_GREEN_2 = 9;

// 신호등 3
int LED_RED_3 = 2;
int LED_YELLOW_3 = 3;
int LED_LEFT_3 = 4;

void setup(){
  Serial.begin(9600);
  
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_YELLOW_1, OUTPUT);
  pinMode(LED_GREEN_1, OUTPUT); 
  
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_YELLOW_2, OUTPUT);
  pinMode(LED_LEFT_2, OUTPUT);
  pinMode(LED_GREEN_2, OUTPUT); 
  
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_YELLOW_3, OUTPUT);
  pinMode(LED_LEFT_3, OUTPUT); 
}

void code_0() // (G,G,R)
{
  digitalWrite(LED_RED_1, LOW);
  digitalWrite(LED_YELLOW_1, LOW);
  digitalWrite(LED_GREEN_1, HIGH);
  
  digitalWrite(LED_RED_2, LOW);
  digitalWrite(LED_YELLOW_2, LOW);
  digitalWrite(LED_LEFT_2, LOW);
  digitalWrite(LED_GREEN_2, HIGH);
  
  digitalWrite(LED_RED_3, HIGH);
  digitalWrite(LED_YELLOW_3, LOW);
  digitalWrite(LED_LEFT_3, LOW);
}

void code_1() // (R,LG,R)
{
  digitalWrite(LED_RED_1, HIGH);
  digitalWrite(LED_YELLOW_1, LOW);
  digitalWrite(LED_GREEN_1, LOW);
  
  digitalWrite(LED_RED_2, LOW);
  digitalWrite(LED_YELLOW_2, LOW);
  digitalWrite(LED_LEFT_2, HIGH);
  digitalWrite(LED_GREEN_2, HIGH);
  
  digitalWrite(LED_RED_3, HIGH);
  digitalWrite(LED_YELLOW_3, LOW);
  digitalWrite(LED_LEFT_3, LOW);
}

void code_2() // (R,R,L)
{
  digitalWrite(LED_RED_1, HIGH);
  digitalWrite(LED_YELLOW_1, LOW);
  digitalWrite(LED_GREEN_1, LOW);
  
  digitalWrite(LED_RED_2, HIGH);
  digitalWrite(LED_YELLOW_2, LOW);
  digitalWrite(LED_LEFT_2, LOW);
  digitalWrite(LED_GREEN_2, LOW);
  
  digitalWrite(LED_RED_3, LOW);
  digitalWrite(LED_YELLOW_3, LOW);
  digitalWrite(LED_LEFT_3, HIGH);
}

void code_3() // (R,LG,R) -> (R,R,L)
{
  code_1();
  delay(500);
  code_2();
  delay(500);
}

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
    
    Serial.print("code : ");
    Serial.println(c);
  }  
}