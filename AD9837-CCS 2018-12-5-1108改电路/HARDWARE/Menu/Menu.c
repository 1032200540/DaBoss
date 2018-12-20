#include "Menu.h"
#include "Picture.c" 
/*
----------------------------------------------------------------------------
�˵���ر���
----------------------------------------------------------------------------
*/

U8 Refresh = 0;               //��ת�����Ӳ˵� ˢ�±�־  >1ˢ��
U8 language = CN;           //���Ա�־
U8 KeyFuncIndex = 0;        //����
//3����������
U8 FatherIndexBackup[MaxMenuDeep+1]; //���˵�������������
U8 Layer = 0;               //�˵�����

U8 ItemBackup[MaxMenuDeep];      //�Ӳ˵����Ա�ű���
U8 ItemBackup_i = 0;          //

U8 WhereReverseBackup[MaxMenuDeep];     //�Ӳ˵�����λ�ñ���
U8 WhereBackup_i = 0;         //


U8 KeyPressCount = 0;               //���ڰ汾��ʾ

#ifdef DynamicBar
U8 BarDataMode = FixedData;
#endif


U8 Item;            //��ǰBar�� ���Ӳ˵���ţ� ��Χ:[0,ItemNum-1]  ����0 ����ItemNum-1  ������ItemNum��ȡֵ
U8 ItemNum;         //Bar�������Ӳ˵�������
U8 Where;           //��ǰ�Ӳ˵�����λ��,[0,DispMax-1]  ��ӳ���Ե�Bar����Ļ�ϵ�λ��
//U8 DispMax = 3;     //����������ʾ������� ͨ�����Ǹ��̶�ֵ--��Ϊ���Һ���Ĵ�С��������һ�ο�����ʾ�Ķ���,��Ҳ�����ڳ������޸�,���ǵ�ά����--��Ϊ���е�Bar�Ͳ˵�����Ҫ�õ�����
#define DispMax  3

U8 DispMin;         //ItemNum��DispMax�е�С��
//��ǰBar��ʾ����ָ��
//U8 const **DispItem; //����ʾ����ָ��
U8 **DispItem; //����ʾ����ָ��

#ifdef DynamicBar
U8 ** DynamicBarDispItem; //��̬����ʾ����ָ��
#endif

//�˵���Դָ��
struct Menu * BarMenu;
//Tipָ��
struct Menu * TipBar;


/*
----------------------------------------------------------------------------
      |---->ָ������ŵ�ַ,Ҳ����{"Function"},{"Parameter"},{"Measure"},�ȵ���Щ�ı����������
      |         |---->ָ���ŵ�λ��,����Щ�ַ����׵�ַӦ�����������  ��Ϊ���Ǹ�ָ�������ŵ����ݾ���ÿ���ַ����Ŀ�ʼ��ַ
      |         |
U8 const * const TopItemEN[]=
{
{"Function"},
{"Parameter"},
{"Measure"},
{"Language"},
{"Test"},
};
���Ǿ�����Щ����ڴ�����,�Լ��ٶ�RAM��ռ��

----------------------------------------------------------------------------
*/


//---------------------------------------------------
//�����˵�����Դ
//������ʽ��:
//---------------------------------------------------
//����˵�


//U8 const * const TopItemCN[]=
U8 * const TopItemCN[]= //ָ�����飬ÿ��Ԫ�ض��� U8 *���͵�ָ��
{
	{"����"},
	{"����"},
	{"����"},
	{"����"},
	{"����"},
};


//U8 const * const TopItemEN[]=
U8 * const TopItemEN[]=    //ָ�����飬ÿ��Ԫ�ض��� U8 *���͵�ָ��
{
	{"Function"},
	{"Parameter"},
	{"Measure"},
	{"Language"},
	{"Test"},
};


//"����"�˵�������ݺͳ���

//U8 const * const FuncItemCN[]=
U8 * const FuncItemCN[]=
{
	{"��������"},
	{"�������"},
	{"��������"},
	{"�޸�����"},
};

