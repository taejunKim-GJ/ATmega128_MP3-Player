
unsigned char ScreenBuffer[8][128]={0};           // screen buffer

#define GLCD_CS1 0x02		 // GLCD_CS1 Select 0000 0010
#define GLCD_CS2 0x01		 // GLCD_CS2 Select 0000 0001
#define GLCD_CS1_2 0x00		 // GLCD_CS1, GLCD_CS2 Select 0000 0011

#define GLCD_SET_X_ADDR 0xB8
#define GLCD_SET_Y_ADDR 0x40

// 점을 찍을 좌표를 잡습니다.
void GLCD_Axis_xy(unsigned char x, unsigned char y)
{
        GLCD_Command(GLCD_CS1_2, GLCD_SET_X_ADDR + x); // X address
        if(y <= 63)
        {
                GLCD_Command(GLCD_CS1, GLCD_SET_Y_ADDR + y); // CS1 Y address
        }
        else
        {
                GLCD_Command(GLCD_CS2, GLCD_SET_Y_ADDR + y - 64); // CS2 Y address
        }
} 



// draw a dot on GLCD
// 점을 그립니다.
void GLCD_Dot(unsigned char xx,unsigned char y)
{
  unsigned char x, i;

  // 해상도 범위(128.64) 인지 검사합니다.
  if((xx > 63) || (y > 127)) return;

  x = xx / 8;				  // calculate x address
  i = xx % 8;
  if(i == 0)      { i = 0x01; }
  else if(i == 1) { i = 0x02; }
  else if(i == 2) { i = 0x04; }
  else if(i == 3) { i = 0x08; }
  else if(i == 4) { i = 0x10; }
  else if(i == 5) { i = 0x20; }
  else if(i == 6) { i = 0x40; }
  else            { i = 0x80; }
  
  ScreenBuffer[x][y] |= i;			// OR old data with new data

  GLCD_Axis_xy(x, y);				      // draw dot on GLCD screen
  if(y <= 63) { GLCD_Data(GLCD_CS1, ScreenBuffer[x][y]);  }
  else        { GLCD_Data(GLCD_CS2, ScreenBuffer[x][y]);  }
}



// draw a straight line
// 원을 그립니다.
void GLCD_Line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2)	
{
  int x, y;

  if(y1 != y2)				
  {
    if(y1 < y2)				
    {
      for(y = y1; y <= y2; y++)
      {
        x = x1 + (y - y1)*(x2 - x1)/(y2 - y1);
        GLCD_Dot(x,y);
      }
    }
    else
    {
      for(y = y1; y >= y2; y--)
      { 
        x = x1 + (y - y1)*(x2 - x1)/(y2 - y1);
        GLCD_Dot(x,y);
      }
    }
  }
  else if(x1 != x2)	  // if x1 != x2, x is variable
  { 
    if(x1 < x2)				
    {
      for(x = x1; x <= x2; x++)
      { y = y1 + (x - x1)*(y2 - y1)/(x2 - x1);
        GLCD_Dot(x,y);
      }
    }
    else
    {
      for(x = x1; x >= x2; x--)
      {
        y = y1 + (x - x1)*(y2 - y1)/(x2 - x1);
        GLCD_Dot(x,y);
      }
    }
  }
  else                  // if x1 == x2 and y1 == y2,
  {
    GLCD_Dot(x1,y1);		//             it is a dot
  }
}


// draw a rectangle
// 비어있는 사각형을 그립니다.
void GLCD_Rectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2) 
{
  GLCD_Line(x1,y1,x1,y2);				// horizontal line
  GLCD_Line(x2,y1,x2,y2);
  GLCD_Line(x1,y1,x2,y1);				// vertical line
  GLCD_Line(x1,y2,x2,y2);
}


