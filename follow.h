#define delayBelok 14    //maju sedikit sebelum belok biar gak nabrak                        ubahSpeed
#define delayBelokKiri 13    //maju sedikit sebelum belok biar gak nabrak                        ubahSpeed
#define delayGeser 1    //untuk gerak geser                        ubahSpeed
#define delayGeserMendekatkan 30    //untuk gerak geser                        ubahSpeed

#define delayGeserSedikit 1   //untuk pivot memperbaiki       ubahSpeed

#define delayMaju 500     //maju sedikit keluar dari room                        ubahSpeed
#define delayMajuRoom 240 //230
#define delayMajuRoom42 280
#define delayMaju12 (delayMaju*1.8)
#define delayBatasCount 6                    //                      ubahSpeed
#define delayBatasCountHome 10                    //                      ubahSpeed

#define delayMajuBoneka 100

#define batasBenerinKananAtas 140 //140
#define batasBenerinKananBawah -160
#define batasBenerinBelakangAtas 140
#define batasBenerinBelakangBawah -160
#define batasBenerinKiriAtas 140
#define batasBenerinKiriBawah -160
#define batasBenerinDepanAtas 140
#define batasBenerinDepanBawah -160

//#define batasBenerinKananAtas 175 //140
//#define batasBenerinKananBawah -175
//#define batasBenerinBelakangAtas 175
//#define batasBenerinBelakangBawah -175
//#define batasBenerinKiriAtas 175
//#define batasBenerinKiriBawah -175
//#define batasBenerinDepanAtas 175
//#define batasBenerinDepanBawah -175

#define batasBenerinKananAtasRoom 130 //120
#define batasBenerinKananBawahRoom -150
#define batasBenerinBelakangAtasRoom 130
#define batasBenerinBelakangBawahRoom -150
#define batasBenerinKiriAtasRoom 130
#define batasBenerinKiriBawahRoom -150
#define batasBenerinDepanAtasRoom 130
#define batasBenerinDepanBawahRoom -150

#define batasLurus 1000 //batas sebelum mendapat tembok lagi
//#define batasDekat 600  //
#define batasSerong 1500  //batas maksimum untuk bergerak serong        1500
#define batasSerongFurn 1200  //batas maksimum untuk bergerak serong        1500
#define batasCount 32 //count sebelum belok lagi                        ubahSpeed
#define batasCountHome 35 //count sebelum belok lagi                        ubahSpeed
#define batasDepan 580

#define lossBoneka 1400             //1600
#define lossBoneka41 900

#define countBoneka41 18
#define countFollow42 11
#define countFollow11 12
void rotateKepala();
void sync(int);

int batasMendekatkan=880; //batas untuk mendekatkan diri ke tembok
int batasMenjauhkan=280; //batas untuk menjauhkan diri dari tembok
int batasBelok=2500;  //batas sebelum berbelok

int motion=0; // 0 = stop, 1 = maju, 2 = kanan, 3 = mundur, 4 = kiri, 5 = putar kiri, 6 = putar kanan, 16 = down speed, 17 = up speed
int selisihKanan=0;
int selisihBelakang=0;
int selisihKiri=0;
int selisihDepan=0;

int counterBelok=0;

void mendekatkanKanan()
{
  if(motion==1)
  {
    if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong) /////
    {
      passData(2);
      delay(delayGeserMendekatkan);
    }
  }
  else if(motion==2)
  {
    if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan   && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeserMendekatkan);
    }
  }
  else if(motion==3)
  {
    if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeserMendekatkan);
    }
  }
  else if(motion==4)
  {
    if(depan0>batasMendekatkan&&depan1>batasMendekatkan && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeserMendekatkan);
    }
  }
}

void mendekatkanKiri()
{
  if(motion==1)
  {
    if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeserMendekatkan);
    }
  }
  else if(motion==2)
  {
    if(depan0>batasMendekatkan&&depan1>batasMendekatkan   && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeserMendekatkan);
    }
  }
  else if(motion==3)
  {
    if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(2);
      delay(delayGeserMendekatkan);
    }
  }
  else if(motion==4)
  {
    if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeserMendekatkan);
    }
  }
}

void majuSampaiDepan()
{
    for(int a=0;a<20;a++)
    {
      if(motion==1)
      {
        passData(1);
        if(depan0<batasDepan||depan1<batasDepan)
          break; 
      }
      else if(motion==2)
      {
        passData(2);
        if(kanan0<batasDepan||kanan1<batasDepan)
          break;
      }
      else if(motion==3)
      {
        passData(3);
        if(belakang0<batasDepan||belakang1<batasDepan)
          break;
      }
      else if(motion==4)
      {
        passData(4);
        if(kiri0<batasDepan||kiri1<batasDepan)
          break;
      }
    }
}
void cekKosong()
{
  flagStopState=0;
  if(motion==1)
  {
    if(kanan0>batasBelok)
      flagStopState=1;
  }
  else if(motion==2)
  {
    if(belakang0>batasBelok)
      flagStopState=1;
  }
  else if(motion==3)
  {
    if(kiri0>batasBelok)
      flagStopState=1;
  }
  else if(motion==4)
  {
    if(depan0>batasBelok)
      flagStopState=1;
  }
}
void speedUp()
{
  for(int a=0;a<2;a++)
  {
    passData(11);
    delay(150);
  }
}

void speedDown()
{
  for(int a=0;a<2;a++)  //passData(10) kecepatan 20   passData(12) kecepatan 15   passData(11) kecepatan 10
  {
    passData(12);
    delay(150);
  }
}

