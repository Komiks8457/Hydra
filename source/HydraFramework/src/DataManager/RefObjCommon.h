#pragma once

#ifndef REFOBJCOMMON_H
#define REFOBJCOMMON_H

#include "pch.h"

namespace HydraFramework
{
    struct RegionInfo
    {
        SHORT RegionID;
        SHORT Dir;
        FLOAT PosX;
        FLOAT PosY;
        FLOAT PosZ;

        RegionInfo() : RegionID(0), Dir(0), PosX(0), PosY(0), PosZ(0)
        {}
    };

    template<BYTE TID1, BYTE TID2, BYTE TID3, BYTE TID4>
    class TID
    {};

    struct TypeId {
    public:
        template<BYTE TID1, BYTE TID2, BYTE TID3, BYTE TID4>
        bool Is(TID<TID1, TID2, TID3, TID4> tid) const {
            return ((TypeID1 / 16) == TID1) && ((TypeID2 / 4) == TID2) && TypeID3 == TID3 && TypeID4 == TID4;
        }

        bool Is(BYTE TID1, BYTE TID2, BYTE TID3, BYTE TID4) const {
            return ((TypeID1 / 16) == TID1 && (TypeID2 / 4) == TID2 && TypeID3 == TID3 && TypeID4 == TID4);
        }

        bool operator==(TypeId type) const {
            return ((TypeID1 / 16) == (type.TypeID1 / 16) && (TypeID2 / 4) == (type.TypeID2 / 4) &&
                    TypeID3 == type.TypeID3 && TypeID4 == type.TypeID4);
        }
    public:
        BYTE TypeID1;
        BYTE TypeID2;
        BYTE TypeID3;
        BYTE TypeID4;
    };

    struct RefObjCommon {
        friend class CRefDataManager;

    private:
        int m_ID;
        stra_t m_CodeName128;
        stra_t m_ObjName128;
        stra_t m_OrgObjCodeName128;
        stra_t m_NameStrID128;
        stra_t m_DescStrID128;
        bool m_CashItem;
        bool m_Bionic;
        TypeId m_TypeID;
        int m_DecayTime;
        BYTE m_Country;
        BYTE m_Rarity;
        BYTE m_CanTrade;
        BYTE m_CanSell;
        BYTE m_CanBuy;
        BYTE m_CanBorrow;
        BYTE m_CanDrop;
        BYTE m_CanPick;
        BYTE m_CanRepair;
        BYTE m_CanRevive;
        BYTE m_CanUse;
        BYTE m_CanThrow;
        int m_Price;
        int m_CostRepair;
        int m_CostRevive;
        int m_CostBorrow;
        int m_KeepingFee;
        int m_SellPrice;
        int m_ReqLevelType1;
        BYTE m_ReqLevel1;
        int m_ReqLevelType2;
        BYTE m_ReqLevel2;
        int m_ReqLevelType3;
        BYTE m_ReqLevel3;
        int m_ReqLevelType4;
        BYTE m_ReqLevel4;
        int m_MaxContain;
        RegionInfo m_RegionInfo;
        short m_Speed1;
        short m_Speed2;
        int m_Scale;
        short m_BCHeight;
        short m_BCRadius;
        int m_EventID;
        stra_t m_AssocFileObj128;
        stra_t m_AssocFileDrop128;
        stra_t m_AssocFileIcon128;
        stra_t m_AssocFile1_128;
        stra_t m_AssocFile2_128;

    protected:
        RefObjCommon() : m_ID(0), m_CashItem(false), m_Bionic(false), m_TypeID(), m_DecayTime(0), m_Country(0),
                         m_Rarity(0), m_CanTrade(0), m_CanSell(0), m_CanBuy(0), m_CanBorrow(0), m_CanDrop(0),
                         m_CanPick(0), m_CanRepair(0), m_CanRevive(0), m_CanUse(0), m_CanThrow(0), m_Price(0),
                         m_CostRepair(0), m_CostRevive(0), m_CostBorrow(0), m_KeepingFee(0), m_SellPrice(0),
                         m_ReqLevelType1(0), m_ReqLevel1(0), m_ReqLevelType2(0), m_ReqLevel2(0), m_ReqLevelType3(0),
                         m_ReqLevel3(0), m_ReqLevelType4(0), m_ReqLevel4(0), m_MaxContain(0), m_RegionInfo(),
                         m_Speed1(0), m_Speed2(0), m_Scale(0), m_BCHeight(0), m_BCRadius(0), m_EventID(0)
        {}

