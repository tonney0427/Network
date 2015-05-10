/**@file
*@brief
*@author ACM2012
*@date 2015.4.18
*@version <0.1>
*@note
*����CRouting����ļ�
*/
#include "stdafx.h"
#include "CRouting.h"

/**
* @author ACM2012
* @param
* @exception
* @return ��
* @note
* CRouting��Ĺ��캯��
* @remarks
*/
CRouting::CRouting()
{
}

/**
* @author ACM2012
* @param
* @return ��
* @note
* CMyIP�����������
* @remarks
*/
CRouting::~CRouting()
{
}

/**
* @author ACM2012
* @param [in] ��ʼ�ڵ�, Ŀ�Ľڵ�, ֮�������ڵ�Ķ�ջ
* @return ��ǰ�ڵ�Ӧ�����´���һ���ڵ�
* @note ��Ҫ��Ѱ����һ���ڵ�
*/
BOOL CRouting::searchPath(int *pre, int v, int u)
{
	int que[maxnum];
	int tot = 1;
	que[tot] = u;
	tot++;
	int tmp = pre[u];
	while (tmp != v)
	{
		que[tot] = tmp;
		tot++;
		tmp = pre[tmp];
	}
	que[tot] = v;
	return que[tot - 1];
}

/**
* @author ACM2012
* @param [in] ��ʼ�ڵ�, Ŀ�Ľڵ�, ��ǰ�ڵ㵽Դ�ڵ�����·������, ��ǰ�ڵ��ǰһ���ڵ�, ��¼ͼ�����ڵ��·������
* @return ��
* @note ȫ���������ŵ���һ���ڵ�
*/
void CRouting::Dijkstra(int n, int v, int *dist, int *pre, int c[maxnum][maxnum])
{
	bool s[maxnum];    // �ж��Ƿ��Ѵ���õ㵽S������
	for (int i = 1; i <= n; ++i)
	{
		dist[i] = c[v][i];
		s[i] = 0;     // ��ʼ��δ�ù��õ�
		if (dist[i] == maxint)
			pre[i] = 0;
		else
			pre[i] = v;
	}
	dist[v] = 0;
	s[v] = 1;

	// ���ν�δ����S���ϵĽ���У�ȡdist[]��Сֵ�Ľ�㣬������S��
	// һ��S����������V�ж��㣬dist�ͼ�¼�˴�Դ�㵽������������֮������·������
	for (int i = 2; i <= n; ++i)
	{
		int tmp = maxint;
		int u = v;
		// �ҳ���ǰδʹ�õĵ�j��dist[j]��Сֵ
		for (int j = 1; j <= n; ++j)
		if ((!s[j]) && dist[j]<tmp)
		{
			u = j;              // u���浱ǰ�ڽӵ��о�����С�ĵ�ĺ���
			tmp = dist[j];
		}
		s[u] = 1;    // ��ʾu���Ѵ���S������

		// ����dist
		for (int j = 1; j <= n; ++j)
		if ((!s[j]) && c[u][j]<maxint)
		{
			int newdist = dist[u] + c[u][j];
			if (newdist < dist[j])
			{
				dist[j] = newdist;
				pre[j] = u;
			}
		}
	}
}

BOOL CRouting::LS(_data *FIP)
{											          
	Dijkstra(FIP->sid, FIP->did, FIP->dist, FIP->pre, FIP->c);
	return searchPath(FIP->pre, FIP->sid, FIP->did);
}