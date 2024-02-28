#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace alsa
      {


         sequence_thread::sequence_thread(::particle * pparticle) :
            object(pparticle),
            thread(pparticle),
            ::music::midi::sequence_thread(pparticle)
         {
         }

         sequence_thread::~sequence_thread()
         {
         }


         bool sequence_thread::init_thread()
         {

            set_thread_priority(::priority_highest);

            return true;

         }


         void sequence_thread::term_thread()
         {

            thread::term_thread();

         }


         void sequence_thread::install_message_routing(::message::sender * pinterface)
         {

            IGUI_MSG_LINK(message_player_command, pinterface, this, &sequence_thread::OnCommand);
            IGUI_MSG_LINK(::music::midi::sequence::message_event, pinterface, this, &sequence_thread::OnMidiSequenceEvent);
            IGUI_MSG_LINK(::music::midi::alsa::sequence::message_run, pinterface, this, &sequence_thread::OnRun);

         }


         void sequence_thread::Stop(imedia_time msEllapse)
         {
            get_sequence()->Stop();
            m_eventStop.wait(millis(msEllapse));
         }

         ::music::midi::sequence * sequence_thread::get_sequence()
         {
            return m_psequence;
         }


         bool sequence_thread::PostMidiSequenceEvent(::music::midi::sequence * pseq, ::music::midi::sequence::e_event eevent)
         {

            return post_object(::music::midi::sequence::message_event,  (WPARAM) pseq,  pseq->create_new_event(eevent));

         }


         bool sequence_thread::PostMidiSequenceEvent(::music::midi::sequence * pseq, ::music::midi::sequence::e_event eevent, LPMIDIHDR lpmh)
         {

            sp(sequence) seq = pseq;

            return post_object(::music::midi::sequence::message_event,  (WPARAM) pseq, seq->create_new_event(eevent, lpmh));

         }


         void sequence_thread::OnMidiSequenceEvent(::message::message * pobj)
         {

//            music::midi::sequence_thread::OnMidiSequenceEvent(pobj);

            SCAST_PTR(::message::base, pbase, pobj);

            sp(::music::midi::sequence::event) pevent(pbase->m_lparam);

            sp(::music::midi::alsa::sequence) pseq = pevent->m_psequence;

            pseq->OnEvent(pevent);

            switch(pevent->m_eevent)
            {
            case ::music::midi::sequence::e_event_midi_playback_end:
               {

                  ::music::midi::sequence::player_link & link = get_sequence()->GetPlayerLink();

                  if(link() & ::music::midi::sequence::e_flag_tempo_change)
                  {

                     PrerollAndWait(link.m_tkRestart);

                     get_sequence()->SetTempoChangeFlag(false);

                     get_sequence()->Start();

                     link() -= ::music::midi::sequence::e_flag_tempo_change;

                  }
                  else if(link() & ::music::midi::sequence::e_flag_setting_position)
                  {

                     link() -= ::music::midi::sequence::e_flag_setting_position;

                     try
                     {

                        PrerollAndWait(link.m_tkRestart);

                     }
                     catch(exception_sp e)
                     {

                        return;

                     }

                     get_sequence()->Start();

                     PostNotifyEvent(::music::midi::notify_event_position_set);

                  }
                  else if(link() & ::music::midi::sequence::e_flag_midi_out_device_change)
                  {

                     link() -= ::music::midi::sequence::e_flag_midi_out_device_change;

                     try
                     {

                        PrerollAndWait(link.m_tkRestart);

                     }
                     catch(exception_sp e)
                     {

                        return;

                     }

                     get_sequence()->Start();

                  }
                  else if(link() & ::music::midi::sequence::e_flag_midi_out_and_restart)
                  {

                     link() -= ::music::midi::sequence::e_flag_midi_out_and_restart;

                     try
                     {

                        PrerollAndWait(link.m_tkRestart);

                     }
                     catch(exception_sp e)
                     {

                        return;

                     }

                     get_sequence()->Start();

                  }
                  else
                  {

                     if(link() & ::music::midi::sequence::e_flag_stop)
                     {

                        link() -= ::music::midi::sequence::e_flag_stop;

                        link.OnFinishCommand(::music::midi::command_stop);

                     }

                     PostNotifyEvent(::music::midi::notify_event_playback_end);

                  }

               }

               break;

            case ::music::midi::sequence::e_event_operation:
               {

                  PostNotifyEvent(::music::midi::notify_event_generic_mmsg_done);

               }
               break;

            case ::music::midi::sequence::e_event_midi_playback_start:
               {

                  pseq->m_psequencer = pseq->create_sequencer();

                  pseq->m_psequencer->begin();

                  PostNotifyEvent(::music::midi::notify_event_playback_start);

               }
               break;

            case ::music::midi::sequence::e_event_midi_playback_out:
               {

                  PostNotifyEvent(::music::midi::notify_event_midi_stream_out);

               }
               break;

            }


         }


         void sequence_thread::PostNotifyEvent(::music::midi::e_notify_event eevent)
         {

            if(m_pplayer != NULL)
            {

               auto pdata = __sp(aaa_primitive_new ::music::midi::notify_event());

               pdata->m_enotifyevent = eevent;

               m_pplayer->post_object(message_player_notify_event, 0, pdata);

            }

         }


//         void sequence_thread::Play(imedia_position tickStart)
//         {
//
//            ASSERT(get_sequence() != NULL);
//
//            ASSERT(get_sequence()->get_state() == ::music::midi::sequence::e_state_opened);
//
//            PrerollAndWait(tickStart);
//
//            get_sequence()->Start();
//
//         }


//         void sequence_thread::PlayRate(double dRate)
//         {
//
//            ASSERT(get_sequence() != NULL);
//
//            ASSERT(get_sequence()->get_state() == ::music::midi::sequence::e_state_opened);
//
//            PrerollAndWait(dRate);
//
//            get_sequence()->Start();
//
//         }


//         void sequence_thread::PrerollAndWait(imedia_position tickStart)
//         {
//
//            ::music::midi::PREROLL                 preroll;
//
//            preroll.tickBase = tickStart;
//            preroll.tickEnd  = get_sequence()->m_tkLength;
//
//            get_sequence()->set_midi_out_device(m_pplayer->get_midi_out_device());
//
//            try
//            {
//               get_sequence()->Preroll(this, &preroll, true);
//            }
//            catch (exception_sp e)
//            {
//               string str;
//               ASSERT(FALSE);
//
//               /* super merge module      CVmsMusDll::load_string(str, IDS_PREROLLUSERERROR001);
//               pme->SetUserText(str);*/
//               throw e;
//            }
//
//         }


//         void sequence_thread::PrerollRateAndWait(double dRate)
//         {
//            ::music::midi::PREROLL                 preroll;
//
//            ::math::math::MaxClip(&dRate, 1.0);
//            ::math::math::MinClip(&dRate,  0.0);
//
//            preroll.tickBase = (imedia_position) (int32_t) ((double) get_sequence()->m_tkLength * dRate);
//            preroll.tickEnd  = get_sequence()->m_tkLength;
//
//            get_sequence()->set_midi_out_device(m_pplayer->get_midi_out_device());
//
//            try
//            {
//               get_sequence()->Preroll(this, &preroll, true);
//            }
//            catch (exception_sp e)
//            {
//               throw not_implemented();
//               /*string str;
//               str.load_string(IDS_PREROLLUSERERROR001);
//               pme->SetUserText(str);*/
//               throw e;
//            }
//
//            //    if(!get_sequence()->IsInSpecialModeV001())
//            //  {
//            //    SendMessage(m_oswindow_, WM_USER, 33, preroll.tickBase);
//            //}
//         }


         void sequence_thread::PostGMReset()
         {
            ASSERT(!get_sequence()->IsPlaying());
            get_sequence()->set_operation(::music::midi::operation_general_midi_reset);
            PrerollAndWait(0.0);
            get_sequence()->Start();

         }

         void sequence_thread::PostTempoChange()
         {
            ASSERT(!get_sequence()->IsPlaying());
            get_sequence()->set_operation(::music::midi::operation_tempo_change);
            PrerollAndWait(0.0);
            get_sequence()->Start();
         }

         void sequence_thread::SendTempoChange()
         {
            ASSERT(!get_sequence()->IsPlaying());
            get_sequence()->m_evMmsgDone.ResetEvent();
            PostTempoChange();
            get_sequence()->m_evMmsgDone.wait();
         }


         void sequence_thread::ExecuteCommand(::music::midi::player_command * pcommand)
         {

            post_object(message_player_command, 0, pcommand);

         }


         void sequence_thread::OnRun(::message::message * pobj)
         {

//            sp(sequence) pseq = get_sequence();
//
//            snd_seq_event_t * pev = NULL;
//
//            imedia_position pos = 0;
//
//            pseq->get_position(pos);
//
//            while(pseq->m_iaBuffered.get_count() > 0 && pseq->m_iaBuffered[0] <= pos)
//            {
//
//               pseq->m_iaBuffered.remove_at(0);
//
//            }
//
//            if(pseq->seq_dump() < 0)
//            {
//
//               if(pseq->m_iaBuffered.get_count() <= 0 || !pseq->m_bPlay)
//               {
//
//                  PostMidiSequenceEvent(pseq, ::music::midi::sequence::e_event_midi_playback_end);
//
//                  return;
//
//               }
//
//               Sleep(84);
//
//            }
//            else
//            {
//
//               Sleep(5);
//
//            }
//
//            post_message(sequence::message_run);

         }


         void sequence_thread::OnCommand(::message::message * pobj)
         {

            SCAST_PTR(::message::base, pbase, pobj);

            sp(::music::midi::player_command) spcommand(pbase->m_lparam);

            try
            {

               _ExecuteCommand(spcommand);

            }
            catch(exception_sp e)
            {

            }
            catch(...)
            {

            }

            spcommand->OnFinish();

         }


         void sequence_thread::_ExecuteCommand(::music::midi::player_command * pcommand)
         {
            switch(pcommand->GetCommand())
            {
            case ::music::midi::command_play:
               {
                  if(pcommand->m_flags.is_signalized(::music::midi::player_command::flag_dRate))
                  {
                     Play(pcommand->m_dRate);
                  }
                  else if(pcommand->m_flags.is_signalized(::music::midi::player_command::flag_ticks))
                  {
                     Play(pcommand->m_ticks);
                  }
                  else
                  {
                     PlayRate();
                  }
               }
               break;
            case ::music::midi::command_close_device:
               {
                  if(get_sequence() != NULL)
                  {
                     get_sequence()->close_file();
                  }
               }
               break;
            case ::music::midi::command_stop:
               {
                  m_eventStop.ResetEvent();
                  ::e_status            mmrc;
                  ::music::midi::sequence::player_link & link = get_sequence()->GetPlayerLink();

                  link.SetCommand(pcommand);

                  link() |= ::music::midi::sequence::e_flag_stop;

                  if(::success != (mmrc = get_sequence()->Stop()))
                  {

                     __throw(aaa_primitive_new ::multimedia::exception(multimedia::exception_music, mmrc));

                  }

               }
               break;
            case ::music::midi::command_stop_and_restart:
               {

                  ::e_status mmrc;

                  ::music::midi::sequence::player_link & link = get_sequence()->GetPlayerLink();

                  link.SetCommand(pcommand);

                  link() |= ::music::midi::sequence::e_flag_midi_out_and_restart;

                  link.m_tkRestart = get_sequence()->get_position_ticks();

                  if(::success != (mmrc = get_sequence()->Stop()))
                  {

                     __throw(aaa_primitive_new ::multimedia::exception(multimedia::exception_music, mmrc));

                  }

               }
               break;
            default:
            {
            music::midi::sequence_thread::_ExecuteCommand(pcommand);
            }
            break;

            }
         }


      } // namespace alsa


   } // namespace midi


} // namespace music









