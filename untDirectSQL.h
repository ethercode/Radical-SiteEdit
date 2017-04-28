//---------------------------------------------------------------------------

#ifndef untDirectSQLH
#define untDirectSQLH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include "SciScintilla.hpp"
#include "SciScintillaBase.hpp"
#include "SciScintillaMemo.hpp"
//---------------------------------------------------------------------------
class TfrmDirectSQL : public TForm
{
__published:	// IDE-managed Components
    TStringGrid *sgResp;
    TButton *btnExecute;
    TButton *btnClear;
    TScintilla *mmoQuery;
    void __fastcall btnExecuteClick(TObject *Sender);
    void __fastcall btnClearClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmDirectSQL(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDirectSQL *frmDirectSQL;
//---------------------------------------------------------------------------
#endif
