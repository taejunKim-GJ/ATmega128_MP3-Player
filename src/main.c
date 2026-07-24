#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "GLCD_Eng.h"
#include "GLCD_Draw.h"

//delay error 때문에 만든 함수
void delay_ms(int ms){  
	while(ms-- != 0)
	_delay_ms(1);
}

//MP3 모드 초기화 함수 
void MP3_Init(){     
	GLCD_String(0, 0, "Playlist");
	GLCD_Filled_Rectangle(10, 5, 13, 127);
	GLCD_Filled_Rectangle(13, 5, 30, 10);
	GLCD_Filled_Rectangle(27, 10, 30, 127);
	GLCD_Filled_Rectangle(13, 122, 27, 127);
	GLCD_String(2, 2, " select songs");
	GLCD_String(4, 2, "only 1~8 or error");
	GLCD_String(7, 7, "8.MENU");
	GLCD_Line(50, 10, 50, 117);   //타임라인용 선 그리기
}

int main(void){
	//GLCD 관련
	_delay_ms(50);
	GLCD_Port_Init();
	GLCD_Init();
	
	//키패드관련
	unsigned char in, in0,in1,in2,in3;
	unsigned char past_value_is_8;
	double past_songtime;
	
	//버저 관련
	unsigned short i=0;  //노래 길이가 긴 것은 char로 감당 못해서 short로 함
	//DDRB = 0x10;       //소리 약하게 내기 위하여 주석 처리
	TCCR0 = 0x03;
	TCNT0 = f_table[song[i]];
	sei();
	
	MP3_Init();  //MP3 모드 초기화
	
	while(1){
		// 키패드 첫번째줄 스캔
		in0 = key_scan(0x01);
		// 키패드 두번째줄 스캔
		in1 = key_scan(0x02);
		// 키패드 세번째줄 스캔
		in2 = key_scan(0x04);
		// 키패드 네번째줄 스캔
		in3 = key_scan(0x08);

		in = (in3 | in2 | in1 | in0); // 4줄 입력 값 취합

		key_convert(in); // keypad 입력 받음
		  
		
		if(in){
			//8번 버튼을 눌렀을 때, 메뉴판 실행
			if(returnvalue == "8"){  
				GLCD_Clear();
				GLCD_String(0, 8, "MENU");
				GLCD_String(1, 0, "1.canon");
				GLCD_String(2, 0, "2.summer");
				GLCD_String(3, 0, "3.MerryGoRoundOfLife");
				GLCD_String(4, 0, "4.Let it go");
				GLCD_String(5, 0, "5.LoveIsAnOpenDoor");
				GLCD_String(6, 0, "6.Marigold");
				GLCD_String(7, 0, "7.KimiwaRockWoKikana");
				past_value_is_8 = 1;
			}
			
			else{
				if(past_value_is_8){	//이전에 8번을 입력했었다면
					GLCD_Clear();		//메뉴판 지우고
					MP3_Init();			//MP3 모드 초기화
					past_value_is_8 = 0;
				}
				
				GLCD_String(2, 2, "                  ");  //keypad 누를 때마다 해당 줄 리셋
				GLCD_Filled_Rectangle(13, 122, 27, 127);   // 플레이리스트 칸까지 지워진 부분은 복구
				if(i>0){
					GLCD_Draw_Partial_Clear(48, 10+((117.0-10.0)/past_songtime)*(i-1), 52, 12+((117.0-10.0)/past_songtime)*(i-1));  //이전 노래의 타임라인 표시 지우기
					GLCD_Line(50, 10+((117.0-10.0)/past_songtime)*(i-1), 50, 12+((117.0-10.0)/past_songtime)*(i-1));  //지운 자리에 선은 복구
				}
			
				GLCD_String(2, 2, returnvalue);   //선택한 노래 표시
				TIMSK = 0x01;  //부저 활성화로 노래 시작
				for(i=0; i<songtime; i++){
			  		if(i>0){  //노래가 시작할 때, if 문은 처음에는 실행하지 않음
						GLCD_Draw_Partial_Clear(48, 10+((117.0-10.0)/songtime)*(i-1), 52, 12+((117.0-10.0)/songtime)*(i-1));   //직전 타임라인 표시 지우기
						GLCD_Line(50, 10+((117.0-10.0)/songtime)*(i-1), 50, 12+((117.0-10.0)/songtime)*(i-1));	//지운 자리에 선은 복구
					}
					GLCD_Filled_Rectangle(48, 10+((117.0-10.0)/songtime)*i, 52, 12+((117.0-10.0)/songtime)*i);  //타임라인 표시가 시간에 맞게 이동
					tone = song[i];
					delay_ms(delay);  //노래 별로 박자가 다름
				}
			}
			
			in = 0;
			past_songtime = songtime;
		}
	}
}