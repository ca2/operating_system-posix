//
// Created by camilo on 15/02/2021.
//
#include "framework.h"
#include "notify_icon.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/system.h"
#include "acme/prototype/string/str.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "aura/windowing/icon.h"


namespace node_gtk3
{


   notify_icon::notify_icon()
   {

      m_bCreated = false;

   }


   notify_icon::~notify_icon()
   {

   }


   void notify_icon::initialize(::particle * pparticle)
   {

      ::user::notify_icon::initialize(pparticle);


      øconstruct(m_pindicator);


   }


   void notify_icon::create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon)
   {

      if (m_bCreated)
      {

         return;

      }

      information() << "node_gnome::notify_icon::create_notify_icon";

      m_strId = atom;

      id() = atom;

      m_piconCurrent = picon;

      m_puserinteractionNotify = puserinteractionNotify;

      string strAppId = m_piconCurrent->get_tray_icon_name();

      string strId(strAppId);

      string strMatterRoot = ::str::token(strId, "/");

      if (strMatterRoot.is_empty())
      {

         strMatterRoot = "app";

      }

      auto iSlash = strAppId.find('/');

      string strAppName = strAppId.substr(iSlash + 1);

      ::file::path pathFolder = directory_system()->roaming() / strMatterRoot / "matter/icon/128";

      ::file::path pathRoamingIcon = pathFolder / (strAppName + ".png");

      //get_app()->file()->copy(pathRoamingIcon, "matter://main/icon-128.png");

      get_app()->file()->copy(pathRoamingIcon, "matter://main/icon-128.png");

      //auto psystem = system();
//
  //    auto pnode = psystem->node();

      m_pindicator->create(m_strId, strAppName, pathFolder, this->menu(), this);

//      if (m_pindicator == nullptr)
//      {
//
//         return false;
//
//      }

      m_bCreated = true;

      //return true;

   }


   void notify_icon::modify_icon(::windowing::icon * picon)
   {

      if (!m_bCreated)
      {

         throw ::exception(error_wrong_state);

      }

      throw ::exception(todo);

   }


   void notify_icon::add_hidden_window(::user::interaction * puserinteraction)
   {

      //auto estatus =
      //
      ::user::notify_icon::add_hidden_window(puserinteraction);

//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   void notify_icon::destroy_notify_icon()
   {

      m_pindicator->close();

      //return ::success;

   }


   bool notify_icon::notify_icon_step()
   {

      //return ::success;

      return true;

   }


} // namespace node_gtk3



