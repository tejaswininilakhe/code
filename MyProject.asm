
_main:
	LDI        R27, 255
	OUT        SPL+0, R27
	LDI        R27, 0
	OUT        SPL+1, R27

;MyProject.c,57 :: 		void main()
;MyProject.c,60 :: 		LED_DATA = 1;
	PUSH       R2
	PUSH       R3
	PUSH       R4
	IN         R27, PORTC0_bit+0
	SBR        R27, 1
	OUT        PORTC0_bit+0, R27
;MyProject.c,61 :: 		LED_DDR  = 0;
	IN         R27, DDB5_bit+0
	CBR        R27, 32
	OUT        DDB5_bit+0, R27
;MyProject.c,62 :: 		USART_Init();
	CALL       _USART_Init+0
;MyProject.c,63 :: 		vInitTimer_1();
	CALL       _vInitTimer_1+0
;MyProject.c,64 :: 		PORTD2_bit = 1;
	IN         R27, PORTD2_bit+0
	SBR        R27, 4
	OUT        PORTD2_bit+0, R27
;MyProject.c,66 :: 		SREG_I_bit = 0;
	IN         R27, SREG_I_bit+0
	CBR        R27, 128
	OUT        SREG_I_bit+0, R27
;MyProject.c,67 :: 		RXEN_bit = 0;
	IN         R27, RXEN_bit+0
	CBR        R27, 16
	OUT        RXEN_bit+0, R27
;MyProject.c,69 :: 		USART_SendByte('M');
	LDI        R27, 77
	MOV        R2, R27
	CALL       _USART_SendByte+0
;MyProject.c,70 :: 		USART_SendByte('I');
	LDI        R27, 73
	MOV        R2, R27
	CALL       _USART_SendByte+0
;MyProject.c,71 :: 		USART_SendByte('C');
	LDI        R27, 67
	MOV        R2, R27
	CALL       _USART_SendByte+0
;MyProject.c,72 :: 		USART_SendByte('R');
	LDI        R27, 82
	MOV        R2, R27
	CALL       _USART_SendByte+0
;MyProject.c,73 :: 		USART_SendByte('O');
	LDI        R27, 79
	MOV        R2, R27
	CALL       _USART_SendByte+0
;MyProject.c,74 :: 		USART_SendByte('L');
	LDI        R27, 76
	MOV        R2, R27
	CALL       _USART_SendByte+0
;MyProject.c,75 :: 		USART_SendByte('O');
	LDI        R27, 79
	MOV        R2, R27
	CALL       _USART_SendByte+0
;MyProject.c,76 :: 		USART_SendByte('G');
	LDI        R27, 71
	MOV        R2, R27
	CALL       _USART_SendByte+0
;MyProject.c,77 :: 		SREG_I_bit = 1;
	IN         R27, SREG_I_bit+0
	SBR        R27, 128
	OUT        SREG_I_bit+0, R27
;MyProject.c,78 :: 		RXEN_bit = 1;
	IN         R27, RXEN_bit+0
	SBR        R27, 16
	OUT        RXEN_bit+0, R27
;MyProject.c,79 :: 		LED_DATA = 0;
	IN         R27, PORTC0_bit+0
	CBR        R27, 1
	OUT        PORTC0_bit+0, R27
;MyProject.c,80 :: 		vClearBuffer();
	CALL       _vClearBuffer+0
;MyProject.c,81 :: 		while(1)
L_main0:
;MyProject.c,83 :: 		LED_DATA = ~LED_DATA;
	IN         R0, PORTC0_bit+0
	LDI        R27, 1
	EOR        R0, R27
	OUT        PORTC0_bit+0, R0
;MyProject.c,84 :: 		delay_ms(1000);
	LDI        R18, 41
	LDI        R17, 150
	LDI        R16, 128
L_main2:
	DEC        R16
	BRNE       L_main2
	DEC        R17
	BRNE       L_main2
	DEC        R18
	BRNE       L_main2
;MyProject.c,124 :: 		ucPacketIndex=0;
	LDI        R27, 0
	STS        _ucPacketIndex+0, R27
;MyProject.c,125 :: 		SREG_I_bit = 0;
	IN         R27, SREG_I_bit+0
	CBR        R27, 128
	OUT        SREG_I_bit+0, R27