void cekBoneka41()
{
    flagBoneka=0;
    if(motion==1)
    {
      if(ir1==LOW&&(depan0>lossBoneka41||depan0==0)&&(depan1>lossBoneka41||depan1==0))
      {
        flagBoneka=1;
        passData(0);motion=3;rotateKepala();
        passData(motion);delay(delayMajuBoneka);passData(0);
      }
    }
    else if(motion==2)
    {
      if(ir2==LOW&&(kanan0>lossBoneka41||kanan0==0)&&(kanan1>lossBoneka41||kanan1==0))
      {
        flagBoneka=1;
        passData(0);motion=4;rotateKepala();
        passData(motion);delay(delayMajuBoneka);passData(0);
      }
    }
    else if(motion==3)
    {
      if(ir3==LOW&&(belakang0>lossBoneka41||belakang0==0)&&(belakang1>lossBoneka41||belakang1==0))
      {
        flagBoneka=1;
        passData(0);motion=1;rotateKepala();
        passData(motion);delay(delayMajuBoneka);passData(0);
      }
    }
    else if(motion==4)
    {
      if(ir4==LOW&&(kiri0>lossBoneka41||kiri0==0)&&(kiri1>lossBoneka41||kiri1==0))
      {
        flagBoneka=1;
        passData(0);motion=2;rotateKepala();
        passData(motion);delay(delayMajuBoneka);passData(0);
      }
    }
}

void cekBoneka()
{
    flagBoneka=0;
    if(motion==1)
    {
      if(ir1==LOW&&(depan0>lossBoneka||depan0==0)&&(depan1>lossBoneka||depan1==0))
      {
        flagBoneka=1;
        passData(0);motion=3;rotateKepala();
        passData(motion);delay(delayMajuBoneka);passData(0);
      }
    }
    else if(motion==2)
    {
      if(ir2==LOW&&(kanan0>lossBoneka||kanan0==0)&&(kanan1>lossBoneka||kanan1==0))
      {
        flagBoneka=1;
        passData(0);motion=4;rotateKepala();
        passData(motion);delay(delayMajuBoneka);passData(0);
      }
    }
    else if(motion==3)
    {
      if(ir3==LOW&&(belakang0>lossBoneka||belakang0==0)&&(belakang1>lossBoneka||belakang1==0))
      {
        flagBoneka=1;
        passData(0);motion=1;rotateKepala();
        passData(motion);delay(delayMajuBoneka);passData(0);
      }
    }
    else if(motion==4)
    {
      if(ir4==LOW&&(kiri0>lossBoneka||kiri0==0)&&(kiri1>lossBoneka||kiri1==0))
      {
        flagBoneka=1;
        passData(0);motion=2;rotateKepala();
        passData(motion);delay(delayMajuBoneka);passData(0);
      }
    }
    if(flagBoneka==1&&jumlahRuang==1&&ruang[jumlahRuang-1]==1&&flagFollow==0&&awalRoom==11)
    {
      flagLetakBoneka==3;
      flagFollow=1;
    }
}

void rotateKepala()
{
  for(int i=0;i<2;i++)
  {
    if(motion==1)
    {
      pos=2040;
      sync(pos);
    }
    else if(motion==2)
    {
      pos=1015;
      sync(pos);
    }
    else if(motion==3)
    {
      if(pos<=2040)
      {
          pos=1;
          sync(pos); 
      }
      else
      {
          pos=4094;
          sync(pos);
      }
    }
    else if(motion==4)
    {
      pos=3064;
      sync(pos);
    }
  }
}

void gantiMotion()
{
  if(motion==1)
  {
    motion=3;
  }
  else if(motion==2)
  {
    motion=4;
  }
  else if(motion==3)
  {
    motion=1;
  }
  else if(motion==4)
  {
    motion=2;
  }
  rotateKepala();
}

void gantiMotionCW()
{
  if(motion==1)
  {
    motion=2;
  }
  else if(motion==2)
  {
    motion=3;
  }
  else if(motion==3)
  {
    motion=4;
  }
  else if(motion==4)
  {
    motion=1;
  }
  rotateKepala();
}

void gantiMotionCCW()
{
  if(motion==1)
  {
    motion=4;
  }
  else if(motion==2)
  {
    motion=1;
  }
  else if(motion==3)
  {
    motion=2;
  }
  else if(motion==4)
  {
    motion=3;
  }
  rotateKepala();
}

void majuSedikit()
{
  if(motion==1)
  {
    passData(1);
  }
  else if(motion==2)
  {
    passData(2);
  }
  else if(motion==3)
  {
    passData(3);
  }
  else if(motion==4)
  {
    passData(4);
  }
}

void mundurSedikit()
{
  if(motion==1)
  {
    passData(3);
  }
  else if(motion==2)
  {
    passData(4);
  }
  else if(motion==3)
  {
    passData(1);
  }
  else if(motion==4)
  {
    passData(2);
  }
}

void cekTerdekatApi()
{
  int cek[4],temp=0, tempIndex=0;
  cek[0]=(depan0+depan1);
  cek[1]=(kanan0+kanan1);
  cek[2]=(belakang0+belakang1);
  cek[3]=(kiri0+kiri1);

  temp=cek[0];
  for(int b=1;b<4;b++)
  {
    if(cek[b]<temp)
    {
      tempIndex=b;
      temp=cek[b]; 
    }
  }
  if(tempIndex==0)
  {
    motion=2;
    flagFollowRoom=0;
  }
  else if(tempIndex==1)
  {
    motion=1;
    flagFollowRoom=1;
  }
  else if(tempIndex==2)
  {
    motion=4;
    flagFollowRoom=0;
  }
  else if(tempIndex==3)
  {
    motion=1;
    flagFollowRoom=0;
  }
}

void cekTerdekat()
{
  int cek[8],temp=0, tempIndex=0;
  cek[0]=depan0;
  cek[1]=depan1;
  cek[2]=kanan0;
  cek[3]=kanan1;
  cek[4]=belakang0;
  cek[5]=belakang1;
  cek[6]=kiri0;
  cek[7]=kiri1;

  temp=cek[0];
  for(int b=1;b<8;b++)
  {
    if(cek[b]<temp)
    {
      tempIndex=b;
      temp=cek[b]; 
    }
  }
  if(tempIndex==0 || tempIndex==1)
  {
    motion=2;
    flagFollowRoom=0;
  }
  else if(tempIndex==2 || tempIndex==3)
  {
    motion=1;
    flagFollowRoom=1;
  }
  else if(tempIndex==4 || tempIndex==5)
  {
    motion=4;
    flagFollowRoom=0;
  }
  else if(tempIndex==6 || tempIndex==7)
  {
    motion=1;
    flagFollowRoom=0;
  }
  rotateKepala();
}

