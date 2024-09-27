#pragma once


#include "apex/_.h"
//#define ISOLATION_AWARE_ENABLED 1
//#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
//#include "acme/_operating_system.h"
//#include <commctrl.h>

//#include "acme/prototype/prototype/memory.h"
//#include <Shlobj.h>
//#include <shellapi.h>
//#include <fcntl.h>
//#include <VersionHelpers.h>
//#include <ddeml.h>
//#include <share.h>
//#include <io.h>
//#include <Winsvc.h>
//

#if defined(_innate_ui_gtk3_project)
#define CLASS_DECL_INNATE_UI_GTK3  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_INNATE_UI_GTK3  CLASS_DECL_IMPORT
#endif
#define G_HANDLER(handler) G_CALLBACK(reinterpret_cast<void(*)(void)>(static_cast<void(*)(GtkWidget*, gpointer)>(handler)))
//
//CLASS_DECL_ACME void TRACELASTERROR();
//
//
//CLASS_DECL_ACME_WINDOWS void windows_registry_initialize();
//
//
//CLASS_DECL_ACME_WINDOWS string read_resource_as_string(hinstance hinst, ::u32 nID, const char * pcszType, strsize iReadAtMostByteCount = -1);
//CLASS_DECL_ACME_WINDOWS const void * get_resource_pointer(HINSTANCE hinst, DWORD nID, const char * pcszType, memsize & memsize);
//CLASS_DECL_ACME_WINDOWS bool read_resource_as_memory(memory & m, HINSTANCE hinst, DWORD nID, const char * pcszType, strsize iReadAtMostByteCount = -1);

//
//
//namespace acme_windows
//{
//
//
//   CLASS_DECL_ACME_WINDOWS string langid_to_iso(LANGID langid);
//
//
//} // namespace acme_windows
//
//
//
//
//
//
//CLASS_DECL_ACME_WINDOWS HANDLE hfile_create(
//   const char * pFileName,
//   ::u32                   dwDesiredAccess,
//   ::u32                   dwShareMode,
//   void * pSecurityAttributes,
//   ::u32                   dwCreationDisposition,
//   ::u32                   dwFlagsAndAttributes,
//   HANDLE                  hTemplateFile
//);
//
//
//
//
//// namespace str
//// {
//
////    string CLASS_DECL_ACME get_window_text_timeout(oswindow oswindow, class ::time tickTimeout = 1000);
//
//// } // namespace str
//
//
//
//
////#include "acme_windows_common/comptr.h"
//bool windows_find_is_dots(WIN32_FIND_DATAW & data);
//
//
//CLASS_DECL_ACME inline i32 muldiv32(i32 a, i32 b, i32 ca)
//{
//
//   return (i32) ::MulDiv((i32)a, (i32)b, (i32)ca);
//
//}
//
//CLASS_DECL_ACME int_bool HFILE_set_size(HANDLE h, u64 iSize);
//
//#ifdef WINDOWS
//CLASS_DECL_ACME int_bool read_resource_as_file(const scoped_string & strFile, HINSTANCE hinst, ::u32 nID, LPCTSTR pcszType);
//
//#endif
//
//
//CLASS_DECL_ACME TCHAR *** process_get_pargv();
//CLASS_DECL_ACME TCHAR ** process_get_argv();
//
//
//inline ansi_string & assign(ansi_string & ansistrDst, const cotaskptr < PWSTR > & pwidesz);
//
//inline wide_string & assign(wide_string & widestrDst, const cotaskptr < PSTR > & pansisz);
//
//inline ansi_string & assign(ansi_string & ansistrDst, const cotaskptr < PWSTR > & pwidesz);
//
//inline wide_string & assign(wide_string & widestrDst, const cotaskptr < PSTR > & pansisz);
//
//
//CLASS_DECL_ACME string get_command_line(HANDLE handleProcess);
//
//
//
//#ifdef WINDOWS
//
//
//CLASS_DECL_ACME FILETIME __FILETIME(const ::earth::time & time);
//
//
//#endif
//
//
//
//void copy(payload & payload, const FILETIME & time);
//void copy(payload & payload, const SYSTEMTIME & time);
//
//
//
//
//inline comptr < IStream > create_istream(const memory_base & memory)
//{
//
//   return ::SHCreateMemStream(memory.get_data(), (::u32)memory.get_size());
//
//}
//
//
//CLASS_DECL_ACME bool is_valid_FILETIME(const FILETIME & ft) noexcept;
//
//
//CLASS_DECL_ACME int_bool read_resource_as_file(const scoped_string & strFile, HINSTANCE hinst, ::u32 nID, LPCTSTR pcszType);
//
//
//namespace acme_windows
//{
//
//
//   CLASS_DECL_ACME_WINDOWS string langid_to_iso(LANGID langid);
//
//
//} // namespace acme_windows
//
//
//
//#include "simple_hold_handle.h"



namespace acme_windows
{


   class dir_context;
   class dir_system;

   class file_context;
   class file_system;


} // namespace apex_windows

