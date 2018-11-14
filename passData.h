void passData(int data)
{
    if(data==0) // 0000 - Stop
    {
        digitalWrite(data1,HIGH);
        digitalWrite(data2,HIGH);
        digitalWrite(data3,HIGH);
        digitalWrite(data4,HIGH);
    }
    else if(data==1) // 0001 - Maju
    {
        digitalWrite(data1,HIGH);
        digitalWrite(data2,HIGH);
        digitalWrite(data3,HIGH);
        digitalWrite(data4,LOW);
    }
    else if(data==2) // 0010 - Mundur
    {
        digitalWrite(data1,HIGH);
        digitalWrite(data2,HIGH);
        digitalWrite(data3,LOW);
        digitalWrite(data4,HIGH);
    }          
    else if(data==3) // 0011 - Serong Kanan
    {
        digitalWrite(data1,HIGH);
        digitalWrite(data2,HIGH);
        digitalWrite(data3,LOW);
        digitalWrite(data4,LOW);
    }
    else if(data==4) // 0100 - Serong Kiri
    {
        digitalWrite(data1,HIGH);
        digitalWrite(data2,LOW);
        digitalWrite(data3,HIGH);
        digitalWrite(data4,HIGH);
    }   
    else if(data==5) // 0101 - Pivot Kanan
    {
        digitalWrite(data1,HIGH);
        digitalWrite(data2,LOW);
        digitalWrite(data3,HIGH);
        digitalWrite(data4,LOW);
    }
    else if(data==6) // 0110 - Pivot Kiri
    {
        digitalWrite(data1,HIGH);
        digitalWrite(data2,LOW);
        digitalWrite(data3,LOW);
        digitalWrite(data4,HIGH);
    }
    else if(data==7) // 0111 - Geser Kanan
    {
        digitalWrite(data1,HIGH);
        digitalWrite(data2,LOW);
        digitalWrite(data3,LOW);
        digitalWrite(data4,LOW);
    }
    else if(data==8) // 1000 - Geser Kiri
    {
        digitalWrite(data1,LOW);
        digitalWrite(data2,HIGH);
        digitalWrite(data3,HIGH);
        digitalWrite(data4,HIGH);
    }
    else if(data==9) // 1001
    {
        digitalWrite(data1,LOW);
        digitalWrite(data2,HIGH);
        digitalWrite(data3,HIGH);
        digitalWrite(data4,LOW);
    }  
    else if(data==10) // 1010
    {
        digitalWrite(data1,LOW);
        digitalWrite(data2,HIGH);
        digitalWrite(data3,LOW);
        digitalWrite(data4,HIGH);
    }  
    else if(data==11) // 1011
    {
        digitalWrite(data1,LOW);
        digitalWrite(data2,HIGH);
        digitalWrite(data3,LOW);
        digitalWrite(data4,LOW);
    }
    else if(data==12) // 1100
    {
        digitalWrite(data1,LOW);
        digitalWrite(data2,LOW);
        digitalWrite(data3,HIGH);
        digitalWrite(data4,HIGH);
    } 
    else if(data==13) // 1101
    {
        digitalWrite(data1,LOW);
        digitalWrite(data2,LOW);
        digitalWrite(data3,HIGH);
        digitalWrite(data4,LOW);
    }  
    else if(data==14) // 1110
    {
        digitalWrite(data1,LOW);
        digitalWrite(data2,LOW);
        digitalWrite(data3,LOW);
        digitalWrite(data4,HIGH);
    }  
    else if(data==15) // 1111
    {
        digitalWrite(data1,LOW);
        digitalWrite(data2,LOW);
        digitalWrite(data3,LOW);
        digitalWrite(data4,LOW);
    }
}
