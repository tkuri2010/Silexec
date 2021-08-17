#pragma once

// // SDKDDKVer.h をインクルードすると、利用できる最も高いレベルの Windows プラットフォームが定義されます。
// 以前の Windows プラットフォーム用にアプリケーションをビルドする場合は、WinSDKVer.h をインクルードし、
// サポートしたいプラットフォームに _WIN32_WINNT マクロを設定してから SDKDDKVer.h をインクルードします。
#include <winsdkver.h>
#define WINVER _WIN32_WINNT_WIN2K
#define _WIN32_WINNT _WIN32_WINNT_WIN2K
#include <SDKDDKVer.h>
