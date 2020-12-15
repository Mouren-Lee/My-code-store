#include "MainWork.h"
#include "IOManage.h"
#include "USART1.h"
#include "USART2.h"
#include "USART3.h"
#include "USART4.h"
#include "DACCtrl.h"
#include "VSPIDAC.h"
#include "stm32f10x.h"
#include "PipeData.h"
#include "PlusOut.h"
//#include "GUI.h"
#include "ADC.h"
#include "PIPE.h"
#include "smec98spManage.h"
/*---------------------------------------��������---------------------------------------------------------------*/
u8 Led_flag=0;

//-----------------------------------------------------------------------




u16 ii=0;
u8 AD_flag=0;
u32 ADCTEMP1=0;
u32 ADCTEMP2=0;
u8 ADCTEMP1_js=0;
u8 ADCTEMP2_js=0;
u16 ComTest_js=0;		
	
	
	
//------------------------------------------------------------------------ 
u16 GK1Buf[4];
u16 GK1Space; 
//-------------------------------------------------------------------------  
 
u8 DuiJiaCS_flag=0; 
u8 ChuiQiCS_flag=0; 
u8 DangBanCS_flag=0; 
u8 YaLiaoCS_flag=0; 
u8 ShuSongCS_flag=0; 


extern u16  Master_ReadReg[100];
extern u8 JiaMi1_flag;   
//----------------------
Sys_Flag Sys_Data;
Time_Flag Time_Data;
//=============================================================
 //�ṹ���ʼ��
 void Typedef_Init(void)
 {
	Time_Data.ChuiQic_Time = 0;
	Time_Data.YaLiaoc_Time = 0;
	Sys_Data.Start_Flag = 0;
	Time_Data.Run_Time = 0;
	Time_Data.Buzzer_Time = 0;
	Sys_Data.BuzzerS_Flag = FALSE;
	Sys_Data.StartIO_Flag = FALSE;
	Sys_Data.BuzzerJs_Flag = FALSE;
	Sys_Data.Count_Pause = FALSE; 
	Sys_Data.Stop_Flag = FALSE;
	Sys_Data.Stop_Button = FALSE;
	Sys_Data.HighStop_Flag = FALSE;
	Sys_Data.Count_Cnt = FALSE;
	Sys_Data.Mode_Flag = 0;
	Sys_Data.Tran_Flag = 0;
	Time_Data.Tran_Time = 0;
	Sys_Data.Start_Button = FALSE;
	Sys_Data.X01_Flag = FALSE;
	Sys_Data.YaLiao_Flag = FALSE;
}
//*************************************************************************
//**********************************��λ�ӳ���****************************************
void SysStop()
{
	IO_SetDO32(0);


	USART1_SetIO(USART_START_IN,0);							   //����𶯱�־
	USART1_SetIO(USART_STOP_IN,0);							   //���ֹͣ��־
	USART1_SetIO(USART_STOP_F,0);								   //���ǿ��ֹͣ��־
	USART1_SetBuf(WORK_INF,WORK_STOP);	


	
  Sys_Data.Count_Cnt = FALSE;
  Sys_Data.BuzzerJs_Flag = FALSE;   
  Sys_Data.Tran_Flag = 0;
  Time_Data.Tran_Time = 0;
  Time_Data.Buzzer_Time = 0;
  Sys_Data.Count_Pause = FALSE;
  Sys_Data.StartIO_Flag = FALSE;
  Sys_Data.BuzzerS_Flag = FALSE;
  Time_Data.Run_Time = 0;		
  Sys_Data.Start_Flag = 0;	
  Sys_Data.Stop_Flag = FALSE;	
  Sys_Data.Stop_Button = FALSE;		
  Sys_Data.HighStop_Flag = FALSE;
  Time_Data.ChuiQic_Time = 0;
  Time_Data.YaLiaoc_Time = 0;
  DuiJiaCS_flag=0; 
  ChuiQiCS_flag=0; 
  DangBanCS_flag=0; 
  YaLiaoCS_flag=0; 
  ShuSongCS_flag=0; 
  Sys_Data.Mode_Flag = 0;	
  PIPE_SaveFlash();
  Typedef_Init();
}


 
 /////////////////////////ZXS

 /////////////////////////ZXS
 

