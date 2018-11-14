#define batasPerempatanDepan 3000
#define batasPerempatan 2500
#define batasJauh 5300
#define batasJauhSamping 4300
#define delayMajuRoomHome 380

int flagPerempatan=0;
//          |     |
//      1   |  4  |   2
//          |     |
//   -------      ---------
//      1             2
//   -------      ---------
//          |     |
//      4   |  3  |   3
//          |     |

void cekRuangReturn();

void clearFlag()
{
  flagSudahBelok=0;
  flagSebelumBelok=0;
}

void cekSajaAwal()
{
  if(flagFollow==0)
  {
    if(motion==1)
    {
      if(kiri1>batasJauhSamping && (depan0>batasJauh || depan1>batasJauh))
      {
        passData(motion);delay(delayMajuRoomHome);passData(0);
        if(kanan0>batasJauhSamping)
        {
          flagPerempatan=1;
        }
      }
    }
    else if(motion==2)
    {
      if(depan1>batasJauhSamping && (kanan0>batasJauh || kanan1>batasJauh))
      {
        passData(motion);delay(delayMajuRoomHome);passData(0);
        if(belakang0>batasJauhSamping)
        {
          flagPerempatan=1;
        }
      }
    }
    else if(motion==3)
    {
      if(kanan1>batasJauhSamping && (belakang0>batasJauh || belakang1>batasJauh))
      {
        passData(motion);delay(delayMajuRoomHome);passData(0);
        if(kiri0>batasJauhSamping)
        {
          flagPerempatan=1;
        }
      }
    }
    else if(motion==4)
    {
      if(belakang1>batasJauhSamping && (kiri0>batasJauh || kiri1>batasJauh))
      {
        passData(motion);delay(delayMajuRoomHome);passData(0);
        if(depan0>batasJauhSamping)
        {
          flagPerempatan=1;
        }
      }
    }
  }
  else if(flagFollow==1)
  {
    if(motion==1)
    {
      if(kanan0>batasJauhSamping && (depan0>batasJauh || depan1>batasJauh))
      {
        passData(motion);delay(delayMajuRoomHome);passData(0);
        if(kiri1>batasJauhSamping)
        {
          flagPerempatan=1;
        }
      }
    }
    else if(motion==2)
    {
      if(belakang0>batasJauhSamping && (kanan0>batasJauh || kanan1>batasJauh))
      {
        passData(motion);delay(delayMajuRoomHome);passData(0);
        if(depan1>batasJauhSamping)
        {
          flagPerempatan=1;
        }
      }
    }
    else if(motion==3)
    {
      if(kiri0>batasJauhSamping && (belakang0>batasJauh || belakang1>batasJauh))
      {
        passData(motion);delay(delayMajuRoomHome);passData(0);
        if(kanan1>batasJauhSamping)
        {
          flagPerempatan=1;
        }
      }
    }
    else if(motion==4)
    {
      if(depan0>batasJauhSamping && (kiri0>batasJauh || kiri1>batasJauh))
      {
        passData(motion);delay(delayMajuRoomHome);passData(0);
        if(belakang1>batasJauhSamping)
        {
          flagPerempatan=1;
        }
      }
    }
  }
}

void cekSaja()
{
  flagPerempatan=0;
  cekSajaAwal();
  if(motion==1)
  {
    if(kanan0>batasPerempatan && kiri1>batasPerempatan && (depan0>batasPerempatanDepan || depan1>batasPerempatanDepan))
    {
      flagPerempatan=1;
    }
  }
  else if(motion==2)
  {
    if(belakang0>batasPerempatan && depan1>batasPerempatan && (kanan0>batasPerempatanDepan || kanan1>batasPerempatanDepan))
    {
      flagPerempatan=1;
    }
  }
  else if(motion==3)
  {
    if(kiri0>batasPerempatan && kanan1>batasPerempatan && (belakang0>batasPerempatanDepan || belakang1>batasPerempatanDepan))
    {
      flagPerempatan=1;
    }
  }
  else if(motion==4)
  {
    if(depan0>batasPerempatan && belakang1>batasPerempatan && (kiri0>batasPerempatanDepan || kiri1>batasPerempatanDepan))
    {
      flagPerempatan=1;
    }
  }
}

