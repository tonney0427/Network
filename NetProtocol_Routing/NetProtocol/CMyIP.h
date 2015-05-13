/**@file
*@brief
*@author ACM2012
*@date 2015/4/18
*@version <0.1>
*@note
*声明MyIP类的头文件
*/
#pragma once
#include "NetProtocol.h"
#include "CRouting.h"


/**
*@class  <CMyIP>
*@brief  基于IP协议与客户端实现可靠传输与不可靠传输的类
*@author ACM2012
*@note
*基于IP协议实现选路与转发, 选路算法包括链路状态选路算法和距离向量选路算法, 通过选路算法构造转发表
*/
class CMyIP
{
public:
	_iphdr IP_HEADER; ///< 定义IP报文头部
	Msg *IP_data;      ///< 定义IP报文数据
	IP_Msg *MyIP;      ///< 定义IP报文
	_data  *info;
	int _offset;
	unsigned int sip;
	

public:
	CRouting Route;

public:
	/** @brief CMyIP类的构造函数 */
	CMyIP();
	/** @brief CMyIP类的析构函数 */
	~CMyIP();
	/** @brief 从网络层传送数据到传输层的函数 */
	Bool IP2Trans(WPARAM wparam, LPARAM lparam);
	/** @brief 从网络层传送数据到链路层的函数 */
	BOOL IP2Link(WPARAM wparam, LPARAM lparam);
	/** @brief 从链路层得到用于选路的信息 */
	BOOL RecvMsg(WPARAM wparam, LPARAM lparam);
	/** @brief 用于发送选路的信息 */
	BOOL SendMsg(WPARAM wparam, LPARAM lparam);
	/** @brief 从数组的下标得到对应的IP */
	unsigned int Num2IP(int num);
	/** @brief 从IP得到对应的数组下标 */
	BOOL IP2Num(unsigned int IP);
};