void InAction(u32 TimChg)   //�������ӿڴ���
{
//========================START===========================================
	if( IO_GetDIChange( DI_FUWEI ) ) {  //��Ӹ�λ
       USART1_SetIO(USART_STOP_F,!IO_GetDI(DI_FUWEI));
	}	
	//----------------------------------------------------------	
	//&&&&&&&&&&&&&&&&&���ֹͣ   X08  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&			
 	if( IO_GetDIChange( DI_STOP ) && !IO_GetDI( DI_STOP ) ) {	      //
		USART1_SetIO(USART_STOP_IN,1);		
	}
	//----------------------------------------------------------	
	//&&&&&&&&&&&&&&&&&�����  X07  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&						
	if( !IO_GetDI( DI_START ) && Sys_Data.Start_Flag == 0 && IO_GetDI( DI_STOP ) ) {   // ������ʱ	
		Sys_Data.StartIO_Flag = TRUE;
		Sys_Data.BuzzerS_Flag = TRUE;   //������
		if( TimChg & BIT4 ) {   //8ms
			Time_Data.Run_Time ++;
			if( Time_Data.Run_Time > USART1_GetBuf( QiDong_Dealy ) ) {
				Sys_Data.BuzzerS_Flag = FALSE;
				Time_Data.Run_Time = 0;
				if( !USART1_GetBuf( SYSTEM1_Time ) ) { 
				  	USART1_SetBuf( WORK_INF , WORK_SYSTEM1 );  
				}					
   			  	else if( JiaMi1_flag == 1 ) {
				  	   
				}	
 				else {
				//-------------------
					Sys_Data.Start_Flag = 1;	
           			Sys_Data.StartIO_Flag = FALSE;					
				//-----------------
					USART1_SetBuf( WORK_INF , WORK_RUN );
            		USART1_SetIO( USART_START_IN , 1 );	
				}
			}
		}	
	}	
    else if( Sys_Data.StartIO_Flag ) {
		Time_Data.Run_Time = 0;
		Sys_Data.BuzzerS_Flag = FALSE;	
		Sys_Data.StartIO_Flag = FALSE;
	}	
//=============================END========================================	
}

//-------------------------------------------


//-----------------------------------------------------------





