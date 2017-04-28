//---------------------------------------------------------------------------
#ifndef untMainH
#define untMainH
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------


#include "CConfiguration.h"

//---------------------------------------------------------------------------
class TfrmMain:public TForm
{
__published:    // IDE-managed Components
    TLabel*                         lblQuit;
    TGroupBox*                      grpConnection;
    TGroupBox*                      grpPage;
    TLabel*                         lblPageCreateNew;
    TLabel*                         lblPageEdit;
    TLabel*                         lblPageDelete;
    TLabel*                         lblPageRefresh;
    TListBox*                       lbxPages;
    TCheckBox*                      chkReverse;
    TGroupBox*                      grpMaintainance;
    TLabel*                         lblEditMenu;
    TGroupBox*                      grpType;
    TLabel*                         lblType;
    TLabel*                         lblTypeCreateNew;
    TLabel*                         lblTypeRename;
    TLabel*                         lblTypeDelete;
    TLabel*                         lblTypeRefresh;
    TComboBox*                      cbxContentTypes;
    TLabel*                         Label1;
    TStatusBar*                     stbMain;
    TTimer*                         tmrIdle;
    TLabel*                         lblEditing_Static;
    TLabel*                         lblEditing;
    TLabel*                         lblPassword;
    TLabel*                         lblConnect;
    TEdit*                          edtPassword;
    TCheckBox*                      chkSavePassword;
    TLabel*                         Label2;
    TComboBox*                      cbxConfigurations;
    TLabel*                         lblConnNew;
    TLabel*                         lblConnModify;
    TLabel*                         lblConnDelete;
    TCheckBox*                      chkIEProxy;
    TLabel*                         lblComment1;
    TLabel*                         lblComment2;
    TLabel*                         lblComment3;
    TLabel *lblDirectSQL;
    TLabel *lblUpdateTables;
    void __fastcall                 FormCreate(TObject* Sender);
    void __fastcall                 lblConnectClick(TObject* Sender);
    void __fastcall                 FormDestroy(TObject* Sender);
    void __fastcall                 OnServerKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
    void __fastcall                 lblTypeRefreshClick(TObject* Sender);
    void __fastcall                 cbxContentTypesChange(TObject* Sender);
    void __fastcall                 lbxPagesClick(TObject* Sender);
    void __fastcall                 lblTypeCreateNewClick(TObject* Sender);
    void __fastcall                 tmrIdleTimer(TObject* Sender);
    void __fastcall                 lblTypeDeleteClick(TObject* Sender);
    void __fastcall                 lblTypeRenameClick(TObject* Sender);
    void __fastcall                 lblPageRefreshClick(TObject* Sender);
    void __fastcall                 lblPageCreateNewClick(TObject* Sender);
    void __fastcall                 lblPageEditClick(TObject* Sender);
    void __fastcall                 lbxPagesDblClick(TObject* Sender);
    void __fastcall                 chkReverseClick(TObject* Sender);
    void __fastcall                 lblPageDeleteClick(TObject* Sender);
    void __fastcall                 lblEditMenuClick(TObject* Sender);
    void __fastcall                 lblQuitClick(TObject* Sender);
    void __fastcall                 lblConnNewClick(TObject* Sender);
    void __fastcall                 lblConnModifyClick(TObject* Sender);
    void __fastcall                 cbxConfigurationsSelect(TObject* Sender);
    void __fastcall                 lblConnDeleteClick(TObject* Sender);
    void __fastcall                 chkSavePasswordClick(TObject* Sender);
    void __fastcall                 edtPasswordChange(TObject* Sender);
    void __fastcall                 FormShow(TObject* Sender);
    void __fastcall lblDirectSQLClick(TObject *Sender);
    void __fastcall lblUpdateTablesClick(TObject *Sender);

private:    // User declarations
    int                             m_iEnableLevel;
    bool                            m_fBusy;
    bool                            m_fAppReady;
    CConfiguration                  m_pConfiguration;

public:     // User declarations
    __fastcall                      TfrmMain(TComponent* Owner);

    static __stdcall unsigned long  AnimThread(void*);
    void                            LoadSettings();
    void                            SaveSettings();

    void                            EnableGuiObject(TLabel* p_pLabel, bool p_fEnable);
    void                            EnableGuiObject(TCheckBox* p_pCheckBox, bool p_fEnable);
    void                            EnableGuiObject(TEdit* p_pEdit, bool p_fEnable);
    void                            EnableGuiObject(TComboBox* p_pComboBox, bool p_fEnable);
    void                            EnableGuiObject(TListBox* p_pListBox, bool p_fEnable);
    void                            EnableGuiObject(TGroupBox* p_pGroupBox, bool p_fEnable);

    void                            SetStatus(AnsiString p_strStatus);

    void                            OnConnect();
    void                            OnDisconnect();

    void                            SetEnableLevel(int p_iEnableLevel);
    void                            ConstrainUI();

    void                            SetBusy(bool p_fBusy);

    void                            SetConfiguration(AnsiString p_strConfiguration);
    void                            SaveConfiguration();


    void                            RefreshConnections();
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
extern PACKAGE TfrmMain*        frmMain;
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

