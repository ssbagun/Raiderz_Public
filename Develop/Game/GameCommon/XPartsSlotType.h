#pragma once

// 플레이어의 메쉬 파츠
enum XPlayerPartsSlotType
{
	PLAYER_PARTS_SLOT_HEAD = 0,
	PLAYER_PARTS_SLOT_HAIR,
	PLAYER_PARTS_SLOT_FACE,
	PLAYER_PARTS_SLOT_HANDS,
	PLAYER_PARTS_SLOT_FEET,
	PLAYER_PARTS_SLOT_BODY,
	PLAYER_PARTS_SLOT_LEG,

	PLAYER_PARTS_SLOT_LWEAPON,
	PLAYER_PARTS_SLOT_RWEAPON,

	PLAYER_PARTS_SLOT_QUIVER,
	PLAYER_PARTS_SLOT_MAX
};


// NPC의 메쉬 파츠
enum XNPCPartsSlotType
{
	NPC_PARTS_SLOT_HAIR = 0,
	NPC_PARTS_SLOT_FACE,
	NPC_PARTS_SLOT_HEAD,
	NPC_PARTS_SLOT_CHEST,
	NPC_PARTS_SLOT_LEG,
	NPC_PARTS_SLOT_HANDS,
	NPC_PARTS_SLOT_FEET,
	NPC_PARTS_SLOT_LWEAPON,
	NPC_PARTS_SLOT_RWEAPON,

	NPC_PARTS_SLOT_MAX
};

class XPartsSlotType
{
public:
	XPartsSlotType() {}
	virtual ~XPartsSlotType() {}

	static XPlayerPartsSlotType Slot2LookSlot( SH_ITEM_SLOT nSlot )
	{
		switch(nSlot)
		{
		case ITEMSLOT_HEAD	: return PLAYER_PARTS_SLOT_HEAD;
		case ITEMSLOT_FACE	: return PLAYER_PARTS_SLOT_FACE;	// NPC 가 이 슬롯으로 로딩하는 경우가 있다
		case ITEMSLOT_HANDS : return PLAYER_PARTS_SLOT_HANDS;
		case ITEMSLOT_FEET	: return PLAYER_PARTS_SLOT_FEET;
		case ITEMSLOT_BODY	: return PLAYER_PARTS_SLOT_BODY;
		case ITEMSLOT_LEG	: return PLAYER_PARTS_SLOT_LEG;
		case ITEMSLOT_LWEAPON : 
		case ITEMSLOT_LWEAPON2 : 
			return PLAYER_PARTS_SLOT_LWEAPON;
		case ITEMSLOT_RWEAPON : 
		case ITEMSLOT_RWEAPON2 : 
			return PLAYER_PARTS_SLOT_RWEAPON;
#ifndef _MADDUCK
		default:
			_ASSERT(FALSE);
#endif // _MADDUCK
		}
		return PLAYER_PARTS_SLOT_MAX;
	}

	static XPlayerPartsSlotType NetSlot2LookSlot( SH_FEATURE_ITEMSLOT nSlot )
	{
		switch(nSlot)
		{
		case FEATURE_ITEMSLOT_HEAD:		return PLAYER_PARTS_SLOT_HEAD;
		case FEATURE_ITEMSLOT_BODY:		return PLAYER_PARTS_SLOT_BODY;
		case FEATURE_ITEMSLOT_HANDS:	return PLAYER_PARTS_SLOT_HANDS;
		case FEATURE_ITEMSLOT_LEG:		return PLAYER_PARTS_SLOT_LEG;
		case FEATURE_ITEMSLOT_FEET:		return PLAYER_PARTS_SLOT_FEET;
		case FEATURE_ITEMSLOT_LWEAPON:
		case FEATURE_ITEMSLOT_LWEAPON2:
			return PLAYER_PARTS_SLOT_LWEAPON;
		case FEATURE_ITEMSLOT_RWEAPON:	
		case FEATURE_ITEMSLOT_RWEAPON2:
			return PLAYER_PARTS_SLOT_RWEAPON;
		}

		return PLAYER_PARTS_SLOT_HEAD;
	}
};
