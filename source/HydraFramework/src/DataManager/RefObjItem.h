#pragma once

#ifndef REFOBJITEM_H
#define REFOBJITEM_H

#include "RefObjCommon.h"

namespace HydraFramework
{
    struct ItemParam
    {
        enum ENUM_PARAM
        {
            Param1,
            Param2,
            Param3,
            Param4,
            Param5,
            Param6,
            Param7,
            Param8,
            Param9,
            Param10,
            Param11,
            Param12,
            Param13,
            Param14,
            Param15,
            Param16,
            Param17,
            Param18,
            Param19,
            Param20,
            MAX_PARAM
        };

        int Value;
        std::string Desc;
        ItemParam() : Value(0)
        {}
    };

    struct RefObjItem : RefObjCommon {
        friend class CRefDataManager;

    private:
        int m_MaxStack;
        BYTE m_ReqGender;
        int m_ReqStr;
        int m_ReqInt;
        BYTE m_ItemClass;
        int m_SetID;
        float m_Dur_L;
        float m_Dur_U;
        float m_PD_L;
        float m_PD_U;
        float m_PDInc;
        float m_ER_L;
        float m_ER_U;
        float m_ERInc;
        float m_PAR_L;
        float m_PAR_U;
        float m_PARInc;
        float m_BR_L;
        float m_BR_U;
        float m_MD_L;
        float m_MD_U;
        float m_MDInc;
        float m_MAR_L;
        float m_MAR_U;
        float m_MARInc;
        float m_PDStr_L;
        float m_PDStr_U;
        float m_MDInt_L;
        float m_MDInt_U;
        bool m_Quivered;
        BYTE m_Ammo1_TID4;
        BYTE m_Ammo2_TID4;
        BYTE m_Ammo3_TID4;
        BYTE m_Ammo4_TID4;
        BYTE m_Ammo5_TID4;
        BYTE m_SpeedClass;
        bool m_TwoHanded;
        short m_Range;
        float m_PAttackMin_L;
        float m_PAttackMin_U;
        float m_PAttackMax_L;
        float m_PAttackMax_U;
        float m_PAttackInc;
        float m_MAttackMin_L;
        float m_MAttackMin_U;
        float m_MAttackMax_L;
        float m_MAttackMax_U;
        float m_MAttackInc;
        float m_PAStrMin_L;
        float m_PAStrMin_U;
        float m_PAStrMax_L;
        float m_PAStrMax_U;
        float m_MAInt_Min_L;
        float m_MAInt_Min_U;
        float m_MAInt_Max_L;
        float m_MAInt_Max_U;
        float m_HR_L;
        float m_HR_U;
        float m_HRInc;
        float m_CHR_L;
        float m_CHR_U;
        ItemParam m_Param[ItemParam::MAX_PARAM];
        BYTE m_MaxMagicOptCount;
        BYTE m_ChildItemCount;

    public:
        RefObjItem() : m_MaxStack(0), m_ReqGender(0), m_ReqStr(0), m_ReqInt(0), m_ItemClass(0),
                       m_SetID(0), m_Dur_L(0.0f), m_Dur_U(0.0f), m_PD_L(0.0f), m_PD_U(0.0f), m_PDInc(0.0f),
                       m_ER_L(0.0f), m_ER_U(0.0f), m_ERInc(0.0f), m_PAR_L(0.0f), m_PAR_U(0.0f), m_PARInc(0.0f),
                       m_BR_L(0.0f), m_BR_U(0.0f), m_MD_L(0.0f), m_MD_U(0.0f), m_MDInc(0.0f), m_MAR_L(0.0f),
                       m_MAR_U(0.0f), m_MARInc(0.0f), m_PDStr_L(0.0f), m_PDStr_U(0.0f), m_MDInt_L(0.0f),
                       m_MDInt_U(0.0f), m_Quivered(false), m_Ammo1_TID4(0), m_Ammo2_TID4(0), m_Ammo3_TID4(0),
                       m_Ammo4_TID4(0), m_Ammo5_TID4(0), m_SpeedClass(0), m_TwoHanded(false), m_Range(0),
                       m_PAttackMin_L(0.0f), m_PAttackMin_U(0.0f), m_PAttackMax_L(0.0f), m_PAttackMax_U(0.0f),
                       m_PAttackInc(0.0f), m_MAttackMin_L(0.0f), m_MAttackMin_U(0.0f), m_MAttackMax_L(0.0f),
                       m_MAttackMax_U(0.0f), m_MAttackInc(0.0f), m_PAStrMin_L(0.0f), m_PAStrMin_U(0.0f),
                       m_PAStrMax_L(0.0f), m_PAStrMax_U(0.0f), m_MAInt_Min_L(0.0f), m_MAInt_Min_U(0.0f),
                       m_MAInt_Max_L(0.0f), m_MAInt_Max_U(0.0f), m_HR_L(0.0f), m_HR_U(0.0f), m_HRInc(0.0f),
                       m_CHR_L(0.0f), m_CHR_U(0.0f), m_MaxMagicOptCount(0), m_ChildItemCount(0)
        {}