        bool Is(BYTE a1, BYTE a2, BYTE a3, BYTE a4) const
        {
            return m_TypeID.TypeID1 == a1 &&
                   m_TypeID.TypeID2 == a2 &&
                   m_TypeID.TypeID3 == a3 &&
                   m_TypeID.TypeID4 == a4;
        }

    public:
        int ObjID() const { return m_ID; }

        const stra_t &CodeName128() const { return m_CodeName128; }

        const stra_t &ObjName128() const { return m_ObjName128; }

        const stra_t &OrgObjCodeName128() const { return m_OrgObjCodeName128; }

        const stra_t &NameStrID128() const { return m_NameStrID128; }

        const stra_t &DescStrID128() const { return m_DescStrID128; }

        bool IsCashItem() const { return m_CashItem; }

        bool IsBionic() const { return m_Bionic; }

        TypeId GetPermanentData() const { return m_TypeID; }

        DWORD GetTypeID() const
        {
            DWORD result = 0;
            result |= m_CashItem + m_Bionic;
            result |= (m_TypeID.TypeID1 << 4);
            result |= ((m_TypeID.TypeID2 * 4) << 8);
            result |= (m_TypeID.TypeID3 << 16);
            result |= (m_TypeID.TypeID4 << 24);
            return result;
        }

        int DecayTime() const { return m_DecayTime; }

        BYTE Country() const { return m_Country; }

        BYTE Rarity() const { return m_Rarity; }

        BYTE CanTrade() const { return m_CanTrade; }

        BYTE CanSell() const { return m_CanSell; }

        BYTE CanBuy() const { return m_CanBuy; }

        BYTE CanBorrow() const { return m_CanBorrow; }

        BYTE CanDrop() const { return m_CanDrop; }

        BYTE CanPick() const { return m_CanPick; }

        BYTE CanRepair() const { return m_CanRepair; }

        BYTE CanRevive() const { return m_CanRevive; }

        BYTE CanUse() const { return m_CanUse; }

        BYTE CanThrow() const { return m_CanThrow; }

        int Price() const { return m_Price; }

        int CostRepair() const { return m_CostRepair; }

        int CostRevive() const { return m_CostRevive; }

        int CostBorrow() const { return m_CostBorrow; }

        int KeepingFee() const { return m_KeepingFee; }

        int SellPrice() const { return m_SellPrice; }

        int ReqLevelType1() const { return m_ReqLevelType1; }

        BYTE ReqLevel1() const { return m_ReqLevel1; }

        int ReqLevelType2() const { return m_ReqLevelType2; }

        BYTE ReqLevel2() const { return m_ReqLevel2; }

        int ReqLevelType3() const { return m_ReqLevelType3; }

        BYTE ReqLevel3() const { return m_ReqLevel3; }

        int ReqLevelType4() const { return m_ReqLevelType4; }

        BYTE ReqLevel4() const { return m_ReqLevel4; }

        int MaxContain() const { return m_MaxContain; }

        const RegionInfo &RegionInfo() const { return m_RegionInfo; }

        short Speed1() const { return m_Speed1; }

        short Speed2() const { return m_Speed2; }

        int Scale() const { return m_Scale; }

        short BCHeight() const { return m_BCHeight; }

        short BCRadius() const { return m_BCRadius; }

        int EventID() const { return m_EventID; }

        const stra_t &AssocFileObj128() const { return m_AssocFileObj128; }

        const stra_t &AssocFileDrop128() const { return m_AssocFileDrop128; }

        const stra_t &AssocFileIcon128() const { return m_AssocFileIcon128; }

        const stra_t &AssocFile1_128() const { return m_AssocFile1_128; }

        const stra_t &AssocFile2_128() const { return m_AssocFile2_128; }

        bool IsPC() const {
            return Is(1,1,0,0);
        };

