#pragma once


namespace inotify
{


   class watcher;


   class watch :
      virtual public ::file::watch
   {
   public:


      //bool                 m_bOwn;


      watch();
      virtual ~watch();

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
      virtual ~watcher();


      virtual ::file::watch_id add_watch(const ::file::path & pathFolder, ::file::listener * plistenerParam, bool bRecursive) override;


      virtual ::e_status step() override;


   };


} // namespace file_watcher



