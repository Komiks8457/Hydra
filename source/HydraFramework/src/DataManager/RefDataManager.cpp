#include "RefDataManager.h"
#include "BSLib/AppLogger.h"
#include "BSLib/Database/DbManager.h"
#include "BSLib/Database/DbRowReader.h"

template<> HydraFramework::CRefDataManager* CSingletonT<HydraFramework::CRefDataManager>::s_pObject = NULL;

namespace HydraFramework
{
    CRefDataManager::CRefDataManager()
    {}

    int CRefDataManager::InitializeData()
    {
        if (!g_pDbMgr)
            return -65535;

        if (!InitializeObjChar())
            return -65534;

        if (!InitializeObjItem())
            return -65533;

        if (!InitializeSkillData())
            return -65532;

        return TRUE;
    }

    bool CRefDataManager::InitializeObjChar()
    {
        CDbRowReader reader;
        CDbConnection *pConnection = g_pDbMgr->GetConnection(SHARD);

        const stra_t &query("SELECT CMN.*, CHR.* FROM [dbo].[_RefObjChar] CHR INNER JOIN [dbo].[_RefObjCommon] "
                            "CMN ON CMN.Link = CHR.ID WHERE CMN.[Service] = 1 AND CMN.Bionic = 1 AND CMN.TypeID1 = 1 "
                            "ORDER BY CMN.ID");

        pConnection->ExecuteReader(reader, query.c_str());

        while (reader.FetchNext())
        {
            reader.Read<int>(); //Service

            RefObjChar charData;
            charData.m_ID = reader.Read<int>();
            charData.m_CodeName128 = reader.ReadStringA(128);
            charData.m_ObjName128 = reader.ReadStringA(128);
            charData.m_OrgObjCodeName128 = reader.ReadStringA(128);
            charData.m_NameStrID128 = reader.ReadStringA(128);
            charData.m_DescStrID128 = reader.ReadStringA(128);
            charData.m_CashItem = reader.Read<BYTE>();
            charData.m_Bionic = reader.Read<BYTE>();
            charData.m_TypeID.TypeID1 = reader.Read<BYTE>();
            charData.m_TypeID.TypeID2 = reader.Read<BYTE>();
            charData.m_TypeID.TypeID3 = reader.Read<BYTE>();
            charData.m_TypeID.TypeID4 = reader.Read<BYTE>();
            charData.m_DecayTime = reader.Read<int>();
            charData.m_Country = reader.Read<BYTE>();
            charData.m_Rarity = reader.Read<BYTE>();
            charData.m_CanTrade = reader.Read<BYTE>();
            charData.m_CanSell = reader.Read<BYTE>();
            charData.m_CanBuy = reader.Read<BYTE>();
            charData.m_CanBorrow = reader.Read<BYTE>();
            charData.m_CanDrop = reader.Read<BYTE>();
            charData.m_CanPick = reader.Read<BYTE>();
            charData.m_CanRepair = reader.Read<BYTE>();
            charData.m_CanRevive = reader.Read<BYTE>();
            charData.m_CanUse = reader.Read<BYTE>();
            charData.m_CanThrow = reader.Read<BYTE>();
            charData.m_Price = reader.Read<int>();
            charData.m_CostRepair = reader.Read<int>();
            charData.m_CostRevive = reader.Read<int>();
            charData.m_CostBorrow = reader.Read<int>();
            charData.m_KeepingFee = reader.Read<int>();
            charData.m_SellPrice = reader.Read<int>();
            charData.m_ReqLevelType1 = reader.Read<int>();
            charData.m_ReqLevel1 = reader.Read<BYTE>();
            charData.m_ReqLevelType2 = reader.Read<int>();
            charData.m_ReqLevel2 = reader.Read<BYTE>();
            charData.m_ReqLevelType3 = reader.Read<int>();
            charData.m_ReqLevel3 = reader.Read<BYTE>();
            charData.m_ReqLevelType4 = reader.Read<int>();
            charData.m_ReqLevel4 = reader.Read<BYTE>();
            charData.m_MaxContain = reader.Read<int>();
            charData.m_RegionInfo.RegionID = reader.Read<short>();
            charData.m_RegionInfo.Dir = reader.Read<short>();
            charData.m_RegionInfo.PosX = reader.Read<float>();
            charData.m_RegionInfo.PosY = reader.Read<float>();
            charData.m_RegionInfo.PosZ = reader.Read<float>();
            charData.m_Speed1 = reader.Read<short>();
            charData.m_Speed2 = reader.Read<short>();
            charData.m_Scale = reader.Read<int>();
            charData.m_BCHeight = reader.Read<short>();
            charData.m_BCRadius = reader.Read<short>();
            charData.m_EventID = reader.Read<int>();
            charData.m_AssocFileObj128 = reader.ReadStringA(128);
            charData.m_AssocFileDrop128 = reader.ReadStringA(128);
            charData.m_AssocFileIcon128 = reader.ReadStringA(128);
            charData.m_AssocFile1_128 = reader.ReadStringA(128);
            charData.m_AssocFile2_128 = reader.ReadStringA(128);

            reader.Read<int>(); //RefObjCommon.Link
            reader.Read<int>(); //RefObjChar.ID

            charData.m_Lvl = reader.Read<BYTE>();
            charData.m_CharGender = reader.Read<BYTE>();
            charData.m_MaxHP = reader.Read<int>();
            charData.m_MaxMP = reader.Read<int>();

            for (int i = 0; i < Resist::MAX_RESIST_TYPE; ++i)
                charData.m_Resist[i].Value = reader.Read<int>();

            charData.m_InventorySize = reader.Read<BYTE>();
            charData.m_CanStore_TID1 = reader.Read<BYTE>();
            charData.m_CanStore_TID2 = reader.Read<BYTE>();
            charData.m_CanStore_TID3 = reader.Read<BYTE>();
            charData.m_CanStore_TID4 = reader.Read<BYTE>();
            charData.m_CanBeVehicle = reader.Read<BYTE>();
            charData.m_CanControl = reader.Read<BYTE>();
            charData.m_DamagePortion = reader.Read<BYTE>();
            charData.m_MaxPassenger = reader.Read<short>();
            charData.m_AssocTactics = reader.Read<int>();
            charData.m_PD = reader.Read<int>();
            charData.m_MD = reader.Read<int>();
            charData.m_PAR = reader.Read<int>();
            charData.m_MAR = reader.Read<int>();
            charData.m_ER = reader.Read<int>();
            charData.m_BR = reader.Read<int>();
            charData.m_HR = reader.Read<int>();
            charData.m_CHR = reader.Read<int>();
            charData.m_ExpToGive = reader.Read<int>();
            charData.m_CreepType = reader.Read<int>();
            charData.m_Knockdown = reader.Read<BYTE>();
            charData.m_KO_RecoverTime = reader.Read<int>();

            for (int i = 0; i < DefaultSkill::MAX_DEFAULT_SKILL; ++i)
                charData.m_DefaultSkill[i].Value = reader.Read<int>();

            charData.m_TextureType = reader.Read<BYTE>();

            for (int i = 0; i < Except::MAX_EXCEPT_TYPE; ++i)
                charData.m_Except[i].Value = reader.Read<int>();

            reader.Read<int>(); //RefObjChar.Link

            m_CharData[charData.m_ID] = charData;
        }

        if (m_CharData.empty())
        {
            g_pDbMgr->Release(SHARD, pConnection);
            reader.Close();
            return false;
        }

        PutLog(FATAL, "Loaded %d RefObjChar entries.", m_CharData.size());
        g_pDbMgr->Release(SHARD, pConnection);
        reader.Close();
        return true;
    }

