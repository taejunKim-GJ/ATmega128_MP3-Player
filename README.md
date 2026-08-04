# ATmega128_MP3-Player
3학년 1학기 마이크로프로세서및응용 Term Project | AVR ATmega128을 활용한 MP3 플레이어

<br>

## 1. 개요 
ATmega128 MCU를 기반으로 키패드 입력을 제어하고, 타이머 인터럽트를 활용한 오디오 출력 및 그래픽 LCD 디스플레이를 구동하는 임베디드 MP3 플레이어 시스템 구현

<br>

## 2. 시스템 구조

### 하드웨어 아키텍쳐
<img width="500" alt="Hardware Configuration" src="https://github.com/user-attachments/assets/1eb28666-72e7-44a5-ae01-fa58fb52e3ba" />

- **IDE:** Microchip Studio
- **MCU:** AVR ATmega128
- **Input:** 4x4 Keypad (곡 선택 및 재생)
- **Output:** Buzzer (PWM 제어 기반 주파수 출력)
- **Output:** GLCD (타임라인, 곡 제목 출력)

<br>

### 파일 구조
본 프로젝트는 그래픽 LCD 및 폰트 제어를 위한 기존 라이브러리를 활용하고, **핵심 구동 로직(`main.c`)과 입출력 모듈 제어(`keypad.h`, `Buzzer.h`)를 직접 설계 및 구현**하였습니다.

```text
src/
├── [Direct Implement]  # 직접 설계 및 구현
│   ├── main.c          # 메인 제어 루프, 상태 머신 및 인터럽트 서비스 루틴(ISR) 관리
│   ├── keypad.h        # 키패드 입력 스캔 및 매트릭스 버튼 제어 로직
│   └── buzzer.h        # 타이머/카운터 및 PWM 제어를 통한 음계/주파수 출력 로직
│
└── [Library / Reference] # 제공받은 그래픽 LCD/폰트 라이브러리
    ├── GLCD_Draw.h     # GLCD 그래픽 제어 및 출력 함수
    ├── GLCD_Eng.h      # GLCD 영문 텍스트 렌더링 지원
    └── font_5x7.h      # 5x7 도트 매트릭스 폰트 데이터
```

<br>

## 3. 핵심 기능

1. **키패드 매트릭스 스캔 (`keypad.h`)**
   - 사용자 버튼 입력에 따른 시스템 제어 상태 머신 동작

2. **타이머/PWM 기반 음원 구동 (`buzzer.h`)**
   - 타이머/카운터의 ISR을 활용한 PWM 신호 생성과 딜레이 함수로, 정확한 박자 주기 및 음계별 주파수 사운드 출력

3. **시스템 통합 제어 (`main.c`)**
   - 키패드 이벤트, 음원 출력, GLCD 화면 갱신 간의 실행 타이밍 동기화

<br>

## 4. 트러블슈팅

### ① 길이가 긴 곡의 재생 시 중단
- **Symptom:** 동요 등 짧은 곡은 정상 작동하나, *'Let it go'* 등 곡 길이가 긴 음원 재생 시 중반부에서 곡이 처음으로 되돌아가거나 루프가 중단.
- **Root Cause:** 음표 인덱스 변수 `i`를 `unsigned char`(최대 255)로 선언하여, 음원 배열 길이(`songtime`)가 256을 초과할 때 인덱스 오버플로우가 발생.
- **Resolution:** 배열 길이를 감안하여 인덱스 변수를 16비트 정수형(`unsigned short`)으로 변경, 
    ```c
    unsigned short i = 0;          // 2바이트 정수형(최대 65,535)으로 변경하여 배열 인덱싱 범위 확장
    ```
    메모리 낭비 없이 긴 음원의 인덱스 오버플로우 해결.

<br>

### ② 타임라인 진행바 이동 시 픽셀 잔상 및 깜빡임
- **Symptom:** `GLCD_Clear()`로 화면 전체를 갱신하면 심한 깜빡임이 발생하고, 진행바 픽셀만 부분 소거하면 배경의 타임라인 가로선이 함께 지워짐.
- **Root Cause:** 전체 화면 소거(`GLCD_Clear`)는 연산 시간이 길어 렌더링 깜빡임을 유발하며, 부분 소거(`Partial_Clear`)는 겹쳐 있는 배경 그래픽까지 함께 제거함.
- **Resolution:** `past_value_is_8` 플래그를 도입해 메뉴 화면에서 복귀할 때만 전체 화면을 초기화하도록 제한. 직전 진행바 픽셀만 부분 소거한 직후, 지워진 구간의 타임라인 가로선(`GLCD_Line`)을 즉시 다시 그리는 방식으로 깜빡임과 선 끊김을 해결.

    ```c
    // 1. 화면 전환 시점에만 전체 Clear 호출 (깜빡임 방지)
    if(past_value_is_8){
        GLCD_Clear();
        MP3_Init();
        past_value_is_8 = 0;
    }
    
    // 2. 부분 소거 직후 끊어진 타임라인 가로선 즉시 복구
    if(i > 0){
        GLCD_Draw_Partial_Clear(48, 10+((117.0-10.0)/songtime)*(i-1), 52, 12+((117.0-10.0)/songtime)*(i-1)); // 직전 진행바 소거
        GLCD_Line(50, 10+((117.0-10.0)/songtime)*(i-1), 50, 12+((117.0-10.0)/songtime)*(i-1));             // 끊어진 가로선 즉시 복구
    }
    GLCD_Filled_Rectangle(48, 10+((117.0-10.0)/songtime)*i, 52, 12+((117.0-10.0)/songtime)*i);             // 새 진행바 출력
    ```
    
<br>

## 5. 시연 영상
[![ATmega128 MP3 플레이어 시연 영상](https://img.youtube.com/vi/Gu2SDf37emw/hqdefault.jpg)](https://youtube.com/shorts/Gu2SDf37emw?feature=share)

<br>

## 참고 자료
- **설계 근거:** [계이름별 PWM 주파수 매핑 데이터](./docs/계이름별_주파수값.png)
- **예시 악보 자료:** [겨울왕국 'Let it go' 구동 악보](./docs/Let_it_go_Frozen_악보.pdf)
