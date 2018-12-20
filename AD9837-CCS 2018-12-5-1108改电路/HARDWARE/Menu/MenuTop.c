/******************************************************************************
 * MenuTop.C - ����˵� ����˵����ĺ��� ͼ��㺯����
 *
 *
 * DESCRIPTION: -
 *
 * modification history
 * --------------------
 * 01a, 04/sep/2007, ���ײ� written
 * --------------------
 ******************************************************************************/

#include "MenuTop.h"

//void Bar(U8 Item_,U8 ItemNum_);


/*
*****************************************************************************
* InitMenuVal - ��ʼ���˵�ϵͳ
* DESCRIPTION: -
* �ú��������ڽ���˵�ǰ������   ��ʼ��ȫ�ֱ���
* @Para void:
* Return :
*
*****************************************************************************
*/
void InitMenuVal(void)
{
    WhereBackup_i = 0;
    ItemBackup_i = 0;
    Layer = 0;
    FatherIndexBackup[Layer++] = MenuTopIndex;  //push index  ����������Ϊ���
}
/*
*****************************************************************************
* DispHomeScreen - ���������5������
* DESCRIPTION: -
* DispHomeScreen   DispHomeScreenEnter  DispHomeScreenBack  DispHomeScreenUp DispHomeScreenDown
*
*
*
*****************************************************************************
*/
void DispHomeScreen(void)//��������
{
    GUI_Clear();
	GUI_DispStringAtBar("��ʪ�ȼ��",4,1,124,GUI_TA_HCENTER);
   // GUI_DispStringAtBar("Desktop",1,1,126,GUI_TA_HCENTER);
    //��ʾ������Ӧ��������ʾ,0-->"�˵�"
  //  GUI_DispStringAtBar(*(Tip[language].Text),0,Enter_PosY,126,GUI_TA_HCENTER);
}
//����������Enter���Ĵ���
void DispHomeScreenEnter(void)
{
//-------------------
    KeyPressCount = 0;
//-------------------
    GUI_Clear();
//-------------------
//�����Ƕ���˵�,����ڽ����Ӳ˵�ǰ��Ҫ��ʼ������
    InitMenuVal();
//--------------------------
//״̬��ת,�����Ӳ˵�
    //jump to Menu index
    Jump2Menu(MenuIndex,FlashMode_AutoInit);
    return;
}
//����������Back���Ĵ���
void DispHomeScreenBack(void)
{

    if((KeyPressCount++)==0x0F)
	{
        GUI_Clear();
        DispBuildTime();
        delay_ms(1000);
        KeyPressCount = 0;
        // we need BackRefresh screen
        Jump2Menu(MenuTopIndex,FlashMode_ReFlash);
        return;

    }
    //return to MenuTop index
    Jump2Menu(MenuTopIndex,FlashMode_NoAction);
    return;
}
//����������Up���Ĵ���
void DispHomeScreenUp(void)
{
    KeyPressCount = 0;
/*
*   �����������������Ĺ��ܶ���,��Ϊ�����ڴ���������
*   ����,��ĳ���Ӳ˵��Ŀ������--���¸ð�����ֱ����ת��ĳ���Ӳ˵�
*/
//-------------------
//�����Ƕ���˵�,����ڽ����Ӳ˵�ǰ��Ҫ��ʼ������
//    InitMenuVal();
//--------------------------
//״̬��ת,�����Ӳ˵�
    Jump2Menu(MenuTopIndex,FlashMode_NoAction);
    return;
}
//����������Down���Ĵ���
void DispHomeScreenDown(void)
{
    KeyPressCount = 0;
//----------------------
//    ClearLCD();
//    DispRate(0);  //���ܺ�����"��ݷ�ʽ"  ��������ʾ
//���ܺ���ִ����Ϻ����»ص���������
//    Jump2Menu(MenuTopIndex);
    Jump2Menu(MenuTopIndex,FlashMode_NoAction);
    return;
}
/*
********************************************************
********************************************************
*/
//-----------------------
//�˵����ݺ���
//���ݵ�ǰ�˵��ĸ�������
void PUSH(void)
{
    WhereReverseBackup[WhereBackup_i++] = Where;      //����Where--->������ʾ��λ��
    ItemBackup[ItemBackup_i++] = Item;         //����Item--->��ǰ���λ��
    FatherIndexBackup[Layer++] = KeyFuncIndex;      //����KeyFuncIndex--->״̬����״̬
//-------------------------------

//-------------------------------

}
//�˵���ԭ����
void POP(void)
{
    Layer--;      //�ȵ���һ��,��Ϊʹ�õ���++,��˵�ǰLayerָ����һ������λ��
    KeyFuncIndex = FatherIndexBackup[Layer-1];     //�ָ�KeyFuncIndex
    Where = WhereReverseBackup[--WhereBackup_i];    //�ָ�������ʾλ��Where
    Item = ItemBackup[--ItemBackup_i];       //�ָ���λ��Item
//-------------------------------

//-------------------------------
    Refresh = FlashMode_ReFlash;                     //�����,����ˢ��
}

