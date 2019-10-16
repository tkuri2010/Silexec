// Silexec.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "Silexec.h"


#define MAX_CMDLENGTH (32 * 1024)

/*
 * エントリポイントです。
 */
int APIENTRY wWinMain(
		_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPWSTR    lpCmdLine,
		_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	if (wcsnlen_s(lpCmdLine, MAX_CMDLENGTH) <= 0) {
		return -1;
	}

	STARTUPINFO startupInfo = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION processInfo;

	auto createProcRv = ::CreateProcessW(
		NULL,
		lpCmdLine,
		NULL, // process attr
		NULL, // threada attr
		FALSE, // inherit handles
		CREATE_NO_WINDOW, // creation fflags
		NULL, // environment
		NULL, // current directory
		&startupInfo, // startup info
		&processInfo // process info
	);

	if (createProcRv) {
		::WaitForSingleObject(processInfo.hProcess, INFINITE);
		::CloseHandle(processInfo.hProcess);
		::CloseHandle(processInfo.hThread);
	}

	return 0;
}

