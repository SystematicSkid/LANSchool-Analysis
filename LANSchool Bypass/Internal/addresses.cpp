#include "../lanschool.h"

namespace Internal
{
	bool Addresses::Init()
	{
		wsock32 = GetModuleHandle(XorStr("WSOCK32.dll"));
		XASSERT(wsock32);

		student_alert_bad_word = Memory::SigScan(XorStr("55 8B EC 83 E4 F8 81 EC ? ? ? ? A1 ? ? ? ? 33 C4 89 84 24 ? ? ? ? 53 56 57 33 DB"), XorStr("student.exe"));
		XASSERT(student_alert_bad_word);
		student_clear_student_desktop = Memory::SigScan(XorStr("55 8B EC 83 E4 F8 B8 ? ? ? ? E8 ? ? ? ? A1 ? ? ? ? 33 C4 89 84 24 ? ? ? ? 56"), XorStr("student.exe"));
		XASSERT(student_clear_student_desktop);
		student_close_lsk_web_svr = Memory::SigScan(XorStr("56 57 8B 3D ? ? ? ? BE ? ? ? ? 8D 49 00 8B 06 85 C0 74 0E"), XorStr("student.exe"));
		XASSERT(student_close_lsk_web_svr);
		student_new_desktop_detected = Memory::SigScan(XorStr("55 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 33 C5 89 45 FC 68 ? ? ? ? 8D 85 ? ? ? ? 6A 00 50 E8 ? ? ? ? 83 C4 0C 8D 8D ? ? ? ? 51 C7 85 ? ? ? ? ? ? ? ? FF 15"), XorStr("student.exe"));
		XASSERT(student_new_desktop_detected);

		return true;
	}

	Addresses addresses;
}