/**@file
*@brief
*@author ACM2012
*@date 2015/4/18
*@version <0.1>
*@note
*����MyIP���ͷ�ļ�
*/
#pragma once
#include "NetProtocol.h"
#include "CRouting.h"


/**
*@class  <CMyIP>
*@brief  ����IPЭ����ͻ���ʵ�ֿɿ������벻�ɿ��������
*@author ACM2012
*@note
*����IPЭ��ʵ��ѡ·��ת��, ѡ·�㷨������·״̬ѡ·�㷨�;�������ѡ·�㷨, ͨ��ѡ·�㷨����ת����
*/
class CMyIP
{
public:
	_iphdr IP_HEADER; ///< ����IP����ͷ��
	Msg *IP_data;      ///< ����IP��������
	IP_Msg *MyIP;      ///< ����IP����
	_data  *info;
	int _offset;
	unsigned int sip;
	

public:
	CRouting Route;

public:
	/** @brief CMyIP��Ĺ��캯�� */
	CMyIP();
	/** @brief CMyIP����������� */
	~CMyIP();
	/** @brief ������㴫�����ݵ������ĺ��� */
	Bool IP2Trans(WPARAM wparam, LPARAM lparam);
	/** @brief ������㴫�����ݵ���·��ĺ��� */
	BOOL IP2Link(WPARAM wparam, LPARAM lparam);
	/** @brief ����·��õ�����ѡ·����Ϣ */
	BOOL RecvMsg(WPARAM wparam, LPARAM lparam);
	/** @brief ���ڷ���ѡ·����Ϣ */
	BOOL SendMsg(WPARAM wparam, LPARAM lparam);
	/** @brief ��������±�õ���Ӧ��IP */
	unsigned int Num2IP(int num);
	/** @brief ��IP�õ���Ӧ�������±� */
	BOOL IP2Num(unsigned int IP);
};

