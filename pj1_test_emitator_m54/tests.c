/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "tests.h"
#include "string.h"
#include <Windows.h>
#include <MATH.h>
#include <time.h>

#define u32 unsigned int
#define u16 unsigned short

// длина массива в 32-разрядных словах
#define ARRAY_LEN 8
unsigned int OutputArray [ARRAY_LEN] __attribute__ ((aligned (8))) = {0,};
unsigned int InputArray1 [ARRAY_LEN] __attribute__ ((aligned (8))) = {0,};
unsigned int InputArray2 [ARRAY_LEN] __attribute__ ((aligned (8))) = {0,};

extern char TEST_var;

void array_init (u32 *a,u32 n,u16 test)
{
	unsigned int i=0;
	unsigned int z=0;

	for (i=0;i<n;i++)
	{
		z=((test&0xffff)<<16)|i;
		a[i]=z;
	}
}


#define Bufer_size 64000
char strng[64];
char msg[Bufer_size];
extern char buff[64000];//буфер UDP смотри в main.c
u32 text_lengh=0;

void Transf (char * s)
{
	u32 l=0;
	u32 i=0;
	l=strlen(s);
	if ((text_lengh+l)>Bufer_size-5) text_lengh=0;
	for (i=text_lengh;i<(text_lengh+l);i++) msg[i]=s[i-text_lengh];
	text_lengh=text_lengh+l;
}

void d_out (char s[],int a)
{
	Transf(s);
	sprintf(strng,"%d",a);
	Transf(strng);
}

void dn_out (char s[],int a)
{
	Transf(s);
	sprintf(strng,"%d\n\r",a);
	Transf(strng);
}

void Transf_Data (char * s,int leng)
{
	u32 l=0;
	u32 i=0;
	l=leng;
	if ((text_lengh+l)>Bufer_size-5) text_lengh=0;
	for (i=text_lengh;i<(text_lengh+l);i++) msg[i]=s[i-text_lengh];
	text_lengh=text_lengh+l;
}

void data_out (int a)
{
    strng[0]=(a>>24)&0xff;
    strng[1]=(a>>16)&0xff;
    strng[2]=(a>> 8)&0xff;
    strng[3]=(a>> 0)&0xff;
	Transf_Data(strng,4);
}

FILE *fp;
char name[] = "my.txt";
//char BUFFER_FILE [32000];
#define SIZE_DATA 4096 //в словах
char * Resive_text;

void init_LANE (u32 data)
{
//	int error=0;
    u32 i =0;
	u32 z =0;
	u32 z1=0;
	u32 z2=0;

	u32 dma1_des =0;
	u32 dma1_data=0;

	u32 dma2_des =0;
	u32 dma2_data=0;

	u32 N_pack1=0;
	u32 N_pack2=0;

	u32 N_v1=0;
	u32 N_v2=0;

	u32 flag=0;
	extern manager_main manager; //тут хранятся адреса дескрипторов RX и TX
	u32 addr = 0;
	u32 col=SIZE_DATA;
	u32 status1 = 0;
	u32 status2 = 0;

//	array_init (&OutputArray,col,data);//заполняем отправляемый массив тестовыми данными

	/*
	for (i=0;i<col;i++){	printf ("%x\n",OutputArray[i]);	}
	*/
    printf("\ninit_manager\n");

//	mcb_enable_interrupt(int_swic1_rx_desc);
//	mcb_enable_interrupt(int_swic1_rx_data);
//	mcb_enable_interrupt(int_swic2_rx_desc);
//	mcb_enable_interrupt(int_swic2_rx_data);
    printf("\nmanager_swic_reset\n");


//	manager_swic_reset(1);
//	manager_swic_reset(2);
	printf("\ninit_LANE\n");

	printf("\nwait LINK 1,2\n\n");

//	setvbuf (fp,BUFFER_FILE,_IOFBF,32000);

if ((fp = fopen(name,"w"))==NULL)
	{
		printf("Не удалось открыть файл\r\n");
		getchar();
		return 0;
	}

	//удалось открыть файл


//----------------------------------------------
//CopyBoard("0");

while (1)
{
	usleep(50000);

		sw_out (i++);


}
//fclose(fp);

}

