#pragma once


#include "apex/filesystem/filesystem/file_watcher.h"


namespace inotify
{


   class watcher;


   class watch :
      virtual public ::file::watch
   {
   public:


      //bool                 m_bOwn;


      watch();
      ~watch() override;

      //virtual bool open(const ::file::path & pathFolder, bool bRecursive);


   };


   class watcher :
      virtual public ::file::watcher
   {
   public:


      i32                        m_iFd;
      struct timeval             m_timevalTimeOut;
      fd_set                     m_fdset;


      watcher();
      ~watcher() override;


      virtual ::file::watch_id add_watch(const ::file::path & pathFolder, ::file::listener * plistenerParam, bool bRecursive) override;


      virtual bool step() override;


   };


} // namespace file_watcher



