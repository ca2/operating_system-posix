#pragma once


#include "app-veriwell/multimedia/music/midi/out.h"


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


            void initialize_message_out(::music::midi::midi * pmidi, const ::string & strDevice) override;


            void open() override;
            void close() override;


            void start() override;
            void stop() override;


            bool use_tick() const override;


            void note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            void note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            void program_change(int iChannel, unsigned char uchProgram) override;
            void control_change(int iChannel, unsigned char uchController, unsigned char uchValue) override;
            void pitch_bend(int iChannel, unsigned short ushBend) override;
            void sysex(const ::block & block) override;
void tempo(int iTempo) override;

            void send_short_message(::music::midi::enum_midi_message etype, int iChannel, int iData1, int iData2) override;


            bool midi_message_step() override;


            class ::time get_time_position() override;


         };


      } // namespace alsa


   } // namespace midi


} // namespace music




