#include "framework.h"
#include "out.h"
#include "acme/platform/application.h"
#include "app-veriwell/multimedia/music/midi/sequencer.h"
#include "app-veriwell/multimedia/music/midi/file.h"
#if !BROAD_PRECOMPILED_HEADER
//#include "acme/_defer.h"
#endif


namespace music
{


   namespace midi
   {


      namespace alsa
      {


         //         out::out()
         //         {
         //
         //            m_poseq = NULL;
         //
         //         }

         out::out()
         {

            m_subscribe = nullptr;
            //m_iWrite = 0;

            //m_prawmidi = NULL;
            m_pseq = NULL;
            // sudo modprobe snd-virmidi snd_index=1
            //            aconnect -i
            //             Or?
            //            aconnect -o
            // modprobe snd-virmidi

            //On my system this gives the following, so I want 72:0. The other ports would also work.
            //
            //client 0: 'System' [type=kernel]
            //    0 'Timer           '
            //    1 'Announce        '
            //client 62: 'Midi Through' [type=kernel]
            //    0 'Midi Through Port-0'
            //client 64: 'MPU-401 MIDI 0-0' [type=kernel]
            //    0 'MPU-401 MIDI 0-0'
            //client 72: 'Virtual Raw MIDI 1-0' [type=kernel]
            //    0 'VirMIDI 1-0     '
            //client 73: 'Virtual Raw MIDI 1-1' [type=kernel]
            //    0 'VirMIDI 1-1     '
            //client 74: 'Virtual Raw MIDI 1-2' [type=kernel]
            //    0 'VirMIDI 1-2     '
            //client 75: 'Virtual Raw MIDI 1-3' [type=kernel]
            //    0 'VirMIDI 1-3     '
            //Connect the Virtual Raw MIDI port to the Timidity port
            //
            //aconnect 72:0 128:0
            //
            //Find the device name of the Virtual Raw MIDI port. Since I went with the first Raw MIDI port, the device name I want is hw:1,0.
            //
            //amidi -l
            //
            //Device    Name
            //hw:0,0    MPU-401 MIDI 0-0
            //hw:1,0    Virtual Raw MIDI (16 subdevices)
            //hw:1,1    Virtual Raw MIDI (16 subdevices)
            //hw:1,2    Virtual Raw MIDI (16 subdevices)
            //hw:1,3    Virtual Raw MIDI (16 subdevices)

            //string strDriver(strDevice);

            //strDriver.case_insensitive_begins_eat("alsa:");

            //m_strDriver = strDriver;

            //            int err = snd_rawmidi_open(NULL, &m_prawmidi, strDriver, SND_RAWMIDI_SYNC);
            //
            //            if(err)
            //            {
            //
            //               fprintf(stderr,"snd_rawmidi_open %s failed: %d\n", strDriver.c_str(), err);
            //
            //            }
            //            else
            //            {
            //
            //               snd_rawmidi_params_t * params = NULL;
            //
            //               err = snd_rawmidi_params_malloc(&params);
            //
            //               err = snd_rawmidi_params_current(m_prawmidi,	params);
            //
            //               err = snd_rawmidi_params_set_avail_min(m_prawmidi, params, 768);
            //
            //               err = snd_rawmidi_params_set_buffer_size(m_prawmidi, params, 1024);
            //
            //               err = snd_rawmidi_params(m_prawmidi, params);
            //
            //               snd_rawmidi_params_free(params);
            //
            //            }

         }


         out::~out()
         {

            close();

         }


         void out::initialize_message_out(::music::midi::midi * pmidi, const ::scoped_string & scopedstrDevice)
         {

            //auto estatus =
            //
            ::music::midi::message_out::initialize_message_out(pmidi, scopedstrDevice);

//            if(!estatus)
//            {
//
//               return estatus;
//
//            }

            string_array_base stra;

            stra.explode(",", m_strDeviceId);

            if(stra.get_count() < 3)
            {

               throw ::exception(error_wrong_state);

            }

            m_addrDest.client = atoi(stra[1]);

            m_addrDest.port = atoi(stra[2]);

            //return estatus;

         }


