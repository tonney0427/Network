
// NetProtocolView.h : CNetProtocolView ��Ľӿ�
//

#pragma once


class CNetProtocolView : public CEditView
{
protected: // �������л�����
	CNetProtocolView();
	DECLARE_DYNCREATE(CNetProtocolView)

// ����
public:
	CNetProtocolDoc* GetDocument() const;
	CString  log;
// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	afx_msg LRESULT OnPrint(WPARAM wparam,LPARAM lparam);

// ʵ��
public:
	virtual ~CNetProtocolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};

#ifndef _DEBUG  // NetProtocolView.cpp �еĵ��԰汾
inline CNetProtocolDoc* CNetProtocolView::GetDocument() const
   { return reinterpret_cast<CNetProtocolDoc*>(m_pDocument); }
#endif

