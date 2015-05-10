/**@file
*@brief
*@author ACM2012
*@date 2015/4/18
*@version <0.1>
*@note
*����CRouting���ͷ�ļ�
*/
#pragma once
#include "NetProtocol.h"

/**
*@class  <CRouting>
*@brief  ʵ��ѡ·�㷨, ����LSȫ�������㷨��DV�ֲ������㷨
*@author ACM2012
*@note
*ѡ·�㷨������·״̬ѡ·�㷨�;�������ѡ·�㷨, ͨ��ѡ·�㷨�õ���һ��ת����IP��ַ
*/
class CRouting
{
public:
	_data *FIP;

public:
	/** @brief CRouting��Ĺ��캯�� */
	CRouting();
	/** @brief CRouting����������� */
	~CRouting();
	/** @brief ��ջѡ����һ��·,������һ��IP��ַ */
	BOOL searchPath(int *pre, int v, int u);
	/** @brief ���ȫ��·�������·�� */
	void Dijkstra(int n, int v, int *dist, int *pre, int c[maxnum][maxnum]);
	/** @brief ���ȫ��·�������·�� */
	BOOL LS(_data *FIP);
};

