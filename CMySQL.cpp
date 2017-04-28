#ifdef BCB  //if compiling under BCB
#include <windows.h>  //include windows.h
#endif

#include "GenericHTTPClient.h"
#include "CMySQL.h"  //include the mysql.h files

#include "untIE.h"
#include <vcl.h>
#include <stdio.h>
#include <xmldoc.hpp>

//---------------------------------------------------------------------------

//CMySQL class implementation

//---------------------------------------------------------------------------

STRING_CLASS SafePack(STRING_CLASS Src)
{
    int         iLen    = Src.Length();
    AnsiString  sRet;

    for (int i = 0; i < iLen; ++i)
    {
        char    ch  = Src.c_str()[i];
        if (isalnum(ch) || ch == '_')
        {
            sRet += ch;
        }
        else
        {
            char    buf[10];
            sprintf(buf, "%02X", ch);
            sRet += "%" + AnsiString(buf);
        }
    }
    return sRet;
}

STRING_CLASS UnEx(STRING_CLASS s)
{
    STRING_CLASS    ret;
    int             iBytes  = (s.Length() - 1) / 2;
    const char*     pCur    = s.c_str() + 1;
    char            check[5];
    check[0] = '0';
    check[1] = 'x';
    check[4] = 0;
    for (int i = 0; i < iBytes; ++i)
    {
        memcpy(check + 2, pCur, 2);
        char    ch  = StrToInt(check);
        if (ch != 0)
        {
            ret += char(ch);
        }
        pCur += 2;
    }
    return ret;
}

STRING_CLASS FixupRecv(STRING_CLASS Src)
{
    int         iLen    = Src.Length();
    AnsiString  sRet;

    for (int i = 0; i < iLen; ++i)
    {
        char    ch  = Src.c_str()[i];
        if (ch == '[')
        {
            ch = '<';
        }
        if (ch == ']')
        {
            ch = '>';
        }
        sRet += ch;
    }
    return sRet;
}

CMySQL::CMySQL()  //constructor
{
    Connected = false;  //initialisation: not yet connected
    mysql_init(&Connection);  //initialise the MYSQL &Connection structure
    m_fPipe = false;
    m_iLastPipeError = 0;
    m_fIEProxy = false;
    m_iCustomPort = 0;
}

CMySQL::~CMySQL()  //destructor
{
    Disconnect();  //disconnect from the server
}

void CMySQL::EnablePipe(STRING_CLASS p_strSqlPipe, bool p_fIEProxy)
{
    m_fIEProxy = p_fIEProxy;
    if (p_strSqlPipe.SubString(0,4) == "http")
    {
        m_strSqlPipe = p_strSqlPipe;
        m_fPipe = true;
        m_iCustomPort = 0;
    }
    else
    {
        try
        {
            m_iCustomPort = StrToInt(p_strSqlPipe);
        }
        catch (...)
        {
            m_iCustomPort = 0;
            if (p_strSqlPipe != "")
            {
                Application->MessageBox("Please enter a valid port / sql pipe string in the configuration for this connection.\r\n\r\n\Using default port instead.", "Radical SiteEdit", MB_ICONWARNING | MB_OK);
            }
        }
        DisablePipe();
    }
}

void CMySQL::DisablePipe()
{
    m_strSqlPipe = "";;
    m_fPipe = false;
}

STRING_CLASS CMySQL::Escape(STRING_CLASS SourceString)
{
    STRING_CLASS    sRet    = "";
    int             iLen    = strlen(SourceString.c_str());

    char*           pBuf    = new char[iLen*4];
    mysql_escape_string(pBuf, SourceString.c_str(), iLen);
    sRet = pBuf;
    delete pBuf;

    return sRet;
}

bool CMySQL::Connect(STRING_CLASS Server, STRING_CLASS Username, STRING_CLASS Password, STRING_CLASS Database)  //connect to the server using appropriate credentials and initial database
{
    FreeAllResults();  //free all results
    if (m_fPipe)
    {
        m_strServer = Server;
        m_strUsername = Username;
        m_strPassword = Password;
        m_strDatabase = Database;
        Connected = true;  //connect succeeded, so set the flag
        return true;
    }
    else
    {
        if (!mysql_real_connect(&Connection, Server.c_str(), Username.c_str(), Password.c_str(), Database.c_str(), m_iCustomPort, 0, 0))  //attempt to connect
        {
            Connected = false;  //connect failed, so set the flag
        }
        else
        {
            Connected = true;  //connect succeeded, so set the flag
        }
    }
    return Connected;  //return the &Connection success flag
}

