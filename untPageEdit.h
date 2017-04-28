//---------------------------------------------------------------------------
#ifndef untPageEditH
#define untPageEditH
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "SciScintilla.hpp"
#include "SciScintillaBase.hpp"
#include "SciScintillaMemo.hpp"
#include <Dialogs.hpp>

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class TfrmPageEdit:public TForm
{
__published:    // IDE-managed Components
        TPanel *Panel1;
        TLabel *lblApply;
        TLabel *lblOK;
        TLabel *lblCancel;
        TLabel *lblContentType_Static;
        TLabel *lblContentType;
        TGroupBox *grpBody;
        TCheckBox *chkWordWrap;
        TGroupBox *grpAttributes;
        TLabel *lblTitle;
        TLabel *lblDescription;
        TLabel *lblKeywords;
        TLabel *lblAltName;
        TLabel *lblDateTime;
        TLabel *lblUpdate;
        TLabel *lblAccess;
        TLabel *lblStyle;
        TEdit *edtTitle;
        TEdit *edtDescription;
        TEdit *edtKeywords;
        TEdit *edtAltName;
        TEdit *edtDateTime;
        TComboBox *cbxAccess;
        TComboBox *cbxStyle;
        TStatusBar *stbMain;
        TScintilla *mmoBody;
        TTimer *tmrIdle;
    TLabel *lblBinary;
    TOpenDialog *opnBinary;
    void __fastcall FormCreate(TObject* Sender);
    void __fastcall lblApplyClick(TObject* Sender);
    void __fastcall lblOKClick(TObject* Sender);
    void __fastcall lblCancelClick(TObject* Sender);
    void __fastcall tmrIdleTimer(TObject* Sender);
    void __fastcall edtTitleChange(TObject* Sender);
    void __fastcall edtDescriptionChange(TObject* Sender);
    void __fastcall edtKeywordsChange(TObject* Sender);
    void __fastcall edtAltNameChange(TObject* Sender);
    void __fastcall edtStyleChange(TObject* Sender);
    void __fastcall cbxAccessChange(TObject* Sender);
    void __fastcall edtDateTimeChange(TObject* Sender);
    void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
    void __fastcall lblUpdateClick(TObject* Sender);
    void __fastcall edtDateTimeDblClick(TObject* Sender);
    void __fastcall edtDateTimeKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
    void __fastcall edtTitleKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
    void __fastcall edtDescriptionKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
    void __fastcall edtKeywordsKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
    void __fastcall edtAltNameKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
    void __fastcall edtStyleKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
    void __fastcall cbxAccessKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
    void __fastcall chkWordWrapClick(TObject* Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall mmoBodyModified(TObject *Sender, const int position,
          const int modificationType, PChar text, const int len,
          const int linesAdded, const int line, const int foldLevelNow,
          const int foldLevelPrev);
    void __fastcall mmoBodyKeyPress(TObject *Sender, char &Key);
    void __fastcall lblBinaryClick(TObject *Sender);

private:    // User declarations
    bool            m_fEdit;
    int             m_iID;
    bool            m_fClosingByLink;
    bool            m_fPermitClose;
    bool            m_fBusy;
    AnsiString      m_strTableName;
    bool            m_fUnsaved;
    bool            m_fAffectedTable;
    bool            m_fExitNow;
    bool            m_fLoaded;


    void            EnableGuiObject(TLabel* p_pLabel, bool p_fEnable);
    void            EnableGuiObject(TCheckBox* p_pCheckBox, bool p_fEnable);
    void            EnableGuiObject(TEdit* p_pEdit, bool p_fEnable);
    void            EnableGuiObject(TComboBox* p_pComboBox, bool p_fEnable);
    void            EnableGuiObject(TListBox* p_pListBox, bool p_fEnable);
    void            EnableGuiObject(TGroupBox* p_pGroupBox, bool p_fEnable);
    void            EnableGuiObject(TMemo* p_pMemoBox, bool p_fEnable);
    void            EnableGuiObject(TScintilla* p_pMemo, bool p_fEnable);

    void            SetStatus(AnsiString p_strStatus);
    void            SetBusy(bool p_fBusy);
    void            UpdateDateTime();
    AnsiString      GetCurrentTimeString();

    bool            DoSubmission();

public:     // User declarations
    __fastcall      TfrmPageEdit(TComponent* Owner);

    void            ShowModal_CreateNew(AnsiString p_strShortTable);
    void            ShowModal_Edit(AnsiString p_strShortTable, int m_iID);
    void            SetUnsaved(bool p_fUnsaved);

    bool            GetAffectedTable();
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