//**********************************���߼��ӳ���****************************************
void MainLogic(u32 TimChg)
//=============================START=================================
{
	u16 tmp,tmp1;
	u32 tmp32;
//-----------------------------------------------
	if( Sys_Data.Start_Flag == 1 ) {	//����״̬��
		if( Sys_Data.Stop_Button ) {   //����״̬�� ֹͣ
			Sys_Data.Stop_Button = FALSE;
			Sys_Data.HighStop_Flag = TRUE;
		}
	//------------------------------------------------------------------------------------	
	//***********************************  ����״̬ **********************************************************
	//------------------------------------------------------------------------------------
		switch ( Sys_Data.Mode_Flag )
		{
		//=======================START===============================================
		case 0://�Լ��봵�����
			if( !IO_GetDI( DI_GK1 ) && !Sys_Data.Stop_Button && !Sys_Data.X01_Flag ) {
				Sys_Data.X01_Flag = TRUE;
				IO_SetDO( DO_DuiJia );
				IO_SetDO( DO_ChuiQi );
				Sys_Data.Mode_Flag = 1;
			}
			break;
		//-------------------------------------------------------
		case 1://������ʱ�����������
			if( TimChg & BIT4 ) {
				Time_Data.ChuiQic_Time ++;
				if( Time_Data.ChuiQic_Time > USART1_GetBuf( ChuiQi_Time ) ) {
					Time_Data.ChuiQic_Time = 0;
					IO_ResetDO( DO_DuiJia );
					IO_ResetDO( DO_ChuiQi );
					IO_SetDO( DO_DangLiao );
					Sys_Data.Mode_Flag = 2;
				}
			}  
			break;
		//---------------------------------------------------------
		case 2://�رյ���
			if( IO_GetDI( DI_GK1 ) && !IO_GetDI( DI_GK3 ) ) {
				IO_ResetDO(DO_DangLiao);
				Sys_Data.X01_Flag = FALSE;
				Sys_Data.Mode_Flag = 3;
			}
			break;
		//---------------------------------------------------------
		case 3://ѹ�����
			if( !IO_GetDI( DI_GK2 ) && !Sys_Data.Stop_Button && !Sys_Data.YaLiao_Flag ) {
				Sys_Data.YaLiao_Flag = TRUE;
				IO_SetDO( DO_YaLiao );
				Sys_Data.Mode_Flag = 4;
			}
			break;
		//---------------------------------------------------------
		case 4://ѹ�ϼ���
			if( TimChg & BIT4 ) {
				Time_Data.YaLiaoc_Time ++;
				if( Time_Data.YaLiaoc_Time > USART1_GetBuf( YaLiao_Time ) ) {
					Time_Data.YaLiaoc_Time = 0;
					IO_ResetDO(DO_YaLiao);
					Sys_Data.Count_Cnt = TRUE;
					Sys_Data.YaLiao_Flag = FALSE;
					Sys_Data.Mode_Flag = 5;//�������޹���
				}
			} 
			break;
		//===============================END=========================================
		default:
			break;
		}
	//--------------------------------------------------
	//�����ӳ���	
		if( Sys_Data.Count_Cnt ) {
			Sys_Data.Count_Cnt = FALSE;
			tmp32 = USART1_GetBuf( TOTAL_COUNT2 ) + 65536 * USART1_GetBuf( TOTAL_COUNT );
			if( ( USART1_GetIO( USART_BuShu ) != 1 ) && IO_GetDI( DI_JiShuPause ) ) {
				tmp32++;
				USART1_SetBuf(TOTAL_COUNT2,tmp32%65536);	
				USART1_SetBuf(TOTAL_COUNT,tmp32/65536);		
			}	
	//////////////////////////////////////////////////////////////////////////////////////
			tmp = USART1_GetBuf( GK1_COUNT );
			if( USART1_GetIO( USART_BuShu ) != 1 && IO_GetDI( DI_JiShuPause ) )	
				USART1_SetBuf(GK1_COUNT,++tmp);	
			
			if( ( tmp > ( USART1_GetBuf( AMOUNT_BATCH ) - USART1_GetBuf( ALARM_CNT ) ) ) || Sys_Data.Count_Pause ) {
				Sys_Data.BuzzerJs_Flag = TRUE;					//��ʾ��
			}
	//////////////////////////////////////////////////////////////////////////////////////		
			tmp1=USART1_GetBuf(AMOUNT_BATCH); 
			if( USART1_GetBuf( GK1_COUNT ) >= USART1_GetBuf( AMOUNT_BATCH ) && USART1_GetBuf( AMOUNT_BATCH ) != 0 ) {
				Sys_Data.Tran_Flag = 1;
				USART1_SetBuf( GK1_COUNT , 0 );
				USART1_SetBuf( BATCH_COUNT , USART1_GetBuf( BATCH_COUNT ) + 1 );
			}
			if( !Sys_Data.Tran_Flag ) {
				Sys_Data.Mode_Flag = 0;
			}		
		}
	//-------------------------------------------------------------------------------------
	}
	else {		//ֹͣ״̬�²��Գ���
	//--------------------------------------------------
		if( USART1_GetIO( USART_DuiJia ) == 1 ) {
			IO_SetDO( DO_DuiJia );
			DuiJiaCS_flag = 1;
		}
		else if( DuiJiaCS_flag == 1 ) {
			DuiJiaCS_flag = 0;
			IO_ResetDO( DO_DuiJia );
		}
		//...................................
		if( USART1_GetIO( USART_ChuiQi ) == 1 ) {
			IO_SetDO( DO_ChuiQi );
			ChuiQiCS_flag = 1;
		}
		else if( ChuiQiCS_flag == 1 ) {
			ChuiQiCS_flag = 0;
			IO_ResetDO( DO_ChuiQi );
		}
		//.....................................
		if( USART1_GetIO( USART_DangLiao ) == 1 ) {
			IO_SetDO( DO_DangLiao );
			DangBanCS_flag = 1;
		}
		else if( DangBanCS_flag == 1 )
		{
			DangBanCS_flag = 0;
			IO_ResetDO( DO_DangLiao );
		}	 
		//......................................
		if( USART1_GetIO( USART_YaLiao ) == 1 ) {
			IO_SetDO( DO_YaLiao );
			YaLiaoCS_flag = 1;
		}
		else if( YaLiaoCS_flag == 1 ) {
			YaLiaoCS_flag = 0;
			IO_ResetDO( DO_YaLiao );
		}	 
		//.......................................
		if( USART1_GetIO( USART_ShuSong ) == 1 ) {
			IO_SetDO( DO_ShuSong );
			ShuSongCS_flag = 1;
		}
		else if( ShuSongCS_flag == 1 ) {
			ShuSongCS_flag = 0;
			IO_ResetDO( DO_ShuSong );
		}	
//------------------------------------------------
}

//-----------------------------------------------
//Y07����
  	if( Sys_Data.Tran_Flag == 1) {
     	if( TimChg & BIT4 ) {
			Time_Data.Tran_Time ++; 
			if( Time_Data.Tran_Time > USART1_GetBuf( ShuSong_Delay ) ) {
             	Time_Data.Tran_Time = 0;
				Sys_Data.Tran_Flag = 2;
				IO_SetDO( DO_ShuSong );
			}
		}
	} 
  	else if( Sys_Data.Tran_Flag == 2 ) {
     	if( TimChg & BIT4 ) {
			Time_Data.Tran_Time ++;
			if( Time_Data.Tran_Time > USART1_GetBuf( ShuSong_Time ) ) {
             	Time_Data.Tran_Time = 0;
				Sys_Data.Tran_Flag = 0;
				Sys_Data.Mode_Flag = 0;
				IO_ResetDO( DO_ShuSong );
			}
		}
	} 
//--------------------------------------------------------
//��λֹͣ	
	if( Sys_Data.HighStop_Flag ) {
		if( !Sys_Data.X01_Flag && !Sys_Data.YaLiao_Flag && !Sys_Data.Count_Cnt ) { //   ��λ
			USART1_SetIO(USART_START_IN,0);			//����𶯱�־		
			USART1_SetIO(USART_STOP_IN,0);			//���ֹͣ��־
			USART1_SetIO(USART_STOP_F,0);				//���ǿ��ֹͣ��־
			Sys_Data.Stop_Flag = FALSE;		
			Sys_Data.HighStop_Flag = FALSE; 
			Sys_Data.Start_Flag = 0;
			Sys_Data.Mode_Flag = 0; 
			USART1_SetBuf(WORK_INF,WORK_STOP);		
		}
	}
//----------------------------------------------------------------------------------------------------------	
//*********************************** ������ͣ **********************************************************
//----------------------------------------------------------------------------------------------------------
//------------------------------------------
//��ӼӰ���
	if( USART1_GetIO( USART_BuShu ) || !IO_GetDI( DI_JiShuPause ) ) {
		Sys_Data.Count_Pause = TRUE;
		USART1_SetBuf( Js_Pause , 1 );
	}
	else {
		Sys_Data.Count_Pause = FALSE;
		USART1_SetBuf( Js_Pause , 0 );
	} 

//------------------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&����������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&	
//------------------------------------------------------------------------------------

	if( Sys_Data.BuzzerJs_Flag == TRUE ) {
    	if( TimChg & BIT4 ) {
			Time_Data.Buzzer_Time ++;
			if(Time_Data.Buzzer_Time > 100) {
             	Time_Data.Buzzer_Time = 0;
				Sys_Data.BuzzerJs_Flag = FALSE;
			}
		}
	}
	//------------------------------------------------------------
	//�������ر�����
	if( !Sys_Data.BuzzerS_Flag && !Sys_Data.BuzzerJs_Flag ) {
		IO_ResetDO(DO_BEEP);
	}
	//-------------------------------------------------------------
	//��������������
	else if( Sys_Data.BuzzerS_Flag == TRUE || Sys_Data.BuzzerJs_Flag == TRUE ) {	
	  	IO_SetDO(DO_BEEP);
	}
	
	
	
	
	
//=======================================END=================================	
}

