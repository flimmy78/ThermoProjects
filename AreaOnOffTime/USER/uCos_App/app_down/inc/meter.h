/*******************************************Copyright (c)*******************************************
									ɽ������ռ似����˾(�����ֲ�)                                                          
**  ��   ��   ��: meter.h
**  ��   ��   ��: ������
**	��   ��   ��: 0.1
**  �� ��  �� ��: 2012��9��10�� 
**  ��        ��: �ȼ�����Э�����
**	�� ��  �� ¼:   	
*****************************************************************************************************/
#ifndef				_METER_H
#define				_METER_H

#include "StoreManage.h"

#define  MaxRec_num      			5
#define METER_ADDR_LEN				7				//�ȼ������ַ����
#define	DELU_FRAME_START			0x68

extern OS_EVENT *UpAskMeterSem;
extern OS_EVENT *METERChangeChannelSem;

extern uint8 gCurrent_Channel;

extern uint16 gu16ValveIDRecord[METER_NUM_MAX];


#pragma pack(1)

typedef struct {
    uint8 	Channel;  				//����MBUSͨ�ŵ� ͨ��
    uint32  Bps;     				//����ͨ�Ų�����
    uint16 	OutTime; 				//�ȴ���ʱʱ��  0��ʾ��ָ�������ײ��ȱʡ��ʱʱ��
    uint8 	RpTimes; 				//ʧ�����Դ�����0��ʾ������
	} DownCommType;

typedef struct{
	uint8   PreSmybolNum;			/*ǰ���ַ�����*/
	uint8   MeterType;				/*�Ǳ�����*/
	uint8 	MeterAddr[7];			/*�ȼ������ַ*/
	uint8 	ControlCode;			/*������*/
	uint8 	Length;					/*�����򳤶�*/
	uint16	DataIdentifier;			/*���ݱ�ʶ��*/
	uint8 	SER;					/*���к�*/
	/*begin:yangfei added 2013-09-18 for �����ȱ�����̫��*/
	#if 0
	uint8   DataBuf[METER_FRAME_LEN_MAX];
    #else
    uint8   DataBuf[METER_FRAME_LEN_MAX*2];
    #endif
	}DELU_Protocol;


typedef struct
{
	uint32 ValveOpenTime;				//����ʱ�䣬BCD�룬���2λΪС��λ����λСʱ��
	uint16 WaterInTemp;					//��ˮ�¶ȣ�BCD�룬2λС������λ�档
	uint16 WaterOutTemp;				//��ˮ�¶ȣ�BCD�룬2λС������λ�档
	uint16 RoomTemp;					//�������¶ȣ�BCD�룬2λС������λ�档
	uint8  RoomSetTemp;					//�����趨�¶ȡ�
	uint8  RoomCompensateTemp;			//���ڲ����¶ȡ�
	uint8  Bit_OnOffState		:1;		//λ��1,���ػ�״̬��1-������0-�ػ���
	uint8  Bit_PanelLockFlag	:1;		//λ��2���������״̬��0-δ������1-������
	uint8  Bit_ValveState		:1;		//λ��3������״̬��0-�ط���1-������
	uint8  Bit_LockOpenFlag		:1;		//λ��4������ǿ�ƿ���־��0-����״̬��1-ǿ�ƿ���
	uint8  Bit_LockCloseFlag	:1;		//λ��5������ǿ�ƹر�־��0-����״̬��1-ǿ�ƹء�
	uint8  Bit_WirelessState	:1;		//λ��6�����߹��ϱ�־��0-����������1-���߹��ϡ�
	uint8  Bit_RechargeFlag		:1;		//λ��7����ֵ��־��0-δ��ֵ��1-��ֵ��
	uint8  Bit_ArrearageFlag	:1;		//λ��8��Ƿ�ѱ�־��0-δǷ�ѣ�1-Ƿ�ѡ�
	
}Valve_Format;  //��ռ13�ֽڡ�

