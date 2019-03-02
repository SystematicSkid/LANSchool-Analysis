#pragma once
#define _CRT_SECURE_NO_WARNINGS

// win
#include <Windows.h>
#include <winternl.h>
#include <comdef.h>
#include <minwindef.h>
#include <winbase.h>
#include <intrin.h>
#include <psapi.h>

// stl
#include <vector>
#include <deque>
#include <list>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <clocale>
#include <algorithm>
#include <sstream>
#include <cmath>

// debug
#define XASSERT( x ) if( !x ){ MessageBoxW( 0, L#x, 0, 0 ); return false; }

// util
#include "memory.h"
#include "xorstr.h"

// core
#include "./Internal/addresses.h"
#include "./Internal/hooks.h"

#include "enums.h"

namespace LANSchool
{
	namespace Student
	{
		HANDLE CloseLskWebSvr();
		void BypassMessage(MessageType msg);
		void SetChannel(int channel);
	}
}