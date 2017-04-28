//---------------------------------------------------------------------------

#include "_includes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmConfig* frmConfig;
//---------------------------------------------------------------------------
__fastcall TfrmConfig::TfrmConfig(TComponent* Owner):
    TForm(Owner)
{
    fOK = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::FormCloseQuery(TObject* Sender, bool& CanClose)
{
    CanClose = (edtName->Text != "") | (lblCancel->Visible);
    if (!CanClose)
    {
        Application->MessageBox("You have to have at least one connection, with a name.", "Error", MB_OK);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::edtNameChange(TObject* Sender)
{
    lblOK->Enabled = (edtName->Text != "");
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::lblOKClick(TObject* Sender)
{
    fOK = true;
    Close();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmConfig::WriteTo(CConfiguration* p_pConf)
{
    p_pConf->SetName(edtName->Text);
    p_pConf->SetHost(edtHost->Text);
    p_pConf->SetUsername(edtUsername->Text);
    p_pConf->SetDatabase(edtDatabase->Text);
    p_pConf->SetSQLPipe(edtSqlPipe->Text);
    p_pConf->Save();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TfrmConfig::ReadFrom(CConfiguration* p_pConf)
{
    edtName->Text = p_pConf->GetName();
    edtHost->Text = p_pConf->GetHost();
    edtUsername->Text = p_pConf->GetUsername();
    edtDatabase->Text = p_pConf->GetDatabase();
    edtSqlPipe->Text = p_pConf->GetSQLPipe();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::lblCancelClick(TObject* Sender)
{
    fOK = false;
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::FormKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
    if (Key == 27)
    {
        fOK = false;
        Close();
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmConfig::edtNameKeyPress(TObject* Sender, char& Key)
{
    if (Key == '<')
    {
        Key = 0;
    }
    if (Key == '>')
    {
        Key = 0;
    }
    if (Key == '/')
    {
        Key = 0;
    }
    if (Key == '\\')
    {
        Key = 0;
    }
    if (Key == '?')
    {
        Key = 0;
    }
    if (Key == ':')
    {
        Key = 0;
    }
    if (Key == '|')
    {
        Key = 0;
    }
    if (Key == '*')
    {
        Key = 0;
    }
    if (Key == '"')
    {
        Key = 0;
    }
}
//---------------------------------------------------------------------------

