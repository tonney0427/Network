/**@file
*@brief
*@author ACM2012
*@date 2015.4.18
*@version <0.1>
*@note
*定义CMyIP类的文件
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
* @return 无
* @note
* CMyIP类的构造函数 
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
* @return 无
* @note
* CMyIP类的析构函数
* @remarks
*/
CMyIP::~CMyIP()
{
}

/**
* @author ACM2012
* @param [in] wparam表示传输层传过来的数据包结构指针, lparam表示传输层传过来的参数.
* @return 返回FALSE说明发送到链路层的消息失败，返回TRUE说明发送成功
* @note 函数功能主要是将Msg结构和IP地址等信息分片组装成IP_msg发送给链路层
*/
BOOL CMyIP::IP2Link(WPARAM wparam, LPARAM lparam)
{
	///< 将运输层送来的Msg结构和IP地址插入到IP_msg结构中,
	///< 如果信息超过容量就进行分片处理, 
	///< 调用链路层的发送函数如果发送失败 return FALSE;
	///< 否则 return TRUE;
	MyIP = new IP_Msg;
	info = new _data;
	int offset = 0, ident = 0;
	ident++;
	IP_data = (struct Msg*)wparam;
	info->sid = IP2Num(sip);
	info->did = IP2Num(IP_data->ih_daddr);
	unsigned int dip = Num2IP(Route.LS(info));
	while (strlen(IP_data->data) - 8 * offset > MAXSIZE)
	{
		MyIP->iphdr->ih_protl = 0;
		MyIP->iphdr->ih_saddr = sip;
		MyIP->iphdr->ih_daddr = dip;
		MyIP->iphdr->ih_flags = 1;
		MyIP->iphdr->ih_ident = ident;
		MyIP->iphdr->ih_offset = offset;
		MyIP->iphdr->ih_len = strlen(IP_data->data);
		MyIP->iphdr->ih_sport = IP_data->ih_sport;
		MyIP->iphdr->ih_dport = IP_data->ih_dport;
		offset = offset + MAXSIZE / 8;
		MyIP->iphdr->ih_version = 4;
		strncpy_s(MyIP->data, MAXSIZE, IP_data->data, MAXSIZE);
		(AfxGetApp()->m_pMainWnd)->SendMessage(LINKSEND, (WPARAM)MyIP, lparam);
	}
	MyIP->iphdr->ih_protl = 0;
	MyIP->iphdr->ih_saddr = sip;
	MyIP->iphdr->ih_daddr = dip;
	MyIP->iphdr->ih_flags = 0;
	MyIP->iphdr->ih_ident = ident;
	MyIP->iphdr->ih_offset = offset;
	MyIP->iphdr->ih_len = strlen(IP_data->data);
	MyIP->iphdr->ih_sport = IP_data->ih_sport;
	MyIP->iphdr->ih_dport = IP_data->ih_dport;
	MyIP->iphdr->ih_version = 4;
	memcpy(MyIP->data, IP_data->data, strlen(IP_data->data) - offset * 8);
	(AfxGetApp()->m_pMainWnd)->SendMessage(LINKSEND, (WPARAM)MyIP, lparam);

	return 0;
}

/**
* @author ACM2012
* @param [in] wparam表示传输层传过来的数据包结构指针, lparam表示传输层传过来的参数.
* @return 返回FALSE说明没有发送成功，返回TRUE说明发送成功
* @note 函数功能主要是链路层发送过来的信息分解成Msg结构, 发送给运输层
*/
Bool CMyIP::IP2Trans(WPARAM wparam, LPARAM lparam)
{
	///< 根据链路层发送的数据进行剥离得到报文长度以及偏移, 比较偏移量是否等于报文长度
	///< 若发现分片缺失或者检验和出错则 return FALSE;
	///< 若是则数据成功接收 进行少量的检验和检查, 若没有错误
	///< 则将IP_msg结构剥离出Msg结构
	int ident = 1;
	MyIP = (struct IP_Msg*)wparam;

	if (MyIP->iphdr->ih_ident == ident)
	{
		if (MyIP->iphdr->ih_offset * 8 == _offset)
		{
			if (MyIP->iphdr->ih_flags){
				memcpy(IP_data->data + _offset, MyIP->data, MAXSIZE);
				_offset = _offset + MAXSIZE;
				IP_data->ih_daddr = MyIP->iphdr->ih_daddr;
			}
			else{
				memcpy(IP_data->data + _offset, MyIP->data, MyIP->iphdr->ih_len - _offset);
				_offset = 0;
				IP_data->ih_daddr = MyIP->iphdr->ih_daddr;
				(AfxGetApp()->m_pMainWnd)->SendMessage(TRANSTOAPP, (WPARAM)IP_data, lparam);
			}
		}
	}

	return 0;
}

/**
* @author ACM2012
* @param [in] wparam表示传输层传过来的数据包结构指针, lparam表示传输层传过来的参数.
* @return 返回FALSE说明没有发送成功，返回TRUE说明发送成功
* @note 函数功能主要是链路层发送过来的信息得到选路的数据
*/
BOOL CMyIP::RecvMsg(WPARAM wparam, LPARAM lparam)
{
	///< 根据链路层发送的数据进行剥离得到源节点的连接信息
	///< 根据源节点与目的节点的连接将info结构进行更新
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
* @param [in] wparam表示自己封装的数据包结构指针, lparam表示若干参数.
* @return 返回0说明发送成功，其他说明发送失败
* @note 函数功能选路的数据的选路算法得到下一个目的IP
*/
BOOL CMyIP::SendMsg(WPARAM wparam, LPARAM lparam)
{
	///< 通过选择两种选路算法, 得到下一个节点的IP
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
* @param [in] 数组下标
* @return 对应的IP
* @note 函数功能主要是从数组的下标得到对应的IP
*/
unsigned int CMyIP::Num2IP(int num)
{
	return IpNum[num];
}

/**
* @author ACM2012
* @param [in] IP
* @return 对应的数组下标
* @note 函数功能主要是从IP得到对应的数组下标
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