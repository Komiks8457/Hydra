#pragma once

#ifndef REFOBJCHAR_H
#define REFOBJCHAR_H

#include "RefObjCommon.h"

namespace HydraFramework
{
    struct Resist
    {
        enum ENUM_RESIST_TYPE
        {
            Frozen,
            Frostbite,
            Burn,
            EShock,
            Poison,
            Zombie,
            Doze,
            Root,
            Slow,
            Fear,
            Myopia,
            Blood,
            Stone,
            Dark,
            Stun,
            Disease,
            Chaos,
            CsePD,
            CseMD,
            CseSTR,
            CseINT,
            CseHP,
            CseMP,
            Resist24,
            Bomb,
            Resist26,
            Resist27,
            Resist28,
            Resist29,
            Resist30,
            Resist31,
            Resist32,
            MAX_RESIST_TYPE
        };

        int Value;
        Resist() : Value(0)
        {}
    };

    struct DefaultSkill
    {
        enum ENUM_DEFAULT_SKILL
        {
            Skill1,
            Skill2,
            Skill3,
            Skill4,
            Skill5,
            Skill6,
            Skill7,
            Skill8,
            Skill9,
            Skill10,
            MAX_DEFAULT_SKILL
        };

        int Value;
        DefaultSkill() : Value(0)
        {}
    };

    struct Except
    {
        enum ENUM_EXCEPT_TYPE
        {
            Except1,
            Except2,
            Except3,
            Except4,
            Except5,
            Except6,
            Except7,
            Except8,
            Except9,
            Except10,
            MAX_EXCEPT_TYPE
        };

        int Value;
        Except() : Value(0)
        {}
    };

    struct RefObjChar: RefObjCommon {
        friend class CRefDataManager;

    private:
        BYTE m_Lvl;
        BYTE m_CharGender;
        int m_MaxHP;
        int m_MaxMP;
        Resist m_Resist[Resist::MAX_RESIST_TYPE];
        BYTE m_InventorySize;
        BYTE m_CanStore_TID1;
        BYTE m_CanStore_TID2;
        BYTE m_CanStore_TID3;
        BYTE m_CanStore_TID4;
        bool m_CanBeVehicle;
        bool m_CanControl;
        BYTE m_DamagePortion;
        short m_MaxPassenger;
        int m_AssocTactics;
        int m_PD;
        int m_MD;
        int m_PAR;
        int m_MAR;
        int m_ER;
        int m_BR;
        int m_HR;
        int m_CHR;
        int m_ExpToGive;
        int m_CreepType;
        bool m_Knockdown;
        int m_KO_RecoverTime;
        DefaultSkill m_DefaultSkill[DefaultSkill::MAX_DEFAULT_SKILL];
        BYTE m_TextureType;
        Except m_Except[Except::MAX_EXCEPT_TYPE];


    public:
        RefObjChar() : m_Lvl(0), m_CharGender(0), m_MaxHP(0), m_MaxMP(0), m_InventorySize(0),
                       m_CanStore_TID1(0), m_CanStore_TID2(0), m_CanStore_TID3(0), m_CanStore_TID4(0),
                       m_CanBeVehicle(0), m_CanControl(0), m_DamagePortion(0), m_MaxPassenger(0), m_AssocTactics(0),
                       m_PD(0), m_MD(0), m_PAR(0), m_MAR(0), m_ER(0), m_BR(0), m_HR(0), m_CHR(0), m_ExpToGive(0),
                       m_CreepType(0), m_Knockdown(0), m_KO_RecoverTime(0), m_TextureType(0)
        {}

        BYTE Lvl() const { return m_Lvl; }

        BYTE CharGender() const { return m_CharGender; }

        int MaxHP() const { return m_MaxHP; }

        int MaxMP() const { return m_MaxMP; }

        int Resist(Resist::ENUM_RESIST_TYPE resistType) const
        {
            if (resistType >= Resist::MAX_RESIST_TYPE)
                return NULL;
            return m_Resist[resistType].Value;
        }

        BYTE InventorySize() const { return m_InventorySize; }

        BYTE CanStore_TID1() const { return m_CanStore_TID1; }

        BYTE CanStore_TID2() const { return m_CanStore_TID2; }

        BYTE CanStore_TID3() const { return m_CanStore_TID3; }

        BYTE CanStore_TID4() const { return m_CanStore_TID4; }

        bool CanBeVehicle() const { return m_CanBeVehicle; }

        bool CanControl() const { return m_CanControl; }

        BYTE DamagePortion() const { return m_DamagePortion; }

        short MaxPassenger() const { return m_MaxPassenger; }

        int AssocTactics() const { return m_AssocTactics; }

        int PD() const { return m_PD; }

        int MD() const { return m_MD; }

        int PAR() const { return m_PAR; }

        int MAR() const { return m_MAR; }

        int ER() const { return m_ER; }

        int BR() const { return m_BR; }

        int HR() const { return m_HR; }

        int CHR() const { return m_CHR; }

        int ExpToGive() const { return m_ExpToGive; }

        int CreepType() const { return m_CreepType; }

        bool Knockdown() const { return m_Knockdown; }

        int KO_RecoverTime() const { return m_KO_RecoverTime; }

        int DefaultSkill(DefaultSkill::ENUM_DEFAULT_SKILL defaultSkill) const
        {
            if (defaultSkill >= DefaultSkill::MAX_DEFAULT_SKILL)
                return NULL;
            return m_DefaultSkill[defaultSkill].Value;
        }

        BYTE TextureType() const { return m_TextureType; }

        int Except(Except::ENUM_EXCEPT_TYPE exceptType) const
        {
            if (exceptType >= Except::MAX_EXCEPT_TYPE)
                return NULL;
            return m_Except[exceptType].Value;
        }
    };
}

#endif
