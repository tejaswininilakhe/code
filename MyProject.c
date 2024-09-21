/********************************************************************************/
Code written by Tejaswini.
 Code to write Modbus Specific Loacations.
 Code to read Specific Modbus Location.
 /*******************************************************************************/
#define START_TIMER_1   CS10_bit = 0;CS11_bit = 1;CS12_bit = 0;
#define STOP_TIMER_1   CS10_bit = 0;CS11_bit = 0;CS12_bit = 0;
#define CLEAR_TIMER_1  TCNT1H=0;TCNT1L=0;
bit bSec;

#define LED_DDR  DDB5_bit
#define LED_DATA PORTC0_bit

//sbit  rs485_rxtx_pin  at PORTD0_bit;//PORTD2_bit;         // set transcieve pin
//sbit  rs485_rxtx_pin_direction at DDD2_bit;//DDD2_bit;  // set transcieve pin direction

#define F_CPU                    8000000
#define USART_BAUDRATE_9600         9600
#define USART_BAUDRATE_14400       14400
#define USART_BAUDRATE_19200       19200

#define BAUD_PRESCALE_9600      (((F_CPU / (USART_BAUDRATE_9600 * 16UL))) - 1)
#define BAUD_PRESCALE_14400     (((F_CPU / (USART_BAUDRATE_14400 * 16UL))) - 1)
#define BAUD_PRESCALE_19200     (((F_CPU / (USART_BAUDRATE_19200 * 16UL))) - 1)
/*
unsigned char  ucVoltage[] = {0x01,0x03,0x63,0x06,0x00,0x01,0x7A,0x4F};
unsigned char  ucCurrent[] = {0x01,0x03,0x63,0x02,0x00,0x01,0x3B,0x8E};
unsigned char  ucFreq[]    = {0x01,0x03,0x63,0x01,0x00,0x01,0xCB,0x8E}; */
/************************Read Status**********************************/
unsigned char  ucInv_OP[] = {0x01,0x03,0xA2,0x18,0x00,0x01,0x27,0xB5};
unsigned char  ucRunF_R[] = {0x01,0x03,0xA0,0xE8,0x00,0x01,0x27,0x3E};
/************************Write Status**********************************/
unsigned char  ucInStat_1_ON[]  = {0x01,0x06,0x9D,0x17,0x00,0x40,0x17,0x92};
unsigned char  ucInStat_2_ON[]  = {0x01,0x06,0x9C,0x49,0x00,0x41,0xD6,0x52};
//unsigned char  ucInStat_3_ON[]  = {0x01,0x06,0x9D,0x17,0x00,0x42,0x96,0x53};


unsigned char  ucInStat_1_OFF[] = {0x01,0x06,0x9D,0x17,0x00,0x00,0x16,0x62};

/*unsigned char  ucInStat_2_ON[]  = {0x01,0x06,0x9D,0x18,0x00,0x01,0xE7,0xA1};
unsigned char  ucInStat_2_OFF[] = {0x01,0x06,0x9D,0x18,0x00,0x00,0x26,0x61};
  */
unsigned char  ucInv_Stat_ON[]  = {0x01,0x06,0x9C,0x49,0x00,0x01,0xB7,0x8C};
unsigned char  ucInv_Stat_OFF[] = {0x01,0x06,0x9C,0x49,0x00,0x01,0x76,0x4E};

void USART_Init(void);
void USART_SendByte(unsigned char u8Data);
void vInitTimer_1(void);
void vClearBuffer(void);
void vSendPacket(unsigned char *Data,unsigned char ucLen);

unsigned int uiInv_OP;  //uiVoltage;
unsigned int uiRunF_R;  //uiCurrent;
unsigned int uiInStat_1,uiInStat_2,uiInv_Stat_ON, uiInv_Stat_OFF;
unsigned char ucBuff[50];
unsigned char ucPacketIndex;
unsigned char ucPacket[20];
bit bCommStatus;
unsigned char ucKeyPress;

