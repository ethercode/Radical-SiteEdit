//---------------------------------------------------------------------------
#include "_includes.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmDirectSQL *frmDirectSQL;
//---------------------------------------------------------------------------
__fastcall TfrmDirectSQL::TfrmDirectSQL(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmDirectSQL::btnExecuteClick(TObject *Sender)
{
    CMySQLResult* resQuery = NULL;
    resQuery = g_pMySQL->Query(mmoQuery->Lines->Text);
    if (resQuery == NULL)
    {
        Application->MessageBox("Query failed.", "Error", MB_ICONERROR);
    }
    else
    {
        if (resQuery->GetResult_Rows() > 0)
        {
            sgResp->ColCount = 1;
            sgResp->RowCount = 1;
            sgResp->ColCount = 2;
            sgResp->RowCount = 2;
            sgResp->FixedCols = 1;
            sgResp->FixedRows = 1;

            sgResp->ColCount = resQuery->GetResult_Fields() + 1;
            sgResp->RowCount = resQuery->GetResult_Rows() + 1;

            for (int c = 0; c < sgResp->ColCount; ++c)
            {
                sgResp->Cells[c + 1][0] = resQuery->GetResult_FieldName(c);
                for (int r = 0; r < sgResp->RowCount; ++r)
                {
                    sgResp->Cells[c + 1][r + 1] = resQuery->GetResult_Text(r,c);
                }
            }
        }
        else
        {
            sgResp->ColCount = 2;
            sgResp->RowCount = 2;
            sgResp->Cells[1][1] = "No result.";
        }
        g_pMySQL->FreeResult(resQuery);
    }


}
//---------------------------------------------------------------------------

void __fastcall TfrmDirectSQL::btnClearClick(TObject *Sender)
{
    sgResp->ColCount = 1;
    sgResp->RowCount = 1;
    mmoQuery->Clear();
}
//---------------------------------------------------------------------------

