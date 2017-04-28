//---------------------------------------------------------------------------

#ifndef untConfigH
#define untConfigH

#include "_forward_declarations.h"

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmConfig:public TForm
{
__published:    // IDE-managed Components
    TGroupBox*                  grpConnection;
    TLabel*                     lblServer;
    TLabel*                     lblDatabase;
    TLabel*                     lblUsername;
    TLabel*                     lblSqlPipe;
    TEdit*                      edtHost;
    TEdit*                      edtDatabase;
    TEdit*                      edtUsername;
    TEdit*                      edtSqlPipe;
    TLabel*                     Label1;
    TEdit*                      edtName;
    TLabel*                     lblOK;
    TLabel*                     lblCancel;
    TLabel*                     Label2;
    TLabel*                     Label3;
    TLabel*                     Label4;
    void __fastcall             FormCloseQuery(TObject* Sender, bool& CanClose);
    void __fastcall             edtNameChange(TObject* Sender);
    void __fastcall             lblOKClick(TObject* Sender);
    void __fastcall             lblCancelClick(TObject* Sender);
    void __fastcall             FormKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
    void __fastcall             edtNameKeyPress(TObject* Sender, char& Key);
private:    // User declarations
public:     // User declarations
    __fastcall                  TfrmConfig(TComponent* Owner);

    void                        WriteTo(CConfiguration* p_pConf);
    void                        ReadFrom(CConfiguration* p_pConf);

    bool                        fOK;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConfig*  frmConfig;
//---------------------------------------------------------------------------
#endif
