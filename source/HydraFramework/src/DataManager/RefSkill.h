#pragma once

#ifndef REFSKILL_H
#define REFSKILL_H

#include "pch.h"

namespace HydraFramework
{
    struct SkillParam
    {
        enum ENUM_SKILL_PARAM {
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
            Param21,
            Param22,
            Param23,
            Param24,
            Param25,
            Param26,
            Param27,
            Param28,
            Param29,
            Param30,
            Param31,
            Param32,
            Param33,
            Param34,
            Param35,
            Param36,
            Param37,
            Param38,
            Param39,
            Param40,
            Param41,
            Param42,
            Param43,
            Param44,
            Param45,
            Param46,
            Param47,
            Param48,
            Param49,
            Param50,
            MAX_SKILL_PARAM
        };

        int Value;
        SkillParam() : Value(0)
        {}
    };

    struct RefSkill {
        friend class CRefDataManager;

    private:
        int m_ID;
        int m_GroupID;
        stra_t m_Basic_Code;
        stra_t m_Basic_Name;
        stra_t m_Basic_Group;
        int m_Basic_Original;
        BYTE m_Basic_Level;
        BYTE m_Basic_Activity;
        int m_Basic_ChainCode;
        int m_Basic_RecycleCost;
        int m_Action_PreparingTime;
        int m_Action_CastingTime;
        int m_Action_ActionDuration;
        int m_Action_ReuseDelay;
        int m_Action_CoolTime;
        int m_Action_FlyingSpeed;
        BYTE m_Action_Interruptable;
        int m_Action_Overlap;
        BYTE m_Action_AutoAttackType;
        BYTE m_Action_InTown;
        short m_Action_Range;
        BYTE m_Target_Required;
        BYTE m_TargetType_Animal;
        BYTE m_TargetType_Land;
        BYTE m_TargetType_Building;
        BYTE m_TargetGroup_Self;
        BYTE m_TargetGroup_Ally;
        BYTE m_TargetGroup_Party;
        BYTE m_TargetGroup_Enemy_M;
        BYTE m_TargetGroup_Enemy_P;
        BYTE m_TargetGroup_Neutral;
        BYTE m_TargetGroup_DontCare;
        BYTE m_TargetEtc_SelectDeadBody;
        int m_ReqCommon_Mastery1;
        int m_ReqCommon_Mastery2;
        BYTE m_ReqCommon_MasteryLevel1;
        BYTE m_ReqCommon_MasteryLevel2;
        short m_ReqCommon_Str;
        short m_ReqCommon_Int;
        int m_ReqLearn_Skill1;
        int m_ReqLearn_Skill2;
        int m_ReqLearn_Skill3;
        BYTE m_ReqLearn_SkillLevel1;
        BYTE m_ReqLearn_SkillLevel2;
        BYTE m_ReqLearn_SkillLevel3;
        int m_ReqLearn_SP;
        BYTE m_ReqLearn_Race;
        BYTE m_Req_Restriction1;
        BYTE m_Req_Restriction2;
        BYTE m_ReqCast_Weapon1;
        BYTE m_ReqCast_Weapon2;
        short m_Consume_HP;
        int m_Consume_MP;
        short m_Consume_HPRatio;
        short m_Consume_MPRatio;
        BYTE m_Consume_WHAN;
        BYTE m_UI_SkillTab;
        BYTE m_UI_SkillPage;
        BYTE m_UI_SkillColumn;
        BYTE m_UI_SkillRow;
        stra_t m_UI_IconFile;
        stra_t m_UI_SkillName;
        stra_t m_UI_SkillToolTip;
        stra_t m_UI_SkillToolTip_Desc;
        stra_t m_UI_SkillStudy_Desc;
        short m_AI_AttackChance;
        BYTE m_AI_SkillType;
        SkillParam m_Param[SkillParam::MAX_SKILL_PARAM];

