#include "../lanschool.h"
#include "PolyHook.hpp"

// Hooks
// WinSock
PLH::IATHook* wsock32_send_hook;
PLH::IATHook* wsock32_recv_hook;

// Student
PLH::X86Detour* student_alert_bad_word_hook;
PLH::X86Detour* student_clear_student_desktop_hook;
PLH::X86Detour* student_new_desktop_detected_hook;

namespace Internal
{
	// Original functions
	tSend oSend;
	tRecv oRecv;

	namespace WinSock
	{
		int __stdcall hkSend(SOCKET s, const char * buf, int len, int flags)
		{
			printf(XorStr("[hkSend] %s\n"), buf);
			return oSend(s, buf, len, flags);
		}

		int __stdcall hkRecv(SOCKET s, char * buf, int len, int flags)
		{
			printf(XorStr("[hkRecv] %s\n"), buf);
			/*
			KeystrokeHistoryRequest: len 10
									 flags: 0
									 socket: fnSocket(2,1,6)
									 buf: *(_WORD *)buf = 0x360;
										  *(_WORD *)&buff[2] = dword_67EFDC;		--> teacher.exe
			*/
			return oRecv(s, buf, len, flags);
		}
	}

	namespace Student
	{
		BOOL __fastcall hkAlertBadWord(int arglist)
		{
			printf(XorStr("[Bad Word] %s\n"), (const char*)arglist);
			return 0; // Don't alert teacher, end function
		}

		void* __cdecl hkClearStudentDesktop(int flags) // Meant to return a handle of CreateToolhelp32Snapshot
		{
			printf(XorStr("[Alert] Teacher tried to clear desktop with flag %i\n"), flags);
			return 0; // Return empty handle 
		}

		bool __stdcall hkNewDesktopDetected(int a1)
		{
			printf(XorStr("[Alert] Trying to detect desktop change : 0x%p\n", a1));
			return false;
		}
	}

	// Setup wsock32 hooks
	bool Hooks::InitNetworkHooks()
	{
		wsock32_send_hook = new PLH::IATHook();
		wsock32_send_hook->SetupHook(XorStr("WSOCK32.dll"), XorStr("send"), (BYTE*)&WinSock::hkSend);
		if (!wsock32_send_hook->Hook())
			return false;
		oSend = wsock32_send_hook->GetOriginal<tSend>();

		wsock32_recv_hook = new PLH::IATHook();
		wsock32_recv_hook->SetupHook(XorStr("WSOCK32.dll"), XorStr("recv"), (BYTE*)&WinSock::hkRecv);
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

		student_clear_student_desktop_hook = new PLH::X86Detour();
		student_clear_student_desktop_hook->SetupHook((BYTE*)Internal::addresses.student_clear_student_desktop, (BYTE*)&Student::hkClearStudentDesktop);
		if (!student_clear_student_desktop_hook->Hook())
			return false;
		
		student_new_desktop_detected_hook = new PLH::X86Detour();
		student_new_desktop_detected_hook->SetupHook((BYTE*)Internal::addresses.student_new_desktop_detected, (BYTE*)&Student::hkNewDesktopDetected);
		if (!student_new_desktop_detected_hook->Hook())
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

