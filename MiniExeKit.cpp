//
// 小さな exe を作るために、__mainCRTStartup() を自前で実装
//

#include "framework.h"


// WinMain の lpCmdLine に該当する値を取得。プログラムに引数が与えられていなくても nullptr にはならないらしい。
static LPCWSTR GetArg()
{
	LPCWSTR line = GetCommandLineW();

	// まず自分自身のパスをスキップ。クオートされているかも知れない事に注意
	const WCHAR QUOTE = L'"';
	if (line[0] == QUOTE)
	{
		do { line++; } while (*line && *line != QUOTE);

		if (*line == QUOTE) line++;
	}
	else if (line[0])
	{
		// 多分、wchar_t だから安全に不等号で比較できるのであって、char版を使うなら注意しなきゃならんのじゃないかと。。。
		while (*line > L' ') line++;
	}
	else
	{
		// ここに来る事は、多分ありえない。。。？
		line = L"";
	}

	// 自分自身のパスをスキップした後、後続の空白があればスキップ
	while (*line && *line <= L' ') line++;

	return line;
}


// WinMain の nCmdShow に該当する値を取得
static int GetShowInfo()
{
	STARTUPINFOW startupInfo = { 0 };
	GetStartupInfoW(&startupInfo);

	return (startupInfo.dwFlags & STARTF_USESHOWWINDOW)
		? startupInfo.wShowWindow
		: SW_SHOWDEFAULT;
}


// だいたいこのあたりは http://hp.vector.co.jp/authors/VA016117/tinyexe.html が参考になった
void __cdecl wWinMainCRTStartup()
{
	auto rv = wWinMain(
		GetModuleHandle(nullptr)
		, nullptr
		, const_cast<LPWSTR>(GetArg())
		, GetShowInfo()
	);

	ExitProcess(rv);
}
