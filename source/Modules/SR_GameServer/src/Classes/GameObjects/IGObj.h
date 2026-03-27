#ifndef IGOBJ_H
#define IGOBJ_H

#include "pch.h"
#include "utils/MemoryUtility.h"
#include "BSLib/AppLogger.h"

enum LIFESTATE
{
    LIFESTATE_ALIVE = 1,
    LIFESTATE_DEAD,
    LIFESTATE_GONE,
    LIFESTATE_EMBRYO = 0,
};

enum MOTIONSTATE
{
    MOTIONSTATE_SKILL = 1,
    MOTIONSTATE_WALK,
    MOTIONSTATE_RUN,
    MOTIONSTATE_SIT,
    MOTIONSTATE_JUMP,
    MOTIONSTATE_SWIM,
    MOTIONSTATE_RIDE,
    MOTIONSTATE_KNOCKDOWN,
    MOTIONSTATE_STUN,
    MOTIONSTATE_FROZEN,
    MOTIONSTATE_HIT,
    MOTIONSTATE_REQ_HELP,
    MOTIONSTATE_PAO,
    MOTIONSTATE_COUNTERATTACK,
    MOTIONSTATE_SKILL_ACTIONOFF,
    MOTIONSTATE_SKILL_KNOCKBACK,
    MOTIONSTATE_PROTECTIONWALL,
    MOTIONSTATE_CHANGEMOTION,
    MOTIONSTATE_SLEEP,
    MOTIONSTATE_STONE,
    MOTIONSTATE_STAND = 0
};

enum BODYMODE
{
    BODYMODE_HWAN = 1,
    BODYMODE_INVINCIBLE,
    BODYMODE_INVISIBLE,
    BODYMODE_BERSERKER,
    BODYMODE_GM_INVISIBLE,
    BODYMODE_STEALTH,
    BODYMODE_SKILL_INVISIBLE,
    BODYMODE_NORMAL = 0,
};

struct sPartyInfo;
struct sMagParamAddInfo;
struct sEventHandler;

struct sWorldID {
    union {
        struct {
            WORD wWorldID;
            WORD wLayerID;
        };
        DWORD dwWorldID;
    };

    sWorldID(WORD wLID = 0, WORD wWID = 0) : wLayerID(wLID), wWorldID(wWID)
    {}

    sWorldID(DWORD dwWID = 0) : dwWorldID(dwWID)
    {}
};

#pragma pack(push, 1)
struct sPosInfo {
public:
    short wRegionID;
    float fltX;
    float fltY;
    float fltZ;

    sPosInfo(short wRID = 0, float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
            : wRegionID(wRID), fltX(X), fltY(Y), fltZ(Z)
    {}

    double GetDistance(const sPosInfo& from, int nScaleFactor = 1919) const
    {
        const double unitToMeterScale = 0.1;

        BYTE RX = LOBYTE(this->wRegionID);
        BYTE RZ = HIBYTE(this->wRegionID);
        BYTE fromRX = LOBYTE(from.wRegionID);
        BYTE fromRZ = HIBYTE(from.wRegionID);

        double WorldX = (static_cast<double>(fltX) + (RX * nScaleFactor)) * unitToMeterScale;
        double WorldZ = (static_cast<double>(fltZ) + (RZ * nScaleFactor)) * unitToMeterScale;

        double targetWorldX = (static_cast<double>(from.fltX) + (fromRX * nScaleFactor)) * unitToMeterScale;
        double targetWorldZ = (static_cast<double>(from.fltZ) + (fromRZ * nScaleFactor)) * unitToMeterScale;

        double dx = targetWorldX - WorldX;
        double dz = targetWorldZ - WorldZ;

        return std::sqrt((dx * dx) + (dz * dz));
    }
};
#pragma pack(pop)

struct sRegionInfo {
    short wRegionID;
    short wRegionBlockID;
    float fltX;
    float fltY;
    float fltZ;

