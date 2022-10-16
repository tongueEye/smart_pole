#include "HX711.h"
 
//캘리브레이션값
#define calibration_factor -18550.0
 
//DT(DOUT)로 사용하는 핀1
#define LOADCELL_DOUT_PIN1 2
//SCK(CLK)로 사용하는 핀1
#define LOADCELL_SCK_PIN1 3

//DT(DOUT)로 사용하는 핀2
#define LOADCELL_DOUT_PIN2 5
//SCK(CLK)로 사용하는 핀2
#define LOADCELL_SCK_PIN2 6
 
HX711 scale1;
HX711 scale2;

//최신값을 몇개 저장해 두는지 개수.
int nValueCount = 10;
//최신값을 저장해 두는 배열. 위의 변수 값과 같은 크기를 설정한다.
float fValue1[10];
float fValue2[10];
 
 
void setup() 
{
  Serial.begin(9600);
 
  //HX711 객체를 초기화 한다.
  scale1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
  scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
  //설정된 캘리브레이션 값을 설정 한다.
  scale1.set_scale(calibration_factor);
  scale2.set_scale(calibration_factor);
  //영점 잡기. 현재 값을 0으로 둔다.
  scale1.tare();
  scale2.tare();
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

}