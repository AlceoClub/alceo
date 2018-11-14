#include <EEPROM.h>                   // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#include <TimerOne.h>/
#include "flagVariabel.h"
#include "defineSRF.h"
#include "setupPin.h"
#include "passData.h"
#include "garis.h"
#include "follow.h"
#include "kompas.h"
#include "pointing.h"
#include "print.h"
#include "returnHome.h"

#define batasKeluar12 2750
#define batasKeluar12Pulang 3000
#define delayMundurSedikit 250

void setup() {
  // put your setup code here, to run once: fix
  Wire.begin();
  Serial.begin(115200);
  portOne.begin(1000000);
  attachInterrupt(digitalPinToInterrupt(3), dptflaggaris, FALLING);//line
  Timer1.initialize(250000);
  Timer1.pwm(8,512);
  Timer1.attachInterrupt(kedip);
  setupPin();
  passData(0);
  motion=1;
  
  all[0]=0xFF;
  all[1]=0xFF;
  all[2]=0x00;
  all[3]=0x07;
  all[4]=0x03;
  all[5]=0x1E;
  //delay(1000);
  
  sync(2040);     
}


void resetGaris()
{
  flagGaris=0;
  flagGarisAwal=0;
}

void cekKillPlug()
{
  if(digitalRead(killPlug)==LOW)
  {
    while(1)
    {
      passData(0);
    }
  }
}

void kedip()
{
  if(timer==1)
  {
    digitalWrite(led1,!digitalRead(led1));
  }
}

void dptflaggaris()
{
  flagGarisAwal=1;
}

void cekJalanPulang()
{
  if(jumlahRuang<4)
  {
    if(flagFollow==0)
    {
      flagFollow=1;
    }
    else if(flagFollow==1)
    {
      flagFollow=0;
    }
  }
}

void cekMic()
{
  if(digitalRead(mic)==LOW)
  {
      flagStart=1;
      flagRoom=0;
      flagTarget=0;
      cekTerdekatApi();
      clearEeprom();
      resetGaris();
      digitalWrite(led,HIGH);
  }
}
void cekStop()
{
  if(digitalRead(tombolStop)==LOW)
  {
      flagStart=1;
      flagRoom=0;
      flagTarget=0;
      cekTerdekatApi();
      clearEeprom();
      resetGaris();
//  digitalWrite(semprotan,HIGH);
//  delay(1200);
//  digitalWrite(semprotan,LOW);
//  delay(40);
//    digitalWrite(semprotan,HIGH);
//  delay(1200);
//  digitalWrite(semprotan,LOW);
  }
}

void clearEeprom()
{
  for(int a=0;a<10;a++)
  {
      EEPROM.write(a,0);
  }
  jumlahRuang=0;jumlahRuangBalik=0;
}

void cekApi()
{
  flagApi=0;
  timer=0;
  
  for(int a=0;a<4;a++)
  {
    if(digitalRead(uvtron)==HIGH)
    {
        timer=1;
        flagApi=1;
    } 
    delay(50);
  }
  if(keluar12==1)
  {
    if(motion==1)
    {
      pos=2400;
      sync(pos);
    }
    else if(motion==2)
    {
      pos=1400;
      sync(pos);
    }
    else if(motion==3)
    {
      pos=400;
      sync(pos);
    }
    else if(motion==4)
    {
      pos=3464;
      sync(pos);
    }
  }
  else
  {
    if(motion==1)
    {
      pos=1600;
      sync(pos);
    }
    else if(motion==2)
    {
      pos=600;
      sync(pos);
    }
    else if(motion==3)
    {
      pos=3694;
      sync(pos);
    }
    else if(motion==4)
    {
      pos=2664;
      sync(pos);
    }
  }
  for(int a=0;a<4;a++)
  {
    if(digitalRead(uvtron)==HIGH)
    {
        timer=1;
        flagApi=1;
    } 
    delay(20);
  }
}