void CMySQL::Disconnect()  //disconnect from the server
{
    FreeAllResults();  //free all results
    if (m_fPipe)
    {
        m_strServer = "";
        m_strUsername = "";
        m_strPassword = "";
        m_strDatabase = "";
        m_strSqlPipe = "";
        m_iLastPipeError = 0;
        Connected = false;
        return;
    }
    if (Connected)  //if we are actually connected
    {
        mysql_close(&Connection);  //close the &Connection
        Connected = false;  //set the connected flag
    }
}

STRING_CLASS CMySQL::GetLastError()
{
    if (m_fPipe)
    {
        switch (m_iLastPipeError)
        {
        case SQLPIPE_ERROR_URL:
            return "Invalid Sql Pipe URL.";

        case SQLPIPE_ERROR_NONE:
            return "Success.";

        case SQLPIPE_ERROR_RESPONSE:
            return "Invalid response from Sql Pipe script.";

        case SQLPIPE_ERROR_LOGIN:
            return "Invalid server, username or password.";

        case SQLPIPE_ERROR_QUERY:
            return "Invalid or malformed SQL Query.";

        case SQLPIPE_ERROR_DB:
            return "Invalid database selected.";
        }
    }


    STRING_CLASS    strRet  = mysql_error(&Connection);
    return strRet;
}

CMySQLResult* CMySQL::Query(STRING_CLASS Query) //perform a mysql query
{
    if (!IsConnected())
    {
        return NULL;
    }
    if (m_fPipe)
    {
        CMySQLResult*   res         = NULL;
        int             iRetries    = 0;
        int             iRetriesMax = 3;
        while (iRetries < iRetriesMax)
        {
            res = DoPipeQuery(Query, m_fIEProxy);
            if (res)
            {
                m_iLastPipeError = 0;
                return res;
            }
            if (m_iLastPipeError == SQLPIPE_ERROR_QUERY)
            {
                return NULL;
            }
            else
            {
                ++iRetries;
            }
        }
        AnsiString  strError    = GetLastError();
        Application->MessageBox((strError + "\r\n\r\nFailed after " + IntToStr(iRetriesMax) + " attempts.").c_str(), "Sql Pipe error", MB_OK);
        Disconnect();
        return NULL;
    }


    /*
      The general idea here is to perform the query, buffer the entire result into a
      CMySQLResult structure and return it. If the query fails, the function will
      return NULL. If the query succeeded but has no result set, a CMySQLResult will
      still be returned, but will contain no information. To determine if this
      happened, use the CMySQL::GetResult_Exists() function.
    */
    int QueryResult = mysql_query(&Connection, Query.c_str());  //perform the query
    if (QueryResult != 0)  //if the query failed to execute (i.e. error in syntax etc)
    {
        return NULL;  //return a NULL result set
    }

    //query succeeded!
    MYSQL_RES*      ResultSet   = mysql_store_result(&Connection);  //buffer the entire result from the server

    CMySQLResult*   Result      = NULL;  //the result pointer to be returned

    if (ResultSet == NULL)  //if there is no result set (but the query succeeded)
    {
        Result = new CMySQLResult();    //create a new CMySQLResult
        mysql_free_result(ResultSet);  //free the result set
    }
    else
    {
        //if there is a result set
        Result = new CMySQLResult; //create a new CMySQLResult

        int Rows    = mysql_num_rows(ResultSet);  //determine how many rows there are in the result set
        int Fields  = mysql_num_fields(ResultSet);  //determine how many fields there are the result set
        Result->Data_Rows = Rows;  //set the amount of rows in the result class
        Result->Data_Fields = Fields;  //and the amount of fields in the result class

        Result->Data_FieldNames = new STRING_CLASS[Fields]; //allocate the memory for the field name text strings
        Result->Data_Binary = new CMySQL_Binary[Fields * Rows];

        int Row     = 0;  //current row counter; initialised to zero
        int Field   = 0;  //current field counter; initialised to zero
        for (Row = 0; Row < Rows; ++Row)     //go through all the rows in the result set
        {
            int*        iLengths    = new int[Fields];
            MYSQL_ROW   RowData     = mysql_fetch_row(ResultSet);  //fetch the row from the result set
            ULONG*      temp        = mysql_fetch_lengths(ResultSet);

            for (Field = 0; Field < Fields; ++Field)     //go through all the fields in the result set
            {
                int Index   = Result->GetIndex(Row, Field);  //calculate the index to set the string at int the array
                iLengths[Field] = temp[Field];
                int iSize   = iLengths[Field];

                Result->Data_Binary[Index].Data = new BYTE[iSize];
                Result->Data_Binary[Index].Size = iSize;

                BYTE*   pData   = RowData[Field];

                memcpy(Result->Data_Binary[Index].Data, pData, Result->Data_Binary[Index].Size);
            }

            delete[] iLengths;
        }
        for (Field = 0; Field < Fields; ++Field)     //go through the the fields
        {
            MYSQL_FIELD*FieldData;  //structure for field information
            FieldData = mysql_fetch_field(ResultSet);  //fetch the field information
            Result->Data_FieldNames[Field] = FieldData->name;  //get the field name
        }
    }
    Results.push_back(Result);  //add the result to the list of results
    return Result;  //return the CMySQLResult
}

