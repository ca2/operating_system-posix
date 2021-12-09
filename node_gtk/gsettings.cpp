//
// Created by camilo on 09/12/2021. 13:03 BRT <ThomasBoregaardSorensen!!



namespace user
{


   bool g_bGInitialized = false;

   pthread_mutex_t g_mutexG;


   ::e_status gsettings_set(const ::string & strSchema, const ::string & strKey, const ::string & strValue)
   {

      if (strSchema.is_empty())
      {

         return error_invalid_argument;

      }

      if (strKey.is_empty())
      {

         return error_invalid_argument;

      }

      GSettings * settings = g_settings_new(strSchema);

      if (settings == nullptr)
      {

         return error_failed;

      }

      gboolean bOk = g_settings_set_string(settings, strKey, strValue);

      g_object_unref(settings);

      if(!bOk)
      {

         return error_failed;

      }

      return ::success;

   }


   bool gsettings_sync()
   {

      g_settings_sync();

      return true;

   }


} // namespace user