//ͨ��ʱ���������λ���·���ֵ̯��ʽ��
typedef struct  
{
	uint16	MeterID;//������š�
	uint32	ApportionValueThis;  //�����ر��η�ֵ̯,BCD�룬2λС������λkWh��
	uint8   ThisUnit;  //���η�̯������λ��
	uint32	ApportionValueSum;  //�����ط�̯��ֵ,BCD�룬2λС������λkWh����
	uint8   SumUint;	//�ܷ�̯������λ��
}HeatValue_Format;



/*begin:yangfei added 2013-03-18 for meter data format standardized*/
typedef struct{
	uint32   DailyHeat;		                /*����������*/	
    uint8     DailyHeatUnit;
	uint32   CurrentHeat;				   /*��ǰ����*/
    uint8     CurrentHeatUnit;
	uint32 	 HeatPower;			      /*�ȹ���*/
    uint8     HeatPowerUnit;
	uint32 	 Flow;			                 /*��������*/
    uint8 	 FlowUnit;
	uint32 	AccumulateFlow;			/*�ۻ�����*/
    uint8 	AccumulateFlowUnit;	
	uint8	WaterInTemp[3];		        /*��ˮ�¶�*/	
	uint8 	WaterOutTemp[3];				/*��ˮ�¶�*/
    uint8 	AccumulateWorkTime[3];	/*�ۼƹ���ʱ��*/
	uint8	RealTime[7];		                /*ʵʱʱ��*/	
	uint16 	ST;					                    /*״̬ST*/  
	}CJ188_Format;

// ����ʱ�������е�20
typedef struct{
   uint32	DailyHeat;					   /*����������*/  
   uint8	 DailyHeatUnit;
   uint32	CurrentHeat;				  /*��ǰ����*/
   uint8	 CurrentHeatUnit;
   uint32	HeatPower;				 /*�ȹ���*/
   uint8	 HeatPowerUnit;
   uint32	Flow;							/*��������*/
   uint8	FlowUnit;
   uint32  AccumulateFlow;		   /*�ۻ�����*/
   uint8   AccumulateFlowUnit; 
   uint8   WaterInTemp[3];			   /*��ˮ�¶�*/    
   uint8   WaterOutTemp[3]; 			   /*��ˮ�¶�*/
   uint8   AccumulateWorkTime[3];  /*�ۼƹ���ʱ��*/
   uint8   RealTime[7]; 					   /*ʵʱʱ��*/    
   uint16  ST;									   /*״̬ST*/  
   }ZHENYU2_Format;

//begin: added by zjjin.
typedef struct{
	uint32	MeterID;
	uint8	Constant08;
	uint32  CurrentCool;		     /*��ǰ����*/	
    uint8   CurrentCoolUnit;
	uint32  CurrentHeat;			/*��ǰ����*/
    uint8   CurrentHeatUnit;
	uint32 	 Flow;			         /*��������*/
    uint8 	 FlowUnit;
	uint32 	AccumulateFlow;			/*�ۻ�����*/
    uint8 	AccumulateFlowUnit;	
	uint8	WaterInTemp[3];		        /*��ˮ�¶�*/	
	uint8 	WaterOutTemp[3];			/*��ˮ�¶�*/
    uint8 	AccumulateWorkTime[3];	/*�ۼƹ���ʱ��*/
	uint8	RealTime[7];		                /*ʵʱʱ��*/	
	uint16 	ST;					                    /*״̬ST*/  
	}YITONGDA_Format;

//end: added by zjjin.

// ��������ӽṹ�壬���ڽ�����������Ľ�������������IE754��ʽת��ΪBCD��
typedef union
{
    u8   gp22_u8[4];
    float gp22_float;
}To_Float;

typedef struct{
    
	//float   DailyHeat;		/*���������������ȱ�Ľ�����������IEEE754Э��*/
	To_Float  DailyHeat;		/*���������������ȱ�Ľ�����������IEEE754Э��*/
	uint8     DailyHeatUnit;	 //��λ 
	uint32   CurrentHeat;				/*��ǰ����*/
	uint8     CurrentHeatUnit;   
	uint32 	 HeatPower;			/*�ȹ���*/
	uint8     HeatPowerUnit;
   	uint32 	 Flow;			/*����*/
	uint8 	 FlowUnit;   
	uint32 	AccumulateFlow;					/*�ۻ�����*/
	uint8 	AccumulateFlowUnit;	
	uint8	WaterInTemp[3];		/*��ˮ�¶�*/	
	uint8 	WaterOutTemp[3];					        /*��ˮ�¶�*/
    uint8 	AccumulateWorkTime[3];					/*�ۼƹ���ʱ��*/
	uint8	RealTime[7];		/*ʵʱʱ����ɵ�ʱ���� �� �� �� ʱ���룬��CJ188ǡ���෴*/	
	uint8 	ST;					        /*״̬ST*/  
	}JICHENG_Format;


