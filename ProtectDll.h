#pragma once

#include <tlhelp32.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#pragma warning (disable:4102)

BOOL NativeNtProtectVirtualMemory(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
{
	typedef LONG * NTAPI LPFN_NtProtectVirtualMemory(HANDLE, PVOID *, PULONG, ULONG, PULONG);

	LPFN_NtProtectVirtualMemory * NtProtectVirtualMemory = (LPFN_NtProtectVirtualMemory*)(GetProcAddress(GetModuleHandleA(XorStr("ntdll.dll")), XorStr("NtProtectVirtualMemory")));

	if (!NtProtectVirtualMemory)
		return FALSE;

	NtProtectVirtualMemory(GetCurrentProcess(), (PVOID*)&lpAddress, (PULONG)&dwSize, flNewProtect, lpflOldProtect);

	return TRUE;
}


#define MARKER_NORM		0x90
#define POLY_SIZE		0x2A			
#define POLY_JUMP_DIST	POLY_SIZE - 2	

#define POLY_NORM \
 __asm _emit 0xEB \
 __asm _emit POLY_JUMP_DIST \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM


int  GetRandom(int min, int max)
{
	long rnd = 0;
	_asm
	{
	osion:
		rdtsc
			xor  eax, edx
			bswap eax
			mov  rnd, eax
	}
	rnd = rnd % max;
	if (rnd < min)
		_asm call osion
	return rnd;
}

	typedef struct _UNICODE_STRING
	{
		USHORT					Length;
		USHORT					MaximumLength;
		PWSTR					Buffer;
	} UNICODE_STRING, *PUNICODE_STRING;

	typedef struct _LDR_MODULE_DUMMY_
	{
		LIST_ENTRY InLoadOrderModuleList;
		LIST_ENTRY InMemoryOrderModuleList;
		LIST_ENTRY InInitializationOrderModuleList;
		PVOID BaseAddress;

		PVOID                   EntryPoint;
		ULONG                   SizeOfImage;
		UNICODE_STRING          FullDllName;
		UNICODE_STRING          BaseDllName;
		ULONG                   Flags;
		SHORT                   LoadCount;
		SHORT                   TlsIndex;
		LIST_ENTRY              HashTableEntry;
		ULONG                   TimeDateStamp;

	} LDR_MODULE, *PLDR_MODULE;

	typedef struct _PEB_LDR_DATA_DUMMY_
	{
		ULONG Length;
		UCHAR Initialized;
		PVOID SsHandle;
		LIST_ENTRY InLoadOrderModuleList;
		LIST_ENTRY InMemoryOrderModuleList;
		LIST_ENTRY InInitializationOrderModuleList;
		PVOID EntryInProgress;
	} PEB_LDR_DATA, *PPEB_LDR_DATA;

	typedef struct PEB_DUMMY_
	{
		PVOID Dummy1;
		PVOID Dummy2;
		PVOID Dummy3;
		PPEB_LDR_DATA LDR_Data;
	} PEB_DUMMY, *PPEB_DUMMY;

	typedef struct _CLIENT_ID
	{
		HANDLE					UniqueProcess;
		HANDLE					UniqueThread;
	} CLIENT_ID, *PCLIENT_ID;

	typedef struct _RTL_DRIVE_LETTER_CURDIR
	{
		USHORT					Flags;
		USHORT					Length;
		ULONG					TimeStamp;
		UNICODE_STRING			DosPath;
	} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

	typedef struct _RTL_USER_PROCESS_PARAMETERS
	{
		ULONG					MaximumLength;
		ULONG					Length;
		ULONG					Flags;
		ULONG					DebugFlags;
		PVOID					ConsoleHandle;
		ULONG					ConsoleFlags;
		HANDLE					StdInputHandle;
		HANDLE					StdOutputHandle;
		HANDLE					StdErrorHandle;
		UNICODE_STRING			CurrentDirectoryPath;
		HANDLE					CurrentDirectoryHandle;
		UNICODE_STRING			DllPath;
		UNICODE_STRING			ImagePathName;
		UNICODE_STRING			CommandLine;
		PVOID					Environment;
		ULONG					StartingPositionLeft;
		ULONG					StartingPositionTop;
		ULONG					Width;
		ULONG					Height;
		ULONG					CharWidth;
		ULONG					CharHeight;
		ULONG					ConsoleTextAttributes;
		ULONG					WindowFlags;
		ULONG					ShowWindowFlags;
		UNICODE_STRING			WindowTitle;
		UNICODE_STRING			DesktopName;
		UNICODE_STRING			ShellInfo;
		UNICODE_STRING			RuntimeData;
		RTL_DRIVE_LETTER_CURDIR	DLCurrentDirectory[0x20];
	} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

	typedef void(*PPEBLOCKROUTINE)(PVOID PebLock);

	typedef struct _PEB_FREE_BLOCK
	{
		_PEB_FREE_BLOCK*		Next;
		DWORD					Size;
	} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;

	typedef struct _PEB
	{
		BOOLEAN                 InheritedAddressSpace;
		BOOLEAN                 ReadImageFileExecOptions;
		BOOLEAN                 BeingDebugged;
		BOOLEAN                 Spare;
		HANDLE                  Mutant;
		PVOID                   ImageBaseAddress;
		PPEB_LDR_DATA           LoaderData;
		PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
		PVOID                   SubSystemData;
		PVOID                   ProcessHeap;
		PVOID                   FastPebLock;
		PPEBLOCKROUTINE         FastPebLockRoutine;
		PPEBLOCKROUTINE         FastPebUnlockRoutine;
		ULONG                   EnvironmentUpdateCount;
		PVOID*                  KernelCallbackTable;
		PVOID                   EventLogSection;
		PVOID                   EventLog;
		PPEB_FREE_BLOCK         FreeList;
		ULONG                   TlsExpansionCounter;
		PVOID                   TlsBitmap;
		ULONG                   TlsBitmapBits[0x2];
		PVOID                   ReadOnlySharedMemoryBase;
		PVOID                   ReadOnlySharedMemoryHeap;
		PVOID*                  ReadOnlyStaticServerData;
		PVOID                   AnsiCodePageData;
		PVOID                   OemCodePageData;
		PVOID                   UnicodeCaseTableData;
		ULONG                   NumberOfProcessors;
		ULONG                   NtGlobalFlag;
		BYTE                    Spare2[0x4];
		LARGE_INTEGER           CriticalSectionTimeout;
		ULONG                   HeapSegmentReserve;
		ULONG                   HeapSegmentCommit;
		ULONG                   HeapDeCommitTotalFreeThreshold;
		ULONG                   HeapDeCommitFreeBlockThreshold;
		ULONG                   NumberOfHeaps;
		ULONG                   MaximumNumberOfHeaps;
		PVOID**					ProcessHeaps;
		PVOID                   GdiSharedHandleTable;
		PVOID                   ProcessStarterHelper;
		PVOID                   GdiDCAttributeList;
		PVOID                   LoaderLock;
		ULONG                   OSMajorVersion;
		ULONG                   OSMinorVersion;
		ULONG                   OSBuildNumber;
		ULONG                   OSPlatformId;
		ULONG                   ImageSubSystem;
		ULONG                   ImageSubSystemMajorVersion;
		ULONG                   ImageSubSystemMinorVersion;
		ULONG                   GdiHandleBuffer[0x22];
		ULONG                   PostProcessInitRoutine;
		ULONG                   TlsExpansionBitmap;
		BYTE                    TlsExpansionBitmapBits[0x80];
		ULONG                   SessionId;
	} PEB, *PPEB;

	typedef struct _TEB
	{
		NT_TIB                  Tib;
		PVOID                   EnvironmentPointer;
		CLIENT_ID               Cid;
		PVOID                   ActiveRpcInfo;
		PVOID                   ThreadLocalStoragePointer;
		PPEB                    Peb;
		ULONG                   LastErrorValue;
		ULONG                   CountOfOwnedCriticalSections;
		PVOID                   CsrClientThread;
		PVOID                   Win32ThreadInfo;
		ULONG                   Win32ClientInfo[0x1F];
		PVOID                   WOW32Reserved;
		ULONG                   CurrentLocale;
		ULONG                   FpSoftwareStatusRegister;
		PVOID                   SystemReserved1[0x36];
		PVOID                   Spare1;
		ULONG                   ExceptionCode;
		ULONG                   SpareBytes1[0x28];
		PVOID                   SystemReserved2[0xA];
		ULONG                   GdiRgn;
		ULONG                   GdiPen;
		ULONG                   GdiBrush;
		CLIENT_ID               RealClientId;
		PVOID                   GdiCachedProcessHandle;
		ULONG                   GdiClientPID;
		ULONG                   GdiClientTID;
		PVOID                   GdiThreadLocaleInfo;
		PVOID                   UserReserved[5];
		PVOID                   GlDispatchTable[0x118];
		ULONG                   GlReserved1[0x1A];
		PVOID                   GlReserved2;
		PVOID                   GlSectionInfo;
		PVOID                   GlSection;
		PVOID                   GlTable;
		PVOID                   GlCurrentRC;
		PVOID                   GlContext;
		NTSTATUS                LastStatusValue;
		UNICODE_STRING          StaticUnicodeString;
		WCHAR                   StaticUnicodeBuffer[0x105];
		PVOID                   DeallocationStack;
		PVOID                   TlsSlots[0x40];
		LIST_ENTRY              TlsLinks;
		PVOID                   Vdm;
		PVOID                   ReservedForNtRpc;
		PVOID                   DbgSsReserved[0x2];
		ULONG                   HardErrorDisabled;
		PVOID                   Instrumentation[0x10];
		PVOID                   WinSockData;
		ULONG                   GdiBatchCount;
		ULONG                   Spare2;
		ULONG                   Spare3;
		ULONG                   Spare4;
		PVOID                   ReservedForOle;
		ULONG                   WaitingOnLoaderLock;
		PVOID                   StackCommit;
		PVOID                   StackCommitMax;
		PVOID                   StackReserved;
	} TEB, *PTEB;

	PPEB_DUMMY __declspec(naked) GetPEB(void)
	{
		_asm
		{
			mov eax, fs:[0x30];
			retn;
		}
	}


	
	void HideModuleFromPEB(HINSTANCE hInstance)
	{
		PPEB_DUMMY PEB = GetPEB();

		PLIST_ENTRY FirstEntryInLoadOrder = (PLIST_ENTRY)&PEB->LDR_Data->InLoadOrderModuleList;
		PLIST_ENTRY FirstEntryInMemoryOrder = (PLIST_ENTRY)&PEB->LDR_Data->InMemoryOrderModuleList;
		PLIST_ENTRY FirstEntryInInitOrder = (PLIST_ENTRY)&PEB->LDR_Data->InInitializationOrderModuleList;

		for (PLIST_ENTRY TempEntry = FirstEntryInLoadOrder->Flink; TempEntry != FirstEntryInLoadOrder; TempEntry = TempEntry->Flink)
		{
			PLDR_MODULE TempModule = (PLDR_MODULE)((DWORD)TempEntry - 0 * sizeof(LIST_ENTRY));
			if (TempModule->BaseAddress == hInstance)
			{
				TempEntry->Blink->Flink = TempEntry->Flink;
				TempEntry->Flink->Blink = TempEntry->Blink;
				break;
			}
		}

		for (PLIST_ENTRY TempEntry = FirstEntryInMemoryOrder->Flink; TempEntry != FirstEntryInMemoryOrder; TempEntry = TempEntry->Flink)
		{
			PLDR_MODULE TempModule = (PLDR_MODULE)((DWORD)TempEntry - 1 * sizeof(LIST_ENTRY));
			if (TempModule->BaseAddress == hInstance)
			{
				TempEntry->Blink->Flink = TempEntry->Flink;
				TempEntry->Flink->Blink = TempEntry->Blink;
				break;
			}
		}

		for (PLIST_ENTRY TempEntry = FirstEntryInInitOrder->Flink; TempEntry != FirstEntryInInitOrder; TempEntry = TempEntry->Flink)
		{
			PLDR_MODULE TempModule = (PLDR_MODULE)((DWORD)TempEntry - 2 * sizeof(LIST_ENTRY));
			if (TempModule->BaseAddress == hInstance)
			{
				TempEntry->Blink->Flink = TempEntry->Flink;
				TempEntry->Flink->Blink = TempEntry->Blink;
				break;
			}
		}
	}
	void RemovePeHeader(DWORD ModuleBase)
	{
		PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)ModuleBase;
		PIMAGE_NT_HEADERS pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + (DWORD)pDosHeader->e_lfanew);

		if (pNTHeader->Signature != IMAGE_NT_SIGNATURE)
			return;

		if (pNTHeader->FileHeader.SizeOfOptionalHeader)
		{
			DWORD Protect;
			WORD Size = pNTHeader->FileHeader.SizeOfOptionalHeader;
			NativeNtProtectVirtualMemory((void*)ModuleBase, Size, PAGE_EXECUTE_READWRITE, &Protect);
			RtlZeroMemory((void*)ModuleBase, Size);
			NativeNtProtectVirtualMemory((void*)ModuleBase, Size, Protect, &Protect);
		}
	}
	void HideModule(HANDLE hModule)
	{
		PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hModule;
		if (pDOSHeader->e_magic == IMAGE_DOS_SIGNATURE)
		{
			PIMAGE_NT_HEADERS pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pDOSHeader + (DWORD)pDOSHeader->e_lfanew);
			if (pNTHeader->Signature == IMAGE_NT_SIGNATURE)
			{
				DWORD dwOld, dwSize = pNTHeader->OptionalHeader.SizeOfHeaders;
				if (NativeNtProtectVirtualMemory((LPVOID)pDOSHeader, dwSize, PAGE_READWRITE, &dwOld))
				{
					memset((void*)pDOSHeader, 0, dwSize);
					NativeNtProtectVirtualMemory((LPVOID)pDOSHeader, dwSize, dwOld, &dwOld);
				}
			}
			_TEB *pTeb = nullptr;
			_asm
			{
				mov eax, fs:[0x18]
				mov pTeb, eax
			}
			PLIST_ENTRY pList = &pTeb->Peb->LoaderData->InLoadOrderModuleList;
			for (PLIST_ENTRY pEntry = pList->Flink; pEntry != pList; pEntry = pEntry->Flink)
			{
				PLDR_MODULE pModule = (PLDR_MODULE)pEntry;
				if (pModule->BaseAddress == hModule)
				{
					pEntry = &pModule->InLoadOrderModuleList; pEntry->Blink->Flink = pEntry->Flink; pEntry->Flink->Blink = pEntry->Blink;
					memset(pEntry, 0, sizeof(LIST_ENTRY));
					pEntry = &pModule->InMemoryOrderModuleList; pEntry->Blink->Flink = pEntry->Flink; pEntry->Flink->Blink = pEntry->Blink;
					memset(pEntry, 0, sizeof(LIST_ENTRY));
					pEntry = &pModule->InInitializationOrderModuleList; pEntry->Blink->Flink = pEntry->Flink; pEntry->Flink->Blink = pEntry->Blink;
					memset(pEntry, 0, sizeof(LIST_ENTRY));
					pEntry = &pModule->HashTableEntry; pEntry->Blink->Flink = pEntry->Flink; pEntry->Flink->Blink = pEntry->Blink;
					memset(pEntry, 0, sizeof(LIST_ENTRY));
					memset(pModule->FullDllName.Buffer, 0, pModule->FullDllName.Length);
					memset(pModule, 0, sizeof(LDR_MODULE));
					break;
				}
			}
		}
	}
	void HideModuleXta(HINSTANCE hModule)
	{
		DWORD dwPEB_LDR_DATA = 0;

		_asm
		{
			pushad;
			pushfd;
			mov eax, fs:[30h]
				mov eax, [eax + 0Ch]
				mov dwPEB_LDR_DATA, eax
				mov esi, [eax + 0Ch]
				mov edx, [eax + 10h]

				LoopInLoadOrderModuleList :
				lodsd
				mov esi, eax
				mov ecx, [eax + 18h]
				cmp ecx, hModule
				jne SkipA
				mov ebx, [eax]
				mov ecx, [eax + 4]
				mov[ecx], ebx
				mov[ebx + 4], ecx
				jmp InMemoryOrderModuleList
				SkipA :
			cmp edx, esi
				jne LoopInLoadOrderModuleList

				InMemoryOrderModuleList :
			mov eax, dwPEB_LDR_DATA
				mov esi, [eax + 14h]
				mov edx, [eax + 18h]

				LoopInMemoryOrderModuleList :
				lodsd
				mov esi, eax
				mov ecx, [eax + 10h]
				cmp ecx, hModule
				jne SkipB
				mov ebx, [eax]
				mov ecx, [eax + 4]
				mov[ecx], ebx
				mov[ebx + 4], ecx
				jmp InInitializationOrderModuleList
				SkipB :
			cmp edx, esi
				jne LoopInMemoryOrderModuleList

				InInitializationOrderModuleList :
			mov eax, dwPEB_LDR_DATA
				mov esi, [eax + 1Ch]
				mov edx, [eax + 20h]

				LoopInInitializationOrderModuleList :
				lodsd
				mov esi, eax
				mov ecx, [eax + 08h]
				cmp ecx, hModule
				jne SkipC
				mov ebx, [eax]
				mov ecx, [eax + 4]
				mov[ecx], ebx
				mov[ebx + 4], ecx
				jmp Finished
				SkipC :
			cmp edx, esi
				jne LoopInInitializationOrderModuleList

				Finished :
			popfd;
			popad;
		}
	}
	bool DestroyModuleHeader(HMODULE hModule)
	{
		DWORD dwStartOffset = (DWORD)hModule;

		IMAGE_DOS_HEADER *pDosHeader = (PIMAGE_DOS_HEADER)dwStartOffset;
		if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
			return false;

		IMAGE_NT_HEADERS *pNtHeader = (PIMAGE_NT_HEADERS)(dwStartOffset + pDosHeader->e_lfanew);
		if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
			return false;

		DWORD dwOldProtection = NULL;
		if (!NativeNtProtectVirtualMemory((PVOID)hModule, pNtHeader->OptionalHeader.SizeOfHeaders, PAGE_EXECUTE_READWRITE, &dwOldProtection))
			return false;

		ZeroMemory((PVOID)hModule, pNtHeader->OptionalHeader.SizeOfHeaders);
		NativeNtProtectVirtualMemory((PVOID)hModule, pNtHeader->OptionalHeader.SizeOfHeaders, dwOldProtection, &dwOldProtection);

		return true;
	}


	void AntiDumping()
	{
		__asm
		{
			MOV EAX, FS:[0x30]
			MOV EAX, [EAX + 0x0C]
			MOV EAX, [EAX + 0x0C]
			MOV DWORD PTR[EAX + 0x20], 0x100000
		}
	}




	DWORD GetProcessIdByName(LPCTSTR name)
	{
		PROCESSENTRY32 pe32;
		HANDLE snapshot = NULL;
		DWORD pid = 0;

		snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshot != INVALID_HANDLE_VALUE) {
			pe32.dwSize = sizeof(PROCESSENTRY32);

			if (Process32First(snapshot, &pe32)) {
				do {
					std::string sName = pe32.szExeFile;
					std::transform(sName.begin(), sName.end(), sName.begin(), ::tolower);

					if (!lstrcmp(sName.c_str(), name)) {
						pid = pe32.th32ProcessID;
						break;
					}
				} while (Process32Next(snapshot, &pe32));
			}

			CloseHandle(snapshot);
		}

		return pid;
	}



	
	// Thread Hide
	inline bool ThreadHiding(HANDLE hThread)
	{
		typedef NTSTATUS(NTAPI *pNtSetInformationThread)
			(HANDLE, UINT, PVOID, ULONG);
		NTSTATUS Status;

		pNtSetInformationThread NtSIT = (pNtSetInformationThread)
			GetProcAddress(GetModuleHandle(XorStr("ntdll.dll")),
				XorStr("NtSetInformationThread"));

		if (NtSIT == NULL)
			return false;

		if (hThread == NULL)
			Status = NtSIT(GetCurrentThread(),
				0x11,
				0, 0);

		else

			Status = NtSIT(hThread, 0x11, 0, 0);

		if (Status != 0x00000000)
			return false;

		else

			return true;
	}