         void out::open(bool bForSequencing)
         {

            if ( m_pseq != NULL )
            {

               //return ::success_none;

               return;

            }

            string clientName = application()->m_strAppId;

            int result = snd_seq_open(&m_pseq, "default", SND_SEQ_OPEN_DUPLEX, 0);

            if ( result < 0 )
            {

               m_pseq = NULL;

               throw ::exception(error_failed);

            }

            m_strClientName = clientName;

            snd_seq_set_client_name(m_pseq, m_strClientName.c_str());

            snd_seq_port_info_t *pinfo;
                int err;
                m_iPort = 0;

                 snd_seq_port_info_alloca(&pinfo);

                 /* the first created port is 0 anyway, but let's make sure ... */
                 snd_seq_port_info_set_port(pinfo, m_iPort);
                 snd_seq_port_info_set_port_specified(pinfo, 1);

                 snd_seq_port_info_set_name(pinfo, m_strClientName);

                 snd_seq_port_info_set_capability(pinfo, 0); /* sic */
                snd_seq_port_info_set_type(pinfo,
                            SND_SEQ_PORT_TYPE_MIDI_GENERIC |
               SND_SEQ_PORT_TYPE_APPLICATION);

                 err = snd_seq_create_port(m_pseq, pinfo);
            //1     check_snd("create port", err);
//             = snd_seq_create_simple_port(m_pseq, clientName,
//                                                 SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_WRITE,
//                                                 SND_SEQ_PORT_TYPE_APPLICATION);

            if(err < 0)
            {

               snd_seq_close(m_pseq);

               m_pseq = nullptr;

               throw ::exception(error_failed);

            }

            m_addrSender.client = snd_seq_client_id(m_pseq);

            m_addrSender.port   = m_iPort; // or 0 ?

            m_iQueue = snd_seq_alloc_named_queue(m_pseq, m_strClientName);

            snd_seq_connect_to(m_pseq, 0, m_addrDest.client, m_addrDest.port);

//            int convert_time = 0, convert_real = 0, exclusive = 0;
//
//            snd_seq_port_subscribe_alloca(&m_subscribe);
//            snd_seq_port_subscribe_set_sender(m_subscribe, &m_addrSender);
//            snd_seq_port_subscribe_set_dest(m_subscribe, &m_addrDest);
//            snd_seq_port_subscribe_set_queue(m_subscribe, m_iQueue);
//            snd_seq_port_subscribe_set_exclusive(m_subscribe, exclusive);
//            snd_seq_port_subscribe_set_time_update(m_subscribe, convert_time);
//            snd_seq_port_subscribe_set_time_real(m_subscribe, convert_real);
//
//            if (snd_seq_get_port_subscription(m_pseq, m_subscribe) == 0)
//            {
//
//               snd_seq_close(m_pseq);
//
//               m_subscribe = nullptr;
//
//               m_pseq = nullptr;
//
//               fprintf(stderr, _("Connection is already subscribed\n"));
//
//               return error_failed;
//
//            }
//
//            if (snd_seq_subscribe_port(m_pseq, m_subscribe) < 0)
//            {
//
//               snd_seq_close(m_pseq);
//
//               m_subscribe = nullptr;
//
//               m_pseq = nullptr;
//
//               fprintf(stderr, _("Connection failed (%s)\n"), snd_strerror(errno));
//
//               return error_failed;
//
//            }

            //return ::success;

         }


         void out::close()
         {

//            if (snd_seq_get_port_subscription(m_pseq, m_subscribe) < 0)
//            {
//
//               snd_seq_close(m_pseq);
//
//               m_subscribe = nullptr;
//
//               m_pseq = nullptr;
//
//               fprintf(stderr, _("No subscription is found\n"));
//
//               return error_failed;
//
//            }
//
//            if (snd_seq_unsubscribe_port(m_pseq, m_subscribe) < 0)
//            {
//
//               snd_seq_close(m_pseq);
//
//               m_subscribe = nullptr;
//
//               m_pseq = nullptr;
//
//               fprintf(stderr, _("Disconnection failed (%s)\n"), snd_strerror(errno));
//
//               return error_failed;
//
//            }

            snd_seq_close(m_pseq);

            m_pseq = nullptr;

            //return ::success;

         }