void cekPerempatan()
{
//  flagPerempatan=0;
//  if(motion==1)
//  {
//    if(kanan0>batasPerempatan && kiri1>batasPerempatan && (depan0>batasPerempatanDepan || depan1>batasPerempatanDepan))
//    {
//      flagPerempatan=1;
//    }
//  }
//  else if(motion==2)
//  {
//    if(belakang0>batasPerempatan && depan1>batasPerempatan && (kanan0>batasPerempatanDepan || kanan1>batasPerempatanDepan))
//    {
//      flagPerempatan=1;
//    }
//  }
//  else if(motion==3)
//  {
//    if(kiri0>batasPerempatan && kanan1>batasPerempatan && (belakang0>batasPerempatanDepan || belakang1>batasPerempatanDepan))
//    {
//      flagPerempatan=1;
//    }
//  }
//  else if(motion==4)
//  {
//    if(depan0>batasPerempatan && belakang1>batasPerempatan && (kiri0>batasPerempatanDepan || kiri1>batasPerempatanDepan))
//    {
//      flagPerempatan=1;
//    }
//  }
  cekSaja();
  if(flagPerempatan==1)
  {
    passData(0);
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
    delay(500);
    clearFlag();
    tempRuang=0;
    cekRuangReturn();
    // optional kasih perbaiki posisi
    if(tempRuang==1)
    {
      digitalWrite(led1,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
      delay(500);
      if(startRoom==1 || startRoom==2)
      {
        while(flagSudahBelok==0)
        {
          followKiriHome();
          if(flagSudahBelok==1)
            break;
        }
        clearFlag();
        if(startRoom==1)
        {
          //Langsung follow kiri lagi (optional)
          while(flagSebelumBelok==0)
          {
            followKananHome();
            if(flagSebelumBelok==1)
              break;
          }
          majuSampaiDepan();
          gantiMotionCCW();
          flagFollow=1;
        }
        else if(startRoom==2)
        {
          flagFollow=1;
        }
      }
      else if(startRoom==3)
      {
        while(flagSudahBelok==0)
        {
          followKiriHome();
          if(flagSudahBelok==1)
            break;
        }
        clearFlag();
        gantiMotion();
        flagFollow=0;
      }
      else if(startRoom==4)
      {
        if(awalRoom==41)
        {
          if(flagLetakBoneka==3)
          {
            gantiMotion();
            majuSedikit();delay(delayMajuRoomHome);
            flagFollow=0;
          }
          else
          {
            flagFollow=1;
          }
        }
        else if(awalRoom==42)
        {
          mundurSedikit();delay(delayMajuRoomHome);
          gantiMotionCW();
          for(int a=0;a<40;a++)
          {
            majuSedikit();
            delay(10);
            cekGaris();
            if(flagGaris==1)
              break;
          }
        }
      }
    }
    else if(tempRuang==2)
    {
      digitalWrite(led1,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
      delay(500);
      digitalWrite(led1,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
      delay(500);
      if(startRoom==1 || startRoom==2)
      {
        while(flagSudahBelok==0)
        {
          followKananHome();
          if(flagSudahBelok==1)
            break;
        }
        clearFlag();
        if(startRoom==1)
        {
          while(flagSebelumBelok==0)
          {
            followKananHome();
            if(flagSebelumBelok==1)
              break;
          }
          majuSampaiDepan();
          gantiMotionCCW();
          flagFollow=1;
        }
        else if(startRoom==2)
        {
          flagFollow=1;
        }
      }
      else if(startRoom==3)
      {
//        while(flagSudahBelok==0)
//        {
//          followKiriHome();
//        }
//        clearFlag();
//        gantiMotion();
//        flagFollow=0;
      }
      else if(startRoom==4)
      {
        if(awalRoom==41)
        {
          if(flagLetakBoneka==3)
          {
            while(flagSudahBelok==0)
            {
              followKiriHome();
              if(flagSudahBelok==1)
                break;
            }
            clearFlag();
            majuSedikit();delay(delayMajuRoomHome);
            gantiMotion();
            flagFollow=0;
          }
          else
          {
            while(flagSudahBelok==0)
            {
              followKiriHome();
              if(flagSudahBelok==1)
                break;
            }
            clearFlag();
            flagFollow=1;
          }
        }
        else if(awalRoom==42)
        {
          while(flagSudahBelok==0)
          {
            followKiriHome();
            if(flagSudahBelok==1)
              break;
          }
          clearFlag();
          gantiMotion();
          flagFollow=0;
        }
      }
    }
    else if(tempRuang==3)
    {
      digitalWrite(led1,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
      delay(500);
      digitalWrite(led1,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
      delay(500);
      digitalWrite(led1,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
      delay(500);
      if(startRoom==1 || startRoom==2)
      {
        while(flagSudahBelok==0)
        {
          followKananHome();
          if(flagSudahBelok==1)
            break;
        }
        clearFlag();
        while(flagSebelumBelok==0)
        {
          followKananHome();
          if(flagSebelumBelok==1)
              break;
        }
        clearFlag();
        majuSampaiDepan();
        gantiMotionCCW();
        while(flagSudahBelok==0)
        {
          followKananHome();
          if(flagSudahBelok==1)
            break;
        }
        clearFlag();
        if(startRoom==1)
        {
          while(flagSebelumBelok==0)
          {
            followKananHome();
            if(flagSebelumBelok==1)
              break;
          }
          majuSampaiDepan();
          gantiMotionCCW();
          flagFollow=1;
        }
        else if(startRoom==2)
        {
          flagFollow=1;
        }
      }
      else if(startRoom==3)
      {
        while(flagSudahBelok==0)
        {
          followKananHome();
          if(flagSudahBelok==1)
            break;
        }
        clearFlag();
        flagFollow=1;
      }
      else if(startRoom==4)
      {
        if(awalRoom==41)
        {
//          if(flagLetakBoneka==3)
//          {
//            gantiMotion();
//            majuSedikit();delay(delayMajuRoom);
//            flagFollow=0;
//          }
//          else
//          {
//            flagFollow=1;
//          }
        }
        else if(awalRoom==42)
        {
          flagFollow=0;
        }
      }
    }
    else if(tempRuang==4)
    {
      if(startRoom==3)
      {
        while(flagSudahBelok==0)
        {
          followKiriHome();
          if(flagSudahBelok==1)
            break;
        }
        clearFlag();
        flagFollow=0;
      }
      else if(startRoom==4)
      {
        while(flagSudahBelok==0)
        {
          followKiriHome();
          if(flagSudahBelok==1)
            break;
        }
        clearFlag();
        majuSedikit();delay(delayMajuRoomHome);
        gantiMotion();
        flagPerempatan=0;
        flagFollow=1;
        while(flagPerempatan==0)
        {
          followKanan();cekSaja();
          if(flagPerempatan==1)
            break;
        }
        if(awalRoom==41)
        {
          if(flagLetakBoneka==3)
          {
            while(flagSudahBelok==0)
            {
              followKiriHome();
              if(flagSudahBelok==1)
                break;
            }
            clearFlag();
            majuSedikit();delay(delayMajuRoomHome);
            gantiMotion();
            flagFollow=0;
          }
          else
          {
            while(flagSudahBelok==0)
            {
              followKiriHome();
              if(flagSudahBelok==1)
                break;
            }
            clearFlag();
            majuSedikit();delay(delayMajuRoomHome);
            flagFollow=1;
          }
        }
        else if(awalRoom==42)
        {
          while(flagSudahBelok==0)
          {
            followKiriHome();
            if(flagSudahBelok==1)
              break;
          }
          clearFlag();
          majuSedikit();delay(delayMajuRoomHome);
          gantiMotion();
          flagFollow=0;
        }
      }
    } 
  }
}

