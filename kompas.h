#include <Wire.h>

#define CMPS11_ADDRESS 0x60  // Address of CMPS11 shifted right one bit for arduino wire library
#define ANGLE_8  1           // Register to read 8bit angle from

#define batas1 22         //kiri atas
#define batas2 236        //kiri bawah
#define batas3 187        //kanan atas
#define batas4 112        //kanan bawah

#define batasRoom41 2450
#define batasRoom43 2300
#define batasRoom34Out 1900
#define batasRoom41Out 2800

unsigned char angle8;
int degree=0;

int sudutSaja()
{
    Wire.beginTransmission(CMPS11_ADDRESS);  //starts communication with CMPS11
    Wire.write(ANGLE_8);                     //Sends the register we wish to start reading from
    Wire.endTransmission();
    Wire.requestFrom(CMPS11_ADDRESS, 1);       
    while(Wire.available()<1);        // Wait for all bytes to come back
      angle8 = Wire.read();
    degree=angle8;
    return degree;
}

void cekRuangSaja()
{
    Wire.beginTransmission(CMPS11_ADDRESS);  //starts communication with CMPS11
    Wire.write(ANGLE_8);                     //Sends the register we wish to start reading from
    Wire.endTransmission();
    Wire.requestFrom(CMPS11_ADDRESS, 1);       
    while(Wire.available()<1);        // Wait for all bytes to come back
      angle8 = Wire.read();
    degree=angle8;
    if(flagRoom==0)  //checkout
    {
      if(degree<=111 && degree>79)//((degree>=0 && degree<=33)||(degree<=255 && degree>227))
      {
        if(motion==1)
        {
          if(kanan0<batasRoom34Out)
            tempRuang=3;
          else
            tempRuang=42;
        }
        else if(motion==2)
        {
          if(belakang0<batasRoom34Out)
            tempRuang=3;
          else
            tempRuang=42;
        }
        else if(motion==3)
        {
          if(kiri0<batasRoom34Out)
            tempRuang=3;
          else
            tempRuang=42;
        }
        else if(motion==4)
        {
          if(depan0<batasRoom34Out)
            tempRuang=3;
          else
            tempRuang=42;
        }
      }
      else if((degree>=0 && degree<=79)||(degree<=255 && degree>235))//(degree<=227 && degree>162)
      {
        tempRuang=2;
      }
      else if(degree<=235 && degree>133)
      {
        if(motion==1)
        {
          if(depan1<batasRoom41Out)
            tempRuang=41;
          else
            tempRuang=11;
        }
        else if(motion==2)
        {
          if(kanan1<batasRoom41Out)
            tempRuang=41;
          else
            tempRuang=11;
        }
        else if(motion==3)
        {
          if(belakang1<batasRoom41Out)
            tempRuang=41;
          else
            tempRuang=11;
        }
        else if(motion==4)
        {
          if(kiri1<batasRoom41Out)
            tempRuang=41;
          else
            tempRuang=11;
        }
      }
      else if(degree<=133 && degree>111)
      {
        tempRuang=12;
      }
    }
    else if(flagRoom==1) //checkin
    {
      if(degree<=111 && degree>79)
      {
        if(motion==1)
        {
          if(depan0<batasRoom41)
            tempRuang=41;
          else
            tempRuang=11;
        }
        else if(motion==2)
        {
          if(kanan0<batasRoom41)
            tempRuang=41;
          else
            tempRuang=11;
        }
        else if(motion==3)
        {
          if(belakang0<batasRoom41)
            tempRuang=41;
          else
            tempRuang=11;
        }
        else if(motion==4)
        {
          if(kiri0<batasRoom41)
            tempRuang=41;
          else
            tempRuang=11;
        }
      }
      else if((degree>=0 && degree<=79)||(degree<=255 && degree>235))
      {
        tempRuang=12;
      }
      else if(degree<=235 && degree>133)
      {
        if(motion==1)
        {
          if(depan0<batasRoom43)
            tempRuang=42;
          else
            tempRuang=3;
        }
        else if(motion==2)
        {
          if(kanan0<batasRoom43)
            tempRuang=42;
          else
            tempRuang=3;
        }
        else if(motion==3)
        {
          if(belakang0<batasRoom43)
            tempRuang=42;
          else
            tempRuang=3;
        }
        else if(motion==4)
        {
          if(kiri0<batasRoom43)
            tempRuang=42;
          else
            tempRuang=3;
        }
      }
      else if(degree<=133 && degree>111)
      {
        tempRuang=2;
      }
    }
    Serial.println(tempRuang);
}