typedef struct{
     
  	
	uint32   BiaoHao;        //���
	uint8     BiaoShi;		 //��ʶ

	uint32   CurrentHeat;				   /*��ǰ����*/
	uint8     CurrentHeatUnit; 
 	
	uint32   DailyHeat;		                /*���������� ����*/
	uint8     DailyHeatUnit;	
    

    //uint8     HeatPowerUnit;
	//uint32 	 HeatPower;			      /*�ȹ���*/

    
	uint32 	 Flow;			                 /*��������*/
	uint8 	 FlowUnit;

    	
	uint32 	AccumulateFlow;			/*�ۻ�����*/
	uint8 	AccumulateFlowUnit;

	uint8	WaterInTemp[3];		        /*��ˮ�¶�*/	
	uint8 	WaterOutTemp[3];				/*��ˮ�¶�*/
    uint8 	AccumulateWorkTime[3];	/*�ۼƹ���ʱ��*/
	uint8	RealTime[7];		                /*ʵʱʱ��*/	
	uint16 	ST;	
	}JingWeiFE_Format;


typedef struct{

 	uint8     DailyHeatUnit;
	uint32   DailyHeat;		                /*����������*/	
    
	uint8     CurrentHeatUnit;
	uint32   CurrentHeat;				   /*��ǰ����*/

    uint8     HeatPowerUnit;
	uint32 	 HeatPower;			      /*�ȹ���*/

    uint8 	 FlowUnit;
	uint32 	 Flow;			                 /*��������*/

    uint8 	AccumulateFlowUnit;	
	uint32 	AccumulateFlow;			/*�ۻ�����*/

	uint8	WaterInTemp[3];		        /*��ˮ�¶�*/	
	uint8 	WaterOutTemp[3];				/*��ˮ�¶�*/
    uint8 	AccumulateWorkTime[3];	/*�ۼƹ���ʱ��*/
	uint8	RealTime[7];		                /*ʵʱʱ��*/	
	uint16 	ST;	
	}JingWeiXiping_Format;






typedef struct{
    uint8     Nouse[9];
    uint8     Vertion;
    uint8     Medium;
    uint8     AccessCnt;
    uint8     Status;
    uint16     Signature;
    uint8     Fabrication_ID[6];
    uint8     Firmware_Version[5];
    uint8     FlowTemperatureUnit[2];
    uint16   FlowTemperature;
    uint8     ReturnTemperatureUnit[2];
    uint16   ReturnTemperature;
    uint8     DiffTemperatureUnit[2];
    uint16   DiffTemperature;

    uint8     Averaging_time[3];

    uint8     FlowRateUnit[2];
    uint32     FlowRate;

    uint8     MaxFlowRateUnit[2];
    uint32   MaxFlowRate;

    uint8     MaxLatestFlowRateUnit[2];
    uint32     MaxLatestFlowRate;

    uint8     MaxPrevFlowRate[7];

    uint8     PowerUnit[2];
    uint32   Power;

    uint8     MaxPower[6];
    uint8     MaxLatestPower[6];
    uint8     MaxPrevPower[7];

    uint8     VolumeUnit[2];
    uint32   Volume;

    uint8     VolumeLatest[6];
    uint8     VolumePrev[7];

    uint8     Futurekeydate1[5];
    uint8     Futurekeydate2[6];

    uint8     Operating_Time_err[6];
    
    uint8     Operating_Time_Unit[2];
    uint32     Operating_Time;

    uint8     DateTime[6];

    uint8     CurrentHeatUnit[2];
    uint32   CurrentHeat;				   /*��ǰ����*/

    uint8     Currentcooling[7];
    
	
	}ZENNER_Format;
