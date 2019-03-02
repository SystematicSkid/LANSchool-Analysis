#include "lanschool.h"

namespace LANSchool
{
	namespace Student
	{
		HANDLE CloseLskWebSvr()
		{
			using tCloseLskWebSvr = HANDLE(__cdecl*)(); // Assuming cdecl, could be stdcall
			tCloseLskWebSvr oCloseLskWebSvr = (tCloseLskWebSvr)Internal::addresses.student_close_lsk_web_svr;
			return oCloseLskWebSvr();
		}
	}
}