void cekRuangAwal()
{
     //baca nilai kompas, tentukan ruang berapa, store ke array ruang[]
    cekRuangSaja();
    if(beforeTempRuang==0)
    {
      beforeTempRuang=tempRuang;
      countError=0;
    }
    else
    {
      if(beforeTempRuang==tempRuang)
        countError++;
      else
        beforeTempRuang=0;
//      if(countError==2)
//      {
//        for(int a=0;a<2;a++)
//        {
//          //keluar paksa
//          majuSedikit();
//          delay(delayMajuRoom);
//        }
//        flagRoom=1;
//        countError=0;
//      }  
    }  
//    Serial.println(angle8);
//    Serial.println(tempRuang);
}

void cekRuang()
{
    cekRuangSaja();
    cekRuangSaja();
    if(beforeTempRuang==0)
    {
      beforeTempRuang=tempRuang;
      countError=0;
    }
    else
    {
      if(beforeTempRuang==tempRuang)
        countError++;
      else
        beforeTempRuang=0;  
    }
    if(tempRuang==11 || tempRuang==12)
      ruangSaatIni=1;
    else if(tempRuang==41 || tempRuang==42)
      ruangSaatIni=4;
    else
      ruangSaatIni=tempRuang;
    int a=0,b=0;
    if(flagTarget==0)
    {
      for(a=0;a<jumlahRuang;a++)
      {
        if(ruang[a]==ruangSaatIni)
          b=1;
      }      
    }
    else if(flagTarget==1)
    {
      for(a=0;a<jumlahRuangBalik;a++)
      {
        if(ruangBalik[a]==ruangSaatIni)
          b=1;
      }      
    }
    if(flagTarget==0)
    {
      if(b==1)
      {
        if(ruang[jumlahRuang-1]==1)
        {
          tempRuang==5;
          ruangSaatIni=3;
        }
      }
    }
    if(b==0 && flagTarget==0)
    {
      ruang[jumlahRuang]=ruangSaatIni;
      EEPROM.write(jumlahRuang, ruangSaatIni);
      if(jumlahRuang==0)
      {
        startRoom=ruangSaatIni;
        awalRoom=tempRuang;
        if(startRoom==2 || startRoom==3 || (startRoom==1&&tempRuang==11))
        {
          flagFollow=1;        
        }
        else if(startRoom==1&&tempRuang==12)
        {
          flagFollow=0;
        }
        else if(startRoom==4)
        {
          flagFollow=1;
        }
      }
      jumlahRuang++;
    }
    else if(b==0 && flagTarget==1)
    {
      ruangBalik[jumlahRuangBalik]=ruangSaatIni;
      EEPROM.write(jumlahRuangBalik+5, ruangSaatIni);
      jumlahRuangBalik++;
    }  
//    for(int aa=0;aa<ruangSaatIni;aa++)
//    {
//      passData(0);
//      delay(1000);
//      digitalWrite(led,HIGH);
//      delay(500);
//      digitalWrite(led,LOW);
//      delay(500);
//    }
    Serial.println(angle8);
}



//+++++++++++++++++++++++++++++++++++++++++++++++ Buat Return Home
void cekRuangReturn()
{
    Wire.beginTransmission(CMPS11_ADDRESS);  //starts communication with CMPS11
    Wire.write(ANGLE_8);                     //Sends the register we wish to start reading from
    Wire.endTransmission();
    Wire.requestFrom(CMPS11_ADDRESS, 1);       
    while(Wire.available()<1);        // Wait for all bytes to come back
      angle8 = Wire.read();
    degree=angle8;
    // pakainya yang checkout
    if(degree<=111 && degree>79)
    {
      tempRuang=3;
    }
    else if((degree>=0 && degree<=79)||(degree<=255 && degree>235))//(degree<=227 && degree>162)
    {
      tempRuang=2;
    }
    else if(degree<=235 && degree>133)
    {
      tempRuang=4;
    }
    else if(degree<=133 && degree>111)
    {
      tempRuang=1;
    }
}
