#include "framework.h"
#include "file_os_watcher.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/inotify.h>
#undef USE_MISC
#include <unistd.h>

#define BUFF_SIZE ((sizeof(struct inotify_event)+FILENAME_MAX)*1024)

namespace file
{


   os_watch::os_watch()
   {

   }


   os_watch::~os_watch()
   {

      os_watcher * pwatcher  =dynamic_cast < os_watcher * >(m_pwatcher);

      inotify_rm_watch(pwatcher->mFD, m_atom);

   }


   os_watcher::os_watcher()
   {

      mFD = inotify_init();

      if (mFD < 0)
      {

         fprintf (stderr, "Error: %s\n", strerror(errno));

      }

      mTimeOut.tv_sec = 1;

      mTimeOut.tv_usec = 0;

      FD_ZERO(&mDescriptorSet);

   }

   //--------
   os_watcher::~os_watcher()
   {

      //::parallelization::post_quit_and_wait(m_pthread, seconds(15));

      m_watchmap.erase_all();

   }


   watch_id os_watcher::add_watch(const ::file::path & pathFolder, listener * plistenerParam, bool bRecursive)
   {

      if (pathFolder.is_empty())
      {

         return -1;

      }

      ::pointer<listener>plistener(plistenerParam);

      synchronous_lock synchronouslock(this->synchronization());

      i32 wd = inotify_add_watch (mFD, pathFolder, IN_MODIFY | IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MOVED_FROM | IN_DELETE);

      if (wd < 0)
      {

         FORMATTED_TRACE("Error: os_watcher::add_watch at directory %s : (%s)", pathFolder.c_str(), strerror(errno));

         return -1;

      }

      auto pwatch = __create_new < os_watch >();

      pwatch->add_listener(plistener);

      pwatch->m_atom = wd;

      pwatch->m_pathFolder = pathFolder;

      pwatch->m_pwatcher = this;

      if(bRecursive)
      {

         pwatch->m_bRecursive = true;

         ::file::path_array stra;

         ::dir::rls_dir(stra, pathFolder);

         for(index index = 0; index < stra.get_count(); index++)
         {

            string strDirPath = stra[index];

            i32 inaw = inotify_add_watch (mFD, strDirPath, IN_MODIFY | IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MODIFY | IN_MOVED_FROM | IN_DELETE);

            if(inaw < 0)
            {

               if(errno == ENOENT)
               {

                  ::throw ::file::exception(ENOENT, strDirPath);

               }
               else
               {

                  ::throw ::file::exception(errno, strDirPath);

               }

            }
            else
            {

               auto pwatch  = __create_new < os_watch > ();

               pwatch->add_listener(plistener);

               pwatch->m_atom = inaw;

               pwatch->m_pathFolder = stra[index];

               pwatch->m_pwatcher = this;

               m_watchmap.set_at(inaw, pwatch);

            }

         }

      }
      else
      {

         pwatch->m_bRecursive = false;

      }

      m_watchmap.set_at(wd, pwatch);

      return wd;

   }


   //::e_status     os_watcher::run()
   //{

   //   while (::task_get_run())
   //   {

   //      if (!step())
   //      {

   //         break;

   //      }

   //   }

   //   return ::success;

   //}


   bool os_watcher::step()
   {

      FD_ZERO(&mDescriptorSet);

      FD_SET(mFD, &mDescriptorSet);

      timeval timeOut = mTimeOut;

      i32 ret = select(mFD + 1, &mDescriptorSet, nullptr, nullptr, &timeOut);

      if(ret < 0)
      {

         if(errno == EINTR)
         {

            sleep(200_ms);

         }
         else
         {

            perror("select");

         }

      }
      else if(FD_ISSET(mFD, &mDescriptorSet))
      {

         ssize_t len, i = 0;
         char action[81+FILENAME_MAX] = {0};
         char buff[BUFF_SIZE] = {0};

         len = ::read (mFD, buff, BUFF_SIZE);


         while (i < len)
         {
            struct inotify_event *pevent = (struct inotify_event *)&buff[i];


            auto pwatch = m_watchmap[(atom)ptopic->wd];

            ::file::action a;
            a.m_pwatch = pwatch;
            a.m_atom = pwatch->m_atom;
            a.m_pathFolder = pwatch->m_pathFolder;
            a.m_pathFile = ptopic->name;
            a.m_eaction = action_none;

            if((IN_CLOSE_WRITE & ptopic->mask) || (IN_MODIFY & ptopic->mask))
            {

               a.m_eaction |= action_modify;

            }

            if(IN_MOVED_TO & ptopic->mask || IN_CREATE & ptopic->mask)
            {

               a.m_eaction |= action_add;

            }

            if(IN_MOVED_FROM & ptopic->mask || IN_DELETE & ptopic->mask)
            {

               a.m_eaction |= action_delete;

            }

            if((IN_CLOSE_WRITE | IN_MODIFY)& ptopic->mask  || IN_MODIFY & ptopic->mask )
            {

               a.m_eaction |= action_modify;

            }

            pwatch->handle_action(&a);

            i += sizeof(struct inotify_event) + ptopic->len;

         }

      }


      return true;

   }



} // namespace file_watcher