// draw a circle
// 비어 있는 원을 그립니다.
void GLCD_Circle(unsigned char x1,unsigned char y1,unsigned char r)	
{
  int x, y;
  float s;

  for(y = y1 - r*3/4; y <= y1 + r*3/4; y++)	// draw with y variable
  {
    s = sqrt(r*r - (y-y1)*(y-y1)) + 0.5;
    x = x1 + (unsigned char)s;
    GLCD_Dot(x,y);
    x = x1 - (unsigned char)s;
    GLCD_Dot(x,y);
  }

  for(x = x1 - r*3/4; x <= x1 + r*3/4; x++)	// draw with x variable
  {
    s = sqrt(r*r - (x-x1)*(x-x1)) + 0.5;
    y = y1 + (unsigned char)s;
    GLCD_Dot(x,y);
    y = y1 - (unsigned char)s;
    GLCD_Dot(x,y);
  }
}


// GLCD_Draw.h 소스에 아래의 함수들을 추가하였습니다.
//                   (국립금오공과대학교 전자공학부) 

// 화면 전체 지우기

void GLCD_Draw_Clear(){


	for(int x=0; x<8; x++){
		for(int y=0; y<128; y++){

			if(ScreenBuffer[x][y] != 0){
				GLCD_Command(GLCD_CS1_2, GLCD_SET_X_ADDR+x);

				if(y <= 63) { 
					GLCD_Command(GLCD_CS1, GLCD_SET_Y_ADDR+y);
					GLCD_Data(GLCD_CS1, 0x00);  
				}
				else  { 
					GLCD_Command(GLCD_CS2, GLCD_SET_Y_ADDR+y-64);    
					GLCD_Data(GLCD_CS2, 0x00);  
				}
			}
		}
	}

	// 1024=128*8 스크린버퍼 지우기
	memset(ScreenBuffer, 0, 1024);

}

// 화면 일부분만 지우기
void GLCD_Draw_Partial_Clear(unsigned char x1,unsigned char y1, unsigned char x2,unsigned char y2)

{

	unsigned char x, y, xx, i;


	for(x=x1; x<=x2; x++){
		for(y=y1; y<=y2; y++){

		  xx = x / 8;				  // calculate x address
		  i = x % 8;

		  if(i == 0)      { i = 0xFE; }
		  else if(i == 1) { i = 0xFD; }
		  else if(i == 2) { i = 0xFB; }
		  else if(i == 3) { i = 0xF7; }
		  else if(i == 4) { i = 0xEF; }
		  else if(i == 5) { i = 0xDF; }
		  else if(i == 6) { i = 0xBF; }
		  else            { i = 0x7F; }

  
		  ScreenBuffer[xx][y] &= i;			// OR old data with new data

		  GLCD_Axis_xy(xx, y);				      // draw dot on GLCD screen

		  if(y <= 63) { GLCD_Data(GLCD_CS1, ScreenBuffer[xx][y]);  }

		  else        { GLCD_Data(GLCD_CS2, ScreenBuffer[xx][y]);  }

		}
	}
}

// 채워진 사각형을 그립니다.
void GLCD_Filled_Rectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2) 
{
	for(int i=x1; i<=x2; i++)
  		GLCD_Line(i, y1, i, y2);   
}

// 반원 그리기 - 원의 위쪽 반원
void GLCD_Partial_Circle_Upper(unsigned char x1,unsigned char y1,unsigned char r)	
{
  int x, y;
  float s;

  for(y = y1 - r*3/4; y <= y1 + r*3/4; y++)	// draw with y variable
  {
    s = sqrt(r*r - (y-y1)*(y-y1)) + 0.5;
    x = x1 + (unsigned char)s;
	if(x < x1) GLCD_Dot(x,y);
    x = x1 - (unsigned char)s;
    if(x < x1) GLCD_Dot(x,y);
  }

  for(x = x1 - r*3/4; x <= x1 + r*3/4; x++)	// draw with x variable
  {
    s = sqrt(r*r - (x-x1)*(x-x1)) + 0.5;
    y = y1 + (unsigned char)s;
    if(x < x1) GLCD_Dot(x,y);
    y = y1 - (unsigned char)s;
    if(x < x1) GLCD_Dot(x,y);
  }
}

