//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#include "_includes.h"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain*   frmMain;
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner):
    TForm(Owner)
{
    g_pMySQL = new CMySQL;
    m_fAppReady = false;
    m_iEnableLevel = EL_DISCONNECTED;
    m_fBusy = false;

    RefreshConnections();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject* Sender)
{
    Caption = APPNAME + " - Main";
    Application->Title = APPNAME;
    LoadSettings();
    SetEnableLevel(EL_DISCONNECTED);
    tmrIdle->OnTimer(this);
    m_fAppReady = true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::SetConfiguration(AnsiString p_strConfiguration)
{
    m_pConfiguration.LoadName(p_strConfiguration);

    if (m_pConfiguration.GetRememberPassword())
    {
        edtPassword->Text = m_pConfiguration.GetPassword();
    }
    else
    {
        edtPassword->Text = "";
    }
    chkSavePassword->Checked = m_pConfiguration.GetRememberPassword();
    chkReverse->Checked = m_pConfiguration.GetReverseList();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::SetBusy(bool p_fBusy)
{
    m_fBusy = p_fBusy;
    ConstrainUI();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMain::lblConnectClick(TObject* Sender)
{
    g_pMySQL->EnablePipe(m_pConfiguration.GetSQLPipe(), chkIEProxy->Checked);

    SaveSettings();

    EnableGuiObject(lblConnect, false);
    if (g_pMySQL->IsConnected() == false)
    {
        SetStatus("Attempting to connect...");
        SetBusy(true);
        g_pMySQL->Connect(m_pConfiguration.GetHost(), m_pConfiguration.GetUsername(), edtPassword->Text, m_pConfiguration.GetDatabase());
        if (g_pMySQL->IsConnected() == false)
        {
            Application->MessageBox(g_pMySQL->GetLastError().c_str(), "Could not connect: ", MB_OK | MB_ICONERROR);
        }
    }
    else
    {
        SetBusy(true);
        g_pMySQL->Disconnect();
    }
    if (g_pMySQL->IsConnected())
    {
        SetStatus("Connected.");
        OnConnect();
        if (!g_pMySQL->IsConnected())
        {
            SetStatus("Disconnected.");
            OnDisconnect();
        }
    }
    else
    {
        SetStatus("Disconnected.");
        OnDisconnect();
    }
    SetBusy(false);

    EnableGuiObject(lblConnect, true);
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
void TfrmMain::LoadSettings()
{
    CIniFile*   iniFile = new CIniFile;

    iniFile->LoadFile(INI_FILE);

    chkIEProxy->Checked = (iniFile->GetItem(INI_GENERAL_GROUP, INI_GENERAL_IEPROXY) == "1");
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::SaveSettings()
{
    CIniFile*   iniFile = new CIniFile;

    iniFile->LoadFile(INI_FILE);
    iniFile->AddGroup(INI_GENERAL_GROUP);
    iniFile->AddItem(INI_GENERAL_GROUP, INI_GENERAL_LASTCONNECTION, cbxConfigurations->Text);
    iniFile->AddItem(INI_GENERAL_GROUP, INI_GENERAL_IEPROXY, (chkIEProxy->Checked ? "1" : "0"));
    iniFile->SaveFile(INI_FILE);

    m_pConfiguration.SetReverseList(chkReverse->Checked);
    m_pConfiguration.Save();

    delete iniFile;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::EnableGuiObject(TLabel* p_pLabel, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;

    if (p_fEnable)
    {
        p_pLabel->Enabled = true;
        if (p_pLabel->Tag == 1)
        {
            TFontStyles pFntNew;
            pFntNew << fsUnderline;
            p_pLabel->Font->Style = pFntNew;
        }
    }
    else
    {
        p_pLabel->Enabled = false;
        if (p_pLabel->Tag == 1)
        {
            TFontStyles pFntNew;
            pFntNew >> fsUnderline;
            p_pLabel->Font->Style = pFntNew;
        }
    }
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::EnableGuiObject(TCheckBox* p_pCheckBox, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    if (p_fEnable)
    {
        p_pCheckBox->Enabled = true;
        p_pCheckBox->Font->Color = clNavy;
        p_pCheckBox->Font->Style >> fsUnderline;
        TFontStyles pFntNew;
        pFntNew << fsUnderline;
        p_pCheckBox->Font->Style = pFntNew;
    }
    else
    {
        p_pCheckBox->Enabled = false;
        p_pCheckBox->Font->Color = clGray;
        TFontStyles pFntNew;
        pFntNew >> fsUnderline;
        p_pCheckBox->Font->Style = pFntNew;
    }
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::EnableGuiObject(TEdit* p_pEditBox, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pEditBox->Enabled = p_fEnable;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::EnableGuiObject(TComboBox* p_pComboBox, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pComboBox->Enabled = p_fEnable;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::EnableGuiObject(TListBox* p_pListBox, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pListBox->Enabled = p_fEnable;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::EnableGuiObject(TGroupBox* p_pGroupBox, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pGroupBox->Enabled = p_fEnable;
    if (p_fEnable)
    {
        p_pGroupBox->Font->Color = clBlack;
    }
    else
    {
        p_pGroupBox->Font->Color = clGray;
    }
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject* Sender)
{
    SaveSettings();
    if (g_pMySQL != NULL)
    {
        g_pMySQL->Disconnect();

        delete g_pMySQL;
        g_pMySQL = NULL;
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMain::OnServerKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
    if (Key == VK_RETURN)
    {
        if (g_pMySQL->IsConnected() == false)
        {
            lblConnectClick(this);
        }
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::SetStatus(AnsiString p_strStatus)
{
    stbMain->SimpleText = p_strStatus;
    tmrIdle->Enabled = false;
    tmrIdle->Enabled = true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::OnConnect()
{
    lblConnect->Caption = "Disconnect";
    lblTypeRefresh->OnClick(this);
    ConstrainUI();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::OnDisconnect()
{
    lblConnect->Caption = "Connect";
    ConstrainUI();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMain::lblTypeRefreshClick(TObject* Sender)
{
    SetStatus("Performing content type refresh...");
    cbxContentTypes->Clear();
    SetBusy(true);
    CMySQLResult*   resQuery    = g_pMySQL->Query("SHOW TABLES");
    SetBusy(false);
    if (resQuery)
    {
        int iRows   = resQuery->GetResult_Rows();
        int iSigLen = CONTENT_TABLE_SIGNATURE.Length();
        for (int i = 0; i < iRows; ++i)
        {
            AnsiString  strTable        = resQuery->GetResult_Text(i, 0);
            AnsiString  strShortTable   = strTable.SubString(iSigLen + 1, strTable.Length() - iSigLen);

            if (strTable.SubString(0, CONTENT_TABLE_SIGNATURE.Length()) == CONTENT_TABLE_SIGNATURE)
            {
                cbxContentTypes->Items->Add(strShortTable);
            }
        }
        g_pMySQL->FreeResult(resQuery);
    }
    SetStatus("Content type refresh complete.");
    ConstrainUI();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::SetEnableLevel(int p_iEnableLevel)
{
    bool    fGroup1 = false;
    bool    fGroup2 = false;
    bool    fGroup3 = false;
    bool    fGroup4 = false;

    m_iEnableLevel = p_iEnableLevel;

    switch (p_iEnableLevel)
    {
    case EL_DISCONNECTED:
        fGroup1 = true;
        break;

    case EL_CONNECTED:
        fGroup2 = true;
        break;

    case EL_GOTTYPE:
        fGroup2 = true;
        fGroup3 = true;
        break;

    case EL_GOTPAGE:
        fGroup2 = true;
        fGroup3 = true;
        fGroup4 = true;
        break;
    }

    EnableGuiObject(lblPassword, fGroup1);
    EnableGuiObject(edtPassword, fGroup1);
    EnableGuiObject(chkSavePassword, fGroup1);
    EnableGuiObject(chkIEProxy, fGroup1);
    EnableGuiObject(lblQuit, fGroup1);
    EnableGuiObject(lblEditMenu, !fGroup1);
    EnableGuiObject(lblDirectSQL, !fGroup1);
    EnableGuiObject(lblUpdateTables, !fGroup1);
    EnableGuiObject(grpMaintainance, !fGroup1);
    EnableGuiObject(lblComment1, fGroup1);

    EnableGuiObject(lblConnNew, fGroup1);
    EnableGuiObject(lblConnModify, fGroup1);
    EnableGuiObject(lblConnDelete, fGroup1);
    EnableGuiObject(cbxConfigurations, fGroup1);

    EnableGuiObject(grpType, fGroup2);
    EnableGuiObject(lblType, fGroup2);
    EnableGuiObject(cbxContentTypes, fGroup2);
    EnableGuiObject(lblTypeCreateNew, fGroup2);
    EnableGuiObject(lblTypeRefresh, fGroup2);
    EnableGuiObject(lblComment2, fGroup2);
    EnableGuiObject(lblComment3, fGroup2);

    EnableGuiObject(chkReverse, fGroup3);
    EnableGuiObject(lblTypeDelete, fGroup3);
    EnableGuiObject(lblTypeRename, fGroup3);
    EnableGuiObject(grpPage, fGroup3);
    EnableGuiObject(lbxPages, fGroup3);
    EnableGuiObject(lblPageCreateNew, fGroup3);
    EnableGuiObject(lblPageRefresh, fGroup3);
    EnableGuiObject(lbxPages, fGroup3);
    EnableGuiObject(lblEditing, fGroup3);
    EnableGuiObject(lblEditing_Static, fGroup3);

    EnableGuiObject(lblPageDelete, fGroup4);
    EnableGuiObject(lblPageEdit, fGroup4);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cbxContentTypesChange(TObject* Sender)
{
    if (lblEditing->Caption == cbxContentTypes->Text)
    {
        return;
    }
    lblEditing->Caption = cbxContentTypes->Text;
    ConstrainUI();

    lblPageRefresh->OnClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lbxPagesClick(TObject* Sender)
{
    //HACK!

    ConstrainUI();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lblTypeCreateNewClick(TObject* Sender)
{
    AnsiString  strNewType;
    bool        fTryAgain   = false;
    do
    {
        bool    fOK = InputQuery("Create new content type", "Content type name:", strNewType);
        strNewType = strNewType.LowerCase();
        if (fOK)
        {
            if (strNewType == "")
            {
                Application->MessageBox("The content type name cannot be blank.\nTry another one.", "Error", MB_OK | MB_ICONERROR);
                fTryAgain = true;
                continue;
            }
            bool    fIsUnique   = true;
            int     iTotal      = cbxContentTypes->Items->Count;
            for (int i = 0; i < iTotal; ++i)
            {
                if (cbxContentTypes->Items->Strings[i].LowerCase() == strNewType.LowerCase())
                {
                    fIsUnique = false;
                    Application->MessageBox("That content type already exists.\nTry another one.", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
            }
            if (fIsUnique)
            {
                fTryAgain = false;
            }
            else
            {
                fTryAgain = true;
            }
            AnsiString  strTableName    = CMySQL::Escape("content_" + strNewType.LowerCase());
            SetStatus("Performing content type creation...");
            AnsiString  strQuery    = "CREATE TABLE `" + strTableName + "`     "
                                                          "(                                       "
                                                          "  `id` int(11) NOT NULL AUTO_INCREMENT, "
                                                          "  `title` varchar(255) NOT NULL,                "
                                                          "  `description` varchar(255) NOT NULL,  "
                                                          "  `keywords` varchar(255) NOT NULL,     "
                                                          "  `body` mediumtext NOT NULL,           "
                                                          "  `datetime` datetime NOT NULL,         "
                                                          "  `updated` datetime NOT NULL,          "
                                                          "  `style` int NOT NULL,                 "
                                                          "  `altname` varchar(255) NOT NULL,      "
                                                          "  `access` int NOT NULL default '0',    "
                                                          "  `hits` int NOT NULL default '0',      "
                                                          "  PRIMARY KEY (`id`),                   "
                                                          "  KEY `Index_altname`(`altname`),       "
                                                          "  KEY `Index_datetime`(`datetime`)      "
                                                          ") TYPE=InnoDB AUTO_INCREMENT=1          "
                                                          "CHARACTER SET utf8 COLLATE utf8_general_ci";
            SetBusy(true);
            CMySQLResult*   resQuery    = g_pMySQL->Query(strQuery);
            SetBusy(false);
            if (!resQuery)
            {
                SetStatus("Content type creation failed.");
                Application->MessageBox("Could not create the table for that content type.\nPlease try again.", "Error", MB_OK | MB_ICONERROR);
                fTryAgain = true;
                continue;
            }
            else
            {
                SetStatus("Content type creation succeeded.");
                Application->MessageBox("The table has been created successfully.", "Success", MB_OK | MB_ICONINFORMATION);
                g_pMySQL->FreeResult(resQuery);
                fTryAgain = false;
                lblTypeRefresh->OnClick(this);
                cbxContentTypes->ItemIndex = cbxContentTypes->Items->IndexOf(strNewType);
                ConstrainUI();
                cbxContentTypes->OnChange(this);
                ConstrainUI();
            }
        }
        else
        {
            fTryAgain = false;
        }
    }
    while (fTryAgain == true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tmrIdleTimer(TObject* Sender)
{
    AnsiString  strConnected    = "Disconnected";
    if (g_pMySQL->IsConnected())
    {
        strConnected = "Connected";
    }
    SetStatus("Idle (" + strConnected + ")");
    tmrIdle->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lblTypeDeleteClick(TObject* Sender)
{
    AnsiString  strContentType  = cbxContentTypes->Text;
    if (strContentType == "")
    {
        return;
    }

    int iResult = Application->MessageBox(("Are you sure you want to delete\n"
                                          "The content type \"" + strContentType + "\"?").c_str(), "Delete content type", MB_YESNO | MB_ICONQUESTION);
    if (iResult == IDYES)
    {
        SetStatus("Deleting content type...");
        AnsiString  strTableName    = "content_" + strContentType;
        AnsiString  strQuery        = "DROP TABLE `" + CMySQL::Escape(strTableName + "`");
        SetBusy(true);
        CMySQLResult*   resQuery    = g_pMySQL->Query(strQuery);
        SetBusy(false);
        if (resQuery)
        {
            SetStatus("Content type deletion succeeded.");
            Application->MessageBox("The table has been deleted successfully.", "Success", MB_OK | MB_ICONINFORMATION);
            g_pMySQL->FreeResult(resQuery);
            lblTypeRefresh->OnClick(this);
            ConstrainUI();
        }
        else
        {
            SetStatus("Content type deletion failed.");
            Application->MessageBox("An error occured deleting the table.\nPlease try again.", "Error", MB_OK | MB_ICONINFORMATION);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lblTypeRenameClick(TObject* Sender)
{
    AnsiString  strNewType;
    bool        fTryAgain   = false;
    do
    {
        AnsiString  strOldType  = cbxContentTypes->Text;
        bool        fOK         = InputQuery("Rename content type \"" + strOldType + "\"", "New content type name:", strNewType);
        strNewType = strNewType.LowerCase();
        if (fOK)
        {
            if (strNewType == "")
            {
                Application->MessageBox("The content type name cannot be blank.\nTry another one.", "Error", MB_OK | MB_ICONERROR);
                fTryAgain = true;
                continue;
            }
            if (strNewType == strOldType)
            {
                Application->MessageBox("The new name cannot be the same as the old name.\nTry another one.", "Error", MB_OK | MB_ICONERROR);
                fTryAgain = true;
                continue;
            }
            bool    fIsUnique   = true;
            int     iTotal      = cbxContentTypes->Items->Count;
            for (int i = 0; i < iTotal; ++i)
            {
                if (cbxContentTypes->Items->Strings[i].LowerCase() == strNewType.LowerCase())
                {
                    fIsUnique = false;
                    Application->MessageBox("That content type already exists.\nTry another one.", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
            }
            if (fIsUnique)
            {
                fTryAgain = false;
            }
            else
            {
                fTryAgain = true;
            }
            AnsiString  strOldTableName = "content_" + strOldType.LowerCase();
            AnsiString  strNewTableName = "content_" + strNewType.LowerCase();
            SetStatus("Renaming content type...");
            AnsiString  strQuery    = "ALTER TABLE `" + CMySQL::Escape(strOldTableName) + "` \n"
                                                          "RENAME `" + CMySQL::Escape(strNewTableName) + "`      \n";
            SetBusy(true);
            CMySQLResult*   resQuery    = g_pMySQL->Query(strQuery);
            SetBusy(false);
            if (!resQuery)
            {
                SetStatus("Content type rename failed.");
                Application->MessageBox("Could not rename the table for that content type.\nPlease try again.", "Error", MB_OK | MB_ICONERROR);
                fTryAgain = true;
                continue;
            }
            else
            {
                SetStatus("Content type renamed successfully.");
                Application->MessageBox("The table has been renamed successfully.", "Success", MB_OK | MB_ICONINFORMATION);
                g_pMySQL->FreeResult(resQuery);
                fTryAgain = false;
                lblTypeRefresh->OnClick(this);
                cbxContentTypes->ItemIndex = cbxContentTypes->Items->IndexOf(strNewType);
                cbxContentTypes->OnChange(this);
                ConstrainUI();
            }
        }
        else
        {
            fTryAgain = false;
        }
    }
    while (fTryAgain == true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lblPageRefreshClick(TObject* Sender)
{
    if (!m_fAppReady)
    {
        return;
    }
    AnsiString  strTableName    = CONTENT_TABLE_SIGNATURE + cbxContentTypes->Text;
    AnsiString  strSortOrder;
    if (chkReverse->Checked)
    {
        strSortOrder = "ORDER BY `id` DESC";
    }
    else
    {
        strSortOrder = "ORDER BY `id`";
    }
    AnsiString  strQuery    = "SELECT `id`, `title` FROM `" + strTableName + "`" + strSortOrder;

    SetBusy(true);
    SetStatus("Refreshing page list...");
    CMySQLResult*   resQuery    = g_pMySQL->Query(strQuery);
    SetBusy(false);
    if (resQuery)
    {
        lbxPages->Items->Clear();
        int     iRows   = resQuery->GetResult_Rows();
        char*   szLine;
        for (int i = 0; i < iRows; ++i)
        {
            int         szID        = resQuery->GetResult_Text(i, 0).ToInt();
            AnsiString  strTitle    = resQuery->GetResult_Text(i, 1);
            szLine = new char[strTitle.Length() + 64];

            sprintf(szLine, "%05d: %s", szID, strTitle.c_str());
            lbxPages->Items->Add(szLine);

            delete[] szLine;
        }
        g_pMySQL->FreeResult(resQuery);
        SetStatus("Page list refreshed.");
    }
    else
    {
        Application->MessageBox("Could not refresh page list.", "Error", MB_OK | MB_ICONERROR);
        SetStatus("Page list refresh failed.");
    }


    ConstrainUI();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::ConstrainUI()
{
    bool    fClearTypes = false;
    bool    fClearPages = false;

    if (g_pMySQL->IsConnected())
    {
        if (cbxContentTypes->ItemIndex >= 0)
        {
            if (lbxPages->ItemIndex >= 0)
            {
                SetEnableLevel(EL_GOTPAGE);
            }
            else
            {
                SetEnableLevel(EL_GOTTYPE);
            }
        }
        else
        {
            fClearPages = true;
            SetEnableLevel(EL_CONNECTED);
        }
    }
    else
    {
        SetEnableLevel(EL_DISCONNECTED);
        fClearPages = true;
        fClearTypes = true;
    }

    if (fClearPages)
    {
        lbxPages->Items->Clear();
        lbxPages->ItemIndex = -1;
        lblEditing->Caption = "None";
    }

    if (fClearTypes)
    {
        cbxContentTypes->Items->Clear();
        cbxContentTypes->ItemIndex = -1;
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::lblPageCreateNewClick(TObject* Sender)
{
    SetBusy(true);
    TfrmPageEdit*   frmPageEditor   = new TfrmPageEdit(this);
    frmPageEditor->ShowModal_CreateNew(cbxContentTypes->Text);
    SetStatus("Waiting for page editor to close...");
    bool    fAffectedTable  = frmPageEditor->GetAffectedTable();
    delete frmPageEditor;
    SetBusy(false);

    if (fAffectedTable)
    {
        lblPageRefresh->OnClick(this);
    }
    else
    {
        SetStatus("Creation of new page cancelled.");
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lblPageEditClick(TObject* Sender)
{
    if (lbxPages->ItemIndex == -1)
    {
        return;
    }

    AnsiString  strCurrent  = lbxPages->Items->Strings[lbxPages->ItemIndex];
    int         iID         = strCurrent.SubString(1, 5).ToInt();

    SetBusy(true);
    SetStatus("Loading page...");
    TfrmPageEdit*   frmPageEditor   = new TfrmPageEdit(this);
    frmPageEditor->ShowModal_Edit(cbxContentTypes->Text, iID);
    SetStatus("Waiting for page editor to close...");
    bool    fAffectedTable  = frmPageEditor->GetAffectedTable();
    delete frmPageEditor;
    SetBusy(false);

    if (fAffectedTable)
    {
        lblPageRefresh->OnClick(this);
    }
    else
    {
        SetStatus("Edit cancelled.");
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lbxPagesDblClick(TObject* Sender)
{
    lblPageEditClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::chkReverseClick(TObject* Sender)
{
    if (chkReverse->Enabled == true)
    {
        lblPageRefresh->OnClick(this);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lblPageDeleteClick(TObject* Sender)
{
    if (lbxPages->ItemIndex == -1)
    {
        return;
    }

    if (Application->MessageBox("Are you sure you want to delete this page?", "Confirm", MB_YESNO | MB_ICONQUESTION) == IDNO)
    {
        return;
    }

    bool        fAffectedTable  = false;

    AnsiString  strCurrent      = lbxPages->Items->Strings[lbxPages->ItemIndex];
    AnsiString  strTable        = CONTENT_TABLE_SIGNATURE + cbxContentTypes->Text;

    int         iID             = strCurrent.SubString(1, 5).ToInt();
    AnsiString  strID           = IntToStr(iID);

    AnsiString  strQuery        = "DELETE from `" + strTable + "` WHERE `id` = '" + strID + "'";



    SetBusy(true);
    SetStatus("Deleting page ...");
    CMySQLResult*   resQuery    = g_pMySQL->Query(strQuery);
    SetBusy(false);
    if (resQuery)
    {
        fAffectedTable = true;
        SetStatus("Page deleted.");
        g_pMySQL->FreeResult(resQuery);
    }
    else
    {
        SetStatus("Failed deleting page.");
        Application->MessageBox("Could not delete entry.", "Error", MB_OK | MB_ICONERROR);
    }

    if (fAffectedTable)
    {
        lblPageRefresh->OnClick(this);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lblEditMenuClick(TObject* Sender)
{
    SetBusy(true);
    SetStatus("Loading menu...");
    TfrmMenuEdit*   frmMenuEditor   = new TfrmMenuEdit(this);

    if (frmMenuEditor->GetAllowShow())
    {
        SetStatus("Ready to edit menu.");
        frmMenuEditor->ShowModal();
    }

    delete frmMenuEditor;
    tmrIdle->OnTimer(this);
    SetBusy(false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lblQuitClick(TObject* Sender)
{
    Close();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMain::RefreshConnections()
{
    static bool fIsFirstRefresh = true;

    CIniFile*   iniFile         = new CIniFile;
    iniFile->LoadFile(INI_FILE);

    AnsiString  strLastConnection;
    if (fIsFirstRefresh)
    {
        strLastConnection = iniFile->GetItem(INI_GENERAL_GROUP, INI_GENERAL_LASTCONNECTION);
    }
    else
    {
        strLastConnection = m_pConfiguration.GetName();
    }

    SetConfiguration(strLastConnection);

    cbxConfigurations->Clear();

    int             iFound  = 0;
    WIN32_FIND_DATA Found;  //file finding data
    HANDLE          SearchHandle;  //handle for next search
    ZeroMemory(&Found, sizeof(WIN32_FIND_DATA));     //clear the memory of the FindData struct
    SearchHandle = FindFirstFile("conf*.ini", &Found);   //find first entry
    if (SearchHandle != INVALID_HANDLE_VALUE)    //if valid handle found
    {
        int SearchAgain = 1;    //flag if we must search again (init to true)
        while (SearchAgain)  //repeat until findnextfile returns false (no more files)
        {
            CIniFile*   ini = new CIniFile;
            ini->LoadFile(Found.cFileName);
            cbxConfigurations->Items->Add(ini->GetItem(INI_CONNECTION_GROUP, INI_CONNECTION_NAME));
            ZeroMemory(&Found, sizeof(WIN32_FIND_DATA));     //clear the memory of the FindData struct
            SearchAgain = FindNextFile(SearchHandle, &Found);   //find first entry
            ++iFound;
            delete ini;
        }
        FindClose(SearchHandle);  //close the serch session
    }

    if (iFound == 0)
    {
        TfrmConfig* form    = new TfrmConfig(this);
        form->lblCancel->Visible = false;
        form->ShowModal();
        form->WriteTo(&m_pConfiguration);
        cbxConfigurations->Items->Add(m_pConfiguration.GetName());
        cbxConfigurations->ItemIndex = 0;
        delete form;
    }

    fIsFirstRefresh = false;

    delete iniFile;

    int iIndex  = -1;
    iIndex = cbxConfigurations->Items->IndexOf(m_pConfiguration.GetName());

    if (iIndex >= 0)
    {
        cbxConfigurations->ItemIndex = iIndex;
    }
    else
    {
        cbxConfigurations->ItemIndex = 0;
        SetConfiguration(cbxConfigurations->Text);
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::lblConnNewClick(TObject* Sender)
{
    TfrmConfig* form    = new TfrmConfig(this);
    form->ShowModal();
    if (form->fOK)
    {
        edtPassword->Text = "";
        chkSavePassword->Checked = false;
        form->WriteTo(&m_pConfiguration);
        RefreshConnections();
    }
    delete form;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::lblConnModifyClick(TObject* Sender)
{
    TfrmConfig* form    = new TfrmConfig(this);
    form->ReadFrom(&m_pConfiguration);
    AnsiString  strFilename1    = m_pConfiguration.GetFilename();
    form->ShowModal();
    if (form->fOK)
    {
        form->WriteTo(&m_pConfiguration);
        AnsiString  strFilename2    = m_pConfiguration.GetFilename();
        if (strFilename1 != strFilename2)
        {
            DeleteFile(strFilename1);
        }
        RefreshConnections();
    }
    delete form;
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::cbxConfigurationsSelect(TObject* Sender)
{
    SetConfiguration(cbxConfigurations->Text);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lblConnDeleteClick(TObject* Sender)
{
    if (Application->MessageBox("Are you sure?", "Delete configuration", MB_YESNO) == IDYES)
    {
        AnsiString  strFilename = m_pConfiguration.GetFilename();
        DeleteFile(strFilename);
        RefreshConnections();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::chkSavePasswordClick(TObject* Sender)
{
    m_pConfiguration.SetRememberPassword(chkSavePassword->Checked);
    if (!chkSavePassword->Checked)
    {
        m_pConfiguration.SetPassword("");
    }
    else
    {
        m_pConfiguration.SetPassword(edtPassword->Text);
    }
    SaveConfiguration();
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
void TfrmMain::SaveConfiguration()
{
    m_pConfiguration.Save();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::edtPasswordChange(TObject* Sender)
{
    if (m_pConfiguration.GetRememberPassword())
    {
        m_pConfiguration.SetPassword(edtPassword->Text);
    }
    else
    {
        m_pConfiguration.SetPassword("");
    }
    SaveConfiguration();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormShow(TObject* Sender)
{
    edtPassword->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lblDirectSQLClick(TObject *Sender)
{
    frmDirectSQL->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lblUpdateTablesClick(TObject *Sender)
{
    SetBusy(true);

    int iUpdated = 0;
    CMySQLResult* resQuery1 = g_pMySQL->Query("SHOW TABLES LIKE \"content_%\"");
    if (resQuery1)
    {
        int iRows = resQuery1->GetResult_Rows();
        CMySQLResult* resQuery2;
        for (int iRow = 0; iRow < iRows; ++iRow)
        {
            resQuery2 = g_pMySQL->Query(
                "ALTER TABLE `" + resQuery1->GetResult_Text(iRow, 0) + "` "
                "  CHANGE `id` `id` int(11) NOT NULL AUTO_INCREMENT, "
                "  CHANGE `title` `title` varchar(255) NOT NULL,                "
                "  CHANGE `description` `description` varchar(255) NOT NULL,  "
                "  CHANGE `keywords` `keywords` varchar(255) NOT NULL,     "
                "  CHANGE `body` `body` mediumtext NOT NULL,           "
                "  CHANGE `datetime` `datetime` datetime NOT NULL,         "
                "  CHANGE `updated` `updated` datetime NOT NULL,          "
                "  CHANGE `style` `style` int NOT NULL,                 "
                "  CHANGE `altname` `altname` varchar(255) NOT NULL,      "
                "  CHANGE `access` `access` int NOT NULL default '0',    "
                "  CHANGE `hits` `hits` int NOT NULL default '0',      "
                "  ENGINE=InnoDB AUTO_INCREMENT=1,          "
                "  CHARACTER SET utf8 COLLATE utf8_general_ci");


            if (resQuery2)
            {
                ++iUpdated;
                g_pMySQL->FreeResult(resQuery2);
                resQuery2 = NULL;
            }
            else
            {
                Application->MessageBox(("Error: ALTER TABLE `" + resQuery1->GetResult_Text(iRow, 0) + "`").c_str(), "Error", MB_ICONERROR);
            }
        }
        g_pMySQL->FreeResult(resQuery1);
        Application->MessageBox(("Updated " + IntToStr(iUpdated) + " tables.").c_str(), "Success", MB_ICONINFORMATION);
    }
    else
    {
        Application->MessageBox("Error: SHOW TABLES", "Error", MB_ICONERROR);
    }


    SetBusy(false);
}
//---------------------------------------------------------------------------

