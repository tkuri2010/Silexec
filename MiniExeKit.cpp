//
// ������ exe ����邽�߂ɁA__mainCRTStartup() �����O�Ŏ���
//

#include "framework.h"


// WinMain �� lpCmdLine �ɊY������l���擾�B�v���O�����Ɉ������^�����Ă��Ȃ��Ă� nullptr �ɂ͂Ȃ�Ȃ��炵���B
static LPCWSTR GetArg()
{
	LPCWSTR line = GetCommandLineW();

	// �܂��������g�̃p�X���X�L�b�v�B�N�I�[�g����Ă��邩���m��Ȃ����ɒ���
	const WCHAR QUOTE = L'"';
	if (line[0] == QUOTE)
	{
		do { line++; } while (*line && *line != QUOTE);

		if (*line == QUOTE) line++;
	}
	else if (line[0])
	{
		// �����Awchar_t ��������S�ɕs�����Ŕ�r�ł���̂ł����āAchar�ł��g���Ȃ璍�ӂ��Ȃ���Ȃ��̂���Ȃ����ƁB�B�B
		while (*line > L' ') line++;
	}
	else
	{
		// �����ɗ��鎖�́A�������肦�Ȃ��B�B�B�H
		line = L"";
	}

	// �������g�̃p�X���X�L�b�v������A�㑱�̋󔒂�����΃X�L�b�v
	while (*line && *line <= L' ') line++;

	return line;
}


// WinMain �� nCmdShow �ɊY������l���擾
static int GetShowInfo()
{
	STARTUPINFOW startupInfo = { 0 };
	GetStartupInfoW(&startupInfo);

	return (startupInfo.dwFlags & STARTF_USESHOWWINDOW)
		? startupInfo.wShowWindow
		: SW_SHOWDEFAULT;
}


// �����������̂������ http://hp.vector.co.jp/authors/VA016117/tinyexe.html ���Q�l�ɂȂ���
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