bool CMySQL::IsConnected()  //determines if the &Connection is established
{
    return Connected;  //return true if connected, and false if not
}

void CMySQL::FreeResult(CMySQLResult* Result)   //frees a result returned from Query()
{
    int SizeBefore  = Results.size();  //get size before remove attempt
    Results.remove(Result);  //remove the result from the list (if its there)
    if (int(Results.size()) != SizeBefore)  //if the size has changed (i.e. the result was in the list)
    {
        delete Result;  //free the result
    }
}

void CMySQL::FreeAllResults()  //free all results created by this instance
{
    while (!Results.empty())     //while there are still results in the CMySQL instance
    {
        CMySQLResult*   Result  = Results.front();  //get a result from the list
        FreeResult(Result);  //free the result
    }
}

CMySQLResult* CMySQL::DoPipeQuery(STRING_CLASS strQuery, bool p_fUseIE)
{
    STRING_CLASS    strResult;

    if (p_fUseIE)
    {
        AnsiString  strPost;
        strPost += "user=" + SafePack(m_strUsername.c_str());
        strPost += "&";
        strPost += "db=" + SafePack(m_strDatabase.c_str());
        strPost += "&";
        strPost += "pass=" + SafePack(m_strPassword.c_str());
        strPost += "&";
        strPost += "server=" + SafePack(m_strServer.c_str());
        strPost += "&";
        strPost += "sql=" + SafePack(strQuery.c_str());
        strResult = FixupRecv(DoURL(m_strSqlPipe.c_str(), strPost));
    }
    else
    {
        GenericHTTPClient*  pClient = new GenericHTTPClient();

        pClient->InitilizePostArguments();
        pClient->AddPostArguments("user", m_strUsername.c_str());
        pClient->AddPostArguments("db", m_strDatabase.c_str());
        pClient->AddPostArguments("pass", m_strPassword.c_str());
        pClient->AddPostArguments("server", m_strServer.c_str());
        pClient->AddPostArguments("sql", strQuery.c_str());

        pClient->GrowBuffers(strQuery.Length() + 2048);

        if (pClient->Request(m_strSqlPipe.c_str(), GenericHTTPClient::RequestPostMethodMultiPartsFormData))
        {
            LPCTSTR szResult    = pClient->QueryHTTPResponse();

            strResult = FixupRecv(szResult);
            delete pClient;
        }
        else
        {
            delete pClient;
            m_iLastPipeError = SQLPIPE_ERROR_URL;
            return NULL;
        }
    }

    if (strResult == "SQLPIPE_ERROR_QUERY")
    {
        m_iLastPipeError = SQLPIPE_ERROR_QUERY;
        return NULL;
    }
    if (strResult == "SQLPIPE_ERROR_LOGIN")
    {
        m_iLastPipeError = SQLPIPE_ERROR_LOGIN;
        return NULL;
    }
    if (strResult == "SQLPIPE_ERROR_DB")
    {
        m_iLastPipeError = SQLPIPE_ERROR_DB;
        return NULL;
    }
    if (strResult.SubString(0, 15) != "SQLPIPE_SUCCESS")
    {
        m_iLastPipeError = SQLPIPE_ERROR_RESPONSE;
        return NULL;
    }

    strResult = strResult.SubString(16, 1024 * 1024);

    if (strResult != "")
    {
        CMySQLResult*       pResult = new CMySQLResult;

        _di_IXMLDocument    docXML  = LoadXMLData(strResult);
        _di_IXMLNode        ndMain  = docXML->ChildNodes->GetNode(1);

        int                 iRows   = 0;
        int                 iCols   = 0;
        if (ndMain->GetHasChildNodes())
        {
            _di_IXMLNode    ndSample    = ndMain->GetChildNodes()->GetNode(0);
            iCols = ndSample->GetChildNodes()->GetCount();
            pResult->Data_FieldNames = new STRING_CLASS[iCols];

            STRING_CLASS    strName;
            for (int j = 0; j < iCols; ++j)
            {
                _di_IXMLNode    ndField = ndSample->GetChildNodes()->GetNode(j);
                strName = UnEx(ndField->GetNodeName());
                pResult->Data_FieldNames[j] = strName;
            }

            iRows = ndMain->ChildNodes->GetCount();
            pResult->Data_Rows = iRows;
            pResult->Data_Fields = iCols;
            pResult->Data_Binary = new CMySQL_Binary[iRows * iCols];

            for (int i = 0; i < iRows ; ++i)
            {
                _di_IXMLNode    ndRow   = ndMain->GetChildNodes()->GetNode(i);
                for (int j = 0; j < iCols; ++j)
                {
                    _di_IXMLNode    ndItem  = ndRow->GetChildNodes()->GetNode(j);
                    STRING_CLASS    strName = ndItem->GetNodeName();
                    STRING_CLASS    strValue;

                    if (ndItem->IsTextElement)
                    {
                        strValue = UnEx(ndItem->GetText());
                    }
                    else
                    {
                        strValue = ndItem->GetXML();
                        strValue = strValue.SubString(strName.Length() + 12, strValue.Length() - strName.Length() * 2 - 17);
                    }

                    int Index   = pResult->GetIndex(i, j);  //calculate the index to set the string at int the array

                    int iSize   = strValue.Length();
                    pResult->Data_Binary[Index].Data = new BYTE[iSize];
                    pResult->Data_Binary[Index].Size = iSize;

                    BYTE*   pData   = strValue.c_str();

                    memcpy(pResult->Data_Binary[Index].Data, pData, pResult->Data_Binary[Index].Size);
                }
            }
        }
        return pResult;
    }
    return NULL;
}

