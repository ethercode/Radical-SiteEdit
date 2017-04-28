//---------------------------------------------------------------------------

#ifndef CMySQLH
#define CMySQLH

#ifdef WIN32
#include <winsock.h>  //tcp sockets headers
#endif

#include <mysql/mysql.h>  //mysql standard headers
#include <list>

//note: this BCB define is not a default C++ Builder 6 define, it needs to be added when compiling under BCB6
#ifndef BCB  //if not compiling under C++ Builder
#include <string>  //string class from standard library
#define STRING_CLASS std::string  //use the standard  library's string class for the interface string
#else
#include <vcl.h>  //borland visual component libray
#define STRING_CLASS AnsiString  //use the VCL AnsiString class as the string class
#endif

#define SQLPIPE_ERROR_NONE 0
#define SQLPIPE_ERROR_RESPONSE 1
#define SQLPIPE_ERROR_LOGIN 2
#define SQLPIPE_ERROR_QUERY 3
#define SQLPIPE_ERROR_DB 4
#define SQLPIPE_ERROR_URL 5

struct CMySQL_Binary
{
    BYTE*   Data;
    int     Size;
};

class CMySQLResult  //query result class
{
    friend class    CMySQL; //allow the CMySQL class to access private members
public:
    bool            GetResult_Exists(); //determine if there is a result set
    int             GetResult_Rows();    //get amount of rows in the result set
    int             GetResult_Fields();  //get amount of fields in the result set
    STRING_CLASS    GetResult_FieldName(int Field);  //get the name of the field specified by Field
    STRING_CLASS    GetResult_Text(int Row, int Field);  //get the actual query data specified by Row and Field
    CMySQL_Binary*  GetResult_Binary(int Row, int Field);

private:
                    CMySQLResult();  //constructor
                    ~CMySQLResult();    //destructor

    int             Data_Rows;  //amount of rows in result
    int             Data_Fields;    //amount of fields in result
    CMySQL_Binary*  Data_Binary;  //data as binary
    STRING_CLASS*   Data_FieldNames;     //field names in the result

    void            FreeData(); //clear the result set string arrays
    int             GetIndex(int Row, int Field);    //get 1 dimensional the array index for a 2D reference
};

class CMySQL    //actual CMySQL class which provides abstract connection and query handling
{
public:
                                CMySQL();    //constructor
                                ~CMySQL();  //destructor

    bool                        Connect(STRING_CLASS Server, STRING_CLASS Username, STRING_CLASS Password, STRING_CLASS Database);   //connect to server
    void                        Disconnect();    //disconnect from the server

    CMySQLResult*               Query(STRING_CLASS Query);   //execute a query.
    void                        FreeResult(CMySQLResult* Result);   //frees a result returned from Query()
    bool                        IsConnected();   //determine if there is an active connection
    void                        FreeAllResults();  //frees all results that were created by this instance

    static STRING_CLASS         Escape(STRING_CLASS SourceString);
    STRING_CLASS                GetLastError();

    void                        EnablePipe(STRING_CLASS p_strSqlPipe, bool p_fIEProxy);
    void                        DisablePipe();

private:
    MYSQL                       Connection; //pointer to standard mysql C api connection object
    bool                        Connected;   //true if connected

    bool                        m_fPipe;
    STRING_CLASS                m_strServer;
    STRING_CLASS                m_strUsername;
    STRING_CLASS                m_strPassword;
    STRING_CLASS                m_strDatabase;
    STRING_CLASS                m_strSqlPipe;
    int                         m_iLastPipeError;
    bool                        m_fIEProxy;
    int                         m_iCustomPort;

    CMySQLResult*               DoPipeQuery(STRING_CLASS strQuery, bool p_fUseIE);

    std::list<CMySQLResult*>    Results;  //list of results belonging to this instance
};

//---------------------------------------------------------------------------
#endif

