# ATmega128_MP3-Player
3학년 1학기 마이크로프로세서및응용 Term Project | AVR ATmega128을 활용한 MP3 플레이어

<br>

## 1. 개요 
ATmega128 MCU를 기반으로 키패드 입력을 제어하고, 타이머 인터럽트를 활용한 오디오 출력(Buzzer/PWM) 및 그래픽 LCD(GLCD) 디스플레이 UI를 구동하는 임베디드 오디오 플레이어 시스템 구현

<br>

## 2. 시스템 구조

### 하드웨어 구성도
<img width="700" alt="Hardware Configuration" src="https://github.com/user-attachments/assets/1eb28666-72e7-44a5-ae01-fa58fb52e3ba" />


### 하드웨어 인터페이스
- **MCU:** AVR ATmega128
- **Input:** 4x4 Keypad (곡 선택, 재생/정지, 볼륨 조절 등 사용자 입력 처리)
- **Output (Audio):** Buzzer / Audio Out (PWM 제어 기반 주파수 출력)
- **Output (Display):** GLCD (재생 상태, 곡 정보 문자 출력)
- **IDE / Compiler:** Microchip Studio (C Language)

<br>

## 3. 프로젝트 파일 구조 
본 프로젝트는 그래픽 LCD 및 폰트 제어를 위한 기존 라이브러리를 활용하고, **핵심 구동 로직(`main.c`)과 입출력 모듈 제어(`keypad.h`, `buzzer.h`)를 직접 설계 및 구현**하였습니다.

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