#define MARKER_NORM		0x90
#define JUNK_CODE_ONE   \
 __asm _emit 0xEB \
 __asm _emit POLY_JUMP_DIST \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM \
 __asm _emit MARKER_NORM


	inline void PushPopSS()
	{

		__asm
		{
			push ss
			pop ss
			mov eax, 9 
			xor edx, edx 
		}
	}

	//////MEMORY PROTECT

	




#pragma once

#include <windows.h>
	
	static BYTE MutByte[42] =
	{
		0xEB,0x28,0x90,0x90,0x90,0x90,0x90,0x90,0x90,
	  0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,
	  0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90, 
	  0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,
	  0x90,0x90,0x90,0x90,0x90,0x90 
	};


	class CMutant
	{
	public:
		CMutant(void);
		virtual ~CMutant(void);

		BOOL MutantFunc(DWORD addres);

	};


	bool mutCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
			if (*szMask == 'x' && *pData != *bMask)
				return false;
		return (*szMask) == NULL;
	}

	DWORD mutFindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask)
	{
		for (DWORD i = 0; i < dwLen; i++)
			if (mutCompare((BYTE*)(dwAddress + i), bMask, szMask))
				return (DWORD)(dwAddress + i);
		return false;
	}

	CMutant::CMutant(void)
	{
	}

	CMutant::~CMutant(void)
	{
	}



	BOOL CMutant::MutantFunc(DWORD addres)
	{
		DWORD dwFind1 = mutFindPattern((DWORD)addres, 0x2A,
			MutByte, "x?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

		if (dwFind1)
		{
			dwFind1 = dwFind1 + POLY_SIZE;

			DWORD dwFind2 = mutFindPattern((dwFind1), 0x2A,
				MutByte, "x?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

			if (dwFind2)
			{
				DWORD offset_data = (dwFind2 - dwFind1);

				if (offset_data >= 1)
				{
					DWORD OldProtection;
					NativeNtProtectVirtualMemory((void*)(dwFind1), offset_data, PAGE_EXECUTE_READWRITE, &OldProtection);

					BYTE bXor = (BYTE)offset_data;

					BYTE * data = (BYTE*)(dwFind1);
					for (DWORD i = 0; i < offset_data; i++) {
						data[i] = data[i] ^ bXor;
					}

					NativeNtProtectVirtualMemory((void*)(dwFind1), offset_data, OldProtection, &OldProtection);
				}

			}
		}


		return FALSE;

	}