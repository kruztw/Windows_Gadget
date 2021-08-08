#pragma once

class CShellExt : public IShellExtInit, IContextMenu
{
  wchar_t _file[PATHCCH_MAX_CCH]{};
  ULONG _refs{};

public:
  CShellExt();
  virtual ~CShellExt();

  // ========== IUnknown
  HRESULT STDMETHODCALLTYPE QueryInterface(
    REFIID riid,
    _COM_Outptr_ void** ppv
  ) override;
  ULONG STDMETHODCALLTYPE AddRef() override;
  ULONG STDMETHODCALLTYPE Release() override;

  // IShellExtInit
  HRESULT STDMETHODCALLTYPE Initialize(
    _In_opt_  PCIDLIST_ABSOLUTE folder,
    _In_opt_  IDataObject*      data,
    _In_opt_  HKEY              prog_id
  ) override;

  // IContextMenu
  HRESULT STDMETHODCALLTYPE QueryContextMenu(
    HMENU menu,
    UINT index_menu,
    UINT cmd_first,
    UINT cmd_last,
    UINT flags
  ) override;
  HRESULT STDMETHODCALLTYPE InvokeCommand(
    CMINVOKECOMMANDINFO* pici
  ) override;
  HRESULT STDMETHODCALLTYPE GetCommandString(
    UINT_PTR cmd,
    UINT type,
    UINT* /*reserved*/,
    CHAR* name,
    UINT name_size
  ) override;
};
