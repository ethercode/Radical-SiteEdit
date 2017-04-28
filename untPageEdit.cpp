#pragma link "SciScintilla"
#pragma link "SciScintillaBase"
#pragma link "SciScintillaMemo"

//---------------------------------------------------------------------------
#include "_includes.h"
#include <sys\stat.h>
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

static const char* base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";


long FileSize(char* filename)
{
  struct stat stbuf;
  stat(filename, &stbuf);
  return stbuf.st_size;
}

AnsiString base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{
  AnsiString ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}


//---------------------------------------------------------------------------
__fastcall TfrmPageEdit::TfrmPageEdit(TComponent* Owner):
    TForm(Owner)
{
    m_fEdit = false;
    m_iID = -1;
    m_fBusy = true;
    m_strTableName = "";
    m_fUnsaved = false;
    m_fAffectedTable = false;
    m_fClosingByLink = false;
    m_fPermitClose = false;
    m_fExitNow = false;
    m_fLoaded = false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmPageEdit::FormCreate(TObject* Sender)
{
    Caption = APPNAME + " - Page Editor";
    SetBusy(false);
    LoadComboBox(cbxAccess, "AccessTypes");
    LoadComboBox(cbxStyle, "PageStyles");
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmPageEdit::ShowModal_CreateNew(AnsiString p_strShortTable)
{
    m_fEdit = false;
    lblContentType->Caption = p_strShortTable;
    m_strTableName = CONTENT_TABLE_SIGNATURE + p_strShortTable;
    ShowModal();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmPageEdit::ShowModal_Edit(AnsiString p_strShortTable, int p_iID)
{
    m_fEdit = true;
    m_iID = p_iID;
    lblContentType->Caption = p_strShortTable;
    m_strTableName = CONTENT_TABLE_SIGNATURE + p_strShortTable;

    AnsiString      strQuery    = "SELECT "
                                 "`title`,`description`,`keywords`,`body`, "
                                 "`datetime`,`style`,`altname`,`access` FROM `" + m_strTableName + "` "
                                 "WHERE `id` = '" + IntToStr(p_iID) + "'";

    CMySQLResult*   resQuery    = g_pMySQL->Query(strQuery);
    if (resQuery)
    {
        edtTitle->Text = resQuery->GetResult_Text(0, 0);
        edtDescription->Text = resQuery->GetResult_Text(0, 1);
        edtKeywords->Text = resQuery->GetResult_Text(0, 2);
        mmoBody->Lines->Text = resQuery->GetResult_Text(0, 3);
        edtDateTime->Text = resQuery->GetResult_Text(0, 4);
        cbxStyle->ItemIndex = resQuery->GetResult_Text(0, 5).ToInt();
        edtAltName->Text = resQuery->GetResult_Text(0, 6);
        cbxAccess->ItemIndex = resQuery->GetResult_Text(0, 7).ToInt();
        g_pMySQL->FreeResult(resQuery);
        mmoBody->EmptyUndoBuffer();
        SetUnsaved(false);
        m_fLoaded = true;
        ShowModal();
    }
    else
    {
        Application->MessageBox("Could not open page for editing.", "Error", MB_OK | MB_ICONERROR);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::lblApplyClick(TObject* Sender)
{
    if (DoSubmission())
    {
        m_fEdit = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::lblOKClick(TObject* Sender)
{
    m_fClosingByLink = true;
    if (DoSubmission())
    {
        m_fPermitClose = true;
        Close();
    }
    m_fClosingByLink = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::lblCancelClick(TObject* Sender)
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
void TfrmPageEdit::EnableGuiObject(TLabel* p_pLabel, bool p_fEnable)
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
void TfrmPageEdit::EnableGuiObject(TCheckBox* p_pCheckBox, bool p_fEnable)
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
void TfrmPageEdit::EnableGuiObject(TEdit* p_pEditBox, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pEditBox->Enabled = p_fEnable;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmPageEdit::EnableGuiObject(TComboBox* p_pComboBox, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pComboBox->Enabled = p_fEnable;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmPageEdit::EnableGuiObject(TMemo* p_pMemo, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pMemo->Enabled = p_fEnable;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmPageEdit::EnableGuiObject(TScintilla* p_pMemo, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pMemo->ReadOnly = m_fBusy;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmPageEdit::EnableGuiObject(TListBox* p_pListBox, bool p_fEnable)
{
    p_fEnable = m_fBusy ? false : p_fEnable;
    p_pListBox->Enabled = p_fEnable;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmPageEdit::EnableGuiObject(TGroupBox* p_pGroupBox, bool p_fEnable)
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
void TfrmPageEdit::SetStatus(AnsiString p_strStatus)
{
    stbMain->SimpleText = p_strStatus;
    tmrIdle->Enabled = false;
    tmrIdle->Enabled = true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmPageEdit::SetBusy(bool p_fBusy)
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

    bool    fEnable         = !p_fBusy;
    bool    fApplyEnabled   = false;
    if (fEnable && m_fUnsaved)
    {
        fApplyEnabled = true;
    }

    EnableGuiObject(grpBody, fEnable);
    EnableGuiObject(grpAttributes, fEnable);
    EnableGuiObject(mmoBody, fEnable);
    EnableGuiObject(edtTitle, fEnable);
    EnableGuiObject(lblTitle, fEnable);
    EnableGuiObject(edtDescription, fEnable);
    EnableGuiObject(lblDescription, fEnable);
    EnableGuiObject(edtKeywords, fEnable);
    EnableGuiObject(lblKeywords, fEnable);
    EnableGuiObject(edtAltName, fEnable);
    EnableGuiObject(lblAltName, fEnable);
    EnableGuiObject(edtDateTime, fEnable);
    EnableGuiObject(lblDateTime, fEnable);
    EnableGuiObject(cbxStyle, fEnable);
    EnableGuiObject(lblStyle, fEnable);
    EnableGuiObject(cbxAccess, fEnable);
    EnableGuiObject(lblAccess, fEnable);
    EnableGuiObject(lblUpdate, fEnable);
    EnableGuiObject(lblOK, fEnable);
    EnableGuiObject(lblCancel, fEnable);
    EnableGuiObject(chkWordWrap, fEnable);
    EnableGuiObject(lblApply, fApplyEnabled);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::tmrIdleTimer(TObject* Sender)
{
    SetStatus("Idle.");
    tmrIdle->Enabled = false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
bool TfrmPageEdit::DoSubmission()
{
    bool    fSuccess    = true;
    if (!m_fUnsaved)
    {
        return true;
    }

    AnsiString  strQuery;
    if (m_fEdit == false)
    {
        AnsiString  strAccess   = IntToStr(cbxAccess->ItemIndex);
        AnsiString  strStyle    = IntToStr(cbxStyle->ItemIndex);
        strQuery = "INSERT INTO `" + m_strTableName + "` "
        "(`id`,`title`,`description`,`keywords`,`body`, "
        "`datetime`,`updated`, `style`,`altname`,`access` ) "
        "VALUES "
        "("
        "\'\', "
        "\'" + CMySQL::Escape(edtTitle->Text) + "', "
        "\'" + CMySQL::Escape(edtDescription->Text) + "\', "
        "\'" + CMySQL::Escape(edtKeywords->Text) + "\', "
        "\'" + CMySQL::Escape(mmoBody->Lines->Text) + "\', "
        "\'" + CMySQL::Escape(edtDateTime->Text) + "\', "
        "\'" + GetCurrentTimeString() + "\', "
        "\'" + CMySQL::Escape(strStyle) + "\', "
        "\'" + CMySQL::Escape(edtAltName->Text) + "\', "
        "\'" + CMySQL::Escape(strAccess) + "\' "
        ")";
        //
    }
    else
    {
        if (m_iID == -1)  //we dont know the id of the next record
        {
            SetBusy(true);
            AnsiString  strQuery2   = "SELECT `id` from `" + m_strTableName + "`"
                                                           "ORDER BY `id` DESC";

            SetStatus("Determining next id for page...");
            CMySQLResult*   resQuery2   = g_pMySQL->Query(strQuery2);
            SetBusy(false);

            if (resQuery2)
            {
                m_iID = resQuery2->GetResult_Text(0, 0).ToInt();
                g_pMySQL->FreeResult(resQuery2);
            }
            else
            {
                Application->MessageBox("Could not determine id of the next record", "Error", MB_OK | MB_ICONERROR);
                return false;
            }
        }
        strQuery = "UPDATE `" + m_strTableName + "` SET "
        "`title` = \'" + CMySQL::Escape(edtTitle->Text) + "', "
        "`description` = \'" + CMySQL::Escape(edtDescription->Text) + "\', "
        "`keywords` = \'" + CMySQL::Escape(edtKeywords->Text) + "\', "
        "`body` = \'" + CMySQL::Escape(mmoBody->Lines->Text) + "\', "
        "`datetime` = \'" + CMySQL::Escape(edtDateTime->Text) + "\', "
        "`updated` = \'" + GetCurrentTimeString() + "\', "
        "`style` = \'" + CMySQL::Escape(IntToStr(cbxStyle->ItemIndex)) + "\', "
        "`altname` = \'" + CMySQL::Escape(edtAltName->Text) + "\', "
        "`access` = \'" + CMySQL::Escape(IntToStr(cbxAccess->ItemIndex)) + "\' "
        "WHERE `id` = '" + IntToStr(m_iID) + "'";
    }

    SetBusy(true);
    SetStatus("Performing submission...");
    CMySQLResult*   resQuery    = g_pMySQL->Query(strQuery);
    SetBusy(false);
    if (resQuery)
    {
        g_pMySQL->FreeResult(resQuery);
        SetUnsaved(false);
        m_fAffectedTable = true;
        SetStatus("Submission succeeded.");
    }
    else
    {
        Application->MessageBox("The submission failed.\nPlease try again.", "Error", MB_OK | MB_ICONERROR);
        SetStatus("Submission failed.");
        fSuccess = false;
    }

    return fSuccess;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmPageEdit::edtTitleChange(TObject* Sender)
{
    SetUnsaved(true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::edtDescriptionChange(TObject* Sender)
{
    SetUnsaved(true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::edtKeywordsChange(TObject* Sender)
{
    SetUnsaved(true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::edtAltNameChange(TObject* Sender)
{
    SetUnsaved(true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::edtStyleChange(TObject* Sender)
{
    SetUnsaved(true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::cbxAccessChange(TObject* Sender)
{
    SetUnsaved(true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::edtDateTimeChange(TObject* Sender)
{
    SetUnsaved(true);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmPageEdit::SetUnsaved(bool p_fUnsaved)
{
    m_fUnsaved = p_fUnsaved;
    EnableGuiObject(lblApply, p_fUnsaved);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
bool TfrmPageEdit::GetAffectedTable()
{
    return m_fAffectedTable;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmPageEdit::FormClose(TObject* Sender, TCloseAction& Action)
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
AnsiString TfrmPageEdit::GetCurrentTimeString()
{
    AnsiString  szDate;
    TDateTime   cDate   = Date();  // store the current date and time
    TDateTime   cTime   = Time();  // store the current date and time

    szDate = cDate.FormatString("yyyy-MM-dd ") + cTime.FormatString("hh:nn:ss");
    return szDate;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmPageEdit::UpdateDateTime()
{
    edtDateTime->Text = GetCurrentTimeString();
}
//---------------------------------------------------------------------------


void __fastcall TfrmPageEdit::lblUpdateClick(TObject* Sender)
{
    UpdateDateTime();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::edtDateTimeDblClick(TObject* Sender)
{
    UpdateDateTime();
}
//---------------------------------------------------------------------------


void __fastcall TfrmPageEdit::edtDateTimeKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
    if (Key == 13)
    {
        UpdateDateTime();
        cbxStyle->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::edtTitleKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
    if (Key == 13)
    {
        edtDescription->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::edtDescriptionKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
    if (Key == 13)
    {
        edtKeywords->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::edtKeywordsKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
    if (Key == 13)
    {
        edtAltName->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::edtAltNameKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
    if (Key == 13)
    {
        edtDateTime->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::edtStyleKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
    if (Key == 13)
    {
        cbxAccess->SetFocus();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::cbxAccessKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
    if (Key == 13)
    {
        mmoBody->SetFocus();
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmPageEdit::chkWordWrapClick(TObject* Sender)
{
    mmoBody->WordWrap = chkWordWrap->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if ( (Shift.Contains(ssCtrl)) && (Key == 'S') && (lblApply->Enabled == true) )
        {
                lblApply->OnClick(this);
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPageEdit::mmoBodyModified(TObject *Sender,
      const int position, const int modificationType, PChar text,
      const int len, const int linesAdded, const int line,
      const int foldLevelNow, const int foldLevelPrev)
{
    if (m_fLoaded)
    {
        if ( (modificationType & SC_MOD_INSERTTEXT) ||
             (modificationType & SC_MOD_DELETETEXT) ||
             (modificationType & SC_PERFORMED_UNDO) ||
             (modificationType & SC_PERFORMED_REDO) )
        {
           SetUnsaved(true);
        }
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmPageEdit::mmoBodyKeyPress(TObject *Sender, char &Key)
{
    if (Key == ('S' - 'A' + 1)) Key = 0;
}
//---------------------------------------------------------------------------


void __fastcall TfrmPageEdit::lblBinaryClick(TObject *Sender)
{
    if (opnBinary->Execute())
    {
        int sz = FileSize(opnBinary->FileName.c_str());
        FILE* f = fopen(opnBinary->FileName.c_str(), "rb");
        if (f)
        {
            if (sz > 0)
            {
                char* dat = new char[sz];
                fread(dat, sz, 1, f);
                fclose(f);
                AnsiString s = base64_encode(dat, sz);
                mmoBody->Lines->Text = s;
                mmoBody->WordWrap = true;
            }
        }

    }
}
//---------------------------------------------------------------------------

