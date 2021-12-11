#pragma once


#include <alsa/asoundlib.h>


namespace music
{


   namespace midi
   {


      namespace alsa
      {


         class message_out :
            virtual public ::music::midi::message_out
         {
         public:


            ::u64                   m_u64Start;
            snd_rawmidi_t *         m_prawmidi;
            int64_t                 m_iWrite;
            memory_file             m_file;


            message_out(midi * pmidi, string strDevice);
            virtual ~message_out();

            virtual ::e_status start() override;

            virtual ::e_status note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            virtual ::e_status note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            virtual ::e_status program_change(int iChannel, unsigned char uchProgram) override;
            virtual void control_change(int iChannel, unsigned char uchController, unsigned char uchValue) override;
            virtual void pitch_bend(int iChannel, unsigned short ushBend) override;
            virtual void sysex(const ::block & block) override;

            virtual ::e_status step() override;

            virtual void general_midi_reset() override;

            virtual void reset_all_controllers() override;

            virtual ::e_status add_short_message(byte * pmessage, int iSize);

            virtual bool is_ok() override;

         };


      } // namespace alsa


   } // namespace midi


} // namespace music