void mauSerongKanan()
{
  if(motion==1)
  {
//    passData(2);delay(delayGeserSedikit);
    passData(8);delay(delayGeserSedikit);  
//    passData(1);delay(delayGeserSedikit2);
  }
  else if(motion==2)
  {
//    passData(3);delay(delayGeserSedikit);
    passData(8);delay(delayGeserSedikit);  
//    passData(2);delay(delayGeserSedikit2);
  }
  else if(motion==3)
  {
//    passData(4);delay(delayGeserSedikit);  
    passData(8);delay(delayGeserSedikit);
//    passData(3);delay(delayGeserSedikit2);
  }
  else if(motion==4)
  {
//    passData(1);delay(delayGeserSedikit);  
    passData(8);delay(delayGeserSedikit);
//    passData(4);delay(delayGeserSedikit2);
  }
}

void mauSerongKiri()
{
  if(motion==1)
  {
//    passData(4);delay(delayGeserSedikit); 
    passData(9);delay(delayGeserSedikit); 
//    passData(1);delay(delayGeserSedikit2);
  }
  else if(motion==2)
  {
//    passData(1);delay(delayGeserSedikit);  
    passData(9);delay(delayGeserSedikit);
//    passData(2);delay(delayGeserSedikit2);
  }
  else if(motion==3)
  {
//    passData(2);delay(delayGeserSedikit); 
    passData(9);delay(delayGeserSedikit); 
//    passData(3);delay(delayGeserSedikit2);
  }
  else if(motion==4)
  {
//    passData(3);delay(delayGeserSedikit);  
    passData(9);delay(delayGeserSedikit);
//    passData(4);delay(delayGeserSedikit2);
  }
}

void followKanan()
{
  batasMenjauhkan=260;
  batasMendekatkan=770;
  if(motion==1)
  { 
    selisihKanan=kanan0-kanan1;
    if(selisihKanan<batasBenerinKananBawah  && kanan0<batasSerong && kanan1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihKanan>batasBenerinKananAtas  && kanan0<batasSerong && kanan1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKanan();
    } 
    else if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong) /////
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    } 
    else 
    {
      passData(1);  
    }
