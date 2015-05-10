
// NetProtocolView.cpp : CNetProtocolView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "NetProtocol.h"
#endif

#include "NetProtocolDoc.h"
#include "NetProtocolView.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void PrintView(CString e)
{
	((CMainFrame *)AfxGetApp()->GetMainWnd())->GetActiveView()->SendMessage(PRINT, (WPARAM)&e);
}


// CNetProtocolView

IMPLEMENT_DYNCREATE(CNetProtocolView, CEditView)

BEGIN_MESSAGE_MAP(CNetProtocolView, CEditView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
	ON_MESSAGE(PRINT, OnPrint)
//	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// CNetProtocolView ����/����

CNetProtocolView::CNetProtocolView()
{
	// TODO:  �ڴ˴���ӹ������
	log.Empty();
}

CNetProtocolView::~CNetProtocolView()
{
}

BOOL CNetProtocolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// CNetProtocolView ��ӡ

BOOL CNetProtocolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void CNetProtocolView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ��ʼ��ӡ
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CNetProtocolView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ������ӡ
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CNetProtocolView ���

#ifdef _DEBUG
void CNetProtocolView::AssertValid() const
{
	CEditView::AssertValid();
}

void CNetProtocolView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CNetProtocolDoc* CNetProtocolView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNetProtocolDoc)));
	return (CNetProtocolDoc*)m_pDocument;
}
#endif //_DEBUG


// CNetProtocolView ��Ϣ�������
LRESULT CNetProtocolView::OnPrint(WPARAM wparam, LPARAM lparam)
{
	CString mystr;
	mystr = *((CString *)wparam)+ _T("\r\n");
	log += mystr;
	SetWindowText(log);
	return 0;
}

