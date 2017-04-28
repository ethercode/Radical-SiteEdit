//---------------------------------------------------------------------------
#include "_includes.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
__fastcall TfrmMenuEdit::TfrmMenuEdit(TComponent* Owner):
    TForm(Owner)
{
    for (int i = 0; i < MAX_MENU_ITEMS; ++i)
    {
        m_pMenuItems[i] = NULL;
    }
    m_fUnsaved = false;
    m_fAllowShow = false;
    m_fEditing = false;
    m_pItemEdited = NULL;
    m_fPermitClose = false;
    m_fClosingByLink = false;
    m_fExitNow = false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::FormCreate(TObject* Sender)
{
    Caption = APPNAME + " - Menu Editor";

    LoadComboBox(cbxStyle, "MenuStyles");
    LoadComboBox(cbxAccess, "AccessTypes");

    Refresh();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::EnableGuiObject(TLabel* p_pLabel, bool p_fEnable)
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
void TfrmMenuEdit::EnableGuiObject(TCheckBox* p_pCheckBox, bool p_fEnable)
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
void TfrmMenuEdit::EnableGuiObject(TEdit* p_pEditBox, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pEditBox->Enabled = p_fEnable;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::EnableGuiObject(TComboBox* p_pComboBox, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pComboBox->Enabled = p_fEnable;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::EnableGuiObject(TMemo* p_pMemo, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pMemo->Enabled = p_fEnable;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::EnableGuiObject(TListBox* p_pListBox, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pListBox->Enabled = p_fEnable;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::EnableGuiObject(TGroupBox* p_pGroupBox, bool p_fEnable)
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
void TfrmMenuEdit::SetStatus(AnsiString p_strStatus)
{
    stbMain->SimpleText = p_strStatus;
    tmrIdle->Enabled = false;
    tmrIdle->Enabled = true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::SetBusy(bool p_fBusy)
{
    if (m_fBusy == p_fBusy)
    {
        return;
    }
    m_fBusy = p_fBusy;

    if (!m_fBusy)
    {
        SetStatus("Idle.");
    }

    ConstrainUI();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::tmrIdleTimer(TObject* Sender)
{
    SetStatus("Idle.");
    tmrIdle->Enabled = false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::FreeMenuItems()
{
    for (int i = 0; i < MAX_MENU_ITEMS; ++i)
    {
        if (m_pMenuItems[i] != NULL)
        {
            delete m_pMenuItems[i];
            m_pMenuItems[i] = NULL;
        }
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::Refresh()
{
    AnsiString  strQuery    = "SELECT "
                                 "`id`, `order`, `text`, `url`, `style`, `access` "
                                 "from `menu` ORDER BY `order`";
    SetBusy(true);
    SetStatus("Getting list of menu items...");
    CMySQLResult*   resQuery    = g_pMySQL->Query(strQuery);
    SetBusy(false);
    if (resQuery)
    {
        lbxItems->Items->Clear();
        FreeMenuItems();
        int iRows   = resQuery->GetResult_Rows();
        for (int i = 0; i < iRows; ++i)
        {
            m_pMenuItems[i] = new CMenuItem;
            m_pMenuItems[i]->SetID(resQuery->GetResult_Text(i, 0).ToInt());
            m_pMenuItems[i]->SetOrder(resQuery->GetResult_Text(i, 1).ToInt());
            m_pMenuItems[i]->SetText(resQuery->GetResult_Text(i, 2));
            m_pMenuItems[i]->SetURL(resQuery->GetResult_Text(i, 3));
            m_pMenuItems[i]->SetStyle(resQuery->GetResult_Text(i, 4).ToInt());
            m_pMenuItems[i]->SetAccess(resQuery->GetResult_Text(i, 5).ToInt());
            m_pMenuItems[i]->SetNew(false);
            m_pMenuItems[i]->SetChanged(false);
            m_pMenuItems[i]->SetCommitted(true);
            lbxItems->Items->Add(m_pMenuItems[i]->GetText());
        }

        SetStatus("Menu item list refreshed.");
        m_fAllowShow = true;
        g_pMySQL->FreeResult(resQuery);
    }
    else
    {
        SetStatus("Menu table does not exist.");
        int iResult = Application->MessageBox("Could not find menu table.\nCreate one?", "Create new menu table", MB_YESNO | MB_ICONQUESTION);

        if (iResult == IDYES)
        {
            strQuery = "CREATE TABLE `menu` (   "
            "`id` INT NOT NULL ,     "
            "`order` INT NOT NULL , "
            "`text` TEXT NOT NULL ,  "
            "`url` TEXT NOT NULL ,   "
            "`style` INT NOT NULL , "
            "`access` INT NOT NULL   "
            ");                      ";
            SetBusy(true);
            SetStatus("Creating new menu table...");
            resQuery = g_pMySQL->Query(strQuery);
            SetBusy(false);
            if (resQuery)
            {
                g_pMySQL->FreeResult(resQuery);
                SetStatus("New menu table created.");
                lbxItems->Items->Clear();
                m_fAllowShow = true;
            }
            else
            {
                Application->MessageBox("Could not create the menu table.", "Error", MB_OK | MB_ICONERROR);
                m_fExitNow = true;
                Close();
            }
        }
        else
        {
            m_fExitNow = true;
            Close();
        }
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
bool TfrmMenuEdit::GetAllowShow()
{
    return m_fAllowShow;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
int TfrmMenuEdit::GetSlot()
{
    for (int i = 0; i < MAX_MENU_ITEMS; ++i)
    {
        if (m_pMenuItems[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::FreeSlot(int p_iIndex)
{
    if (p_iIndex >= 0 && p_iIndex < MAX_MENU_ITEMS)
    {
        if (m_pMenuItems[p_iIndex] != NULL)
        {
            delete m_pMenuItems[p_iIndex];
            m_pMenuItems[p_iIndex] = NULL;
        }
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::lblNewClick(TObject* Sender)
{
    int iNewIndex   = GetSlot();
    int iNewID      = GetUnusedID();
    if (iNewIndex == -1)
    {
        return;
    }

    m_pMenuItems[iNewIndex] = new CMenuItem;
    CMenuItem*  pItem   = m_pMenuItems[iNewIndex];

    pItem->SetID(iNewID);
    pItem->SetOrder(iNewIndex);
    pItem->SetText("[Unnamed]");
    pItem->SetURL("");
    pItem->SetStyle(0);
    pItem->SetAccess(0);
    pItem->SetNew(true);
    pItem->SetCommitted(false);

    lbxItems->Items->Add(pItem->GetText());

    lbxItems->ItemIndex = pItem->GetOrder();
    int iCount  = lbxItems->Items->Count;
    for (int i = 0; i < iCount; ++i)
    {
        if (i == pItem->GetOrder())
        {
            lbxItems->Selected[i] = true;
        }
        else
        {
            lbxItems->Selected[i] = false;
        }
    }
    m_fUnsaved = true;
    ConstrainUI();
    lbxItems->OnClick(this);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
int TfrmMenuEdit::GetUnusedID()
{
    int     i;

    bool    faUsageTable[MAX_MENU_ITEMS];
    for (i = 0; i < MAX_MENU_ITEMS; ++i)
    {
        faUsageTable[i] = false;
    }

    for (i = 0; i < MAX_MENU_ITEMS; ++i)
    {
        if (m_pMenuItems[i] != NULL)
        {
            faUsageTable[m_pMenuItems[i]->GetID()] = true;
        }
    }

    for (i = 0; i < MAX_MENU_ITEMS; ++i)
    {
        if (faUsageTable[i] == false)
        {
            return i;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::lblDeleteClick(TObject* Sender)
{
    int iTotal  = lbxItems->Items->Count;
    int i;
    for (i = iTotal - 1; i >= 0; --i)
    {
        if (lbxItems->Selected[i])
        {
            m_fUnsaved = true;
            if (m_pMenuItems[i]->GetCommitted())
            {
                m_queDeletes.push(m_pMenuItems[i]->GetID());
            }
            delete m_pMenuItems[i];
            for (int j = i; j < iTotal - 1; ++j)
            {
                m_pMenuItems[j] = m_pMenuItems[j + 1];
            }
            m_pMenuItems[iTotal - 1] = NULL;
            lbxItems->Items->Delete(i);
        }
    }
    ConstrainUI();
    lbxItems->OnClick(this);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::lblMoveUpClick(TObject* Sender)
{
    int iUpper, iLower, i;
    GetSelectRange(iLower, iUpper);
    if (iLower <= 0)
    {
        return;
    }

    int     iCount          = lbxItems->Items->Count;
    bool*   faOrigSelected  = new bool[iCount];

    for (i = 0; i < iCount; ++i)
    {
        faOrigSelected[i] = lbxItems->Selected[i];
    }
    for (i = iLower; i <= iUpper; ++i)
    {
        if (faOrigSelected[i])
        {
            SwapItems(i, i - 1);
        }
    }

    delete[] faOrigSelected;
    m_fUnsaved = true;
    ConstrainUI();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::lblMoveDownClick(TObject* Sender)
{
    int iUpper, iLower, i;

    GetSelectRange(iLower, iUpper);

    int iCount  = lbxItems->Items->Count;
    if (iUpper >= iCount - 1 || iUpper == -1)
    {
        return;
    }

    bool*   faOrigSelected  = new bool[iCount];

    for (i = 0; i < iCount; ++i)
    {
        faOrigSelected[i] = lbxItems->Selected[i];
    }
    for (i = iUpper; i >= iLower; --i)
    {
        if (faOrigSelected[i])
        {
            SwapItems(i, i + 1);
        }
    }

    delete[] faOrigSelected;
    m_fUnsaved = true;
    ConstrainUI();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::GetSelectRange(int& p_iLowest, int& p_iHighest)
{
    int iCount  = lbxItems->Items->Count;
    if (iCount == 0)
    {
        p_iLowest = -1;
        p_iHighest = -1;
        return;
    }
    else
    {
        p_iLowest = iCount;
        p_iHighest = 0;
    }
    for (int i = 0; i < lbxItems->Items->Count; ++i)
    {
        if (lbxItems->Selected[i])
        {
            if (i < p_iLowest)
            {
                p_iLowest = i;
            }
            if (i > p_iHighest)
            {
                p_iHighest = i;
            }
        }
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::SwapItems(int p_iFirst, int p_iSecond)
{
    bool        fSelected1  = lbxItems->Selected[p_iFirst];
    bool        fSelected2  = lbxItems->Selected[p_iSecond];
    int         iCount      = lbxItems->Items->Count;
    int         i;

    AnsiString  strText1    = lbxItems->Items->Strings[p_iFirst];
    AnsiString  strText2    = lbxItems->Items->Strings[p_iSecond];
    lbxItems->Selected[p_iFirst] = fSelected2;
    lbxItems->Selected[p_iSecond] = fSelected1;

    bool*   faOrigSelected  = new bool[iCount];
    for (i = 0; i < iCount; ++i)
    {
        faOrigSelected[i] = lbxItems->Selected[i];
    }

    lbxItems->Items->Strings[p_iFirst] = strText2;
    lbxItems->Items->Strings[p_iSecond] = strText1;

    for (i = 0; i < iCount; ++i)
    {
        lbxItems->Selected[i] = faOrigSelected[i];
    }
    delete[] faOrigSelected;

    CMenuItem*  pTempItem   = m_pMenuItems[p_iFirst];
    m_pMenuItems[p_iFirst] = m_pMenuItems[p_iSecond];
    m_pMenuItems[p_iSecond] = pTempItem;
    m_pMenuItems[p_iFirst]->SetChanged(true);
    m_pMenuItems[p_iSecond]->SetChanged(true);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::lbxItemsKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
    if (Shift.Contains(ssAlt))
    {
        if (Key == VK_UP)
        {
            lblMoveUp->OnClick(this);
        }
        if (Key == VK_DOWN)
        {
            lblMoveDown->OnClick(this);
        }
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::SetEditing(bool p_fEditing)
{
    if (p_fEditing)
    {
        m_pItemEdited = GetCurrentItem();
    }
    else
    {
        m_pItemEdited = NULL;
    }
    if (m_fEditing != p_fEditing)
    {
        m_fEditing = p_fEditing;
        ConstrainUI();
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmMenuEdit::ConstrainUI()
{
    bool    fEnableEditing  = !m_fBusy;
    bool    fEnableGeneral  = !m_fBusy && !m_fEditing;
    if (lbxItems->Count == 0)
    {
        fEnableEditing = false;
    }
    int iLower, iUpper;
    GetSelectRange(iLower, iUpper);
    if (fEnableEditing && (!(iLower == iUpper) && (iLower != -1)))
    {
        fEnableEditing = false;
    }

    EnableGuiObject(grpOptions, fEnableGeneral);
    EnableGuiObject(grpMenuItems, fEnableGeneral);
    EnableGuiObject(lbxItems, fEnableGeneral);
    EnableGuiObject(lblNew, fEnableGeneral);
    EnableGuiObject(lblDelete, fEnableGeneral);
    EnableGuiObject(lblMoveUp, fEnableGeneral);
    EnableGuiObject(lblMoveDown, fEnableGeneral);
    EnableGuiObject(lblOK, fEnableGeneral);
    EnableGuiObject(lblCancel, fEnableGeneral);
    EnableGuiObject(lblApply, fEnableGeneral && m_fUnsaved);

    EnableGuiObject(grpProperties, fEnableEditing);
    EnableGuiObject(cbxAccess, fEnableEditing);
    EnableGuiObject(edtText, fEnableEditing);
    EnableGuiObject(edtURL, fEnableEditing);
    EnableGuiObject(cbxStyle, fEnableEditing);
    EnableGuiObject(lblAccess, fEnableEditing);
    EnableGuiObject(lblStyle, fEnableEditing);
    EnableGuiObject(lblText, fEnableEditing);
    EnableGuiObject(lblURL, fEnableEditing);

    EnableGuiObject(lblPropCancel, m_fEditing);
    EnableGuiObject(lblPropApply, m_fEditing);

    if (!m_fEditing)
    {
        m_fEditing = true;
        edtText->Clear();
        edtURL->Clear();
        cbxStyle->ItemIndex = 0;
        cbxAccess->ItemIndex = 0;
        m_fEditing = false;
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::edtTextChange(TObject* Sender)
{
    if (m_fEditing)
    {
        return;
    }
    SetEditing(true);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::edtURLChange(TObject* Sender)
{
    if (m_fEditing)
    {
        return;
    }
    SetEditing(true);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::cbxAccessChange(TObject* Sender)
{
    if (m_fEditing)
    {
        return;
    }
    SetEditing(true);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::lbxItemsClick(TObject* Sender)
{
    ConstrainUI();

    CMenuItem*  pItem   = GetCurrentItem();
    if (!pItem)
    {
        return;
    }

    m_fEditing = true;
    edtText->Text = pItem->GetText();
    edtURL->Text = pItem->GetURL();
    cbxStyle->ItemIndex = pItem->GetStyle();
    cbxAccess->ItemIndex = pItem->GetAccess();
    m_fEditing = false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::lblPropCancelClick(TObject* Sender)
{
    SetEditing(false);
    lbxItems->SetFocus();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::lblPropApplyClick(TObject* Sender)
{
    int iFocusedItem    = lbxItems->ItemIndex;
    m_pItemEdited->SetText(edtText->Text);
    m_pItemEdited->SetURL(edtURL->Text);
    m_pItemEdited->SetStyle(cbxStyle->ItemIndex);
    m_pItemEdited->SetAccess(cbxAccess->ItemIndex);
    lbxItems->Items->Strings[iFocusedItem] = m_pItemEdited->GetText();
    SetEditing(false);
    lbxItems->SetFocus();
    lbxItems->ItemIndex = iFocusedItem;
    lbxItems->Selected[iFocusedItem] = true;
    m_fUnsaved = true;
    ConstrainUI();
    lbxItems->OnClick(this);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
CMenuItem* TfrmMenuEdit::GetCurrentItem()
{
    bool    fEnableEditing  = !m_fBusy;
    if (lbxItems->Count == 0)
    {
        fEnableEditing = false;
    }
    int iLower, iUpper;
    GetSelectRange(iLower, iUpper);
    if (fEnableEditing && (!(iLower == iUpper) && (iLower != -1)))
    {
        fEnableEditing = false;
    }

    if (!fEnableEditing)
    {
        return NULL;
    }

    if (lbxItems->ItemIndex == -1)
    {
        return NULL;
    }
    return m_pMenuItems[lbxItems->ItemIndex];
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::lblCancelClick(TObject* Sender)
{
    if (m_fUnsaved)
    {
        int iResult = Application->MessageBox("Are you sure you want to cancel?\n"
                                             "There are unsaved changes.", "Warning", MB_YESNO | MB_ICONWARNING);
        if (iResult == IDNO)
        {
            return;
        }
        else
        {
            m_fExitNow = true;
        }
    }
    m_fPermitClose = true;
    Close();
    m_fClosingByLink = false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::FormClose(TObject* Sender, TCloseAction& Action)
{
    if (m_fExitNow)
    {
        Action = caFree;
        return;
    }

    m_fPermitClose = false;
    if (!m_fClosingByLink)
    {
        lblCancel->OnClick(this);
    }
    if (m_fPermitClose)
    {
        Action = caFree;
    }
    else
    {
        Action = caNone;
    }
    m_fPermitClose = false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
bool TfrmMenuEdit::Save()
{
    SetBusy(true);
    SetStatus("Applying menu changes...");

    AnsiString              strQuery;
    bool                    fFailed = false;
    std::queue<AnsiString>  queOperations;

    while (!m_queDeletes.empty())
    {
        int iDelete = m_queDeletes.front();
        m_queDeletes.pop();
        AnsiString  strOp   = "DELETE FROM `menu` WHERE `id` = '" + IntToStr(iDelete) + "' ";
        queOperations.push(strOp);
    }

    for (int i = 0; i < MAX_MENU_ITEMS; ++i)
    {
        if (m_pMenuItems[i] != NULL)
        {
            m_pMenuItems[i]->SetOrder(i);
            if (m_pMenuItems[i]->GetChanged() == true)
            {
                m_pMenuItems[i]->SetCommitted(true);
                if (m_pMenuItems[i]->GetNew())
                {
                    strQuery = "INSERT INTO `menu` "
                    "(`id`, `order`, `text`, `url`, `style`, `access`) "
                    "VALUES ("
                    "'" + CMySQL::Escape(IntToStr(m_pMenuItems[i]->GetID())) + "', "
                    "'" + CMySQL::Escape(IntToStr(m_pMenuItems[i]->GetOrder())) + "', "
                    "'" + CMySQL::Escape(m_pMenuItems[i]->GetText()) + "', "
                    "'" + CMySQL::Escape(m_pMenuItems[i]->GetURL()) + "', "
                    "'" + CMySQL::Escape(m_pMenuItems[i]->GetStyle()) + "', "
                    "'" + CMySQL::Escape(IntToStr(m_pMenuItems[i]->GetAccess())) + "' ) ; ";
                }
                else
                {
                    strQuery = "UPDATE `menu` "
                    "SET "
                    "`id` = '" + CMySQL::Escape(IntToStr(m_pMenuItems[i]->GetID())) + "', "
                    "`order` = '" + CMySQL::Escape(IntToStr(m_pMenuItems[i]->GetOrder())) + "', "
                    "`text` = '" + CMySQL::Escape(m_pMenuItems[i]->GetText()) + "', "
                    "`url` = '" + CMySQL::Escape(m_pMenuItems[i]->GetURL()) + "', "
                    "`style` = '" + CMySQL::Escape(m_pMenuItems[i]->GetStyle()) + "', "
                    "`access` = '" + CMySQL::Escape(IntToStr(m_pMenuItems[i]->GetAccess())) + "' "
                    "WHERE `id` = '" + CMySQL::Escape(IntToStr(m_pMenuItems[i]->GetID())) + "' ; ";
                }
                queOperations.push(strQuery);
                m_pMenuItems[i]->SetChanged(false);
            }
        }
    }

    int iOperations = queOperations.size();
    int iCurrentOp  = 0;

    while (!queOperations.empty())
    {
        strQuery = queOperations.front();
        queOperations.pop();
        char    szMessage[256];
        sprintf(szMessage, "Performing operations... %d%%", int((100 * iCurrentOp) / iOperations));
        ++iCurrentOp;
        SetStatus(szMessage);
        CMySQLResult*   resQuery    = g_pMySQL->Query(strQuery);
        if (resQuery)
        {
            g_pMySQL->FreeResult(resQuery);
        }
        else
        {
            fFailed = true;
            Application->MessageBox(g_pMySQL->GetLastError().c_str(), "", 0);
        }
    }


    if (fFailed)
    {
        Application->MessageBox("Failed to update menu.\nPlease try again.", "Error", MB_OK | MB_ICONERROR);
    }
    else
    {
        m_fUnsaved = false;
    }

    SetBusy(false);
    ConstrainUI();

    return !fFailed;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::lblApplyClick(TObject* Sender)
{
    Save();
    ConstrainUI();
    lbxItems->OnClick(this);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmMenuEdit::lblOKClick(TObject* Sender)
{
    if (Save())
    {
        m_fExitNow = true;
        m_fPermitClose = true;
        Close();
        m_fClosingByLink = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMenuEdit::cbxStyleChange(TObject* Sender)
{
    if (m_fEditing)
    {
        return;
    }
    SetEditing(true);
}
//---------------------------------------------------------------------------