typedef struct{
    uint8     Nouse[12];
    uint8     Status;
    uint16   Signature;
    uint8     Updating_time[3];
    uint8     Averaging_time[3];
  
    uint8     CurrentHeatUnit[2];                  /*06h/0Eh VIF: Heat quantity (kWh, MJ)*/
    uint32   CurrentHeat;				   /*��ǰ����*/

    uint8     VolumeUnit[2];                   /*  m3*1/100  */
    uint32   Volume;

    uint8     PowerUnit[2];                     /*  Heat power (kW/10)   */
    uint8   Power[3];

    uint8     FlowRateUnit[2];          /*Flowrate (l/h)*/
    uint8     FlowRate[3];

    uint8     FlowTemperatureUnit[2];   /*Flow temperature (��C)*/
    uint16   FlowTemperature;
	
    uint8     ReturnTemperatureUnit[2]; /*Return temperature (��C)*/
    uint16   ReturnTemperature;
	}LANDISGYR_Format;

typedef struct{
	uint32   DailyHeat;		/*����������*/	
    uint8     DailyHeatUnit;
	uint32   CurrentHeat;				/*��ǰ����*/
    uint8     CurrentHeatUnit;
	uint32 	 HeatPower;			/*�ȹ���*/
    uint8     HeatPowerUnit;
	uint32 	 Flow;			/*����*/
    uint8 	 FlowUnit;
	uint32 	AccumulateFlow;					/*�ۻ�����*/
    uint8 	AccumulateFlowUnit;	
	uint8	WaterInTemp[3];		/*��ˮ�¶�*/	
	uint8 	WaterOutTemp[3];					        /*��ˮ�¶�*/
    uint8 	AccumulateWorkTime[3];					/*�ۼƹ���ʱ��*/
	uint8	RealTime[7];		/*ʵʱʱ��*/	
	uint16 	ST;					        /*״̬ST*/  
	}Danfoss_Format;
typedef struct{
    uint8     DailyHeatUnit;
	uint32   DailyHeat;		/*����������*/	
    uint8     CurrentHeatUnit;
	uint32   CurrentHeat;				/*��ǰ����*/
    uint8     HeatPowerUnit;
	uint32 	 HeatPower;			/*�ȹ���*/
    uint8 	 FlowUnit;
	uint32 	 Flow;			/*����*/
    uint8 	AccumulateFlowUnit;	
	uint32 	AccumulateFlow;					/*�ۻ�����*/
    
	uint8	WaterInTemp[3];		/*��ˮ�¶�*/	
	uint8 	WaterOutTemp[3];					        /*��ˮ�¶�*/
    uint8 	AccumulateWorkTime[3];					/*�ۼƹ���ʱ��*/
	uint8	RealTime[7];		/*ʵʱʱ��*/	
	uint16 	ST;					        /*״̬ST*/  
	}LICHUANG_Format;
typedef struct{
    uint8     DailyHeatUnit;
	uint32   DailyHeat;		/*����������*/	
    uint8     CurrentHeatUnit;
	uint32   CurrentHeat;				/*��ǰ����*/
    uint8     HeatPowerUnit;
	uint32 	 HeatPower;			/*�ȹ���*/
    uint8 	 FlowUnit;
	uint32 	 Flow;			/*����*/
    uint8 	AccumulateFlowUnit;	
	uint32 	AccumulateFlow;					/*�ۻ�����*/
    
	uint8	WaterInTemp[3];		/*��ˮ�¶�*/	
	uint8 	WaterOutTemp[3];					        /*��ˮ�¶�*/
    uint8 	AccumulateWorkTime[3];					/*�ۼƹ���ʱ��*/
	uint8	RealTime[7];		/*ʵʱʱ��*/	
	uint16 	ST;					        /*״̬ST*/  
	}WANHUA_Format;
