// Changed by camilo on 2021-12-09 13:44 BRT <3ThomasBorregaardSorensen!!
#pragma once


namespace node_gtk
{


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);


   ::e_status gsettings_set(const ::string & strSchema, const ::string & strKey, const ::string & strValue);


} // namespace node_gtk