        bool IsMob() const {
            return (Is(1,2,1,0) ||
                    Is(1,2,1,1) ||
                    (Is(1,2,1,4) && m_DecayTime != 0) ||
                    Is(1,2,3,6) ||
                    Is(1,2,3,7) ||
                    Is(1,2,3,8));
        }

        bool IsMobThief() const {
            return Is(1,2,1,2);
        }

        bool IsMobHunter() const {
            return Is(1,2,1,3);
        }

        bool IsJobNPC() const {
            return (IsMobThief() || IsMobHunter());
        }

        bool IsStructure() const {
            return (Is(1,2,1,4) || Is(1,2,1,8) || Is(1,2,4,2));
        }

        bool IsMobEvenPandora() const {
            return Is(1,2,1,5); //One and only
        }

        bool IsTradeCOS_UNK() const {
            return Is(1,2,1,6);
        }

        bool IsTradeCOSThief() const {
            return Is(1,2,1,7); //?
        }

        bool IsNPC() const {
            return Is(1,2,2,0);
        }

        bool IsStructPulley() const {
            return Is(1,2,2,1);
        }

        bool IsNPCBossDungeon() const {
            return (Is(1,2,2,2) || Is(1,2,2,3));
        }

        bool IsCOS() const {
            return (Is(1,2,3,0) || Is(1,2,3,1));
        }

        bool IsTradeCOS() const {
            return Is(1,2,3,2);
        }

        bool IsPet() const {
            return Is(1,2,3,3);
        }

        bool IsGrabPet() const {
            return Is(1,2,3,4);
        }

        bool IsMercenary() const {
            return Is(1,2,3,5);
        }

        bool IsFellowPet() const {
            return Is(1,2,3,9);
        }

        bool IsSiegeCOS() const {
            return (Is(1,2,3,9) || Is(1,2,3,10));
        }

        bool IsSiegeGuardCOS() const {
            return (Is(1,2,4,1) || Is(1,2,4,4));
        }

        bool IsSiegeUniques() const {
            return Is(1,2,4,3);
        }

        bool IsSiegeStructHeart() const {
            return Is(1,2,5,1);
        }

        bool IsSiegeStructTower() const {
            return Is(1,2,5,2);
        }

        bool IsSiegeStructGate() const {
            return Is(1,2,5,3);
        }

        bool IsSiegeStructCommandCamp() const {
            return Is(1,2,5,4);
        }

        bool IsSiegeStructDefensivePos() const {
            return Is(1,2,5,5);
        }

        bool IsSiegeStructBarricade() const {
            return Is(1,2,5,6);
        }

        bool IsMuhanTower() const {
            return Is(1,2,6,0);
        }

        bool IsMuhanTreasureBox() const {
            return Is(1,2,7,0);
        }

        bool IsSurvivalArenaSafeZone() const {
            return Is(1,2,8,0);
        }

        bool IsArmor() const {
            return (Is(3,1,1,1) ||
                    Is(3,1,1,2) ||
                    Is(3,1,1,3) ||
                    Is(3,1,1,4) ||
                    Is(3,1,1,5) ||
                    Is(3,1,1,6) ||
                    Is(3,1,2,1) ||
                    Is(3,1,2,2) ||
                    Is(3,1,2,3) ||
                    Is(3,1,2,4) ||
                    Is(3,1,2,5) ||
                    Is(3,1,2,6) ||
                    Is(3,1,3,1) ||
                    Is(3,1,3,2) ||
                    Is(3,1,3,3) ||
                    Is(3,1,3,4) ||
                    Is(3,1,3,5) ||
                    Is(3,1,3,6) ||
                    Is(3,1,9,1) ||
                    Is(3,1,9,2) ||
                    Is(3,1,9,3) ||
                    Is(3,1,9,4) ||
                    Is(3,1,9,5) ||
                    Is(3,1,9,6) ||
                    Is(3,1,10,1) ||
                    Is(3,1,10,2) ||
                    Is(3,1,10,3) ||
                    Is(3,1,10,4) ||
                    Is(3,1,10,5) ||
                    Is(3,1,10,6) ||
                    Is(3,1,11,1) ||
                    Is(3,1,11,2) ||
                    Is(3,1,11,3) ||
                    Is(3,1,11,4) ||
                    Is(3,1,11,5) ||
                    Is(3,1,11,6)
            );
        }