    public:
        RefSkill() : m_ID(0), m_GroupID(0), m_Basic_Original(0), m_Basic_Level(0), m_Basic_Activity(0),
                     m_Basic_ChainCode(0), m_Basic_RecycleCost(0), m_Action_PreparingTime(0), m_Action_CastingTime(0),
                     m_Action_ActionDuration(0) ,m_Action_ReuseDelay(0) ,m_Action_CoolTime(0) ,m_Action_FlyingSpeed(0),
                     m_Action_Interruptable(0) ,m_Action_Overlap(0) ,m_Action_AutoAttackType(0) ,m_Action_InTown(0),
                     m_Action_Range(0), m_Target_Required(0), m_TargetType_Animal(0), m_TargetType_Land(0),
                     m_TargetType_Building(0), m_TargetGroup_Self(0), m_TargetGroup_Ally(0), m_TargetGroup_Party(0),
                     m_TargetGroup_Enemy_M(0), m_TargetGroup_Enemy_P(0), m_TargetGroup_Neutral(0),
                     m_TargetGroup_DontCare(0), m_TargetEtc_SelectDeadBody(0), m_ReqCommon_Mastery1(0),
                     m_ReqCommon_Mastery2(0), m_ReqCommon_MasteryLevel1(0), m_ReqCommon_MasteryLevel2(0),
                     m_ReqCommon_Str(0), m_ReqCommon_Int(0), m_ReqLearn_Skill1(0), m_ReqLearn_Skill2(0),
                     m_ReqLearn_Skill3(0), m_ReqLearn_SkillLevel1(0), m_ReqLearn_SkillLevel2(0),
                     m_ReqLearn_SkillLevel3(0), m_ReqLearn_SP(0), m_ReqLearn_Race(0), m_Req_Restriction1(0),
                     m_Req_Restriction2(0), m_ReqCast_Weapon1(0), m_ReqCast_Weapon2(0), m_Consume_HP(0),
                     m_Consume_MP(0), m_Consume_HPRatio(0), m_Consume_MPRatio(0), m_Consume_WHAN(0),
                     m_UI_SkillTab(0), m_UI_SkillPage(0), m_UI_SkillColumn(0), m_UI_SkillRow(0),
                     m_AI_AttackChance(0), m_AI_SkillType(0)
        {}

        int SkillID() const { return m_ID; }

        int GroupID() const { return m_GroupID; }

        const stra_t &Basic_Code() const { return m_Basic_Code; }

        const stra_t &Basic_Name() const { return m_Basic_Name; }

        const stra_t &Basic_Group() const { return m_Basic_Group; }

        int Basic_Original() const { return m_Basic_Original; }

        BYTE Basic_Level() const { return m_Basic_Level; }

        BYTE Basic_Activity() const { return m_Basic_Activity; }

        int Basic_ChainCode() const { return m_Basic_ChainCode; }

        int Basic_RecycleCost() const { return m_Basic_RecycleCost; }

        int Action_PreparingTime() const { return m_Action_PreparingTime; }

        int Action_CastingTime() const { return m_Action_CastingTime; }

        int Action_ActionDuration() const { return m_Action_ActionDuration; }

        int Action_ReuseDelay() const { return m_Action_ReuseDelay; }

        int Action_CoolTime() const { return m_Action_CoolTime; }

        int Action_FlyingSpeed() const { return m_Action_FlyingSpeed; }

        BYTE Action_Interruptable() const { return m_Action_Interruptable; }

        int Action_Overlap() const { return m_Action_Overlap; }

        BYTE Action_AutoAttackType() const { return m_Action_AutoAttackType; }

        BYTE Action_InTown() const { return m_Action_InTown; }

        short Action_Range() const { return m_Action_Range; }

        BYTE Target_Required() const { return m_Target_Required; }

        BYTE TargetType_Animal() const { return m_TargetType_Animal; }

        BYTE TargetType_Land() const { return m_TargetType_Land; }

        BYTE TargetType_Building() const { return m_TargetType_Building; }

        BYTE TargetGroup_Self() const { return m_TargetGroup_Self; }

