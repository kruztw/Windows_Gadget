#pragma once

// Beware: Most of these macros and include ordering are figured out via trying until it compiles.

#ifndef STRICT
#define STRICT
#endif

#define NOMINMAX

// thanks, microsoft
#define Unknown Unknown_FROM_WINDOWS

#include <winsdkver.h>

// Windows 7
#define _WIN32_WINNT 0x0601

#include <sdkddkver.h>

#define PHNT_VERSION PHNT_WIN7

#define ISOLATION_AWARE_ENABLED 1
#define SIDEBYSIDE_COMMONCONTROLS 1

#include <ntstatus.h>

#define WIN32_NO_STATUS

// ATL
#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

// PHNT
#include <Windows.h>
#include <windowsx.h>

// Windows
#include <WinUser.h>
#include <CommCtrl.h>
#include <VersionHelpers.h>
#include <PathCch.h>
#include <shlobj.h>
#include <shlwapi.h>

#undef Unknown

#include <atomic>
#include <xutility>
#include <optional>
#include <array>
