
// ApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "ApplicationDlg.h"
#include "afxdialogex.h"
#include <utility>
#include <tuple>
#include <vector>
#include <gdiplus.h>
#include <iostream>
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef MIN_SIZE
#define MIN_SIZE 300
#endif


void CStaticImage::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	GetParent()->SendMessage(CApplicationDlg::WM_DRAW_IMAGE, (WPARAM)lpDrawItemStruct);
	
}

void CStaticHistogram::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	GetParent()->SendMessage(CApplicationDlg::WM_DRAW_HISTOGRAM, (WPARAM)lpDrawItemStruct);

}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override    // DDX/DDV support
	{
		CDialogEx::DoDataExchange(pDX);
	}

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CApplicationDlg dialog

CApplicationDlg::CApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_APPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_ctrlImage);
	DDX_Control(pDX, IDC_HISTOGRAM, m_ctrlHistogram);
}

BEGIN_MESSAGE_MAP(CApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateFileClose)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_MESSAGE(WM_DRAW_IMAGE, OnDrawImage)
	ON_MESSAGE(WM_DRAW_HISTOGRAM, OnDrawHistogram)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


void CApplicationDlg::OnDestroy()
{
	Default();
}

float CApplicationDlg::Skalovanie(CRect r, BITMAP bi)
{
	float fact = 1.0;

	if ((bi.bmHeight > r.Height()) && (bi.bmWidth <= r.Width()))
		fact = (float)bi.bmHeight / (float)r.Height();

	if ((bi.bmWidth > r.Width()) && (bi.bmHeight <= r.Height()))
		fact = (float)bi.bmWidth / (float)r.Width();

	if (((bi.bmWidth < r.Width()) && (bi.bmHeight < r.Height())) ||
		((bi.bmWidth > r.Width()) && (bi.bmHeight > r.Height()))) {

		if (r.Height() > r.Width())
			fact = (float)bi.bmWidth / (float)r.Width();
		else fact = (float)bi.bmHeight / (float)r.Height();
	}

	return fact;
}

LRESULT CApplicationDlg::OnDrawImage(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)wParam;

	CDC * pDC = CDC::FromHandle(lpDI->hDC);

	//DRAW BITMAP
	if (image != nullptr) {

		CBitmap bmp;
		CDC bmDC;
		CBitmap *pOldbmp;
		BITMAP  bi;

		//udaje nasho image obrazku 
		bmp.Attach(image->Detach());
		//udaje z pdc su skopirovane do bmDC
		bmDC.CreateCompatibleDC(pDC);

		CRect r(lpDI->rcItem);

		//bmDC je kopia pDC, pDC je to s cim pracujeme
		//smernik ukazuje na bmDC
		pOldbmp = bmDC.SelectObject(&bmp);
		//vlastnosti BITMAP do bmp
		bmp.GetBitmap(&bi);
		
		//skalovanie		
		bi.bmWidth *= ((float)r.Width() / (float)bi.bmWidth) * Skalovanie(r, bi);;
		bi.bmHeight *= ((float)r.Height() / (float)bi.bmHeight) * Skalovanie(r, bi);;
		pDC->SetStretchBltMode(HALFTONE);

		pDC->StretchBlt(0, 0, r.Width(), r.Height(), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
		bmDC.SelectObject(pOldbmp);
		image->Attach((HBITMAP)bmp.Detach());

		return S_OK;
	}
	return S_OK;
}

void CApplicationDlg::Histogram(int h, int w)
{
	if (image != nullptr) {

		COLORREF ccolor = 0;
		int *Red = new int[(h*w)];
		int *Green = new int[(h*w)];
		int *Blue = new int[(h*w)];

		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				ccolor = image->GetPixel(i, j);
				Red[(w*j) + i] = (int)GetRValue(ccolor);
				Green[(w*j) + i] = (int)GetGValue(ccolor);
				Blue[(w*j) + i] = (int)GetBValue(ccolor);
			}

		for (int i = 0; i < h*w; i++)
		{
			histogramR[Red[i]]++; histogramG[Green[i]]++; histogramB[Blue[i]]++;
		}
	}
}


float CApplicationDlg::FunkciaMax(int *pole)
{
	float max;
	max = pole[0];
	for (int i = 0; i <= 255; i++)
	{
		if (max < pole[i]) max = pole[i];
	}
	return max;
}