        bool IsShield() const {
            return (Is(3,1,4,1) ||
                    Is(3,1,4,2)
            );
        }

        bool IsAccessory() const {
            return (Is(3,1,5,1) ||
                    Is(3,1,5,2) ||
                    Is(3,1,5,3) ||
                    Is(3,1,12,1) ||
                    Is(3,1,12,2) ||
                    Is(3,1,12,3)
            );
        }

        bool IsWeapon() const {
            return (Is(3,1,6,2) ||
                    Is(3,1,6,3) ||
                    Is(3,1,6,4) ||
                    Is(3,1,6,5) ||
                    Is(3,1,6,6) ||
                    Is(3,1,6,7) ||
                    Is(3,1,6,8) ||
                    Is(3,1,6,9) ||
                    Is(3,1,6,10) ||
                    Is(3,1,6,11) ||
                    Is(3,1,6,12) ||
                    Is(3,1,6,13) ||
                    Is(3,1,6,14) ||
                    Is(3,1,6,15) ||
                    Is(3,1,6,16)
            );
        }

        bool IsEquip() const {
            return (IsArmor() || IsShield() || IsAccessory() || IsWeapon());
        }

        bool IsExtra() const {
            return (Is(3,1,7,1) ||
                    Is(3,1,7,2) ||
                    Is(3,1,7,3) ||
                    Is(3,1,7,5) ||
                    Is(3,1,7,6) ||
                    Is(3,1,7,7)
            );
        }

        bool IsAvatar() const {
            return (Is(3,1,13,1) ||
                    Is(3,1,13,2) ||
                    Is(3,1,13,3) ||
                    Is(3,1,13,4) //FLAG
            );
        }

        bool IsSpiritBracelet() const {
            return (Is(3,1,14,1));
        }

        bool IsSummonScroll() const {
            return (Is(3,2,1,1) ||
                    Is(3,2,1,2) ||
                    Is(3,2,1,3)
            );
        }