//U8 const * const FuncItemEN[]=
U8 * const FuncItemEN[]=
{
	{"Read Data"},
	{"BackLight"},
	{"Factory Set"},
	{"Change CODE"}
};
//"����"�˵�������ݺͳ���

//U8 const * const ParaItemCN[]=
U8 * const ParaItemCN[]=
{
	{"��ֵ"},
	{"��ʱ��T"},
	{"������K"},
	{"����ʱ��"}
};

//U8 const * const ParaItemEN[]=
U8 * const ParaItemEN[]=
{
	{"Menu0"},
	{"Menu1"},
	{"Menu2"},
	{"Menu3"},
	{"Menu4"},
	{"Menu5"},
	{"Menu6"},
	{"Menu7"},
};
//"����"�˵�������ݺͳ���

//U8 const * const LanguageItemCN[]=
U8 * const LanguageItemCN[]=
{
	{"����"},
	{"English"},
};

//U8 const * const LanguageItemEN[]=
U8 * const LanguageItemEN[]=
{
	{"����"},
	{"English"},
};


//����

//U8 const * const MeasureItemCN[]=
U8 * const MeasureItemCN[]=
{
	{"�����������"},
	{"��ճ����¼"},
	{"��������"},
	{"����ڲ���"},
	{"ģ���������"},
	{"���źŲ���"},
	{"�̵�������"},
};

//U8 const * const MeasureItemEN[]=
U8 * const MeasureItemEN[]=
{
	{"PushUp Res"},
	{"ClearErrCount"},
	{"OnlineCMD "},
	{"SysInputTest"},
	{"SVC TEST"},
	{"AXis TEST"},
	{"Relay TEST"},
};
//��ʾ�����ı�

//U8 const * const TipCN[]=
U8 * const TipCN[]=
{
	{"Menu"},
	{"ѡ��"},
	{"ȷ��"},
	{"ȡ��"},
	{"?ȷ��?"},
};



//U8 const * const TipEN[]=
U8 * const TipEN[]=
{
	{"Menu"},
	{"Select"},
	{"Ok"},
	{"Cancel"},
	{"? OK ?"},
};

//----------------------------------------
//�궨��:

#define MenuWhat(n) {(U8 **)n, (sizeof(n)/sizeof(U8 *)),0}
//ͼ���
const struct Menu IcoMenu[] =
{
	MenuWhat(TopItemCN),
	MenuWhat(TopItemEN),
};

//���ܲ˵�
const struct Menu MenuFunc[] =
{
	MenuWhat(FuncItemCN),
	MenuWhat(FuncItemEN),
};
//�����˵�
const struct Menu MenuPara[] =
{
	MenuWhat(ParaItemCN),
	MenuWhat(ParaItemEN),
};
//�����˵�
const struct Menu MenuMeasure[] =
{
	MenuWhat(MeasureItemCN),
	MenuWhat(MeasureItemEN),
};

//���Բ˵�
const struct Menu MenuLanguage[] =
{
	MenuWhat(LanguageItemCN),
	MenuWhat(LanguageItemEN),
};

//Tip
const struct Menu Tip[] =   //�ṹ������
{
	MenuWhat(TipCN),
	MenuWhat(TipEN),
};


//��������ʱѯ�ʵ�ͼ��������
#define WarningICO  5
#define PassICO     0

//ͼ������
u8 const * const icos[]=
{
	FunctionIco,   //����
	ParaIco,       //����
	TimeIco,       //ʱ��
	ActionIco,     //����
	MenuIco,       //����
	QuestionIco,   //ѯ��
	WarningIco,
	SoundIco,
};


//��ת��ָ���˵�
/*
void Jump2Menu(U8 Index)
{
    KeyFuncIndex = Index;             //jump to Menu index
}
*/
void Jump2Menu(U8 Index,U8 FlashMode)
{
    KeyFuncIndex = Index;             //jump to Menu index
    if(FlashMode)
	{
        Refresh = FlashMode;
    }
}

