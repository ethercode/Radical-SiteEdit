//---------------------------------------------------------------------------
#include "_includes.h"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
USEFORM("untMain.cpp", frmMain);
USEFORM("untPageEdit.cpp", frmPageEdit);
USEFORM("untMenuEdit.cpp", frmMenuEdit);
USEFORM("untConfig.cpp", frmConfig);
USEFORM("untDirectSQL.cpp", frmDirectSQL);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "Radical SiteEdit";
        Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->CreateForm(__classid(TfrmDirectSQL), &frmDirectSQL);
         Application->Run();
    }
    catch (Exception& exception)
    {
        Application->ShowException(&exception);
    }
    catch (...)
    {
        try
        {
            throw Exception("");
        }
        catch (Exception& exception)
        {
            Application->ShowException(&exception);
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