// 반원 그리기 - 원의 아래쪽 반원
void GLCD_Partial_Circle_Lower(unsigned char x1,unsigned char y1,unsigned char r)	
{
  int x, y;
  float s;

  for(y = y1 - r*3/4; y <= y1 + r*3/4; y++)	// draw with y variable
  {
    s = sqrt(r*r - (y-y1)*(y-y1)) + 0.5;
    x = x1 + (unsigned char)s;
	if(x > x1) GLCD_Dot(x,y);
    x = x1 - (unsigned char)s;
    if(x > x1) GLCD_Dot(x,y);
  }

  for(x = x1 - r*3/4; x <= x1 + r*3/4; x++)	// draw with x variable
  {
    s = sqrt(r*r - (x-x1)*(x-x1)) + 0.5;
    y = y1 + (unsigned char)s;
    if(x > x1) GLCD_Dot(x,y);
    y = y1 - (unsigned char)s;
    if(x > x1) GLCD_Dot(x,y);
  }
}

// draw a circle
// 채워진 원을 그립니다.
void GLCD_Filled_Circle(unsigned char x1,unsigned char y1,unsigned char r)	
{
  int x, y;
  float s;

  for(y = y1 - r*3/4; y <= y1 + r*3/4; y++)	// draw with y variable
  {
    s = sqrt(r*r - (y-y1)*(y-y1)) + 0.5;
	for(x=x1-s; x<= x1+s; x++)
       	GLCD_Dot(x,y);    
  }

  for(x = x1 - r*3/4; x <= x1 + r*3/4; x++)	// draw with x variable
  {
    s = sqrt(r*r - (x-x1)*(x-x1)) + 0.5;
	for(y=y1-s; y<= y1+s; y++)
       	GLCD_Dot(x,y);    
  }
}


// 점 하나 지우기
void GLCD_Dot_Clear(unsigned char xx,unsigned char y)
{
	unsigned char x, i;

	if((xx > 63) || (y > 127)) return;

	x = xx / 8;					            	i = xx % 8;
	if(i == 0)      { i = 0xFE; }
	else if(i == 1) { i = 0xFD; }
	else if(i == 2) { i = 0xFB; }
	else if(i == 3) { i = 0xF7; }
	else if(i == 4) { i = 0xEF; }
	else if(i == 5) { i = 0xDF; }
	else if(i == 6) { i = 0xBF; }
	else            { i = 0x7F; }

	ScreenBuffer[x][y] &= i;			

	GLCD_Axis_xy(x, y);		
	if(y <= 63) { GLCD_Data(GLCD_CS1, ScreenBuffer[x][y]);  }
	else        { GLCD_Data(GLCD_CS2, ScreenBuffer[x][y]);  }
}
// 선 지우기
void GLCD_Line_Clear(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2)	
{
  int x, y;

  if(y1 != y2)				// if y1 != y2, y is variable
  {
    if(y1 < y2)				//              x is function
    {
      for(y = y1; y <= y2; y++)
      {
        x = x1 + (y - y1)*(x2 - x1)/(y2 - y1);
        GLCD_Dot_Clear(x,y);
      }
    }
    else
    {
      for(y = y1; y >= y2; y--)
      { 
        x = x1 + (y - y1)*(x2 - x1)/(y2 - y1);
        GLCD_Dot_Clear(x,y);
      }
    }
  }
  else if(x1 != x2)	  // if x1 != x2, x is variable
  { 
    if(x1 < x2)				//              y is function
    {
      for(x = x1; x <= x2; x++)
      { y = y1 + (x - x1)*(y2 - y1)/(x2 - x1);
        GLCD_Dot_Clear(x,y);
      }
    }
    else
    {
      for(x = x1; x >= x2; x--)
      {
        y = y1 + (x - x1)*(y2 - y1)/(x2 - x1);
        GLCD_Dot_Clear(x,y);
      }
    }
  }
  else                  // if x1 == x2 and y1 == y2,
  {
    GLCD_Dot_Clear(x1,y1);		//             it is a dot
  }
}