//***********************************��������������**********************************/
void HMI_Manage(u32 TimChg)	  // 
{

	if( USART1_GetIO( USART_TOTAL_CLR ) ) {
		USART1_SetIO( USART_TOTAL_CLR , 0 );	
		USART1_SetBuf(TOTAL_COUNT , 0 );	
		USART1_SetBuf(TOTAL_COUNT2 , 0 );			
	}	
	
	if( USART1_GetIO( USART_CNT_CLR ) ) {
		USART1_SetIO( USART_CNT_CLR , 0 );	
		USART1_SetBuf( GK1_COUNT , 0 );	
	}	
	
	if( USART1_GetIO( USART_BATCH_CLR ) ) {
		USART1_SetIO( USART_BATCH_CLR , 0 );	
		USART1_SetBuf( BATCH_COUNT , 0 );	
	}	
//----------------------------------------------------------------------------------------------------------	
//*********************************** ��λ���� **********************************************************
//----------------------------------------------------------------------------------------------------------
	
	
	if( USART1_GetIO( USART_STOP_F ) ) {       //ǿ��ֹͣ
		SysStop();
	}
	//------------------------------------
	

	
	//----------------------------------------------
//----------------------------------------------------------------------------------------------------------	
//*********************************** �������� **********************************************************
//----------------------------------------------------------------------------------------------------------
	if( USART1_GetIO( USART_START_IN ) && Sys_Data.Start_Flag == 0 && IO_GetDI( DI_STOP ) ) {	  // ������ʱ
		Sys_Data.Start_Button = TRUE;
		Sys_Data.BuzzerS_Flag = FALSE;
		if( !USART1_GetBuf( SYSTEM1_Time ) ) {
			USART1_SetBuf( WORK_INF , WORK_SYSTEM1 );  
		}
   		else if( JiaMi1_flag == 1 ) {
				  	   
		}					
		else {
		//-------------------
			Sys_Data.Start_Flag = 1;
			Sys_Data.Start_Button = FALSE;
		//-----------------
			USART1_SetBuf( WORK_INF , WORK_RUN );
		}	
	}	
    else if( Sys_Data.Start_Button )  {
      	Sys_Data.Start_Button = FALSE;
		Sys_Data.BuzzerS_Flag = FALSE;
	}	
	//--------------------------------------------------		
		
//----------------------------------------------------------------------------------------------------------
//***********************************  ֹͣ���� **********************************************************
//----------------------------------------------------------------------------------------------------------
  	if( USART1_GetIO( USART_STOP_IN ) == 1 && !Sys_Data.Stop_Flag ) {
		Sys_Data.Stop_Flag = TRUE;
	  	Sys_Data.Stop_Button = TRUE;
		PIPE_SaveFlash();
		USART1_SetIO( USART_STOP_IN , 0 );	
	}

//------------------------------------------------------------------------------------			
//***********************************  ֹͣ״̬�°�ֹͣ���� **********************************************************		
//------------------------------------------------------------------------------------
 	if( Sys_Data.Stop_Button && !Sys_Data.Start_Flag ) {   //�ѱ� ��  ��ֹͣ  
		Sys_Data.Stop_Button = FALSE;
		USART1_SetBuf(WORK_INF,WORK_STOP);
		USART1_SetIO(USART_STOP_IN,0);					//���ֹͣ��־
		Sys_Data.Stop_Flag = FALSE;
		Sys_Data.BuzzerS_Flag = FALSE;
		Sys_Data.BuzzerJs_Flag=0;
  	}		
//==================================END================================================
}
//**********************************LED���е��ӳ���****************************************
void Run_LED(u32 TimChg)	   
{
	
	
						if(TimChg&BIT10)
	        {
						if(Led_flag==0)
						{
								RunLed_on();
							  Led_flag=1;
						}		
            else
						{
								RunLed_off();
							  Led_flag=0;
						}							
						
					}	
	
	
		
}

