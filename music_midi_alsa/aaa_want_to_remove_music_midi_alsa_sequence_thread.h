#pragma once



namespace music
{


   namespace midi
   {


      namespace alsa
      {


         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA sequence_thread :
            virtual public ::music::midi::sequence_thread
         {
         public:


            sequence_thread(::particle * pparticle);
            virtual ~sequence_thread();


            void install_message_routing(::message::sender * pinterface);

            ::music::midi::sequence * get_sequence();
            void Stop(imedia_time msEllapse);

            bool PostMidiSequenceEvent(::music::midi::sequence * pseq, ::music::midi::sequence::e_event event);

            bool PostMidiSequenceEvent(::music::midi::sequence * pseq, ::music::midi::sequence::e_event event, LPMIDIHDR lpmh);

            void PostNotifyEvent(::music::midi::e_notify_event eevent);

            //virtual void PrerollRateAndWait(double rate = 0.0) override;
            //virtual void PrerollAndWait(imedia_position tickStart) override;
            //virtual void PlayRate(double dRate = 0.0) override;
            //virtual void Play(imedia_position tickStart) override;
            void PostGMReset();
            void PostTempoChange();
            void SendTempoChange();

            void ExecuteCommand(::music::midi::player_command * pcommand);
            void _ExecuteCommand(::music::midi::player_command * pcommand);

            virtual bool init_thread() override;
            virtual void term_thread() override;

            DECL_GEN_SIGNAL(OnCommand);
            DECL_GEN_SIGNAL(OnMidiSequenceEvent);
            DECL_GEN_SIGNAL(OnRun);

         };


      } // namespace alsa


   } // namespace midi


} // namespace music





