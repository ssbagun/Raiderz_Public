// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.
//

#pragma once

#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable : 4996)		// sprintf_s ...
#pragma warning (disable : 4244)	// warning C4244: '=' : 'int'에서 'float'(으)로 변환하면서 데이터가 손실될 수 있습니다.
#pragma warning (disable : 4305)	// warning C4305: '인수' : 'double'에서 'float'(으)로 잘립니다.
#pragma warning (disable : 4267)	// warning C4267: '=' : 'size_t'에서 'int'(으)로 변환하면서 데이터가 손실될 수 있습니다.

#define WIN32_LEAN_AND_MEAN		// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일입니다.
#include <windows.h>
// C의 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <algorithm>
#include <cctype>
#include "MTstring.h"

using namespace std;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <windows.h>
#include <mmsystem.h>

#include "MProfiler.h"
#include "MStatisticsProfiler.h"

#include "CSDef.h"
#include "CTransData.h"

#include "MTime.h"

#include "MTest.h"

#include "MiNet.h"

#pragma warning( disable : 4204 )

