//---------------------------------------------------------------------------
#include "_includes.h"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void Split(std::string Source, char Splitter, std::string* Dest1, std::string* Dest2)
{
    const char* Source_cstr = Source.c_str();  //get the char* of the source string
    int         a;  //temp var
    int         b           = Source.size();  //get the size of the source string
    int         Found       = -1;  //default found state as not yet found
    for (a = 0; a < b; a++)  //go through the whole string
    {
        if (Source_cstr[a] == Splitter)  //if splitter character found
        {
            Found = a;  //set the found position
            break;  //break out of the for loop
        }
    }
    if (Found == -1)  //if not found
    {
        if (Dest1 != 0)
        {
            *Dest1 = Source;
        }  //copy source into Dest1
        if (Dest2 != 0)
        {
            *Dest2 = "";
        }  //and leave Dest2 blank
        return;  //exit
    }
    else  //if it was found
    {
        if (Dest1 != 0)
        {
            *Dest1 = Source.substr(0, Found);
        }  //put the first half in Dest1
        if (Dest2 != 0)
        {
            *Dest2 = Source.substr(Found + 1, b - Found);
        }  //and the last half in Dest2
        return;  //exit
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void Split(AnsiString Source, char Splitter, AnsiString* Dest1, AnsiString* Dest2)
{
    std::string strProxySource  = Source.c_str();
    std::string*strProxyDest1   = NULL;
    std::string*strProxyDest2   = NULL;

    if (Dest1 != NULL)
    {
        strProxyDest1 = new std::string;
    }
    if (Dest2 != NULL)
    {
        strProxyDest2 = new std::string;
    }

    Split(strProxySource, Splitter, strProxyDest1, strProxyDest2);

    if (Dest1 != NULL)
    {
        *Dest1 = strProxyDest1->c_str();
        delete strProxyDest1;
    }
    if (Dest2 != NULL)
    {
        *Dest2 = strProxyDest2->c_str();
        delete strProxyDest2;
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void LoadComboBox(TComboBox* pComboBox, AnsiString strGroupName)
{
    CIniFile    iniFile;
    iniFile.LoadFile(INI_FILE);
    int         iIndex  = 0;
    AnsiString  strDesc;
    do
    {
        AnsiString  strIndex    = IntToStr(iIndex);
        strDesc = iniFile.GetItem(strGroupName, strIndex);
        if (strDesc == "")
        {
            break;
        }
        pComboBox->Items->Add(IntToStr(iIndex) + ": " + strDesc);
        ++iIndex;
    }
    while (strDesc != "");
    if (iIndex == 0)
    {
        pComboBox->Items->Add("0: [Default]");
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
