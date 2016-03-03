#include <16F887.h>
#device *=16 adc=8
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=4000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#include<lcd.h>
/***************************************************************/
/***************************************************************/
char sms[90];
char c=0x00,c1=0x00,c2=0x00,c3=0x00,c4=0x00;
unsigned int8 new_sms=0,i=0,j=0,k=0;
unsigned int8 index=0,interrupt=0;
unsigned int8 status=1;
char st[4];

/***************************************************************/
void _Delete_SMS();
void _Reset_SMS();
void _Send_SMS(unsigned char style);
void _Dial(char number);
void _Delay(int n);
void _Waiting_SIM(void);
void _Startup();
void _Configuration_Sim();
void _Display();
void _Blank();
void _Reset_Buffer(int time);
void _Response(char style);
void _Status_1();
void _Status_2();
void _Status_3();
void _Status_4();
void _Turn_On(char name);
void _Turn_Off(char name);
void _Turn_On_All();
void _Turn_Off_All();

/***************************************************************/
#int_RDA
void  RDA_isr(void)
{
  	c=getc();
    if(c=='+') c1=c;
  	if(c=='C') c2=c;
  	if(c=='M') c3=c;
  	if(c=='T') c4=c;
  	if(c1=='+' && c2=='C' && c3=='M' && c4=='T') new_sms=1;

	if(c!='\0')
	{sms[index++]=c;}

	if(index>=89)
	{
		index=0;
	}

	if(index>5 && new_sms==0)
	{
		interrupt=1;
	}
}
/***************************************************************/
/***************************************************************/
void main()
{
	_Startup();		
  	_Waiting_SIM();
	_Configuration_Sim();_Delay(30);
  	_Send_SMS(1);_Delay(5);_Display();
	_Turn_Off_All();
	_Blank();
	_Status_1();
	_Status_2();
	_Status_3();
	_Status_4();
		
	while(1)
	{			
		lcd_gotoxy(1,1);
		printf(lcd_putc,"TRANG THAI TB            ");
		lcd_gotoxy(1,2);
		printf(lcd_putc,"1%c2%c3%c4%c             ",st[0],st[1],st[2],st[3]);
		
		if(interrupt==1)
		{			
			lcd_gotoxy(1,2);
			printf(lcd_putc,"Interrupting        ");	
			_Delay(10); _Display();_Blank();
		}
		else if(new_sms==1)
		{
			lcd_gotoxy(1,2);
			printf(lcd_putc,"New inbox              ");
			_Delay(10);
			for(j=50;j<80;j++)
			{	
			   if((sms[j]=='x'||sms[j]=='X')&&(sms[j+1]=='o'||sms[j+1]=='O')&&(sms[j+2]=='a'||sms[j+2]=='A'))
				{
					_Blank();
					lcd_gotoxy(1,1);					
					printf(lcd_putc,"%c%c%c             ",sms[j],sms[j+1],sms[j+2]);	
					_Delay(10);
					_Delete_SMS();_Delay(5);_Display();_Blank();
					_Reset_SMS();
					_Response(2);
				}
			   else if((sms[j]=='b'||sms[j]=='B')&&(sms[j+1]=='a'||sms[j+1]=='A')&&(sms[j+2]=='t'||sms[j+2]=='T')&&(sms[j+3]=='h'||sms[j+3]=='H')&&(sms[j+4]=='e'||sms[j+4]=='E')&&(sms[j+5]=='t'||sms[j+5]=='T'))
				{
					_Blank();
					lcd_gotoxy(1,1);					
					printf(lcd_putc,"%c%c%c%c%c%c%c            ",sms[j],sms[j+1],sms[j+2],sms[j+3],sms[j+4],sms[j+5],sms[j+6]);	//sms[j+3]:Ten thiet bi can bat
					_Delay(10);
					_Turn_On_All();
					_Reset_SMS();
					_Response(1);
					break;
				}	
				else if((sms[j]=='t'||sms[j]=='T')&&(sms[j+1]=='a'||sms[j+1]=='A')&&(sms[j+2]=='t'||sms[j+2]=='T')&&(sms[j+3]=='h'||sms[j+3]=='H')&&(sms[j+4]=='e'||sms[j+4]=='E')&&(sms[j+5]=='t'||sms[j+5]=='T'))
				{
					_Blank();
					lcd_gotoxy(1,1);					
					printf(lcd_putc,"%c%c%c%c%c%c%c           ",sms[j],sms[j+1],sms[j+2],sms[j+3],sms[j+4],sms[j+5],sms[j+6]);	//sms[j+3]:Ten thiet bi can bat
					_Delay(10);					
				 	_Turn_Off_All();
					_Reset_SMS();
					_Response(1);			
					break;
				}	
				else if((sms[j]=='b'||sms[j]=='B')&&(sms[j+1]=='a'||sms[j+1]=='A')&&(sms[j+2]=='t'||sms[j+2]=='T'))
				{
					lcd_gotoxy(1,1);					
					printf(lcd_putc,"%c%c%c%c%c             ",sms[j],sms[j+1],sms[j+2],sms[j+3],sms[j+4]);	//sms[j+3]:Ten thiet bi can bat
					_Delay(10);					
					_Turn_On(sms[j+3]);
					_Delay(10);
					_Reset_SMS();
					_Response(1);			
					break;
				}
				else if((sms[j]=='t'||sms[j]=='T')&&(sms[j+1]=='a'||sms[j+1]=='A')&&(sms[j+2]=='t'||sms[j+2]=='T'))
				{
					lcd_gotoxy(1,1);					
					printf(lcd_putc,"%c%c%c%c%c             ",sms[j],sms[j+1],sms[j+2],sms[j+3],sms[j+4]);	//sms[j+3]:Ten thiet bi can bat
					_Delay(10);						
					_Turn_Off(sms[j+3]);
					_Delay(10);
					_Reset_SMS();
					_Response(1);
					break;
				}						
			}
			_Delay(5);_Display();_Blank();
		}		
	}
}
/***************************************************************/
/***************************************************************/
void _Delete_SMS()
{
  	printf("AT+CMGD=1,4\r\n");
  	_Delay(5);
}

