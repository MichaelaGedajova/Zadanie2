
// ApplicationDlg.h : header file
//

#pragma once

#include <GdiPlus.h>

class CStaticImage : public CStatic
{
public:
	// Overridables (for owner draw only)
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
};

class CStaticHistogram : public CStatic
{
public:
	// Overridables (for owner draw only)
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
};
// CApplicationDlg dialog
class CApplicationDlg : public CDialogEx
{
// Construction
public:
	enum
	{
		WM_DRAW_IMAGE = (WM_USER + 1),
		WM_DRAW_HISTOGRAM
	};
	enum
	{
		WM_DRAW_IMAGE2 = (WM_USER + 1),
		WM_DRAW_HISTOGRAM2
	};

	CApplicationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APPLICATION_DIALOG };
#endif

	protected:
	void DoDataExchange(CDataExchange* pDX) override;	// DDX/DDV support

	void OnOK() override {}
	void OnCancel() override {}


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	BOOL OnInitDialog() override;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CString path_name;
	DECLARE_MESSAGE_MAP()
	CImage *image=nullptr;
	BITMAP bitmap;
	float CApplicationDlg::Skalovanie(CRect r, BITMAP bi);
	bool checkbox_red = false;
	bool checkbox_green = false;
	bool checkbox_blue = false;
	bool checkbox_vyrovnanie = false;
	bool checkbox_ciernobiely = false;
	int m_hR[256] = { 0 };
	int m_hG[256] = { 0 };
	int m_hB[256] = { 0 };
	int noveR[256] = { 0 };
	int noveG[256] = { 0 };
	int noveB[256] = { 0 };
	float kumR[256] = { 0 };
	float kumG[256] = { 0 };
	float kumB[256] = { 0 };
	int tmp_hist[256] = { 0 };
	int max_hist = 0;
	int min_hist = 0;
	int tmpR, tmpG, tmpB;
	int tmpRf, tmpGf, tmpBf;

	bool m_bhist = false;
	BYTE *byte_ptr;
	BYTE *byte_ptr1;
	BYTE *byte_ptr2;
	int pitch; //kolko realne ma bitmapa na sirku
	int pitch1;
	int pitch2;
	int width = 0;
	int height = 0;
	UINT_PTR id = 0;
	float tmp;
	float tmpf[256] = { 0 };

public:
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	afx_msg void OnFileClose();
	afx_msg void OnUpdateFileClose(CCmdUI *pCmdUI);
	afx_msg void OnClose();
	afx_msg LRESULT OnDrawImage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrawHistogram(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHistogramRed();
	afx_msg void OnHistogramGreen();
	afx_msg void OnHistogramBlue();
	afx_msg void OnUpdateHistogramRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHistogramGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHistogramBlue(CCmdUI *pCmdUI);
	afx_msg void OnHistogramVyrovnanie();
	afx_msg void OnHistogramCiernobiely();
	afx_msg void OnUpdateHistogramVyrovnanie(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHistogramCiernobiely(CCmdUI *pCmdUI);
	afx_msg void KresliHistogram(CRect, CDC *, int *, COLORREF color, float);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void HistogramEqualization();
	afx_msg void Grayscale(int h, int w);

	void Histogram();
	float FunkciaMax(int *pole);
	
	//void KresliHistogram(CRect rect, CDC * pDC, int *pole, COLORREF color, float scale);

protected:
	CStaticImage m_ctrlImage;
	CStaticHistogram m_ctrlHistogram;
	CPoint m_ptImage;
	CPoint m_ptHistogram;

public:
	afx_msg void OnStnClickedImage();
};
