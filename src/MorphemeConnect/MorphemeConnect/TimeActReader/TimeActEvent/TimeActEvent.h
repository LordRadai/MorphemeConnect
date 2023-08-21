#include "../../MemReader/MemReader.h"

enum TimeActGroupType
{
	SoundCtrl = 200,
	AiCtrl = 300,
	DamageCtrl = 1100,
	BulletCtrl = 1150,
	ParryCtrl = 1220,
	CameraCtrl = 1500,
	SfxCtrl = 2100,
	FootEffectCtrl = 2200,
	WeaponCtrl = 2300,
	LockOnCtrl = 2400,
	StaminaCtrl = 101000,
	DamageActionCtrl = 110000,
	AttackCtrl = 120000,
	GimmickCtrl = 210000,
	ItemCtrl = 220000,
	ChrGenerateCtrl = 230000,
	DeadCtrl = 240000,
	ObjGenerateCtrl = 250000,
	ModelCtrl = 260000,
	ChrPartsCtrl = 270000,
	ChrMoveCtrl = 280000,
	ChrCollidCtrl = 290000,
	EventCtrl = 300000,
	SpEffectCtrl = 310000
};

enum TimeActEventType
{

};

class TimeActEvent
{
public:
	struct EventData
	{
		UINT64 m_id;
		BYTE m_args[16];

		EventData();
		EventData(ifstream* tae);
	};

	float m_start;
	float m_end;
	EventData* m_eventData;

	TimeActEvent();
	TimeActEvent(ifstream* tae);
};

class EventGroup
{
public:
	struct EventGroupData
	{
		UINT64 m_eventType;
		std::vector<int> m_eventOffsets;

		EventGroupData();
		EventGroupData(ifstream* tae, int count);
	};

	UINT64 m_count;
	std::vector<TimeActEvent> m_event;
	EventGroupData* m_groupData;
	UINT64 m_pad;

	EventGroup();
	EventGroup(ifstream* tae);
};