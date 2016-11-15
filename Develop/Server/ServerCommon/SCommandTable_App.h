#pragma once

#include "ServerCommonLib.h"

enum SAppCommandTable
{
	// 커맨드 선언 //////////////////////////////////////////////////////////////////////////
	// 커맨드 번호 1 000 000 001 ~ 1 000 000 999 까지 사용

	// 로그 출력(LOG) ------------------------------------------------------------------------------------
	MAPP_LOG_OUT_PUT				= 1000000001,

};

// 어플리케이션에서 사용하는 커맨드 등록
SCOMMON_API void AddAppCommandTable();
