#pragma once


namespace music
{


   namespace midi
   {


      namespace alsa
      {


         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA out :
            virtual public ::music::midi::out
         {
         public:


            snd_seq_t *                   m_pseq;
            int                           m_iPort;

            string                        m_strClientName;

            snd_seq_port_subscribe_t *    m_subscribe;
            snd_seq_addr_t                m_addrSender;
            snd_seq_addr_t                m_addrDest;

            int                           m_iQueue;


            out();
            ~out() override;


            ::e_status initialize_message_out(::music::midi::midi * pmidi, const ::string & strDevice) override;


            ::e_status open() override;
            ::e_status close() override;


            ::e_status start() override;
            ::e_status stop() override;


            bool use_tick() const override;


            ::e_status note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            ::e_status note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            ::e_status program_change(int iChannel, unsigned char uchProgram) override;
            void control_change(int iChannel, unsigned char uchController, unsigned char uchValue) override;
            void pitch_bend(int iChannel, unsigned short ushBend) override;
            void sysex(const ::block & block) override;
void tempo(int iTempo) override;

            ::e_status send_short_message(::music::midi::e_message etype, int iChannel, int iData1, int iData2) override;


            ::e_status step() override;


         };


      } // namespace alsa


   } // namespace midi


} // namespace music