;MyProject.c,126 :: 		RXEN_bit = 0;
	IN         R27, RXEN_bit+0
	CBR        R27, 16
	OUT        RXEN_bit+0, R27
;MyProject.c,127 :: 		vSendPacket(&ucInStat_1_ON,8);
	LDI        R27, 8
	MOV        R4, R27
	LDI        R27, #lo_addr(_ucInStat_1_ON+0)
	MOV        R2, R27
	LDI        R27, hi_addr(_ucInStat_1_ON+0)
	MOV        R3, R27
	CALL       _vSendPacket+0
;MyProject.c,128 :: 		SREG_I_bit = 1;
	IN         R27, SREG_I_bit+0
	SBR        R27, 128
	OUT        SREG_I_bit+0, R27
;MyProject.c,129 :: 		RXEN_bit = 1;
	IN         R27, RXEN_bit+0
	SBR        R27, 16
	OUT        RXEN_bit+0, R27
;MyProject.c,130 :: 		delay_ms(1000);
	LDI        R18, 41
	LDI        R17, 150
	LDI        R16, 128
L_main4:
	DEC        R16
	BRNE       L_main4
	DEC        R17
	BRNE       L_main4
	DEC        R18
	BRNE       L_main4
;MyProject.c,131 :: 		if(ucPacket[2] != 0x86 && ucPacket[1] != 0x00)
	LDS        R16, _ucPacket+2
	CPI        R16, 134
	BRNE       L__main28
	JMP        L__main24
L__main28:
	LDS        R16, _ucPacket+1
	CPI        R16, 0
	BRNE       L__main29
	JMP        L__main23
L__main29:
L__main22:
;MyProject.c,133 :: 		uiInStat_1 = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
	LDS        R16, _ucPacket+4
	MOV        R19, R16
	CLR        R18
	LDS        R16, _ucPacket+5
	LDI        R17, 0
	OR         R16, R18
	OR         R17, R19
	STS        _uiInStat_1+0, R16
	STS        _uiInStat_1+1, R17
;MyProject.c,134 :: 		bCommStatus = 1;
	LDS        R27, _bCommStatus+0
	SBR        R27, BitMask(_bCommStatus+0)
	STS        _bCommStatus+0, R27
;MyProject.c,135 :: 		}
	JMP        L_main9
;MyProject.c,131 :: 		if(ucPacket[2] != 0x86 && ucPacket[1] != 0x00)
L__main24:
L__main23:
;MyProject.c,138 :: 		bCommStatus = 0;
	LDS        R27, _bCommStatus+0
	CBR        R27, BitMask(_bCommStatus+0)
	STS        _bCommStatus+0, R27
;MyProject.c,139 :: 		}
L_main9:
;MyProject.c,140 :: 		vClearBuffer();
	CALL       _vClearBuffer+0
;MyProject.c,244 :: 		}
	JMP        L_main0
;MyProject.c,245 :: 		}
L_end_main:
L__main_end_loop:
	JMP        L__main_end_loop
; end of _main

_vSerialRx_ISR:
	PUSH       R30
	PUSH       R31
	PUSH       R27
	IN         R27, SREG+0
	PUSH       R27

;MyProject.c,246 :: 		void vSerialRx_ISR() org IVT_ADDR_USART__RXC      // This funtion is Interrupt Funtion
;MyProject.c,249 :: 		if ( FE_bit)
	IN         R27, FE_bit+0
	SBRS       R27, 4
	JMP        L_vSerialRx_ISR10
;MyProject.c,252 :: 		}
	JMP        L_vSerialRx_ISR11
L_vSerialRx_ISR10:
;MyProject.c,255 :: 		dmxByte = UDR0;
; dmxByte start address is: 19 (R19)
	IN         R19, UDR0+0
;MyProject.c,256 :: 		ucPacket[ucPacketIndex]=dmxByte;
	LDI        R17, #lo_addr(_ucPacket+0)
	LDI        R18, hi_addr(_ucPacket+0)
	LDS        R16, _ucPacketIndex+0
	MOV        R30, R16
	LDI        R31, 0
	ADD        R30, R17
	ADC        R31, R18
	ST         Z, R19