void CApplicationDlg::KresliHistogram(float sx, float sy, CRect rect,CDC * pDC)
{
	CPen penR(PS_SOLID, 1, RGB(255, 0, 0));
	CPen penG(PS_SOLID, 1, RGB(0, 255, 0));
	CPen penB(PS_SOLID, 1, RGB(0, 0, 255));

	for (int i = 0; i < 255; i++)
	{
		pDC->SelectObject(&penR);
		pDC->MoveTo(sx*i, rect.Height() - sy * histogramR[i]);
		pDC->LineTo(sx*(i + 1), rect.Height() - sy *histogramR[i + 1]);

		pDC->SelectObject(&penG);
		pDC->MoveTo(sx*i, rect.Height() - sy * histogramG[i]);
		pDC->LineTo(sx*(i + 1), rect.Height() - sy * histogramG[i + 1]);

		pDC->SelectObject(&penB);
		pDC->MoveTo(sx*i, rect.Height() - sy * histogramB[i]);
		pDC->LineTo(sx*(i + 1), rect.Height() - sy * histogramB[i + 1]);
	}
}

LRESULT CApplicationDlg::OnDrawHistogram(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)wParam;

	CDC * pDC = CDC::FromHandle(lpDI->hDC);

	//DRAW BITMAP
	if (image != nullptr) {

		CBitmap bmp;
		CDC bmDC;
		BITMAP  bi;
		CRect rect(lpDI->rcItem);
		float maxR, maxG, maxB;
		float factor = 0;
		float sx, sy;
		
		bmp.Attach(image->Detach());
		bmDC.CreateCompatibleDC(pDC);
		bmp.GetBitmap(&bi);
		image->Attach((HBITMAP)bmp.Detach());

		Histogram(bi.bmHeight, bi.bmWidth);

		//skalovanie histogramu
		maxR = FunkciaMax(histogramR);
		maxG = FunkciaMax(histogramG);
		maxB = FunkciaMax(histogramB);
		
		if ((factor < maxR) || (factor < maxG) || (factor < maxB))
		{
			if (factor < maxR) factor = maxR;
			else if(factor < maxG) factor = maxG;
			else factor = maxB;
		}

		sx = (float)rect.Width()/256;
		sy = (float)rect.Height()/factor;
		KresliHistogram(sx, sy, rect, pDC);
	}
	else
	{
		CRect rect(lpDI->rcItem);
		CBrush brush;
		brush.CreateSolidBrush(RGB(255, 255, 255));
		pDC->FillRect(&rect, &brush);
		DeleteObject(brush);

	}
	return S_OK;
}

void CApplicationDlg::OnClose()
{
	EndDialog(0);
}

BOOL CApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

									// TODO: Add extra initialization here
	CRect rct;

	CRect rctClient;
	GetClientRect(&rctClient);

	m_ctrlImage.GetWindowRect(&rct);
	m_ptImage.x = rctClient.Width() - rct.Width();
	m_ptImage.y = rctClient.Height() - rct.Height();

	m_ctrlHistogram.GetWindowRect(&rct);
	m_ptHistogram.x = rctClient.Width() - rct.Width();
	m_ptHistogram.y = rctClient.Height() - rct.Height();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


void CApplicationDlg::OnSize(UINT nType, int cx, int cy)
{
	Invalidate();
	__super::OnSize(nType, cx, cy);
	if (m_ctrlImage)
		m_ctrlImage.MoveWindow(CRect((cx*0.2), 0, cx, cy));

	if (m_ctrlHistogram)
		m_ctrlHistogram.MoveWindow(CRect(0, (cy*0.5), (cx*0.2), cy));
}


void CApplicationDlg::OnPaint()
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
HCURSOR CApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CApplicationDlg::OnFileOpen()
{
	//GET FILE NAME AND CREATE GDIPLUS BITMAP
	// file dialog (.jpg a .png)
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Jpg Files (*.jpg)|*.jpg|Png Files (*.png)|*.png||"));
	if (image == nullptr) {
		// tu zobrazujem dialog
		if (dlg.DoModal() == IDOK) {
			path_name = dlg.GetPathName();
			image = new CImage();
			//path_name je protected premenna
			if (image->Load(path_name))
			{
				delete image;
				image = nullptr;
			}

			// prekreslenie vsetkych okien
			Invalidate();
		}
		else {
			::MessageBox(NULL, __T("Chyba pri zobrazeni file dialogu."), __T("Error"), MB_OK);
		}
		//::MessageBox(NULL, __T("Prvy IF, image je nula"), __T("Error"), MB_OK);
	}
	else {
		delete image;
		image = nullptr;
		/* zobrazenie file dialogu */
		if (dlg.DoModal() == IDOK) {
			path_name = dlg.GetPathName();
			image = new CImage();
			if (image->Load(path_name))
			{
				delete image;
				image = nullptr;
			}
			// prekreslenie vsetkych okien
			Invalidate();
		}
		else {
			::MessageBox(NULL, __T("Chyba pri zobrazeni file dialogu."), __T("Error"), MB_OK);
		}
	}
}


void CApplicationDlg::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);

}


void CApplicationDlg::OnFileClose()
{
	::MessageBox(NULL, __T("Zatvorenie suboru"), __T("Message"), MB_OK);
	if (image != nullptr)
	{
		delete image;
		image = nullptr;
	}
	Invalidate();
}


void CApplicationDlg::OnUpdateFileClose(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}