    sRegionInfo(short wRID = 0, short wBID = 0, float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
            : wRegionID(wRID), wRegionBlockID(wBID), fltX(X), fltY(Y), fltZ(Z)
    {}

    double GetDistance(const sRegionInfo& from, int nScaleFactor = 1919) const
    {
        const double unitToMeterScale = 0.1;

        BYTE RX = LOBYTE(this->wRegionID);
        BYTE RZ = HIBYTE(this->wRegionID);
        BYTE fromRX = LOBYTE(from.wRegionID);
        BYTE fromRZ = HIBYTE(from.wRegionID);

        double WorldX = (static_cast<double>(fltX) + (RX * nScaleFactor)) * unitToMeterScale;
        double WorldZ = (static_cast<double>(fltZ) + (RZ * nScaleFactor)) * unitToMeterScale;

        double targetWorldX = (static_cast<double>(from.fltX) + (fromRX * nScaleFactor)) * unitToMeterScale;
        double targetWorldZ = (static_cast<double>(from.fltZ) + (fromRZ * nScaleFactor)) * unitToMeterScale;

        double dx = targetWorldX - WorldX;
        double dz = targetWorldZ - WorldZ;

        return std::sqrt((dx * dx) + (dz * dz));
    }

    double GetDistance(const sPosInfo& from, int nScaleFactor = 1919) const
    {
        sRegionInfo regionInfo;
        regionInfo.wRegionID = from.wRegionID;
        regionInfo.fltX = from.fltX;
        regionInfo.fltZ = from.fltZ;

        return GetDistance(regionInfo, nScaleFactor);
    }
};

class __declspec(novtable) IGObj {
public:
    virtual void *Init() = 0;
    virtual int GetRefObjID() const = 0;
    virtual int GetJID() const = 0;
    virtual int GetGameID() const = 0;
    virtual int GetTypeID() const = 0;

    virtual sWorldID& GetWorldID(sWorldID &) const = 0;

    virtual BOOL IsChar() const = 0;
    virtual BOOL IsPC() const = 0;
    virtual BOOL IsNPC() const = 0;
    virtual BOOL IsNPCNPC() const = 0;
    virtual BOOL IsMonster() const = 0;
    virtual BOOL IsCOS() const = 0;
    virtual BOOL IsCart() const = 0;
    virtual BOOL IsVehicle() const = 0;
    virtual BOOL IsPet() const = 0;
    virtual BOOL IsMercenary() const = 0;
    virtual BOOL IsAttackableCOS() const = 0;
    virtual BOOL IsStruct() const = 0;
    virtual BOOL IsItem() const = 0;
    virtual BOOL IsExpendables() const = 0;
    virtual BOOL IsContainerItem() const = 0;
    virtual BOOL IsContainerSummonerItem() const = 0;
    virtual BOOL IsSpecialty() const = 0;
    virtual BOOL IsPotion() const = 0;
    virtual BOOL IsScroll() const = 0;
    virtual BOOL IsBullet() const = 0;
    virtual BOOL IsArrow() const = 0;
    virtual BOOL IsBolt() const = 0;
    virtual BOOL IsHPPotion() const = 0;
    virtual BOOL IsMPPotion() const = 0;
    virtual BOOL IsElixir() const = 0;
    virtual BOOL IsGold() const = 0;
    virtual BOOL IsTownPortal() const = 0;
    virtual BOOL IsEquip() const = 0;
    virtual BOOL IsWeapon() const = 0;
    virtual BOOL IsShield() const = 0;
    virtual BOOL IsAccessory() const = 0;
    virtual BOOL IsTeleportGate() const = 0;
    virtual BOOL IsRobe() const = 0;
    virtual BOOL IsArmor() const = 0;
    virtual BOOL IsBow() const = 0;
    virtual BOOL IsCrossBow() const = 0;
    virtual BOOL IsSummonScroll() const = 0;
    virtual BOOL IsReinforceRecipe() const = 0;
    virtual BOOL IsReinforceProbUP() const = 0;
    virtual BOOL IsFreeBattleEquip() const = 0;
    virtual BOOL IsQuest_n_EventItem() const = 0;
    virtual BOOL IsCashItem() const = 0;