    bool CRefDataManager::InitializeObjItem()
    {
        CDbRowReader reader;
        CDbConnection *pConnection = g_pDbMgr->GetConnection(SHARD);

        const stra_t &query("SELECT CMN.*, ITEM.* FROM [dbo].[_RefObjItem] ITEM INNER JOIN [dbo].[_RefObjCommon] "
                            "CMN ON CMN.Link = ITEM.ID WHERE CMN.[Service] = 1 AND CMN.TypeID1 = 3 ORDER BY CMN.ID");

        pConnection->ExecuteReader(reader, query.c_str());

        while (reader.FetchNext())
        {
            reader.Read<int>(); //Service

            RefObjItem itemData;
            itemData.m_ID = reader.Read<int>();
            itemData.m_CodeName128 = reader.ReadStringA(128);
            itemData.m_ObjName128 = reader.ReadStringA(128);
            itemData.m_OrgObjCodeName128 = reader.ReadStringA(128);
            itemData.m_NameStrID128 = reader.ReadStringA(128);
            itemData.m_DescStrID128 = reader.ReadStringA(128);
            itemData.m_CashItem = reader.Read<BYTE>();
            itemData.m_Bionic = reader.Read<BYTE>();
            itemData.m_TypeID.TypeID1 = reader.Read<BYTE>();
            itemData.m_TypeID.TypeID2 = reader.Read<BYTE>();
            itemData.m_TypeID.TypeID3 = reader.Read<BYTE>();
            itemData.m_TypeID.TypeID4 = reader.Read<BYTE>();
            itemData.m_DecayTime = reader.Read<int>();
            itemData.m_Country = reader.Read<BYTE>();
            itemData.m_Rarity = reader.Read<BYTE>();
            itemData.m_CanTrade = reader.Read<BYTE>();
            itemData.m_CanSell = reader.Read<BYTE>();
            itemData.m_CanBuy = reader.Read<BYTE>();
            itemData.m_CanBorrow = reader.Read<BYTE>();
            itemData.m_CanDrop = reader.Read<BYTE>();
            itemData.m_CanPick = reader.Read<BYTE>();
            itemData.m_CanRepair = reader.Read<BYTE>();
            itemData.m_CanRevive = reader.Read<BYTE>();
            itemData.m_CanUse = reader.Read<BYTE>();
            itemData.m_CanThrow = reader.Read<BYTE>();
            itemData.m_Price = reader.Read<int>();
            itemData.m_CostRepair = reader.Read<int>();
            itemData.m_CostRevive = reader.Read<int>();
            itemData.m_CostBorrow = reader.Read<int>();
            itemData.m_KeepingFee = reader.Read<int>();
            itemData.m_SellPrice = reader.Read<int>();
            itemData.m_ReqLevelType1 = reader.Read<int>();
            itemData.m_ReqLevel1 = reader.Read<BYTE>();
            itemData.m_ReqLevelType2 = reader.Read<int>();
            itemData.m_ReqLevel2 = reader.Read<BYTE>();
            itemData.m_ReqLevelType3 = reader.Read<int>();
            itemData.m_ReqLevel3 = reader.Read<BYTE>();
            itemData.m_ReqLevelType4 = reader.Read<int>();
            itemData.m_ReqLevel4 = reader.Read<BYTE>();
            itemData.m_MaxContain = reader.Read<int>();
            itemData.m_RegionInfo.RegionID = reader.Read<short>();
            itemData.m_RegionInfo.Dir = reader.Read<short>();
            itemData.m_RegionInfo.PosX = reader.Read<float>();
            itemData.m_RegionInfo.PosY = reader.Read<float>();
            itemData.m_RegionInfo.PosZ = reader.Read<float>();
            itemData.m_Speed1 = reader.Read<short>();
            itemData.m_Speed2 = reader.Read<short>();
            itemData.m_Scale = reader.Read<int>();
            itemData.m_BCHeight = reader.Read<short>();
            itemData.m_BCRadius = reader.Read<short>();
            itemData.m_EventID = reader.Read<int>();
            itemData.m_AssocFileObj128 = reader.ReadStringA(128);
            itemData.m_AssocFileDrop128 = reader.ReadStringA(128);
            itemData.m_AssocFileIcon128 = reader.ReadStringA(128);
            itemData.m_AssocFile1_128 = reader.ReadStringA(128);
            itemData.m_AssocFile2_128 = reader.ReadStringA(128);

            reader.Read<int>(); //RefObjCommon.Link
            reader.Read<int>(); //RefObjItem.ID

            itemData.m_MaxStack = reader.Read<int>();
            itemData.m_ReqGender  = reader.Read<BYTE>();
            itemData.m_ReqStr = reader.Read<int>();
            itemData.m_ReqInt = reader.Read<int>();
            itemData.m_ItemClass = reader.Read<BYTE>();
            itemData.m_SetID = reader.Read<int>();
            itemData.m_Dur_L = reader.Read<float>();
            itemData.m_Dur_U = reader.Read<float>();
            itemData.m_PD_L = reader.Read<float>();
            itemData.m_PD_U = reader.Read<float>();
            itemData.m_PDInc = reader.Read<float>();
            itemData.m_ER_L = reader.Read<float>();
            itemData.m_ER_U = reader.Read<float>();
            itemData.m_ERInc = reader.Read<float>();
            itemData.m_PAR_L = reader.Read<float>();
            itemData.m_PAR_U = reader.Read<float>();
            itemData.m_PARInc = reader.Read<float>();
            itemData.m_BR_L = reader.Read<float>();
            itemData.m_BR_U = reader.Read<float>();
            itemData.m_MD_L = reader.Read<float>();
            itemData.m_MD_U = reader.Read<float>();
            itemData.m_MDInc = reader.Read<float>();
            itemData.m_MAR_L = reader.Read<float>();
            itemData.m_MAR_U = reader.Read<float>();
            itemData.m_MARInc = reader.Read<float>();
            itemData.m_PDStr_L = reader.Read<float>();
            itemData.m_PDStr_U = reader.Read<float>();
            itemData.m_MDInt_L = reader.Read<float>();
            itemData.m_MDInt_U = reader.Read<float>();
            itemData.m_Quivered = reader.Read<bool>();
            itemData.m_Ammo1_TID4 = reader.Read<BYTE>();
            itemData.m_Ammo2_TID4 = reader.Read<BYTE>();
            itemData.m_Ammo3_TID4 = reader.Read<BYTE>();
            itemData.m_Ammo4_TID4 = reader.Read<BYTE>();
            itemData.m_Ammo5_TID4 = reader.Read<BYTE>();
            itemData.m_SpeedClass = reader.Read<BYTE>();
            itemData.m_TwoHanded = reader.Read<bool>();
            itemData.m_Range = reader.Read<short>();
            itemData.m_PAttackMin_L = reader.Read<float>();
            itemData.m_PAttackMin_U = reader.Read<float>();
            itemData.m_PAttackMax_L = reader.Read<float>();
            itemData.m_PAttackMax_U = reader.Read<float>();
            itemData.m_PAttackInc = reader.Read<float>();
            itemData.m_MAttackMin_L = reader.Read<float>();
            itemData.m_MAttackMin_U = reader.Read<float>();
            itemData.m_MAttackMax_L = reader.Read<float>();
            itemData.m_MAttackMax_U = reader.Read<float>();
            itemData.m_MAttackInc = reader.Read<float>();
            itemData.m_PAStrMin_L = reader.Read<float>();
            itemData.m_PAStrMin_U = reader.Read<float>();
            itemData.m_PAStrMax_L = reader.Read<float>();
            itemData.m_PAStrMax_U = reader.Read<float>();
            itemData.m_MAInt_Min_L = reader.Read<float>();
            itemData.m_MAInt_Min_U = reader.Read<float>();
            itemData.m_MAInt_Max_L = reader.Read<float>();
            itemData.m_MAInt_Max_U = reader.Read<float>();
            itemData.m_HR_L = reader.Read<float>();
            itemData.m_HR_U = reader.Read<float>();
            itemData.m_HRInc = reader.Read<float>();
            itemData.m_CHR_L = reader.Read<float>();
            itemData.m_CHR_U = reader.Read<float>();

            for (int i = 0; i < ItemParam::MAX_PARAM; ++i)
            {
                itemData.m_Param[i].Value = reader.Read<int>();
                itemData.m_Param[i].Desc = reader.ReadStringA(128);
            }

            itemData.m_MaxMagicOptCount = reader.Read<BYTE>();
            itemData.m_ChildItemCount = reader.Read<BYTE>();

            reader.Read<int>(); //RefObjItem.Link

            m_ItemData[itemData.m_ID] = itemData;
        }

        if (m_ItemData.empty())
        {
            g_pDbMgr->Release(SHARD, pConnection);
            reader.Close();
            return false;
        }

        g_pDbMgr->Release(SHARD, pConnection);
        reader.Close();
        return true;
    }

