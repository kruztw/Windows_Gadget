// 這個檔案主要就是定義 OLE class (請參考 OLE 資料夾的 DLL, 也許用 class 直接定義是比較新的做法ㄅ !?)
// CLSID_ShellExtension 跟 installer.iss 定義的一樣 (installer.iss 會將他註冊到 regedit)

#include "pch.h"
#include "dllmain.h"

#include "CShellExt.h"

// {19AEAA33-1BA9-4D92-BFE7-066322481069}
static const GUID CLSID_ShellExtension =
{ 0x19aeaa33, 0x1ba9, 0x4d92, { 0xbf, 0xe7, 0x6, 0x63, 0x22, 0x48, 0x10, 0x69 } };

std::atomic<UINT> g_refs;

EXTERN_C BOOL APIENTRY DllEntry(
  HMODULE /*module*/,
  DWORD /*reason_for_call*/,
  LPVOID /*reserved*/
)
{
  return TRUE;
}

class CShellExtClassFactory : public IClassFactory
{
protected:
  ULONG _refs{};

public:
  CShellExtClassFactory() { ++g_refs; }
  virtual ~CShellExtClassFactory() { --g_refs; }

  // ========== IUnknown
  HRESULT STDMETHODCALLTYPE QueryInterface(
    REFIID riid,
    _COM_Outptr_ void** ppv
  ) override
  {
    *ppv = nullptr;
    if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IClassFactory)) {
      *ppv = (IClassFactory*)this;
      AddRef();
      return NOERROR;
    }
    return E_NOINTERFACE;
  }

  ULONG STDMETHODCALLTYPE AddRef() override
  {
    return ++_refs;
  }

  ULONG STDMETHODCALLTYPE Release() override
  {
    if (--_refs)
      return _refs;
    delete this;
    return 0;
  }

  // ========== IClassFactory
  HRESULT STDMETHODCALLTYPE CreateInstance(
    _In_opt_ IUnknown* punk,
    _In_ REFIID riid,
    _COM_Outptr_ void** ppv
  ) override
  {
    *ppv = nullptr;
    if (punk)
      return CLASS_E_NOAGGREGATION;
    const auto shell_extension = new CShellExt();
    if (!shell_extension)
      return E_OUTOFMEMORY;
    return shell_extension->QueryInterface(riid, ppv);
  }

  HRESULT STDMETHODCALLTYPE LockServer(
    _In_ BOOL /*lock*/
  ) override
  {
    return NOERROR;
  }
};

_Use_decl_annotations_  STDAPI DllCanUnloadNow()
{
  return (g_refs == 0 ? S_OK : S_FALSE);
}

_Use_decl_annotations_ STDAPI DllGetClassObject(
  _In_      REFCLSID  rclsid,
  _In_      REFIID    riid,
  _Outptr_  LPVOID*   ppv
)
{
  *ppv = nullptr;
  if (IsEqualIID(rclsid, CLSID_ShellExtension))
  {
    const auto pcf = new CShellExtClassFactory;
    return pcf->QueryInterface(riid, ppv);
  }
  return CLASS_E_CLASSNOTAVAILABLE;
}