/*
*****************************************************************************
* BarDisp - Bar�Ͳ˵���ʾ
* DESCRIPTION: -
*
* @Para s:BAR��ʾ����������
* @Para X:X������
* @Para Y:Y������
* @Para HighLight:1--->������ʾ��ǰ��  0--->��ͨ��ʾ��ǰ��
//HightLight = 1--->HightLight Disp
//HightLight = 0--->Normal Disp
* Return :
*
*****************************************************************************
*/
//void BarDisp(U8 const*s,U8 X,U8 Y,U8 HighLight)
void BarDisp(U8 *s,U8 X,U8 Y,U8 HighLight)
{

#ifdef LessCPUUseage
    if (HighLight == 1) { //������ʾ
        GUI_DispStringAtBar(s,X+8,Y,120,GUI_TA_LEFT);
        GUI_SetEnFont(En_8x16);
        GUI_DispCharAt('>',X,Y);
    } else {  //ͨ����ʾ
        //��ʾBar��Text
        GUI_DispStringAtBar(s,X+8,Y,120,GUI_TA_LEFT);
        GUI_SetEnFont(En_8x16);
        GUI_DispCharAt(' ',X,Y);
    }
#else
    if (HighLight == 1) { //������ʾ
//------------------------------------
        GUI_SetTextMode(GUI_TEXTMODE_REVERSE);//����������ɫ��ͻ����ʾ
        GUI_DispStringAtBar(s,X,Y,120,GUI_TA_LEFT);
        GUI_SetTextMode(GUI_TEXTMODE_NORMAL);        //�ָ�ԭ��������ɫ�ͱ�����ɫ
//------------------------------------
    } else {  //ͨ����ʾ
        //��ʾBar��Text
        GUI_DispStringAtBar(s,X,Y,120,GUI_TA_LEFT);
    }
#endif
}
/*
FIXME!!!
����޸�BarMenuInit����δ���Item Where�ĳ�ʼ�����ﵽ���һ��Ŀ�ģ�
��ǰϵͳ�����趨��Ӣ���Ӣ��������ڵ�2��λ�ã����������������˵���������ѡ��ʱ������λ�þ���Ӣ�����
1���޸�BarMenuInit���룬�����һ�ν���ʱ�Ĵ���ʽ��Ҳ��Ϳ��Խ���ʹ�ô��Ӳ˵��˳�ʱ�Ĵ�����
*/
//Bar�Ͳ˵���ʼ��  ��������
void BarMenuInit(void)
{
U8 Menu_i;          //�������� �ڲ˵��������õ�
U8 Menu_j;          //��������
//-------------------
//�Ƚ�"��ʾ��������ʾ�������Ŀ(DispMax)"��"��Ҫ��ʾ����Ŀ(ItemNum)"
//�ҳ�С��,��С��Ϊ��ʾ����
//������ʾ��������ʾ3��,��Ҫ��ʾ������2��,��ô��ʾ2��,��3��,��ʾ3��,��4��Ļ�,��ʾ3��
    if (ItemNum > DispMax) 
	{
        DispMin = DispMax;
    } 
	else 
	{
        DispMin = ItemNum;
    }
//--------------------
//    if (Refresh) {//�Ӹ��˵����� ��ʼ��
        if(Refresh == FlashMode_AutoInit)
		{//������� ������
            PUSH();//���޸�Item Where֮ǰ������Щ�������ݣ���
            Item = 0;
            Where = 0;
        } 
		else if (Refresh == FlashMode_ManualInit)
		{    //�ǳ������  ��֮ǰ�Ѿ������ˣ��������߽���
            if(Where > DispMin-1)
			{//����Ƿ����
                //Where = DispMin-1;//A.��ײ�����ʾλ��
                Where = 0;          //B.�������ʾλ��
            }
            if(Item > ItemNum-1)
			{//����Ƿ����
                //Item = ItemNum-1;//A.����һ����
                Item = 0;          //B.�ʼ��һ����
            }
        }
//    }
//-------------------
//��ȻItem Where����δ���ģ���ô����ʹ�ô��Ӳ˵��˳��ķ������ҵ�Ӧ����Where=0λ����ʾ��Item��
//----------------
//����2
    if (Item >= Where) {//δ��Խ���
        Menu_j = Item -Where;
    } else {            //��Խ���
        Menu_j = ItemNum  - (Where - Item);
    }
    //��ʱMenu_J��ֵ���Ƕ���(Where=0)��ʾ��Itemֵ
//----------------
    //��ʾȫ�����Ӳ˵���
    for (Menu_i = 0; Menu_i < DispMin; Menu_i++) {
        if (Menu_j == Item){ //���Ե�Item��,λ����Where
            BarDisp(*(DispItem+Item),BarXOffset,Where*BarYSize+BarYOffset,1);
        } else {             //������ ������ʾ
            BarDisp(*(DispItem+Menu_j),BarXOffset,Menu_i*BarYSize+BarYOffset,0);
        }
        if (Menu_j == (ItemNum-1)) {//�������һ��ػ����ʼ��һ��
            Menu_j = 0;
        } else {                    //��һ��
            Menu_j++;
        }
    }
    Bar(Item,ItemNum,MenuBarPosX,MenuBarNumPosX);                  //ά��������
}


