#ifndef _GAI_STATE_H
#define _GAI_STATE_H

enum AI_BEHAVIOR_STATE
{
	AI_BEHAVIOR_NONE		= -1,
	AI_BEHAVIOR_PEACE		= 0,	// 평화로운 상태
	AI_BEHAVIOR_COMBAT		= 1,	// 전투중
	AI_BEHAVIOR_MISSION		= 2,	// 미션
	AI_BEHAVIOR_DEAD		= 3,	// 죽었음
	AI_BEHAVIOR_RETURN		= 4,	// 전투종료후 귀환중
	AI_BEHAVIOR_SESSION		= 5,	// 세션상태
	AI_BEHAVIOR_SIZE,
};

enum AI_COMBAT_STATE
{
	AI_COMBAT_NONE = -1,
	AI_COMBAT_COMBAT = 0,
	AI_COMBAT_FLEE,
	AI_COMBAT_VICTORY,
	AI_COMBAT_PROLOGUE,

	AI_COMBAT_SIZE
};








#endif