
// Pavlovska_zapocetDlg.h : header file
//

#pragma once


// CPavlovskazapocetDlg dialog
class CPavlovskazapocetDlg : public CDialogEx
{
// Construction
public:
	CPavlovskazapocetDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAVLOVSKA_ZAPOCET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic PictureBox1;
	CStatic PictureBox2;
	CStatic PictureBox3;
	CButton Hrat;
	CButton Zastavit;
	CEdit Vysledek;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CSpinButtonCtrl SpinButton;
	CEdit Interval;
	afx_msg void OnEnChangeEditspin();
	afx_msg void OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
