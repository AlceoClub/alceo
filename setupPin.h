#define mic 38
#define semprotan 22
#define uvtron A9
#define led 40
#define led1 42
#define tombolStop 50
#define killPlug 24

#define data1 12  //abu putih abu putih
#define data2 11
#define data3 10
#define data4 9

#define ir1 digitalRead(7)
#define ir2 digitalRead(4)
#define ir3 digitalRead(5)
#define ir4 digitalRead(6)

#define flame0 A8 ///pojok kanan
#define flame1 A3 
#define flame2 A2
#define flame3 A1
#define flame4 A0///tengah 
#define flame5 A4
#define flame6 A5
#define flame7 A7
#define flame8 A6////pojok kiri

void setupPin()
{
    //SRF
    pinMode(trig0,OUTPUT);
    pinMode(echo0,INPUT);

    pinMode(trig1,OUTPUT);
    pinMode(echo1,INPUT);

    pinMode(trig2,OUTPUT);
    pinMode(echo2,INPUT);

    pinMode(trig3,OUTPUT);
    pinMode(echo3,INPUT);

    pinMode(trig3,OUTPUT);
    pinMode(echo3,INPUT);

    pinMode(trig4,OUTPUT);
    pinMode(echo4,INPUT);

    pinMode(trig5,OUTPUT);
    pinMode(echo5,INPUT);

    pinMode(trig6,OUTPUT);
    pinMode(echo6,INPUT);

    pinMode(trig7,OUTPUT);
    pinMode(echo7,INPUT);

    //Kabel Data
    pinMode(data1,OUTPUT);
    pinMode(data2,OUTPUT);
    pinMode(data3,OUTPUT);
    pinMode(data4,OUTPUT);

    //Mic, semprotan, uvtron, led
    pinMode(mic,INPUT_PULLUP);
    pinMode(tombolStop,INPUT_PULLUP);
    pinMode(killPlug,INPUT);
    pinMode(semprotan,OUTPUT);
    digitalWrite(semprotan,LOW);
    pinMode(uvtron,INPUT);
    pinMode(led,OUTPUT);
    pinMode(led1,OUTPUT);

    //IR
    pinMode(7,INPUT_PULLUP);
    pinMode(6,INPUT_PULLUP);
    pinMode(5,INPUT_PULLUP);
    pinMode(4,INPUT_PULLUP);
    
    pinMode(3,INPUT_PULLUP);

    //flame Array
    pinMode(flame0,INPUT);
    pinMode(flame1,INPUT);
    pinMode(flame2,INPUT);
    pinMode(flame3,INPUT);
    pinMode(flame4,INPUT);
    pinMode(flame5,INPUT);
    pinMode(flame6,INPUT);
    pinMode(flame7,INPUT);
    pinMode(flame8,INPUT);
}

