// Created by camilo on 2024-06-02 16:56 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/linux/library.cpp by
// camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// From acme/nano/dynamic_library on 2024-06-02 18:06 by camilo <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "nano_dynamic_library_dl.h"
#include <dlfcn.h>
#include <link.h>

namespace dl
{


   namespace nano
   {

      namespace dynamic_library
      {


         dynamic_library::dynamic_library()
         {

         }


         dynamic_library::~dynamic_library()
         {


         }

         struct query_loaded_library
         {

            string m_strPathIn;
            string m_strPathOut;


         };


         int
         dynamic_library::__node_library_is_loaded_callback(struct dl_phdr_info *info, size_t size, void *data)
         {
            query_loaded_library *q = (query_loaded_library *) data;

            if (::file::path(info->dlpi_name).name() == q->m_strPathIn)
            {


               q->m_strPathOut = info->dlpi_name;

               return 1;

            }
            return 0;
         }


         string dynamic_library::is_loaded(const char *pszPath)
         {


            query_loaded_library q;

            q.m_strPathIn = pszPath;

            if (!q.m_strPathIn.case_insensitive_ends(".so"))
            {

               q.m_strPathIn += ".so";

            }

            if (!q.m_strPathIn.case_insensitive_begins("/") && !q.m_strPathIn.case_insensitive_begins("lib"))
            {

               q.m_strPathIn = "lib" + q.m_strPathIn;

            }

            dl_iterate_phdr(__node_library_is_loaded_callback, &q);

            return q.m_strPathOut;

         }


         library_t *dynamic_library::touch(const ::file::path &path, string &strMessage)
         {

            string strPath = __node_library_is_loaded(path);

            if (strPath.has_char())
            {

               return operating_system_library_open(path, strMessage);

            }

            return nullptr;

         }


         library_t *dynamic_library::open(const ::file::path &path, string &strMessage)
         {

            string strPath(path);

            string strOs("os");

            if (strPath == strOs)
            {

               strPath = "ca2os";

            } else if (strPath == "app_sphere")
            {

               strPath = "basesphere";

            }

            if (ansi_find_string(strPath, ".") == nullptr)
            {

               strPath += ".so";

            }

            if (strstr((const char *) strPath, "/") == nullptr && !ansi_begins(strPath, "lib"))
            {

               strPath = "lib" + strPath;

            }

            auto plibrary = (library_t*) dlopen(strPath, RTLD_GLOBAL | RTLD_LAZY | RTLD_NODELETE);
            //void * plibrary = dlopen(strPath, RTLD_GLOBAL | RTLD_NODELETE);

            if (plibrary == nullptr)
            {

               // pubs.opengroup.org contribution

               int iError = errno;

               const char *psz = strerror(iError);

               if (psz != nullptr)
               {

                  strMessage += psz;

               }

               char *errstr;

               errstr = dlerror();

               if (errstr != nullptr)
               {

                  strMessage += errstr;

               }

            } else
            {

               strMessage += "Successfully loaded library ";

               strMessage += path;

            }

            return plibrary;

         }


         library_t *dynamic_library::open_on_context(const ::file::path &path, string &strMessage)
         {

            string strPath(path);

            if (!strPath.case_insensitive_ends(".so"))
            {

               strPath += ".so";

            }

            if (!strPath.case_insensitive_begins("lib"))
            {

               strPath = "lib" + strPath;

            }

            auto plibrary = (library_t*)dlopen(strPath, RTLD_GLOBAL | RTLD_LAZY | RTLD_NODELETE);

            if (plibrary != nullptr)
            {

               return plibrary;

            }

            int iError = errno;

            const char *psz = strerror(iError);

            if (psz != nullptr)
            {

               strMessage += psz;

            }

            const char *psz2 = dlerror();

            if (psz2 != nullptr)
            {

               strMessage += psz2;

            }

            return plibrary;

         }


         bool dynamic_library::close(library_t *plibrary)
         {

            if (plibrary == nullptr)
               return false;

            return dlclose(plibrary) == 0;

         }


         void *dynamic_library::raw_get(library_t *plibrary, const ::scoped_string &scopedstrEntryName)
         {

            return dlsym(plibrary, scopedstrEntryName.c_str());

         }


      } // namespace dynamic_library


   } // namespace nano


} // namespace dl



