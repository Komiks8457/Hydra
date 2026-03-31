#pragma once

#ifndef REFDATAMANAGER_H
#define REFDATAMANAGER_H

#include "pch.h"
#include "BSLib/Pattern/Singleton.h"
#include "BSLib/CriticalSectionScoped.h"

#include "RefObjCommon.h"
#include "RefObjChar.h"
#include "RefObjItem.h"
#include "RefObjStruct.h"
#include "RefSkill.h"

#define GETCHARDATA(x)  (g_pRDM ? g_pRDM->GetRefCharData(x) : NULL)
#define GETITEMDATA(x)  (g_pRDM ? g_pRDM->GetRefItemData(x) : NULL)
#define GETSTRUCTDATA(x)  (g_pRDM ? g_pRDM->GetRefStructData(x) : NULL)
#define GETSKILLDATA(x) (g_pRDM ? g_pRDM->GetRefSkillData(x) : NULL)

namespace HydraFramework
{
    typedef std::map<DWORD, RefObjChar> CharData;
    typedef std::map<DWORD, RefObjItem> ItemData;
    typedef std::map<DWORD, RefObjStruct> StructData;
    typedef std::map<DWORD, RefSkill> SkillData;

    class CRefDataManager : public CSingletonT<CRefDataManager> {
        friend class CSingletonT<CRefDataManager>;

    public:
        static bool CreateInstance()
        {
            if (GetSingletonPtr()) return false;
            static CRefDataManager init;
            return true;
        }

        int InitializeData();
        RefObjChar *GetRefCharData(DWORD dwID);
        RefObjChar *GetRefCharData(const stra_t &codename);
        RefObjItem *GetRefItemData(DWORD dwID);
        RefObjItem *GetRefItemData(const stra_t &codename);
        RefObjStruct *GetRefStructData(DWORD dwID);
        RefObjStruct *GetRefStructData(const stra_t &codename);
        RefSkill *GetRefSkillData(DWORD dwID);
        RefSkill *GetRefSkillData(const stra_t &codename);

    private:
        bool InitializeObjChar();
        bool InitializeObjItem();
        bool InitializeObjStruct();
        bool InitializeSkillData();
        void CleanUp();

        CRefDataManager();
        CRefDataManager(const CRefDataManager&);
        CRefDataManager& operator=(const CRefDataManager&);
        ~CRefDataManager() { CleanUp(); };

    private:
        CCriticalSection m_cs;
        CharData m_CharData;
        ItemData m_ItemData;
        StructData m_StructData;
        SkillData m_SkillData;
    };
}

#define g_pRDM (&HydraFramework::CRefDataManager::GetSingleton())

#endif
