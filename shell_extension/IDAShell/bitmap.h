#pragma once

using ARGB = ULONG;

HRESULT Create32BitHBITMAP(HDC hdc, const SIZE* psize, void** ppvBits, HBITMAP* phBmp);
HRESULT ConvertToPARGB32(HDC hdc, ARGB* pargb, HBITMAP hbmp, SIZE& sizImage, int cxRow);
HBITMAP IconToBitmapPARGB32(HICON hIcon, DWORD cx, DWORD cy);
