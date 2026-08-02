# ATmega128_MP3-Player
3학년 1학기 마이크로프로세서및응용 Term Project | AVR ATmega128을 활용한 MP3 플레이어

<br>

## 1. 개요 
ATmega128 MCU를 기반으로 키패드 입력을 제어하고, 타이머 인터럽트를 활용한 오디오 출력(Buzzer/PWM) 및 그래픽 LCD(GLCD) 디스플레이 UI를 구동하는 임베디드 오디오 플레이어 시스템 구현

<br>

## 2. 시스템 구조

### 하드웨어 구성도
<img width="500" alt="Hardware Configuration" src="https://github.com/user-attachments/assets/1eb28666-72e7-44a5-ae01-fa58fb52e3ba" />


### 하드웨어 인터페이스
- **MCU:** AVR ATmega128
- **Input:** 4x4 Keypad (곡 선택 및 재생)
- **Output (Audio):** Buzzer / Audio Out (PWM 제어 기반 주파수 출력)
- **Output (Display):** GLCD (재생 상태, 곡 정보 문자 출력)
- **IDE / Compiler:** Microchip Studio (C Language)

<br>

## 3. 파일 구조
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

### 핵심 기능

1. **키패드 매트릭스 스캔 (`keypad.h`)**
   - 입출력 포트 제어를 통한 키 입력 감지 및 디바운싱(Debouncing) 처리
   - 사용자 버튼 입력에 따른 시스템 제어 상태 머신 동작

2. **타이머/PWM 기반 음원 구동 (`buzzer.h`)**
   - ATmega128 타이머/카운터를 활용한 PWM 신호 생성 및 음계별 주파수 제어
   - 인터럽트 서비스 루틴(ISR)을 활용한 정확한 음장(박자) 주기 제어 및 사운드 출력

3. **시스템 통합 제어 (`main.c`)**
   - 키패드 이벤트, 음원 출력, GLCD 화면 갱신 간의 실행 타이밍 동기화
   - 인터럽트 우선순위 관리 및 메인 제어 루프 최적화

<br>

## 4. 트러블슈팅 
하드웨어 연동 및 펌웨어 디버깅 과정에서 발생한 주요 이슈와 근본 원인(Root Cause) 규명 및 해결 과정입니다.

| 이슈 (Issue) | 근본 원인 (Root Cause) | 해결 방안 (Solution) |
| :--- | :--- | :--- |
| *(예시) 키패드 입력 시 곡이 2회씩 중복 건너뛰어지는 현상* | 기계적 접점 스위치 불량으로 인한 바운싱(Bouncing) 노이즈 신호 입력 | 키패드 스캔 루틴 내에 소프트웨어적인 디바운싱 지연(Delay) 로직 및 상태 플래그 적용 |
| *(예시) 음악 출력 중 GLCD 화면이 깜빡이거나 멈추는 현상* | 타이머 인터럽트 주기가 지나치게 짧아 메인 루프의 디스플레이 렌더링 타임아웃 발생 | ISR 내 처리 연산을 최소화하고 주기를 최적화하여 렌더링 병목 해결 |
*(※ 실제 겪으셨던 에러와 디버깅 경험을 이 테이블 형태로 간결하게 채워 넣으시면 됩니다.)*

<br>

## 5. 시연 영상

### 데모 영상
> 본 구동 영상에서는 4×4 키패드 입력을 통한 곡 재생 및 타이머 PWM 기반 오디오 출력 동작을 확인할 수 있습니다.
[MP3 Player 구동 데모 영상 보기](

<br>

## 참고 자료
- **[악보 자료]** [겨울왕국 'Let it go' 구동 악보 (`Let it go_Frozen_악보.pdf`)](./docs/Let_it_go_Frozen_악보.pdf)
- **[설계 근거]** [계이름별 PWM 주파수 매핑 데이터 (`계이름별_주파수값.png`)](./docs/계이름별_주파수값.png)
