//---------------------------------------------------------------------------
#ifndef _utility_functionsH
#define _utility_functionsH
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#include "_includes.h"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void    Split(std::string Source, char Splitter, std::string* Dest1, std::string* Dest2);
void    Split(AnsiString Source, char Splitter, AnsiString* Dest1, AnsiString* Dest2);
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void    LoadComboBox(TComboBox* pComboBox, AnsiString strGroupName);
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
