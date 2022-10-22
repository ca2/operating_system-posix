#pragma once


#include "apex/filesystem/file/watch.h"


namespace inotify
{


   class watcher;


   class watch :
      virtual public ::file::watch
   {
   public:

      i32                        m_iFd;
      struct timeval             m_timevalTimeOut;
      fd_set                     m_fdset;
      int                        m_watchdescriptor;
      //bool                 m_bOwn;


      watch();
      ~watch() override;

      bool open(const ::file::path & pathFolder, bool bRecursive) override;


      bool step() override;


   };


} // namespace inotify



