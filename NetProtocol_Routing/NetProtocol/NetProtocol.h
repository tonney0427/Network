
// NetProtocol.h : NetProtocol Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#define PRINT		(WM_USER+1000)
#define CHECKHWND	 WM_USER+1001

// CNetProtocolApp:
// �йش����ʵ�֣������ NetProtocol.cpp
//

#define  TRANSTOIP      WM_USER+1000
#define  IPTOLINK       WM_USER+1001
#define  LINKSEND       WM_USER+1002
#define  TRANSTOAPP		WM_USER+1003
#define  IPTOTRANS      WM_USER+1004
#define  LINKTOIP       WM_USER+1005


typedef unsigned char Byte;
typedef unsigned short Ushort;
typedef int Bool;
#define MAXSIZE 1480

/**
*@class <_iphdr>
*@brief ���IP�ײ��Ľṹ��
*@author ACM2012
*@note
*�Լ������IP�����ײ�
*/
struct _iphdr //����IP�ײ� 
{
	unsigned short ih_version;  ///< ��ʶ�����ݰ���IP�汾��,һ��4λ, 0100��ʾIPv4, 0110��ʾIPv6
	unsigned short ih_len;	    ///< 16λ���ݱ�����
	unsigned short ih_ident;	///< ���ݱ���16λ��ʶ
	unsigned short ih_flags;    ///< ���ݱ��ı�־
	unsigned short ih_offset;	///< ���ݱ���Ƭƫ��
	unsigned short ih_protl;	///< ���ݱ���Э��, ����0�����������, ����1����ڵ���ӵ���Ϣ
	unsigned int ih_saddr;		///< 32λԴIP
	unsigned int ih_daddr;		///< 32λĿ��IP
};

struct Msg{                     ///<����
	unsigned int dip;
	char data[1024];
};

struct IP_Msg{
	_iphdr *iphdr;				///<ָ��ip�ײ���ָ��
	char *data;
};

#define maxnum 100				///<�������Ľڵ���
#define maxint 999999			///<������Ľڵ�����

struct _data{
	int sid;				 ///< Դ�ڵ�
	int did;				 ///< Ŀ�Ľڵ�
	int dist[maxnum];		 ///< ��ʾ��ǰ�㵽Դ������·������
	int pre[maxnum];		 ///< ��¼��ǰ���ǰһ�����
	int c[maxnum][maxnum];   ///< ��¼ͼ�������·������
};

#define IPN	6
                        
class CNetProtocolApp : public CWinApp
{
public:
	CNetProtocolApp();

	// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNetProtocolApp theApp;