void cekKejebak()
{
  if(countKejebak==12)
  {
    countKejebak=0;
    gantiMotion();
    resetGaris();
    while(1)
    {
        if(flagFollow==1) //follow kiri
        {
          followKanan();
        }
        else if(flagFollow==0)  //follow kanan
        {
          followKiri();
        }
        cekGaris();
        if(flagGaris==1)
          break;
    }
    passData(0);delay(200);
    majuSedikit();
    delay(delayMajuRoom);
    resetGaris();
  }
}

void cekSRF()
{
  if(kiri1<200 && kiri0<200)
    flagStart=1;
}

void loop()
{
  while(flagStart==0)   //Menunggu mic atau tombol start
  {
    flagRoom=0;
    printSRF();
//    printSelisih();
    printMic();
    Serial.println(sudutSaja());
//    cekRuangSaja();
    printTPA();
    printFlame();
    //printIR();

    flagGaris=0;
    cekStop();
    cekMic();
//    cekSRF();
    passData(0);
  }
  while(flagStart==1)   //Saat sudah ada sinyal untuk dimulai
  {
    while(1)
    {
     pointing(); 
    }
    if(flagTarget==0)   //Masih cari api
    {
      if(flagRoom==1&&flagFollow==0) //sudah di luar ruangan
      {
        cekBoneka();
        followKiri();rotateKepala();
        cekKejebak();
      }
      else if(flagRoom==1&&flagFollow==1)  //follow kanan
      {
        cekBoneka();
        followKanan();rotateKepala();
        cekKejebak();
      }
      else if(flagRoom==0&&flagFollowRoom==0&&jumlahRuang==0) //follow kiri
      {
        followRoomKiriFurn();rotateKepala();
      }
      else if(flagRoom==0&&flagFollowRoom==1&&jumlahRuang==0)  //follow kanan
      {
        followRoomKananFurn();rotateKepala();
      }
      else if(flagRoom==0&&flagFollowRoom==0&&jumlahRuang>0) //follow kiri
      {
        followRoomKiriFurn();rotateKepala();
      }
      else if(flagRoom==0&&flagFollowRoom==1&&jumlahRuang>0)  //follow kanan
      {
        followRoomKananFurn();rotateKepala();
      }
      cekGaris();
      if(flagGaris==1)
      {
        countKejebak=0;
        digitalWrite(led,HIGH);
        resetGaris();  
        if(flagRoom==0)
        {
          passData(0);  
          //rotateKepala();//digitalWrite(led,HIGH);delay(1200);
          //dimajuin sedikit sampai gak kena garis
          //cekRuangSaja();
          digitalWrite(led,LOW);
          majuSedikit();
          delay(delayMajuRoom);
          passData(0);
          delay(500);
          cekRuang();
//          delay(400);
          digitalWrite(led,HIGH);
          resetGaris();
          if(awalRoom==41 && jumlahRuang==1)  //maju dulu terus follow kanan, ketemu boneka putar balik jadi follow kiri
          {
              majuSampaiDepan();
              if(motion>1)
                motion--;
              else if(motion==1)
                motion=4;
              rotateKepala();
              mundurSedikit();delay(delayMundurSedikit);
              flagFollow=1;
              digitalWrite(led,LOW);
              for(int a=0;a<countBoneka41;a++)     //delay untuk cek boneka
              {
                cekBoneka41();
                if(flagBoneka==1)
                {
                  passData(0);digitalWrite(led,HIGH);delay(300);digitalWrite(led,LOW);
                  flagFollow=0;
                  a=countBoneka41;
                  flagLetakBoneka=3;
                  break;
                } 
                else if(flagBoneka==0)
                {
                  flagLetakBoneka=2;
                  followRoomKanan();
                  rotateKepala();
                }
                cekGaris();
                if(flagGaris==1)
                {
                  passData(0);
                  gantiMotion();
                  break;
                }
              }
          }
          else if(awalRoom==42 && jumlahRuang==1) //maju terus follow kanan
          {
            for(int a=0;a<13;a++)   //delay sebelum putar balikcountFollow42
            {
              followKanan();
              cekBoneka();
              cekKosong();
              if(flagStopState==1  && a>10)
              {
                a=13;break;
              }
            }
            gantiMotion();
          }
          else if(awalRoom==11 && jumlahRuang==1)
          {
            mendekatkanKanan();
            for(int a=0;a<countFollow11;a++)     //delay untuk cek boneka
            {
                cekBoneka41();
                if(flagBoneka==1)
                {
                  passData(0);digitalWrite(led,HIGH);delay(300);digitalWrite(led,LOW);
                  flagFollow=1;
                  flagLetakBoneka=1;
                  break;
                }
                else if(flagBoneka==0)
                {
                  flagLetakBoneka=2;
                  followRoomKanan();
                  flagFollow=0;
                }
            }
          }
          flagRoom=1;
          resetGaris();
        }
        else if(flagRoom==1)  // Sudah di lorong dan dapat garis
        {
          passData(0);delay(1000);
          //rotateKepala();
          cekRuang();
//          delay(400);
          resetGaris();
          if(tempRuang==11&&ruang[jumlahRuang-1]==3&&jumlahRuang==3)
          {
            gantiMotion();
            majuSedikit();delay(delayMajuRoom);majuSedikit();delay(delayMajuRoom);
            resetGaris();
            mendekatkanKanan();
            flagFollow=0;
            flagLetakBoneka=1;
            for(int a=0;a<12;a++)     //delay untuk cek boneka
            {
                followRoomKanan();
                if(a>6)
                {
                  if(motion==1)
                  {
                    if(kiri0<2000)
                      break;
                  }
                  else if(motion==2)
                  {
                    if(depan0<2000)
                      break;
                  }
                  else if(motion==3)
                  {
                    if(kanan0<2000)
                      break;
                  }
                  else if(motion==4)
                  {
                    if(belakang0<2000)
                      break;
                  } 
                }
            }
          }
          else
          {
              cekApi();
              if(countError<4)
              {
                if(tempRuang==12)
                {
                  keluar12=0;
                  if(motion==1)
                  {
                    if(belakang0>batasKeluar12&&belakang1>batasKeluar12)
                      keluar12=1;
                  }
                  else if(motion==2)
                  {
                    if(kiri0>batasKeluar12&&kiri1>batasKeluar12)
                      keluar12=1;
                  }
                  else if(motion==3)
                  {
                    if(depan0>batasKeluar12&&depan1>batasKeluar12)
                      keluar12=1;
                  }
                  else if(motion==4)
                  {
                    if(kanan0>batasKeluar12&&kanan1>batasKeluar12)
                      keluar12=1;
                  }
                }
                resetGaris();
                flagFollowRoom=0;
                if(ruangSaatIni==2||ruangSaatIni==3)
                {
                  mendekatkanKiri();
                  for(int a=0;a<6;a++)
                  {
                    followRoomKiri();
                  }
                }
                else if(ruangSaatIni==4)
                {
                  for(int a=0;a<6;a++)
                  {
                    followRoomKiri();
                  }
                }
                else if(ruangSaatIni==1)
                {
                  if(motion==1)
                  {
                    if(keluar12==1)//kanan1<batasSRFruang1)
                    {
                      flagFollowRoom=1;
                    }
                  }
                  else if(motion==2)
                  {
                    if(keluar12==1)//belakang1<batasSRFruang1)
                    {
                      flagFollowRoom=1;
                    }
                  }
                  else if(motion==3)
                  {
                    if(keluar12==1)//kiri1<batasSRFruang1)
                    {
                      flagFollowRoom=1;
                    }
                  }
                  else if(motion==4)
                  {
                    if(keluar12==1)//depan1<batasSRFruang1)
                    {
                      flagFollowRoom=1;
                    }
                  } 
//                  if(flagFollowRoom==0)
//                  {
//                    mendekatkanKiri();
//                  }
//                  else if(flagFollowRoom==1)
//                  {
//                    mendekatkanKanan();
//                  } 
                  for(int a=0;a<6;a++)
                  {
                    if(flagFollowRoom==0)
                    {
                      followRoomKiri();
                    }
                    else if(flagFollowRoom==1)
                    {
                      followRoomKanan();
                    }
                  }
                }
                resetGaris();
                passData(0);
                if(flagApi==0)
                {
                  gantiMotion();
                  while(1)
                  {
                    if(flagFollowRoom==1) //follow kiri
                    {
                      followKiri();
                    }
                    else if(flagFollowRoom==0)  //follow kanan
                    {
                      followKanan();
                    }
                    cekGaris();
                    if(flagGaris==1)
                      break;
                  }
                  if(tempRuang==3 || tempRuang==2)
                    mendekatkanKanan();
                  passData(0);delay(50);               // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                  if(tempRuang==42 || tempRuang==3)
                  {
                    majuSedikit();
                    delay(delayMajuRoom42);passData(0);
                  }
                  else
                  {
                    majuSedikit();
                    delay(delayMajuRoom);passData(0);
                  }
                  resetGaris();
                  flagGaris=0;
                  if(jumlahRuang==2&&startRoom==2&&ruangSaatIni==1)
                  {
                    if(keluar12==0)
                    {
                        majuSampaiDepan();
                        if(motion<4)
                          motion++;
                        else if(motion==4)
                          motion=1;
                        rotateKepala();
                        flagFollow=0; 
                    }
                    else if(keluar12==1)
                    {
                        for(int a=0;a<3;a++)
                        {
                          followRoomKiri();
                        }
                        if(motion<4)
                          motion++;
                        else if(motion==4)
                          motion=1;
                        rotateKepala();
                        flagFollow=0;
                        passData(motion);delay(delayMaju*3);                  
                    }
                  }
                  else if(tempRuang==41 && ruangSaatIni==4)  //maju dulu terus follow kanan, ketemu boneka putar balik jadi follow kiri
                  {
                      majuSampaiDepan();
                      if(motion>1)
                        motion--;
                      else if(motion==1)
                        motion=4;
                      rotateKepala();
                      mundurSedikit();delay(delayMundurSedikit);
                      flagFollow=1;
                      digitalWrite(led,LOW);
                      for(int a=0;a<countBoneka41;a++)     //delay untuk cek boneka
                      {
                        cekBoneka41();
                        if(flagBoneka==1)
                        {
                          passData(0);digitalWrite(led,HIGH);delay(300);digitalWrite(led,LOW);
                          flagFollow=0;
                          a=countBoneka41;
                          flagLetakBoneka=3;
                          break;
                        } 
                        else if(flagBoneka==0)
                        {
                          flagLetakBoneka=2;
                          followRoomKanan();
                        }
                        cekGaris();
                        if(flagGaris==1)
                        {
                          passData(0);
                          gantiMotion();
                          break;
                        }
                      }
                      if(flagBoneka==1 && jumlahRuang==2 && ruang[0]==1 && awalRoom==11)
                      {
                        while(flagDepanKena41==0)
                        {
                          followKiriHome();
                          if(flagDepanKena41==1)
                            break;
                        }
                        flagDepanKena41=0;
                        passData(motion);delay(delayMajuRoom);delay(delayMajuRoom);delay(delayMajuRoom);
                        flagFollow=1;
                      }
                  }
                  else if(tempRuang==42 && ruangSaatIni==4) //maju terus follow kanan
                  {
                    flagGaris=0;
                    for(int a=0;a<13;a++)   //delay sebelum putar balikcountFollow42
                    {
                      followKanan();
                      cekBoneka();
                      cekKosong();
                      if(flagStopState==1  && a>10)
                      {
                        a=13;break;
                      }
                    }
                    gantiMotion();
                    passData(0);
                    flagFollow=1;
                    digitalWrite(led,HIGH);delay(500);digitalWrite(led,LOW);delay(500);
                  }
                  else if(ruangSaatIni==1 && tempRuang==11 && awalRoom!=41 && jumlahRuang>2)
                  {
                    mendekatkanKanan();
                    for(int a=0;a<countFollow11;a++)     //delay untuk cek boneka
                    {
                        cekBoneka41();
                        if(flagBoneka==1)
                        {
                          passData(0);digitalWrite(led,HIGH);delay(300);digitalWrite(led,LOW);
                          flagFollow=1;
                          flagLetakBoneka=1;
                          break;
                        }
                        else if(flagBoneka==0)
                        {
                          flagLetakBoneka=2;
                          followRoomKanan();
                          flagFollow=1;
                        }
                    }
                  }
                  resetGaris();
                }
                else if(flagApi==1)
                {
                  flagTarget=0;
                  flagPointing=0;
                  flagTembok=0;
                  flagDapat=0;
                  passData(0);
                  while(1)
                  {
                    pointing();
                    if(flagTarget==1)
                      break; 
                  }
                  if(flagSearchLagi==1)
                  {
                    flagTarget=0;
                    flagRoom=1;
                    flagSearchLagi=0;
                  }
                  else
                  {
                    cekJalanPulang();
                    gantiMotion();majuSedikit();delay(100);
                    cekTerdekatApi();
                    flagRoom=0;
                  }
                  passData(0);
                  resetGaris();
                  timer=0;
                } 
              }
              else
              {
                countError=0;
                majuSedikit();
                delay(delayMajuRoom);
                passData(0);
                resetGaris();
              }
          }
        }
        digitalWrite(led,LOW);
      }
    }
    else if(flagTarget==1)  //mau balik rumah
    {
      if(flagRoom==1&&flagFollow==0) //sudah di luar ruangan
      {
        cekBoneka();
        cekPerempatan();
        followKiriPulang();
        if(flagSiapPerempatan==1)
        {
          passData(0);
          cekPerempatan();
          flagSiapPerempatan=0;
        }
      }
      else if(flagRoom==1&&flagFollow==1)  //follow kanan
      {
        cekBoneka();
        cekPerempatan();
        followKananPulang();
        if(flagSiapPerempatan==1)
        {
          passData(0);
          cekPerempatan();
          flagSiapPerempatan=0;
        }
      }
      else if(flagRoom==0&&flagFollowRoom==0) //follow kiri
      {
        followRoomKiriFurn();
      }
      else if(flagRoom==0&&flagFollowRoom==1)  //follow kanan
      {
        followRoomKananFurn();
      }
      cekGaris();
      cekGaris();
      if(flagGaris==1)
      {
        digitalWrite(led,HIGH);
        resetGaris();
        if(flagRoom==0)
        {
          majuSedikit();
          delay(delayMajuRoom);
          passData(0); delay(500);
          cekRuang();
          if(tempRuang==3 || tempRuang==2)
          {
            mendekatkanKanan();
          }
          flagRoom=1;
          resetGaris();
          if(tempRuang==41 && jumlahRuangBalik==1)
          {
            //lihat posisi boneka nya, jika di posisi 3, follow kiri dulu baru follow kanan
              majuSampaiDepan();
              if(motion>1)
                motion--;
              else if(motion==1)
                motion=4;
              rotateKepala();
              mundurSedikit();delay(delayMundurSedikit);
              flagFollow=1;
              digitalWrite(led,LOW);
              for(int a=0;a<countBoneka41;a++)     //delay untuk cek boneka
              {
                cekBoneka41();
                if(flagBoneka==1)
                {
                  passData(0);digitalWrite(led,HIGH);delay(300);digitalWrite(led,LOW);
                  flagFollow=0;
                  a=countBoneka41;
                  flagLetakBoneka=3;
                  break;
                } 
                else if(flagBoneka==0)
                {
                  flagLetakBoneka=2;
                  followRoomKanan();
                }
                cekGaris();
                if(flagGaris==1)
                {
                  passData(0);
                  gantiMotion();
                  break;
                }
              }
              if(flagBoneka==1)
              {
                while(flagDepanKena41==0)
                {
                  followKiriHome();
                  if(flagDepanKena41==1)
                    break;
                }
                flagDepanKena41=0;
                passData(motion);delay(delayMajuRoom);delay(delayMajuRoom);delay(delayMajuRoom);
                flagFollow=1;
              }
          }
          else if(tempRuang==42 && jumlahRuangBalik==1)
          {
            majuSampaiDepan();
            if(motion<4)
              motion++;
            else if(motion==4)
              motion=1;
            rotateKepala();
            flagFollow=0; 
          }
          else if(tempRuang==11 && jumlahRuangBalik==1)
          {
            //jika boneka gak di posisi 1, tetap follow kanan terus cek boneka di depan ruang 41, jika ada follow kiri dulu baru kanan.
            //jika boneka di posisi 1, putar balik, follow kanan, terus follow kiri
            gantiMotion();
            mendekatkanKiri();
            for(int a=0;a<10;a++)
            {
              followRoomKiriFurn();
            }
            resetGaris();
            flagRoom=0;
            jumlahRuangBalik=0;
            ruangBalik[0]=0;
          }
          else if(tempRuang==12 && jumlahRuangBalik==1)
          {
            if(tempRuang==12)
            {
              keluar12=0;
              if(motion==1)
              {
                if(depan0>batasKeluar12Pulang&&depan1>batasKeluar12)
                  keluar12=1;
              }
              else if(motion==2)
              {
                if(kanan0>batasKeluar12Pulang&&kanan1>batasKeluar12)
                  keluar12=1;
              }
              else if(motion==3)
              {
                if(belakang0>batasKeluar12Pulang&&belakang1>batasKeluar12)
                  keluar12=1;
              }
              else if(motion==4)
              {
                if(kiri0>batasKeluar12Pulang&&kiri1>batasKeluar12)
                  keluar12=1;
              }
            }
            if(startRoom==3 || startRoom==4)
            {
              if(keluar12==0)
              {
                  majuSampaiDepan();
                  if(motion<4)
                    motion++;
                  else if(motion==4)
                    motion=1;
                  rotateKepala();
                  flagFollow=0; 
              }
              else if(keluar12==1)
              {
                  for(int a=0;a<3;a++)
                  {
                    followRoomKiri();
                  }
                  if(motion<4)
                    motion++;
                  else if(motion==4)
                    motion=1;
                  rotateKepala();
                  flagFollow=0;
                  passData(motion);delay(delayMaju*3);                  
              }
            }
          }
        }
        else if(flagRoom==1)
        {
          passData(0);delay(500);
          //rotateKepala();delay(1200);
          cekRuang();
//          delay(400);
          if(tempRuang==12)
          {
            keluar12=0;
            if(motion==1)
            {
              if(belakang0>batasKeluar12&&belakang1>batasKeluar12)
                keluar12=1;
            }
            else if(motion==2)
            {
              if(kiri0>batasKeluar12&&kiri1>batasKeluar12)
                keluar12=1;
            }
            else if(motion==3)
            {
              if(depan0>batasKeluar12&&depan1>batasKeluar12)
                keluar12=1;
            }
            else if(motion==4)
            {
              if(kanan0>batasKeluar12&&kanan1>batasKeluar12)
                keluar12=1;
            }

            if(keluar12==1)
            {
              majuSedikit();delay(100);
              for(int a=0;a<4;a++)
              {
                followRoomKanan();
              }
              while(1)
                passData(0);
            }
            else if(keluar12==0)
            {
              majuSedikit();delay(100);
              for(int a=0;a<4;a++)
              {
                followRoomKiri();
              }
              while(1)
                passData(0);
            }
          }
          else
          {
            majuSampaiDepan();
            while(1)
              passData(0);
          }
        }
      }
      digitalWrite(led,LOW);
    }
  }
}