        int MaxStack() const { return m_MaxStack; }

        BYTE ReqGender() const { return m_ReqGender; }

        int ReqStr() const { return m_ReqStr; }

        int ReqInt() const { return m_ReqInt; }

        BYTE ItemClass() const { return m_ItemClass; }

        int SetID() const { return m_SetID; }

        float Dur_L() const { return m_Dur_L; }

        float Dur_U() const { return m_Dur_U; }

        float PD_L() const { return m_PD_L; }

        float PD_U() const { return m_PD_U; }

        float PDInc() const { return m_PDInc; }

        float ER_L() const { return m_ER_L; }

        float ER_U() const { return m_ER_U; }

        float ERInc() const { return m_ERInc; }

        float PAR_L() const { return m_PAR_L; }

        float PAR_U() const { return m_PAR_U; }

        float PARInc() const { return m_PARInc; }

        float BR_L() const { return m_BR_L; }

        float BR_U() const { return m_BR_U; }

        float MD_L() const { return m_MD_L; }

        float MD_U() const { return m_MD_U; }

        float MDInc() const { return m_MDInc; }

        float MAR_L() const { return m_MAR_L; }

        float MAR_U() const { return m_MAR_U; }

        float MARInc() const { return m_MARInc; }

        float PDStr_L() const { return m_PDStr_L; }

        float PDStr_U() const { return m_PDStr_U; }

        float MDInt_L() const { return m_MDInt_L; }

        float MDInt_U() const { return m_MDInt_U; }

        bool Quivered() const { return m_Quivered; }

        BYTE Ammo1_TID4() const { return m_Ammo1_TID4; }

        BYTE Ammo2_TID4() const { return m_Ammo2_TID4; }

        BYTE Ammo3_TID4() const { return m_Ammo3_TID4; }

        BYTE Ammo4_TID4() const { return m_Ammo4_TID4; }

        BYTE Ammo5_TID4() const { return m_Ammo5_TID4; }

        BYTE SpeedClass() const { return m_SpeedClass; }

        bool TwoHanded() const { return m_TwoHanded; }

        short Range() const { return m_Range; }

        float PAttackMin_L() const { return m_PAttackMin_L; }

        float PAttackMin_U() const { return m_PAttackMin_U; }

        float PAttackMax_L() const { return m_PAttackMax_L; }

        float PAttackMax_U() const { return m_PAttackMax_U; }

        float PAttackInc() const { return m_PAttackInc; }

        float MAttackMin_L() const { return m_MAttackMin_L; }

        float MAttackMin_U() const { return m_MAttackMin_U; }

        float MAttackMax_L() const { return m_MAttackMax_L; }

        float MAttackMax_U() const { return m_MAttackMax_U; }

        float MAttackInc() const { return m_MAttackInc; }

        float PAStrMin_L() const { return m_PAStrMin_L; }

        float PAStrMin_U() const { return m_PAStrMin_U; }

        float PAStrMax_L() const { return m_PAStrMax_L; }

        float PAStrMax_U() const { return m_PAStrMax_U; }

        float MAInt_Min_L() const { return m_MAInt_Min_L; }

        float MAInt_Min_U() const { return m_MAInt_Min_U; }

        float MAInt_Max_L() const { return m_MAInt_Max_L; }

        float MAInt_Max_U() const { return m_MAInt_Max_U; }

        float HR_L() const { return m_HR_L; }

        float HR_U() const { return m_HR_U; }

        float HRInc() const { return m_HRInc; }

        float CHR_L() const { return m_CHR_L; }

        float CHR_U() const { return m_CHR_U; }

        ItemParam Params(ItemParam::ENUM_PARAM type) const
        {
            if (type == ItemParam::MAX_PARAM)
                return ItemParam(); //default
            return m_Param[type];
        }

        BYTE MaxMagicOptCount() const { return m_MaxMagicOptCount; }

        BYTE ChildItemCount() const { return m_ChildItemCount; }

        bool HasParam(int nParam) const
        {
            for (int i = 0; i < ItemParam::MAX_PARAM; ++i)
            {
                if (m_Param[i].Value == nParam)
                    return true;
            }

            return false;
        }

        bool HasParam(int nParam, ItemParam &param) const
        {
            for (int i = 0; i < ItemParam::MAX_PARAM; ++i)
            {
                if (m_Param[i].Value == nParam)
                {
                    param = m_Param[i];
                    return true;
                }
            }

            return false;
        }

        bool HasParamDesc(const std::string &desc128) const
        {
            for (int i = 0; i < ItemParam::MAX_PARAM; ++i)
            {
                if (__stringa(m_Param[i].Desc).startwith(desc128))
                    return true;
            }

            return false;
        }

        bool HasParamDesc(const std::string &desc128, ItemParam &param) const
        {
            for (int i = 0; i < ItemParam::MAX_PARAM; ++i)
            {
                if (__stringa(m_Param[i].Desc).startwith(desc128))
                {
                    param = m_Param[i];
                    return true;
                }
            }

            return false;
        }
    };
}

#endif
