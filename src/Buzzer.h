#ifndef BUZZER_H_
#define BUZZER_H_

#define DO 0
#define RE 1
#define MI 2
#define FA 3
#define SOL 4
#define RA 5
#define SI 6
#define DDO 7
#define RRE 8
#define MMI 9
#define FFA 10
#define SSOL 11
#define RRA 12
#define SSI 13
#define DDDO 14
#define RRRE 15
#define MMMI 16
#define FFFA 17
#define SSSOL18
#define RRRA 19
#define SSSI 20
#define SII 21
#define EOS -1
#define ON 0
#define OFF 1

volatile int state = OFF, tone = 0, *song;
char f_table[] = {17, 43, 66, 77, 97, 114, 130, // 6옥타브 계이름
	137, 150, 161, 167, 176, 185, 193,          // 7옥타브 계이름
	196, 203, 209, 211, 216, 220, 224, 3        // 8옥타브 계이름, 5옥타브 시
};


int canon[] = { SSOL, SSOL, MMI, FFA, SSOL, SSOL, MMI, FFA, 
	SSOL, SOL, RA, SI, DDO, RRE, MMI, FFA, 
	MMI, MMI, DDO, RRE, MMI, MMI, MI, FA, SOL, RA, SOL, FA, SOL, DDO, SI, DDO, EOS
};

int summer[] = { SOL, DDO, RRE, MMI, RRE, RRE, DDO, DDO, DDO, DDO,
	SOL, DDO, RRE, MMI, RRE, RRE, DDO, RRE, RRE, RRE, MMI, MMI, MMI, MMI,
	SOL, DDO, RRE, MMI, RRE, RRE, DDO, DDO, DDO, DDO,
	SOL, DDO, RRE, MMI, RRE, RRE, DDO, RRE, RRE, RRE, SSOL, SSOL, FFA, FFA, EOS	
};

int MerryGoRoundOfLife[] = {MI, RA, DDO, MMI, MMI, MMI, RRE, DDO, SI, DDO, DDO, DDO,
	 RA, DDO, MMI, RRA, RRA, RRA, RRA, SSOL, FFA, SSOL, SSOL, SSOL,
	 SI, MMI, SSOL, SSI, SSI, RRA, SSOL, FFA, SSOL, RRA, RRA, SSOL,
	 FFA, FFA, MMI, RRE, DDO, RRE, MMI, RRE, RA, SI, SI, EOS
};

int LetItGo[] = {MI, FA, SOL, SOL, SOL, SOL, SOL, RE, RE, RA, RA, RA, RA, RA,
	SOL, SOL, MI, MI, MI, MI, MI, FA, FA, SOL, SOL, SOL, SOL, SOL,
	MI, FA, SOL, SOL, SOL, SOL, SOL, RE, SI, SI, SI, RA, RA, RA, RA,
	SOL, RA, SI, SI, SI, SI, DDO, DDO, DDO, SI, RA, RA, SOL, SOL, SOL, SOL, SOL, SOL, EOS
};

int LoveIsAnOpenDoor[] = {FFA, MMI, RRE, MMI, MMI, RRE, RRE, RRRE, RRRE, RRRE, RRRE, RRRE, RRRE, RRRE, RRRE,
	DDDO, DDDO, DDDO, DDDO, DDDO, DDDO, DDDO, DDDO, SSI, SSI, SSI, SSI, SSI, SSI, SSI, SSI,
	FFA, MMI, RRE, MMI, MMI, RRE, RRE, RRRE, RRRE, RRRE, RRRE, MMMI, MMMI, MMMI, MMMI, MMMI, MMMI, DDDO, DDDO, DDDO, DDDO, RRRE, RRRE, RRRE, RRRE, RRRE, RRRE, RRRE, RRRE,
	FFA, MMI, RRE, MMI, MMI, RRE, RRE, RRA, RRA, RRA, RRA, SSI, SSI, RRA, RRA, RRA, RRA, SSI, SSI, RRA, RRA, SSI, SSI, RRA, RRA, SSI, SSI, RRRE, RRRE, RRRE, RRRE,
	FFA, MMI, RRE, MMI, MMI, RRE, RRE, RA, RA, RA, RA, RA, RA, RA, RA, RA, RA, RA, RA, EOS
};

