#include <NewPing.h>
//SRF
#define echo0 23
#define echo1 37
#define echo2 35
#define echo3 33
#define echo4 31
#define echo5 29
#define echo6 27
#define echo7 25

#define trig0 39
#define trig1 47
#define trig2 49
#define trig3 51
#define trig4 53
#define trig5 45
#define trig6 43
#define trig7 41

#define depan0 srf0()
#define depan1 srf1()
#define kanan0 srf2()
#define kanan1 srf3()
#define belakang0 srf4()
#define belakang1 srf5()
#define kiri0 srf6()
#define kiri1 srf7()

#define MAX_D 200

NewPing sonar0(trig0, echo0, MAX_D);
NewPing sonar1(trig1, echo1, MAX_D);
NewPing sonar2(trig2, echo2, MAX_D);
NewPing sonar3(trig3, echo3, MAX_D);
NewPing sonar4(trig4, echo4, MAX_D);
NewPing sonar5(trig5, echo5, MAX_D);
NewPing sonar6(trig6, echo6, MAX_D);
NewPing sonar7(trig7, echo7, MAX_D);

#define delays 34
unsigned int distance=0; //penyimpanan sementara SRF

unsigned int srf0()
{
    delay(delays);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    //unsigned int uS = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
    distance=sonar0.ping(); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    return distance;
}
unsigned int srf1()
{
    delay(delays);                    // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    //unsigned int uS = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
    distance=sonar1.ping(); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    return distance;
}
unsigned int srf2()
{
    delay(delays);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    //unsigned int uS = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
    distance=sonar2.ping(); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    return distance;
}
unsigned int srf3()
{
    delay(delays);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    //unsigned int uS = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
    distance=sonar3.ping(); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    return distance;
}
unsigned int srf4()
{
    delay(delays);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    //unsigned int uS = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
    distance=sonar4.ping(); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    return distance;
}
unsigned int srf5()
{
    delay(delays);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    //unsigned int uS = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
    distance=sonar5.ping(); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    return distance;
}
unsigned int srf6()
{
    delay(delays);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    //unsigned int uS = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
    distance=sonar6.ping(); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    return distance;
}
unsigned int srf7()
{
    delay(delays);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    //unsigned int uS = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
    distance=sonar7.ping(); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    return distance;
}