         void out::start()
         {

            snd_seq_queue_tempo_t *tempo;

            int err;

            snd_seq_queue_tempo_alloca(&tempo);

            auto dwTempoDivision = m_psequencer->m_psequence->m_pfile->m_dwTempoDivision;

            bool smpte_timing = (dwTempoDivision & 0x8000);

            int uSMPTE = 0;

            if(smpte_timing)
            {

               uSMPTE = -(int32_t)(char)((dwTempoDivision >> 8)&0xFF);

//               if (29 == uSMPTE)
//               {
//
//                  uSMPTE = 30;
//
//               }

            }

            if (!smpte_timing)
            {
               snd_seq_queue_tempo_set_tempo(tempo, m_psequencer->m_psequence->m_pfile->m_tempoa[0].speed); /* default: 120 bpm */
               snd_seq_queue_tempo_set_ppq(tempo, dwTempoDivision);
            }
            else
            {
               /*
            * ALSA doesn't know about the SMPTE time divisions, so
            * we pretend to have a musical tempo with the equivalent
            * number of ticks/s.
            */
               switch (uSMPTE)
               {
                  case 24:
                         snd_seq_queue_tempo_set_tempo(tempo, 500000);
                     snd_seq_queue_tempo_set_ppq(tempo, 12 * dwTempoDivision);
                     break;
                     case 25:
                              snd_seq_queue_tempo_set_tempo(tempo, 400000);
                        snd_seq_queue_tempo_set_ppq(tempo, 10 * dwTempoDivision);
                        break;
                        case 29:
                                   snd_seq_queue_tempo_set_tempo(tempo, 100000000);
                           snd_seq_queue_tempo_set_ppq(tempo, 2997 * dwTempoDivision);
                           break;
                           case 30:
                                        snd_seq_queue_tempo_set_tempo(tempo, 500000);
                              snd_seq_queue_tempo_set_ppq(tempo, 15 * dwTempoDivision);
                              break;
                              default:
                                 //informationf("Invalid SMPTE frames " + ::unicode_from((int)uSMPTE));
                                 informationf("Invalid SMPTE frames ");
                     throw ::exception(error_failed);

               }

            }

            err = snd_seq_set_queue_tempo(m_pseq, m_iQueue, tempo);

            if(err < 0)
            {

               throw ::exception(error_failed);

            }

            err = snd_seq_start_queue(m_pseq, m_iQueue, NULL);

            if(err < 0)
            {

               throw ::exception(error_failed);

            }

            //return ::success;

         }


         void out::stop()
         {


            int err;

            snd_seq_event_t happening={};

            snd_seq_ev_set_fixed(&happening);
            happening.type = SND_SEQ_EVENT_STOP;
            happening.time.tick = m_psequencer->m_psequence->m_pfile->m_tkLength;
            happening.dest.client = SND_SEQ_CLIENT_SYSTEM;
            happening.dest.port = SND_SEQ_PORT_SYSTEM_TIMER;
            happening.data.queue.queue = m_iQueue;

            err = snd_seq_event_output(m_pseq, &happening);

            err = snd_seq_drain_output(m_pseq);

               /*
      * There are three possibilities how to wait until all happenings have
      * been played:
      * 1) send an happening back to us (like pmidi does), and wait for it;
      * 2) wait for the EVENT_STOP notification for our queue which is sent
      *    by the system timer port (this would require a subscription);
      * 3) wait until the output pool is empty.
      * The last is the simplest.
      */

               err = snd_seq_sync_output_queue(m_pseq);

               //             if (end_delay > 0)
//                    sleep(end_delay);

            //return ::success;

         }

         bool out::use_tick() const
         {

            return true;

         }


         void out::send_short_message(::music::midi::enum_midi_message emessage, int iChannel, int iData1, int iData2)
         {

            //return midiOutShortMsg(m_hmidiout, MIDIMSG(((int) etype) >> 4, iChannel, iData1, iData2));

            //return ::success;

         }


         void out::note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity)
         {

            snd_seq_event_t  happening = {};

            happening.queue = m_iQueue;

            //snd_seq_ev_set_fixed(&happening);

            snd_seq_ev_set_source(&happening, m_iPort);

            snd_seq_ev_set_dest(&happening, m_addrDest.client, m_addrDest.port);

            if(use_tick())
            {

               happening.time.tick = m_tick;
               happening.flags = SND_SEQ_TIME_STAMP_TICK;

            }
            else
            {

               snd_seq_ev_set_direct(&happening);

            }

            snd_seq_ev_set_noteon(&happening, iChannel, uchNote, uchVelocity);

            snd_seq_event_output(m_pseq, &happening);

            //snd_seq_event_output_direct(m_pseq, &happening);

            //return ::success;

         }


         void out::note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity)
         {

            snd_seq_event_t  happening ={};

            happening.queue = m_iQueue;

            //snd_seq_ev_set_fixed(&happening);

            snd_seq_ev_set_source(&happening, m_iPort);

            snd_seq_ev_set_dest(&happening, m_addrDest.client, m_addrDest.port);

            if(use_tick())
            {

               happening.time.tick = m_tick;
               happening.flags = SND_SEQ_TIME_STAMP_TICK;

            }
            else
            {

               snd_seq_ev_set_direct(&happening);

            }

            snd_seq_ev_set_noteoff(&happening, iChannel, uchNote, uchVelocity);

            //snd_seq_event_output_direct(m_pseq, &happening);

            snd_seq_event_output(m_pseq, &happening);

            //return ::success;

         }