//**********************************AD�ӳ���****************************************
void AD_Manage(u32 TimChg)
{
		u16 tmp1;
	
							if(TimChg&BIT2)
	        {						
					
					
					if(AD_flag==0)
					{
					    ADC_START(10) ;
              AD_flag=1;
		      }
					
					
					
					
					
					else	if(AD_flag==1)
					{
						
					    tmp1=Get_AdcData() ;
						  ADCTEMP1_js++;
              ADCTEMP1=ADCTEMP1+tmp1;
						  if(ADCTEMP1_js==20)
						  {
								tmp1=ADCTEMP1/20;
								
								USART1_SetBuf(USART_PARA_AD1,tmp1);
								ADCTEMP1_js=0;
								ADCTEMP1=0;
							}
						
							

              AD_flag=2;						
						
		      }				
					
					else	if(AD_flag==2)
					{
					    ADC_START(11) ;
              AD_flag=3;
		      }
									
					else	if(AD_flag==3)
					{

					    tmp1=Get_AdcData() ;

						  ADCTEMP2_js++;
              ADCTEMP2=ADCTEMP2+tmp1;
						  if(ADCTEMP2_js==20)
						  {
								tmp1=ADCTEMP2/20;
								
								USART1_SetBuf(USART_PARA_AD2,tmp1);
								ADCTEMP2_js=0;
								ADCTEMP2=0;
							}

	              AD_flag=0;					
		      }							
					
					
				}
	
	
}


