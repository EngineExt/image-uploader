// This file was generated by WTL Dialog wizard 
// Declaration of the CAddDirectoryServerDialog

#pragma once
#include "atlheaders.h"
#include "resource.h"       // main symbols
#include <vector>
#include <Gui/Controls/IconButton.h>
class CUploadEngineList;
// CAddDirectoryServerDialog

class CAddDirectoryServerDialog : 
	public CDialogImpl<CAddDirectoryServerDialog>	
{
public:
	CAddDirectoryServerDialog(CUploadEngineList* uploadEngineList);
	~CAddDirectoryServerDialog();
	enum { IDD = IDD_ADDDIRECTORYSERVERDLG, IDC_PRESETMENU_FIRST_ID = 15000,IDC_PRESETMENU_LAST_ID = 15100,
		IDC_PRESETMENU_SHARED_FOLDER_FIRST_ID=15200,  IDC_PRESETMENU_SHARED_FOLDER_LAST_ID = 15400};

    BEGIN_MSG_MAP(CAddDirectoryServerDialog)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
        COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
		COMMAND_HANDLER(IDC_DIRECTORYEDIT, EN_CHANGE, OnDirectoryEditChange);
		COMMAND_HANDLER(IDC_DOWNLOADURLEDIT, EN_CHANGE, OnDownloadUrlEditChange);
		COMMAND_HANDLER(IDC_CONNECTIONNAMEEDIT, EN_CHANGE, OnConnectionNameEditChange);
		COMMAND_HANDLER(IDC_BROWSEBUTTON, BN_CLICKED, OnBnClickedBrowsebutton)
		COMMAND_HANDLER(IDC_PRESETSBUTTON, BN_CLICKED, OnPresetButtonClicked)
		COMMAND_RANGE_HANDLER(IDC_PRESETMENU_FIRST_ID, IDC_PRESETMENU_LAST_ID, OnPresetMenuItemClick);
		COMMAND_RANGE_HANDLER(IDC_PRESETMENU_SHARED_FOLDER_FIRST_ID, IDC_PRESETMENU_SHARED_FOLDER_LAST_ID, OnPresetSharedFolderMenuItemClick);
		COMMAND_HANDLER(IDC_ADDFILEPROTOCOL, BN_CLICKED, OnBnClickedAddfileprotocol)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
    // Handler prototypes:
    //  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    //  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDirectoryEditChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDownloadUrlEditChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnConnectionNameEditChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPresetMenuItemClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPresetSharedFolderMenuItemClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	CString createdServerName();
protected:
	void GenerateDownloadLink();
	void GenerateExampleUrl();
	bool LoadComputerAddresses();
	bool connectionNameEdited;
	bool downloadUrlEdited;
	bool serverNameEdited;
	CUploadEngineList* uploadEngineList_;
	CString createdServerName_;
	std::vector<CString> addresses_;
	std::vector<CString> sharedFolders_;
	CIconButton presetButton_;
	CString computerName_;
public:
	LRESULT OnBnClickedBrowsebutton(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnPresetButtonClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBnClickedAddfileprotocol(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};


