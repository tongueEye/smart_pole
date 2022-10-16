#include "HX711.h"
 
//캘리브레이션값
#define calibration_factor -18550.0
 
//SCK(CLK)로 사용하는 핀1
#define LOADCELL_SCK_PIN1 2
//DT(DOUT)로 사용하는 핀1
#define LOADCELL_DOUT_PIN1 3

//SCK(CLK)로 사용하는 핀2
#define LOADCELL_SCK_PIN2 5
//DT(DOUT)로 사용하는 핀2
#define LOADCELL_DOUT_PIN2 6
 
//SCK(CLK)로 사용하는 핀3
#define LOADCELL_SCK_PIN3 8
//DT(DOUT)로 사용하는 핀3
#define LOADCELL_DOUT_PIN3 9

//SCK(CLK)로 사용하는 핀4
#define LOADCELL_SCK_PIN4 11
//DT(DOUT)로 사용하는 핀4
#define LOADCELL_DOUT_PIN4 12

HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;

//최신값을 몇개 저장해 두는지 개수.
int nValueCount = 10;
//최신값을 저장해 두는 배열. 위의 변수 값과 같은 크기를 설정한다.
float fValue1[10];
float fValue2[10];
float fValue3[10];
float fValue4[10];
 
 
void setup() 
{
  Serial.begin(9600);
 
  //HX711 객체를 초기화 한다.
  scale1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
  scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
  scale3.begin(LOADCELL_DOUT_PIN3, LOADCELL_SCK_PIN3);
  scale4.begin(LOADCELL_DOUT_PIN4, LOADCELL_SCK_PIN4);
  //설정된 캘리브레이션 값을 설정 한다.
  scale1.set_scale(calibration_factor);
  scale2.set_scale(calibration_factor);
  scale3.set_scale(calibration_factor);
  scale4.set_scale(calibration_factor);
  //영점 잡기. 현재 값을 0으로 둔다.
  scale1.tare();
  scale2.tare();
  scale3.tare();
  scale4.tare();
}
 
void loop() 
{
  Serial.print("Weight1: ");
 
  //값 임시 저장
  float fValueTemp1 = 0.0;
  //값 합산
  float fValueSum1 = 0.0;
 
  
  //scale.get_units() returns a float
  fValueTemp1 = scale1.get_units();
  //읽은 값을 합산값에 넣어 준다.
  fValueSum1 = fValueTemp1;
  
  int i;
  for(i = 0; i < nValueCount; i = i + 1)
  {
    if(i > 0)
    {//0보다 클때만 계산
      //앞번호일수록 오래된 데이터이다.
      
      //기존에 저장된 데이터 합산
      fValueSum1 = fValueSum1 + fValue1[i];
 
      //값을 앞으로 한칸씩 민다.
      fValue1[i - 1] = fValue1[i];
    }
  }
 
  //맨 마지막에 최신값을 넣어 준다.
  fValue1[nValueCount - 1] = fValueTemp1;
 
  //합산값을 평균을 낸다.
  Serial.print(abs(fValueSum1 / nValueCount), 1);
  
  //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.print(" kg");
  Serial.println();


  Serial.print("Weight2: ");
 
  //값 임시 저장
  float fValueTemp2 = 0.0;
  //값 합산
  float fValueSum2 = 0.0;
 
  
  //scale.get_units() returns a float
  fValueTemp2 = scale2.get_units();
  //읽은 값을 합산값에 넣어 준다.
  fValueSum2 = fValueTemp2;
  
  int j;
  for(j = 0; j < nValueCount; j = j + 1)
  {
    if(j > 0)
    {//0보다 클때만 계산
      //앞번호일수록 오래된 데이터이다.
      
      //기존에 저장된 데이터 합산
      fValueSum2 = fValueSum2 + fValue2[j];
 
      //값을 앞으로 한칸씩 민다.
      fValue2[j - 1] = fValue2[j];
    }
  }
 
  //맨 마지막에 최신값을 넣어 준다.
  fValue2[nValueCount - 1] = fValueTemp2;
 
  //합산값을 평균을 낸다.
  Serial.print(abs(fValueSum2 / nValueCount), 1);
  
  //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.print(" kg");
  Serial.println();


  Serial.print("Weight3: ");
 
  //값 임시 저장
  float fValueTemp3 = 0.0;
  //값 합산
  float fValueSum3 = 0.0;
 
  
  //scale.get_units() returns a float
  fValueTemp3 = scale3.get_units();
  //읽은 값을 합산값에 넣어 준다.
  fValueSum3 = fValueTemp3;
  
  int k;
  for(k = 0; k < nValueCount; k = k + 1)
  {
    if(k > 0)
    {//0보다 클때만 계산
      //앞번호일수록 오래된 데이터이다.
      
      //기존에 저장된 데이터 합산
      fValueSum3 = fValueSum3 + fValue3[k];
 
      //값을 앞으로 한칸씩 민다.
      fValue3[k - 1] = fValue3[k];
    }
  }
 
  //맨 마지막에 최신값을 넣어 준다.
  fValue3[nValueCount - 1] = fValueTemp3;
 
  //합산값을 평균을 낸다.
  Serial.print(abs(fValueSum3 / nValueCount), 1);
  
  //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.print(" kg");
  Serial.println();

  Serial.print("Weight4: ");
 
  //값 임시 저장
  float fValueTemp4 = 0.0;
  //값 합산
  float fValueSum4 = 0.0;
 
  
  //scale.get_units() returns a float
  fValueTemp4 = scale4.get_units();
  //읽은 값을 합산값에 넣어 준다.
  fValueSum4 = fValueTemp4;
  
  int l;
  for(l = 0; l < nValueCount; l = l + 1)
  {
    if(l > 0)
    {//0보다 클때만 계산
      //앞번호일수록 오래된 데이터이다.
      
      //기존에 저장된 데이터 합산
      fValueSum4 = fValueSum4 + fValue4[l];
 
      //값을 앞으로 한칸씩 민다.
      fValue4[l - 1] = fValue4[l];
    }
  }
 
  //맨 마지막에 최신값을 넣어 준다.
  fValue4[nValueCount - 1] = fValueTemp4;
 
  //합산값을 평균을 낸다.
  Serial.print(abs(fValueSum4 / nValueCount), 1);
  
  //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.print(" kg");
  Serial.println();  

  //delay(500); //(느리게 보기-테스트용)
}
