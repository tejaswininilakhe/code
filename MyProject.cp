#line 1 "C:/Users/V/Desktop/Code/MyProject.c"




bit bSec;
#line 26 "C:/Users/V/Desktop/Code/MyProject.c"
unsigned char ucInv_OP[] = {0x01,0x03,0xA2,0x18,0x00,0x01,0x27,0xB5};
unsigned char ucRunF_R[] = {0x01,0x03,0xA0,0xE8,0x00,0x01,0x27,0x3E};

unsigned char ucInStat_1_ON[] = {0x01,0x06,0x9D,0x17,0x00,0x40,0x17,0x92};
unsigned char ucInStat_2_ON[] = {0x01,0x06,0x9C,0x49,0x00,0x41,0xD6,0x52};



unsigned char ucInStat_1_OFF[] = {0x01,0x06,0x9D,0x17,0x00,0x00,0x16,0x62};
#line 39 "C:/Users/V/Desktop/Code/MyProject.c"
unsigned char ucInv_Stat_ON[] = {0x01,0x06,0x9C,0x49,0x00,0x01,0xB7,0x8C};
unsigned char ucInv_Stat_OFF[] = {0x01,0x06,0x9C,0x49,0x00,0x01,0x76,0x4E};

void USART_Init(void);
void USART_SendByte(unsigned char u8Data);
void vInitTimer_1(void);
void vClearBuffer(void);
void vSendPacket(unsigned char *Data,unsigned char ucLen);

unsigned int uiInv_OP;
unsigned int uiRunF_R;
unsigned int uiInStat_1,uiInStat_2,uiInv_Stat_ON, uiInv_Stat_OFF;
unsigned char ucBuff[50];
unsigned char ucPacketIndex;
unsigned char ucPacket[20];
bit bCommStatus;
unsigned char ucKeyPress;

void main()
{

  PORTC0_bit  = 1;
  DDB5_bit  = 0;
 USART_Init();
 vInitTimer_1();
 PORTD2_bit = 1;

 SREG_I_bit = 0;
 RXEN_bit = 0;

 USART_SendByte('M');
 USART_SendByte('I');
 USART_SendByte('C');
 USART_SendByte('R');
 USART_SendByte('O');
 USART_SendByte('L');
 USART_SendByte('O');
 USART_SendByte('G');
 SREG_I_bit = 1;
 RXEN_bit = 1;
  PORTC0_bit  = 0;
 vClearBuffer();
 while(1)
 {
  PORTC0_bit  = ~ PORTC0_bit ;
 delay_ms(1000);
#line 124 "C:/Users/V/Desktop/Code/MyProject.c"
 ucPacketIndex=0;
 SREG_I_bit = 0;
 RXEN_bit = 0;
 vSendPacket(&ucInStat_1_ON,8);
 SREG_I_bit = 1;
 RXEN_bit = 1;
 delay_ms(1000);
 if(ucPacket[2] != 0x86 && ucPacket[1] != 0x00)
 {
 uiInStat_1 = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
 bCommStatus = 1;
 }
 else
 {
 bCommStatus = 0;
 }
 vClearBuffer();
#line 244 "C:/Users/V/Desktop/Code/MyProject.c"
 }
}
void vSerialRx_ISR() org IVT_ADDR_USART__RXC
{
 unsigned char dmxByte;
 if ( FE_bit)
 {
 dmxByte = UDR0;
 }
 else
 {
 dmxByte = UDR0;
 ucPacket[ucPacketIndex]=dmxByte;
 ucPacketIndex++;
  PORTC0_bit  = ~ PORTC0_bit ;
 }
}
void USART_Init(void){
 if(1)
 {
 UBRRH =  9600  >> 8;
 UBRRL =  9600 ;

 }
 else
 {
 }
 TXEN_bit = 1;
 RXEN_bit = 1;
 RXCIE_bit = 1;

}
void USART_SendByte(unsigned char u8Data)
{


 UDR = u8Data;
 while(UDRE_bit == 0);
}
void vSendPacket(unsigned char *Data,unsigned char ucLen)
{
 unsigned char ucCount=0;
 while(ucLen)
 {
 ucLen--;
 USART_SendByte(Data[ucCount]);
 ucCount++;
 }
}
unsigned int uci;
void vTimer1_ISR() org IVT_ADDR_TIMER1_OVF
{

 TCNT1H = 0XF8;
 TCNT1L = 0X2F;
 uci++;
 if(uci>1000)
 {
 uci = 0;
 bSec = 1;
 }
}
void vInitTimer_1(void)
{

 CS10_bit = 0;
 CS11_bit = 1;
 CS12_bit = 0;
 TOIE1_bit = 1;
 TCNT1H = 0;
 TCNT1L = 0;
}
void vInitDefaultData(void)
{
}
void vClearBuffer(void)
{
 unsigned char ucCounter=0;
 for(ucCounter=0;ucCounter<20;ucCounter++)
 {
 ucPacket[ucCounter] = 0x00;
 }
}
