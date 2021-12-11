#pragma once


namespace music
{


   namespace midi
   {


      namespace alsa
      {



         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA midi :
            virtual public ::music::midi::midi
         {
         public:


            //base_library                 m_library;
            //midi_listener_set             m_listenerptra;
            //::u32                      m_uiMidiOutDevice;


            midi();
            virtual ~midi();


            typedef void (midi:: * action_func_t)(snd_seq_t *seq, snd_seq_client_info_t *cinfo, snd_seq_port_info_t *pinfo, int count);

            //virtual ::e_status enumerate_midi_devices();
            virtual void enumerate_midi_out_devices() override;

            //void RemoveListener(midi_listener * plistener);
            //void AddListener(midi_listener * plistener);
            //::u32 GetMidiOutDevice();
            //void SetMidiOutDevice(::u32 uiDevice);
            //bool Initialize();


            //bool IsSoftKaraokeFile(const char * lpszPathName);
            //bool IsXFFile(const char * lpcszPathName);


            //virtual bool veriwell_multimedia_music_midi_factory_exchange();


   /*            void mmsystem_LogMidiInCaps(::u32 i, MIDIINCAPSW caps);
            void mmsystem_GetMidiInDeviceInterface(::u32 i);
            void mmsystem_LogMidiOutCaps(::u32 i, MIDIOUTCAPSW caps);
            void mmsystem_GetMidiOutDeviceInterface(::u32 i);*/


            virtual __pointer(::music::midi::message_out) get_message_out(const string& strDevice) override;
            virtual __pointer(::music::midi::sequencer) create_midi_sequencer(sequence * psequence, const string& strDevice) override;


            using ::music::midi::midi::translate_os_result;
            virtual ::e_status translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pobject, int64_t iOsResult, const string & strContext, const string & strText);


            virtual bool Initialize();

            //virtual bool list_midi_out_card_devices(int card);

            //virtual bool list_midi_out_devices(snd_ctl_t *ctl, int card, int device);

            void list_each_subs(snd_seq_t *seq, snd_seq_query_subscribe_t *subs, snd_seq_query_subs_type_t type, const char *msg);

            void list_subscribers(snd_seq_t *seq, const snd_seq_addr_t *addr);

            void error_handler(const char *file, int line, const char *function, int err, const char *fmt, ...);

            int check_permission(snd_seq_port_info_t *pinfo, int perm);

            void do_search_port(snd_seq_t *seq, int perm, action_func_t do_action);

            void print_port(snd_seq_t *seq, snd_seq_client_info_t *cinfo,
                                  snd_seq_port_info_t *pinfo, int count);

            void print_port_and_subs(snd_seq_t *seq, snd_seq_client_info_t *cinfo,
                                            snd_seq_port_info_t *pinfo, int count);


         };


      } // namespace alsa


   } // namespace midi


} // namespace music




