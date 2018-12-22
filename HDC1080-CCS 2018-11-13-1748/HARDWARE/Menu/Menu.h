/******************************************************************************
 * Menu.H - �˵���غ꿪�� ����������
 *
 *
 * DESCRIPTION: -
 *
 * modification history
 * --------------------
 * 01a, 04/sep/2007, ���ײ� written
 * --------------------
 ******************************************************************************/
#ifndef __MENU_H
#define __MENU_H 

#include "stm32f10x.h"
#include "CPU.h"
#include "delay.h"
#include "KeyScan.h"
#include "ds18b20.h"
#include "DHT11.h"


#include "MenuTop.h"
#include "MenuFunc.h"
#include "MenuPara.h"
#include "MenuLanguage.h"
#include "MenuFSM.h"
#include "MenuMeasure.h"
#include "MenuPara.h"
#include "MenuMain.h"
#include "ST7565R.h"





/*
LessCPUUseage:
������ʾ��ǰ���������
1.��������Bar������ ��ʾ��ǰ��
2.ͨ��һ��'>'����ʾ��ǰλ��
��1�ַ����ڵ���CPU��LCD�ϱȽϷ�ʱ
������������õ�2�ַ���,�Ͼ�����һ��'>'�ȷ�������Ҫʡ�µĶ�
��û�н����������,�����Ȼ�����Ҫȫ��ˢ�µ����
���CPU��#define LessCPUUseage
���򲻶����ֵ
*/
//
//#define LessCPUUseage

//��̬��������˵�  ��Ҫ�ع���ʽ��֧��
//#define DynamicBar
//�Ƿ�ع���ʽ
#define RockBack

//���ּ���ݷ�ʽ
//��ҪԤ�������ּ��ļ�ֵKey_1---Key_9
//���ṩһ�������ܰѼ�ֵת����ʵ�ʶ�Ӧ���� Key = chang_code(Key);
//#define DigiKeyLink

//��������Ҫ��̬����˵�,����Ҫ�ع���ʽ,���������
#ifdef DynamicBar
    #ifndef RockBack
        #error  "DynamicBar need RockBack!"
        #error  "#define RockBack pls"
    #endif
#endif

//--------------
//��ʾλ�õĺ궨��
//��Bar�����ʾλ��
#define FatherXOffset    10     //Father��Xƫ��
#define FatherYOffset    2      //Father��Yƫ��
//Bar�����ʾXYƫ��
#define BarXOffset      1//Bar��Xƫ��
#define BarYOffset      1//Bar��Yƫ��
//Bar���XY�ߴ�
#define BarXSize      (7*12)    //Bar�ĳ���
#define BarYSize      2         //Bar�ļ��

//���Դ���
#define CN    0
#define EN    1

//����ʼ��Refresh
#define FlashMode_NoAction     0
//ϵͳϵͳ�����ʼ��
#define FlashMode_AutoInit     1
//�ֶ���ʼ��
#define FlashMode_ManualInit   2
//�ػ滭��
#define FlashMode_ReFlash      3



//Ҳ��������ʹ��Push�ĸ���
#define MaxMenuDeep 4          //�˵�������ֵ

#ifdef DynamicBar
#define FixedData       0
#define DynamicData     1
//�������ݵ���Դ�ǹ̶��Ļ��Ƕ�̬���ɵģ�ͨ���ǹ̶��ģ�
#endif

//u8 DispMax = 3;     //����������ʾ������� ͨ�����Ǹ��̶�ֵ--��Ϊ���Һ���Ĵ�С��������һ�ο�����ʾ�Ķ���,��Ҳ�����ڳ������޸�,���ǵ�ά����--��Ϊ���е�Bar�Ͳ˵�����Ҫ�õ�����
#define DispMax  3

//-----------------------------------------------------
//Bar�Ͳ˵������ݽṹ
struct Menu
{
//  u8 const **Text;     //ָ����ʾ���������ָ��
    u8 **Text;     //ָ����ʾ���������ָ��,ָ��ָ���ָ�롣 U8 * const TipCN[]
    u8 TextNum;         //�����
    void* (*Action)();  //��Ӧ��ִ�к���
};

//----------------------------------------------------
//��������������Menu.C������
extern u8 BackRefresh ;             //����˵����� ˢ�±�־
extern u8 Refresh ;               //��ת�����Ӳ˵� ˢ�±�־
extern u8 language;           //���Ա�־
extern u8 KeyFuncIndex ;        //����

extern u8 FatherIndexBackup[MaxMenuDeep+1]; //���˵���������
extern u8 Layer;               //�˵�����

extern u8 ItemBackup[MaxMenuDeep];      //��ǰ�˵����
extern u8 ItemBackup_i;          //

extern u8 WhereReverseBackup[MaxMenuDeep];     //����λ�ñ���
extern u8 WhereBackup_i;         //


extern u8 KeyPressCount;         //ͳ����������ʱ��,��ʱ�䰴���� �汾��ʾ

#ifdef DynamicBar
extern u8 BarDataMode;
#endif
extern u8 Item;            //��ǰBar��  ��Χ:[0,ItemNum-1]  ����0 ����ItemNum-1  ������ItemNum��ȡֵ
extern u8 ItemNum;         //Bar����
extern u8 Where;           //��ǰ����λ��,[0,DispMax-1]  ��ӳ���Ե�Bar����Ļ�ϵ�λ��

extern u8 DispMin;         //ItemNum��DispMax�е�С��

//��ǰBar��ʾ����ָ��
//extern u8 const **DispItem; //����ʾ����ָ��
extern u8 **DispItem; //����ʾ����ָ��

#ifdef DynamicBar
extern u8 ** DynamicBarDispItem; //��̬����ʾ����ָ��
#endif
//---------------------------------------------------
//���ص�ǰ�˵�
#define SelfMenuIndex FatherIndexBackup[Layer-1]

//----------------------------------------------------
//extern void Jump2Menu(u8 Index);//,u8 FlashMode);
void Jump2Menu(u8 Index,u8 FlashMode);

//ͼ���
extern const struct Menu IcoMenu[];
//���ܲ˵�
extern const struct Menu MenuFunc[];
//�����˵�
extern const struct Menu MenuPara[];
//�����˵�
extern const struct Menu MenuMeasure[];

//���Բ˵�
extern const struct Menu MenuLanguage[];

//Tip
extern const struct Menu Tip[];
//ͼ��
extern u8 const * const icos[];

//�˵���Դָ��
extern struct Menu * BarMenu;
//Tipָ��
extern struct Menu * TipBar;

//--------------------------------------------------------------------
#define Enter_PosX      50      //"����"��ʾ��λ��
#define Enter_PosY      7
#define ICO_PosX      48      //ͼ����ʾ��λ��
#define ICO_PosY      3
#define ICO_XSize    32      //ͼ��ĳߴ�
#define ICO_YSize    (-2)

#define MenuBarPosX     125
#define MenuBarNumPosX  121




//-----------------------
//���¶����KeyTab�еõ�
//����KeyTabʱ����������µĶ���
//����˵����ӳ���!
#define MenuTopIndex       0
#define MenuIndex          5
#define MenuFuncIndex     10
#define MenuParaIndex     15
#define MenuLanguageIndex 20
#define MenuMeasureIndex  25

#define MenuDataIndex     30



void BarMenuInit(void);
void BarMenuUp(void);
void BarMenuDown(void);
void PUSH(void);
void POP(void);



//void DispHomeScreen(void);
//u8 CheckKey(void);

#endif  