void _Reset_SMS()
{
	int k;
	for(k=0;k<90;k++)
	{
		sms[k]='\0';
	}
	c1=c2=c3=c4='\0';
	new_sms=0;
	index=0;
	interrupt=0;
	i=j=k=0;
}

void _Response(char style)
{
	if(style==1)
	{
		printf("AT+CMGS=\"01639091561\"\r\n");
	  	_Delay(5);
		printf("1%c2%c3%c4%c",st[0],st[1],st[2],st[3]);
	  	_Delay(5);
	  	putc(26);
	  	_Delay(5);	
	}
	else if(style==2)
	{
		printf("AT+CMGS=\"01639091561\"\r\n");
	  	_Delay(5);
		printf("Delete Successfully!");
	  	_Delay(5);
	  	putc(26);
	  	_Delay(5);	
	}
}

void _Send_SMS(unsigned char style)
{
	printf("AT+CMGS=\"01639091561\"\r\n");
  	_Delay(5);
	switch(style)
	{
		case 1:
		{
			printf("I Am Ready!\r\nPlease Give Me Order! ");
			break;
		}
		case 2:
		{
			printf("OK ");
			break;
		}
		case 3:
		{
			printf("Error");
			break;
		}
	}
  	_Delay(5);
  	putc(26);
  	_Delay(5);
}

void _Delay(int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		delay_ms(100);
	}
}

void _Waiting_SIM(void)
{
  	lcd_gotoxy(1,1);
	printf(lcd_putc,"I Am Busy ");
	_Delay(30);
  	lcd_gotoxy(1,1);
	printf(lcd_putc,"I Am Busy. ");
	_Delay(30);
  	lcd_gotoxy(1,1);
	printf(lcd_putc,"I Am Busy.. ");
	_Delay(20);
  	lcd_gotoxy(1,1);
	printf(lcd_putc,"I Am Busy... ");
	_Delay(20);
	_Turn_Off_All();
}

void _Turn_Off(char name)
{
	int delay=1;
	switch(name)
	{
		case'1':
		{
			output_high(PIN_C0);
			st[0]='0';
			_Delay(delay);
			break;
		}
		case'2':
		{
			output_high(PIN_C1);
			st[1]='0';
			_Delay(delay);
			break;
		}
		case'3':
		{
			output_high(PIN_C2);
			st[2]='0';
			_Delay(delay);
			break;
		}
		case'4':
		{
			output_high(PIN_C3);
			st[3]='0';
			_Delay(delay);
			break;
		}	
		default:
		{

			break;
		}	
	}
}