//Bar��˵����ϰ�������Ϊ
/*
���ܵļ������:
A.ԭ��Bar�Ķ���,����������,��ô����Ҫˢ��ȫ������ʾ
A1.������Ҫ��ʾ��Bar���ڵ���������ʾ��Bar,��ô������ʾȫ��
A2.������Ҫ��ʾ��Bar�����ڵ���������ʾ��Bar,ȡ������������ʾ,������ʾ���һ��Bar
B.ԭ��Bar�����ڶ���,��������,��ôȡ��ԭ��Bar�ĸ���,������ʾ��һ��Bar��
��Ȼ����Ҫά��:������ʾ��λ��where/������ʾBar���Item
*/

//ά��Bar��ʾ
void BarMenuUp(void)
{
    U8 Menu_i;          //�������� �ڲ˵��������õ�
    U8 Menu_j;          //��������
    U8 ItemBack;
    ItemBack = Item;//����ԭ�е�Item,ȡ��ԭ�з���ʱ��Ҫʹ��
    //ά��Item,�õ���Ҫ���Ե�Item
    if (Item == 0) {
        Item = ItemNum-1;
    } else {
        Item--;
    }
    //ά����ʾ
    if (Where) {//��ǰλ�ò�Ϊ0,����˵�����ڶ���,���η���

#ifdef LessCPUUseage
        GUI_SetEnFont(En_8x16);
        GUI_DispCharAt(' ',BarXOffset,(Where--)*BarYSize+BarYOffset);
        GUI_DispCharAt('>',BarXOffset,Where*BarYSize+BarYOffset);
#else
        //ԭ��λ��ȡ������   ����ItemBack  λ��Where
        BarDisp(*(DispItem+ItemBack),BarXOffset,(Where--)*BarYSize+BarYOffset,0);
        //���ƺ��λ�÷���   ����Item      λ��Where-1 (Where--ʵ��)
        BarDisp(*(DispItem+Item),BarXOffset,Where*BarYSize+BarYOffset,1);//������ʾ
#endif

#ifdef RockBack
    } else {//��ǰλ��Ϊ0,     ����  ����  ��Ҫˢ��ȫ���Ӳ˵�����ʾ   //1.�ع���ʽ,���˶�����ع����ײ�
    #ifdef DynamicBar
        if ((ItemNum > DispMax)||(BarDataMode == DynamicData)){//��Ҫ��ʾ��Bar���ڵ���������ʾ��Bar,��ô������ʾ//08/29
    #else
        if (ItemNum > DispMax) {//��Ҫ��ʾ��Bar���ڵ���������ʾ��Bar,��ô������ʾ
    #endif
#else
    } else if(ItemBack != 0){
        if (ItemNum > DispMax) {//��Ҫ��ʾ��Bar���ڵ���������ʾ��Bar,��ô������ʾȫ��
#endif

            Menu_j = Item;
            Menu_i = 0;
            //���� Item λ�� 0
            BarDisp(*(DispItem+Menu_j),BarXOffset,Menu_i*BarYSize+BarYOffset,1);
            if (Menu_j == (ItemNum-1)) {   //ά��Menu_j
                Menu_j=0;
            } else {
                Menu_j++;
            }
            //��ʾ������
            for (Menu_i = 1; Menu_i < DispMax; Menu_i++) {
                BarDisp(*(DispItem+Menu_j),BarXOffset,Menu_i*BarYSize+BarYOffset,0);
                if (Menu_j == (ItemNum-1)) {
                    Menu_j=0;
                } else {
                    Menu_j++;
                }
            }
            Where = 0;//��ǰλ����Ȼ�ڿ�ͷ��0λ��
        } else {//��������ʾ��ȫ���˵���,"���� ����"Ӧ����ת���ײ�(����ʲô������)
            //������ֻ��һ���ʱ��Ӧ��һֱ��Where=0�ĵط����Եģ���������Ҳ��ʵ�֣���Ϊ����Ƿ��Եĺ���
            Where = ItemNum-1;
            //ȡ��������ԭ�еķ���  ��ItemBack  λ��0
            BarDisp(*(DispItem+ItemBack),BarXOffset,0*BarYSize+BarYOffset,0);
            //���Ը���  ��Item  λ��ItemNum-1
            BarDisp(*(DispItem+Item),BarXOffset,Where*BarYSize+BarYOffset,1);//����
        }
#ifdef RockBack
    }
#else
    }else{
        Item = ItemBack;//Restore
    }

#endif

    Bar(Item,ItemNum,125,120);                  //ά��������
    Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
}
//Bar��˵����°�������Ϊ
//ά��Bar��ʾ
void BarMenuDown(void)
{
    U8 Menu_i;          //�������� �ڲ˵��������õ�
    U8 Menu_j;          //��������
    U8 ItemBack;
    ItemBack = Item;
//---ά��Item
    if (Item == (ItemNum-1)) {
        Item = 0;
    } else {
        Item++;
    }
//------------
//---ά����ʾ
    if (Where != (DispMin-1)) {//��ǰλ�ò�Ϊ��ĩ,���η���


#ifdef LessCPUUseage
        /*
        �����ʹ��">"�����ķ��ű�־��ǰ�������ôֱ�ӷ��Ըñ�־���� 2007��1��8
        */
        GUI_SetEnFont(En_8x16);
        GUI_DispCharAt(' ',BarXOffset,(Where++)*BarYSize+BarYOffset);
        GUI_DispCharAt('>',BarXOffset,Where*BarYSize+BarYOffset);
#else
        //ԭ��λ��ȡ������   ����ItemBack  λ��Where
        BarDisp(*(DispItem+ItemBack),BarXOffset,(Where++)*BarYSize+BarYOffset,0);
        //���ƺ��λ�÷���   ����Item      λ��Where+1(Where++ʵ��)
        BarDisp(*(DispItem+Item),BarXOffset,Where*BarYSize+BarYOffset,1);//����
#endif

#ifdef RockBack
    } else {    //��ǰλ��ΪDispMax    �ײ�  ����
    #ifdef DynamicBar
        if ((ItemNum > DispMax)||(BarDataMode == DynamicData)){//��Ҫ��ʾ��Bar���ڵ���������ʾ��Bar,��ô������ʾ//08/29
    #else
        if (ItemNum > DispMax) {//��Ҫ��ʾ��Bar���ڵ���������ʾ��Bar,��ô������ʾ
    #endif
#else
    }else if(ItemBack != (ItemNum-1)){//��ǰλ��ΪDispMax    ���ԭ����ʾλ�ò������һ��� �ײ�  ����
        if (ItemNum > DispMax) {//��Ҫ��ʾ��Bar���ڵ���������ʾ��Bar,��ô������ʾ
#endif
            Menu_j = Item;
            Menu_i = DispMax;
            //���� Item  λ���� DispMax
            BarDisp(*(DispItem+Menu_j),BarXOffset,(Menu_i-1)*BarYSize+BarYOffset,1);
            if (Menu_j == 0) {
                Menu_j = ItemNum-1;
            } else {
                Menu_j--;
            }
            //��ʾ������
            for (Menu_i = DispMax-1; Menu_i > 0; Menu_i--) {
                BarDisp(*(DispItem+Menu_j),BarXOffset,(Menu_i-1)*BarYSize+BarYOffset,0);
                if (Menu_j == 0) {
                    Menu_j = ItemNum-1;
                } else {
                    Menu_j--;
                }
            }
            Where = DispMax-1;//��ǰλ����Ȼĩβλ��
        } else {//��������ʾ��ȫ���˵���,"�ײ� ����"Ӧ����ת����������(����ʲô������)
            Where = 0;
            //ȡ���ײ�ԭ�з���   ��ItemBack  λ��ItemNum-1
            BarDisp(*(DispItem+ItemBack),BarXOffset,(ItemNum-1)*BarYSize+BarYOffset,0);
            //���Զ��� ��Item  λ��0
            BarDisp(*(DispItem+Item),BarXOffset,Where*BarYSize+BarYOffset,1);//����
        }
#ifdef RockBack
    }
#else
    }else{
        Item = ItemBack;//Restore
    }
#endif

    Bar(Item,ItemNum,MenuBarPosX,MenuBarNumPosX);                  //ά��������
    Jump2Menu(SelfMenuIndex,FlashMode_NoAction);

}
//*********************************************************


/*
*****************************************************************************
* DispIcoMenuInit - ͼ���˵�����
* DESCRIPTION: -
* ����5������
 DispIcoMenuInit    DispIcoMenuEnter   DispIcoMenuBack
 DispIcoMenuUp    DispIcoMenuDown
* @Return :
*
*****************************************************************************
*/
void DispIcoMenuInit()
{

    ItemNum = IcoMenu[language].TextNum;//����������
    DispItem = IcoMenu[language].Text;  //����


    GUI_Clear();
//-------------------
    if(Refresh == FlashMode_AutoInit)
	{//��0����,��ʼ��Item��ֵ
        PUSH();
        Item = 0;
        Where = 0;
    }
    GUI_DispStringAtBar(*(DispItem+Item),1,ICO_PosY+ICO_YSize,126,GUI_TA_HCENTER);//�˵�����
    GUI_DrawIcon(icos[Item],ICO_PosX,ICO_PosY);               //ͼ��

    //��ʾ������Ӧ��������ʾ,1-->"����"
    GUI_DispStringAtBar(*(Tip[language].Text+1),1,Enter_PosY,126,GUI_TA_HCENTER);

    Bar(Item,ItemNum,MenuBarPosX,MenuBarNumPosX);                  //ά��������
    return;
}

/*
*****************************************************************************
* DispIcoMenuEnter - ͼ�����ȷ��������Ϊ
* DESCRIPTION: -
* �ַ����������ת
* ��һ��˵���Enter������
* Return :
*
*****************************************************************************
*/
void DispIcoMenuEnter()
{

    switch(Item)
	{
        case 0:
		{
            GUI_Clear();
            //����
            Jump2Menu(MenuFuncIndex,FlashMode_AutoInit);
            return;
        }
        case 1:
		{
            GUI_Clear();
            //����
            Jump2Menu(MenuParaIndex,FlashMode_AutoInit);
            return;
        }
        case 2:
		{
            GUI_Clear();
            //����
            Jump2Menu(MenuMeasureIndex,FlashMode_AutoInit);
            return;
        }
        case 3:
		{
            GUI_Clear();
            //����
            Jump2Menu(MenuLanguageIndex,FlashMode_ManualInit);
            //��MenuLanguage.C�е�DispMenuLanguageInit�������޸�Item Where!
            return;
        }
        case 4:
		{
            Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
            return;
        }
        case 5:
		{
            Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
            return;
        }
        default:
		{
            Jump2Menu(MenuTopIndex,FlashMode_NoAction);
            return;
        }
    }

}

void DispIcoMenuBack()
{
    POP();
}

void DispIcoMenuUp()
{
    if(Item==0)
	{
        Item = ItemNum-1;
    }
	else
	{
        Item--;
    }

    GUI_DispStringAtBar(*(DispItem+Item),0,ICO_PosY+ICO_YSize,126,GUI_TA_HCENTER);//�˵�����
    GUI_DrawIcon(icos[Item],ICO_PosX,ICO_PosY);            //ͼ��
    Bar(Item,ItemNum,MenuBarPosX,MenuBarNumPosX);                  //ά��������
    Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
}

void DispIcoMenuDown()
{
    if(Item==(ItemNum-1))
	{
        Item = 0;
    }
	else
	{
        Item++;
    }

    GUI_DispStringAtBar(*(DispItem+Item),0,ICO_PosY+ICO_YSize,126,GUI_TA_HCENTER);//�˵�����
    GUI_DrawIcon(icos[Item],ICO_PosX,ICO_PosY);             //ͼ��
    Bar(Item,ItemNum,MenuBarPosX,MenuBarNumPosX);                  //ά��������
    Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
}
//---------------------------------------------------------



//---------------------------

void DispBuildTime(void)//����ʱ��
{

    GUI_DispStringAt("Build Time:",0,0);
    GUI_DispStringAt(__DATE__,0,2);
    GUI_DispStringAt(__TIME__,0,4);
}
