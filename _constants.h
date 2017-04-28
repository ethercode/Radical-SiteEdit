//---------------------------------------------------------------------------
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#include "_includes.h"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#define APPNAME (AnsiString("Radical SiteEdit 2.01"))

#define EL_DISCONNECTED     1
#define EL_CONNECTED        2
#define EL_GOTTYPE          3
#define EL_GOTPAGE          4

#define CONTENT_TABLE_SIGNATURE (AnsiString("content_"))

#define INI_FILE "_configuration.ini"

#define INI_GENERAL_GROUP "General_Options"

#define INI_GENERAL_LASTCONNECTION "Last_Connection"
#define INI_GENERAL_IEPROXY "Use_IE_Proxy"

#define INI_CONNECTION_GROUP "Connection_Settings"
#define INI_CONNECTION_NAME "Connection_Name"
#define INI_CONNECTION_SERVER "Database_Hostname"
#define INI_CONNECTION_DATABASE "Database_Name"
#define INI_CONNECTION_USERNAME "Database_Username"
#define INI_CONNECTION_PASSWORD "Database_Password"
#define INI_CONNECTION_SQLPIPE "SQLPipe_Url"
#define INI_CONNECTION_SAVEPASSWORD "Remember_Password"
#define INI_CONNECTION_REVERSELIST "Reverse_Page_List"

#define MAX_MENU_ITEMS 2048

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

