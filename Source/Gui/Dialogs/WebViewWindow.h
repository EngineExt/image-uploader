#ifndef IU_GUI_DIALOGS_WEBVIEWWINDOW_H
#define IU_GUI_DIALOGS_WEBVIEWWINDOW_H

#include "atlheaders.h"
#include <atlcrack.h>
#include "resource.h"       // main symbols
#include <Gui/Controls/WTLBrowserView.h>


class CWebViewWindow: public CWindowImpl<CWebViewWindow>
{
public:
	CWebViewWindow();
	~CWebViewWindow();

	DECLARE_WND_CLASS(_T("CWebViewWindow"))
	bool NavigateTo(const CString& url);
	int DoModal(HWND parent, bool show = true);
	int exec();
	void close();
	CWTLBrowserView view_;

protected:
	BEGIN_MSG_MAP(CWebViewWindow)
		
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnResize)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_ENABLE, OnEnable)
		MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
		                     
		 
	END_MSG_MAP()
	// Handler prototypes:
	//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnResize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEnable(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	HWND hWndClient_;
	bool isModal_;
	CIcon icon_;
	CIcon iconSmall_;
	bool captureActivate_;
	

};


#endif