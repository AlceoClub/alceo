#define ADDRESS             0x6A
#define ADDRESS1            0x69       
#define AMBIANT             0x01                                
#define endCom()        (Serial.end())          
#define switchCom(DirPin,Mode) (digitalWrite(DirPin,Mode))  
#define pin 2
#define Tx_MODE 1
#define Rx_MODE 0
#include <SoftwareSerial.h>

#define suhu 55
#define suhuSemprot 90
#define cepatGeser 50
#define cepatGeserKipas 80
#define cepatScan 50    //30
#define cepatScanKipas 50
#define cepatScanApi 100
#define batasKompasPosisi 160
#define batasDepanFurniture 450

#define delayMendekatiApi 500
#define delayGeserSedikitApi 2
//#define delayGeserSedikitApi2 200
#define delaySerongApi 30
#define delaySerongApiFurn 100
#define delayMajuLagi 35
#define delayMenjauhFurniture 250
#define delayPivotPosisikan 5

#define pivotKiriApi passData(9);
#define pivotKananApi passData(8);
#define selisih 70

#define serongKiri1 passData(9);//passData(9);
#define serongKanan1 passData(8);//passData(8);
#define serongKiri2 passData(9);//passData(11);
#define serongKanan2 passData(8);//passData(10);
#define serongKiri4 passData(9);//passData(15);
#define serongKanan4 passData(8);//passData(14);

#define batasTembokPointing 350
#define batasDepanApi 400

#define jumScan 1

SoftwareSerial portOne(19,18);
void resetGaris();
void scanKananKiri();
void cekApi();
////////////////////////////////////////////////////////////////////SETUP SCAN///////////////////////////////////
int temperature[] = {0,0,0,0,0,0,0,0};
int temperature1[] = {0,0,0,0,0,0,0,0};
int counter;
int i=0;
int flagGerak=0;
int flagSens=0;
int flagGeser=0;
int flagDapat=0;
int flagChange=0;
int flagPointing=0;
int flagTembok=0; //0=scan biasa 1=ada tembok yang jauh karena furniture
int flagPivot=0;  //0=pivotKiri  1=pivotKanan
int count=0;
int countMendekati=0;
int countSerong=0;
int sudutApi=0;
int sudutAwal=0;
int countScan=0;
int batasBawah=0;
int batasAtas=0;
int motionNext=0;
int gakDapat=0;
int keluarFlame=0;

int countArrayTPA=0;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////PID///////////////////////////////////////
int sensor[9]={0,0,0,0,0,0,0,0,0};
int batasSensor[9]={520,520,520,520,520,520,520,520,520};
double P=0,I=0,D=0,PID_Value=0,previous_error=0;
float posisi,lastPosisi;
int countErrorPosisi;
float kp=3,ki=0,kd=0.1;
int pid;
int flagFlame=0;
float nilai_error=0;
float index[9]={-4,-3,-2,-1,0,1,2,3,4};
int count_error=0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
byte getData(byte reg){                                  
  Wire.beginTransmission(ADDRESS);                        
  Wire.write(reg);                                      
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS, 1);                          
  while(Wire.available() < 1);                            
  byte data = Wire.read();                                
  return(data);                                           
}

byte getData1(byte reg){                                   
  Wire.beginTransmission(ADDRESS1);                        
  Wire.write(reg);                                      
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS1, 1);                          
  while(Wire.available() < 1);                            
  byte data = Wire.read();                                
  return(data);                                           
}
//////////////////////////////////////////////////////////////////////////////////////Setup Servo MX////////////////////////////
unsigned char all[100],checksum;
int inn=0;
int ss=2048;
int speeds;