//---------------------------------------------------------------------------

//CMySQLResult class implementation

//---------------------------------------------------------------------------

CMySQLResult::CMySQLResult()  //constructor
{
    Data_Rows = 0;  //no rows
    Data_Fields = 0;  //no fields
    Data_Binary = 0;
    Data_FieldNames = NULL;  //no field names
}

CMySQLResult::~CMySQLResult()  //destructor
{
    FreeData();  //deallocate memory allocated
}

bool CMySQLResult::GetResult_Exists()  //determine if this result has a result set
{
    if ((Data_Rows * Data_Fields) != 0)
    {
        return true;
    }    //if there are rows and fields, return true
    else
    {
        return false;
    }   //otherwise, we know there was no result
}

int CMySQLResult::GetResult_Rows()  //determine how many rows are in the result set
{
    return Data_Rows;  //return the amount of rows in the result set
}

int CMySQLResult::GetResult_Fields()  //determine how many fields are in the result set
{
    return Data_Fields;  //return the amount of fields in the result set
}

STRING_CLASS CMySQLResult::GetResult_FieldName(int Field)  //get the name of a certain field
{
    STRING_CLASS    Result;     //result string
    if (Field >= 0 && Field < Data_Fields)  //if the Field number is in valid range
    {
        Result = Data_FieldNames[Field];  //copy the appropriate string
    }
    return Result;  //return the result
}

CMySQL_Binary* CMySQLResult::GetResult_Binary(int Row, int Field)
{
    if (Row >= 0 && Row < Data_Rows && Field >= 0 && Field < Data_Fields)  //if data item is in range
    {
        return &Data_Binary[GetIndex(Row, Field)];
    }
    return 0;  //return the result
}

STRING_CLASS CMySQLResult::GetResult_Text(int Row, int Field)  //get the result data at Row, Field
{
    STRING_CLASS    Result;     //result string
    if (Row >= 0 && Row < Data_Rows && Field >= 0 && Field < Data_Fields)  //if data item is in range
    {
        int     iSize   = Data_Binary[GetIndex(Row, Field)].Size;
        char*   pData   = new char[iSize + 1];
        pData[iSize] = 0;

        memcpy(pData, (char *) Data_Binary[GetIndex(Row, Field)].Data, iSize);     //copy the data item to the result string

        Result = pData;
        delete[] pData;
    }
    return Result;  //return the result
}

void CMySQLResult::FreeData()  //deallocate data
{
    if (Data_Binary != NULL)  //if there are data strings to deallocate
    {
        int iItems  = Data_Rows* Data_Fields;
        for (int i = 0; i < iItems; ++i)
        {
            delete[] Data_Binary[i].Data;
        }
        delete[] Data_Binary;  //delete them
        Data_Binary = NULL;  //reset the pointer
    }
    if (Data_FieldNames != NULL)     //if there are field name strings to delete
    {
        delete[] Data_FieldNames;  //delete them
        Data_FieldNames = NULL;  //reset the pointer
    }
    Data_Rows = 0;  //no rows anymore
    Data_Fields = 0;  //no fields anymore
}

int CMySQLResult::GetIndex(int Row, int Field)  //determine the array index for a certain row/field
{
    return Row + (Field * Data_Rows);  //return the column array index
}

//---------------------------------------------------------------------------

