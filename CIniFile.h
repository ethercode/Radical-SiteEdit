#ifndef _CIniFile_h_
#define _CIniFile_h_

#include <stdio.h>

#include <list>
using namespace std;

struct  SIniFile_Group;
struct  SIniFile_Item;

//=======================================================================================================
/*
    An item in an ini file (a value)
*/
struct SIniFile_Item
{
    SIniFile_Group* Group;  //pointer to group item belongs in
    AnsiString      Name;  //name of the item
    AnsiString      Value;  //value of the item
};
//=======================================================================================================


//=======================================================================================================
/*
    A group in an ini file
*/
struct SIniFile_Group
{
    AnsiString              Name;  //name of the group
    list<SIniFile_Item*>    Items;  //list of items in that group
};
//=======================================================================================================


//=======================================================================================================
/*
    Ini file loading / saving return values
*/
const int               INI_SUCCESS     = 0;  //successful read/write performed
const int               INI_ERROR_LOAD  = 1;  //couldn't load; file not found
const int               INI_ERROR_SAVE  = 2;  //couldn't save; file not writable for some reason
//=======================================================================================================


//=======================================================================================================
class CIniFile
{
public:
                            CIniFile();  //constructor
                            ~CIniFile();  //destructor

    int                     LoadFile(AnsiString Filename);  //load and parse an ini file
    int                     SaveFile(AnsiString Filename);  //save the ini file to Filename

    AnsiString              GetItem(AnsiString GroupName, AnsiString Name);  //get the value of an item from a certain group
    bool                    GetGroupItems(AnsiString GroupName, list<AnsiString>* Names);  //get a list of items in a certain group
    bool                    GroupExists(AnsiString GroupName);  //determine if a group exists

    bool                    AddItem(AnsiString GroupName, AnsiString Name, AnsiString Value);  //add/change an item to a certain group
    bool                    RemoveItem(AnsiString GroupName, AnsiString Name);  //remove an item from a certain group
    void                    AddGroup(AnsiString GroupName);  //add a new group
    void                    RemoveGroup(AnsiString GroupName);  //remove a group


private:
    list<AnsiString>        Lines;  //all lines read from the file
    int                     ReadLines(AnsiString Filename);  //read in all the lines from the file
    void                    ParseLines();  //parse the loaded lines, look for items

    list<SIniFile_Group*>   Groups;  //all groups in the file

    SIniFile_Group*         GetGroup(AnsiString GroupName);  //gets a group pointer from a group name
    SIniFile_Item*          GetItem(SIniFile_Group* Group, AnsiString Name);  //get the value of an item from a certain group
};
//=======================================================================================================

#endif
