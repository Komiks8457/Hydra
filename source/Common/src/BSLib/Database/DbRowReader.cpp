#include "DbRowReader.h"

std::string CDbRowReader::ReadStringA(int nMaxLen)
{
    ACS_SCOPED_LOCK(m_cs);
    std::vector<char> buf(nMaxLen + 1, 0);
    SQLLEN cb;
    ::SQLGetData(m_hStmt, m_nColID++, SQL_C_CHAR, &buf[0],
                 buf.size(), &cb);
    return (cb == SQL_NULL_DATA) ? "" : std::string(&buf[0]);
}

std::wstring CDbRowReader::ReadStringW(int nMaxLen)
{
    ACS_SCOPED_LOCK(m_cs);
    std::vector<wchar_t> buf(nMaxLen + 1, 0);
    SQLLEN cb;
    ::SQLGetData(m_hStmt, m_nColID++, SQL_C_WCHAR, &buf[0],
                 buf.size() * sizeof(wchar_t), &cb);
    return (cb == SQL_NULL_DATA) ? L"" : std::wstring(&buf[0]);
}

std::vector<BYTE> CDbRowReader::ReadBinary(int nDataLen)
{
    ACS_SCOPED_LOCK(m_cs);
    std::vector<BYTE> result(nDataLen);
    SQLLEN cb;
    ::SQLGetData(m_hStmt, m_nColID++, SQL_C_BINARY, &result[0],
                 nDataLen, &cb);
    if (cb == SQL_NULL_DATA) result.clear();
    return result;
}

SimpleTime CDbRowReader::ReadDateTime()
{
    ACS_SCOPED_LOCK(m_cs);
    SQL_TIMESTAMP_STRUCT ts;
    SQLLEN cb;
    ::SQLGetData(m_hStmt, m_nColID++, SQL_C_TYPE_TIMESTAMP, &ts,
                 0, &cb);
    SimpleTime st;
    if (cb != SQL_NULL_DATA) {
        st.year = ts.year; st.month = ts.month; st.day = ts.day;
        st.hour = ts.hour; st.min = ts.minute; st.sec = ts.second;
    }
    return st;
}