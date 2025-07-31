#include "framework.h"
#include "midi.h"
#include "out.h"
#include "app-veriwell/multimedia/music/midi/sequencer.h"
#include "app-veriwell/multimedia/music/midi/message_out.h"
#if !BROAD_PRECOMPILED_HEADER
//#include "acme/_defer.h"
#endif

namespace music
{


   namespace midi
   {


      namespace alsa
      {


         midi::midi()
         {

            m_strName = "alsa";

         }


         midi::~midi()
         {

         }


         //         ::e_status midi::enumerate_midi_devices()
         //         {
         //
         //            return ::success;
         //
         //   /*         unsigned int devs = midiInGetNumDevs();
         //
         //            LOG("midiIn devices: %u", devs);
         //
         //            for (unsigned int dev = 0; dev < devs; dev++)
         //            {
         //
         //               MIDIINCAPSW caps = {};
         //
         //               MMRESULT mmr = midiInGetDevCapsW(dev, &caps, sizeof(caps));
         //
         //               if (MMSYSERR_NOERROR != mmr)
         //               {
         //
         //                  return translate_os_result(mmr, "enumerate_midi_devices", "midiInGetDevCapsW");
         //
         //               }
         //
         //               m_uiaIn.add(dev);
         //
         //               mmsystem_LogMidiInCaps(dev, caps);
         //
         //               mmsystem_GetMidiInDeviceInterface(dev);
         //
         //            }
         //
         //            devs = midiOutGetNumDevs();
         //
         //            LOG("midiOut devices: %u", devs);
         //
         //            for (unsigned int dev = 0; dev < devs; dev++)
         //            {
         //
         //               MIDIOUTCAPSW caps = {};
         //
         //               MMRESULT mmr = midiOutGetDevCapsW(dev, &caps, sizeof(caps));
         //
         //               if (MMSYSERR_NOERROR != mmr)
         //               {
         //
         //                  return translate_os_result(mmr, "enumerate_midi_devices", "midiOutGetDevCaps");
         //
         //               }
         //
         //               mmsystem_LogMidiOutCaps(dev, caps);
         //
         //               mmsystem_GetMidiOutDeviceInterface(dev);
         //
         //            }
         //
         //            return ::success;*/
         //
         //         }




         //      void midi::mmsystem_GetMidiInDeviceInterface(unsigned int i)
         //    {

         // query the size of the device interface string
         /*         HMIDIIN h = reinterpret_cast<HMIDIIN>(i);
                  ULONG size = 0;
                  MMRESULT mmr = midiInMessage(
                     h,
                     DRV_QUERYDEVICEINTERFACESIZE,
                     reinterpret_cast<DWORD_PTR>(&size),
                     0
                     );
                  if (MMSYSERR_NOERROR != mmr) {
                     LOG("midiInMessage(DRV_QUERYDEVICEINTERFACESIZE) failed: mmr = 0x%08x", mmr);
                     return;
                  }

                  if (0 == size) {
                     LOG("No device interface");
                     return;
                  }
                  if (size % sizeof(WCHAR)) {
                     LOG("Device interface length in bytes (%u) should be a multiple of the size of a WCHAR!", size);
                     return;
                  }

                  wstring wstr;
                  wstr.alloc(size);




                  mmr = midiInMessage(
                     h,
                     DRV_QUERYDEVICEINTERFACE,
                     reinterpret_cast<DWORD_PTR>((wchar_t *) wstr),
                     size
                     );
                  if (MMSYSERR_NOERROR != mmr) {
                     LOG("midiInMessage(DRV_QUERYDEVICEINTERFACE) failed: mmr = 0x%08x", mmr);
                     return;
                  }

                  LOG("    Device interface: \"%S\"", wstr);*/
         //  }

         //void midi::mmsystem_GetMidiOutDeviceInterface(unsigned int i)
         //{

