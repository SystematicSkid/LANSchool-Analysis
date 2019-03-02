#include "../lanschool.h"

namespace Internal
{
	bool Addresses::Init()
	{
		wsock32 = GetModuleHandle("WSOCK32.dll");
		XASSERT(wsock32);

		student_alert_bad_word = Memory::SigScan("55 8B EC 83 E4 F8 81 EC ? ? ? ? A1 ? ? ? ? 33 C4 89 84 24 ? ? ? ? 53 56 57 33 DB", "student.exe");
		student_clear_student_desktop = Memory::SigScan("55 8B EC 83 E4 F8 B8 ? ? ? ? E8 ? ? ? ? A1 ? ? ? ? 33 C4 89 84 24 ? ? ? ? 56", "student.exe");
		student_close_lsk_web_svr = Memory::SigScan("56 57 8B 3D ? ? ? ? BE ? ? ? ? 8D 49 00 8B 06 85 C0 74 0E", "student.exe");

		return true;
	}

	Addresses addresses;
}