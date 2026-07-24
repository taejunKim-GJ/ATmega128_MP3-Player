#define KEY_DDR DDRF
#define KEY_PORT PORTF
#define KEY_PIN PINF
#include "Buzzer.h"

unsigned char key_scan(unsigned char a);
int key_convert(unsigned char in);

//키패드에 각 줄에 입력 값이 있는지 스캔하는 함수
unsigned char key_scan(unsigned char a){
	unsigned char in;

	KEY_DDR = 0xFF; //all out
	KEY_PORT = a; //키패드 줄 위치
	KEY_DDR = 0x0F; //Port 7bit~4bit(In) 3bit~0bit(Out)
	_delay_us(50);

	// 키패드 입력 포트의 상위 4자리 값 추출
	in = (PINF & 0xF0);
	if(in != 0x00){
		in |= a;
		return in;
	}
	return 0;
}

unsigned char* returnvalue;
double songtime, delay;  //노래 시간, 박자에 따른 계이름 하나당 딜레이(250: 4분음표 / 125: 8분음표 / 62.5: 16분음표)
int key_convert(unsigned char in){
	switch(in) {
		case 0x18 : returnvalue = "1.Canon", song = canon, songtime = sizeof(canon)/sizeof(int), delay = 250; break;
		case 0x14 : returnvalue = "2.Summer", song = summer, songtime = sizeof(summer)/sizeof(int), delay = 125; break;
		case 0x12 : returnvalue = "3.Merry go round", song = MerryGoRoundOfLife, songtime = sizeof(MerryGoRoundOfLife)/sizeof(int), delay = 250; break;
		case 0x11 : returnvalue = "4.Let it go", song = LetItGo, songtime = sizeof(LetItGo)/sizeof(int), delay = 125; break;
		case 0x28 : returnvalue = "5.LoveisAnOpenDoor", song = LoveIsAnOpenDoor, songtime = sizeof(LoveIsAnOpenDoor)/sizeof(int), delay = 62.5; break;
		case 0x24 : returnvalue = "6.Marigold", song = Marigold, songtime = sizeof(Marigold)/sizeof(int), delay = 62.5; break;
		case 0x22 : returnvalue = "7.Kimi Rock", song = KimiRock, songtime = sizeof(KimiRock)/sizeof(int), delay = 62.5; break;
		case 0x21 : returnvalue = "8"; break;
		/*case 0x48 : returnvalue = 9; break;
		case 0x44 : returnvalue = 10; break;
		case 0x42 : returnvalue = 11; break;
		case 0x41 : returnvalue = 12; break;
		case 0x88 : returnvalue = 13; break;
		case 0x84 : returnvalue = 14; break;
		case 0x82 : returnvalue = 15; break;
		case 0x81 : returnvalue = 16; break;*/
		default : returnvalue = ""; break;
	}
	return returnvalue;
}