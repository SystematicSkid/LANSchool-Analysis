#pragma once
namespace Internal
{
	// Prototypes
	using tSend = int(__stdcall*)(SOCKET s, const char *buf, int len, int flags);
	using tRecv = int(__stdcall*)(SOCKET s, char *buf, int len, int flags);

	using tAlertBadWord = BOOL(__fastcall*)(int arglist);
	using tClearStudentDesktop = void*(__cdecl*)(int flags);
	using tNewDesktopDetected = bool(__stdcall*)(int a1);

	namespace WinSock
	{
		int __stdcall hkSend(SOCKET s, const char *buf, int len, int flags);
		int __stdcall hkRecv(SOCKET s, char *buf, int len, int flags);
	}

	namespace Student
	{
		BOOL __fastcall hkAlertBadWord(int arglist);
		void* __cdecl hkClearStudentDesktop(int flags);
		bool __stdcall hkNewDesktopDetected(int a1);
	}

	class Hooks
	{
	private:
		bool InitNetworkHooks();
		bool InitStudentHooks();
	public:
		bool Init();
	};
	extern Hooks hooks;
}