//    if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong)
//    {
//      passData(2);
//      delay(delayGeser);
//    }
//    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
//    {
//      passData(4);
//      delay(delayGeser);
//    }
    if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      countKejebak++;
      passData(1);
      delay(delayBelok);
      counterBelok=0;
      motion=2;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(depan0<batasDepan || depan1<batasDepan)
    {
      motion=4;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihBelakang=belakang0-belakang1;
    if(selisihBelakang<batasBenerinBelakangBawah  && belakang0<batasSerong  && belakang1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihBelakang>batasBenerinBelakangAtas  && belakang0<batasSerong  && belakang1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan   && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan   && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }    
    else
    {
      passData(2);
    }
//    if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan   && belakang0<batasSerong  && belakang1<batasSerong)
//    {
//      passData(3);
//      delay(delayGeser);
//    }
//    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan   && belakang0<batasSerong  && belakang1<batasSerong)
//    {
//      passData(1);
//      delay(delayGeser);
//    }
    if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      countKejebak++;
      passData(2);
      delay(delayBelok);
      counterBelok=0;
      motion=3;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(kanan0<batasDepan || kanan1<batasDepan)
    {
        motion=1;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKiri=kiri0-kiri1;
    if(selisihKiri<batasBenerinKiriBawah  && kiri0<batasSerong && kiri1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihKiri>batasBenerinKiriAtas  && kiri0<batasSerong && kiri1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKanan();
    }  
    else if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }  
    else
    {
      passData(3);
    }
//    if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
//    {
//      passData(4);
//      delay(delayGeser);
//    }
//    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
//    {
//      passData(2);
//      delay(delayGeser);
//    }
    if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      countKejebak++;
      passData(3);
      delay(delayBelok);
      counterBelok=0;
      motion=4;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(belakang0<batasDepan || belakang1<batasDepan)
    {
        motion=2;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihDepan=depan0-depan1;
    if(selisihDepan<batasBenerinDepanBawah  && depan0<batasSerong  && depan1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihDepan>batasBenerinDepanAtas  && depan0<batasSerong && depan1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKanan();
    }   
    else if(depan0>batasMendekatkan&&depan1>batasMendekatkan && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else
    {
      passData(4); 
    }
//    if(depan0>batasMendekatkan&&depan1>batasMendekatkan && depan0<batasSerong  && depan1<batasSerong)
//    {
//      passData(1);
//      delay(delayGeser);
//    }
//    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan && depan0<batasSerong  && depan1<batasSerong)
//    {
//      passData(3);
//      delay(delayGeser);
//    }
    if(depan0>batasBelok&&depan1>batasBelok)
    {
      countKejebak++;
      passData(4);
      delay(delayBelok);
      counterBelok=0;
      motion=1;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(kiri0<batasDepan || kiri1<batasDepan)
    {
        motion=3;rotateKepala();
    }
  }
}
void followKiri()
{
  batasMenjauhkan=240;
  batasMendekatkan=770;
  if(motion==1)
  { 
    selisihKiri=kiri1-kiri0;
    if(selisihKiri<batasBenerinKiriBawah  && kiri0<batasSerong && kiri1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihKiri>batasBenerinKiriAtas  && kiri0<batasSerong && kiri1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiri();
    }  
    else if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    else 
    {
      passData(1);  
    }
    if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      countKejebak++;
      passData(1);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=4;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(depan0<batasDepan || depan1<batasDepan)
    {
      motion=2;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihDepan=depan1-depan0;
    if(selisihDepan<batasBenerinDepanBawah  && depan0<batasSerong  && depan1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihDepan>batasBenerinDepanAtas  && depan0<batasSerong  && depan1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiri();
    }   
    else if(depan0>batasMendekatkan&&depan1>batasMendekatkan   && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan   && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    } 
    else
    {
      passData(2);
    }
    if(depan0>batasBelok&&depan1>batasBelok)
    {
      countKejebak++;
      passData(2);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=1;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(kanan0<batasDepan || kanan1<batasDepan)
    {
        motion=3;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKanan=kanan1-kanan0;
    if(selisihKanan<batasBenerinKananBawah  && kanan0<batasSerong && kanan1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihKanan>batasBenerinKananAtas  && kanan0<batasSerong && kanan1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiri();
    }    
    else if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else
    {
      passData(3);
    }
    if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      countKejebak++;
      passData(3);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=2;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(belakang0<batasDepan || belakang1<batasDepan)
    {
        motion=4;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihBelakang=belakang1-belakang0;
    if(selisihBelakang<batasBenerinBelakangBawah  && belakang0<batasSerong  && belakang1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihBelakang>batasBenerinBelakangAtas  && belakang0<batasSerong && belakang1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiri();
    }   
    else if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else
    {
      passData(4); 
    }
    if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      countKejebak++;
      passData(4);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=3;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(kiri0<batasDepan || kiri1<batasDepan)
    {
        motion=1;rotateKepala();
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////follow Room
void followRoomKanan()
{
  batasMenjauhkan=260;
  batasMendekatkan=750;
  if(motion==1)
  { 
    selisihKanan=kanan0-kanan1;
    if(selisihKanan<batasBenerinKananBawahRoom  && kanan0<batasSerong && kanan1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihKanan>batasBenerinKananAtasRoom  && kanan0<batasSerong && kanan1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKanan();
    }  
    else if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else 
    {
      passData(1);  
    }
    
    if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      passData(1);
      delay(delayBelok);
      counterBelok=0;
      motion=2;
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
      passData(0);rotateKepala();
    }
    else if(depan0<batasDepan || depan1<batasDepan)
    {
      motion=4;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihBelakang=belakang0-belakang1;
    if(selisihBelakang<batasBenerinBelakangBawahRoom  && belakang0<batasSerong  && belakang1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihBelakang>batasBenerinBelakangAtasRoom  && belakang0<batasSerong  && belakang1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan   && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan   && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }    
    else
    {
      passData(2);
    }
    
    if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      passData(2);
      delay(delayBelok);
      counterBelok=0;
      motion=3;
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
      passData(0);rotateKepala();
    }
    else if(kanan0<batasDepan || kanan1<batasDepan)
    {
        motion=1;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKiri=kiri0-kiri1;
    if(selisihKiri<batasBenerinKiriBawahRoom  && kiri0<batasSerong && kiri1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihKiri>batasBenerinKiriAtasRoom  && kiri0<batasSerong && kiri1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKanan();
    }  
    else if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }  
    else
    {
      passData(3);
    }
    
    if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      passData(3);
      delay(delayBelok);
      counterBelok=0;
      motion=4;
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
      passData(0);rotateKepala();
    }
    else if(belakang0<batasDepan || belakang1<batasDepan)
    {
        motion=2;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihDepan=depan0-depan1;
    if(selisihDepan<batasBenerinDepanBawahRoom  && depan0<batasSerong  && depan1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihDepan>batasBenerinDepanAtasRoom  && depan0<batasSerong && depan1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKanan();
    }   
    else if(depan0>batasMendekatkan&&depan1>batasMendekatkan && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else
    {
      passData(4); 
    }
    
    if(depan0>batasBelok&&depan1>batasBelok)
    {
      passData(4);
      delay(delayBelok);
      counterBelok=0;
      motion=1;
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
      passData(0);rotateKepala();
    }
    else if(kiri0<batasDepan || kiri1<batasDepan)
    {
        motion=3;rotateKepala();
    }
  }
}

void followRoomKiri()
{
  batasMenjauhkan=260;
  batasMendekatkan=750;
  if(motion==1)
  { 
    selisihKiri=kiri1-kiri0;
    if(selisihKiri<batasBenerinKiriBawahRoom  && kiri0<batasSerong && kiri1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihKiri>batasBenerinKiriAtasRoom  && kiri0<batasSerong && kiri1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiri();
    }  
    else if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    else 
    {
      passData(1);  
    }
    
    if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      passData(1);
      delay(delayBelok);
      counterBelok=0;
      motion=4;
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
      passData(0);rotateKepala();
    }
    else if(depan0<batasDepan || depan1<batasDepan)
    {
      motion=2;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihDepan=depan1-depan0;
    if(selisihDepan<batasBenerinDepanBawahRoom  && depan0<batasSerong  && depan1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihDepan>batasBenerinDepanAtasRoom  && depan0<batasSerong  && depan1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiri();
    }  
    else if(depan0>batasMendekatkan&&depan1>batasMendekatkan   && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan   && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }  
    else
    {
      passData(2);
    }
    
    if(depan0>batasBelok&&depan1>batasBelok)
    {
      passData(2);
      delay(delayBelok);
      counterBelok=0;
      motion=1;
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
      passData(0);rotateKepala();
    }
    else if(kanan0<batasDepan || kanan1<batasDepan)
    {
        motion=3;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKanan=kanan1-kanan0;
    if(selisihKanan<batasBenerinKananBawahRoom  && kanan0<batasSerong && kanan1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihKanan>batasBenerinKananAtasRoom  && kanan0<batasSerong && kanan1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiri();
    }  
    else if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }  
    else
    {
      passData(3);
    }
    
    if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      passData(3);
      delay(delayBelok);
      counterBelok=0;
      motion=2;
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
      passData(0);rotateKepala();
    }
    else if(belakang0<batasDepan || belakang1<batasDepan)
    {
        motion=4;rotateKepala();
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihBelakang=belakang1-belakang0;
    if(selisihBelakang<batasBenerinBelakangBawahRoom  && belakang0<batasSerong  && belakang1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihBelakang>batasBenerinBelakangAtasRoom  && belakang0<batasSerong && belakang1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiri();
    }  
    else if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    } 
    else
    {
      passData(4); 
    }
    
    if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      passData(4);
      delay(delayBelok);
      counterBelok=0;
      motion=3;
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
      passData(0);rotateKepala();
    }
    else if(kiri0<batasDepan || kiri1<batasDepan)
    {
        motion=1;rotateKepala();
    }
  }
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++furniture
void followRoomKananFurn()
{
  batasMenjauhkan=240;
  batasMendekatkan=750;
  if(motion==1)
  { 
    selisihKanan=kanan0-kanan1;
    if(selisihKanan<batasBenerinKananBawahRoom  && kanan0<batasSerong && kanan1<batasSerongFurn)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihKanan>batasBenerinKananAtasRoom  && kanan0<batasSerong && kanan1<batasSerongFurn)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKanan();
    }  
    else if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerongFurn)
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerongFurn)
    {
      passData(4);
      delay(delayGeser);
    }
    else 
    {
      passData(1);  
    }
    
    if(depan0<batasDepan || depan1<batasDepan)
    {
      motion=4;rotateKepala();
    }
    else if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      countKejebak++;
      passData(1);
      delay(delayBelok);
      counterBelok=0;
      motion=2;
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
      passData(0);rotateKepala();
    }
    if(countKejebak==4)
    {
      countKejebak=0;
//      if(flagFollowRoom==1)
//        flagFollowRoom=0;
//      else if(flagFollowRoom==0)
//        flagFollowRoom=1;
      gantiMotion();
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihBelakang=belakang0-belakang1;
    if(selisihBelakang<batasBenerinBelakangBawahRoom  && belakang0<batasSerong  && belakang1<batasSerongFurn)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihBelakang>batasBenerinBelakangAtasRoom  && belakang0<batasSerong  && belakang1<batasSerongFurn)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKanan();
    } 
    else if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan   && belakang0<batasSerong  && belakang1<batasSerongFurn)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan   && belakang0<batasSerong  && belakang1<batasSerongFurn)
    {
      passData(1);
      delay(delayGeser);
    }   
    else
    {
      passData(2);
    }
    
    if(kanan0<batasDepan || kanan1<batasDepan)
    {
        motion=1;rotateKepala();
    }
    else if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      countKejebak++;
      passData(2);
      delay(delayBelok);
      counterBelok=0;
      motion=3;
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
      passData(0);rotateKepala();
    }
    if(countKejebak==4)
    {
      countKejebak=0;
//      if(flagFollowRoom==1)
//        flagFollowRoom=0;
//      else if(flagFollowRoom==0)
//        flagFollowRoom=1;
      gantiMotion();
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKiri=kiri0-kiri1;
    if(selisihKiri<batasBenerinKiriBawahRoom  && kiri0<batasSerong && kiri1<batasSerongFurn)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihKiri>batasBenerinKiriAtasRoom  && kiri0<batasSerong && kiri1<batasSerongFurn)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKanan();
    } 
    else if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerongFurn)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerongFurn)
    {
      passData(2);
      delay(delayGeser);
    }   
    else
    {
      passData(3);
    }
    
    if(belakang0<batasDepan || belakang1<batasDepan)
    {
        motion=2;rotateKepala();
    }
    else if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      countKejebak++;
      passData(3);
      delay(delayBelok);
      counterBelok=0;
      motion=4;
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
      passData(0);rotateKepala();
    }
    if(countKejebak==4)
    {
      countKejebak=0;
//      if(flagFollowRoom==1)
//        flagFollowRoom=0;
//      else if(flagFollowRoom==0)
//        flagFollowRoom=1;
      gantiMotion();
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihDepan=depan0-depan1;
    if(selisihDepan<batasBenerinDepanBawahRoom  && depan0<batasSerong  && depan1<batasSerongFurn)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihDepan>batasBenerinDepanAtasRoom  && depan0<batasSerong && depan1<batasSerongFurn)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKanan();
    }  
    else if(depan0>batasMendekatkan&&depan1>batasMendekatkan && depan0<batasSerong  && depan1<batasSerongFurn)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan && depan0<batasSerong  && depan1<batasSerongFurn)
    {
      passData(3);
      delay(delayGeser);
    } 
    else
    {
      passData(4); 
    }
    
    if(kiri0<batasDepan || kiri1<batasDepan)
    {
        motion=3;rotateKepala();
    }
    else if(depan0>batasBelok&&depan1>batasBelok)
    {
      countKejebak++;
      passData(4);
      delay(delayBelok);
      counterBelok=0;
      motion=1;
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
      passData(0);rotateKepala();
    }
    if(countKejebak==4)
    {
      countKejebak=0;
//      if(flagFollowRoom==1)
//        flagFollowRoom=0;
//      else if(flagFollowRoom==0)
//        flagFollowRoom=1;
      gantiMotion();
    }
  }
}

