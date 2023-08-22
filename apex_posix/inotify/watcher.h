#pragma once


#include "acme/filesystem/watcher/watcher.h"


namespace inotify
{


   class watch;


   class watcher :
      virtual public ::file::watcher
   {
   public:


      watcher();
      ~watcher() override;


      //virtual ::file::watch_id add_watch(const ::file::path & pathFolder, ::file::listener * plistenerParam, bool bRecursive) override;


      virtual bool step() override;


   };


} // namespace inotify



