#pragma once

class StudentInfo
{
public:
	char pad_0000[8]; //0x0000
	int32_t addr; //0x0008
	char pad_000C[4]; //0x000C
	int32_t wChannel; //0x0010
	DWORD dwMajorVersion; //0x0014
	DWORD dwMinorVersion; //0x0018
	DWORD dwPacketVersion; //0x001C
	DWORD dwState; //0x0020
	DWORD dwConnectionState; //0x0024
	DWORD dwConectionStateChangedTime; //0x0028
	DWORD dwReportedState; //0x002C
	bool bNonResponsive; //0x0030
	char pad_0031[3]; //0x0031
	DWORD dwGetInfoStartTime; //0x0034
	char pad_0038[40]; //0x0038
	HANDLE hGetInfoThread; //0x0060
	int32_t iStructInUseCnt; //0x0064
	bool bFreeStructWhenDone; //0x0068
	char pad_0069[3]; //0x0069
	char* szLoginName; //0x006C
	char pad_0070[60]; //0x0070
	char* szMachineName; //0x00AC
	char pad_00B0[60]; //0x00B0
	char* szRunningApp; //0x00EC
	char pad_00F0[496]; //0x00F0
	int32_t iStudentType; //0x02E0
	int32_t bCustomThumbnailLocation; //0x02E4
	char pad_02E8[12]; //0x02E8
	int32_t appLimitAddr; //0x02F4
	char pad_02F8[4]; //0x02F8
	int32_t usbLimitAddr; //0x02FC
	int32_t blankScreenAddr; //0x0300
	int32_t bcastScreenAddr; //0x0304
	char* szLastQuestion; //0x0308
	char pad_030C[196]; //0x030C
	int32_t lastThumbnail; //0x03D0
	DWORD dwSecureKey; //0x03D4
	char pad_03D8[68]; //0x03D8
	HANDLE hGetStudentThumbnailThread; //0x041C
	HANDLE hAthenticateToStudentThread; //0x0420
	char pad_0424[12]; //0x0424
	char* szMovedByTeacher; //0x0430
	char pad_0434[272]; //0x0434
	bool bIsLite; //0x0544
	char pad_0545[3]; //0x0545
	DWORD dwLastSSPIAuthenticationFailure; //0x0548
	char pad_054C[24]; //0x054C
	DWORD dwUserAccountControl; //0x0564
	char pad_0568[208]; //0x0568
	bool bReportedTestName; //0x0638
	char pad_0639[3]; //0x0639
	bool bIsWireless; //0x063C
	char pad_063D[3]; //0x063D
	bool bThisStudentReallyIsATeacher; //0x0640
	char pad_0641[3]; //0x0641
	int32_t wTeacherTCPPort; //0x0644
	DWORD dwTeacherState; //0x0648
	bool bTeacherCanPair; //0x064C
	char pad_064D[5]; //0x064D
	int8_t bSteadyStateMode; //0x0652
	char pad_0653[341]; //0x0653
	bool bTeacherUsingChannelGroups; //0x07A8
	char pad_07A9[3]; //0x07A9
	int32_t iLastListViewIndex; //0x07AC
	bool bNoKeystrokeMon; //0x07B0
	char pad_07B1[3]; //0x07B1
	char* szLastIpAddress; //0x07B4
	char pad_07B8[60]; //0x07B8
	char* szLastActivity; //0x07F4
	char pad_07F8[60]; //0x07F8
	DWORD dwCapabilityDemonstrate; //0x0834
	DWORD dwCapabilityMonitor; //0x0838
	DWORD dwCapabilityRestrict; //0x083C
	DWORD dwCapabilityAdminister; //0x0840
	DWORD dwCapabilityManage; //0x0844
}; //Size: 0x844