    bool CRefDataManager::InitializeObjStruct()
    {
        CDbRowReader reader;
        CDbConnection *pConnection = g_pDbMgr->GetConnection(SHARD);

        const stra_t &query("SELECT CMN.*, STRUCT.* FROM [dbo].[_RefObjStruct] STRUCT INNER JOIN [dbo].[_RefObjCommon] "
                            "CMN ON CMN.Link = STRUCT.ID WHERE CMN.[Service] = 1 AND CMN.TypeID1 = 4 ORDER BY CMN.ID");

        pConnection->ExecuteReader(reader, query.c_str());

        while (reader.FetchNext())
        {
            reader.Read<int>(); //Service

            RefObjStruct structData;
            structData.m_ID = reader.Read<int>();
            structData.m_CodeName128 = reader.ReadStringA(128);
            structData.m_ObjName128 = reader.ReadStringA(128);
            structData.m_OrgObjCodeName128 = reader.ReadStringA(128);
            structData.m_NameStrID128 = reader.ReadStringA(128);
            structData.m_DescStrID128 = reader.ReadStringA(128);
            structData.m_CashItem = reader.Read<BYTE>();
            structData.m_Bionic = reader.Read<BYTE>();
            structData.m_TypeID.TypeID1 = reader.Read<BYTE>();
            structData.m_TypeID.TypeID2 = reader.Read<BYTE>();
            structData.m_TypeID.TypeID3 = reader.Read<BYTE>();
            structData.m_TypeID.TypeID4 = reader.Read<BYTE>();
            structData.m_DecayTime = reader.Read<int>();
            structData.m_Country = reader.Read<BYTE>();
            structData.m_Rarity = reader.Read<BYTE>();
            structData.m_CanTrade = reader.Read<BYTE>();
            structData.m_CanSell = reader.Read<BYTE>();
            structData.m_CanBuy = reader.Read<BYTE>();
            structData.m_CanBorrow = reader.Read<BYTE>();
            structData.m_CanDrop = reader.Read<BYTE>();
            structData.m_CanPick = reader.Read<BYTE>();
            structData.m_CanRepair = reader.Read<BYTE>();
            structData.m_CanRevive = reader.Read<BYTE>();
            structData.m_CanUse = reader.Read<BYTE>();
            structData.m_CanThrow = reader.Read<BYTE>();
            structData.m_Price = reader.Read<int>();
            structData.m_CostRepair = reader.Read<int>();
            structData.m_CostRevive = reader.Read<int>();
            structData.m_CostBorrow = reader.Read<int>();
            structData.m_KeepingFee = reader.Read<int>();
            structData.m_SellPrice = reader.Read<int>();
            structData.m_ReqLevelType1 = reader.Read<int>();
            structData.m_ReqLevel1 = reader.Read<BYTE>();
            structData.m_ReqLevelType2 = reader.Read<int>();
            structData.m_ReqLevel2 = reader.Read<BYTE>();
            structData.m_ReqLevelType3 = reader.Read<int>();
            structData.m_ReqLevel3 = reader.Read<BYTE>();
            structData.m_ReqLevelType4 = reader.Read<int>();
            structData.m_ReqLevel4 = reader.Read<BYTE>();
            structData.m_MaxContain = reader.Read<int>();
            structData.m_RegionInfo.RegionID = reader.Read<short>();
            structData.m_RegionInfo.Dir = reader.Read<short>();
            structData.m_RegionInfo.PosX = reader.Read<float>();
            structData.m_RegionInfo.PosY = reader.Read<float>();
            structData.m_RegionInfo.PosZ = reader.Read<float>();
            structData.m_Speed1 = reader.Read<short>();
            structData.m_Speed2 = reader.Read<short>();
            structData.m_Scale = reader.Read<int>();
            structData.m_BCHeight = reader.Read<short>();
            structData.m_BCRadius = reader.Read<short>();
            structData.m_EventID = reader.Read<int>();
            structData.m_AssocFileObj128 = reader.ReadStringA(128);
            structData.m_AssocFileDrop128 = reader.ReadStringA(128);
            structData.m_AssocFileIcon128 = reader.ReadStringA(128);
            structData.m_AssocFile1_128 = reader.ReadStringA(128);
            structData.m_AssocFile2_128 = reader.ReadStringA(128);

            reader.Read<int>(); //RefObjCommon.Link
            reader.Read<int>(); //RefObjStruct.ID
            reader.Read<int>(); //RefObjStruct.Dummy_Data

            m_StructData[structData.m_ID] = structData;
        }

        if (m_ItemData.empty())
        {
            g_pDbMgr->Release(SHARD, pConnection);
            reader.Close();
            return false;
        }

        g_pDbMgr->Release(SHARD, pConnection);
        reader.Close();
        return true;
    }

