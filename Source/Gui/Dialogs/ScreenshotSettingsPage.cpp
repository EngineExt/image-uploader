/*

    Image Uploader -  free application for uploading images/files to the Internet

    Copyright 2007-2015 Sergey Svistunov (zenden2k@gmail.com)

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

*/

#include "atlheaders.h"
#include "ScreenshotSettingsPage.h"
#include "Func/Common.h"
#include "LogWindow.h"
#include "Func/Settings.h"
#include "Gui/GuiTools.h"

#define CheckBounds(n,a,b,d) {if((n<a) || (n>b)) n=d;}

// CScreenshotSettingsPagePage
CScreenshotSettingsPagePage::CScreenshotSettingsPagePage()
{

}

CScreenshotSettingsPagePage::~CScreenshotSettingsPagePage()
{
}

LRESULT CScreenshotSettingsPagePage::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	TRC(IDC_GROUPPARAMS, "�������������");
	TRC(IDC_QUALITYLABEL, "��������:");
	TRC(IDC_DELAYLABEL, "��������:");
	TRC(IDC_FORMATLABEL, "������:");
	TRC(IDC_SECLABEL, "���");
	TRC(IDC_MSECLABEL, "��");
	TRC(IDC_SCREENSHOTSFOLDERSELECT, "�����");
	TRC(IDC_SCREENSHOTFOLDERLABEL, "����� ��� ���������� ����������:");
	TRC(IDC_SCREENSHOTFILENAMELABEL, "������ ����� �����");
	TRC(IDC_DELAYLABEL2, "�������� ��� ������� ����:");
	TRC(IDC_ALWAYSCOPYTOCLIPBOARD, "������ ���������� � ����� ������");
	TRC(IDC_SCREENSHOTSAVINGPARAMS, "��������� ���������� �������");
	TRC(IDC_FOREGROUNDWHENSHOOTING, "�������� ���� �� �������� ���� ��� ������ �����");
	TRC(IDC_PARAMETERSHINTLABEL, "%y - ���, %m - �����, %d - ����\n%h - ���, %n - ������, %s - �������\n %i - ���������� �����,\n%width% - ������,  %height% - ������ �����������");
	TRC(IDC_ADDSHADOW, "��������� ���� ����");
	CString removeCornersText = TR("������� ������ � ����")+CString(_T(" (Windows Vista/7)"));
	SetDlgItemText(IDC_REMOVECORNERS, removeCornersText);
	TRC(IDC_REMOVEBACKGROUND, "������� ��� ����");
	TRC(IDC_SHORTENURLFROMTRAYCHECKBOX, "��������� ������ ��� ������� �������� (�� ������� �������)");
	TRC(IDC_AEROONLY, "������ ��� Aero (Windows Vista � �����)");
	TRC(IDC_USEOLDREGIONSCREENSHOTMETHOD, "������������ ������ ������ ������ ������� ������");
	
	SetDlgItemText(IDC_SCREENSHOTFILENAMEEDIT, Settings.ScreenshotSettings.FilenameTemplate);

	SetDlgItemText(IDC_SCREENSHOTFOLDEREDIT, Settings.ScreenshotSettings.Folder);
	SendDlgItemMessage(IDC_DELAYSPIN, UDM_SETRANGE, 0, (LPARAM) MAKELONG((short)30, (short)0) );
	SendDlgItemMessage(IDC_QUALITYSPIN, UDM_SETRANGE, 0, (LPARAM) MAKELONG((short)100, (short)1) );
	
	SendDlgItemMessage(IDC_FORMATLIST, CB_ADDSTRING, 0, (LPARAM)_T("JPEG"));
	SendDlgItemMessage(IDC_FORMATLIST, CB_ADDSTRING, 0, (LPARAM)_T("PNG"));
	SendDlgItemMessage(IDC_FOREGROUNDWHENSHOOTING, BM_SETCHECK,Settings.ScreenshotSettings.ShowForeground);
	SendDlgItemMessage(IDC_ALWAYSCOPYTOCLIPBOARD, BM_SETCHECK, Settings.ScreenshotSettings.CopyToClipboard);

	SendDlgItemMessage(IDC_REMOVECORNERS, BM_SETCHECK, Settings.ScreenshotSettings.RemoveCorners);
	SendDlgItemMessage(IDC_ADDSHADOW, BM_SETCHECK, Settings.ScreenshotSettings.AddShadow);
	SendDlgItemMessage(IDC_REMOVEBACKGROUND, BM_SETCHECK, Settings.ScreenshotSettings.RemoveBackground);

	GuiTools::SetCheck(m_hWnd, IDC_SHORTENURLFROMTRAYCHECKBOX, Settings.TrayIconSettings.ShortenLinks);
	GuiTools::SetCheck(m_hWnd, IDC_USEOLDREGIONSCREENSHOTMETHOD, Settings.ScreenshotSettings.UseOldRegionScreenshotMethod);

	int Quality, Delay, Format;
	Quality = Settings.ScreenshotSettings.Quality;
	Format = Settings.ScreenshotSettings.Format;
	Delay = Settings.ScreenshotSettings.Delay;

	if( Format < 0) Format = 0;
	if( Quality < 0) Quality = 85;
	if( Delay < 0 || Delay > 30) Delay = 2;

	SetDlgItemInt(IDC_QUALITYEDIT, Quality);
	SetDlgItemInt(IDC_DELAYEDIT, Delay);
	SetDlgItemInt(IDC_WINDOWHIDINGDELAY, Settings.ScreenshotSettings.WindowHidingDelay);
	SendDlgItemMessage(IDC_FORMATLIST, CB_SETCURSEL, Format, 0);

	bool isVista = IsVista();
	::EnableWindow(GetDlgItem(IDC_AEROONLY), isVista);
	::EnableWindow(GetDlgItem(IDC_REMOVECORNERS), isVista);
	::EnableWindow(GetDlgItem(IDC_ADDSHADOW), isVista);
	::EnableWindow(GetDlgItem(IDC_REMOVEBACKGROUND), isVista);
	return 1;  // Let the system set the focus
}

