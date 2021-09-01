
// Pavlovska_zapocetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Pavlovska_zapocet.h"
#include "Pavlovska_zapocetDlg.h"
#include "afxdialogex.h"

#include <thread>
#include <time.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

UINT_PTR Timer;

int hodnoty[3] = { 0,0,0 };

int cisloCasovace = 1;

byte cisloBitmapy[3] = { IDB_BITMAP1 ,IDB_BITMAP2 ,IDB_BITMAP3 };

CBitmap bmp[3];


int intervalTimer = 100;



int main()
{
	srand(time(NULL));
}

int nahodneCislo()
{
	return 1 + (int)(3 * rand()) / RAND_MAX;
}

// CPavlovskazapocetDlg dialog




CPavlovskazapocetDlg::CPavlovskazapocetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAVLOVSKA_ZAPOCET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPavlovskazapocetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDB_BITMAP1, PictureBox1);
	DDX_Control(pDX, IDB_BITMAP2, PictureBox2);
	DDX_Control(pDX, IDB_BITMAP3, PictureBox3);
	DDX_Control(pDX, IDC_BUTTON1, Hrat);
	DDX_Control(pDX, IDC_BUTTON2, Zastavit);
	DDX_Control(pDX, IDC_EDIT3, Vysledek);
	DDX_Control(pDX, IDC_SPIN, SpinButton);
	DDX_Control(pDX, IDC_EDITSPIN, Interval);
}

BEGIN_MESSAGE_MAP(CPavlovskazapocetDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPavlovskazapocetDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPavlovskazapocetDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDITSPIN, &CPavlovskazapocetDlg::OnEnChangeEditspin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, &CPavlovskazapocetDlg::OnDeltaposSpin)
	ON_WM_TIMER()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_EN_CHANGE(IDC_EDIT3, &CPavlovskazapocetDlg::OnEnChangeEdit3)
	
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPavlovskazapocetDlg message handlers

BOOL CPavlovskazapocetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	Zastavit.EnableWindow(FALSE);
	Hrat.SetFocus();
	Hrat.UpdateWindow();
	Hrat.UpdateData();
	Zastavit.UpdateWindow();
	Zastavit.UpdateData();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	for (int i = 0; i < 3; i++) {
		bmp[i].LoadBitmap(cisloBitmapy[i]);
	}
	PictureBox1.SetBitmap(bmp[0]);
	PictureBox2.SetBitmap(bmp[1]);
	PictureBox3.SetBitmap(bmp[2]);

	UDACCEL AccellValue;
	AccellValue.nSec = 1000;
	AccellValue.nInc = 100;
	SpinButton.SetRange(100, 1000);
	SpinButton.SetAccel(1, &AccellValue);
	SpinButton.SetPos(500);
	SpinButton.SetBuddy(&Interval);
	Interval.UpdateData(TRUE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPavlovskazapocetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPavlovskazapocetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int pocetStejnych() {
	int pocet[3] = { 0,0,0 };

	for (int i = 0; i < 3; i++) {
		pocet[hodnoty[i] - 1] = pocet[hodnoty[i] - 1] + 1;
	}
	int max = 0;
	for (int i = 0; i < 3; i++) {
		if (pocet[i] > max) {
			max = pocet[i];
		}
	}
	return max;
}

void CPavlovskazapocetDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	Vysledek.SetWindowText((LPCTSTR)" ");
	Zastavit.EnableWindow(TRUE);
	Hrat.EnableWindow(FALSE);
	Zastavit.SetFocus();
	Zastavit.SetActiveWindow();
	intervalTimer = SpinButton.GetPos();
	Timer = SetTimer(cisloCasovace, intervalTimer, NULL);
	UpdateDialogControls(this, false);
}


void CPavlovskazapocetDlg::OnBnClickedButton2() //Zastavit
{
	// TODO: Add your control notification handler code here
	KillTimer(cisloCasovace);
	Timer = NULL;
	CString stejnychStr;
	stejnychStr.Format(_T("%d - %d"), pocetStejnych(), 3);
	Vysledek.SetWindowText((LPCTSTR)stejnychStr);
	Zastavit.EnableWindow(FALSE);
	Hrat.EnableWindow(TRUE);
	Hrat.SetFocus();
	Hrat.SetActiveWindow();
	UpdateDialogControls(this, false);

}




void CPavlovskazapocetDlg::OnEnChangeEditspin()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}



void CPavlovskazapocetDlg::OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (Timer != NULL) {
		KillTimer(cisloCasovace);
		intervalTimer = SpinButton.GetPos();
		Timer = SetTimer(cisloCasovace, intervalTimer, NULL);
	}
	*pResult = 0;
}


void CPavlovskazapocetDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}



void CPavlovskazapocetDlg::OnTimer(UINT_PTR nIDEvent)
{
	for (int i = 0; i < 3; i++) {
		hodnoty[i] = nahodneCislo();
	}

	PictureBox1.SetBitmap(bmp[hodnoty[0] - 1]);
	PictureBox2.SetBitmap(bmp[hodnoty[1] - 1]);
	PictureBox3.SetBitmap(bmp[hodnoty[2] - 1]);
}