         // query the size of the device interface string
         /*         HMIDIOUT h = reinterpret_cast<HMIDIOUT>(i);
                  ULONG size = 0;
                  MMRESULT mmr = midiOutMessage(
                     h,
                     DRV_QUERYDEVICEINTERFACESIZE,
                     reinterpret_cast<DWORD_PTR>(&size),
                     0
                     );
                  if (MMSYSERR_NOERROR != mmr) {
                     LOG("midiOutMessage(DRV_QUERYDEVICEINTERFACESIZE) failed: mmr = 0x%08x", mmr);
                     return;
                  }

                  if (0 == size) {
                     LOG("No device interface");
                     return;
                  }
                  if (size % sizeof(WCHAR)) {
                     LOG("Device interface length in bytes (%u) should be a multiple of the size of a WCHAR!", size);
                     return;
                  }

                  wstring wstr;
                  wstr.alloc(size);

                  mmr = midiOutMessage(
                     h,
                     DRV_QUERYDEVICEINTERFACE,
                     reinterpret_cast<DWORD_PTR>((wchar_t *) wstr),
                     size
                     );
                  if (MMSYSERR_NOERROR != mmr) {
                     LOG("midiOutMessage(DRV_QUERYDEVICEINTERFACE) failed: mmr = 0x%08x", mmr);
                     return;
                  }

                  LOG("    Device interface: \"%S\"", wstr);*/
         //}

         //void midi::mmsystem_LogMidiInCaps(unsigned int i, MIDIINCAPSW caps)
         //{
         /*         LOG(
                     "-- %u: %S --\n"
                     "    Device ID: %u\n"
                     "    Manufacturer identifier: %u\n"
                     "    Product identifier: %u\n"
                     "    Driver version: %u.%u\n"
                     "    Product name: %S\n"
                     "    Support: 0x%x"
                     ,
                     i,
                     caps.szPname ? caps.szPname : L"(no name)",
                     i,
                     caps.wMid,
                     caps.wPid,
                     caps.vDriverVersion / 256, caps.vDriverVersion % 256,
                     caps.szPname ? caps.szPname : L"(no name)",
                     caps.dwSupport
                     );
                  string strName;
                  if (caps.szPname != NULL)
                  {
                     strName.formatf("%s (%d)", caps.szPname, i);
                  }
                  else
                  {
                     strName.formatf("(no name midi In device) (%d)", i);
                  }
                  m_straIn.add(strName);*/
         //}

         //void midi::mmsystem_LogMidiOutCaps(unsigned int i, MIDIOUTCAPSW caps)
         //{
         /*         LOG(
                     "-- %u: %S --\n"
                     "    Device ID: %u\n"
                     "    Manufacturer identifier: %u\n"
                     "    Product identifier: %u\n"
                     "    Driver version: %u.%u\n"
                     "    Product name: %S\n"
                     "    Technology: %u (%S)\n"
                     "    Voices: %u\n"
                     "    Notes: %u\n"
                     "    Channel mask: 0x%x\n"
                     "    Support: 0x%x"
                     "%S%S%S%S"
                     ,
                     i,
                     caps.szPname ? caps.szPname : L"(no name)",
                     i,
                     caps.wMid,
                     caps.wPid,
                     caps.vDriverVersion / 256, caps.vDriverVersion % 256,
                     caps.szPname ? caps.szPname : L"(no name)",
                     caps.wTechnology,
                     caps.wTechnology == MOD_MIDIPORT ? L"MOD_MIDIPORT" :
                     caps.wTechnology == MOD_SYNTH ? L"MOD_SYNTH" :
                     caps.wTechnology == MOD_SQSYNTH ? L"MOD_SQSYNTH" :
                     caps.wTechnology == MOD_FMSYNTH ? L"MOD_FMSYNTH" :
                     caps.wTechnology == MOD_MAPPER ? L"MOD_MAPPER" :
                     caps.wTechnology == MOD_WAVETABLE ? L"MOD_WAVETABLE" :
                     caps.wTechnology == MOD_SWSYNTH ? L"MOD_SWSYNTH" :
                     L"Unrecognized",
                     caps.wVoices,
                     caps.wNotes,
                     caps.wChannelMask,
                     caps.dwSupport,
                     (caps.dwSupport & MIDICAPS_CACHE) ? L"\n        MIDICAPS_CACHE" : L"",
                     (caps.dwSupport & MIDICAPS_LRVOLUME) ? L"\n        MIDICAPS_LRVOLUME" : L"",
                     (caps.dwSupport & MIDICAPS_STREAM) ? L"\n        MIDICAPS_STREAM" : L"",
                     (caps.dwSupport & MIDICAPS_VOLUME) ? L"\n        MIDICAPS_VOLUME" : L""
                     );
                  string strName;
                  if (caps.szPname != NULL)
                  {
                     strName.formatf("%S (%d)", caps.szPname, i);
                  }
                  else
                  {
                     strName.formatf("(no name midi Out device) (%d)", i);
                  }
                  m_straOut.add(strName);*/
         //}


