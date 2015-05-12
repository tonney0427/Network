/**@file
*@brief
*@author ACM2012
*@date 2015.4.18
*@version <0.1>
*@note
*����CMyIP����ļ�
*/
#include "stdafx.h"
#include "CMyIP.h"

/******************************************************
*
*			  222.20.101.215
*             /				\
*            /				 \
*           /			      \
*  127.0.0.1                222.20.101.58
*			\					   /
*			 \				      /
*             \				     /
*       222.20.101.43----222.20.101.54
********************************************************/

					/*127.0.0.1, 222.20.101.215, 222.20.101.43, 222.20.101.54, 222.20.101.58 */
unsigned int IpNum[IPN] = { 0, 2130706433, 3725878743, 3725878571, 3725878582, 3725878586};
/**
* @author ACM2012
* @param
* @exception
* @return ��
* @note
* CMyIP��Ĺ��캯�� 
* @remarks
*/
CMyIP::CMyIP()
{
	_offset = 0;
	sip = IpNum[1];
	info->c[1][2] = 1;
	info->c[1][3] = 1;
}

/**
* @author ACM2012
* @param
* @return ��
* @note
* CMyIP�����������
* @remarks
*/
CMyIP::~CMyIP()
{
}

/**
* @author ACM2012
* @param [in] wparam��ʾ����㴫���������ݰ��ṹָ��, lparam��ʾ����㴫�����Ĳ���.
* @return ����FALSE˵�����͵���·�����Ϣʧ�ܣ�����TRUE˵�����ͳɹ�
* @note ����������Ҫ�ǽ�Msg�ṹ��IP��ַ����Ϣ��Ƭ��װ��IP_msg���͸���·��
*/
BOOL CMyIP::IP2Link(WPARAM wparam, LPARAM lparam)
{
	///< �������������Msg�ṹ��IP��ַ���뵽IP_msg�ṹ��,
	///< �����Ϣ���������ͽ��з�Ƭ����, 
	///< ������·��ķ��ͺ����������ʧ�� return FALSE;
	///< ���� return TRUE;
	MyIP = new IP_Msg;
	int offset = 0, ident = 0;
	ident++;
	IP_data = (struct Msg*)wparam;
	while (IP_data->datelen - 8 * offset > MAXSIZE)
	{
		IP_HEADER.ih_protl = IP_data->protocol;
		IP_HEADER.ih_saddr = IP_data->sip;
		IP_HEADER.ih_daddr = IP_data->dip;
		IP_HEADER.ih_flags = 1;
		IP_HEADER.ih_ident = ident;
		IP_HEADER.ih_offset = offset;
		IP_HEADER.ih_len = strlen(IP_data->data);
		offset = offset + MAXSIZE / 8;
		IP_HEADER.ih_version = 4;
		IP_HEADER.ih_sport = IP_data->ih_sport;
		IP_HEADER.ih_dport = IP_data->ih_dport;
		MyIP->iphdr = &IP_HEADER;
		memcpy(MyIP->data, IP_data->data, MAXSIZE);
		(AfxGetApp()->m_pMainWnd)->SendMessage(LINKSEND, (WPARAM)MyIP, lparam);
	}
	IP_HEADER.ih_protl = IP_data->protocol;
	IP_HEADER.ih_saddr = IP_data->sip;
	IP_HEADER.ih_daddr = IP_data->dip;
	IP_HEADER.ih_flags = 0;
	IP_HEADER.ih_ident = ident;
	IP_HEADER.ih_offset = offset;
	IP_HEADER.ih_len = strlen(IP_data->data);
	IP_HEADER.ih_version = 4;
	IP_HEADER.ih_sport = IP_data->ih_sport;
	IP_HEADER.ih_dport = IP_data->ih_dport;
	MyIP->iphdr = &IP_HEADER;
	memcpy(MyIP->data, IP_data->data, IP_data->datelen - 8 * offset);
	(AfxGetApp()->m_pMainWnd)->SendMessage(LINKSEND, (WPARAM)MyIP, lparam);
	return 0;
}