         void out::program_change(int iChannel, unsigned char uchProgram)
         {

            snd_seq_event_t  happening ={};

            happening.queue = m_iQueue;

            //snd_seq_ev_set_fixed(&happening);

            snd_seq_ev_set_source(&happening, m_iPort);

            snd_seq_ev_set_dest(&happening, m_addrDest.client, m_addrDest.port);

            if(use_tick())
            {

               happening.time.tick = m_tick;
               happening.flags = SND_SEQ_TIME_STAMP_TICK;

            }
            else
            {

               snd_seq_ev_set_direct(&happening);

            }

            snd_seq_ev_set_pgmchange(&happening, iChannel, uchProgram);

            //snd_seq_event_output_direct(m_pseq, &happening);

            snd_seq_event_output(m_pseq, &happening);

            //return ::success;

         }


         void out::control_change(int iChannel, unsigned char uchController, unsigned char uchValue)
         {

            snd_seq_event_t  happening ={};

            happening.queue = m_iQueue;

            //snd_seq_ev_set_fixed(&happening);

            snd_seq_ev_set_source(&happening, m_iPort);

            snd_seq_ev_set_dest(&happening, m_addrDest.client, m_addrDest.port);

            if(use_tick())
            {

               happening.time.tick = m_tick;
               happening.flags = SND_SEQ_TIME_STAMP_TICK;

            }
            else
            {

               snd_seq_ev_set_direct(&happening);

            }

            snd_seq_ev_set_controller(&happening, iChannel, uchController, uchValue);

            //snd_seq_event_output_direct(m_pseq, &happening);

            snd_seq_event_output(m_pseq, &happening);

         }


         void out::pitch_bend(int iChannel, unsigned short ushBend)
         {

            snd_seq_event_t  happening ={};

            happening.queue = m_iQueue;

            //snd_seq_ev_set_fixed(&happening);

            snd_seq_ev_set_source(&happening, m_iPort);

            snd_seq_ev_set_dest(&happening, m_addrDest.client, m_addrDest.port);

            if(use_tick())
            {

               happening.time.tick = m_tick;
               happening.flags = SND_SEQ_TIME_STAMP_TICK;

            }
            else
            {

               snd_seq_ev_set_direct(&happening);

            }

            snd_seq_ev_set_pitchbend(&happening, iChannel, ushBend);

            //snd_seq_event_output_direct(m_pseq, &happening);

            snd_seq_event_output(m_pseq, &happening);

         }


         void out::sysex(const ::block & block)
         {

            snd_seq_event_t  happening ={};

            happening.queue = m_iQueue;

            //snd_seq_ev_set_variable(&happening);

            snd_seq_ev_set_source(&happening, m_iPort);

            snd_seq_ev_set_dest(&happening, m_addrDest.client, m_addrDest.port);

            if(use_tick())
            {

               happening.time.tick = m_tick;
               happening.flags = SND_SEQ_TIME_STAMP_TICK;

            }
            else
            {

               snd_seq_ev_set_direct(&happening);

            }

            snd_seq_ev_set_sysex(&happening, block.size(), (void *) block.data());

            //snd_seq_event_output_direct(m_pseq, &happening);

            snd_seq_event_output(m_pseq, &happening);

         }


         void out::tempo(int iTempo)
         {

            snd_seq_event_t  happening ={};

            snd_seq_ev_set_fixed(&happening);
            happening.queue = m_iQueue;
            happening.dest.client = SND_SEQ_CLIENT_SYSTEM;
            happening.dest.port = SND_SEQ_PORT_SYSTEM_TIMER;

            if(use_tick())
            {

               happening.time.tick = m_tick;
               happening.flags = SND_SEQ_TIME_STAMP_TICK;

            }
            else
            {

               snd_seq_ev_set_direct(&happening);

            }
            happening.data.queue.param.value = iTempo;
            happening.data.queue.queue = m_iQueue;


            snd_seq_event_output(m_pseq, &happening);

         }


         bool out::midi_message_step()
         {

//            if(::is_null(m_pseq))
//            {
//
//               return error_failed;
//
//            }
//
//            snd_seq_drain_output(m_pseq);

            //return ::success;

            return true;

         }


         class ::time out::get_time_position()
         {


            snd_seq_queue_status_t * pstatus = nullptr;

            int iError  = snd_seq_queue_status_malloc	(	&pstatus);

            iError = snd_seq_get_queue_status (m_pseq, m_iQueue, pstatus);

            snd_seq_tick_time_t tick =	snd_seq_queue_status_get_tick_time (pstatus);

            auto time = m_psequencer->m_psequence->m_pfile->tick_to_time(tick);

            snd_seq_queue_status_free	(pstatus);

            return time;

         }


      } // namespace alsa


   } // namespace midi


} // namespace music




