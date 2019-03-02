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

		void BypassMessage(MessageType msg)
		{
			switch (msg)
			{
			case PEEK_DESKTOP_STREAM_START:
				*(uintptr_t*)Internal::addresses.student_peek_desktop_update_rate = INT_MAX;
				/*
				cmp     PeekDesktopUpdateRate, 0
				jnz     loc_465A42   
				*/
				break;
			case PEEK_DESKTOP_STREAM_INPUT_EVENT:	
			case PEEK_DESKTOP_STREAM_SETTING_CHANGE:
			case PEEK_DESKTOP_STREAM_STOP:
				*(uintptr_t*)Internal::addresses.student_is_streaming_desktop = 0;
				/*
				 mov     ecx, IsStreamingDesktop
				 test    ecx, ecx
				 jz      short loc_465A42
				*/
				break;
			default:
				break;
			}
		}

		void SetChannel(int channel)
		{
			*(int*)Internal::addresses.student_current_channel = channel;
		}

		Teacher* GetTeacher()
		{
			return Internal::addresses.student_current_teacher;
		}
	}
}