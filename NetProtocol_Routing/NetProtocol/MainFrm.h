
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include <map>
#include "CMyIP.h"
using namespace std;

class CMainFrame : public CFrameWnd
{

protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	// ����
public:

	// ����
public:

public:
	CMyIP IP;
	// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	HWND PPwnd;
	// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar            m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	map <CWnd *, int>  pwnd2port;
	map <int, HWND>  port2hwnd;
	int  numprocess;
	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	static DWORD WINAPI packcap(LPVOID lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg LRESULT OnCheck(WPARAM, LPARAM);
	afx_msg LRESULT OnTrans2App(WPARAM, LPARAM);
	afx_msg LRESULT OnApp2Trans(WPARAM, LPARAM);
	afx_msg LRESULT OnIP2Trans(WPARAM, LPARAM);
	afx_msg LRESULT OnLink2IP(WPARAM, LPARAM);
	afx_msg LRESULT OnTrans2IP(WPARAM, LPARAM);
	afx_msg LRESULT OnIP2Link(WPARAM, LPARAM);
	afx_msg LRESULT OnLinkSend(WPARAM, LPARAM);
};


