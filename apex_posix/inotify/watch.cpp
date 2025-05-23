#include "framework.h"
#include "watch.h"
#include "watcher.h"
#include "acme/filesystem/watcher/action.h"
#include "acme/operating_system/shared_posix/c_error_number.h"
#include "acme/parallelization/synchronous_lock.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/inotify.h>

#undef USE_MISC

#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define BUFF_SIZE ((sizeof(struct inotify_event)+FILENAME_MAX)*1024)

namespace inotify
{


   watch::watch()
   {

      m_timevalTimeOut.tv_sec = 1;

      m_timevalTimeOut.tv_usec = 0;

      FD_ZERO(&m_fdset);

   }


   watch::~watch()
   {

      inotify_rm_watch(m_iFd, m_watchdescriptor);

   }


   void watch::on_initialize_particle()
   {

      m_iFd = inotify_init();

      if (m_iFd < 0)
      {

         errorf("Error: %s", c_error_number().get_error_description().c_str());

      }

   }


   bool watch::open(const ::file::path & pathFolder, bool bRecursive)
   {


      if (pathFolder.is_empty())
      {

         return -1;

      }


      synchronous_lock synchronouslock(this->synchronization());

      int wd = inotify_add_watch(m_iFd, pathFolder,
                                 IN_MODIFY | IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MOVED_FROM | IN_DELETE);

      if (wd < 0)
      {

         auto cerrornumber = c_error_number();

         auto strErrorDescription = cerrornumber.get_error_description();

         informationf("Error: os_watcher::add_watch at directory %s : (%s)", pathFolder.c_str(), strErrorDescription.c_str());

         return false;

      }

//      auto watchid = ::file::watcher::add_watch(pathFolder, plistenerParam, bRecursive);
//
//      auto pwatch = __create_new < watch >();
//
//      pwatch->add_listener(plistener);

      id() = wd;

      m_pathFolder = pathFolder;

      //>m_pwatcher = this;

//      if(bRecursive)
//      {
//
//         pwatch->m_bRecursive = true;
//
//         ::file::listing listing;
//
//         listing.set_folder_listing(pathFolder, ::e_depth_recursively);
//
//         directory_system()->enumerate(listing);
//
//         for(::collection::index index = 0; index < listing.get_count(); index++)
//         {
//
//            string strDirPath = listing[index];
//
//            int inaw = inotify_add_watch (m_iFd, strDirPath, IN_MODIFY | IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MODIFY | IN_MOVED_FROM | IN_DELETE);
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
//               pwatch->id() = inaw;
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
      {

         m_bRecursive = false;

      }

      //m_watchmap.set_at(wd, pwatch);

      return true;

   }


   bool watch::file_watch_step()
   {

      FD_ZERO(&m_fdset);

      FD_SET(m_iFd, &m_fdset);

      auto timeOut = m_timevalTimeOut;

      int ret = select(m_iFd + 1, &m_fdset, nullptr, nullptr, &timeOut);

      if (ret < 0)
      {

         auto cerrornumber = c_error_number();

         if (cerrornumber == EINTR)
         {

            sleep(200_ms);

         }
         else
         {

            fprintf(stderr, "inotify::watch::file_watch_step select");

         }

      }
      else if (FD_ISSET(m_iFd, &m_fdset))
      {

         ssize_t len, i = 0;
         char action[81 + FILENAME_MAX] = {0};
         char buff[BUFF_SIZE] = {0};

         len = ::read(m_iFd, buff, BUFF_SIZE);


         while (i < len)
         {
            struct inotify_event * pevent = (struct inotify_event *) &buff[i];


//auto pwatch = m_watchmap[(atom)pevent->wd];

            ::file::action a;
            a.m_pfilewatch = this;
            a.m_pathFolder = m_pathFolder;
            a.m_pathFile = pevent->name;
            a.m_eaction = ::file::e_action_none;

            if ((IN_CLOSE_WRITE & pevent->mask) || (IN_MODIFY & pevent->mask))
            {

               a.m_eaction |= ::file::e_action_modify;

            }

            if (IN_MOVED_TO & pevent->mask || IN_CREATE & pevent->mask)
            {

               a.m_eaction |= ::file::e_action_add;

            }

            if (IN_MOVED_FROM & pevent->mask || IN_DELETE & pevent->mask)
            {

               a.m_eaction |= ::file::e_action_delete;

            }

            if ((IN_CLOSE_WRITE | IN_MODIFY) & pevent->mask || IN_MODIFY & pevent->mask)
            {

               a.m_eaction |= ::file::e_action_modify;

            }

            handle_action(&a);

            i += sizeof(struct inotify_event) + pevent->len;

         }

      }

      return true;

   }


} // namespace inotify



