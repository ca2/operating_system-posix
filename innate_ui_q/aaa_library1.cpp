#include "framework.h"
#include "apex/operating_system.h"


void * __node_library_open(const scoped_string & strPath, string & strMessage)
{

   strMessage.empty();

   string strError;

   string strPath(pszPath);

   unsigned int uiError;

   void * plibrary = nullptr;

   if (ansi_ends_ci(strPath, ".ilk"))
   {

      return nullptr;

   }

   if(ansi_ends_ci(strPath,".pdb"))
   {

      return nullptr;

   }

   if(ansi_ends_ci(strPath,".lib"))
   {

      return nullptr;

   }

   if(ansi_ends_ci(strPath,".exp"))
   {

      return nullptr;

   }

   if (strPath.find('.') < 0 || !file_system()->exists(strPath))
   {

      strPath += ".dll";

   }

   ::file::path path;

   path = strPath;

   try
   {

      plibrary = ::LoadLibraryW(wstring(path));

   }
   catch(...)
   {

   }

   if (plibrary != nullptr)
   {

      informationf("Loaded Library (1) %s", strPath.c_str());

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (1) LoadLibraryW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = "\\\\?\\" + strPath;

   try
   {

      plibrary = ::LoadLibraryW(wstring(path));

   }
   catch (...)
   {

   }

   if (plibrary != nullptr)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (2) LoadLibraryW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = ::dir::ca2_module() / strPath;

   try
   {

      plibrary = ::LoadLibraryW(wstring(path));

   }
   catch (...)
   {

   }

   uiError = ::GetLastError();

   strError = "\n (3) LoadLibraryW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = "\\\\?\\" + string(::dir::ca2_module() / strPath);

   try
   {

      plibrary = ::LoadLibraryW(wstring(path));

   }
   catch (...)
   {

   }

   if (plibrary != nullptr)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (4) LoadLibraryW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = ::dir::base_module() / strPath;

   try
   {

      plibrary = ::LoadLibraryW(wstring(path));

   }
   catch (...)
   {

   }

   if (plibrary != nullptr)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (5) LoadLibraryW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = "\\\\?\\" + string(::dir::base_module() / strPath);

   try
   {

      plibrary = ::LoadLibraryW(wstring(path));

   }
   catch (...)
   {

   }

   if (plibrary != nullptr)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (6) LoadLibraryW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;


finished:

   if (plibrary != nullptr)
   {

      strMessage = "node_library_open Success opening " + path;

   }
   else
   {

      strMessage = "node_library_open Failed opening " + strPath + strMessage;

   }

   ::output_debug_string(strMessage + "\n\n");

   return plibrary;

}


void * __node_library_touch(const scoped_string & strPath, string & strMessage)
{

   strMessage.empty();

   string strError;

   string strPath(pszPath);

   unsigned int uiError;

   void * plibrary = nullptr;

   if (ansi_ends_ci(strPath, ".ilk"))
   {

      return nullptr;

   }

   if (ansi_ends_ci(strPath, ".pdb"))
   {

      return nullptr;

   }

   if (ansi_ends_ci(strPath, ".lib"))
   {

      return nullptr;

   }

   if (ansi_ends_ci(strPath, ".exp"))
   {

      return nullptr;

   }

   if (ansi_find_string(file_path_name(strPath), ".") == nullptr)
   {

      strPath += ".dll";

   }

   ::output_debug_string("\n\nGoing to touch library (1) " + string(strPath) + "\n");

   ::file::path path;

   path = strPath;

   try
   {

      plibrary = ::GetModuleHandleW(wstring(path));

   }
   catch (...)
   {

   }

   if (plibrary != nullptr)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (1) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = "\\\\?\\" + strPath;

   try
   {

      plibrary = ::GetModuleHandleW(wstring(path));

   }
   catch (...)
   {

   }

   if (plibrary != nullptr)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (2) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = ::dir::ca2_module() / strPath;

   try
   {

      plibrary = ::GetModuleHandleW(wstring(path));

   }
   catch (...)
   {

   }

   uiError = ::GetLastError();

   strError = "\n (3) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = "\\\\?\\" + string(::dir::ca2_module() / strPath);

   try
   {

      plibrary = ::GetModuleHandleW(wstring(path));

   }
   catch (...)
   {

   }

   if (plibrary != nullptr)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (4) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = ::dir::base_module() / strPath;

   try
   {

      plibrary = ::GetModuleHandleW(wstring(path));

   }
   catch (...)
   {

   }

   if (plibrary != nullptr)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (5) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = "\\\\?\\" + string(::dir::base_module() / strPath);

   try
   {

      plibrary = ::GetModuleHandleW(wstring(path));

   }
   catch (...)
   {

   }

   if (plibrary != nullptr)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (6) GetModuleHandleW " + path + " failed with (" + ::as_string(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;


finished:

   if (plibrary != nullptr)
   {

      strMessage = "node_library_touch Success touching " + path;

   }
   else
   {

      strMessage = "node_library_touch Failed touch " + strPath + strMessage;

   }

   ::output_debug_string(strMessage + "\n\n");

   return plibrary;

}


bool __node_library_close(void * plibrary)
{

   if(plibrary == nullptr)
      return false;

   bool bOk = false;
//#ifndef MEMDLEAK
   try
   {

      bOk = ::FreeLibrary((HINSTANCE)plibrary) != false;

   }
   catch(...)
   {

   }
//#endif
   return bOk;

}


void * __node_library_open_ca2(const scoped_string & str, string & strMessage)
{

   void * p = LoadLibraryW(wstring(psz));

   if (p != nullptr)
   {

      strMessage = "Loaded Library (2) " + string(psz);

   }
   else
   {

      unsigned int uiError = GetLastError();

      strMessage = "Failed to Load Library (2) " + string(psz) + " with error (" + ::as_string(uiError) +
                   ")" + get_error_string(uiError);

   }

   ::output_debug_string("\n" + strMessage + "\n\n");

   return p;

}

void * __node_library_raw_get(void * plibrary,const scoped_string & strEntryName)
{

   return ::GetProcAddress((HINSTANCE)plibrary,pszEntryName);

}