    bool CRefDataManager::InitializeSkillData()
    {
        CDbRowReader reader;
        CDbConnection *pConnection = g_pDbMgr->GetConnection(SHARD);

        const stra_t &query("SELECT * FROM [dbo].[_RefSkill] WHERE [Service] = 1 ORDER BY ID");

        pConnection->ExecuteReader(reader, query.c_str());

        while (reader.FetchNext())
        {
            RefSkill skillData;
            reader.Read<int>(); //Service
            skillData.m_ID = reader.Read<int>();
            skillData.m_GroupID = reader.Read<int>();
            skillData.m_Basic_Code = reader.ReadStringA(128);
            skillData.m_Basic_Name = reader.ReadStringA(128);
            skillData.m_Basic_Group = reader.ReadStringA(128);
            skillData.m_Basic_Original = reader.Read<int>();
            skillData.m_Basic_Level = reader.Read<BYTE>();
            skillData.m_Basic_Activity = reader.Read<BYTE>();
            skillData.m_Basic_ChainCode = reader.Read<int>();
            skillData.m_Basic_RecycleCost = reader.Read<int>();
            skillData.m_Action_PreparingTime = reader.Read<int>();
            skillData.m_Action_CastingTime = reader.Read<int>();
            skillData.m_Action_ActionDuration = reader.Read<int>();
            skillData.m_Action_ReuseDelay = reader.Read<int>();
            skillData.m_Action_CoolTime = reader.Read<int>();
            skillData.m_Action_FlyingSpeed = reader.Read<int>();
            skillData.m_Action_Interruptable = reader.Read<BYTE>();
            skillData.m_Action_Overlap = reader.Read<int>();
            skillData.m_Action_AutoAttackType = reader.Read<BYTE>();
            skillData.m_Action_InTown = reader.Read<BYTE>();
            skillData.m_Action_Range = reader.Read<short>();
            skillData.m_Target_Required = reader.Read<BYTE>();
            skillData.m_TargetType_Animal = reader.Read<BYTE>();
            skillData.m_TargetType_Land = reader.Read<BYTE>();
            skillData.m_TargetType_Building = reader.Read<BYTE>();
            skillData.m_TargetGroup_Self = reader.Read<BYTE>();
            skillData.m_TargetGroup_Ally = reader.Read<BYTE>();
            skillData.m_TargetGroup_Party = reader.Read<BYTE>();
            skillData.m_TargetGroup_Enemy_M = reader.Read<BYTE>();
            skillData.m_TargetGroup_Enemy_P = reader.Read<BYTE>();
            skillData.m_TargetGroup_Neutral = reader.Read<BYTE>();
            skillData.m_TargetGroup_DontCare = reader.Read<BYTE>();
            skillData.m_TargetEtc_SelectDeadBody = reader.Read<BYTE>();
            skillData.m_ReqCommon_Mastery1 = reader.Read<int>();
            skillData.m_ReqCommon_Mastery2 = reader.Read<int>();
            skillData.m_ReqCommon_MasteryLevel1 = reader.Read<BYTE>();
            skillData.m_ReqCommon_MasteryLevel2 = reader.Read<BYTE>();
            skillData.m_ReqCommon_Str = reader.Read<short>();
            skillData.m_ReqCommon_Int = reader.Read<short>();
            skillData.m_ReqLearn_Skill1 = reader.Read<int>();
            skillData.m_ReqLearn_Skill2 = reader.Read<int>();
            skillData.m_ReqLearn_Skill3 = reader.Read<int>();
            skillData.m_ReqLearn_SkillLevel1 = reader.Read<BYTE>();
            skillData.m_ReqLearn_SkillLevel2 = reader.Read<BYTE>();
            skillData.m_ReqLearn_SkillLevel3 = reader.Read<BYTE>();
            skillData.m_ReqLearn_SP = reader.Read<int>();
            skillData.m_ReqLearn_Race = reader.Read<BYTE>();
            skillData.m_Req_Restriction1 = reader.Read<BYTE>();
            skillData.m_Req_Restriction2 = reader.Read<BYTE>();
            skillData.m_ReqCast_Weapon1 = reader.Read<BYTE>();
            skillData.m_ReqCast_Weapon2 = reader.Read<BYTE>();
            skillData.m_Consume_HP = reader.Read<short>();
            skillData.m_Consume_MP = reader.Read<int>();
            skillData.m_Consume_HPRatio = reader.Read<short>();
            skillData.m_Consume_MPRatio = reader.Read<short>();
            skillData.m_Consume_WHAN = reader.Read<BYTE>();
            skillData.m_UI_SkillTab = reader.Read<BYTE>();
            skillData.m_UI_SkillPage = reader.Read<BYTE>();
            skillData.m_UI_SkillColumn = reader.Read<BYTE>();
            skillData.m_UI_SkillRow = reader.Read<BYTE>();
            skillData.m_UI_IconFile = reader.ReadStringA(128);
            skillData.m_UI_SkillName = reader.ReadStringA(128);
            skillData.m_UI_SkillToolTip = reader.ReadStringA(128);
            skillData.m_UI_SkillToolTip_Desc = reader.ReadStringA(128);
            skillData.m_UI_SkillStudy_Desc = reader.ReadStringA(128);
            skillData.m_AI_AttackChance = reader.Read<short>();
            skillData.m_AI_SkillType = reader.Read<BYTE>();

            for (int i = 0; i < SkillParam::MAX_SKILL_PARAM; ++i)
                skillData.m_Param[i].Value = reader.Read<int>();

            m_SkillData[skillData.m_ID] = skillData;
        }

        if (m_SkillData.empty())
        {
            g_pDbMgr->Release(SHARD, pConnection);
            reader.Close();
            return false;
        }

        g_pDbMgr->Release(SHARD, pConnection);
        reader.Close();
        return true;
    }