bool CScreenshotSettingsPagePage::Apply()
{
	CString fileName = GuiTools::GetWindowText(GetDlgItem(IDC_SCREENSHOTFILENAMEEDIT));
	if(!CheckFileName(fileName))
	{
		MessageBox(TR("��� ����� �������� ����������� �������!"));
		::SetFocus(GetDlgItem(IDC_SCREENSHOTFILENAMEEDIT));
		return false;
	}
	Settings.ScreenshotSettings.FilenameTemplate = fileName;
	
	Settings.ScreenshotSettings.Format = SendDlgItemMessage(IDC_FORMATLIST,CB_GETCURSEL,0,0);
	Settings.ScreenshotSettings.Quality = GetDlgItemInt(IDC_QUALITYEDIT);
	Settings.ScreenshotSettings.Delay = GetDlgItemInt(IDC_DELAYEDIT);
	Settings.ScreenshotSettings.ShowForeground = SendDlgItemMessage(IDC_FOREGROUNDWHENSHOOTING, BM_GETCHECK) == BST_CHECKED;

	Settings.ScreenshotSettings.Folder = GuiTools::GetWindowText(GetDlgItem(IDC_SCREENSHOTFOLDEREDIT));
	Settings.ScreenshotSettings.Format = SendDlgItemMessage(IDC_FORMATLIST,CB_GETCURSEL,0,0);
	Settings.ScreenshotSettings.Quality = GetDlgItemInt(IDC_QUALITYEDIT);
	Settings.ScreenshotSettings.Delay = GetDlgItemInt(IDC_DELAYEDIT);
	Settings.ScreenshotSettings.ShowForeground = SendDlgItemMessage(IDC_FOREGROUNDWHENSHOOTING, BM_GETCHECK) == BST_CHECKED;
	Settings.ScreenshotSettings.CopyToClipboard =  SendDlgItemMessage(IDC_ALWAYSCOPYTOCLIPBOARD, BM_GETCHECK) == BST_CHECKED;
	
	Settings.ScreenshotSettings.WindowHidingDelay = GetDlgItemInt(IDC_WINDOWHIDINGDELAY);

	Settings.ScreenshotSettings.RemoveCorners = SendDlgItemMessage(IDC_REMOVECORNERS, BM_GETCHECK)!=0;
	Settings.ScreenshotSettings.AddShadow = SendDlgItemMessage(IDC_ADDSHADOW, BM_GETCHECK)!=0;
	Settings.ScreenshotSettings.RemoveBackground = SendDlgItemMessage(IDC_REMOVEBACKGROUND, BM_GETCHECK)!=0;
	Settings.ScreenshotSettings.UseOldRegionScreenshotMethod = GuiTools::GetCheck(m_hWnd, IDC_USEOLDREGIONSCREENSHOTMETHOD );


	 Settings.TrayIconSettings.ShortenLinks = GuiTools::GetCheck(m_hWnd, IDC_SHORTENURLFROMTRAYCHECKBOX);

	return true;
}

LRESULT CScreenshotSettingsPagePage::OnScreenshotsFolderSelect(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CFolderDialog fd(m_hWnd,TR("����� �����"), BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE );
	CString path = GuiTools::GetWindowText(GetDlgItem(IDC_SCREENSHOTFOLDEREDIT));
	fd.SetInitialFolder(path,true);
	if(fd.DoModal(m_hWnd) == IDOK)
	{
		SetDlgItemText(IDC_SCREENSHOTFOLDEREDIT,fd.GetFolderPath());
		return true;
	}
	return 0;
}