; dmxByte end address is: 19 (R19)
;MyProject.c,257 :: 		ucPacketIndex++;
	LDS        R16, _ucPacketIndex+0
	SUBI       R16, 255
	STS        _ucPacketIndex+0, R16
;MyProject.c,258 :: 		LED_DATA = ~LED_DATA;
	IN         R0, PORTC0_bit+0
	LDI        R27, 1
	EOR        R0, R27
	OUT        PORTC0_bit+0, R0
;MyProject.c,259 :: 		}
L_vSerialRx_ISR11:
;MyProject.c,260 :: 		}
L_end_vSerialRx_ISR:
	POP        R27
	OUT        SREG+0, R27
	POP        R27
	POP        R31
	POP        R30
	RETI
; end of _vSerialRx_ISR

_USART_Init:

;MyProject.c,261 :: 		void USART_Init(void){
;MyProject.c,264 :: 		UBRRH = USART_BAUDRATE_9600 >> 8;
	LDI        R27, 37
	OUT        UBRRH+0, R27
;MyProject.c,265 :: 		UBRRL = USART_BAUDRATE_9600;//BAUD_PRESCALE_9600;// Load lower 8-bits into the low byte of the UBRR register
	LDI        R27, 128
	OUT        UBRRL+0, R27
;MyProject.c,270 :: 		}
L_USART_Init13:
;MyProject.c,271 :: 		TXEN_bit = 1;
	IN         R27, TXEN_bit+0
	SBR        R27, 8
	OUT        TXEN_bit+0, R27
;MyProject.c,272 :: 		RXEN_bit = 1;
	IN         R27, RXEN_bit+0
	SBR        R27, 16
	OUT        RXEN_bit+0, R27
;MyProject.c,273 :: 		RXCIE_bit = 1;
	IN         R27, RXCIE_bit+0
	SBR        R27, 128
	OUT        RXCIE_bit+0, R27
;MyProject.c,275 :: 		}
L_end_USART_Init:
	RET
; end of _USART_Init

_USART_SendByte:

;MyProject.c,276 :: 		void USART_SendByte(unsigned char u8Data)
;MyProject.c,280 :: 		UDR = u8Data;
	OUT        UDR+0, R2
;MyProject.c,281 :: 		while(UDRE_bit == 0);
L_USART_SendByte14:
	IN         R27, UDRE_bit+0
	SBRC       R27, 5
	JMP        L_USART_SendByte15
	JMP        L_USART_SendByte14
L_USART_SendByte15:
;MyProject.c,282 :: 		}
L_end_USART_SendByte:
	RET
; end of _USART_SendByte

_vSendPacket:

;MyProject.c,283 :: 		void vSendPacket(unsigned char *Data,unsigned char ucLen)
;MyProject.c,285 :: 		unsigned char ucCount=0;
; ucCount start address is: 17 (R17)
	LDI        R17, 0
; ucCount end address is: 17 (R17)
;MyProject.c,286 :: 		while(ucLen)
L_vSendPacket16:
; ucCount start address is: 17 (R17)
	TST        R4
	BRNE       L__vSendPacket37
	JMP        L_vSendPacket17
L__vSendPacket37:
;MyProject.c,288 :: 		ucLen--;
	MOV        R16, R4
	SUBI       R16, 1
	MOV        R4, R16
;MyProject.c,289 :: 		USART_SendByte(Data[ucCount]);
	MOV        R30, R17
	LDI        R31, 0
	ADD        R30, R2
	ADC        R31, R3
	LD         R16, Z
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _USART_SendByte+0
	POP        R2
	POP        R3
;MyProject.c,290 :: 		ucCount++;
	MOV        R16, R17
	SUBI       R16, 255
	MOV        R17, R16
;MyProject.c,291 :: 		}
; ucCount end address is: 17 (R17)
	JMP        L_vSendPacket16
L_vSendPacket17:
;MyProject.c,292 :: 		}
L_end_vSendPacket:
	RET
; end of _vSendPacket

_vTimer1_ISR:
	PUSH       R30
	PUSH       R31
	PUSH       R27
	IN         R27, SREG+0
	PUSH       R27

;MyProject.c,294 :: 		void vTimer1_ISR() org IVT_ADDR_TIMER1_OVF
;MyProject.c,297 :: 		TCNT1H = 0XF8;
	LDI        R27, 248
	OUT        TCNT1H+0, R27