//--------------------------------------
//----------функция шума----------------
const float RAND_MAX_F = RAND_MAX;

float get_rand() {
    return rand() / RAND_MAX_F;
}
//--------------------------------------

extern int FREQ_GEN;

void test_to_data (unsigned int port,unsigned int size)
{
	 int i=0;

    unsigned int reg = 0;
	double A1=0;
	double A2=0;
	double A3=0;
	double A4=0;
	double A5=0;
	double A6=0;
	double A7=200;//амплитуда шума
	double A_gen=20000;
	double F1=0;
	double F2=0;
	double F3=0;
	double F4=0;
	double F5=0;
	double F6=0;
	double F7=0;
	double F_gen=0;
	double freq1=10;
	double freq2=-3000;
	double freq3=-1561;
	double freq4=500;
	double freq5=1561;
	double freq6=3000;
	double freq_gen=0;
	double Fclk=6250;//KHz
	double pi=3.1415926535;

	double M=0;
	
//	freq_gen=(100000000-(((double)(FREQ_GEN))-360000000))-25000000;
	freq_gen=(double)(FREQ_GEN);
	freq_gen=freq_gen/1000;
	
    data_out(port);  //отправляем номер входа 1 или 0 ( у поделки)
  for(i=0;i<size;i++)//изменил начало индекса!!!!
    {
        F7=A7*get_rand();//генерируем шум
		F1=((int)(A1*(cos(i*2*pi*freq1/Fclk)))<<16)+A1*(sin(i*2*pi*freq1/Fclk));
		F2=((int)(A2*(cos(i*2*pi*freq2/Fclk)))<<16)+A2*(sin(i*2*pi*freq2/Fclk));
		F3=((int)(A3*(cos(i*2*pi*freq3/Fclk)))<<16)+A3*(sin(i*2*pi*freq3/Fclk));
		F4=((int)(A4*(cos(i*2*pi*freq4/Fclk)))<<16)+A4*(sin(i*2*pi*freq4/Fclk));
		F5=((int)(A5*(cos(i*2*pi*freq5/Fclk)))<<16)+A5*(sin(i*2*pi*freq5/Fclk));
		F6=((int)(A6*(cos(i*2*pi*freq6/Fclk)))<<16)+A6*(sin(i*2*pi*freq6/Fclk));
		
		F_gen=((int)(A_gen*(cos(i*2*pi*freq_gen/Fclk)))<<16)+A_gen*(sin(i*2*pi*freq_gen/Fclk));
		
        reg=F_gen+F1+F2+F3+F4+F5+F6+F7-(A7/2);
        M=(M+reg)/2;
    //  reg=reg-M;
        data_out(reg);
//      printf ("reg:%d\n",reg);
    }
}

void sw_out (unsigned int a)
{
u32 dma1_des =0;
u32 dma1_data=0;
u32 dma2_des =0;
u32 dma2_data=0;

u32 N_pack1=0;
u32 N_pack2=0;

u32 N_v1=0;
u32 N_v2=0;

u32 flag=0;
extern manager_main manager; //тут хранятся адреса дескрипторов RX и TX
u32 addr = 0;
u32 col=SIZE_DATA;
u32 status1 = 0;
u32 status2 = 0;
u32 N_col=SIZE_DATA;

//--------------------------------------------------------------------------

//    strnset(msg,0x00,Bufer_size);//очищаем транспортный буфер
    text_lengh=0;//сбрасываем счётчик данных в msg

test_to_data (1,N_col);
UDP_transmit ();

//    strnset(msg,0x00,Bufer_size);//очищаем транспортный буфер
    text_lengh=0;//сбрасываем счётчик данных в msg
test_to_data (2,N_col);
UDP_transmit ();

//	printf(msg);
//	UDP_transmit ();
}

void UDP_transmit ()
{
    int i=0;
    int k=0;
    int l=0;
    k=text_lengh;
    for (i=0;i<k;i++)
    {
        buff[i]=msg[i];
  //     if (i<50) printf ("buff[i]:%d\n",buff[i]);
    }
    UDP_work(k);

}
