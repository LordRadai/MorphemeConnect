#include "../TimeActEvent/TimeActEventData/TimeActEventData.h"
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

class TimeActEvent
{
public:
	struct EventData
	{
        int m_id;
        int m_pad;
		UINT64 m_argsOffset;
        TimeActEventData* m_args;

		EventData();
		EventData(ifstream* tae);
	};

	UINT64 m_startOffset;
	UINT64 m_endOffset;
	UINT64 m_eventDataOffset;

	float m_start;
	float m_end;
	EventData* m_eventData;

	TimeActEvent();
	TimeActEvent(ifstream* tae);

	void GenerateBinary(ofstream* tae);
	int GetArgumentsSize();
};

class EventGroup
{
public:
	struct EventGroupData
	{
		UINT64 m_eventType;
		UINT64 m_offset;

		EventGroupData();
		EventGroupData(ifstream* tae);
	};

	UINT64 m_count;
	UINT64 m_eventsOffset;
	UINT64 m_groupDataOffset;
	UINT64 m_pad;

	std::vector<TimeActEvent> m_event;
	std::vector<UINT64> m_eventOffset;
	EventGroupData* m_groupData;

	EventGroup();
	EventGroup(ifstream* tae);

	void GenerateBinary(ofstream* tae);
};