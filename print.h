void printSelisih()
{
  selisihKanan=kanan0-kanan1;
  selisihBelakang=belakang0-belakang1;
  selisihKiri=kiri0-kiri1;
  selisihDepan=depan0-depan1;
  Serial.print(selisihKanan);
  Serial.print("  ");
  Serial.print(selisihBelakang);
  Serial.print("  ");
  Serial.print(selisihKiri);
  Serial.print("  ");
  Serial.print(selisihDepan);
  Serial.println("  ");
}

void printSRF()
{
  int a,b;
  Serial.print(depan0);Serial.print("  ");
  Serial.print(depan1);Serial.print("  ");
  Serial.print(kanan0);Serial.print("  ");
  Serial.print(kanan1);Serial.print("  ");
  Serial.print(belakang0);Serial.print("  ");
  Serial.print(belakang1);Serial.print("  ");
  Serial.print(kiri0);Serial.print("  ");
  Serial.print(kiri1);Serial.println("  ");
  for(a=0;a<10;a++)
  {
      b=0;
      b=EEPROM.read(a);
      Serial.print(b);Serial.print("\t");
  }
  Serial.print("\n");
}

void printIR()
{
  Serial.print("IR : ");
  Serial.print(ir1);Serial.print("  ");
  Serial.print(ir2);Serial.print("  ");
  Serial.print(ir3);Serial.print("  ");
  Serial.print(ir4);Serial.println("  ");
}

void printMic()
{
  Serial.print("MIC : ");
  Serial.print(digitalRead(mic));Serial.println("  ");
  Serial.print("UVtron : ");
  Serial.print(analogRead(uvtron));Serial.println("  ");
  Serial.print("Tombol Stop : ");
  Serial.print(digitalRead(tombolStop));Serial.println("  ");
  Serial.print("Kill Plug : ");
  Serial.print(digitalRead(killPlug));Serial.println("  ");
  
}

void printFlame()
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
  
  for(int a=0;a<9;a++)
  {
//      if(sensor[a]> batasSensor[a])sensor[a]=1;
//      else sensor[a]=0;
      Serial.print(sensor[a]);Serial.print("     ");

  }
  Serial.println(" ");
}

void printTPA()
{
  for(i = 0; i < 8; i++)
  {
     temperature[i] = getData(i+2);
     Serial.print(temperature[i]);
     Serial.print(" ");
  }
  Serial.println("  ");
  delay(50);
  for(i = 0; i < 8; i++)
  {
     temperature1[i] = getData1(i+2);
     Serial.print(temperature1[i]);
     Serial.print(" ");
  }
  Serial.println("  ");
  delay(50);
}