void main()
{

    LED_DATA = 1;
    LED_DDR  = 0;
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
   LED_DATA = 0;
   vClearBuffer();
   while(1)
   {
     LED_DATA = ~LED_DATA;
     delay_ms(1000);
    /************************* Inverter Output ********************************/
     /*ucPacketIndex=0;
     SREG_I_bit = 0;
     RXEN_bit = 0;
     vSendPacket(&ucInv_OP,8);
     SREG_I_bit = 1;
     RXEN_bit = 1;
     delay_ms(1000);
     if(ucPacket[2] != 0x83 && ucPacket[1] != 0x00)
     {
       uiInv_OP = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
       bCommStatus = 1;
     }
     else
     {
       bCommStatus = 0;
     }
     vClearBuffer(); */
     /************************ Run _Forward_Reverse ****************************/
     /*ucPacketIndex=0;
     SREG_I_bit = 0;
     RXEN_bit = 0;
     vSendPacket(&ucRunF_R,8);
     SREG_I_bit = 1;
     RXEN_bit = 1;
     delay_ms(1000);
     if(ucPacket[2] != 0x83 && ucPacket[1] != 0x00)
     {
       uiRunF_R = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
       bCommStatus = 1;
     }
     else
     {
       bCommStatus = 0;
     }
     vClearBuffer();    */
     /************************* Input Status 1 *****************************/
    // if(PORTB1_bit)
     //{
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
       
       
     /*}
     else
     {
       ucPacketIndex=0;
       SREG_I_bit = 0;
       RXEN_bit = 0;
       vSendPacket(&ucInStat_1_OFF,8);
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
     }
     vClearBuffer();   */
     /*************************** Input Status 2 ****************************/
     /*if(PORTB2_bit)
     {
       ucPacketIndex=0;
       SREG_I_bit = 0;
       RXEN_bit = 0;
       vSendPacket(&ucInStat_2_ON,8);
       SREG_I_bit = 1;
       RXEN_bit = 1;
       delay_ms(1000);
       if(ucPacket[2] != 0x86 && ucPacket[1] != 0x00)
       {
          uiInStat_2 = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
          bCommStatus = 1;
       }
       else
       {
           bCommStatus = 0;
       }
     }
     else
     {
       ucPacketIndex=0;
       SREG_I_bit = 0;
       RXEN_bit = 0;
       vSendPacket(&ucInStat_2_OFF,8);
       SREG_I_bit = 1;
       RXEN_bit = 1;
       delay_ms(1000);
       if(ucPacket[2] != 0x86 && ucPacket[1] != 0x00)
       {
          uiInStat_2 = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
          bCommStatus = 1;
       }
       else
       {
           bCommStatus = 0;
       }
     }
     vClearBuffer();       */
     /*************************** Inverter Status ***************************/
     /*if(PORTC7_bit)
     {
       ucPacketIndex=0;
       SREG_I_bit = 0;
       RXEN_bit = 0;
       vSendPacket(&ucInStat_2_ON,8);
       SREG_I_bit = 1;
       RXEN_bit = 1;
       delay_ms(1000);
       if(ucPacket[2] != 0x86 && ucPacket[1] != 0x00)
       {
          uiInv_Stat_ON = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
          bCommStatus = 1;
       }
       else
       {
           bCommStatus = 0;
       }
     }
     //else
     {
       ucPacketIndex=0;
       SREG_I_bit = 0;
       RXEN_bit = 0;
       vSendPacket(&ucInStat_2_OFF,8);
       SREG_I_bit = 1;
       RXEN_bit = 1;
       delay_ms(1000);
       if(ucPacket[2] != 0x86 && ucPacket[1] != 0x00)
       {
          uiInv_Stat_OFF = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
          bCommStatus = 1;
       }
       else
       {
           bCommStatus = 0;
       }
     }
     vClearBuffer();*/
     }
}
void vSerialRx_ISR() org IVT_ADDR_USART__RXC      // This funtion is Interrupt Funtion
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
      LED_DATA = ~LED_DATA;
   }
}
void USART_Init(void){
   if(1)
    {
      UBRRH = USART_BAUDRATE_9600 >> 8;
      UBRRL = USART_BAUDRATE_9600;//BAUD_PRESCALE_9600;// Load lower 8-bits into the low byte of the UBRR register
      //(BAUD_PRESCALE_9600 >> 8);
    }
    else
    {
    }
    TXEN_bit = 1;
    RXEN_bit = 1;
    RXCIE_bit = 1;
    //UCSR0B = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE));
}
void USART_SendByte(unsigned char u8Data)
{
    // Wait until last byte has been transmitted
    // Transmit data
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
   //STOP_TIMER_1;
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
    //Init Timer 1
    CS10_bit  = 0;
    CS11_bit  = 1;
    CS12_bit  = 0;
    TOIE1_bit = 1;
    TCNT1H    = 0;
    TCNT1L    = 0;
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

 /*
bool mmodbus_writeHoldingRegister16i(uint8_t slaveAddress, uint16_t number, uint16_t data)
{
  #if( _MMODBUS_RTU == 1)
  uint8_t txData[8];
  txData[0] = slaveAddress;
  txData[1] = 0x06;//MModbusCMD_WriteSingleRegister;
  txData[2] = (number & 0xFF00) >> 8;
  txData[3] = (number & 0x00FF);
  txData[4] = (data & 0xFF00) >> 8;
  txData[5] = data & 0x00FF;
  static uint16_t  crc;
  crc = mmodbus_crc16(txData, 6);
  txData[6] = (crc & 0x00FF);
  txData[7] = (crc & 0xFF00) >> 8;
  mmodbus_sendRaw(txData, 8, 100);
  uint16_t recLen = mmodbus_receiveRaw(mmodbus.timeout);
  if(recLen == 0)
    return false;
  if(memcmp(txData, mmodbus.rxBuf, 8) == 0)
    return true;
  else
    return false;
  #endif
  #if( _MMODBUS_ASCII == 1)

  #endif
}  */
