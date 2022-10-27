#include "framework.h"
#include "watcher.h"
#include "apex/filesystem/file/watch.h"


#include <sys/stat.h>
#include <fcntl.h>
#include <sys/inotify.h>

#undef USE_MISC

#include <unistd.h>

#define BUFF_SIZE ((sizeof(struct inotify_event)+FILENAME_MAX)*1024)

namespace inotify
{


   watcher::watcher()
   {


   }

   //--------
   watcher::~watcher()
   {

      //::parallelization::post_quit_and_wait(m_pthread, seconds(15));

      //m_watchmap.erase_all();

   }

//
//   ::file::watch_id watcher::add_watch(const ::file::path & pathFolder, ::file::listener * plistenerParam, bool bRecursive)
//   {
//
//
//
//      if (pathFolder.is_empty())
//      {
//
//         return -1;
//
//      }
//
//
//      ::pointer<::file::listener>plistener(plistenerParam);
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      i32 wd = inotify_add_watch (m_iFd, pathFolder, IN_MODIFY | IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MOVED_FROM | IN_DELETE);
//
//      if (wd < 0)
//      {
//
//         FORMATTED_TRACE("Error: os_watcher::add_watch at directory %s : (%s)", pathFolder.c_str(), strerror(errno));
//
//         return -1;
//
//      }
//
//      auto watchid = ::file::watcher::add_watch(pathFolder, plistenerParam, bRecursive);
//
//      auto pwatch = __create_new < watch >();
//
//      pwatch->add_listener(plistener);
//
//      pwatch->m_atom = wd;
//
//      pwatch->m_pathFolder = pathFolder;
//
//      pwatch->m_pwatcher = this;
//
//      if(bRecursive)
//      {
//
//         pwatch->m_bRecursive = true;
//
//         ::file::listing listing;
//
//         listing.set_folder_listing(pathFolder, ::e_depth_recursively);
//
//         acmedirectory()->enumerate(listing);
//
//         for(index index = 0; index < listing.get_count(); index++)
//         {
//
//            string strDirPath = listing[index];
//
//            i32 inaw = inotify_add_watch (m_iFd, strDirPath, IN_MODIFY | IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MODIFY | IN_MOVED_FROM | IN_DELETE);
//
//            if(inaw < 0)
//            {
//
//               if(errno == ENOENT)
//               {
//
//                  throw ::file::exception(error_io, ENOENT, ENOENT, strDirPath);
//
//               }
//               else
//               {
//
//                  throw ::file::exception(error_io, errno, errno, strDirPath);
//
//               }
//
//            }
//            else
//            {
//
//               auto pwatch  = __create_new < watch > ();
//
//               pwatch->add_listener(plistener);
//
//               pwatch->m_atom = inaw;
//
//               pwatch->m_pathFolder = listing[index];
//
//               pwatch->m_pwatcher = this;
//
//               m_watchmap.set_at(inaw, pwatch);
//
//            }
//
//         }
//
//      }
//      else
//      {
//
//         pwatch->m_bRecursive = false;
//
//      }
//
//      m_watchmap.set_at(wd, pwatch);
//
//      return wd;
//
//   }


   bool watcher::step()
   {

      for (auto & pwatch: m_watchmap.values())
      {

         pwatch->step();

      }

      return true;

   }


} // namespace inotify