         ::pointer<::music::midi::message_out>midi::get_message_out(const ::scoped_string & scopedstrDevice)
         {


            string strEngine = device_engine(strDevice);

            if (strEngine.case_insensitive_order("rtmidi") == 0)
            {

               return m_pmidiRealTime->get_message_out(strDevice);

            }

            auto pout = __allocate class out();

            pout->initialize_message_out(this, strDevice);

            pout->open(false);

            return pout;

         }


         ::pointer<::music::midi::sequencer>midi::create_midi_sequencer(sequence * psequence, const ::scoped_string & scopedstrDevice)
         {


            if (strDevice.case_insensitive_order("alsa") == 0)
            {

               return __allocate ::music::midi::sequencer(psequence, get_message_out(strDevice));

            }

            auto psequencer = ::music::midi::midi::create_midi_sequencer(psequence, strDevice);

            if(psequencer)
            {

               return psequencer;

            }

            auto pmessageout = get_message_out(strDevice);

            return __allocate ::music::midi::sequencer(psequence, pmessageout);

         }


         ::e_status midi::translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pobject, int64_t iOsResult, const ::scoped_string & scopedstrContext, const ::scoped_string & scopedstrText)
         {

            ::e_status mmrc = iOsResult == 0 ? ::success : ::error_failed;

            if (mmrc == ::success)
            {

               return ::success;

            }

            return mmrc;

         }


         void midi::error_handler(const char *file, int line, const char *function, int err, const char *fmt, ...)
         {
            va_list arg;

            if (err == ENOENT)	/* Ignore those misleading "warnings" */
               return;
               va_start(arg, fmt);
               fprintf(stderr, "ALSA lib %s:%i:(%s) ", file, line, function);
               vfprintf(stderr, fmt, arg);
               if (err)
                  fprintf(stderr, ": %s", snd_strerror(err));
               putc('\n', stderr);
               va_end(arg);
         }

         /*
 * check permission (capability) of specified port
 */

#define LIST_INPUT	1
#define LIST_OUTPUT	2

#define perm_ok(pinfo,bits) ((snd_seq_port_info_get_capability(pinfo) & (bits)) == (bits))

         int midi::check_permission(snd_seq_port_info_t *pinfo, int perm)
         {
            if (perm) {
               if (perm & LIST_INPUT) {
                  if (perm_ok(pinfo, SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ))
                     goto __ok;
               }
               if (perm & LIST_OUTPUT) {
                  if (perm_ok(pinfo, SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE))
                     goto __ok;
               }
               return 0;
            }
            __ok:
            if (snd_seq_port_info_get_capability(pinfo) & SND_SEQ_PORT_CAP_NO_EXPORT)
               return 0;
            return 1;
         }



         /*
 * search all ports
 */

         void midi::do_search_port(snd_seq_t *seq, int perm, action_func_t do_action)
         {
            snd_seq_client_info_t *cinfo;
            snd_seq_port_info_t *pinfo;
            int count;

            snd_seq_client_info_alloca(&cinfo);
            snd_seq_port_info_alloca(&pinfo);
            snd_seq_client_info_set_client(cinfo, -1);
            while (snd_seq_query_next_client(seq, cinfo) >= 0) {
               /* reset query info */
               snd_seq_port_info_set_client(pinfo, snd_seq_client_info_get_client(cinfo));
               snd_seq_port_info_set_port(pinfo, -1);
               count = 0;
               while (snd_seq_query_next_port(seq, pinfo) >= 0) {
                  if (check_permission(pinfo, perm)) {
                     (this->*do_action)(seq, cinfo, pinfo, count);
                     count++;
                  }
               }
            }
         }
         void midi::enumerate_midi_out_devices()
         {

            ::music::midi::midi::enumerate_midi_out_devices();


            int c;
            snd_seq_t *seq;
            int queue = 0, convert_time = 0, convert_real = 0, exclusive = 0;
            //int command = SUBSCRIBE;
            int list_perm = 0;
            int client;
            int list_subs = 1;
            snd_seq_port_subscribe_t *subs;
            snd_seq_addr_t sender, dest;


            //            int card, err;
            //
            //            card = -1;
            //
            //            while(true)
            //            {
            //
            //               if ((err = snd_card_next(&card)) < 0)
            //               {
            //
            //                  informationf("cannot determine card number: %s", snd_strerror(err));
            //
            //                  break;
            //
            //               }
            //
            //               if(card < 0)
            //               {
            //
            //                  break;
            //
            //               }
            //
            //               list_midi_out_card_devices(card);
            //
            //            }

            if (snd_seq_open(&seq, "default", SND_SEQ_OPEN_DUPLEX, 0) < 0)
            {
               fprintf(stderr, "Can't open sequencer\n");
               //  return 1;
               return;
            }

            //snd_lib_error_set_handler(error_handler);
            //snd_seq_client_info_t *cinfo;
            //snd_seq_port_info_t *pinfo;
            //int count;
            //
            //snd_seq_client_info_alloca(&cinfo);
            //snd_seq_port_info_alloca(&pinfo);
            //snd_seq_client_info_set_client(cinfo, -1);
            //while (snd_seq_query_next_client(seq, cinfo) >= 0) {
            //   /* reset query info */
            //   snd_seq_port_info_set_client(pinfo, snd_seq_client_info_get_client(cinfo));
            //   snd_seq_port_info_set_port(pinfo, -1);
            //   count = 0;
            //   while (snd_seq_query_next_port(seq, pinfo) >= 0) {
            //      if (check_permission(pinfo, perm)) {
            //         do_action(seq, cinfo, pinfo, count);
            //         count++;
            //      }
            //   }
            //}
            list_perm |= LIST_OUTPUT;
            do_search_port(seq, list_perm,
                           list_subs ? &midi::print_port_and_subs : &midi::print_port);

            snd_seq_close(seq);
         }

