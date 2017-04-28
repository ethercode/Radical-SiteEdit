//---------------------------------------------------------------------------
#ifndef untMenuEditH
#define untMenuEditH
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class TfrmMenuEdit:public TForm
{
__published:    // IDE-managed Components
    TGroupBox*      grpMenuItems;
    TListBox*       lbxItems;
    TGroupBox*      grpProperties;
    TLabel*         lblText;
    TLabel*         lblURL;
    TLabel*         lblStyle;
    TLabel*         lblAccess;
    TEdit*          edtText;
    TEdit*          edtURL;
    TGroupBox*      grpOptions;
    TLabel*         lblApply;
    TLabel*         lblOK;
    TLabel*         lblCancel;
    TTimer*         tmrIdle;
    TStatusBar*     stbMain;
    TComboBox*      cbxAccess;
    TLabel*         lblNew;
    TLabel*         lblDelete;
    TLabel*         lblMoveUp;
    TLabel*         lblMoveDown;
    TLabel*         lblPropCancel;
    TLabel*         lblPropApply;
    TComboBox*      cbxStyle;
    void __fastcall FormCreate(TObject* Sender);
    void __fastcall tmrIdleTimer(TObject* Sender);
    void __fastcall lblNewClick(TObject* Sender);
    void __fastcall lblDeleteClick(TObject* Sender);
    void __fastcall lblMoveUpClick(TObject* Sender);
    void __fastcall lblMoveDownClick(TObject* Sender);
    void __fastcall lbxItemsKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
    void __fastcall edtTextChange(TObject* Sender);
    void __fastcall edtURLChange(TObject* Sender);
    void __fastcall cbxAccessChange(TObject* Sender);
    void __fastcall lbxItemsClick(TObject* Sender);
    void __fastcall lblPropCancelClick(TObject* Sender);
    void __fastcall lblPropApplyClick(TObject* Sender);
    void __fastcall lblCancelClick(TObject* Sender);
    void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
    void __fastcall lblApplyClick(TObject* Sender);
    void __fastcall lblOKClick(TObject* Sender);
    void __fastcall cbxStyleChange(TObject* Sender);
private:    // User declarations
    bool            m_fBusy;
    bool            m_fUnsaved;
    bool            m_fAllowShow;
    bool            m_fEditing;
    bool            m_fExitNow;

    CMenuItem*      m_pMenuItems[MAX_MENU_ITEMS];
    CMenuItem*      GetCurrentItem();
    CMenuItem*      m_pItemEdited;
    bool            m_fPermitClose;
    bool            m_fClosingByLink;

    std::queue<int> m_queDeletes;

    int             GetSlot();
    void            FreeSlot(int p_iIndex);
    int             GetUnusedID();
    void            GetSelectRange(int& p_iLowest, int& p_iHighest);
    void            SwapItems(int iFirst, int iSecond);
    bool            Save();

public:     // User declarations
    __fastcall      TfrmMenuEdit(TComponent* Owner);

    bool            GetAllowShow();

    void            EnableGuiObject(TLabel* p_pLabel, bool p_fEnable);
    void            EnableGuiObject(TCheckBox* p_pCheckBox, bool p_fEnable);
    void            EnableGuiObject(TEdit* p_pEdit, bool p_fEnable);
    void            EnableGuiObject(TComboBox* p_pComboBox, bool p_fEnable);
    void            EnableGuiObject(TListBox* p_pListBox, bool p_fEnable);
    void            EnableGuiObject(TGroupBox* p_pGroupBox, bool p_fEnable);
    void            EnableGuiObject(TMemo* p_pMemoBox, bool p_fEnable);

    void            SetStatus(AnsiString p_strStatus);
    void            SetBusy(bool p_fBusy);

    void            Refresh();
    void            FreeMenuItems();

    void            ConstrainUI();
    void            SetEditing(bool p_fEditing);
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

