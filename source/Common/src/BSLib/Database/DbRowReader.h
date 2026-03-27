#pragma once

#include "pch.h"
#include "DbInstance.h"
#include "BSLib/CriticalSectionScoped.h"
#include "utils/SimpleTime.h"

class CDbRowReader {
public:
    CDbRowReader() : m_hStmt(SQL_NULL_HSTMT), m_nColID(1), m_bIsClosed(true) {}
    CDbRowReader(SQLHANDLE hStmt) : m_hStmt(hStmt), m_nColID(1), m_bIsClosed(false) {}
    ~CDbRowReader() { Close(); }

    void Attach(SQLHANDLE hStmt) {
        ACS_SCOPED_LOCK(m_cs);
        if (m_hStmt != SQL_NULL_HSTMT && !m_bIsClosed) Close();
        m_hStmt = hStmt;
        m_nColID = 1;
        m_bIsClosed = (hStmt == SQL_NULL_HSTMT);
    }

    void Close() {
        ACS_SCOPED_LOCK(m_cs);
        if (!m_bIsClosed && m_hStmt != SQL_NULL_HSTMT) {
            ::SQLFreeStmt(m_hStmt, SQL_CLOSE);
            m_bIsClosed = true;
        }
    }

    bool FetchNext() {
        ACS_SCOPED_LOCK(m_cs);
        m_nColID = 1;
        SQLRETURN ret = ::SQLFetch(m_hStmt);
        return SQL_SUCCEEDED(ret);
    }

    template<typename T>
    T Read() {
        ACS_SCOPED_LOCK(m_cs);
        T result; SQLLEN cb;
        ::SQLGetData(m_hStmt, m_nColID++, GetColType<T>(), &result, 0, &cb);
        return (cb == SQL_NULL_DATA) ? T() : result;
    }

    std::vector<BYTE> ReadBinary(int nDataLen);
    std::string ReadStringA(int nMaxLen);
    std::wstring ReadStringW(int nMaxLen);
    SimpleTime ReadDateTime();

private:
    CDbRowReader(const CDbRowReader&);
    CDbRowReader& operator=(const CDbRowReader&);

    template<typename T>
    static SQLSMALLINT GetColType() {
        if (typeid(T) == typeid(BYTE)) return SQL_C_TINYINT;
        if (typeid(T) == typeid(short)) return SQL_C_SHORT;
        if (typeid(T) == typeid(int)) return SQL_C_LONG;
        if (typeid(T) == typeid(long long)) return SQL_C_SBIGINT;
        if (typeid(T) == typeid(float)) return SQL_C_FLOAT;
        if (typeid(T) == typeid(double)) return SQL_C_DOUBLE;
        if (typeid(T) == typeid(bool)) return SQL_C_BIT;
        return SQL_C_CHAR;
    }

    SQLHANDLE m_hStmt;
    int m_nColID;
    bool m_bIsClosed;
    CCriticalSection m_cs;
};