//
// Created by camilo on 15/02/2021.
//
#include "framework.h"
#include "aura/user/_user.h"
#include "acme/filesystem/filesystem/acme_dir.h"


namespace node_gnome
{


   notify_icon::notify_icon()
   {

      m_bCreated = false;

   }


   notify_icon::~notify_icon()
   {

   }


   ::e_status notify_icon::create_notify_icon(const ::id & id, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon)
   {

      if (m_bCreated)
      {

         return false;

      }

      m_strId.format("notify_icon_%s", id.to_string().c_str());

      m_strId = "ca2-" + picon->get_tray_icon_name() + "-" + m_strId;

      m_id = id;

      m_piconCurrent = picon;

      m_puserinteractionNotify = puserinteractionNotify;

      string strAppId = m_piconCurrent->get_tray_icon_name();

      string strId(strAppId);

      string strMatterRoot = ::str::token(strId, "/");

      if (strMatterRoot.is_empty())
      {

         strMatterRoot = "app";

      }

      ::file::path pathFolder = m_psystem->m_pacmedir->ca2roaming() / "matter/icon/128";

      string strIconName = get_application()->m_strAppId;

      strIconName.replace("/", "_");
      strIconName.replace("-", "_");

      auto psystem = m_psystem;

      auto pnode = psystem->node();

      auto estatus = __construct(m_pindicator);

      m_pindicator->create(m_strId, strIconName, pathFolder, this);

      if (m_pindicator == nullptr)
      {

         return false;

      }

      m_bCreated = true;

      return true;

   }


   ::e_status notify_icon::modify_icon(::windowing::icon * picon)
   {

      if (!m_bCreated)
      {

         return false;

      }

      __throw(todo);

      return error_not_implemented;

   }


   ::e_status notify_icon::add_hidden_window(::user::interaction * puserinteraction)
   {

      auto estatus = ::user::notify_icon::add_hidden_window(puserinteraction);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status notify_icon::destroy_notify_icon()
   {

      m_pindicator->close();

      return ::success;

   }


   ::e_status notify_icon::step()
   {

      return ::success;

   }


} // namespace node_gnome



