#include "Dio.h"
#include "delay.h"

#define SCK DIO_CHANNEL_PA0
#define MISO DIO_CHANNEL_PA1
#define MOSI DIO_CHANNEL_PA2
#define SS DIO_CHANNEL_PA3
#define btn DIO_CHANNEL_PC13
void SPI_Soft_init(void);
void Clock(void);
void SPI_Soft_Transmit(uint8_t data);
uint8_t SPI_Soft_Receive(void);
int main(void)
{
	config(SCK, OUTPUT);
	config(MOSI, OUTPUT);
	config(SS, OUTPUT);
	config(btn, INPUT_PULLUP);
	SPI_Soft_init();
	while(1)
	{
		if(Dio_ReadChannel(btn) == STD_LOW)
		{		
			uint8_t data = 0b10101010;
			SPI_Soft_Transmit(data);
		}
	}
}
void SPI_Soft_init(void){
	Dio_WriteChannel(SCK,STD_LOW);
	Dio_WriteChannel(MOSI, STD_LOW);
	Dio_WriteChannel(SS, STD_HIGH);
}

void Clock(void){
	Dio_WriteChannel(SCK, STD_HIGH);
	DelayMs(100);
	Dio_WriteChannel(SCK, STD_LOW);
	DelayMs(100);
}

void SPI_Soft_Transmit(uint8_t data){
	Dio_WriteChannel(SS, STD_LOW);
	uint8_t i ;
	for (i = 0;i < 8;i++)
	{
		if((data & 0x80) != 0) Dio_WriteChannel(MOSI,STD_HIGH);
		else Dio_WriteChannel(MOSI,STD_LOW);
		Clock();
		data = data << 1;
	}
	Dio_WriteChannel(SS, STD_HIGH);
}
uint8_t SPI_Soft_Receive(void){
	
	uint8_t data = 0;
	uint8_t MOSI_Data;
	uint8_t SCK_State;
	uint8_t i = 0;
	
	while( i < 8)
	{
		SCK_State = Dio_ReadChannel(SCK);
		if(SCK_State == 1){
			MOSI_Data = Dio_ReadChannel(MOSI);
			data = data << 1;
			data = data | MOSI_Data;
			i++;
			while(SCK_State == 1) SCK_State = Dio_ReadChannel(SCK);
		}
	}
	if(i == 8)
  {
    i = 0;
    data = 0;
    MOSI_Data = 0;
		return data;
  }
}