/**
* @author ACM2012
* @param [in] wparam��ʾ����㴫���������ݰ��ṹָ��, lparam��ʾ����㴫�����Ĳ���.
* @return ����FALSE˵��û�з��ͳɹ�������TRUE˵�����ͳɹ�
* @note ����������Ҫ����·�㷢�͹�������Ϣ�ֽ��Msg�ṹ, ���͸������
*/
Bool CMyIP::IP2Trans(WPARAM wparam, LPARAM lparam)
{
	///< ������·�㷢�͵����ݽ��а���õ����ĳ����Լ�ƫ��, �Ƚ�ƫ�����Ƿ���ڱ��ĳ���
	///< �����ַ�Ƭȱʧ���߼���ͳ����� return FALSE;
	///< ���������ݳɹ����� ���������ļ���ͼ��, ��û�д���
	///< ��IP_msg�ṹ�����Msg�ṹ
	int ident = 1;
	MyIP = (struct IP_Msg*)wparam;

	if (MyIP->iphdr->ih_ident == ident)
	{
		if (MyIP->iphdr->ih_offset * 8 == _offset)
		{
			if (MyIP->iphdr->ih_flags){
				memcpy(IP_data->data + _offset, MyIP->data, MAXSIZE);
				_offset = _offset + MAXSIZE;
			}
			else{
				memcpy(IP_data->data + _offset, MyIP->data, MyIP->iphdr->ih_len - _offset);
				_offset = 0;
				IP_data->sip = MyIP->iphdr->ih_saddr;
				IP_data->dip = MyIP->iphdr->ih_daddr;
				IP_data->ih_sport = MyIP->iphdr->ih_sport;
				IP_data->ih_dport = MyIP->iphdr->ih_dport;
				IP_data->protocol = MyIP->iphdr->ih_protl;
				IP_data->datelen = MyIP->iphdr->ih_len;
				(AfxGetApp()->m_pMainWnd)->SendMessage(TRANSTOAPP, (WPARAM)IP_data, lparam);
			}
		}
	}

	return 0;
}

/**
* @author ACM2012
* @param [in] wparam��ʾ����㴫���������ݰ��ṹָ��, lparam��ʾ����㴫�����Ĳ���.
* @return ����FALSE˵��û�з��ͳɹ�������TRUE˵�����ͳɹ�
* @note ����������Ҫ����·�㷢�͹�������Ϣ�õ�ѡ·������
*/
BOOL CMyIP::RecvMsg(WPARAM wparam, LPARAM lparam)
{
	///< ������·�㷢�͵����ݽ��а���õ�Դ�ڵ��������Ϣ
	///< ����Դ�ڵ���Ŀ�Ľڵ�����ӽ�info�ṹ���и���
	MyIP = (struct IP_Msg*)wparam;
	for (int i = 1; i <= IPN; i++)
	{
		for (int j = i; j <= IPN; j++)
		{
			info->c[i][j] = maxint;
			info->c[j][i] = maxint;
		}
	}
	_data *indata = (struct _data*)MyIP->data;
	for (int i = 1; i <= IPN; i++)
		for (int j = 1; j <= IPN; j++)
		{
			if (info->c[i][j] != 1 && indata->c[i][j] == 1)
				info->c[i][j] = 1;
		}

	int m = 0, n = 0;
	m = IP2Num(MyIP->iphdr->ih_saddr);         
	n = IP2Num(MyIP->iphdr->ih_daddr);

	info->c[m][n] = 1;
	info->c[n][m] = 1;

	return 0;
}

/**
* @author ACM2012
* @param [in] wparam��ʾ�Լ���װ�����ݰ��ṹָ��, lparam��ʾ���ɲ���.
* @return ����0˵�����ͳɹ�������˵������ʧ��
* @note ��������ѡ·�����ݵ�ѡ·�㷨�õ���һ��Ŀ��IP
*/
BOOL CMyIP::SendMsg(WPARAM wparam, LPARAM lparam)
{
	///< ͨ��ѡ������ѡ·�㷨, �õ���һ���ڵ��IP
	///< 
	///< 
	MyIP->data = (char *)info;
	MyIP->iphdr->ih_saddr = sip;
	MyIP->iphdr->ih_protl = 1;
	MyIP->iphdr->ih_flags = 0;
	MyIP->iphdr->ih_ident = 0;
	MyIP->iphdr->ih_offset = 0;
	MyIP->iphdr->ih_len = strlen(MyIP->data);
	MyIP->iphdr->ih_version = 4;
	int m = IP2Num(sip);
	for (int i = 1; i <= IPN; i++)
	{
		if (info->c[i][m] == 1 || info->c[m][i] == 1)
		{
			MyIP->iphdr->ih_daddr = Num2IP(i);
			(AfxGetApp()->m_pMainWnd)->SendMessage(LINKSEND, (WPARAM)MyIP, lparam);
		}
	}
	return 0;
}

/**
* @author ACM2012
* @param [in] �����±�
* @return ��Ӧ��IP
* @note ����������Ҫ�Ǵ�������±�õ���Ӧ��IP
*/
unsigned int CMyIP::Num2IP(int num)
{
	return IpNum[num];
}

/**
* @author ACM2012
* @param [in] IP
* @return ��Ӧ�������±�
* @note ����������Ҫ�Ǵ�IP�õ���Ӧ�������±�
*/
BOOL CMyIP::IP2Num(unsigned int IP)
{
	for (int i = 1; i <= IPN; i++)              
	{
		if (IpNum[i] == IP)
			return i;
	}

	return 0;
}