;MyProject.c,298 :: 		TCNT1L = 0X2F;
	LDI        R27, 47
	OUT        TCNT1L+0, R27
;MyProject.c,299 :: 		uci++;
	LDS        R16, _uci+0
	LDS        R17, _uci+1
	MOVW       R18, R16
	SUBI       R18, 255
	SBCI       R19, 255
	STS        _uci+0, R18
	STS        _uci+1, R19
;MyProject.c,300 :: 		if(uci>1000)
	LDI        R16, 232
	LDI        R17, 3
	CP         R16, R18
	CPC        R17, R19
	BRLO       L__vTimer1_ISR39
	JMP        L_vTimer1_ISR18
L__vTimer1_ISR39:
;MyProject.c,302 :: 		uci = 0;
	LDI        R27, 0
	STS        _uci+0, R27
	STS        _uci+1, R27
;MyProject.c,303 :: 		bSec = 1;
	LDS        R27, _bSec+0
	SBR        R27, BitMask(_bSec+0)
	STS        _bSec+0, R27
;MyProject.c,304 :: 		}
L_vTimer1_ISR18:
;MyProject.c,305 :: 		}
L_end_vTimer1_ISR:
	POP        R27
	OUT        SREG+0, R27
	POP        R27
	POP        R31
	POP        R30
	RETI
; end of _vTimer1_ISR

_vInitTimer_1:

;MyProject.c,306 :: 		void vInitTimer_1(void)
;MyProject.c,309 :: 		CS10_bit  = 0;
	IN         R27, CS10_bit+0
	CBR        R27, 1
	OUT        CS10_bit+0, R27
;MyProject.c,310 :: 		CS11_bit  = 1;
	IN         R27, CS11_bit+0
	SBR        R27, 2
	OUT        CS11_bit+0, R27
;MyProject.c,311 :: 		CS12_bit  = 0;
	IN         R27, CS12_bit+0
	CBR        R27, 4
	OUT        CS12_bit+0, R27
;MyProject.c,312 :: 		TOIE1_bit = 1;
	IN         R27, TOIE1_bit+0
	SBR        R27, 4
	OUT        TOIE1_bit+0, R27
;MyProject.c,313 :: 		TCNT1H    = 0;
	LDI        R27, 0
	OUT        TCNT1H+0, R27
;MyProject.c,314 :: 		TCNT1L    = 0;
	LDI        R27, 0
	OUT        TCNT1L+0, R27
;MyProject.c,315 :: 		}
L_end_vInitTimer_1:
	RET
; end of _vInitTimer_1

_vInitDefaultData:

;MyProject.c,316 :: 		void vInitDefaultData(void)
;MyProject.c,318 :: 		}
L_end_vInitDefaultData:
	RET
; end of _vInitDefaultData

_vClearBuffer:

;MyProject.c,319 :: 		void vClearBuffer(void)
;MyProject.c,321 :: 		unsigned char ucCounter=0;
;MyProject.c,322 :: 		for(ucCounter=0;ucCounter<20;ucCounter++)
; ucCounter start address is: 18 (R18)
	LDI        R18, 0
; ucCounter end address is: 18 (R18)
L_vClearBuffer19:
; ucCounter start address is: 18 (R18)
	CPI        R18, 20
	BRLO       L__vClearBuffer43
	JMP        L_vClearBuffer20
L__vClearBuffer43:
;MyProject.c,324 :: 		ucPacket[ucCounter] = 0x00;
	LDI        R16, #lo_addr(_ucPacket+0)
	LDI        R17, hi_addr(_ucPacket+0)
	MOV        R30, R18
	LDI        R31, 0
	ADD        R30, R16
	ADC        R31, R17
	LDI        R27, 0
	ST         Z, R27
;MyProject.c,322 :: 		for(ucCounter=0;ucCounter<20;ucCounter++)
	MOV        R16, R18
	SUBI       R16, 255
	MOV        R18, R16
;MyProject.c,325 :: 		}
; ucCounter end address is: 18 (R18)
	JMP        L_vClearBuffer19
L_vClearBuffer20:
;MyProject.c,326 :: 		}
L_end_vClearBuffer:
	RET
; end of _vClearBuffer
