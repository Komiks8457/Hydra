#pragma once

class CCriticalSection {
public:
    CCriticalSection() { InitializeCriticalSection(&m_cs); }
    ~CCriticalSection() { DeleteCriticalSection(&m_cs); }

    __forceinline void Enter() { EnterCriticalSection(&m_cs); }
    __forceinline void Leave() { LeaveCriticalSection(&m_cs); }

private:
    CCriticalSection(const CCriticalSection&);
    CCriticalSection& operator=(const CCriticalSection&);

    CRITICAL_SECTION m_cs;
};

class CCriticalSectionScoped {
public:
    CCriticalSectionScoped(CCriticalSection& ccs) : m_ccs(ccs) {  m_ccs.Enter(); }
    ~CCriticalSectionScoped() { m_ccs.Leave(); }

private:
    CCriticalSectionScoped(const CCriticalSectionScoped&);
    CCriticalSectionScoped& operator=(const CCriticalSectionScoped&);

    CCriticalSection& m_ccs;
};

#define ACS_SCOPED_LOCK(cs) CCriticalSectionScoped cslock(cs)