    virtual BOOL sub_66DE50() const = 0; //

    virtual int CanTrade() const = 0;
    virtual int CanSell() const = 0;
    virtual int CanBorrow() const = 0;
    virtual int CanDrop() const = 0;
    virtual int CanPick() const = 0;
    virtual int CanRepair() const = 0;
    virtual int CanRevive() const = 0;
    virtual int CanUse() const = 0;
    virtual int CanThrow() const = 0;

    virtual const char* GetCodeName() const = 0;
    virtual const char* GetCharName() const = 0;
    virtual const char* GetNickName() const = 0;

    virtual sPosInfo& GetPosInfo(sPosInfo &) const = 0;

    virtual LIFESTATE GetLifeState() const = 0;
    virtual MOTIONSTATE GetMotionState() const = 0;
    virtual BODYMODE GetBodyMode() const = 0;
    virtual BOOL GetParam(WORD) const = 0;
    virtual BOOL GetCurHP() const = 0;
    virtual BOOL GetCurMP() const = 0;
    virtual BOOL GetMaxHP() const = 0;
    virtual BOOL GetMaxMP() const = 0;
    virtual bool IsTargeting() const = 0;
    virtual char GetTCJobState() const = 0;
    virtual int GetUserTCJob() const = 0;
    virtual char GetTeleportState() const = 0;
    virtual char GetLevel() const = 0;
    virtual BYTE GetMaxLevel() const = 0;
    virtual BOOL GetMonsterClass() const = 0;

    virtual sPartyInfo& GetPartyInfo(sPartyInfo &) const = 0;

    virtual int AttachCustomTeleportCapability(int a2) const = 0; // sub_69DA80
    virtual int RegisterEventHandler(int a2, int a3, int a4) const = 0; // sub_69DAB0
    virtual int UnregisterEventHandler(int a2) const = 0; // sub_69DAE0

    virtual int RaiseEvent(int a2, int a3, int a4, int a5) const = 0; // sub_69DB40
    virtual int RaiseEvent(int a2, int a3, int a4) const = 0; // sub_69DB10

