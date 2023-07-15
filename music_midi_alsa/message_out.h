#pragma once


#include "acme/filesystem/file/memory_file.h"
#include "app-veriwell/multimedia/music/midi/message_out.h"
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
            ~message_out() override;

            void start() override;

            void note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            void note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            void program_change(int iChannel, unsigned char uchProgram) override;
            void control_change(int iChannel, unsigned char uchController, unsigned char uchValue) override;
            void pitch_bend(int iChannel, unsigned short ushBend) override;
            void sysex(const ::block & block) override;

            bool step() override;

            void general_midi_reset() override;

            void xg_system_on() override;

            void reset_all_controllers() override;

            virtual void add_short_message(::u8 * pmessage, int iSize);

            bool is_ok() override;

         };


      } // namespace alsa


   } // namespace midi


} // namespace music



