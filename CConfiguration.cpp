//---------------------------------------------------------------------------


#pragma hdrstop

#include "_includes.h"
#include "CConfiguration.h"


//---------------------------------------------------------------------------
CConfiguration::CConfiguration()
{
    m_fRememberPassword = false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
CConfiguration::~CConfiguration()
{
    Save();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString CConfiguration::GetFilename()
{
    return "conf_" + m_strName + ".ini";
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void CConfiguration::LoadName(AnsiString p_strName)
{
    m_strName = p_strName;
    Load();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void CConfiguration::SetName(AnsiString p_strName)
{
    m_strName = p_strName;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void CConfiguration::SetHost(AnsiString p_strHost)
{
    m_strHost = p_strHost;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void CConfiguration::SetUsername(AnsiString p_strUsername)
{
    m_strUsername = p_strUsername;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void CConfiguration::SetPassword(AnsiString p_strPassword)
{
    m_strPassword = p_strPassword;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void CConfiguration::SetDatabase(AnsiString p_strDatabase)
{
    m_strDatabase = p_strDatabase;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void CConfiguration::SetSQLPipe(AnsiString p_strSQLPipe)
{
    m_strSQLPipe = p_strSQLPipe;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void CConfiguration::SetRememberPassword(bool p_fRememberPassword)
{
    m_fRememberPassword = p_fRememberPassword;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void CConfiguration::SetReverseList(bool p_fReverseList)
{
    m_fReverseList = p_fReverseList;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString CConfiguration::GetName()
{
    return m_strName;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString CConfiguration::GetHost()
{
    return m_strHost;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString CConfiguration::GetUsername()
{
    return m_strUsername;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString CConfiguration::GetPassword()
{
    return m_strPassword;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString CConfiguration::GetDatabase()
{
    return m_strDatabase;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString CConfiguration::GetSQLPipe()
{
    return m_strSQLPipe;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
bool CConfiguration::GetRememberPassword()
{
    return m_fRememberPassword;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
bool CConfiguration::GetReverseList()
{
    return m_fReverseList;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void CConfiguration::Load()
{
    CIniFile*   iniFile = new CIniFile;
    if (m_strName != "")
    {
        AnsiString  strFilename = GetFilename();
        iniFile->LoadFile(strFilename);
    }

    m_strName = iniFile->GetItem(INI_CONNECTION_GROUP, INI_CONNECTION_NAME);
    m_strHost = iniFile->GetItem(INI_CONNECTION_GROUP, INI_CONNECTION_SERVER);
    m_strDatabase = iniFile->GetItem(INI_CONNECTION_GROUP, INI_CONNECTION_DATABASE);
    m_strUsername = iniFile->GetItem(INI_CONNECTION_GROUP, INI_CONNECTION_USERNAME);
    m_strPassword = iniFile->GetItem(INI_CONNECTION_GROUP, INI_CONNECTION_PASSWORD);
    m_strSQLPipe = iniFile->GetItem(INI_CONNECTION_GROUP, INI_CONNECTION_SQLPIPE);
    m_fRememberPassword = (iniFile->GetItem(INI_CONNECTION_GROUP, INI_CONNECTION_SAVEPASSWORD) == "1");
    m_fReverseList = (iniFile->GetItem(INI_CONNECTION_GROUP, INI_CONNECTION_REVERSELIST) == "1");

    delete iniFile;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void CConfiguration::Save()
{
    CIniFile*   iniFile = new CIniFile;

    iniFile->AddGroup(INI_CONNECTION_GROUP);
    iniFile->AddItem(INI_CONNECTION_GROUP, INI_CONNECTION_NAME, m_strName);
    iniFile->AddItem(INI_CONNECTION_GROUP, INI_CONNECTION_SERVER, m_strHost);
    iniFile->AddItem(INI_CONNECTION_GROUP, INI_CONNECTION_DATABASE, m_strDatabase);
    iniFile->AddItem(INI_CONNECTION_GROUP, INI_CONNECTION_USERNAME, m_strUsername);
    iniFile->AddItem(INI_CONNECTION_GROUP, INI_CONNECTION_PASSWORD, m_strPassword);
    iniFile->AddItem(INI_CONNECTION_GROUP, INI_CONNECTION_SQLPIPE, m_strSQLPipe);
    iniFile->AddItem(INI_CONNECTION_GROUP, INI_CONNECTION_SAVEPASSWORD, (m_fRememberPassword ? "1" : "0"));
    iniFile->AddItem(INI_CONNECTION_GROUP, INI_CONNECTION_REVERSELIST, (m_fReverseList ? "1" : "0"));

    if (m_strName != "")
    {
        iniFile->SaveFile(GetFilename());
    }

    delete iniFile;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