    virtual int SetEventResult(int a2) const = 0; // sub_69DB70
    virtual int RaiseEventSingle(int a2, int a3, int a4) const = 0; // sub_69E990
    virtual int ShowMenu(int a2, int a3, int a4, int a5, int a6, int a7, int a8) const = 0; // sub_69DBA0
    virtual int __cdecl TerminateMenu() const = 0; // sub_69DBD0
    virtual int GetMenuContext() const = 0; // sub_69DBF0
    virtual int __cdecl OutputChatMsg() = 0; // sub_69DC20
    virtual int SetCharName() const = 0; // sub_69DC50
    /*virtual int AddAvailableInteraction() const = 0; // sub_69DC80
    virtual int CompareGold() const = 0; // sub_69DCB0
    virtual int OffsetGold() const = 0; // sub_69DCE0
    virtual int OffsetExpPoint() const = 0; // sub_69DD10
    virtual int OffsetSkillPoint() const = 0; // sub_69DD40
    virtual int GetGuildName() const = 0; // sub_69DD70
    virtual int GetPCGuildMemberAverageLevel() const = 0; // sub_69DDA0
    virtual int GetPCGuildMemberHighestLevel() const = 0; // sub_69DDD0
    virtual int GetQuestData() const = 0; // sub_69DE00
    virtual int PrepareQuestData() const = 0; // sub_69DE30
    virtual int PrepareClosedQuestData() const = 0; // sub_69DE60
    virtual int SaveClearQuestNow() const = 0; // sub_69DE90
    virtual int GetQuestStatus() const = 0; // sub_69DEC0
    virtual int GetQuestStatusByName() const = 0; // sub_69DEF0
    virtual int UpdateQuestStatus() const = 0; // sub_69DF20
    virtual int SaveQuestNow() const = 0; // sub_69DF50
    virtual int GetQuestAchievementCount() const = 0; // sub_69DF80
    virtual int GetQuestEndDate(int a1, int a2) const = 0; // sub_69DFB0
    virtual int GetQuestStatus() const = 0; // sub_69DFF0
    virtual int GetQuestAchievementCountByName() const = 0; // sub_69E020
    virtual int AddQuestAchievementCount() const = 0; // sub_69E050
    virtual int SetQuestAchievementCount() const = 0; // sub_69E080
    virtual int GetRecvQuestCount() const = 0; // sub_69EF90
    virtual int UpdateQuestContentsString() const = 0; // sub_69E0B0
    virtual int UpdateQuestStartDataAll() const = 0; // sub_69E0E0
    virtual int UpdateQuestTimeLimit() const = 0; // sub_69E110
    virtual int UpdateQuestNpcID() const = 0; // sub_69E140
    virtual int SendQuestEventMessage() const = 0; // sub_69E170
    virtual int SendQuestNpcChat() const = 0; // sub_69E1A0
    virtual int SendQuestStartTimeBar() const = 0; // sub_69E1D0
    virtual int SendQuestCatchMobResult() const = 0; // sub_69E200
    virtual int IsCatchMob() const = 0; // sub_69E230
    virtual int DeleteMobForCatchQuest() const = 0; // sub_69E260
    virtual int SpawnCatchCOSForCatchQuest() const = 0; // sub_69E290
    virtual int SearchHaveCatchMob() const = 0; // sub_69E2C0
    virtual int DeleteCatchCOS() const = 0; // sub_69E2F0
    virtual int SetLifeState() const = 0; // sub_69E320
    virtual int SetChangeObjActiveState() const = 0; // sub_69E350
    virtual int SetInsDungeonInfo() const = 0; // sub_69E370
    virtual int GetInsDungeonInfo() const = 0; // sub_69E3A0
    virtual int SetEventResultInfo() const = 0; // sub_69ED90
    virtual int GetEventResultInfo() const = 0; // sub_69EDC0
    virtual int Zoe() const = 0; // sub_69E3D0
    virtual int GetVolatileQuestData() const = 0; // sub_69E430
    virtual int GetVolatileEventData() const = 0; // sub_69E460
    virtual int RegisterSpot_Object() const = 0; // sub_69E520
    virtual int RegisterSpot_Position() const = 0; // sub_69E550
    virtual int UnregisterSpot() const = 0; // sub_69E580
    virtual int UnregisterSpotByQuest() const = 0; // sub_69E5B0
    virtual int nullsub_1() const = 0; // sub_703BC0
    virtual int InquireSameItem() const = 0; // sub_69E5E0
    virtual int FindEmptySlotNum() const = 0; // sub_69E610
    virtual int AddItem_EXT() const = 0; // sub_69E640
    virtual int DelItem_EXT() const = 0; // sub_69E670
    virtual int MutateItemAt() const = 0; // sub_69E6A0
    virtual int CompareMyAndGuildMaster() const = 0; // sub_69E400
    virtual int QB_ForceBlockOperation() const = 0; // sub_69E700
    virtual int QB_ReleaseBlockedJob() const = 0; // sub_69E730
    virtual int QB_IsBlocked() const = 0; // sub_69E760
    virtual int GetCurArmorType() const = 0; // sub_69E6D0
    virtual int GetGender() const = 0; // sub_69E790
    virtual int GetCountry() const = 0; // sub_69E7C0
    virtual void __stdcall AddDisplayEffect(int a1, char a2, ...) = 0; // sub_69E7F0
    virtual int ForceDropItem() const = 0; // sub_69E820
    virtual int GetWorldLayerData() const = 0; // sub_69CE30
    virtual int SetWorldLayerData() const = 0; // sub_69CE00
    virtual int GetInstanceWorldUsers(int a1, int a2, int a3) = 0; // sub_69FA90
    virtual int SaveCurPosAsLastTelPosition() const = 0; // sub_69CE60
    virtual int GetEquipedWeaponType() const = 0; // sub_69E850
    virtual int RefreshEventGuideData() const = 0; // sub_69E880
    virtual int SetAvailableInteractionPerGObj() const = 0; // sub_69E8A0
    virtual int BackupData() const = 0; // sub_69E8D0
    virtual int AllocMsgForPeer() const = 0; // sub_69E900
    virtual int SendMsgToPeer() const = 0; // sub_69E930
    virtual int SetTalkMenuTitle() const = 0; // sub_69E960
    virtual int RegisterTalkMenuItem() const = 0; // sub_69E9C0
    virtual int IsFirstTalkMenuEnable() const = 0; // sub_69EA40
    virtual int ShowFirstTalkMenu() const = 0; // sub_69E9F0
    virtual int EnableTalkMenuItem() const = 0; // sub_69EA10
    virtual int ResetQuestBlock() const = 0; // sub_69EAA0
    virtual int RegisterNPCInteractionBlock() const = 0; // sub_69EAC0
    virtual int UnregisterNPCInteractionBlock() const = 0; // sub_69EAF0
    virtual int IsInteractionAble() const = 0; // sub_69EB20
    virtual int ChattingByProxy() const = 0; // sub_69EB80
    virtual int ChattingByProxy() const = 0; // sub_69EB80
    virtual int ChattingByProxyArg() const = 0; // sub_69EBB0
    virtual int ChattingByProxyArg() const = 0; // sub_69EBB0
    virtual int SetCharacterState() const = 0; // sub_69EBE0
    virtual int EnterWorld() const = 0; // sub_69EC10
    virtual int ExpandInventory() const = 0; // sub_69EC40
    virtual int ExpandInventory() const = 0; // sub_69EC70
    virtual int IsUsingBunusTimeOfGoldTimeItem() const = 0; // sub_69ECA0
    virtual int IsQuestByCompositeItem() const = 0; // sub_69ECD0
    virtual int UseQuestByCompositeItem() const = 0; // sub_69ED00
    virtual int GetRemainCountOfQuestByCompositeItem() const = 0; // sub_69ED30
    virtual int GetMaxCountOfQuestByCompositeItem() const = 0; // sub_69ED60
    virtual int GetEventHandlers() const = 0; // sub_69EDF0
    virtual int GetWorldLayerEventHandlers() const = 0; // sub_69EED0
    virtual int LeaveWorldReq() const = 0; // sub_69EE20
    virtual int REH_OnTrapped() const = 0; // sub_69CE80
    virtual int GetCurSelectedObj() const = 0; // sub_69CDA0
    virtual int IHaveTradeItem() const = 0; // sub_69EE40
    virtual int IHaveCart() const = 0; // sub_69EE70
    virtual int IHaveQuestCart() const = 0; // sub_69EEA0
    virtual int GetWorldLayerEventHandlers() const = 0; // sub_69EED0
    virtual int IHaveMercenary() const = 0; // sub_69EF00
    virtual int BanToDefaultWorld() const = 0; // sub_69EF30
    virtual int ActivateAI() const = 0; // sub_69EF60
    virtual int IsPCBangUser() const = 0; // sub_69EFC0
    virtual int GetMonsterType() const = 0; // sub_69EFF0
    virtual int IsPartySupportMonster() const = 0; // sub_69F020
    virtual int ConsumeHpMp() const = 0; // sub_69F050
    virtual int IsChinsTombMonster() const = 0; // sub_69F080
    virtual int EnterScriptMode() const = 0; // sub_69F0B0
    virtual int UpdateHwanLevel() const = 0; // sub_69F0E0
    virtual int SetBodyMode() const = 0; // sub_69F110
    virtual int IsTraniningCampMento() const = 0; // sub_69F140
    virtual int Event_HiSilkRoad_Data_Update() const = 0; // sub_69F170
    virtual int IsHiSilkRoadEvent() const = 0; // sub_69F190
    virtual int CountEmptyInventory() const = 0; // sub_69F1C0
    virtual int EngageBuffSkill() const = 0; // sub_69F1F0
    virtual int PostTempleReputationSetReq() const = 0; // sub_69F220
    virtual int PostTempleReputationCheckReq() const = 0; // sub_69F250
    virtual int NotifyClientAPIconStatus() const = 0; // sub_69F280
    virtual int IsActiveBuff() const = 0; // sub_69F2A0
    virtual int IsActiveBuffByItem() const = 0; // sub_69F2D0
    virtual int IsCanUseItem() const = 0; // sub_69F300
    virtual int UpdateRamadanVoucherPayCount() const = 0; // sub_69F330
    virtual int IsRamadanVoucherPlayer() const = 0; // sub_69F390
    virtual int GetRamadanVoucherRanking() const = 0; // sub_69F360
    virtual int GetFestivalReceipt() const = 0; // sub_69F870
    virtual int SetFestivalReceipt() const = 0; // sub_69F8A0
    virtual int OnUseEventBombAck() const = 0; // sub_69F3C0
    virtual int GetRemainSkillPoint() const = 0; // sub_69F3F0
    virtual int IsIsOptionalFunctionOfRegion() const = 0; // sub_69F420
    virtual int ShowRewardWindow() const = 0; // sub_69F450
    virtual int ADD_EVENT_NPC_COUNT() const = 0; // sub_69F480
    virtual int IsAccomplishedCollectionBook_Theme() const = 0; // sub_69F4E0
    virtual int IsAccomplishedCollectionBook_Theme() const = 0; // sub_69F4B0
    virtual int IsRegisteredCollectionBook_Item() const = 0; // sub_69F540
    virtual int IsRegisteredCollectionBook_Item() const = 0; // sub_69F510
    virtual int OnUseEventGhostAmulet() const = 0; // sub_69F570
    virtual int TC_IsJobState() const = 0; // sub_69F5A0
    virtual int TC_GetJobLevel() const = 0; // sub_69F5D0
    virtual int TC_GainJobExp() const = 0; // sub_69F600
    virtual int TC_IsInTCQuest() const = 0; // sub_69F630
    virtual int TC_IsInSafeMode() const = 0; // sub_69F660
    virtual int TC_SetSafeMode() const = 0; // sub_69F690
    virtual int ShowExplicitRewardWindow() const = 0; // sub_69F6C0
    virtual int IsHavingTCQuest() const = 0; // sub_69F6F0
    virtual int IsPremiumQuestByPremiumQuestTicket() const = 0; // sub_69F720
    virtual int GetRemainCountOfQuestByTicketItem() const = 0; // sub_69F750
    virtual int IsAvailableProcessPremiumQuest() const = 0; // sub_69F780
    virtual int GetCompletePremiumQuestCountByPremiumQuestTicket() const = 0; // sub_69F7B0
    virtual int UsePremiumQuestByItem() const = 0; // sub_69F7E0
    virtual int TC_IsInNewTrade() const = 0; // sub_69F810
    virtual int GetPlayTimeMin() const = 0; // sub_69F840
    virtual int IsSilkRoadRBuffReceipt() const = 0; // sub_69F8D0
    virtual int UpdateSilkRBuffReceipt() const = 0; // sub_69F900
    virtual int GetMoonPotReceipt() const = 0; // sub_69F920
    virtual int SetMoonPotReceipt() const = 0; // sub_69F950
    virtual int IsGetSurvivalEventReward() const = 0; // sub_69F980
    virtual int UpdateSurvivalEventReward() const = 0; // sub_69F9B0
    virtual int GetPlayCountSurvivalEvent() const = 0; // sub_69F9D0
    virtual int IsGetForgottenEventReward() const = 0; // sub_69FA00
    virtual int UpdateForgottenEventReward() const = 0; // sub_69FA30*/
};

#endif