         /*
          * list subscribers of specified type
          */
         void midi::list_each_subs(snd_seq_t *seq, snd_seq_query_subscribe_t *subs, snd_seq_query_subs_type_t type, const char *msg)
         {
            int count = 0;
            snd_seq_query_subscribe_set_type(subs, type);
            snd_seq_query_subscribe_set_index(subs, 0);
            while (snd_seq_query_port_subscribers(seq, subs) >= 0) {
               const snd_seq_addr_t *addr;
               if (count++ == 0)
                  printf("\t%s: ", msg);
               else
                  printf(", ");
               addr = snd_seq_query_subscribe_get_addr(subs);
               printf("%d:%d", addr->client, addr->port);
               if (snd_seq_query_subscribe_get_exclusive(subs))
                  printf("[ex]");
               if (snd_seq_query_subscribe_get_time_update(subs))
                  printf("[%s:%d]",
                         (snd_seq_query_subscribe_get_time_real(subs) ? "real" : "tick"),
                         snd_seq_query_subscribe_get_queue(subs));
               snd_seq_query_subscribe_set_index(subs, snd_seq_query_subscribe_get_index(subs) + 1);
            }
            if (count > 0)
               printf("\n");
         }

         /*
 * list subscribers
 */
         void midi::list_subscribers(snd_seq_t *seq, const snd_seq_addr_t *addr)
         {
            snd_seq_query_subscribe_t *subs;
            snd_seq_query_subscribe_alloca(&subs);
            snd_seq_query_subscribe_set_root(subs, addr);
            list_each_subs(seq, subs, SND_SEQ_QUERY_SUBS_READ, _("Connecting To"));
            list_each_subs(seq, subs, SND_SEQ_QUERY_SUBS_WRITE, _("Connected From"));
         }

         void midi::print_port_and_subs(snd_seq_t *seq, snd_seq_client_info_t *cinfo,

                                         snd_seq_port_info_t *pinfo, int count)
         {
            print_port(seq, cinfo, pinfo, count);
            list_subscribers(seq, snd_seq_port_info_get_addr(pinfo));

         }


         bool midi::Initialize()
         {

            if(!::music::midi::midi::Initialize())
            {

               return false;

            }

            return true;

         }


//         bool midi::list_midi_out_card_devices(int card)
//         {
//
//            snd_ctl_t *ctl;
//            char name[32];
//            int device;
//            int err;
//
//            sprintf(name, "hw:%d", card);
//
//            if ((err = snd_ctl_open(&ctl, name, 0)) < 0)
//            {
//
//               informationf("cannot open control for card %d: %s", card, snd_strerror(err));
//
//               return false;
//            }
//
//            snd_ctl_card_info_t *info;
//
//            snd_ctl_card_info_alloca(&info);
//
//            if ((err = snd_ctl_card_info(ctl, info)) < 0)
//            {
//
//               printf("HW info error: %s\n", snd_strerror(err));
//
//               return false;
//
//            }
//
//            printf("Soundcard #%i:\n", card);
//            printf("  card - %i\n", snd_ctl_card_info_get_card(info));
//            printf("  id - '%s'\n", snd_ctl_card_info_get_id(info));
//            printf("  driver - '%s'\n", snd_ctl_card_info_get_driver(info));
//            printf("  name - '%s'\n", snd_ctl_card_info_get_name(info));
//            printf("  longname - '%s'\n", snd_ctl_card_info_get_longname(info));
//            printf("  mixername - '%s'\n", snd_ctl_card_info_get_mixername(info));
//            printf("  components - '%s'\n", snd_ctl_card_info_get_components(info));
//
//            device = -1;
//
//            for (;;)
//            {
//
//               if ((err = snd_ctl_rawmidi_next_device(ctl, &device)) < 0)
//               {
//
//                  informationf("cannot determine device number: %s", snd_strerror(err));
//
//                  break;
//
//               }
//
//               if (device < 0)
//               {
//
//                  break;
//
//               }
//
//               list_midi_out_devices(ctl, card, device);
//
//            }
//
//            snd_ctl_close(ctl);
//
//            return true;
//
//         }