void _Turn_On(char name)
{
	int delay=1;
	switch(name)
	{
		case'1':
		{
			output_low(PIN_C0);
			st[0]='#';
			_Delay(delay);
			break;
		}
		case'2':
		{
			output_low(PIN_C1);
			st[1]='#';
			_Delay(delay);
			break;
		}
		case'3':
		{
			output_low(PIN_C2);
			st[2]='#';
			_Delay(delay);
			break;
		}
		case'4':
		{
			output_low(PIN_C3);
			st[3]='#';
			_Delay(delay);
			break;
		}
		default:
		{

			break;
		}	
	}
}

void _Startup()
{
	PORT_B_PULLUPS(0xFF);
	ENABLE_INTERRUPTS(INT_RDA); 
	ENABLE_INTERRUPTS(GLOBAL); 
	output_high(PIN_A0);
   	_Turn_Off_All();
  	lcd_init();
	_Blank();
}

void _Configuration_Sim()
{
	printf("AT\r\n");_Delay(3);_Display();
	_Turn_Off_All();
//	printf("ATZ\r\n");_Delay(3);_Display();
//	printf("ATE1\r\n");_Delay(3);_Display();
//	printf("AT+ICF=3,3\r\n");_Delay(3);_Display();
//	printf("AT+IPR=9600\r\n");_Delay(5);_Display();
//	printf("AT&W\r\n");_Delay(5);_Display();
//	printf("AT+CMGF=1\r\n");_Delay(3);_Display();
//	printf("AT+CNMI=2,2,0,0,0\r\n");_Delay(5);_Display();
//	printf("AT+CSAS\r\n");_Delay(5);_Display();
	printf("AT+CMGD=1,4\r\n");_Delay(5);_Display();_Blank();
	_Turn_Off_All();
}

void _Display()
{
	_Blank();
	lcd_gotoxy(1,1);
	printf(lcd_putc,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",sms[0],sms[1],sms[2],sms[3],sms[4],sms[5],sms[6],sms[7],	sms[8],sms[9],sms[10],sms[11],sms[12],sms[13],sms[14],sms[15]);
	_Delay(10);	
	_Reset_SMS();
}

void _Blank()
{
	lcd_putc('\f');_Delay(1);	
}

void _Reset_Buffer(int time)
{
	int k,n;
	for(n=0;n<time;n++)
	{
		for(k=0;k<90;k++)
		{
			sms[k]='\0';
		}
		c1=c2=c3=c4='\0';
		new_sms=0;
		index=0;
		interrupt=0;
		i=j=k=0;	
		_Delay(1);
	}
	_Blank();
}

void _Status_1()
{
	if(INPUT(PIN_C0)==0)
	{
		st[0]='#';
	}
	else 
	{
		st[0]='0';
	}
}

void _Status_2()
{
	if(INPUT(PIN_C1)==0)
	{
		st[1]='#';
	}
	else
	{
		st[1]='0';
	}
}

void _Status_3()
{
	if(INPUT(PIN_C2)==0)
	{
		st[2]='#';
	}
	else 
	{
		st[2]='0';
	}
}

void _Status_4()
{
	if(INPUT(PIN_C3)==0)
	{
		st[3]='#';
	}
	else
	{
		st[3]='0';
	}
}

void _Turn_Off_All()
{
	int i=0;
	output_high(PIN_C0);
	output_high(PIN_C1);
	output_high(PIN_C2);
	output_high(PIN_C3);
	output_high(PIN_C4);
	output_high(PIN_C5);
	output_high(PIN_D0);
	output_e(0xFF);
	for(i=0;i<4;i++)
	{st[i]='0';}
}

void _Turn_On_All()
{
	int i=0;
	output_low(PIN_C0);
	output_low(PIN_C1);
	output_low(PIN_C2);
	output_low(PIN_C3);
	output_low(PIN_C4);
	output_low(PIN_C5);
	output_low(PIN_D0);
	output_e(0x00);
	for(i=0;i<4;i++)
	{st[i]='#';}
}