typedef struct{
	uint32   DailyHeat;		/*����*/	
    uint8     DailyHeatUnit;
	uint32   CurrentHeat;				/*����*/
    uint8     CurrentHeatUnit;
    uint8     CurrentHeatDecimal[2];/*����С��*/
    uint8     AccumulateFlowDecimal[3];/*�ۻ�����С��*/
	uint32 	 Flow;			/*����*/
    uint8 	 FlowUnit;
	uint32 	AccumulateFlow;					/*�ۻ�����*/
    uint8 	AccumulateFlowUnit;	
	uint8	WaterInTemp[3];		/*��ˮ�¶�*/	
	uint8 	WaterOutTemp[3];					        /*��ˮ�¶�*/
    uint8 	AccumulateWorkTime[3];					/*�ۼƹ���ʱ��*/
	uint8	RealTime[7];		        /*ʵʱʱ��*/	
	uint16 	ST;					        /*״̬ST*/  
	}LEYE485_Format;

typedef struct{
    uint8 Nouse[15];
    uint16   CurrentEnergyUnit;
	uint32   CurrentEnerg;		/*�ۻ�����*/	
    uint8     CurrenTariff1[7];
	uint8     CurrentTariff2[7];			/*��ǰ����*/
    uint16   CurrentVolumeUnit;
	uint32 	 CurrentVolume;			/*�ۻ�����*/
    uint16 	 CurrentPowerUnit;
	uint32 	 CurrentPower;			/*�ȹ���*/
    uint16 	 CurrentFlowRateUnit;	
	uint8 	 CurrentFlowRate[3];					/*����*/

    uint16  ForwardTemperatureUnit;
	uint8	ForwardTemperature[2];		/*��ˮ�¶�*/	
	uint16  ReturnTemperatureUnit;
	uint8	ReturnTemperature[2];		/*��ˮ�¶�*/	
  
	uint8	RealTime[9];		/*ʵʱʱ��*/	
	}HYDROMETER_Format;



#pragma pack()
extern uint8 Get_Current_Channel(void);
extern void Reset_Current_Channel(void);

extern uint8 DelayTime_485;           //  485ͨѶ��ȡ���б�Ƶ���ʱʱ��     ʮ����
extern void METER_CreateFrame(DELU_Protocol *pData, uint8 *pSendFrame, uint8 *plenFrame);
extern uint8 METER_ReceiveFrame(uint8 dev, uint8 *buf, uint16 Out_Time, uint8 *datalen);
extern uint8 METER_DELU_AnalDataFrame(DELU_Protocol *pProtoclData, uint8 *pRecFrame);
extern uint8 METER_MeterCommunicate(DELU_Protocol *pData, uint8 *pResBuf, uint8 *pDataLenBack);
extern uint8 METER_MeterCommunicate_Direct(uint8 *pData, uint8 InLen, uint8 *pResBuf, uint8 *pOutLen);
extern uint8 Communicate_ForAll(uint8 *pData);
extern uint8 METER_ReadMeterDataTiming(uint16 MeterSn, uint8 *EleBuf);
extern uint8 VALVE_ReadMeterDataTiming(uint16 MeterSn, uint8 *EleBuf);
extern uint8 METER_ReadMeterDataCur(DELU_Protocol *pReadMeter, uint16 MeterSn);
extern void DisableAllMBusChannel(void);
extern uint8 METER_ChangeChannel(uint8 Channel);
extern uint8 METER_DataItem(DELU_Protocol *pProtocoalInfo);
extern void YINLINVALVE_CreateFrame(DELU_Protocol *pData, uint8 *pSendFrame, uint8 *plenFrame);
extern uint8 METER_MeterDataForValve(DELU_Protocol *pProtocoalInfo, uint8 ProtocolVer);
extern CJ188_Format METER_Data_To_CJ188Format(uint8 ProtocolVer,uint8* DataBuf,uint8 len,uint8* err);
extern uint8 To_Little_endian(uint8* Databuff,uint8 size);
extern uint8 Yilin_Calc_Parity(uint8 *pStart, uint8 ucLen);
extern uint8 ReadData_Communicate(uint8 *DataFrame, uint8 *DataLen);
extern uint8 Yilin_Valve_ReceiveFrame(uint8 *buf, uint8 *datalen);

#endif

