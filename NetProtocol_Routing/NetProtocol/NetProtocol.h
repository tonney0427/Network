
// NetProtocol.h : NetProtocol 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

#define PRINT		(WM_USER+1000)
#define CHECKHWND	 WM_USER+1001

// CNetProtocolApp:
// 有关此类的实现，请参阅 NetProtocol.cpp
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
*@brief 存放IP首部的结构体
*@author ACM2012
*@note
*自己定义的IP报文首部
*/
struct _iphdr //定义IP首部 
{
	unsigned short ih_version;  ///< 标识了数据包的IP版本号,一共4位, 0100表示IPv4, 0110表示IPv6
	unsigned short ih_len;	    ///< 16位数据报长度
	unsigned short ih_ident;	///< 数据报的16位标识
	unsigned short ih_flags;    ///< 数据报的标志
	unsigned short ih_offset;	///< 数据报的片偏移
	unsigned short ih_protl;	///< 数据报的协议, 定义0代表传输层数据, 定义1代表节点相接的信息
	unsigned int ih_saddr;		///< 32位源IP
	unsigned int ih_daddr;		///< 32位目的IP
	unsigned int ih_sport;		///< 32位源端口号
	unsigned int ih_dport;		///< 32位目的端口号
};

struct Msg{                     ///<数据
	unsigned int ih_sport;		///< 32位源端口号
	unsigned int ih_dport;		///< 32位目的端口号
	unsigned int sip;			///< 32位源IP
	unsigned int dip;			///< 32位目的IP
	int datelen;
	char data[2048];
	unsigned int protocol;		///< 上层协议类型
};

struct IP_Msg{
	_iphdr *iphdr;				///<指向ip首部的指针
	char *data;
};

#define maxnum 100				///<定义最大的节点数
#define maxint 999999			///<定义最长的节点间距离

struct _data{
	int sid;				 ///< 源节点
	int did;				 ///< 目的节点
	int dist[maxnum];		 ///< 表示当前点到源点的最短路径长度
	int pre[maxnum];		 ///< 记录当前点的前一个结点
	int c[maxnum][maxnum];   ///< 记录图的两点间路径长度
};

#define IPN	6
#define MAX 0x3f3f3f3f
#define N 1010


//需要添加一个这样的结构，然后把边的个数和每个边的初始节点u,v,长度cost建立一个Edge结构
struct Edge{
	int u, v;
	int cost;
};
                        
class CNetProtocolApp : public CWinApp
{
public:
	CNetProtocolApp();

	// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNetProtocolApp theApp;
