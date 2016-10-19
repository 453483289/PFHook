
// PFHookDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <vector>

using namespace std;

typedef struct _HOOKITEM
{
	int iID;
	int iHookID;
	DWORD dwPID;
	LPVOID lpHookedAddr;
	LPVOID lpJmpAddr;
}HOOKITEM, *PHOOKITEM;

// CPFHookDlg �Ի���
class CPFHookDlg : public CDialogEx
{
// ����
public:
	CPFHookDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PFHOOK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbbProc;
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	int m_iDriverStatus;
	bool RefreshProcess();
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonHook();
	afx_msg void OnBnClickedButtonUnhook();
	CListBox m_lbHook;
	CEdit m_editHookAddr;
	CEdit m_editJmpAddr;
	int AddHookItem(DWORD dwPID, LPVOID lpHookedAddr, LPVOID lpJmpAddr);
	BOOL RemoveHookItem(int iItemID);
	vector<HOOKITEM> m_vecHookItem;
	CStatic m_staticStatus;
	BOOL CheckVT();
};
