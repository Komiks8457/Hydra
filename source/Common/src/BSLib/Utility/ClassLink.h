#pragma once
#pragma warning(disable: 4355)

#include "pch.h"

#define CL_FLAG_ERASED	0x00000001

template <class _T>
struct __SCLStaticData;

template <class _T>
struct	_CL
{
    typedef _CL<_T>	iterator;

    __SCLStaticData<_T>* pStatic;

    _CL()
    {
        pStatic = NULL;
    }
    _CL(__SCLStaticData<_T>* p)
    {
        pStatic = p;
        if (pStatic)
        {
            pStatic->m_lpCLCur = pStatic->m_lpCLBegin;
            pStatic->m_dwFlag &= ~CL_FLAG_ERASED;
        }
    }

    inline iterator& operator++()
    {
        if(pStatic->m_dwFlag & CL_FLAG_ERASED)
        {
            pStatic->m_dwFlag &= ~CL_FLAG_ERASED;
            return *this;
        }
        if(pStatic->m_lpCLCur)
            pStatic->m_lpCLCur = pStatic->m_lpCLCur->GetNext();
        return *this;
    }
    iterator operator ++(int)
    {
        if(pStatic->m_dwFlag & CL_FLAG_ERASED)
        {
            pStatic->m_dwFlag &= ~CL_FLAG_ERASED;
            return *this;
        }
        if(pStatic->m_lpCLCur)
            pStatic->m_lpCLCur = pStatic->m_lpCLCur->GetNext();
        return *this;
    }
    inline _T* operator*()
    {
        return pStatic->m_lpCLCur->GetObj();
    }
    inline BOOL	IsData() { return (pStatic && pStatic->m_lpCLCur) ? TRUE : FALSE; }
    inline BOOL	IsEnd() { return (pStatic && pStatic->m_lpCLCur) ? FALSE : TRUE; }
};


template <class _T>
class CClassLink;

template <class _T>
struct __SCLStaticData
{
    BOOL			m_blAutoLink;
    LONG			m_lnCnt;
    CClassLink<_T>*	m_lpCLBegin;
    CClassLink<_T>*	m_lpCLEnd;
    CClassLink<_T>*	m_lpCLCur;
    DWORD			m_dwFlag;

    void			Init()
    {
        m_lnCnt = 0;
        m_lpCLBegin = m_lpCLEnd = m_lpCLCur = NULL;
        m_dwFlag = 0;
    }
};


#define CLASSLINK_BEGIN(CN)		\
typedef CN typeClassLink; \
static	__SCLStaticData<typeClassLink> m_sCLBegin;

#define DECLARE_CLASS_LINK(CN)		\
public:					\
	CLASSLINK_BEGIN(CN)	\
	CClassLink<CN>	m_ClassLink;

#define IMPLEMENT_CLASSLINK(CN, AutoLink)	\
	__SCLStaticData<CN>  CN::m_sCLBegin = { AutoLink, 0, NULL, NULL, NULL, 0 };

#define GET_CLASSLINK_BEGIN(CN)	_CL<CN>(&CN::m_sCLBegin)
#define GET_CLASSLINK_CNT(CN)	CN::m_sCLBegin.m_lnCnt

template <class _T>
class	CClassLink
{
    BOOL		m_blLinked;
    CClassLink*	m_lpPre;
    CClassLink*	m_lpNext;
    __SCLStaticData<_T>* m_lpBeginPtr;

public:
    CClassLink()
    {
        m_blLinked = FALSE;
        // Default to the class's own static data
        m_lpBeginPtr = &_T::m_sCLBegin;
        if(_T::m_sCLBegin.m_blAutoLink)
            Link();
    }
    virtual ~CClassLink()
    {
        Unlink();
    }

    inline BOOL	IsLinked() { return m_blLinked; }
    inline __SCLStaticData<_T>* GetBeginPtr() { return m_lpBeginPtr; }
    inline void SetBeginPtr(void* p) { m_lpBeginPtr = (__SCLStaticData<_T>*)p; }

    inline CClassLink*	GetPre() { return m_lpPre; }
    inline CClassLink*	GetNext() { return m_lpNext; }
    inline _T*			GetObj() { return (_T*)((ULONG_PTR)(this) - offsetof(_T, m_ClassLink)); }

    void	Link(BOOL blPushBack = TRUE, BOOL blForce = FALSE)
    {
        if(blForce == FALSE && m_blLinked)
            return;

        // Use the instance pointer so we can link to external modules
        __SCLStaticData<_T>* pData = m_lpBeginPtr;
        if(!pData) return;

        m_blLinked = TRUE;
        ++pData->m_lnCnt;

        if( pData->m_lpCLBegin == NULL )
        {
            pData->m_lpCLBegin = this;
            pData->m_lpCLEnd = this;

            m_lpPre = NULL;
            m_lpNext = NULL;
        }
        else
        {
            if(blPushBack)
            {
                CClassLink* pOldEnd = pData->m_lpCLEnd;
                pOldEnd->m_lpNext = this;
                pData->m_lpCLEnd = this;

                m_lpPre = pOldEnd;
                m_lpNext = NULL;
            }
            else
            {
                CClassLink* pOldBegin = pData->m_lpCLBegin;
                pOldBegin->m_lpPre = this;
                pData->m_lpCLBegin = this;

                m_lpPre = NULL;
                m_lpNext = pOldBegin;
            }
        }
    }

    void	Unlink()
    {
        if(m_blLinked == FALSE)
            return;

        __SCLStaticData<_T>* pData = m_lpBeginPtr;
        if(!pData) return;

        m_blLinked = FALSE;
        if(this == pData->m_lpCLCur)
        {
            pData->m_lpCLCur = m_lpNext;
            pData->m_dwFlag |= CL_FLAG_ERASED;
        }

        --pData->m_lnCnt;

        if( m_lpPre )
            m_lpPre->m_lpNext = m_lpNext;
        else
            pData->m_lpCLBegin = m_lpNext;

        if( m_lpNext )
            m_lpNext->m_lpPre = m_lpPre;
        else
            pData->m_lpCLEnd = m_lpPre;

        m_lpPre = m_lpNext = NULL;
    }
};