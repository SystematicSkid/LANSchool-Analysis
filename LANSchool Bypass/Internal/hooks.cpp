#include "../lanschool.h"
#include "PolyHook.hpp"

// Hooks
// WinSock
PLH::IATHook* wsock32_send_hook;
PLH::IATHook* wsock32_recv_hook;

// Student
PLH::X86Detour* student_alert_bad_word_hook;
PLH::X86Detour* student_clear_student_desktop;

namespace Internal
{
	// Original functions
	tSend oSend;
	tRecv oRecv;

	namespace WinSock
	{
		int __stdcall hkSend(SOCKET s, const char * buf, int len, int flags)
		{
			printf("[hkSend] %s\n", buf);
			return oSend(s, buf, len, flags);
		}

		int __stdcall hkRecv(SOCKET s, char * buf, int len, int flags)
		{
			printf("[hkRecv] %s\n", buf);
			return oRecv(s, buf, len, flags);
		}
	}

	namespace Student
	{
		BOOL __fastcall hkAlertBadWord(int arglist)
		{
			printf("[Bad Word] %s\n", (const char*)arglist);
			return 0; // Don't alert teacher, end function
		}

		void* __cdecl hkClearStudentDesktop(int flags) // Meant to return a handle of CreateToolhelp32Snapshot
		{
			printf("[Alert] Teacher tried to clear desktop with flag %i\n", flags);
			return 0; // Return empty handle 
		}
	}

	// Setup wsock32 hooks
	bool Hooks::InitNetworkHooks()
	{
		wsock32_send_hook = new PLH::IATHook();
		wsock32_send_hook->SetupHook("WSOCK32.dll", "send", (BYTE*)&WinSock::hkSend);
		if (!wsock32_send_hook->Hook())
			return false;
		oSend = wsock32_send_hook->GetOriginal<tSend>();

		wsock32_recv_hook = new PLH::IATHook();
		wsock32_recv_hook->SetupHook("WSOCK32.dll", "recv", (BYTE*)&WinSock::hkRecv);
		if (!wsock32_recv_hook->Hook())
			return false;
		oRecv = wsock32_recv_hook->GetOriginal<tRecv>();

		return true;
	}

	bool Hooks::InitStudentHooks()
	{
		student_alert_bad_word_hook = new PLH::X86Detour();
		student_alert_bad_word_hook->SetupHook((BYTE*)Internal::addresses.student_alert_bad_word, (BYTE*)&Student::hkAlertBadWord);
		if (!student_alert_bad_word_hook->Hook())
			return false;

		student_clear_student_desktop = new PLH::X86Detour();
		student_clear_student_desktop->SetupHook((BYTE*)Internal::addresses.student_clear_student_desktop, (BYTE*)&Student::hkClearStudentDesktop);
		if (!student_clear_student_desktop->Hook())
			return false;

		return true;
	}

	bool Hooks::Init()
	{
		if (!InitNetworkHooks())
			return false;
		if (!InitStudentHooks())
			return false;
		return true;
	}
	Hooks hooks;
}

