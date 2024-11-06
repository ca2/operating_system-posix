#pragma once


#define C_TEMPO_MAP_CHK     16


namespace music
{


   namespace midi
   {


      namespace alsa
      {


      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA file :
         virtual public ::music::midi::file
      {
      public:



         file(::particle * pparticle);
         virtual ~file();


/*         double GetTempoShiftRate();

         bool IsTrackMute(int32_t iIndex);

         void MuteAll(bool bMute = true, int32_t iExcludeTrack = -1);

         void MuteTrack(int32_t iIndex, bool bMute = true);

         ::e_status WorkSeekBegin();

         ::e_status CalcTkLength();

         ::e_status CreateTempoMap();

         ::e_status ImmediatePutTempoChange();

         ::e_status GetTempoEvent(::music::midi::event & event);

         void OnStop();

         unsigned int GetImageSize();

         LPBYTE GetImage();

         ::e_status Format0();

         ::e_status InsertTempoEvent();

         ::music::midi::tempo_map_entry * GetTempoMapEntry(const imedia::position & position);

         int32_t GetTempoShift();

         ::e_status SetTempoShift(int32_t iTempoShift);

         void ToWorkStorage();

         void FromWorkStorage();

         int32_t GetKeyShift();

         int32_t SetKeyShift(int32_t iKeyShift);

         bool IsSoftKaraokeFile(bool bWork = false, string_array * pstra = NULL);

         bool IsXFFile();

         bool IsTune1000File();

         bool IsOpened();

         ::e_status RebuildIndex();

         ::e_status WriteHeader(MIDIFILEHDR * lpmfh);

         ::e_status ChangeEventDelta(::music::midi::event *pEvent, imedia::position tickNewDelta);

         ::e_status ReplaceSameDeltaEvent(::music::midi::event & pEventNew);

         ::e_status GetPreviousEvent(::music::midi::event * pPreviousEvent, ::music::midi::event * pEvent);

         ::e_status SaveFile(const char * lpFilePath);

         ::e_status WorkWriteXFTracks(string_array & tokena, imedia::position_array & positiona, ::music::xf::info_header & xfinfoheader);

         int32_t CalcMelodyTrack(::music::midi::events ** ppEvents, imedia::position_array & ticka);

         int32_t WorkCalcMelodyTrack(::music::midi::events ** ppEvents, imedia::position_array & positiona, ::int_array & iaTokenLine);

         int32_t GetFormat();

         ::e_status WorkMergeTracks();

         ::e_status WorkStreamRender(LPMIDIHDR lpmh, imedia::position tickMax, unsigned int cbPrerollNomimalMax);

         ::e_status WorkGetNextEvent(::music::midi::event * & pevent, imedia::position tickMax, bool bTkMaxInclusive);

         ::e_status WorkGetNextRawEvent(::music::midi::event * & pevent, imedia::position tickMax, bool bTkMaxInclusive);

         ::e_status WorkGetNextRawMidiEvent(::music::midi::event * & pevent, imedia::position tickMax, bool bTkMaxInclusive);

         ::e_status WorkSeek(::imedia::position tickPosition, LPMIDIHDR lpmh);

         void delete_contents();

         int32_t GetDivision();

         imedia::position GetPosition();

         void AttachSeekSync(::ikaraoke::events_tracks_v1 * ptracksv1);

         bool IsNull();

         void WorkSeekEnd();

         ::e_status OpenFile(::music::midi::file::buffer &file, int32_t openMode);

         ::e_status OpenFile(::file::stream_buffer & file, int32_t openMode);

         ::e_status OpenFile(primitive::memory * pmemstorage, int32_t openMode, ::music::e_storage);

         ::e_status OpenFile(primitive::memory * pmemstorage, ::music::midi::file::e_open eopenmode, ::music::e_storage estorage);

         ::e_status SaveFile(::file::stream_buffer & file);

         ::e_status CloseFile();

         ::e_status GetFileInfo(PSMFFILEINFO psfi);

         int_ptr TicksToMillisecs(imedia::position tickOffset);

         void TicksToMillisecs(imedia::time_array *pMillisArray, imedia::position_array *pTickArray, int_ptr tickOffset);

         void TicksToMillisecs(imedia::time_array_array *ptimeaaArray, imedia::position_2darray & tickaaArray, int_ptr tickOffset);

         void PositionToTime(imedia::time_array_array  & timea, imedia::position_2darray  & positiona, int_ptr tickOffset);

         void PositionToTime(imedia::time_array  & timea, imedia::position_array  & positiona, int_ptr tickOffset);

         imedia::position MillisecsToTicks(imediaclass ::time msOffset);

         imediaclass ::time PositionToTime(imedia::position msOffset);

         imedia::position TimeToPosition(imediaclass ::time msOffset);

         void MillisecsToTicks(imedia::position_array * pTickArray, imedia::time_array *pMillisArray, imediaclass ::time msOffset);

         void TimeToPosition(imedia::position_array & positiona, imedia::time_array & timea, imediaclass ::time msOffset);

         ::e_status StreamRender(LPMIDIHDR lpmh, imedia::position tickMax, unsigned int cbPrerollNomimalMax);

         ::e_status StreamEvent(imedia::position tickDelta, ::music::midi::event * Event, LPMIDIHDR lpmh, imedia::position tickMax, unsigned int cbPrerollNomimalMax);

         ::e_status StreamEventF1(imedia::position tickDelta, array < ::music::midi::event *, ::music::midi::event * > & eventptra, LPMIDIHDR lpmh, imedia::position tickMax, unsigned int cbPrerollNomimalMax);

         ::e_status seek(imedia::position tickPosition, LPMIDIHDR lpmh);

         ::e_status seek(imedia::position tickPosition);

         ::e_status Build();

         ::e_status GetNextEvent(::music::midi::event *& pevent, imedia::position tickMax, bool   bTkMaxInclusive);

         ::e_status GetNextEventTkPosition(imedia::position * pTkPosition, imedia::position tickMax);

         void _SyncSeek(imedia::position tickPosition, ::ikaraoke::events_tracks_v1 * ptracksv1);

         void _SyncSeek(imedia::position tickPosition);

         ::e_status InsertParmData(imedia::position tickDelta, LPMIDIHDR lpmh);

         ::e_status InsertLyricEvents(::ikaraoke::lyric_event_v1 * pLyricEvent, LPMIDIHDR lpmh);

         ::e_status InsertPadEvent(imedia::position tickDelta, LPMIDIHDR lpmh);

         void SetOpened(bool bOpened = true);
*/

      };


      } // namespace alsa


   } // namespace midi


} // namespace music