int Marigold[] = {FA, FA, MI, FA, FA, FA, SOL, SOL, FA, FA, FA, FA, FA, FA, FA, FA, FA, FA, FA, FA,
	FA, FA, MI, MI, FA, FA, SOL, SOL, RA, RA, RA, RA, MI, MI, MI, MI, MI, MI, FA, FA, MI, MI, RE, RE, 
	SII, SII, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, MI, MI, MI, MI, FA, FA, FA, FA, FA, FA, DO, DO, DO, DO, DO, DO, DO, DO,
	RE, DO, SII, SII, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, MI, MI, RE, RE, FA, FA, SOL, SOL, FA, FA, SOL, FA, FA, FA, RE, RE, RE, RE,
	RE, RE, SOL, SOL, FA, FA, FA, FA, FA, FA, SOL, SOL, FA, FA, MI, MI, RE, RE, SI, SI, RA, RA, RA, RA, SI, SI, FA, FA, FA, FA, MI, MI, MI, MI,
	
	FA, FA, FA, FA, FA, FA, FA, FA, FA, FA, MI, MI, FA, FA, SOL, SOL, RA, RA, RA, RA, MI, MI, MI, MI, MI, MI, FA, FA, MI, MI, RE, RE,
	SII, SII, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, MI, MI, MI, MI, FA, FA, FA, FA, FA, FA, DO, DO, DO, DO, DO, DO, DO, DO,
	RE, DO, SII, SII, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, MI, MI, RE, RE, FA, FA, SOL, SOL, SOL, SOL, RA, RA, RA, RA, RE, RE, RE, RE,
    FA, FA, SOL, SOL, FA, FA, MI, MI, RE, RE, SII, SII, RE, RE, RE, RE, RE, RE, SOL, SOL, FA, FA, MI, MI, RE, RE, RE, RE, SII, SII, SII, SII, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, EOS
};

int KimiRock[] = {SI, SI, RA, RA, SOL, SOL, SOL, SOL, SOL, MI, SOL, SOL, SOL, MI, SOL, RA, RA, RA, RA, RA, RE, RE, SI, SI, DDO, SI, SI, RA, SOL, SOL, SOL, SOL, SOL, SOL, SOL, SOL,
	MI, SOL, SOL, SOL, MI, SOL, SOL, SOL, MI, SOL, RA, RA, RA, RA, RA, RA, RE, SI, SI, DDO, DDO, SI, SI, DDO, DDO, SI, SI, RA, RA, SOL, RA, RA, RA,
	SI, SI, RA, RA, SOL, SOL, SOL, SOL, SOL, MI, SOL, SOL, SOL, MI, SOL, RA, RA, RA, RA, RA, RE, RE, SI, SI, DDO, SI, SI, RRE, RRE, RA, RA, RA, SOL, SOL, SOL, SOL,
	MI, FA, SOL, SOL, SOL, SOL, SOL, SOL, SOL, FA, FA, SOL, SOL, SOL, SOL, SOL, SOL, SOL, SOL, SOL, SOL, SOL, SOL, SOL, SOL, RA, RA, RA, RA, RA, SOL, SOL, SOL, SOL,
	DDO, DDO, SI, SI, RA, RA, SOL, SOL, SOL, SOL, FA, MI, MI, MI, FA, SOL, SOL, SOL, SOL, SOL, EOS
};


ISR(TIMER0_OVF_vect){
	if (state == ON){
		PORTB = 0x00;
		state = OFF;
	}

	else{
		PORTB = 0x10;
		state = ON;
	}
	
	TCNT0 = f_table[tone];
}

#endif /* BUZZER_H_ */