int flagStart=0;  //0=menunggu mic 1=saatnya jalan
int flagRoom=0;   //0=di dalam ruang  1=di luar
int flagFollow=0; //0=follow kiri 1=follow kanan
int flagFollowRoom=0; //0=follow kiri 1=follow kanan
int flagTarget=0; //0=masih cari api 1=mau pulang
int flagGaris=0;  //0=tidak ada garis 1=ada garis
int flagApi=0;  //0=tidak ada api 1=ada api
int flagBoneka=0; //0=tidak ada boneka 1=ada boneka
int flagKecepatan=0;  //0=kecepatan normal  1=kecepatan lambat
int flagGarisAwal=0;  //
int flagStopState=0;
int timer=0;

int keluar12=0; //keluar room 12, 0=belakang ada tembok, 1=tidak ada tembok
int ruangSaatIni=0,startRoom=0,endRoom=0,awalRoom=0;
int ruang[4];
int ruangBalik[4];
int jumlahRuang=0;
int jumlahRuangBalik=0;
int countKejebak=0;
int countFollowApi=0;
int flagSearchLagi=0;

int flagSudahBelok=0;
int flagSebelumBelok=0;
int flagLetakBoneka=0;
// 1 di depan ruang 11, 2 di depan ruang 42, 3 di depan ruang 41
int flagDepanKena41=0;
int flagSiapPerempatan=0;

int pos=2048;

//kompas
int tempRuang=0,beforeTempRuang=0,countError=0;