        bool IsExpendables() const {
            return (Is(3,3,1,1) ||
                    Is(3,3,1,2) ||
                    Is(3,3,1,3) ||
                    Is(3,3,1,4) ||
                    Is(3,3,1,6) ||
                    Is(3,3,1,8) ||
                    Is(3,3,1,9) ||
                    Is(3,3,1,10) ||
                    Is(3,3,1,11) ||
                    Is(3,3,1,12) ||
                    Is(3,3,1,13) ||
                    Is(3,3,2,1) ||
                    Is(3,3,2,6) ||
                    Is(3,3,2,7) ||
                    Is(3,3,2,8) ||
                    Is(3,3,2,9) ||
                    Is(3,3,3,1) ||
                    Is(3,3,3,2) ||
                    Is(3,3,3,3) ||
                    Is(3,3,3,4) ||
                    Is(3,3,3,5) ||
                    Is(3,3,3,6) ||
                    Is(3,3,3,7) ||
                    Is(3,3,3,8) ||
                    Is(3,3,3,9) ||
                    Is(3,3,3,10) ||
                    Is(3,3,3,11) ||
                    Is(3,3,3,12) ||
                    Is(3,3,3,13) ||
                    Is(3,3,3,14) ||
                    Is(3,3,3,15) ||
                    Is(3,3,3,16) ||
                    Is(3,3,3,17) ||
                    Is(3,3,3,18) ||
                    Is(3,3,3,19) ||
                    Is(3,3,3,20) ||
                    Is(3,3,3,21) ||
                    Is(3,3,3,22) ||
                    Is(3,3,3,23) ||
                    Is(3,3,4,1) ||
                    Is(3,3,4,2) ||
                    Is(3,3,5,0) ||
                    Is(3,3,5,1) ||
                    Is(3,3,6,1) ||
                    Is(3,3,6,2) ||
                    Is(3,3,7,1) ||
                    Is(3,3,8,0) ||
                    Is(3,3,8,1) ||
                    Is(3,3,8,2) ||
                    Is(3,3,8,3) ||
                    Is(3,3,9,0) ||
                    Is(3,3,9,1) ||
                    Is(3,3,11,1) ||
                    Is(3,3,11,2) ||
                    Is(3,3,11,3) ||
                    Is(3,3,11,4) ||
                    Is(3,3,11,5) ||
                    Is(3,3,11,6) ||
                    Is(3,3,11,7) ||
                    Is(3,3,11,8) ||
                    Is(3,3,11,9) ||
                    Is(3,3,11,10) ||
                    Is(3,3,11,11) ||
                    Is(3,3,11,12) ||
                    Is(3,3,11,13) ||
                    Is(3,3,11,14) ||
                    Is(3,3,11,15) ||
                    Is(3,3,11,17) ||
                    Is(3,3,11,18) ||
                    Is(3,3,12,1) ||
                    Is(3,3,12,2) ||
                    Is(3,3,12,3) ||
                    Is(3,3,12,4) ||
                    Is(3,3,12,5) ||
                    Is(3,3,12,6) ||
                    Is(3,3,12,7) ||
                    Is(3,3,12,8) ||
                    Is(3,3,12,9) ||
                    Is(3,3,12,10) ||
                    Is(3,3,13,0) ||
                    Is(3,3,13,1) ||
                    Is(3,3,13,4) ||
                    Is(3,3,13,5) ||
                    Is(3,3,13,6) ||
                    Is(3,3,13,7) ||
                    Is(3,3,13,8) ||
                    Is(3,3,13,9) ||
                    Is(3,3,13,10) ||
                    Is(3,3,13,11) ||
                    Is(3,3,13,12) ||
                    Is(3,3,13,13) ||
                    Is(3,3,13,14) ||
                    Is(3,3,13,15) ||
                    Is(3,3,13,16) ||
                    Is(3,3,13,17) ||
                    Is(3,3,13,18) ||
                    Is(3,3,13,19) ||
                    Is(3,3,13,20) ||
                    Is(3,3,13,21) ||
                    Is(3,3,13,22) ||
                    Is(3,3,13,23) ||
                    Is(3,3,13,24) ||
                    Is(3,3,13,25) ||
                    Is(3,3,13,26) ||
                    Is(3,3,13,30) ||
                    Is(3,3,13,31) ||
                    Is(3,3,14,1) ||
                    Is(3,3,14,2) ||
                    Is(3,3,14,3) ||
                    Is(3,3,14,4) ||
                    Is(3,3,14,5) ||
                    Is(3,3,15,1) ||
                    Is(3,3,15,2) ||
                    Is(3,3,16,1) ||
                    Is(3,3,16,3) ||
                    Is(3,3,16,4) ||
                    Is(3,3,16,5)
            );
        }

        bool IsEquipment() const {
            return (IsArmor() || IsShield() || IsAccessory() || IsWeapon());
        }

        bool IsJobEquipment() const {
            return (Is(3,4,1,1) ||
                    Is(3,4,1,2) ||
                    Is(3,4,1,3) ||
                    Is(3,4,1,4) ||
                    Is(3,4,1,5) ||
                    Is(3,4,1,6) ||
                    Is(3,4,2,1) ||
                    Is(3,4,3,1) ||
                    Is(3,4,3,2) ||
                    Is(3,4,3,3) ||
                    Is(3,4,4,1) ||
                    Is(3,4,4,2) ||
                    Is(3,4,4,3) ||
                    Is(3,4,4,4) ||
                    Is(3,4,4,5) ||
                    Is(3,4,4,6) ||
                    Is(3,4,5,1) ||
                    Is(3,4,6,1) ||
                    Is(3,4,6,2) ||
                    Is(3,4,6,3)
            );
        }

        bool IsSpecialty() const {
            return (Is(3,3,10,1) ||
                    Is(3,3,10,2) ||
                    Is(3,3,10,4) ||
                    Is(3,3,10,5) ||
                    Is(3,3,10,6) ||
                    Is(3,3,10,8) ||
                    Is(3,3,10,9) ||
                    Is(3,3,10,10) ||
                    Is(3,3,10,11)
            );
        }
    };
}

#endif