void followRoomKiriFurn()
{
  batasMenjauhkan=240;
  batasMendekatkan=750;
  if(motion==1)
  { 
    selisihKiri=kiri1-kiri0;
    if(selisihKiri<batasBenerinKiriBawahRoom  && kiri0<batasSerong && kiri1<batasSerongFurn)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihKiri>batasBenerinKiriAtasRoom  && kiri0<batasSerong && kiri1<batasSerongFurn)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiri();
    }  
    else if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerongFurn)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerongFurn)
    {
      passData(2);
      delay(delayGeser);
    }
    else 
    {
      passData(1);  
    }
    
    if(depan0<batasDepan || depan1<batasDepan)
    {
      motion=2;rotateKepala();
    }
    else if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      countKejebak++;
      passData(1);
      delay(delayBelok);
      counterBelok=0;
      motion=4;
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
      passData(0);rotateKepala();
    }
    if(countKejebak==4)
    {
      countKejebak=0;
//      if(flagFollowRoom==1)
//        flagFollowRoom=0;
//      else if(flagFollowRoom==0)
//        flagFollowRoom=1;
      gantiMotion();
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihDepan=depan1-depan0;
    if(selisihDepan<batasBenerinDepanBawahRoom  && depan0<batasSerong  && depan1<batasSerongFurn)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihDepan>batasBenerinDepanAtasRoom  && depan0<batasSerong  && depan1<batasSerongFurn)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiri();
    }  
    else if(depan0>batasMendekatkan&&depan1>batasMendekatkan   && depan0<batasSerong  && depan1<batasSerongFurn)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan   && depan0<batasSerong  && depan1<batasSerongFurn)
    {
      passData(3);
      delay(delayGeser);
    }  
    else
    {
      passData(2);
    }
    
    if(kanan0<batasDepan || kanan1<batasDepan)
    {
        motion=3;rotateKepala();
    }
    else if(depan0>batasBelok&&depan1>batasBelok)
    {
      countKejebak++;
      passData(2);
      delay(delayBelok);
      counterBelok=0;
      motion=1;
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
      passData(0);rotateKepala();
    }
    if(countKejebak==4)
    {
      countKejebak=0;
//      if(flagFollowRoom==1)
//        flagFollowRoom=0;
//      else if(flagFollowRoom==0)
//        flagFollowRoom=1;
      gantiMotion();
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKanan=kanan1-kanan0;
    if(selisihKanan<batasBenerinKananBawahRoom  && kanan0<batasSerong && kanan1<batasSerongFurn)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihKanan>batasBenerinKananAtasRoom  && kanan0<batasSerong && kanan1<batasSerongFurn)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiri();
    }   
    else if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerongFurn)
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerongFurn)
    {
      passData(4);
      delay(delayGeser);
    } 
    else
    {
      passData(3);
    }
    
    if(belakang0<batasDepan || belakang1<batasDepan)
    {
        motion=4;rotateKepala();
    }
    else if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      countKejebak++;
      passData(3);
      delay(delayBelok);
      counterBelok=0;
      motion=2;
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
      passData(0);rotateKepala();
    }
    if(countKejebak==4)
    {
      countKejebak=0;
//      if(flagFollowRoom==1)
//        flagFollowRoom=0;
//      else if(flagFollowRoom==0)
//        flagFollowRoom=1;
       gantiMotion();
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihBelakang=belakang1-belakang0;
    if(selisihBelakang<batasBenerinBelakangBawahRoom  && belakang0<batasSerong  && belakang1<batasSerongFurn)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihBelakang>batasBenerinBelakangAtasRoom  && belakang0<batasSerong && belakang1<batasSerongFurn)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiri();
    } 
    else if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan && belakang0<batasSerong  && belakang1<batasSerongFurn)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan && belakang0<batasSerong  && belakang1<batasSerongFurn)
    {
      passData(1);
      delay(delayGeser);
    }  
    else
    {
      passData(4); 
    }
    
    if(kiri0<batasDepan || kiri1<batasDepan)
    {
        motion=1;rotateKepala();
    }
    else if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      countKejebak++;
      passData(4);
      delay(delayBelok);
      counterBelok=0;
      motion=3;
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
      passData(0);rotateKepala();
    }
    if(countKejebak==4)
    {
      countKejebak=0;
//      if(flagFollowRoom==1)
//        flagFollowRoom=0;
//      else if(flagFollowRoom==0)
//        flagFollowRoom=1;
      gantiMotion();
    }
  }
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ follow untuk return home
void followKananHome()
{
  batasMenjauhkan=260;
  batasMendekatkan=800;
  if(motion==1)
  { 
    selisihKanan=kanan0-kanan1;
    if(selisihKanan<batasBenerinKananBawah  && kanan0<batasSerong && kanan1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihKanan>batasBenerinKananAtas  && kanan0<batasSerong && kanan1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKanan();
    } 
    else if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong) /////
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    } 
    else 
    {
      passData(1);  
    }
    if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      countKejebak++;
      passData(1);
      delay(delayBelok);
      counterBelok=0;
      motion=2;
      while(belakang1>batasLurus)
      {
        passData(2);delay(delayBatasCountHome);
        counterBelok++;
        if(counterBelok>batasCountHome)// && belakang0>batasBelok && belakang1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
      flagSudahBelok=1;
    }
    else if(depan0<batasDepan || depan1<batasDepan)
    {
      motion=4;rotateKepala();
    }
    if(kanan0>batasBelok)
    {
      flagSebelumBelok=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihBelakang=belakang0-belakang1;
    if(selisihBelakang<batasBenerinBelakangBawah  && belakang0<batasSerong  && belakang1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihBelakang>batasBenerinBelakangAtas  && belakang0<batasSerong  && belakang1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan   && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan   && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }    
    else
    {
      passData(2);
    }
    if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      countKejebak++;
      passData(2);
      delay(delayBelok);
      counterBelok=0;
      motion=3;
      while(kiri1>batasLurus)
      {
        passData(3);delay(delayBatasCountHome);
        counterBelok++;
        if(counterBelok>batasCountHome)// && kiri0>batasBelok &&kiri1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
      flagSudahBelok=1;
    }
    else if(kanan0<batasDepan || kanan1<batasDepan)
    {
        motion=1;rotateKepala();
    }
    if(belakang0>batasBelok)
    {
      flagSebelumBelok=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKiri=kiri0-kiri1;
    if(selisihKiri<batasBenerinKiriBawah  && kiri0<batasSerong && kiri1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihKiri>batasBenerinKiriAtas  && kiri0<batasSerong && kiri1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKanan();
    }  
    else if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }  
    else
    {
      passData(3);
    }
    if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      countKejebak++;
      passData(3);
      delay(delayBelok);
      counterBelok=0;
      motion=4;
      while(depan1>batasLurus)
      {
        passData(4);delay(delayBatasCountHome);
        counterBelok++;
        if(counterBelok>batasCountHome)// && depan0>batasBelok && depan1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
      flagSudahBelok=1;
    }
    else if(belakang0<batasDepan || belakang1<batasDepan)
    {
        motion=2;rotateKepala();
    }
    if(kiri0>batasBelok)
    {
      flagSebelumBelok=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihDepan=depan0-depan1;
    if(selisihDepan<batasBenerinDepanBawah  && depan0<batasSerong  && depan1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihDepan>batasBenerinDepanAtas  && depan0<batasSerong && depan1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKanan();
    }   
    else if(depan0>batasMendekatkan&&depan1>batasMendekatkan && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else
    {
      passData(4); 
    }
    if(depan0>batasBelok&&depan1>batasBelok)
    {
      countKejebak++;
      passData(4);
      delay(delayBelok);
      counterBelok=0;
      motion=1;
      while(kanan1>batasLurus)
      {
        passData(1);delay(delayBatasCountHome);
        counterBelok++;
        if(counterBelok>batasCountHome)// && kanan0>batasBelok && kanan1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
      flagSudahBelok=1;
    }
    else if(kiri0<batasDepan || kiri1<batasDepan)
    {
        motion=3;rotateKepala();
    }
    if(depan0>batasBelok)
    {
      flagSebelumBelok=1;
    }
  }
}

void followKiriHome()
{
  batasMenjauhkan=260;
  batasMendekatkan=800;
  if(motion==1)
  { 
    selisihKiri=kiri1-kiri0;
    if(selisihKiri<batasBenerinKiriBawah  && kiri0<batasSerong && kiri1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihKiri>batasBenerinKiriAtas  && kiri0<batasSerong && kiri1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiri();
    }  
    else if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    else 
    {
      passData(1);  
    }
    if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      countKejebak++;
      passData(1);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=4;
      while(belakang0>batasLurus)
      {
        passData(4);delay(delayBatasCountHome);
        counterBelok++;
        if(counterBelok>batasCountHome)// && belakang0>batasBelok && belakang1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
      flagSudahBelok=1;
    }
    else if(depan0<batasDepan || depan1<batasDepan)
    {
      motion=2;rotateKepala();
      flagDepanKena41=1;
    }
    if(kiri1>batasBelok)
    {
      flagSebelumBelok=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihDepan=depan1-depan0;
    if(selisihDepan<batasBenerinDepanBawah  && depan0<batasSerong  && depan1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihDepan>batasBenerinDepanAtas  && depan0<batasSerong  && depan1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiri();
    }   
    else if(depan0>batasMendekatkan&&depan1>batasMendekatkan   && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan   && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    } 
    else
    {
      passData(2);
    }
    if(depan0>batasBelok&&depan1>batasBelok)
    {
      countKejebak++;
      passData(2);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=1;
      while(kiri0>batasLurus)
      {
        passData(1);delay(delayBatasCountHome);
        counterBelok++;
        if(counterBelok>batasCountHome)// && kiri0>batasBelok && kiri1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
      flagSudahBelok=1;
    }
    else if(kanan0<batasDepan || kanan1<batasDepan)
    {
        motion=3;rotateKepala();
        flagDepanKena41=1;
    }
    if(depan1>batasBelok)
    {
      flagSebelumBelok=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKanan=kanan1-kanan0;
    if(selisihKanan<batasBenerinKananBawah  && kanan0<batasSerong && kanan1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihKanan>batasBenerinKananAtas  && kanan0<batasSerong && kanan1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiri();
    }    
    else if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else
    {
      passData(3);
    }
    if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      countKejebak++;
      passData(3);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=2;
      while(depan0>batasLurus)
      {
        passData(2);delay(delayBatasCountHome);
        counterBelok++;
        if(counterBelok>batasCountHome)// &&depan0>batasBelok && depan1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
      flagSudahBelok=1;
    }
    else if(belakang0<batasDepan || belakang1<batasDepan)
    {
        motion=4;rotateKepala();
        flagDepanKena41=1;
    }
    if(kanan1>batasBelok)
    {
      flagSebelumBelok=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihBelakang=belakang1-belakang0;
    if(selisihBelakang<batasBenerinBelakangBawah  && belakang0<batasSerong  && belakang1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihBelakang>batasBenerinBelakangAtas  && belakang0<batasSerong && belakang1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiri();
    }   
    else if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else
    {
      passData(4); 
    }
    if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      countKejebak++;
      passData(4);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=3;
      while(kanan0>batasLurus)
      {
        passData(3);delay(delayBatasCountHome);
        counterBelok++;
        if(counterBelok>batasCountHome)// && kanan0>batasBelok && kanan1>batasBelok)
        {
          break;
        }
        cekGaris();
        if(flagGaris==1)
        {
          break;
        }
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
      flagSudahBelok=1;
    }
    else if(kiri0<batasDepan || kiri1<batasDepan)
    {
        motion=1;rotateKepala();
        flagDepanKena41=1;
    }
    if(belakang1>batasBelok)
    {
      flagSebelumBelok=1;
    }
  }
}

//======================================================== Pulang
void followKananPulang()
{
  batasMenjauhkan=260;
  batasMendekatkan=760;
  if(motion==1)
  { 
    selisihKanan=kanan0-kanan1;
    if(selisihKanan<batasBenerinKananBawah  && kanan0<batasSerong && kanan1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihKanan>batasBenerinKananAtas  && kanan0<batasSerong && kanan1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKanan();
    } 
    else if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong) /////
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    } 
    else 
    {
      passData(1);  
    }
//    if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong)
//    {
//      passData(2);
//      delay(delayGeser);
//    }
//    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
//    {
//      passData(4);
//      delay(delayGeser);
//    }
    if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      countKejebak++;
      passData(1);
      delay(delayBelok);
      counterBelok=0;
      motion=2;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(depan0<batasDepan || depan1<batasDepan)
    {
      motion=4;rotateKepala();
    }
    else if(kanan0>batasBelok)
    {
      flagSiapPerempatan=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihBelakang=belakang0-belakang1;
    if(selisihBelakang<batasBenerinBelakangBawah  && belakang0<batasSerong  && belakang1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihBelakang>batasBenerinBelakangAtas  && belakang0<batasSerong  && belakang1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan   && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan   && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }    
    else
    {
      passData(2);
    }
//    if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan   && belakang0<batasSerong  && belakang1<batasSerong)
//    {
//      passData(3);
//      delay(delayGeser);
//    }
//    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan   && belakang0<batasSerong  && belakang1<batasSerong)
//    {
//      passData(1);
//      delay(delayGeser);
//    }
    if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      countKejebak++;
      passData(2);
      delay(delayBelok);
      counterBelok=0;
      motion=3;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(kanan0<batasDepan || kanan1<batasDepan)
    {
        motion=1;rotateKepala();
    }
    else if(belakang0>batasBelok)
    {
      flagSiapPerempatan=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKiri=kiri0-kiri1;
    if(selisihKiri<batasBenerinKiriBawah  && kiri0<batasSerong && kiri1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihKiri>batasBenerinKiriAtas  && kiri0<batasSerong && kiri1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKanan();
    }  
    else if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }  
    else
    {
      passData(3);
    }
//    if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
//    {
//      passData(4);
//      delay(delayGeser);
//    }
//    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
//    {
//      passData(2);
//      delay(delayGeser);
//    }
    if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      countKejebak++;
      passData(3);
      delay(delayBelok);
      counterBelok=0;
      motion=4;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(belakang0<batasDepan || belakang1<batasDepan)
    {
        motion=2;rotateKepala();
    }
    else if(kiri0>batasBelok)
    {
      flagSiapPerempatan=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihDepan=depan0-depan1;
    if(selisihDepan<batasBenerinDepanBawah  && depan0<batasSerong  && depan1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiri();
    }
    else if(selisihDepan>batasBenerinDepanAtas  && depan0<batasSerong && depan1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKanan();
    }   
    else if(depan0>batasMendekatkan&&depan1>batasMendekatkan && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else
    {
      passData(4); 
    }
//    if(depan0>batasMendekatkan&&depan1>batasMendekatkan && depan0<batasSerong  && depan1<batasSerong)
//    {
//      passData(1);
//      delay(delayGeser);
//    }
//    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan && depan0<batasSerong  && depan1<batasSerong)
//    {
//      passData(3);
//      delay(delayGeser);
//    }
    if(depan0>batasBelok&&depan1>batasBelok)
    {
      countKejebak++;
      passData(4);
      delay(delayBelok);
      counterBelok=0;
      motion=1;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(kiri0<batasDepan || kiri1<batasDepan)
    {
        motion=3;rotateKepala();
    }
    else if(depan0>batasBelok)
    {
      flagSiapPerempatan=1;
    }
  }
}
void followKiriPulang()
{
  batasMenjauhkan=240;
  batasMendekatkan=760;
  if(motion==1)
  { 
    selisihKiri=kiri1-kiri0;
    if(selisihKiri<batasBenerinKiriBawah  && kiri0<batasSerong && kiri1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihKiri>batasBenerinKiriAtas  && kiri0<batasSerong && kiri1<batasSerong)// && (kanan0<batasDekat) && (kanan1<batasDekat))
    {
      mauSerongKiri();
    }  
    else if(kiri0>batasMendekatkan&&kiri1>batasMendekatkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else if(kiri0<batasMenjauhkan&&kiri1<batasMenjauhkan && kiri0<batasSerong && kiri1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    else 
    {
      passData(1);  
    }
    if(kiri0>batasBelok&&kiri1>batasBelok)
    {
      countKejebak++;
      passData(1);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=4;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(depan0<batasDepan || depan1<batasDepan)
    {
      motion=2;rotateKepala();
    }
    else if(kiri1>batasBelok)
    {
      flagSiapPerempatan=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==2)
  {
    selisihDepan=depan1-depan0;
    if(selisihDepan<batasBenerinDepanBawah  && depan0<batasSerong  && depan1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihDepan>batasBenerinDepanAtas  && depan0<batasSerong  && depan1<batasSerong)// && (belakang0<batasDekat) && (belakang1<batasDekat))
    {
      mauSerongKiri();
    }   
    else if(depan0>batasMendekatkan&&depan1>batasMendekatkan   && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else if(depan0<batasMenjauhkan&&depan1<batasMenjauhkan   && depan0<batasSerong  && depan1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    } 
    else
    {
      passData(2);
    }
    if(depan0>batasBelok&&depan1>batasBelok)
    {
      countKejebak++;
      passData(2);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=1;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(kanan0<batasDepan || kanan1<batasDepan)
    {
        motion=3;rotateKepala();
    }
    else if(depan1>batasBelok)
    {
      flagSiapPerempatan=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==3)
  {
    selisihKanan=kanan1-kanan0;
    if(selisihKanan<batasBenerinKananBawah  && kanan0<batasSerong && kanan1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihKanan>batasBenerinKananAtas  && kanan0<batasSerong && kanan1<batasSerong)// && (kiri0<batasDekat) && (kiri1<batasDekat))
    {
      mauSerongKiri();
    }    
    else if(kanan0>batasMendekatkan&&kanan1>batasMendekatkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(2);
      delay(delayGeser);
    }
    else if(kanan0<batasMenjauhkan&&kanan1<batasMenjauhkan && kanan0<batasSerong && kanan1<batasSerong)
    {
      passData(4);
      delay(delayGeser);
    }
    else
    {
      passData(3);
    }
    if(kanan0>batasBelok&&kanan1>batasBelok)
    {
      countKejebak++;
      passData(3);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=2;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(belakang0<batasDepan || belakang1<batasDepan)
    {
        motion=4;rotateKepala();
    }
    else if(kanan1>batasBelok)
    {
      flagSiapPerempatan=1;
    }
  }
  /////////////////////////////////////////////
  else if(motion==4)
  {
    selisihBelakang=belakang1-belakang0;
    if(selisihBelakang<batasBenerinBelakangBawah  && belakang0<batasSerong  && belakang1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKanan();
    }
    else if(selisihBelakang>batasBenerinBelakangAtas  && belakang0<batasSerong && belakang1<batasSerong)// && (depan0<batasDekat) && (depan1<batasDekat))
    {
      mauSerongKiri();
    }   
    else if(belakang0>batasMendekatkan&&belakang1>batasMendekatkan && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(3);
      delay(delayGeser);
    }
    else if(belakang0<batasMenjauhkan&&belakang1<batasMenjauhkan && belakang0<batasSerong  && belakang1<batasSerong)
    {
      passData(1);
      delay(delayGeser);
    }
    else
    {
      passData(4); 
    }
    if(belakang0>batasBelok&&belakang1>batasBelok)
    {
      countKejebak++;
      passData(4);
      delay(delayBelokKiri);
      counterBelok=0;
      motion=3;
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
        cekBoneka();
        if(flagBoneka==1)
        {
          break;
        }
      }
      passData(0);rotateKepala();
    }
    else if(kiri0<batasDepan || kiri1<batasDepan)
    {
        motion=1;rotateKepala();
    }
    else if(belakang1>batasBelok)
    {
      flagSiapPerempatan=1;
    }
  }
}