        BYTE TargetGroup_Ally() const { return m_TargetGroup_Ally; }

        BYTE TargetGroup_Party() const { return m_TargetGroup_Party; }

        BYTE TargetGroup_Enemy_M() const { return m_TargetGroup_Enemy_M; }

        BYTE TargetGroup_Enemy_P() const { return m_TargetGroup_Enemy_P; }

        BYTE TargetGroup_Neutral() const { return m_TargetGroup_Neutral; }

        BYTE TargetGroup_DontCare() const { return m_TargetGroup_DontCare; }

        BYTE TargetEtc_SelectDeadBody() const { return m_TargetEtc_SelectDeadBody; }

        int ReqCommon_Mastery1() const { return m_ReqCommon_Mastery1; }

        int ReqCommon_Mastery2() const { return m_ReqCommon_Mastery2; }

        BYTE ReqCommon_MasteryLevel1() const { return m_ReqCommon_MasteryLevel1; }

        BYTE ReqCommon_MasteryLevel2() const { return m_ReqCommon_MasteryLevel2; }

        short ReqCommon_Str() const { return m_ReqCommon_Str; }

        short ReqCommon_Int() const { return m_ReqCommon_Int; }

        int ReqLearn_Skill1() const { return m_ReqLearn_Skill1; }

        int ReqLearn_Skill2() const { return m_ReqLearn_Skill2; }

        int ReqLearn_Skill3() const { return m_ReqLearn_Skill3; }

        BYTE ReqLearn_SkillLevel1() const { return m_ReqLearn_SkillLevel1; }

        BYTE ReqLearn_SkillLevel2() const { return m_ReqLearn_SkillLevel2; }

        BYTE ReqLearn_SkillLevel3() const { return m_ReqLearn_SkillLevel3; }

        int ReqLearn_SP() const { return m_ReqLearn_SP; }

        BYTE ReqLearn_Race() const { return m_ReqLearn_Race; }

        BYTE Req_Restriction1() const { return m_Req_Restriction1; }

        BYTE Req_Restriction2() const { return m_Req_Restriction2; }

        BYTE ReqCast_Weapon1() const { return m_ReqCast_Weapon1; }

        BYTE ReqCast_Weapon2() const { return m_ReqCast_Weapon2; }

        short Consume_HP() const { return m_Consume_HP; }

        int Consume_MP() const { return m_Consume_MP; }

        short Consume_HPRatio() const { return m_Consume_HPRatio; }

        short Consume_MPRatio() const { return m_Consume_MPRatio; }

        BYTE Consume_WHAN() const { return m_Consume_WHAN; }

        BYTE UI_SkillTab() const { return m_UI_SkillTab; }

        BYTE UI_SkillPage() const { return m_UI_SkillPage; }

        BYTE UI_SkillColumn() const { return m_UI_SkillColumn; }

        BYTE UI_SkillRow() const { return m_UI_SkillRow; }

        const stra_t &UI_IconFile() const { return m_UI_IconFile; }

        const stra_t &UI_SkillName() const { return m_UI_SkillName; }

        const stra_t &UI_SkillToolTip() const { return m_UI_SkillToolTip; }

        const stra_t &UI_SkillToolTip_Desc() const { return m_UI_SkillToolTip_Desc; }

        const stra_t &UI_SkillStudy_Desc() const { return m_UI_SkillStudy_Desc; }

        short AI_AttackChance() const { return m_AI_AttackChance; }

        BYTE AI_SkillType() const { return m_AI_SkillType; }

        int Param(SkillParam::ENUM_SKILL_PARAM skillParam) const
        {
            if (skillParam >= SkillParam::MAX_SKILL_PARAM)
                return NULL;
            return m_Param[skillParam].Value;
        }

        bool HasParam(int nParam) const
        {
            for (int i = 0; i < SkillParam::MAX_SKILL_PARAM; ++i)
            {
                if (m_Param[i].Value == nParam)
                    return true;
            }

            return false;
        }
    };
}

#endif