void sync(int angle)
{
  all[6]=angle&0xFF;
  all[7]=angle>>8;
  all[8]=speeds&0xFF;
  all[9]=speeds>>8;
  checksum=0;
  for(int a=2;a<10;a++)
  {
    checksum += all[a];
  }
  all[10]=~checksum;

  switchCom(pin,Tx_MODE);
  portOne.write(all,11);
  delayMicroseconds(100);
  switchCom(pin,Rx_MODE);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float error()
{
    gakDapat=0;
 
//    if(sensor[0]==1 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return -8;
//    else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return -7;
//    else if(sensor[0]==0 && sensor[1]==1 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return -6;
//    else if(sensor[0]==0 && sensor[1]==1 && sensor[2]==1 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return -5;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==1 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return -4;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==1 && sensor[3]==1 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return -3;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==1 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return -2;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==1 && sensor[4]==1 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return -1;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==1 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return 0;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return 0;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==1 && sensor[5]==1 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return 1;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==1 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)return 2;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==1 && sensor[6]==1 && sensor[7]==0 && sensor[8]==0)return 3;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==1 && sensor[7]==0 && sensor[8]==0)return 4;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==1 && sensor[7]==1 && sensor[8]==0)return 5;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==1 && sensor[8]==0)return 6;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==1 && sensor[8]==1)return 7;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0 && sensor[8]==1)return 8;
//    else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0 && sensor[8]==0)
//    {
//      gakDapat=1;
//    }

    nilai_error=0;
    count_error=0;
    for(int s=0;s<=8;s++)
    {
      if(sensor[s] == 1)
      {
        nilai_error+=index[s];
      }
      else if(sensor[s]==0)
      {
        count_error+=1;
      }
    }
    if(count_error >= 9)
    { 
      gakDapat=1;
    }
    if(count_error==5)
    {
      if(nilai_error==-2)
        nilai_error=0;
      else if(nilai_error==2)
        nilai_error=0; 
    }
    else return nilai_error;    
}

void cekFlame()
{
  if(keluar12==1)
  {
    if(analogRead(flame5)>batasSensor[5] || analogRead(flame4)>batasSensor[4] || analogRead(flame3)>batasSensor[3]  || analogRead(flame2)>batasSensor[2] || analogRead(flame1)>batasSensor[1] || analogRead(flame0)>batasSensor[0])  /////kiri
    {
      flagFlame=1;
    }
    else  
    {
      flagFlame=0;
    }
  }
  else if(keluar12==0)
  {
    if(analogRead(flame8)>batasSensor[8] || analogRead(flame7)>batasSensor[7] || analogRead(flame6)>batasSensor[6] || analogRead(flame5)>batasSensor[5] || analogRead(flame4)>batasSensor[4] || analogRead(flame3)>batasSensor[3])  /////kanan
    {
      flagFlame=1;
    }
    else
    {
      flagFlame=0;
    }
  }
  
}

void mauSerongKananApi()
{
  if(motion==1)
  {
//    passData(2);delay(delayGeserSedikit);
    passData(6);delay(delayGeserSedikitApi);  
//    passData(1);delay(delayGeserSedikitApi2);  
  }
  else if(motion==2)
  {
//    passData(3);delay(delayGeserSedikit);
    passData(6);delay(delayGeserSedikitApi);  
//    passData(2);delay(delayGeserSedikitApi2); 
  }
  else if(motion==3)
  {
//    passData(4);delay(delayGeserSedikit);  
    passData(6);delay(delayGeserSedikitApi);
//    passData(3);delay(delayGeserSedikitApi2); 
  }
  else if(motion==4)
  {
//    passData(1);delay(delayGeserSedikit);  
    passData(6);delay(delayGeserSedikitApi);
//    passData(4);delay(delayGeserSedikitApi2); 
  }
}

void mauSerongKiriApi()
{
  if(motion==1)
  {
//    passData(4);delay(delayGeserSedikit); 
    passData(5);delay(delayGeserSedikitApi); 
//    passData(1);delay(delayGeserSedikitApi2); 
  }
  else if(motion==2)
  {
//    passData(1);delay(delayGeserSedikit);  
    passData(5);delay(delayGeserSedikitApi);
//    passData(2);delay(delayGeserSedikitApi2); 
  }
  else if(motion==3)
  {
//    passData(2);delay(delayGeserSedikit); 
    passData(5);delay(delayGeserSedikitApi); 
//    passData(3);delay(delayGeserSedikitApi2); 
  }
  else if(motion==4)
  {
//    passData(3);delay(delayGeserSedikit);  
    passData(5);delay(delayGeserSedikitApi);
//    passData(4);delay(delayGeserSedikitApi2); 
  }
}

void semprot()
{
  passData(0);
  digitalWrite(semprotan,HIGH);delay(700);          //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ DIGANTI 1200 !!!!!!!!!!
  digitalWrite(semprotan,LOW);delay(40);
  digitalWrite(semprotan,HIGH);delay(700);
  batasBawah=pos-200;batasAtas=pos+200;
  for(int a=0;a<2;a++)
  {
    for(i=batasAtas;i>=batasBawah;i-=selisih)
    {
      speeds=1000;sync(i);
      delay(cepatScanApi);
    }
    for(i=batasBawah;i<=batasAtas;i+=selisih)
    {
      speeds=1000;sync(i);
      delay(cepatScanApi);
    }
  }
  speeds=1000;sync(pos);
  delay(300);
  digitalWrite(semprotan,LOW);
  cekApi();                     //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Diganti !!!!!!!!!!!!!!!!
  if(flagApi==1)
  {
    digitalWrite(semprotan,HIGH);delay(200);
    digitalWrite(semprotan,LOW);delay(30);
    digitalWrite(semprotan,HIGH);delay(200);
    batasBawah=pos-250;batasAtas=pos+250; 
    for(int a=0;a<1;a++)
    {
      for(i=batasAtas;i>=batasBawah;i-=selisih)
      {
        speeds=1000;sync(i);
        delay(cepatScanApi);
        digitalWrite(semprotan,HIGH);
      }
      for(i=batasBawah;i<=batasAtas;i+=selisih)
      {
        speeds=1000;sync(i);
        delay(cepatScanApi);
        digitalWrite(semprotan,HIGH);
      }
    }
    digitalWrite(semprotan,LOW);
  }
}

void tembokKosong()
{
  rotateKepala();
  passData(0);
  flagDapat=0;
  flagPointing=0;
  flagTembok=1;
}

void followKananApi()
{
  motionNext=0;
  batasMenjauhkan=260;
  batasMendekatkan=750;
  if(motion==1)
  { 
    selisihKanan=kanan0-kanan1;
    if(selisihKanan<batasBenerinKananBawahRoom  && kanan0<batasSerong && kanan1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiriApi();
    }
    else if(selisihKanan>batasBenerinKananAtasRoom  && kanan0<batasSerong && kanan1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKananApi();
    }  
    else 
    {
      passData(1);  
    }
    if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    if(depan0!=0 && depan1!=0&&(depan0<batasDepanApi || depan1<batasDepanApi))
    {
      countFollowApi++;
      motionNext=4; //scan
      passData(0);
      flagDapat=0;
      flagPointing=0;
      flagTembok=1;
    }
    else if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      passData(1);
      delay(delayBelok);
      counterBelok=0;
      while(belakang1>batasLurus)
      {
        passData(2);delay(delayBatasCount);
        counterBelok++;
        if(counterBelok>batasCount)// && belakang0>batasBelok && belakang1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
      }
      motion=2;tembokKosong();
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihBelakang=belakang0-belakang1;
    if(selisihBelakang<batasBenerinBelakangBawahRoom  && belakang0<batasSerong  && belakang1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiriApi();
    }
    else if(selisihBelakang>batasBenerinBelakangAtasRoom  && belakang0<batasSerong  && belakang1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKananApi();
    }    
    else
    {
      passData(2);
    }
    if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan   && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan   && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    if(kanan0!=0&&kanan1!=0&&(kanan0<batasDepanApi || kanan1<batasDepanApi))
    {
        countFollowApi++;
        motionNext=1; //scan
        passData(0);
        flagDapat=0;
        flagPointing=0;
        flagTembok=1;
    }
    else if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      passData(2);
      delay(delayBelok);
      counterBelok=0;
      while(kiri1>batasLurus)
      {
        passData(3);delay(delayBatasCount);
        counterBelok++;
        if(counterBelok>batasCount)// && kiri0>batasBelok &&kiri1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
      }
      motion=3;tembokKosong();
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKiri=kiri0-kiri1;
    if(selisihKiri<batasBenerinKiriBawahRoom  && kiri0<batasSerong && kiri1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiriApi();
    }
    else if(selisihKiri>batasBenerinKiriAtasRoom  && kiri0<batasSerong && kiri1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKananApi();
    }    
    else
    {
      passData(3);
    }
    if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    if(belakang0!=0&&belakang1!=0&&(belakang0<batasDepanApi || belakang1<batasDepanApi))
    {
      countFollowApi++;
        motionNext=2; //scan
        passData(0);
        flagDapat=0;
        flagPointing=0;
        flagTembok=1;
    }
    else if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      passData(3);
      delay(delayBelok);
      counterBelok=0;
      while(depan1>batasLurus)
      {
        passData(4);delay(delayBatasCount);
        counterBelok++;
        if(counterBelok>batasCount)// && depan0>batasBelok && depan1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
      }
      motion=4;tembokKosong();
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihDepan=depan0-depan1;
    if(selisihDepan<batasBenerinDepanBawahRoom  && depan0<batasSerong  && depan1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiriApi();
    }
    else if(selisihDepan>batasBenerinDepanAtasRoom  && depan0<batasSerong && depan1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKananApi();
    }   
    else
    {
      passData(4); 
    }
    if(depan0>batasMendekatkan&&depan1>batasMendekatkan && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    if(kiri0!=0&&kiri1!=0&&(kiri0<batasDepanApi || kiri1<batasDepanApi))
    {
      countFollowApi++;
        motionNext=3; //scan
        passData(0);
        flagDapat=0;
        flagPointing=0;
        flagTembok=1;
    }
    else if(depan0>batasBelok&&depan1>batasBelok)
    {
      passData(4);
      delay(delayBelok);
      counterBelok=0;
      while(kanan1>batasLurus)
      {
        passData(1);delay(delayBatasCount);
        counterBelok++;
        if(counterBelok>batasCount)// && kanan0>batasBelok && kanan1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
      }
      motion=1;tembokKosong();
    }
  }
}

void followKiriApi()
{
  motionNext=0;
  batasMenjauhkan=260;
  batasMendekatkan=750;
  if(motion==1)
  { 
    selisihKiri=kiri1-kiri0;
    if(selisihKiri<batasBenerinKiriBawahRoom  && kiri0<batasSerong && kiri1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKananApi();
    }
    else if(selisihKiri>batasBenerinKiriAtasRoom  && kiri0<batasSerong && kiri1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiriApi();
    }  
    else 
    {
      passData(1);  
    }
    if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    if(depan0!=0&&depan1!=0&&(depan0<batasDepanApi || depan1<batasDepanApi))
    {
      countFollowApi++;
      motionNext=2; //scan
      passData(0);
      flagDapat=0;
      flagPointing=0;
      flagTembok=1;
    }
    else if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      passData(1);
      delay(delayBelok);
      counterBelok=0;
      while(belakang0>batasLurus)
      {
        passData(4);delay(delayBatasCount);
        counterBelok++;
        if(counterBelok>batasCount)// && belakang0>batasBelok && belakang1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
      }
      motion=4;tembokKosong();
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihDepan=depan1-depan0;
    if(selisihDepan<batasBenerinDepanBawahRoom  && depan0<batasSerong  && depan1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKananApi();
    }
    else if(selisihDepan>batasBenerinDepanAtasRoom  && depan0<batasSerong  && depan1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiriApi();
    }    
    else
    {
      passData(2);
    }
    if(depan0>batasMendekatkan&&depan1>batasMendekatkan   && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan   && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    if(kanan0!=0&&kanan1!=0&&(kanan0<batasDepanApi || kanan1<batasDepanApi))
    {
      countFollowApi++;
        motionNext=3; //scan
        passData(0);
        flagDapat=0;
        flagPointing=0;
        flagTembok=1;
    }
    else if(depan0>batasBelok&&depan1>batasBelok)
    {
      passData(2);
      delay(delayBelok);
      counterBelok=0;
      while(kiri0>batasLurus)
      {
        passData(1);delay(delayBatasCount);
        counterBelok++;
        if(counterBelok>batasCount)// && kiri0>batasBelok && kiri1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
      }
      motion=1;tembokKosong();
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKanan=kanan1-kanan0;
    if(selisihKanan<batasBenerinKananBawahRoom  && kanan0<batasSerong && kanan1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKananApi();
    }
    else if(selisihKanan>batasBenerinKananAtasRoom  && kanan0<batasSerong && kanan1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiriApi();
    }    
    else
    {
      passData(3);
    }
    if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    if(belakang0!=0&&belakang1!=0&&(belakang0<batasDepanApi || belakang1<batasDepanApi))
    {
      countFollowApi++;
        motionNext=4; //scan
        passData(0);
        flagDapat=0;
        flagPointing=0;
        flagTembok=1;
    }
    else if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      passData(3);
      delay(delayBelok);
      counterBelok=0;
      while(depan0>batasLurus)
      {
        passData(2);delay(delayBatasCount);
        counterBelok++;
        if(counterBelok>batasCount)// &&depan0>batasBelok && depan1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
      }
      motion=2;tembokKosong();
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihBelakang=belakang1-belakang0;
    if(selisihBelakang<batasBenerinBelakangBawahRoom  && belakang0<batasSerong  && belakang1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKananApi();
    }
    else if(selisihBelakang>batasBenerinBelakangAtasRoom  && belakang0<batasSerong && belakang1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiriApi();
    }   
    else
    {
      passData(4); 
    }
    if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    if(kiri0!=0&&kiri1!=0&&(kiri0<batasDepanApi || kiri1<batasDepanApi))
    {
      countFollowApi++;
        motionNext=1; //scan
        passData(0);
        flagDapat=0;
        flagPointing=0;
        flagTembok=1;
    }
    else if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      passData(4);
      delay(delayBelok);
      counterBelok=0;
      while(kanan0>batasLurus)
      {
        passData(3);delay(delayBatasCount);
        counterBelok++;
        if(counterBelok>batasCount)// && kanan0>batasBelok && kanan1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
      }
      motion=3;tembokKosong();
    }
  }
}

void updateTpa()                                                                  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    update TPA
{
  countArrayTPA=0;
  flagDapat=0;
  for(int a = 0; a < 8; a++)
  {
     temperature[a] = getData(a+2);
     temperature1[a] = getData1(a+2);
  }
//  temperature1[2]=0;
//  temperature1[4]=0;
  for(int a=0;a<8;a++)
  {
    if(temperature[a]>=suhu || temperature1[a]>=suhu)// || analogRead(flame)>800)
    {
      flagDapat=1;
    }
    if(temperature[a]>suhuSemprot || temperature1[a]>suhuSemprot)// || analogRead(flame)>1020)
      countArrayTPA++;
  }
  if(analogRead(flame4)>batasSensor[4])
  {
    flagDapat=1;
  }
//  if(flagDapat==1)
//  {
//      digitalWrite(led,HIGH);
//      delay(500);
//      digitalWrite(led,LOW);
//      delay(500);
//      digitalWrite(led,HIGH);
//      delay(500);
//      digitalWrite(led,LOW);
//      delay(500);
//      digitalWrite(led,HIGH);
//      delay(500);
//      digitalWrite(led,LOW);
//      delay(500);
//  }
  if(countArrayTPA>=2)
  {
    if(motionNext>0)
    {
      motion=motionNext;
      motionNext=0;
    }
    passData(0);
///    semprot();
//    digitalWrite(led,HIGH);
//    delay(500);
//    digitalWrite(led,LOW);
//    delay(500);
//    digitalWrite(led,HIGH);
//    delay(500);
//    digitalWrite(led,LOW);
//    delay(500);
    flagTarget=1;  
  }
}

void posisikanDiri()  //memposisikan diri ke arah kompas         //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    posisikan Diri
{
  if(pos<2558&&pos>=1535)
  {
    motion=1;
    if(pos>=2248)
    {
      //pivotKiri
      flagPivot=0;
    }
    else if(pos<1848)
    {
      //pivotKanan
      flagPivot=1;
    }
    else
      flagPivot=2;
  }
  else if(pos<3581&&pos>=2558)
  {
    motion=4;
    if(pos>=3272)
    {
      //pivotKiri
      flagPivot=0;
    }
    else if(pos<2872)
    {
      //pivotKanan
      flagPivot=1;
    }
    else
      flagPivot=2;
  }
  else if(pos<1535&&pos>=512)
  {
    motion=2;
    if(pos>=1224)
    {
      //pivotKiri
      flagPivot=0;
    }
    else if(pos<824)
    {
      //pivotKanan
      flagPivot=1;
    }
    else
      flagPivot=2;
  }
  else if(pos<=4095&&pos>=3581)
  {
    motion=4;
    flagPivot=0;
  }
  else if(pos<512&&pos>=0)
  {
    motion=4;
    flagPivot=0;
  }
  if(flagPivot<3)
  {
    delay(500);
    sudutApi=sudutSaja();
    delay(500);
    rotateKepala();
    delay(500);
    sudutAwal=sudutSaja();
    sudutAwal=sudutSaja();
    if(flagPivot==0)
    {
      if(sudutAwal>sudutApi)
      {
        pivotKiriApi
        while(sudutAwal>sudutApi)
        {
          pivotKiriApi
          sudutAwal=sudutSaja();
          if(sudutAwal<=sudutApi)
            break;
          updateTpa();
          if(flagDapat==1)
          {
            passData(0);
            break;
          }
          delay(delayPivotPosisikan);
        }
      }
      else if(sudutAwal<sudutApi)
      {
        pivotKiriApi
        while(sudutAwal<batasKompasPosisi)
        {
          pivotKiriApi
          sudutAwal=sudutSaja();
          if(sudutAwal>=batasKompasPosisi)
            break;
          updateTpa();
          if(flagDapat==1)
          {
            passData(0);
            break;
          }
          delay(delayPivotPosisikan);
        }
        while(sudutAwal>sudutApi)
        {
          pivotKiriApi
          sudutAwal=sudutSaja();
          if(sudutAwal<=sudutApi)
            break;
          updateTpa();
          if(flagDapat==1)
          {
            passData(0);
            break;
          }
          delay(delayPivotPosisikan);
        }
      }
    }
    else if(flagPivot==1)
    {
      if(sudutAwal<sudutApi)
      {
        pivotKananApi
        while(sudutAwal<sudutApi)
        {
          pivotKananApi
          sudutAwal=sudutSaja();
          if(sudutAwal>=sudutApi)
            break;  
          updateTpa();
          if(flagDapat==1)
          {
            passData(0);
            break;
          }
          delay(delayPivotPosisikan);
        }
      }
      else if(sudutAwal>sudutApi)
      {
        pivotKananApi
        while(sudutAwal>batasKompasPosisi)
        {
          pivotKananApi
          sudutAwal=sudutSaja();
          if(sudutAwal<batasKompasPosisi)
            break;
          updateTpa();
          if(flagDapat==1)
          {
            passData(0);
            break;
          }
          delay(delayPivotPosisikan);
        }
        while(sudutAwal<sudutApi)
        {
          
          pivotKananApi
          sudutAwal=sudutSaja();
          if(sudutAwal>sudutApi)
            break;
          updateTpa();
          if(flagDapat==1)
          {
            passData(0);
            break;
          }
          delay(delayPivotPosisikan);
        }
      }
    }
    passData(0);
    if(motion==3)
    {
      pivotKananApi
      delay(800);
//      sudutApi=sudutSaja();delay(100);
//      pos=1023;
//      sync(pos);delay(500);
//      sudutAwal=sudutSaja();
//      if(sudutAwal<sudutApi)
//      {
//        while(sudutAwal<sudutApi)
//        {
//          sudutAwal=sudutSaja();
//          pivotKananApi
//        }
//      }
//      else if(sudutAwal>sudutApi)
//      {
//        while(sudutAwal>batasKompasPosisi)
//        {
//          sudutAwal=sudutSaja();
//          pivotKananApi
//        }
//        while(sudutAwal<sudutApi)
//        {
//          sudutAwal=sudutSaja();
//          pivotKananApi
//        }
//      }
//      passData(0);motion=2;
      motion=2;
      passData(0);
      flagDapat=0;
      flagPointing=0;
      flagTembok=0;
    }
  }
}
    
void scanKananKiri()                                                                  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    scan Kanan Kiri
{
  int i;
  flagDapat=0;
  if(flagDapat==0)
  {
      for(i=batasAtas;i>=batasBawah;i-=selisih)
      {
        speeds=1000;sync(i);
        delay(cepatScan);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          break;
        }
      }
  }
  if(flagDapat==0)
  {
      for(i=batasBawah;i<=batasAtas;i+=selisih)
      {
        speeds=1000;sync(i);
        delay(cepatScan);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          break;
        }
      }
  }
}

void pidFlame()
{
  keluarFlame=0;
  while(keluarFlame==0)
  {
    sensor[0]=analogRead(flame0);
    sensor[1]=analogRead(flame1);
    sensor[2]=analogRead(flame2);
    sensor[3]=analogRead(flame3);
    sensor[4]=analogRead(flame4);
    sensor[5]=analogRead(flame5);
    sensor[6]=analogRead(flame6);
    sensor[7]=analogRead(flame7);
    sensor[8]=analogRead(flame8);
      
    for(int d=0;d<=8;d++)
    {
        if(sensor[d]> batasSensor[d])sensor[d]=1;
        else sensor[d]=0;
    }
    posisi=error();
    if(gakDapat==1)
    {
      countErrorPosisi++;
    }
    else
    {
      countErrorPosisi=0;
      P= posisi;
      I= I + posisi;
      D= posisi - previous_error;
      PID_Value=(kp*P)+(ki*I)+(kd*D);
      previous_error=posisi;
      pid=int(PID_Value);
      if(pos+pid>4095 || pos+pid<0)
      {
        pid=0;
      }
      pos=pos+pid;
      speeds=1000;
      sync(pos);
//      Serial.println(pos);
      flagDapat=0;
      updateTpa();              //ini

      if(posisi<=-2 || posisi>=2)
        passData(0);
      else if(posisi==0)          //ini
      {
        passData(0);
        updateTpa();
        keluarFlame=1;break;
      }
    }
    if(countErrorPosisi>=100)
    {
      posisi=10;
      countErrorPosisi=0;
      keluarFlame=1;break;
    }
  }
}

void mendekatiLagi()
{
  if(pos>1535&&pos<=2558)
  {
    motion=1;
  }
  else if(pos>512&&pos<=1535)
  {
    motion=2;
  }
  else if(pos>2558&&pos<=3581)
  {
    motion=4;
  }
  else
  {
    passData(0);
    flagDapat=0;
    flagPointing=0;
    flagTembok=1;
  }
  if(motion==1)
  {
    batasBawah=1535;batasAtas=2558;
    pidFlame();
    if(pos>2150)
    {
      serongKiri1
      delay(delaySerongApi);
      countSerong++;//passData(0);//delay(20);
    }
    else if(pos<1950)
    {
      serongKanan1
      delay(delaySerongApi);
      countSerong++;//passData(0);//delay(20);
    }
    else if(pos>=1950&&pos<=2150)
    {
      passData(1);
      delay(delayMajuLagi);//passData(0);
      countSerong=0;
    }
  }
  else if(motion==2)
  {
    batasBawah=512;batasAtas=1535;
    pidFlame();
    if(pos>1124)
    {
      serongKiri2
      delay(delaySerongApi);
      countSerong++;//passData(0);//delay(20);
    }
    else if(pos<924)
    {
      serongKanan2
      delay(delaySerongApi);
      countSerong++;//passData(0);//delay(20);
    }
    else if(pos>=924&&pos<=1124)
    {
      passData(2);
      delay(delayMajuLagi);//passData(0);
      countSerong=0;
    }
  }
  else if(motion==4)
  {
    batasBawah=2558;batasAtas=3581;
    pidFlame();
    if(pos>3172)
    {
      serongKiri4
      delay(delaySerongApi);
      countSerong++;//passData(0);//delay(20);
    }
    else if(pos<2972)
    {
      serongKanan4
      delay(delaySerongApi);
      countSerong++;//passData(0);//delay(20);
    }
    else if(pos>=2972&&pos<=3172)
    {
      passData(4);
      delay(delayMajuLagi);//passData(0);
      countSerong=0;
    }
  } 
  if(posisi==10)
  {
//      passData(0);
//      flagDapat=0;
//      batasAtas=pos+500;
//      batasBawah=pos-500;
//      scanKananKiri();
      passData(0);
      flagDapat=0;
      scanKananKiri();
      
//        passData(0);
//        flagDapat=0;
//        flagPointing=0;
//        flagTembok=1;
  }
  if(countSerong>=100)
  {
        passData(0); 
        flagDapat=0;
        flagPointing=0;
        flagTembok=0;
  }
  if(motion==1)
  {
    batasBawah=1535;batasAtas=2558;
    if(depan0<batasDepanFurniture && depan0!=0)
    {
        passData(2);delay(delayMenjauhFurniture);
        serongKiri2
        delay(delaySerongApiFurn);
//        passData(0);
//        flagDapat=0;
//        flagPointing=0;
//        flagTembok=1;
      passData(0);
      flagDapat=0;
      scanKananKiri();
    }
    else if(depan1<batasDepanFurniture && depan1!=0)
    {
      passData(4);delay(delayMenjauhFurniture);
      serongKanan2
      delay(delaySerongApiFurn);
//      passData(0);
//      flagDapat=0;
//      flagPointing=0;
//      flagTembok=1;
      passData(0);
      flagDapat=0;
      scanKananKiri();
    }
  }
  else if(motion==2)
  {
    batasBawah=512;batasAtas=1535;
    if(kanan0<batasDepanFurniture && kanan0!=0)
    {
        passData(3);delay(delayMenjauhFurniture);
        serongKiri2
        delay(delaySerongApiFurn);
//        passData(0);
//        flagDapat=0;
//        flagPointing=0;
//        flagTembok=1;
      passData(0);
      flagDapat=0;
      scanKananKiri();
    }
    else if(kanan1<batasDepanFurniture && kanan1!=0)
    {
      passData(1);delay(delayMenjauhFurniture);
      serongKanan2
      delay(delaySerongApiFurn);
//      passData(0);
//      flagDapat=0;
//      flagPointing=0;
//      flagTembok=1;
      passData(0);
      flagDapat=0;
      scanKananKiri();
    }
  }
  else if(motion==4)
  {
    batasBawah=2558;batasAtas=3581;
    if(kiri0<batasDepanFurniture && kiri0!=0)
    {
        passData(1);delay(delayMenjauhFurniture);
        serongKiri2
        delay(delaySerongApiFurn);
//        passData(0);
//        flagDapat=0;
//        flagPointing=0;
//        flagTembok=1;
      passData(0);
      flagDapat=0;
      scanKananKiri();
    }
    else if(kiri1<batasDepanFurniture && kiri1!=0)
    {
      passData(3);delay(delayMenjauhFurniture);
      serongKanan2
      delay(delaySerongApi);
//      passData(0);
//      flagDapat=0;
//      flagPointing=0;
//      flagTembok=1;
      passData(0);
      flagDapat=0;
      scanKananKiri();
    }
  }
}

void mendekatiScan()                                                                  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    Mendekati Scan
{
  if(countMendekati==0)
  {
    if(motion==1)
    {
      passData(1);batasBawah=1535;batasAtas=2558;
      delay(delayMendekatiApi);
    }
    else if(motion==2)
    {
      passData(2);batasBawah=512;batasAtas=1535;
      delay(delayMendekatiApi);
    }
    else if(motion==4)
    {
      passData(4);batasBawah=2558;batasAtas=3581;
      delay(delayMendekatiApi);
    } 
  }
  else    //bisa serong juga
  {
    if(motion==1)
    {
      if(flagDapat==0)
      {
        batasBawah=1535;batasAtas=2558;
      }
      else
      {
        batasBawah=pos-200;batasAtas=pos+200; 
      }
      if(pos>2250)
      {
        serongKiri1
        delay(delaySerongApi);
//        rotateKepala();
        passData(1);delay(delayMendekatiApi/2);
      }
      else if(pos<1850)
      {
        serongKanan1
        delay(delaySerongApi);
//        rotateKepala();
        passData(1);delay(delayMendekatiApi/2);
      }
      else
      {
//        rotateKepala();
        passData(1);delay(delayMendekatiApi);
      }
    }
    else if(motion==2)
    {
      if(flagDapat==0)
      {
        batasBawah=512;batasAtas=1535;
      }
      else
      {
        batasBawah=pos-200;batasAtas=pos+200; 
      }
      if(pos>1224)
      {
        serongKiri2
        delay(delaySerongApi);
//        rotateKepala();
        passData(2);delay(delayMendekatiApi/2);
      }
      else if(pos<824)
      {
        serongKanan2
        delay(delaySerongApi);
//        rotateKepala();
        passData(2);delay(delayMendekatiApi/2);
      }
      else
      {
//        rotateKepala();
        passData(2);delay(delayMendekatiApi);
      }
    }
    else if(motion==4)
    {
      if(flagDapat==0)
      {
        batasBawah=2558;batasAtas=3581;
      }
      else
      {
        batasBawah=pos-200;batasAtas=pos+200; 
      }
      if(pos>3272)
      {
        serongKiri4
        delay(delaySerongApi);
//        rotateKepala();
        passData(4);delay(delayMendekatiApi/2);
      }
      else if(pos<2872)
      {
        serongKanan4
        delay(delaySerongApi);
//        rotateKepala();
        passData(4);delay(delayMendekatiApi/2);
      }
      else
      {
//        rotateKepala();
        passData(4);delay(delayMendekatiApi);
      }
    } 
  }
  passData(0);
  flagDapat=0;
  scanKananKiri();
  countMendekati++;
  if(pos==batasAtas && flagDapat==0)
  {
    passData(0);
    flagDapat=0;
    flagPointing=0;
    flagTembok=1;
  }
  if(motion==1)
  {
    if((depan0<batasDepanApi || depan1<batasDepanApi)&&depan0!=0&&depan1!=0)
    {
        passData(0);
        flagDapat=0;
        flagPointing=0;
        flagTembok=1;
    }
  }
  else if(motion==2)
  {
    if((kanan0<batasDepanApi || kanan1<batasDepanApi)&&kanan0!=0&&kanan1!=0)
    {
        passData(0);
        flagDapat=0;
        flagPointing=0;
        flagTembok=1;
    }
  }
  else if(motion==4)
  {
    if((kiri0<batasDepanApi || kiri1<batasDepanApi)&&kiri0!=0&&kiri1!=0)
    {
        passData(0);
        flagDapat=0;
        flagPointing=0;
        flagTembok=1;
    }
  }
}

//void mendekati()                                                                  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    Mendekati
//{
//  if(pos>=512&&pos<1535)
//  {
//    passData(2);
//    delay(delayMendekati);
//  }
//  else if(pos>=1535&&pos<2558)
//  {
//    passData(1);
//    delay(delayMendekati);
//  }
//  else if(pos>=2558&&pos<3581)
//  {
//    passData(4);
//    delay(delayMendekati);
//  }
//  else if(pos >= 0 && pos<512 || pos>= 3581 && pos < 4096)
//  {
//    passData(3);
//    delay(delayMendekati);
//  }
//  passData(0);
//}

void geserKipas()                                                                  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    Geser Kipas
{
  int i;
  if(motion==1)
  {
    if(flagDapat==0)
    {
      for(i=3250;i>=750;i-=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          if(motionNext>0)
          {
            motion=motionNext;
            motionNext=0;
          }
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
        }
      }
    }
    if(flagDapat==0)
    {
      for(i=750;i<=3250;i+=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa(); 
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          if(motionNext>0)
          {
            motion=motionNext;
            motionNext=0;
          }
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
        }
      }
      count++;
    }
    if(flagDapat==0 && count>=jumScan)
    {
      // gak dapat 2 kali
      count=0;
      flagChange=0;
      flagPointing=2;
      if(motionNext>0)
      {
        motion=motionNext;
        motionNext=0;
      }
    }
  }
  else if(motion==2)
  {
    if(flagDapat==0 && flagChange==0)
    {
      for(i=2250;i>=0;i-=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          if(motionNext>0)
          {
            motion=motionNext;
            motionNext=0;
          }
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;  
        }
      }
    }
    if(flagDapat==0&&flagChange==0)
    {
      for(i=0;i<=2250;i+=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa(); 
        if(flagDapat==1)
        {
            //dapat Api
            pos=i;
            if(motionNext>0)
            {
              motion=motionNext;
              motionNext=0;
            }
            posisikanDiri();
            flagPointing=1;
            countMendekati=0;
            break;
        }
      }
      count++;
    }
    if(flagDapat==0 && flagChange==0 && count>=jumScan)
    {
      flagChange=1;
      count=0;
    }
    if(flagDapat==0 && flagChange==1)
    {
      for(i=4095;i>=3750;i-=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
            //dapat Api
            if(motionNext>0)
            {
              motion=motionNext;
              motionNext=0;
            }
            pos=i;
            posisikanDiri();
            flagPointing=1;
            countMendekati=0;
            break; 
        }
       }
    }
    if(flagDapat==0 && flagChange==1)
    {
      for(i=3750;i<=4095;i+=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa();
        if(flagDapat==1)
         {
            //dapat Api
            pos=i;
            if(motionNext>0)
            {
              motion=motionNext;
              motionNext=0;
            }
            posisikanDiri();
            flagPointing=1;
            countMendekati=0;
            break;
         }
      }
      count++;
    }
    if(flagDapat==0 && flagChange==1 && count>=jumScan)
    {
      count=0;
      flagChange=0;
      flagPointing=2;
      if(motionNext>0)
      {
        motion=motionNext;
        motionNext=0;
      }
    }
  }
  else if(motion==3)
  {
    if(flagDapat==0 && flagChange==0)
    {
      for(i=1250;i>=0;i-=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          if(motionNext>0)
          {
            motion=motionNext;
            motionNext=0;
          }
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;  
        }
      }
    }
    if(flagDapat==0&&flagChange==0)
    {
      for(i=0;i<=1250;i+=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa(); 
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          if(motionNext>0)
          {
            motion=motionNext;
            motionNext=0;
          }
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
        }
      }
      count++;
    }
    if(flagDapat==0 && flagChange==0 && count>=jumScan)
    {
      count=0;
      flagChange=1;
    }
    if(flagDapat==0 && flagChange==1)
    {
      for(i=4095;i>=2750;i-=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          if(motionNext>0)
          {
            motion=motionNext;
            motionNext=0;
          }
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break; 
        }
      }
    }
    if(flagDapat==0 && flagChange==1)
    {
      for(i=2750;i<=4095;i+=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
            //dapat Api
            pos=i;
            if(motionNext>0)
            {
              motion=motionNext;
              motionNext=0;
            }
            posisikanDiri();
            flagPointing=1;
            countMendekati=0;
            break; 
        }
      }
      count++;
    }
    if(flagDapat==0 && flagChange==1 && count>=jumScan)
    {
       count=0;
       flagChange=0;
       flagPointing=2;
       if(motionNext>0)
        {
          motion=motionNext;
          motionNext=0;
        }
    }
  }
  else if(motion==4)
  {
    if(flagDapat==0 && flagChange==0)
    {
      for(i=4095;i>=1800;i-=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          if(motionNext>0)
          {
            motion=motionNext;
            motionNext=0;
          }
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
        }
      }
    }
    if(flagDapat==0&&flagChange==0)
    {
      for(i=1800;i<=4095;i+=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          if(motionNext>0)
          {
            motion=motionNext;
            motionNext=0;
          }
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
        }
      }
      count++;
    }
    if(flagDapat==0 && flagChange==0 && count>=jumScan)
    {
      count=0;
      flagChange=1;
    }
    if(flagDapat==0 && flagChange==1)
    {
      for(i=0;i<=250;i+=cepatGeserKipas)
      {
        speeds=1000;sync(i);
        delay(cepatScanKipas);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          if(motionNext>0)
          {
            motion=motionNext;
            motionNext=0;
          }
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break; 
        }
       }
    }
    if(flagDapat==0 && flagChange==1)
    {
        for(i=250;i>=0;i-=cepatGeserKipas)
        {
          speeds=1000;sync(i);
          delay(cepatScanKipas);
          pos=i;
          updateTpa();
          if(flagDapat==1)
           {
              //dapat Api
              pos=i;
              if(motionNext>0)
              {
                motion=motionNext;
                motionNext=0;
              }
              posisikanDiri();
              flagPointing=1;
              countMendekati=0;
              break;
           }
        }
        count++;
    }
    if(flagDapat==0 && flagChange==1 && count>=jumScan)
    {
      count=0;
      flagChange=0;
      flagPointing=2;
      if(motionNext>0)
      {
        motion=motionNext;
        motionNext=0;
      }
    }
  }
}