//**********************************���������ӳ���****************************************
void ParaSave_Manage(u32 TimChg)
{
	
	//-------------------------------------

			
				if(USART1_GetIO(USART_PB_SavePara))
				{
					PIPE_SaveFlash();
					USART1_SetIO(USART_PB_SavePara,0);
					
					
					//tmp1=	USART1_GetIO(0);
				}
								
			

	//---------------------------------------				
	if(USART1_GetIO(USART_ShuJuBaoCun)==1)
	{
    
    BackSaveParameters();
		USART1_SetIO(USART_ShuJuBaoCun,0);
 							
	}
 
  //------------------------------------------------
	
	if(USART1_GetIO(USART_ShuJuHuiFu)==1)
	{
     BackLoadParameters();
	 	USART1_SetIO(USART_ShuJuHuiFu,0);		
		
	}	
 
	
}	

/////////////////////////////////////////////////////////////////////////////
void JiaMiManage(u32 TimChg)		
{  
 		if((TimChg&BIT12)&&Sys_Data.Start_Flag==0)	
	  SMEC_Test();
	
}

//**********************************������****************************************
void MainWork(u32 TimChg)
{

	//----------------------------------------
	 ParaSave_Manage(TimChg); //��������ָ�
	 Run_LED(TimChg);         //���е�
	 AD_Manage(TimChg);
	InAction(TimChg);	  //��ӿؼ������������ٶȼ���
 	JiaMiManage(TimChg);
  HMI_Manage(TimChg); 
	MainLogic(TimChg);	  //�������߼���ϵ

	
	
}
