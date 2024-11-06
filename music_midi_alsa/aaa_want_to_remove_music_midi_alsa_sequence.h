#pragma once


#define  VERSION_MINOR              0x00
#define  VERSION_MAJOR              0x04
#define  SEQ_VERSION                ((::u32)(::u16)((unsigned char)VERSION_MINOR | (((::u16)(unsigned char)VERSION_MAJOR) << 8)))

#define MMSG_DONE                   (WM_USER+20)


namespace music
{


   namespace midi
   {


      namespace alsa
      {


      class file;
      class sequence;
      class sequence_thread;


      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA midi_callback_data
      {
      public:


         sequence *          m_psequence;


      };


      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA sequence :
         virtual public ::music::midi::sequence
      {
      public:

         class buffer_array;

         enum e_message
         {

            message_run = WM_APP + 1050,

         };


         class buffer
         {
         public:


            MIDIHDR              m_midihdr;
            memory               m_storage;
            bool                 m_bPrepared;

            bool IsPrepared();
            void Reset();
            void Initialize(int32_t iSize, ::u32 dwUser);

            ::e_status midiStreamOut(seq_context_t * hmidiout);
            //::e_status midiOutPrepareHeader(HMIDIOUT hmidiout);
            //::e_status midiOutUnprepareHeader(HMIDIOUT hmidiout);


            inline LPMIDIHDR GetMidiHdr() { return &m_midihdr; }

            void SetNextMidiHdr(LPMIDIHDR lpNext);


         };


         class buffer_array :
            public array < buffer, buffer >
         {
         public:


            void Reset();
            void Initialize(int32_t iCount, int32_t iSize, ::u32 dwUser);


            ::e_status midiStreamOut(seq_context_t * hmidiout);
            //::e_status midiOutPrepareHeader(HMIDIOUT hmidiout);
            //::e_status midiOutUnprepareHeader(HMIDIOUT hmidiout);

         };

         class event :
            public ::music::midi::sequence::event
         {
         public:


            LPMIDIHDR                     m_lpmh;


         };


         buffer_array                  m_buffera;

         seq_context_t *               m_pseq; /* The snd_seq handle to /dev/snd/seq */

         bool                          m_bTimerStarted;	/* True if timer is running */

         int                           m_iPortCount;		/* Ports allocated */

         int                           m_iClient;

         int                           m_iPort;

         array < ::music::midi::event * >    m_evptra;

         //struct seq_context *main; /* Pointer to the main context */

         //GSList *ctlist;		/* Context list if a main context */

         midi_callback_data            m_midicallbackdata;

         imedia_position            m_tkPosition;

         array < imedia_position >    m_iaBuffered;

         int                           m_iBuffered;
         bool                          m_bPlay;
         sp(midi_out)                  m_pmidiout;


         sequence(::particle * pparticle);
         virtual ~sequence();


//         inline ::u32 get_status();
//         inline ::u32 GetPreviousState();
//         ::u32 set_status(::u32 uiState);
//
//         void SetSpecialModeV001Flag(bool bSet = true);

//         void MuteAll(bool bMute = true, int32_t iExcludeTrack = -1);
//         void MuteTrack(int32_t iIndex, bool bMute = true);
//
//
//         virtual int32_t GetDefaultCodePage();

//         void Prepare(::ikaraoke::data & data);
//         void Prepare(int32_t iTrack, ::ikaraoke::data & data);
//         void Prepare(
//            string_array_array & straa,
//            imedia_position_2darray & tickaaTokensTicks,
//            int32_t iMelodyTrack,
//            int2a & ia2TokenLine,
//            ::ikaraoke::data & data);

         //imedia::position GetPositionTicks();
         void SetLevelMeter(int32_t iLevel);
         ::e_status CloseStream();
         bool SetMidiOutDevice(::u32 uiDevice);
         int32_t SetKeyShift(int32_t iKeyShift);
         int32_t GetKeyShift();

         void OnMidiPlaybackEnd(::music::midi::sequence::event * pevent);
         int32_t SetTempoShift(int32_t iTempoShift);

         void OnPositionCB(LPMIDIHDR lpmidihdr);
         void OnDone(seq_context_t * hmidistream, LPMIDIHDR lpmidihdr);
         virtual void GetTimeLength(imedia_time & time);
         virtual void GetPositionLength(imedia_position & position);

         using ::ikaraoke::karaoke::TimeToPosition;
         using ::ikaraoke::karaoke::PositionToTime;

         virtual imedia_position TimeToPosition(imedia_time time);
         virtual imedia_time PositionToTime(imedia_position position);

         virtual bool IsOpened();

         virtual bool IsNull();
         virtual void SetTempoChangeFlag(bool bSet = true);
         virtual bool IsChangingTempo();

         virtual double GetTempoShift();
//         virtual void GetMidiDoneData(::music::midi::LPMIDIDONEDATA lpmdd);
         virtual bool IsInSpecialModeV001();
         virtual bool WasInSpecialModeV001();
         //virtual void SetSpecialModeV001Operation(::u32 uiOperation);

         virtual void OnEvent(::music::midi::sequence::event * pevent);


         ::e_status AllocBuffers();

         VOID FreeBuffers();

         //::e_status OpenFile(const char * lpFileName, int32_t openMode);
//         ::e_status OpenFile(::music::midi::sequence & sequence, int32_t iOpenMode);
//         ::e_status OpenFile(::file::file & ar, int32_t openMode) override;
//         ::e_status OpenFile(const char * lpFileName, int32_t openMode);
//         ::e_status OpenFile(memory * pmemorystorage, int32_t openMode, ::music::e_storage estorage);

         ::e_status CloseFile();
         //::e_status SaveFile(const char * lpFileName);
         //::e_status SaveFile();
         //::e_status SaveFile(::file::file & file) override;
         //::e_status Preroll(::thread * pthread, ::music::midi::LPPREROLL lpPreroll, bool bThrow);
         ::e_status Start();

         ::e_status Pause();

         ::e_status Restart();

         //::e_status Stop(::u32 dwEllapse);
         ::e_status Stop();

         //void get_position(imedia_position  & time) override;
//         void get_time(imedia_time  & time) override;

         //::e_status get_ticks(imedia_position & time) override;
         //::e_status get_millis(imedia_time & time) override;


         //imedia_position MillisecsToTicks(imedia_time msOffset);

         //imedia_time TicksToMillisecs(imedia_position tickOffset);

         bool IsPlaying();

//         static void CALLBACK MidiOutProc(HMIDIOUT hmo, ::u32 wMsg, ::u32 dwInstance, ::u32 dwParam1, ::u32 dwParam2);

         sp(message_out) get_message_out();

         bool IsSettingPosition();

         void SetSettingPositionFlag(bool bSet = TRUE);

         imedia_position GetQuarterNote();


         inline sp(::music::midi::alsa::file) file()
         {
            return get_file();
         }

         inline sp(::music::midi::alsa::sequence_thread) thread()
         {
            return m_pthread;
         }

         using ::music::midi::sequence::create_new_event;
         virtual ::music::midi::sequence::event * create_new_event(::music::midi::sequence::e_event eevent, LPMIDIHDR lpmidihdr);

         //int seq_dump();
         //void seq_run();
         //::music::midi::event * seq_get_next_event();



         //int seq_play(::music::midi::event * pevent);
         //::e_status seq_start();

      };


      } // namespace alsa


   } // namespace midi


} // namespace music