void geserKiri()                                                                  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    Geser Kiri
{
  int i;  
  if(motion==1)
  {
    if(flagDapat==0)
    {
      for(i=3750;i>=1250;i-=cepatGeser)
      {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
      }
    }
    if(flagDapat==0)
    {
      for(i=1250;i<=3750;i+=cepatGeser)
      {
        speeds=1000;sync(i);
        delay(cepatScan);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
        }
      }
      count++;
    }
    if(flagDapat==0 && count>=jumScan)
    {
      // gak dapat 2 kali
      count=0;
      flagChange=0;
      flagPointing=2;
    }
  }
  if(motion==2)
  {
    if(flagDapat==0)
    {
      for(i=2750;i>=250;i-=cepatGeser)
      {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
      }
    }
    if(flagDapat==0)
    {
      for(i=250;i<=2750;i+=cepatGeser)
      {
        speeds=1000;sync(i);
        delay(cepatScan);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
        }
      }
      count++;
    }
    if(flagDapat==0 && count>=jumScan)
    {
      //gak dapat 2 kali
      count=0;
      flagChange=0;
      flagPointing=2;
    }
 }  
 if(motion==3)
 {
   if(flagDapat==0 && flagChange==0)
   {
    for(i=4096;i>=3250 ;i-=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
   }
   if(flagDapat==0 && flagChange==0)
   {
    for(i=3250;i<=4096;i+=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
    count++;
   }
   if(flagDapat==0 && flagChange==0 && count>=jumScan)
   {
     count=0;
     flagChange=1;
   }
   if(flagDapat==0 && flagChange==1)
   {
    for(i=0;i<=1750;i+=cepatGeser)
    {
      speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
   }
   if(flagDapat==0 && flagChange==1)
   {
    for(i=1750;i>=0;i-=cepatGeser)
    {
      speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
    count++;
   }
   if(flagDapat==0 && flagChange==1 && count>=jumScan)
    {
      count=0;
      flagChange=0;
      flagPointing=2;
    }
  }
 if(motion==4)
 {
  if(flagDapat==0 && flagChange==0)
   {
    for(i=4096;i>=2250;i-=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
   }
   if(flagDapat==0 && flagChange==0)
   {
    for(i=2250;i<=4096;i+=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
    count++;
   }
   if(flagDapat==0 && flagChange==0 && count>=jumScan)
    {
      count=0;
      flagChange=1;
    }
   if(flagDapat==0 && flagChange==1)
   {
    for(i=0;i<=750;i+=cepatGeser)
    {
      speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
   }
   if(flagDapat==0 && flagChange==1)
   {
    for(i=750;i>=0;i-=cepatGeser)
    {
      speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
    count++;
   }
   if(flagDapat==0 && flagChange==1 && count>=jumScan)
    {
      count=0;
      flagChange=0;
      flagPointing=2;
    }
  }
}

void geserKanan()                                                                  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    Geser Kanan
{
  int i;
  if(motion==1)
  {
    if(flagDapat==0)
    {
      for(i=2800;i>=250;i-=cepatGeser)
      {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
      }
    }
    if(flagDapat==0)
    {
      for(i=250;i<=2800;i+=cepatGeser)
      {
        speeds=1000;sync(i);
        delay(cepatScan);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
        }
      }
      count++;
    }
    if(flagDapat==0 && count>=jumScan)
    {
      //2 kali scan gak dapat
      flagChange=0;
      count=0;
      flagPointing=2;
    }
  } 
  if(motion==2)
  {
   if(flagDapat==0 && flagChange==0)
   {
    for(i=1800;i>=0;i-=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
   }
   if(flagDapat==0  && flagChange==0)
   {
    for(i=0;i<=1800;i+=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
    count++;
   }
   if(flagDapat==0 && flagChange==0 && count>=jumScan)
    {
      count=0;
      flagChange=1;
    }
   if(flagDapat==0 && flagChange==1)
   {
    for(i=3250;i<=4096;i+=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
        //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
   }
   if(flagDapat==0 && flagChange==1)
   {
    for(i=4096;i>=3250;i-=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
    count++;
   }
   if(flagDapat==0 && flagChange==1 && count>=jumScan)
    {
      //2 kali scan gak dapat
      flagChange=0;
      count=0;
      flagPointing=2;
    }
  }  
 if(motion==3)
 {
   if(flagDapat==0 && flagChange==0)
   {
    for(i=750;i>=0;i-=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
   }
   if(flagDapat==0 && flagChange==0)
   {
    for(i=0;i<=750;i+=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
    count++;
   }
   if(flagDapat==0 && flagChange==0 && count>=jumScan)
    {
      count=0;
      flagChange=1;
    }
   if(flagDapat==0 && flagChange==1)
   {
    for(i=2250;i<= 4096;i+=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
   }
   if(flagDapat==0 && flagChange==1)
   {
    for(i=4096;i>=2250;i-=cepatGeser)
    {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
    }
    count++;
   }
   if(flagDapat==0 && flagChange==1 && count>=jumScan)
   {
      count=0;
      flagChange=0;
      //2 kali scan gak dapat
      flagPointing=2; 
   }
 }
 if(motion==4)
 {
    if(flagDapat==0)
    {
      for(i=3750;i>= 1250;i-=cepatGeser)
      {
       speeds=1000;sync(i);
       delay(cepatScan);
       pos=i;
       updateTpa();
       if(flagDapat==1)
       {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
       }
      }
    }
    if(flagDapat==0)
    {
      for(i=1250;i<= 3750;i+=cepatGeser)
      {
        speeds=1000;sync(i);
        delay(cepatScan);
        pos=i;
        updateTpa();
        if(flagDapat==1)
        {
          //dapat Api
          pos=i;
          posisikanDiri();
          flagPointing=1;
          countMendekati=0;
          break;
        }
      }
      count++;
    }
    if(flagDapat==0 && count>=jumScan)
    {
      //2 kali scan gak dapat
      count=0;
      flagChange=0;
      flagPointing=2;
    }
 } 
}

void pointing()
{                                                                  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++           Pointing
  speedDown();passData(0);
  while(flagTarget==0)
  {
    if(flagPointing==0) // scan
    {
      if(flagTembok==0) //scan yang biasa
      {
        if(keluar12==1)
        {
          geserKiri();
        }
        else
        {
          geserKanan();
        } 
      }
      else if(flagTembok==1)  //scan jika tembok di sampingnya jauh
      {
        geserKipas();
      }
      countScan++;
    }
    else if(flagPointing==1)  //mendekati langsung sambil scan
    {
      mendekatiLagi();
    }
    else if(flagPointing==2)  //follow
    {
        if(keluar12==1)
        {
          followKananApi();rotateKepala();
          cekGaris();
          if(flagGaris==1)
          {
            gantiMotion();passData(motion);delay(400);
            resetGaris();
          }
          cekFlame();
          if(flagFlame==1)
          {
            flagFlame=0;
            passData(0);
            flagDapat=0;
            flagPointing=0;
            flagTembok=1;
          }
          if(countFollowApi==9)
          {
            countFollowApi=0;
            while(1)
            {
              followKananApi();rotateKepala();
              cekGaris();
              if(flagGaris==1)
              {
                majuSedikit();delay(delayMajuRoom);
                passData(0);
                flagTarget=1;
                flagSearchLagi=1;
                break;
              }
            }
          }
        }
        else
        { 
          followKiriApi();rotateKepala();
          cekGaris();
          if(flagGaris==1)
          {
            gantiMotion();passData(motion);delay(500);
            resetGaris();
          }
          cekFlame();
          if(flagFlame==1)
          {
            flagFlame=0;
            passData(0);
            flagDapat=0;
            flagPointing=0;
            flagTembok=1;
          }
          if(countFollowApi==9)
          {
            countFollowApi=0;
            while(1)
            {
              followKiriApi();rotateKepala();
              cekGaris();
              if(flagGaris==1)
              {
                majuSedikit();delay(delayMajuRoom);
                passData(0);
                flagTarget=1;
                flagSearchLagi=1;
                break;
              }
            }
          }
        } 
    }
  }
  speedUp();
  passData(0);
}

