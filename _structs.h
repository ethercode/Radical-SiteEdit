//---------------------------------------------------------------------------
#ifndef _STRUCTS_H_
#define _STRUCTS_H_
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#include "_includes.h"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class CMenuItem
{
public:
    CMenuItem()
    {
        m_iID = 0;
        m_iOrder = 0;
        m_iAccess = 0;
        m_iStyle = 0;
        m_fChanged = false;
        m_fNew = false;
        m_fCommitted = false;
    }

    int GetID()
    {
        return m_iID;
    }

    int GetOrder()
    {
        return m_iOrder;
    }

    AnsiString GetText()
    {
        return m_strText;
    }

    AnsiString GetURL()
    {
        return m_strURL;
    }
    int GetStyle()
    {
        return m_iStyle;
    }

    int GetAccess()
    {
        return m_iAccess;
    }

    bool GetChanged()
    {
        return m_fChanged;
    }

    void SetID(int p_iID)
    {
        if (m_iID != p_iID)
        {
            m_iID = p_iID;
            m_fChanged = true;
        }
    }

    void SetOrder(int p_iOrder)
    {
        if (m_iOrder != p_iOrder)
        {
            m_iOrder = p_iOrder;
            m_fChanged = true;
        }
    }

    void SetText(AnsiString p_strText)
    {
        if (m_strText != p_strText)
        {
            m_strText = p_strText;
            m_fChanged = true;
        }
    }

    void SetURL(AnsiString p_strURL)
    {
        if (m_strURL != p_strURL)
        {
            m_strURL = p_strURL;
            m_fChanged = true;
        }
    }

    void SetStyle(int p_iStyle)
    {
        if (m_iStyle != p_iStyle)
        {
            m_iStyle = p_iStyle;
            m_fChanged = true;
        }
    }

    void SetAccess(int p_iAccess)
    {
        if (m_iAccess != p_iAccess)
        {
            m_iAccess = p_iAccess;
            m_fChanged = true;
        }
    }

    void SetChanged(bool p_fChanged)
    {
        if (m_fChanged != p_fChanged)
        {
            m_fChanged = p_fChanged;
        }
    }

    void SetNew(bool p_fNew)
    {
        m_fNew = p_fNew;
    }

    bool GetNew()
    {
        return m_fNew;
    }

    void SetCommitted(bool p_fCommitted)
    {
        m_fCommitted = p_fCommitted;
    }

    bool GetCommitted()
    {
        return m_fCommitted;
    }



private:
    int         m_iID;
    int         m_iOrder;
    AnsiString  m_strText;
    AnsiString  m_strURL;
    int         m_iStyle;
    int         m_iAccess;
    bool        m_fChanged;
    bool        m_fNew;
    bool        m_fCommitted;
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
