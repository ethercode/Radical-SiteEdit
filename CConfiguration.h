//---------------------------------------------------------------------------

#ifndef CConfigurationH
#define CConfigurationH

class CConfiguration
{
public:

                CConfiguration();
                ~CConfiguration();

    void        Save();

    AnsiString  GetFilename();
    void        LoadName(AnsiString p_strName);
    void        SetName(AnsiString p_strName);
    void        SetHost(AnsiString p_strHost);
    void        SetUsername(AnsiString p_strUsername);
    void        SetPassword(AnsiString p_strPassword);
    void        SetDatabase(AnsiString p_strDatabase);
    void        SetSQLPipe(AnsiString p_strSQLPipe);
    void        SetRememberPassword(bool p_fRememberPassword);
    void        SetReverseList(bool p_fReverseList);
    AnsiString  GetName();
    AnsiString  GetHost();
    AnsiString  GetUsername();
    AnsiString  GetPassword();
    AnsiString  GetDatabase();
    AnsiString  GetSQLPipe();
    bool        GetRememberPassword();
    bool        GetReverseList();

private:

    void        Load();

    AnsiString  m_strName;
    AnsiString  m_strHost;
    AnsiString  m_strUsername;
    AnsiString  m_strPassword;
    AnsiString  m_strDatabase;
    AnsiString  m_strSQLPipe;
    bool        m_fRememberPassword;
    bool        m_fReverseList;
};

//---------------------------------------------------------------------------
#endif