    RefObjChar *CRefDataManager::GetRefCharData(DWORD dwID)
    {
        ACS_SCOPED_LOCK(m_cs);

        if (m_CharData.find(dwID) == m_CharData.end())
            return NULL;

        return &m_CharData[dwID];
    }

    RefObjChar *CRefDataManager::GetRefCharData(const stra_t &codename)
    {
        ACS_SCOPED_LOCK(m_cs);

        for (CharData::iterator it = m_CharData.begin(); it != m_CharData.end(); ++it)
        {
            if (it->second.m_CodeName128 == codename)
                return &it->second;
        }

        return NULL;
    }

    RefObjItem *CRefDataManager::GetRefItemData(DWORD dwID)
    {
        ACS_SCOPED_LOCK(m_cs);

        if (m_ItemData.find(dwID) == m_ItemData.end())
            return NULL;

        return &m_ItemData[dwID];
    }

    RefObjItem *CRefDataManager::GetRefItemData(const stra_t &codename)
    {
        ACS_SCOPED_LOCK(m_cs);

        for (ItemData::iterator it = m_ItemData.begin(); it != m_ItemData.end(); ++it)
        {
            if (it->second.m_CodeName128 == codename)
                return &it->second;
        }

        return NULL;
    }

    RefObjStruct *CRefDataManager::GetRefStructData(DWORD dwID)
    {
        ACS_SCOPED_LOCK(m_cs);

        if (m_StructData.find(dwID) == m_StructData.end())
            return NULL;

        return &m_StructData[dwID];
    }

    RefObjStruct *CRefDataManager::GetRefStructData(const stra_t &codename)
    {
        ACS_SCOPED_LOCK(m_cs);

        for (StructData ::iterator it = m_StructData.begin(); it != m_StructData.end(); ++it)
        {
            if (it->second.m_CodeName128 == codename)
                return &it->second;
        }

        return NULL;
    }

    RefSkill *CRefDataManager::GetRefSkillData(DWORD dwID)
    {
        ACS_SCOPED_LOCK(m_cs);

        if (m_SkillData.find(dwID) == m_SkillData.end())
            return NULL;

        return &m_SkillData[dwID];
    }

    RefSkill *CRefDataManager::GetRefSkillData(const stra_t &codename)
    {
        ACS_SCOPED_LOCK(m_cs);

        for (SkillData::iterator it = m_SkillData.begin(); it != m_SkillData.end(); ++it)
        {
            if (it->second.m_Basic_Code == codename)
                return &it->second;
        }

        return NULL;
    }

    void CRefDataManager::CleanUp()
    {
        m_CharData.clear();
        m_ItemData.clear();
        m_SkillData.clear();
    }
}