         void midi::print_port(snd_seq_t *seq, snd_seq_client_info_t *cinfo,
                                snd_seq_port_info_t *pinfo, int count)
         {

            int iClient = 0;
            //if (! count)
            {
               iClient =snd_seq_client_info_get_client(cinfo);
               printf(_("client %d: '%s' [type=%s]\n"),
                      iClient,
                      snd_seq_client_info_get_name(cinfo),
                      (snd_seq_client_info_get_type(cinfo) == SND_SEQ_USER_CLIENT ?
                      _("user") : _("kernel")));
            }

            int iPort =snd_seq_port_info_get_port(pinfo);
            printf("  %3d '%-16s'\n",
                   iPort,
                   snd_seq_port_info_get_name(pinfo));

            string strDev = snd_seq_port_info_get_name(pinfo);

            string strDevicePrefix;

            strDevicePrefix.formatf("alsa:%s,%d,%d", strDev.c_str(), iClient, iPort);

            string strName;

            strName.formatf("%s (%d:%d)", strDev.c_str(), iClient, iPort);

            add_midi_out_device(strName, strDevicePrefix);

         }


//                                void midi::print_port_and_subs(snd_seq_t *seq, snd_seq_client_info_t *cinfo,
//                                                                snd_seq_port_info_t *pinfo, int count)
//         {
//
//            print_port(seq, cinfo, pinfo, count);
//            list_subscribers(seq, snd_seq_port_info_get_addr(pinfo));
//         }


      //}


//         bool midi::list_midi_out_devices(snd_ctl_t *ctl, int card, int device)
//         {
//
//            snd_rawmidi_info_t *info = nullptr;
//            const char *name;
//            const char *sub_name;
//            int subs;
//            int sub;
//            int err;
//
//            snd_rawmidi_info_alloca(&info);
//
//            snd_rawmidi_info_set_device(info, device);
//
//            snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
//
//            err = snd_ctl_rawmidi_info(ctl, info);
//
//            if (err >= 0)
//            {
//
//               subs = snd_rawmidi_info_get_subdevices_count(info);
//
//            }
//            else
//            {
//
//               const char * pszError = snd_strerror(err);
//
//               informationf("cannot not get snd_ctl_rawmidi_info: %s", pszError);
//
//               subs = 0;
//
//            }
//
//            if (!subs)
//            {
//
//               return false;
//
//            }
//
//            for (sub = 0; sub < subs; ++sub)
//            {
//
//               snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
//
//               snd_rawmidi_info_set_subdevice(info, sub);
//
//               err = snd_ctl_rawmidi_info(ctl, info);
//
//               if (err < 0)
//               {
//
//                  informationf("cannot get rawmidi information %d:%d:%d: %s\n", card, device, sub, snd_strerror(err));
//
//                  return false;
//
//               }
//
//               name = snd_rawmidi_info_get_name(info);
//
//               sub_name = snd_rawmidi_info_get_subdevice_name(info);
//
//               if (sub == 0 && sub_name[0] == '\0')
//               {
//
//                  string strDev;
//
//                  strDev.formatf("hw:%d,%d", card, device);
//
//                  printf("hw:%d,%d    %s", card, device, name);
//
//                  add_midi_out_device(name, "alsa:" + strDev);
//
//                  break;
//
//               }
//               else
//               {
//
//                  string strDev;
//
//                  strDev.formatf("hw:%d,%d,%d", card, device, sub);
//
//                  printf("hw:%d,%d,%d  %s\n",  card, device, sub, sub_name);
//
//                  add_midi_out_device(sub_name, "alsa:" + strDev);
//
//
//
//               }
//
//            }
//
//            return true;
//
//         }


      } // namespace alsa


   } // namespace midi


} // namespace music



