#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace alsa
      {


         file::file(::particle * pparticle) :
            object(pparticle),
            ::music::midi::file(pparticle)
         {

            m_tkLength              = 0;
            m_dwFormat              = 0;
            m_dwTracks              = 0;
//            m_dw        = 0;

            m_dwPendingUserEvent    = 0;
            m_cbPendingUserEvent    = 0;
            m_hpbPendingUserEvent   = 0;

            //m_tempoa.set_size(0, C_TEMPO_MAP_CHK);

            m_iKeyShift             = 0;
            m_dTempoShift           = 0;


            m_pFileHeader = NULL;

            //keep_pointer((void **) &m_pMThd);
            //keep_pointer((void **) &m_pFileHeader);

         }


         file::~file()
         {

            close_file();

         }

//
//      ::e_status file::OpenFile(::music::midi::file::buffer &file, int32_t openMode)
//      {
//
//         ::e_status               smfrc = ::music::success;
//
//         m_ptracks->m_iMelodyTrackTipA = -1;
//
//         m_iOpenMode = openMode;
//
//         GetFlags().unsignalize_all();
//
//         if(openMode == ::music::midi::file::OpenForParsingLevel3)
//         {
//            GetFlags().signalize(::music::midi::file::DisablePlayLevel1Operations);
//         }
//
//         m_ptracks->GetFlags() = GetFlags();
//
//         unsigned int cbImage = file.GetImageSize();
//         try
//         {
//            allocate(cbImage);
//         }
//         catch(memory_exception * pe)
//         {
//            information( "smfOpenFile: No primitive::memory for image! [%08lX]", cbImage);
//            smfrc = ::music::ENoMemory;
//            delete pe;
//            goto smf_Open_File_Cleanup;
//         }
//
//         LPBYTE lpbImage;
//
//         lpbImage = GetImage();
//
//         memory_copy(lpbImage, file.GetImage(), cbImage);
//
//         /* If the file exists, parse it just enough to pull out the header and
//         ** build a track index.
//         */
//         smfrc = Build();
//
//smf_Open_File_Cleanup:
//
//         if (::music::success != smfrc)
//         {
//         }
//         else
//         {
//            SetOpened();
//         }
//
//         return smfrc;
//      }
//
//      ::e_status file::OpenFile(primitive::memory * pmemorystorage, int32_t openMode, e_storage estorage)
//      {
//         ASSERT(pmemorystorage != NULL);
//
//         ::e_status smfrc = ::music::success;
//
//         m_ptracks->m_iMelodyTrackTipA = -1;
//
//         m_iOpenMode = openMode;
//
//         GetFlags().unsignalize_all();
//
//         if(openMode ==::music::midi::file::OpenForParsingLevel3)
//         {
//            GetFlags().signalize(::music::midi::file::DisablePlayLevel1Operations);
//         }
//
//         m_ptracks->GetFlags() = GetFlags();
//
//         if(estorage == ::music::storage_copy)
//         {
//            this->get_primitive_memory()->operator=(*pmemorystorage);
//         }
//         else if(estorage == ::music::storage_attach)
//         {
//            if(m_estorage == ::music::storage_attach)
//            {
//               detach();
//            }
//            else if(m_estorage == ::music::storage_own)
//            {
//               delete detach();
//            }
//            attach(pmemorystorage);
//         }
//         else if(estorage == ::music::storage_own)
//         {
//            if(m_estorage == ::music::storage_attach)
//            {
//               detach();
//            }
//            this->get_primitive_memory()->operator=(*pmemorystorage);
//         }
//
//         m_estorage = estorage;
//
//
//         /* If the file exists, parse it just enough to pull out the header and
//         ** build a track index.
//         */
//
//         smfrc = Build();
//
//         if (::music::success == smfrc)
//         {
//            SetOpened();
//         }
//         return smfrc;
//      }
//
//
//      ::e_status file::OpenFile(primitive::memory * pmemorystorage, ::music::midi::file::e_open eopenmode, e_storage estorage)
//      {
//
//         return OpenFile(pmemorystorage, (int32_t) eopenmode, estorage);
//
//      }
//
//
//      /*****************************************************************************
//      *
//      * smfOpenFile
//      *
//      * This function opens a MIDI file for access.
//      *
//      * psofs                     - Specifies the file to open and associated
//      *                             parameters. Contains a valid HSMF handle
//      *                             on success.
//      *
//      * Returns
//      *   ::music::success The specified file was opened.
//      *
//      *   SMF_OPEN_FAILED The specified file could not be opened because it
//      *     did not exist or could not be created on the disk.
//      *
//      *   ::music::EInvalidFile The specified file was corrupt or not a MIDI file.
//      *
//      *   ::music::ENoMemory There was insufficient primitive::memory to open the file.
//      *
//      *   SMF_INVALID_PARM The given flags or time division in the
//      *     SMFOPENFILESTRUCT were invalid.
//      *
//      *****************************************************************************/
//      ::e_status file::OpenFile(::file::stream_buffer &ar, int32_t openMode)
//      {
//         ::e_status               smfrc = ::music::success;
//
//         m_ptracks->m_iMelodyTrackTipA = -1;
//
//         m_iOpenMode = openMode;
//
//         GetFlags().unsignalize_all();
//
//         if(openMode == ::music::midi::file::OpenForParsingLevel3)
//         {
//            GetFlags().signalize(::music::midi::file::DisablePlayLevel1Operations);
//         }
//
//         m_ptracks->GetFlags() = GetFlags();
//
//
//         get_memory()->transfer_from_begin(ar);
//
//         /* If the file exists, parse it just enough to pull out the header and
//         ** build a track index.
//         */
//         smfrc = Build();
//
//         if (::music::success != smfrc)
//         {
//         }
//         else
//         {
//            SetOpened();
//         }
//
//         return smfrc;
//      }
//
//      /*****************************************************************************
//      *
//      * smfCloseFile
//      *
//      * This function closes an open MIDI file.
//      *
//      * hSmf                      - The handle of the open file to close.
//      *
//      * Returns
//      *   ::music::success The specified file was closed.
//      *   SMF_INVALID_PARM The given handle was not valid.
//      *
//      * Any track handles opened from this file handle are invalid after this
//      * call.
//      *
//      *****************************************************************************/
//      ::e_status file::CloseFile()
//      {
//         single_lock(&m_cs, TRUE);
//         SetOpened(false);
//         delete_contents();
//         return ::music::success;
//      }
//
//
//      void file::delete_contents()
//      {
//         single_lock(&m_cs, TRUE);
//         SetOpened(false);
//
//
//         m_ptracks->clear();
//
//
//         m_tempomap.remove_all();
//
//
//         m_bPendingLyric = false;
//
//
//         for(int32_t i = 0; i < m_mepaOnQuarterNote.get_size(); i++)
//         {
//            delete m_mepaOnQuarterNote.element_at(i);
//         }
//         m_mepaOnQuarterNote.remove_all();
//
//
//         for(int32_t i = 0; i < m_mepaImmediate.get_size(); i++)
//         {
//            delete m_mepaImmediate.element_at(i);
//         }
//         m_mepaImmediate.remove_all();
//
//
//         m_tkLength              = 0;
//         m_dwFormat              = 0;
//         m_dwTracks              = 0;
//         m_dwTimeDivision        = 0;
//
//         m_dwPendingUserEvent    = 0;
//         m_cbPendingUserEvent    = 0;
//         m_hpbPendingUserEvent   = 0;
//
//
//         m_iKeyShift             = 0;
//         m_iTempoShift           = 0;
//
//         m_pFileHeader           = NULL;
//
//      }
//
//
//
//
//      /******************************************************************************
//      *
//      * smfGetFileInfo This function gets information about the MIDI file.
//      *
//      * hSmf                      - Specifies the open MIDI file to inquire about.
//      *
//      * psfi                      - A structure which will be filled in with
//      *                             information about the file.
//      *
//      * Returns
//      *   ::music::success Information was gotten about the file.
//      *   SMF_INVALID_PARM The given handle was invalid.
//      *
//      *****************************************************************************/
//      ::e_status file::GetFileInfo(
//         PSMFFILEINFO            psfi)
//      {
//         //    PSMF                    pSmf = (PSMF)hSmf;
//         //    assert(pSmf != NULL);
//         ASSERT(psfi != NULL);
//
//         /*
//         ** Just fill in the structure with useful information.
//         */
//         psfi->dwTracks      = m_dwTracks;
//         //psfi->dwTracks      = m_ptracks->get_size();
//         psfi->dwFormat      = m_dwFormat;
//         psfi->dwTimeDivision= m_dwTimeDivision;
//         psfi->tickLength      = m_tkLength;
//
//         return ::music::success;
//      }
//
//      /******************************************************************************
//      *
//      * smfTicksToMillisecs
//      *
//      * This function returns the millisecond offset into the file given the
//      * tick offset.
//      *
//      * hSmf                      - Specifies the open MIDI file to perform
//      *                             the conversion on.
//      *
//      * tickOffset                  - Specifies the tick offset into the stream
//      *                             to convert.
//      *
//      * Returns the number of milliseconds from the start of the stream.
//      *
//      * The conversion is performed taking into ac::collection::count the file's time division and
//      * tempo map from the first track. Note that the same millisecond value
//      * might not be valid at a later time if the tempo track is rewritten.
//      *
//      *****************************************************************************/
//      int_ptr file::TicksToMillisecs(imedia::position tickOffset)
//      {
//         single_lock(&m_cs, true);
//         if(!IsOpened())
//            return 0xffffffff;
//
//         ::music::midi::tempo_map_entry *  ptempo;
//         int32_t                  idx;
//         unsigned int                 uSMPTE;
//         unsigned int                dwTicksPerSec;
//
//         if (tickOffset > m_tkLength)
//         {
//            information( "sTTM: Clipping ticks to file length!");
//            tickOffset = m_tkLength;
//         }
//
//         /* SMPTE time is easy -- no tempo map, just linear conversion
//         ** Note that 30-Drop means nothing to us here since we're not
//         ** converting to a colonized format, which is where dropping
//         ** happens.
//         */
//         if (m_dwTimeDivision & 0x8000)
//         {
//            uSMPTE = -(int32_t)(char)((m_dwTimeDivision >> 8)&0xFF);
//            if (29 == uSMPTE)
//               uSMPTE = 30;
//
//            dwTicksPerSec = (unsigned int)uSMPTE *
//               (unsigned int)(unsigned char)(m_dwTimeDivision & 0xFF);
//
//            return (unsigned int)muldiv32((int32_t) tickOffset, 1000L, dwTicksPerSec);
//         }
//
//         /* Walk the tempo map and find the nearest tick position. Linearly
//         ** calculate the rest (using MATH.ASM)
//         */
//
//         for (idx = 0; idx < m_tempomap.get_size(); idx++)
//         {
//            ptempo = &m_tempomap.element_at(idx);
//            if (tickOffset < ptempo->tickTempo)
//               break;
//         }
//
//         if(idx <= 0)
//            idx = 0;
//         else
//            idx--;
//
//         if(idx >= m_tempomap.get_size())
//            return 0;
//
//         if(idx <= 0)
//            ptempo = &m_tempomap.element_at(0);
//         else
//            ptempo = &m_tempomap.element_at(idx);
//
//         /* ptempo is the tempo map entry preceding the requested tick offset.
//         */
//
//         return ptempo->msBase + muldiv32((int32_t)(tickOffset - ptempo->tickTempo), ptempo->dwTempo, 1000L * m_dwTimeDivision);
//
//      }
//
//
//      /******************************************************************************
//      *
//      * smfMillisecsToTicks
//      *
//      * This function returns the nearest tick offset into the file given the
//      * millisecond offset.
//      *
//      * hSmf                      - Specifies the open MIDI file to perform the
//      *                             conversion on.
//      *
//      * msOffset                  - Specifies the millisecond offset into the stream
//      *                             to convert.
//      *
//      * Returns the number of ticks from the start of the stream.
//      *
//      * The conversion is performed taking into ac::collection::count the file's time division and
//      * tempo map from the first track. Note that the same tick value
//      * might not be valid at a later time if the tempo track is rewritten.
//      * If the millisecond value does not exactly map to a tick value, then
//      * the tick value will be rounded down.
//      *
//      *****************************************************************************/
//      imedia::position file::MillisecsToTicks(imedia::time msOffset)
//      {
//
//         single_lock(&m_cs, true);
//
//         if(!IsOpened())
//            return 0xffffffff;
//
//         if(m_tempomap.get_size() <= 0)
//            return I32_MINIMUM;
//
//         ::music::midi::tempo_map_entry *    ptempo;
//         int32_t                      idx;
//         unsigned int                    uSMPTE;
//         unsigned int                   dwTicksPerSec;
//         imedia::position                   tickOffset;
//
//         /* SMPTE time is easy -- no tempo map, just linear conversion
//         ** Note that 30-Drop means nothing to us here since we're not
//         ** converting to a colonized format, which is where dropping
//         ** happens.
//         */
//         if (m_dwTimeDivision & 0x8000)
//         {
//            uSMPTE = -(int32_t)(char)((m_dwTimeDivision >> 8)&0xFF);
//            if (29 == uSMPTE)
//               uSMPTE = 30;
//
//            dwTicksPerSec = (unsigned int)uSMPTE * (unsigned int)(unsigned char)(m_dwTimeDivision & 0xFF);
//
//            return (int64_t) muldiv32((int32_t) msOffset, dwTicksPerSec, 1000L);
//         }
//
//         /* Walk the tempo map and find the nearest millisecond position. Linearly
//         ** calculate the rest (using MATH.ASM)
//         */
//         //ptempo = m_pTempoMap;
//         ptempo = &m_tempomap.element_at(0);
//         ASSERT(ptempo != NULL);
//
//         //for (idx = 0; idx < m_cTempoMap; idx++, ptempo++)
//         for (idx = 0; idx < m_tempomap.get_size(); idx++)
//         {
//            ptempo = &m_tempomap.element_at(idx);
//            if (msOffset < ptempo->msBase)
//               break;
//         }
//         ptempo = &m_tempomap.element_at(--idx);
//
//         /* ptempo is the tempo map entry preceding the requested tick offset.
//         */
//
//         tickOffset = ptempo->tickTempo + muldiv32((int32_t) msOffset-ptempo->msBase, 1000L * m_dwTimeDivision, ptempo->dwTempo);
//
//         if (tickOffset > m_tkLength)
//         {
//            information( "sMTT: Clipping ticks to file length!");
//            tickOffset = m_tkLength;
//         }
//
//         return tickOffset;
//      }
//
//      imedia::time  file::PositionToTime(
//         imedia::position position)
//      {
//         return TicksToMillisecs(position);
//      }
//
//      imedia::position  file::TimeToPosition(
//         imedia::time time)
//      {
//         return MillisecsToTicks(time);
//      }
//
//      void  file::PositionToTime(imedia::time_array & timea, imedia::position_array  & positiona, int_ptr tickOffset)
//      {
//         if(tickOffset < 0)
//         {
//            for(int32_t i = 0; i < positiona.get_size(); i++)
//            {
//               imedia::position tick = positiona[i];
//               imedia::position tickResult =  tick + tickOffset;
//               if(tickResult > tick)
//                  tickResult = 0;
//
//               timea.add(
//                  PositionToTime(tickResult));
//            }
//         }
//         else
//         {
//            for(int32_t i = 0; i < positiona.get_size(); i++)
//            {
//               imedia::position tick = positiona[i];
//               imedia::position tickResult =  tick + tickOffset;
//               if(tickResult < tick)
//                  tickResult = 0xFFFFFFFF;
//               timea.add(
//                  PositionToTime(
//                  tickResult));
//            }
//         }
//      }
//
//      void file::TicksToMillisecs(imedia::time_array_array * ptimeaa, imedia::position_2darray & tickaa, int_ptr tickOffset)
//      {
//         ASSERT(ptimeaa->get_size() == 0);
//         ptimeaa->set_app(get_app());
//         ptimeaa->set_size_create(ptickaa->get_size());
//         int32_t i;
//         for(i = 0; i < ptickaa->get_size(); i++)
//         {
//            TicksToMillisecs(
//               ptimeaa->element_at(i),
//               ptickaa->element_at(i),
//               tickOffset);
//         }
//
//      }
//
//      void file::PositionToTime(imedia::time_array_array  & timea, imedia::position_2darray  & positiona, int_ptr tickOffset)
//      {
//         ASSERT(timea.get_size() == 0);
//         timea.set_app(get_app());
//         timea.set_size_create(positiona.get_size());
//         int32_t i;
//         for(i = 0; i < positiona.get_size(); i++)
//         {
//            PositionToTime(
//               timea[i],
//               positiona[i],
//               tickOffset);
//         }
//
//      }
//
//      void  file::TicksToMillisecs(imedia::time_array *pMillisArray, imedia::position_array *pTickArray, int_ptr tickOffset)
//      {
//         if(tickOffset < 0)
//         {
//            for(int32_t i = 0; i < pTickArray->get_size(); i++)
//            {
//               imedia::position tick = pTickArray->operator [](i);
//               imedia::position tickResult =  tick + tickOffset;
//               if(tickResult > tick)
//                  tickResult = 0;
//
//               pMillisArray->add(
//                  (imedia::time)
//                  TicksToMillisecs(
//                  tickResult));
//            }
//         }
//         else
//         {
//            for(int32_t i = 0; i < pTickArray->get_size(); i++)
//            {
//               imedia::position tick = pTickArray->operator [](i);
//               imedia::position tickResult =  tick + tickOffset;
//               if(tickResult < tick)
//                  tickResult = 0xFFFFFFFF;
//               pMillisArray->add(
//                  (imedia::time)
//                  TicksToMillisecs(
//                  tickResult));
//            }
//         }
//      }
//
//
//      void  file::MillisecsToTicks(
//         imedia::position_array *pTickArray,
//         imedia::time_array *pMillisArray,
//         imedia::time msOffset)
//      {
//         if(msOffset < 0)
//         {
//            for(int32_t i = 0; i < pMillisArray->get_size(); i++)
//            {
//               imedia::time ms = pMillisArray->operator [](i);
//               imedia::time msResult = ms + msOffset;
//               if(msResult > ms)
//                  msResult = 0;
//               pTickArray->add(
//                  (imedia::position)
//                  MillisecsToTicks(
//                  msResult));
//            }
//         }
//         else
//         {
//            for(int32_t i = 0; i < pMillisArray->get_size(); i++)
//            {
//               imedia::time ms = pMillisArray->operator [](i);
//               imedia::time msResult = ms + msOffset;
//               if(msResult < ms)
//                  msResult = 0xffffffff;
//               pTickArray->add(
//                  (imedia::position)
//                  MillisecsToTicks(
//                  msResult));
//            }
//         }
//
//      }
//
//      void  file::TimeToPosition(
//         imedia::position_array & positiona,
//         imedia::time_array  & timea,
//         imedia::time msOffset)
//      {
//         if(msOffset < 0)
//         {
//            for(int32_t i = 0; i < timea.get_size(); i++)
//            {
//               imedia::time ms = timea[i];
//               imedia::time msResult = ms + msOffset;
//               if(msResult < 0)
//                  msResult = 0;
//               positiona.add(
//                  TimeToPosition(
//                  msResult));
//            }
//         }
//         else
//         {
//            for(int32_t i = 0; i < timea.get_size(); i++)
//            {
//               imedia::time ms = timea[i];
//               imedia::time msResult = ms + msOffset;
//               if(msResult < ms)
//                  msResult = 0xffffffff;
//               positiona.add(
//                  TimeToPosition(
//                  msResult));
//            }
//         }
//
//      }
//
//      ::e_status file::StreamEventF1(imedia::position tickDelta,
//         array < ::music::midi::event *, ::music::midi::event * > & eventptra,
//         LPMIDIHDR lpmh,
//         imedia::position tickMax,
//         unsigned int cbPrerollNomimalMax
//         )
//      {
//         __UNREFERENCED_PARAMETER(tickMax);
//         __UNREFERENCED_PARAMETER(cbPrerollNomimalMax);
//         ::e_status               smfrc;
//
//         if(eventptra.get_size() <= 0)
//         {
//            return ::success;
//         }
//
//         ::music::midi::event * pevent;
//         int32_t iSize = sizeof(midi_stream_event_header);
//         int32_t i;
//         for(i = 0; i < eventptra.get_size(); i++)
//         {
//            pevent = eventptra[i];
//            ASSERT(pevent->GetFlags() & 1);
//            iSize += (int32_t) pevent->GetParamSize();
//            iSize += sizeof(midi_stream_event_header);
//         }
//
//         m_memstorageF1.allocate(iSize);
//         LPBYTE lpbParam;
//         LPDWORD lpdwType;
//         midi_stream_event_header * pheader;
//         pheader = (midi_stream_event_header *) &m_memstorageF1.get_data()[0];
//         pheader->m_dwLength = iSize - sizeof(midi_stream_event_header);
//         pheader->m_dwType = 0;
//         iSize = sizeof(midi_stream_event_header);
//         for(i = 0; i < eventptra.get_size(); i++)
//         {
//            pevent = eventptra[i];
//            lpbParam = pevent->GetParam();
//            lpdwType = (LPDWORD) lpbParam;
//            pheader = (midi_stream_event_header *) &m_memstorageF1.get_data()[iSize];
//            pheader->m_dwLength = (unsigned int) pevent->GetParamSize();
//            pheader->m_dwType = *lpdwType;
//            memory_copy(
//               &m_memstorageF1.get_data()[iSize + sizeof(midi_stream_event_header)],
//               lpbParam,
//               pheader->m_dwLength);
//            iSize += pheader->m_dwLength + sizeof(midi_stream_event_header);
//         }
//
//         m_cbPendingUserEvent = (unsigned int) m_memstorageF1.get_size();
//         m_hpbPendingUserEvent = m_memstorageF1.get_data();
//         ASSERT(m_hpbPendingUserEvent);
//         GetFlags().unsignalize(::music::midi::file::InsertSysEx);
//         //m_dwPendingUserEvent = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((unsigned int)MEVT_COMMENT)<<24)) & 0xFF000000L);
//
//         smfrc = InsertParmData(tickDelta, lpmh);
//         if (::music::success != smfrc)
//         {
//            information( "smfInsertParmData[2] %u", (unsigned int)smfrc);
//            return ::music::translate(smfrc);
//         }
//
//         return ::music::translate(smfrc);
//
//      }
//
//
//      ::e_status file::StreamEvent(
//         imedia::position                   tickDelta,
//         ::music::midi::event *        pEvent,
//         LPMIDIHDR               lpmh,
//         imedia::position                   tickMax,
//         unsigned int                   cbPrerollNominalMax)
//      {
//         __UNREFERENCED_PARAMETER(tickMax);
//         __UNREFERENCED_PARAMETER(cbPrerollNominalMax);
//         //   informationf("file::StreamEvent tickDelta %d\n", tickDelta);
//
//         unsigned int                   dwTempo;
//         LPDWORD                 lpdw;
//         ::e_status    smfrc;
//         lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//         ASSERT(!(pEvent->GetFlags() & 1));
//         if(pEvent->GetFlags() & 1)
//         {
//            ASSERT(FALSE);
//         }
//         else if (pEvent->GetFullType() < ::music::midi::SysEx)
//         {
//            if(pEvent->GetType() == ::music::midi::ProgramChange)
//            {
//               int32_t iTrack = pEvent->GetTrack();
//               int32_t iProgramChange = pEvent->GetChB1();
//               m_keyframe.rbProgram[iTrack] = (unsigned char) iProgramChange;
//               //if(iProgramChange == 54)
//               //{
//               // pEvent->SetChB1(62);
//               //}
//            }
//            if(pEvent->GetTrack() == 9 ||
//               pEvent->GetTrack() == 15)
//            {
//               //         informationf("ReadEvents Track %d Program %d", pEvent->GetTrack(), m_keyframe.rbProgram[pEvent->GetTrack()]);
//            }
//            if((pEvent->GetType() == ::music::midi::NoteOn ||
//               pEvent->GetType() == ::music::midi::NoteOff)
//               && !((m_keyframe.rbProgram[pEvent->GetTrack()] == 0)
//               ))
//               //&& (pEvent->GetTrack() == 9 ||
//               //pEvent->GetTrack() == 15)))
//            {
//               int32_t iNotePitch = pEvent->GetNotePitch();
//               iNotePitch += m_iKeyShift;
//               while(iNotePitch >= 0x80)
//               {
//                  iNotePitch -= 12;
//               }
//               while(iNotePitch < 0)
//               {
//                  iNotePitch += 12;
//               }
//               pEvent->SetNotePitch((unsigned char) iNotePitch);
//            }
//
//            *lpdw++ = (unsigned int)tickDelta;
//            *lpdw++ = 0;
//            /**lpdw++ = (((unsigned int)MEVT_SHORTMSG)<<24) |
//               ((unsigned int)pEvent->GetFullType()) |
//               (((unsigned int)pEvent->GetChB1()) << 8) |
//               (((unsigned int)pEvent->GetChB2()) << 16);*/
//
//            lpmh->dwBytesRecorded += 3*sizeof(unsigned int);
//         }
//         else if (pEvent->GetFullType() == ::music::midi::Meta &&
//            pEvent->GetMetaType() ==  ::music::midi::MetaEOT)
//         {
//            /* These are ignoreable since smfReadNextEvent()
//            ** takes care of track merging
//            */
//         }
//         else if (::music::midi::Meta == pEvent->GetFullType() &&
//            ::music::midi::MetaTempo == pEvent->GetMetaType())
//         {
//            if (pEvent->GetParamSize() != 3)
//            {
//               information( "smfReadEvents: Corrupt tempo event");
//               return ::music::translate(::music::EInvalidFile);
//            }
//            dwTempo = (((unsigned int)pEvent->GetParam()[0])<<16)|
//               (((unsigned int)pEvent->GetParam()[1])<<8)|
//               ((unsigned int)pEvent->GetParam()[2]);
//            dwTempo = (unsigned int) ((double) dwTempo / GetTempoShiftRate());
//            //unsigned int dw = (((unsigned int)MEVT_TEMPO)<<24)| dwTempo;
//
//
//            *lpdw++ = (unsigned int)tickDelta;
//            *lpdw++ = 0;
//            //*lpdw++ = dw;
//
//            lpmh->dwBytesRecorded += 3*sizeof(unsigned int);
//         }
//         //       else if ((Meta == pEvent->GetType()) &&
//         //          (05 == pEvent->GetType()))
//         ///      {
//         /**lpdw++ = (unsigned int)pEvent->tickDelta;
//         *lpdw++ = 0;
//         *lpdw++ = MEVT_F_SHORT | MEVT_F_CALLBACK |
//         (((unsigned int)MEVT_SHORTMSG )<<24) |
//         ((unsigned int)7) |
//         (((unsigned int)13) << 8) |
//         (((unsigned int)31) << 16);
//         lpmh->dwBytesRecorded += 3*sizeof(unsigned int);*/
//         //m_cbPendingUserEvent = ((unsigned int)MEVT_SHORTMSG )<<24;
//         //         str = (char *) malloc(pEvent->cbParm + 1);
//         //         strncpy(str, (const char *) pEvent->hpbParm,  pEvent->cbParm);
//         //         str[pEvent->cbParm] = 0;
//         //         printf("%s", str);
//
//         //         m_cbPendingUserEvent = pEvent->cbParm;
//         //            m_hpbPendingUserEvent = pEvent->hpbParm;
//         //            m_fdwSMF &= ~FlagInsertSysEx;
//         //         m_dwPendingUserEvent = MEVT_F_CALLBACK |(((unsigned int)MEVT_LONGMSG )<<24);
//         //m_dwPendingUserEvent = (((unsigned int)MEVT_LONGMSG )<<24);
//         //         smfrc = smfInsertParmData(pSmf, pEvent->tickDelta, lpmh);
//         //            if (::music::success != smfrc)
//         //            {
//         //                information( "smfInsertParmData[2] %u", (unsigned int)smfrc);
//         //                return smfrc;
//         //            }
//
//         //            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//
//
//         //smfrc = smfInsertParmData(pSmf, pEvent->tickDelta, lpmh);
//         //if (::music::success != smfrc)
//         //{
//         //    information( "smfInsertParmData[2] %u", (unsigned int)smfrc);
//         //    return smfrc;
//         //}
//         //         _CrtSetReportFile(_CRT_WARN, debugFile);
//         //         _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
//
//         //_RPT0(_CRT_WARN, "Lyric:");
//         //_RPT1(_CRT_WARN, "%s", lpmh->lpData);
//         //_RPT0(_CRT_WARN, "\n");
//
//         //    }
//         else if (pEvent->GetFullType() != ::music::midi::Meta)
//            //   else
//         {
//            //            if(pEvent->GetFullType() == SysEx)
//            //         {
//            //                break;
//            //            }
//            /* Must be F0 or F7 system exclusive or FF meta
//            ** that we didn't recognize
//            */
//
//            m_cbPendingUserEvent = (unsigned int) pEvent->GetParamSize();
//            m_hpbPendingUserEvent = pEvent->GetParam();
//            GetFlags().unsignalize(::music::midi::file::InsertSysEx);
//
//            if(pEvent->GetFullType() == ::music::midi::SysExEnd)
//            {
//               //m_dwPendingUserEvent = ((unsigned int)MEVT_LONGMSG) << 24;
//            }
//            else if(pEvent->GetFullType() == ::music::midi::SysEx)
//            {
//               GetFlags().signalize(::music::midi::file::InsertSysEx);
//               ++m_cbPendingUserEvent;
//
//               /* Falling through...
//               */
//
//               //m_dwPendingUserEvent = ((unsigned int)MEVT_LONGMSG) << 24;
//            }
//
//            smfrc = InsertParmData(tickDelta, lpmh);
//            if (::music::success != smfrc)
//            {
//               information( "smfInsertParmData[2] %u", (unsigned int)smfrc);
//               return ::music::translate(smfrc);
//            }
//
//            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//         }
//         else // Meta
//         {
//            // se o meta event possuir tickDelta > 0,
//            // insere o evento no stream para que nao haja perda de sincronismo
//            if(tickDelta > 0)
//            {
//               InsertPadEvent(tickDelta, lpmh);
//               lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//            }
//         }
//         return ::music::translate(::music::success);
//      }
//
//      /******************************************************************************
//      *
//      * smfReadEvents
//      *
//      * This function reads events from a track.
//      *
//      * hSmf                      - Specifies the file to read data from.
//      *
//      * lpmh                      - Contains information about the buffer to fill.
//      *
//      * tickMax                     - Specifies a cutoff point in the stream
//      *                             beyond which events will not be read.
//      *
//      * Return@rdes
//      *   ::music::success The events were successfully read.
//      *   SMF_END_OF_TRACK There are no more events to read in this track.
//      *   ::music::EInvalidFile A disk error occured on the file.
//      *
//      * @xref <f smfWriteEvents>
//      *****************************************************************************/
//      ::e_status file::StreamRender(
//         LPMIDIHDR               lpmh,
//         imedia::position                   tickMax,
//         unsigned int                   cbPrerollNominalMax)
//      {
//
//         //    PSMF                    pSmf = (PSMF)hSmf;
//         ::e_status               smfrc;
//         ::music::midi::event * pevent;
//         LPDWORD                 lpdw;
//         //    unsigned int                   dwTempo;
//         imedia::position               tickDelta;
//         //   imedia::position               tickPosition;
//         //   imedia::position               tickMin;
//         //   imedia::position               tick;
//         int32_t                  iTrackFound;
//         //   int32_t                  i;
//         imedia::position               tickLastDelta = 0 ;
//         imedia::position                   tickOnQuarterNoteDelta = 0;
//         //   imedia::position               tickLastPositionCB = I32_MAXIMUM;
//         //CXfplayerApp *pApp = (CXfplayerApp *) &System;
//         //ASSERT(pApp != NULL);
//         //CXfplayerDoc *pDoc = (CXfplayerDoc *) pApp->GetPlayingDocument();
//         //ASSERT(pDoc != NULL);
//         //   char * str;
//         //assert(pSmf != NULL);
//         ASSERT(lpmh != NULL);
//
//         /*
//         ** read events from the track and pack them into the buffer in polymsg
//         ** format.
//         **
//         ** If a SysEx or meta would go over a buffer boundry, split it.
//         */
//         lpmh->dwBytesRecorded = 0;
//         if (m_dwPendingUserEvent)
//         {
//            smfrc = InsertParmData((imedia::position)0, lpmh);
//            if (::music::success != smfrc)
//            {
//               information( "smfInsertParmData() -> %u", (unsigned int)smfrc);
//               return smfrc;
//            }
//         }
//         //   if(m_pendingLyricEventArray.get_size() > 0)
//         //   {
//         //      smfrc = InsertLyricEvents(NULL, lpmh);
//         //        if (::music::success != smfrc)
//         //      {
//         //        information( "smfInsertParmData() -> %u", (unsigned int)smfrc);
//         //      return smfrc;
//         //}
//         //}
//
//         lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//
//         if (GetFlags().is_signalized(::music::midi::file::EndOfFile))
//         {
//            return ::music::SEndOfFile;
//         }
//         /*if(pDoc->m_iBufferingOffsetTokenIndex >= pDoc->m_TokensOffsetTicks.get_size())
//         {
//         tickNextOffsetLyricEvent = -1;
//         }
//         else
//         {
//         tickNextOffsetLyricEvent = pDoc->m_TokensOffsetTicks[pDoc->m_iBufferingOffsetTokenIndex ];
//         }
//         if(pDoc->m_iBufferingTokenIndex >= pDoc->m_TokensTicks.get_size())
//         {
//         tickNextLyricEvent = -1;
//         }
//         else
//         {
//         tickNextLyricEvent = pDoc->m_TokensTicks[pDoc->m_iBufferingTokenIndex ];
//         }*/
//         //   ::ikaraoke::lyric_events_v1 *pEventsV1;
//         while(TRUE)
//         {
//            ASSERT(lpmh->dwBytesRecorded <= lpmh->dwBufferLength);
//            if(lpmh->dwBytesRecorded > cbPrerollNominalMax)
//            {
//               break;
//            }
//
//            /* If we know ahead of time we won't have room for the
//            ** event, just break out now. We need 2 unsigned int's for the
//            ** terminator event and at least 2 unsigned int's for any
//            ** event we might store - this will allow us a full
//            ** int16_t event or the delta time and stub for a long
//            ** event to be split.
//            */
//            /*
//            now 16 DWORDS
//            */
//            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(unsigned int))
//            {
//               break;
//            }
//
//
//
//
//            //smfrc = GetNextEventTkPosition(&tickPosition, tickMax);
//
//
//            /*        if (::music::success != smfrc)
//            {
//            smfrc = GetNextEvent((event_v1 *)&event, tickMax, TRUE);
//            ASSERT(::music::success != smfrc); */
//
//            /* smfGetNextEvent doesn't set this because smfSeek uses it
//            ** as well and needs to distinguish between reaching the
//            ** seek point and reaching end-of-file.
//            **
//            ** To the ::fontopus::user, however, we present the selection between
//            ** their given tickBase and tickEnd as the entire file, therefore
//            ** we want to translate this into EOF.
//            */
//            /*if (SReachedTkMax == smfrc)
//            {
//            m_fdwSMF |= FlagEof;
//            }
//
//            information( "smfReadEvents: ReadEvents() -> %u", (unsigned int)smfrc);
//            break;
//            }*/
//            iTrackFound = -1;
//            tickLastDelta = 0;
//            /*      while(TRUE)
//            {
//            for(i = 0; i < m_eventsTracksForPositionCB.get_size(); i++)
//            {
//            pEventsV1 = m_eventsTracksForPositionCB.get_at(i);
//            if(pEventsV1->GetClassOrder() == 1)
//            {
//            while(m_ptracks->m_tkPosition >
//            (tick = pEventsV1->GetCurrentTkTokenPosition()))
//            {
//            pEventsV1->m_iCurrentToken++;
//            }
//            }
//            else
//            {
//            while(m_ptracks->m_tkPosition >
//            (tick = ((::ikaraoke::lyric_events_v2 *)pEventsV1)->GetCurrentTkNotePosition()))
//            {
//            pEventsV1->m_iCurrentNote++;
//            }
//            }
//            if(iTrackFound < 0)
//            {
//            if(tick >= 0)
//            if(tickPosition >= tick)
//            {
//            tickMin = tick;
//            iTrackFound = i;
//            }
//            }
//            else
//            {
//            if(tick >= 0)
//            if(tickPosition >= tick)
//            {
//            if(tick < tickMin)
//            {
//            tickMin = tick;
//            iTrackFound = i;
//            }
//            }
//
//            }
//            }
//            if(iTrackFound < 0)
//            break;
//            else
//            {
//            pEventsV1 = m_eventsTracksForPositionCB.get_at(iTrackFound);
//            #ifdef _DEBUG
//            //         if(pEventsV1->m_iType == 1)
//            //         {
//            //            informationf("ReadEvents pEventsV1->m_iCurrentToken = %d\n", pEventsV1->m_iCurrentToken);
//            //            informationf("ReadEvents pEventsV1->m_iType = %d\n", pEventsV1->m_iType);
//            //            informationf("ReadEvents m_ptracks->m_tkPosition = %d\n", m_ptracks->m_tkPosition);
//            //         }
//            #endif
//            tickDelta = tickMin - m_ptracks->m_tkPosition;
//            if((tickDelta - tickLastDelta) == 0)
//            {
//            pEventsV1->m_tkDelta = 0;
//            InsertLyricEvents(pEventsV1, lpmh);
//            }
//            else
//            {
//            if(m_pendingLyricEventArray.get_size() > 0)
//            {
//            smfrc = InsertLyricEvents(NULL, lpmh);
//            if(MetaPending == smfrc)
//            {
//            break;
//            }
//            else if (::music::success != smfrc)
//            {
//
//            information( "smfInsertLyricEvent %u", (unsigned int)smfrc);
//            return smfrc;
//            }
//            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//            }
//            pEventsV1->m_tkDelta = tickDelta - tickLastDelta;
//            InsertLyricEvents(pEventsV1, lpmh);
//            }
//
//            iTrackFound = -1;
//            tickLastDelta = tickDelta;
//            }
//            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(unsigned int))
//            {
//            break;
//            }
//            }*/
//            /*if(m_pendingLyricEventArray.get_size() > 0)
//            {
//            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(unsigned int))
//            {
//            break;
//            }
//            smfrc = InsertLyricEvents(NULL, lpmh);
//            if(MetaPending == smfrc)
//            {
//            break;
//            }
//            else if (::music::success != smfrc)
//            {
//            information( "smfInsertLyricEvent %u", (unsigned int)smfrc);
//            return smfrc;
//            }
//            lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//            }*/
//            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(unsigned int))
//            {
//               m_ptracks->m_tkPosition += tickDelta;
//               break;
//            }
//
//            smfrc = GetNextEvent(pevent, tickMax, TRUE);
//            if (::music::success != smfrc)
//            {
//               /* smfGetNextEvent doesn't set this because smfSeek uses it
//               ** as well and needs to distinguish between reaching the
//               ** seek point and reaching end-of-file.
//               **
//               ** To the ::fontopus::user, however, we present the selection between
//               ** their given tickBase and tickEnd as the entire file, therefore
//               ** we want to translate this into EOF.
//               */
//               if (::music::SReachedTkMax == smfrc)
//               {
//                  GetFlags().signalize(::music::midi::file::EndOfFile);
//               }
//
//               information( "smfReadEvents: ReadEvents() -> %u", (unsigned int)smfrc);
//               break;
//            }
//            ::e_status vmsr;
//            vmsr = StreamEvent(tickDelta, pevent, lpmh, tickMax, cbPrerollNominalMax);
//
//         }
//
//         return (GetFlags().is_signalized(::music::midi::file::EndOfFile)) ? ::music::SEndOfFile : ::music::success;
//      }
//
//      /******************************************************************************
//      *
//      * smfReadEvents
//      *
//      * This function reads events from a track.
//      *
//      * hSmf                      - Specifies the file to read data from.
//      *
//      * lpmh                      - Contains information about the buffer to fill.
//      *
//      * tickMax                     - Specifies a cutoff point in the stream
//      *                             beyond which events will not be read.
//      *
//      * Return@rdes
//      *   ::music::success The events were successfully read.
//      *   SMF_END_OF_TRACK There are no more events to read in this track.
//      *   ::music::EInvalidFile A disk error occured on the file.
//      *
//      * @xref <f smfWriteEvents>
//      *****************************************************************************/
//
//      ::e_status file::InsertLyricEvents(
//         ::ikaraoke::lyric_event_v1 *      pLyricEvent,
//         LPMIDIHDR         lpmh)
//      {
//         __UNREFERENCED_PARAMETER(pLyricEvent);
//         __UNREFERENCED_PARAMETER(lpmh);
//         /*    LPDWORD                 lpdw;
//         unsigned int                   dwRounded;
//         unsigned int               dwLength;
//         unsigned int               dwSize;
//         imedia::position               tickDelta;
//
//         if(pLyricEvent != NULL)
//         {
//         m_pendingLyricEventArray.add(*pLyricEvent);
//         if(pLyricEvent->GetClassOrder() == 1)
//         pLyricEvent->m_iCurrentToken++;
//         else
//         {
//         ::ikaraoke::lyric_events_v2 * pPendingLyricEventV2 =
//         (::ikaraoke::lyric_events_v2 *) pLyricEvent;
//         pPendingLyricEventV2->m_iCurrentNote++;
//         if(pPendingLyricEventV2->m_iCurrentNote <
//         pPendingLyricEventV2->m_timeaNotesPosition.get_size())
//         {
//         ::unsigned_int_array dwArray;
//         //            VERIFY(1 == pPendingLyricEventV2->GetNoteTokens(m_pPendingLyricEventV1->m_iCurrentNote, dwArray));
//         pPendingLyricEventV2->GetNoteTokens(pPendingLyricEventV2->m_iCurrentNote, dwArray);
//         if(dwArray.get_size() > 0)
//         pPendingLyricEventV2->m_iCurrentToken = dwArray.get_at(0);
//         else
//         pPendingLyricEventV2->m_iCurrentToken = -1;
//         }
//         }
//         return ::music::success;
//         }
//
//         ASSERT(lpmh != NULL);
//
//         if(m_pendingLyricEventArray.get_size() <= 0)
//         {
//         return ::music::success;
//         }
//
//         tickDelta = m_pendingLyricEventArray[0].m_tkDelta;
//
//         ASSERT(tickDelta >= 0);
//
//         /* Can't fit 4 unsigned int's? (tickDelta + stream-id + event + some data)
//         ** Can't do anything.
//         */
//         /*ASSERT(lpmh->dwBufferLength >= lpmh->dwBytesRecorded);
//         //   m_dwPendingUserEvent = MEVT_F_CALLBACK |
//         //             (((unsigned int)MEVT_LONGMSG)<<24);
//         //   m_cbPendingUserEvent = 2 * sizeof(unsigned int);
//
//         if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4 * sizeof(unsigned int))
//         {
//         if (0 == tickDelta)
//         return ::music::success;
//
//         /* If we got here with a real delta, that means smfReadEvents screwed
//         ** up calculating left space and we should flag it somehow.
//         */
//         /*        information( "Can't fit initial piece of SysEx into buffer!");
//         return ::music::EInvalidFile;
//         }
//
//         CMemFile memFile;
//         CArchive ar(&memFile, CArchive::store);
//         m_pendingLyricEventArray.Serialize(ar);
//         ar.Flush();
//         dwSize = (memFile.get_length() + sizeof(unsigned int) + 3) & (~3L);
//
//
//         lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//         dwLength = lpmh->dwBufferLength - lpmh->dwBytesRecorded - 3*sizeof(unsigned int);
//         if(dwSize > dwLength)
//         return MetaPending;
//         dwLength = dwSize;
//
//         //   unsigned int dwa = MEVT_F_CALLBACK;
//         //   unsigned int dwb = MEVT_LONGMSG;
//         //   unsigned int dwc = MEVT_F_LONG;
//         //   unsigned int dwd = MEVT_COMMENT;
//
//         ASSERT((dwSize & 3L) == 0);
//         dwRounded = dwSize;
//         //dwRounded = (dwLength + 3) & (~3L);
//
//         //tickOffset = tickDelta;
//         *lpdw++ = (unsigned int) tickDelta;
//         *lpdw++ = 0;
//         //*lpdw++ = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((unsigned int)MEVT_LONGMSG)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
//         *lpdw++ = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((unsigned int)MEVT_COMMENT)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
//         *lpdw++ = EVENT_ID_LYRIC_V1;
//
//         //   if(m_cbPendingLyricEventV1 >= (3 * sizeof(unsigned int)))
//         //   {
//         //      // offset Lyric CallBack Event Code
//         //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nType;
//         //   }
//         //   if(m_cbPendingLyricEventV1 >= (2 * sizeof(unsigned int)))
//         //   {
//         //      // offset Lyric CallBack Event Code
//         //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nTrack;
//         //   }
//         //   if(m_cbPendingLyricEventV1 >= (1 * sizeof(unsigned int)))
//         //   {
//         //      // offset Lyric CallBack Event Code
//         //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nCurrentIndex;
//         //      m_pPendingLyricEventV1->m_Union.m_pevent->m_nCurrentIndex++;
//         //   }
//         memFile.seek_to_begin();
//         memFile.read(lpdw, dwLength);
//         while(0 < m_pendingLyricEventArray.get_size())
//         {
//         m_pendingLyricEventArray.remove_at(
//         m_pendingLyricEventArray.get_size() - 1);
//         }
//         lpmh->dwBytesRecorded += 3*sizeof(unsigned int) + dwRounded;
//         */
//         return ::music::translate(::music::success);
//      }
//
//      ::e_status file::InsertPadEvent(
//         imedia::position            tickDelta,
//         LPMIDIHDR         lpmh)
//
//      {
//         LPDWORD                 lpdw;
//         unsigned int                   dwRounded;
//         unsigned int               dwLength;
//
//
//         ASSERT(tickDelta >= 0);
//         //    assert(pSmf != NULL);
//         ASSERT(lpmh != NULL);
//
//         /* Can't fit 4 unsigned int's? (tickDelta + stream-id + event + some data)
//         ** Can't do anything.
//         */
//         ASSERT(lpmh->dwBufferLength >= lpmh->dwBytesRecorded);
//         //   m_dwPendingUserEvent = MEVT_F_CALLBACK |
//         //             (((unsigned int)MEVT_LONGMSG)<<24);
//         //   m_cbPendingUserEvent = 2 * sizeof(unsigned int);
//         //   if(!m_cbPendingLyricEventV1)
//         //   if(!1)
//         //   {
//         //      return ::music::success;
//         //   }
//
//         if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4 * sizeof(unsigned int))
//         {
//            if (0 == tickDelta)
//               return ::music::success;
//
//            /* If we got here with a real delta, that means smfReadEvents screwed
//            ** up calculating left space and we should flag it somehow.
//            */
//            information( "Can't fit initial piece of SysEx into buffer!");
//            return ::music::EInvalidFile;
//         }
//
//         lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//         dwLength = lpmh->dwBufferLength - lpmh->dwBytesRecorded - 3*sizeof(unsigned int);
//         dwLength = min(dwLength, 8);
//
//         //unsigned int dwa = MEVT_F_CALLBACK;
//         //   unsigned int dwb = MEVT_LONGMSG;
//         //   unsigned int dwc = MEVT_F_LONG;
//         //   unsigned int dwd = MEVT_COMMENT;
//
//         dwRounded = (dwLength + 3) & (~3L);
//
//         //tickOffset = tickDelta;
//         *lpdw++ = (unsigned int) tickDelta;
//         *lpdw++ = 0;
//         //*lpdw++ = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((unsigned int)MEVT_LONGMSG)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
//         //   *lpdw++ = ((MEVT_F_CALLBACK | MEVT_F_LONG |(((unsigned int)MEVT_COMMENT)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
//         // xxx *lpdw++ = ((MEVT_F_LONG |(((unsigned int)MEVT_COMMENT)<<24)) & 0xFF000000L )   | (dwLength & 0x00FFFFFFL);;
//         *lpdw++ = 0;
//         *lpdw++ = EVENT_ID_PAD;
//
//         //   if(m_cbPendingLyricEventV1 >= (3 * sizeof(unsigned int)))
//         //   {
//         //      // offset Lyric CallBack Event Code
//         //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nType;
//         //   }
//         //   if(m_cbPendingLyricEventV1 >= (2 * sizeof(unsigned int)))
//         //   {
//         //      // offset Lyric CallBack Event Code
//         //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nTrack;
//         //   }
//         //   if(m_cbPendingLyricEventV1 >= (1 * sizeof(unsigned int)))
//         //   {
//         //      // offset Lyric CallBack Event Code
//         //      *lpdw++ = m_pPendingLyricEventV1->m_Union.m_pevent->m_nCurrentIndex;
//         //      m_pPendingLyricEventV1->m_Union.m_pevent->m_nCurrentIndex++;
//         //   }
//         //   m_pPendingLyricEventV1->ToData(lpdw, m_cbPendingLyricEventV1);
//         //   if (0 == (m_cbPendingLyricEventV1 -= dwLength))
//         //   {
//         //   }
//         //   else
//         //   {
//         //      int32_t i = 5;
//         //   }
//
//         lpmh->dwBytesRecorded += 3*sizeof(unsigned int) + dwRounded;
//         return ::music::success;
//      }
//      /******************************************************************************
//      *
//      * smfInsertParmData
//      *
//      * Inserts pending long data from a track into the given buffer.
//      *
//      * pSmf                      - Specifies the file to read data from.
//      *
//      * tickDelta                   - Specfices the tick delta for the data.
//      *
//      * lpmh                      - Contains information about the buffer to fill.
//      *
//      * Returns
//      *   ::music::success The events were successfully read.
//      *   ::music::EInvalidFile A disk error occured on the file.
//      *
//      * Fills as much data as will fit while leaving room for the buffer
//      * terminator.
//      *
//      * If the long data is depleted, resets m_dwPendingUserEvent so
//      * that the next event may be read.
//      *
//      *****************************************************************************/
//      ::e_status file::InsertParmData(
//         imedia::position                   tickDelta,
//         LPMIDIHDR               lpmh)
//      {
//         unsigned int                   dwLength;
//         unsigned int                   dwRounded;
//         LPDWORD                 lpdw;
//
//         //    assert(pSmf != NULL);
//         ASSERT(lpmh != NULL);
//
//         /* Can't fit 4 unsigned int's? (tickDelta + stream-id + event + some data)
//         ** Can't do anything.
//         */
//         ASSERT(lpmh->dwBufferLength >= lpmh->dwBytesRecorded);
//
//         if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(unsigned int))
//         {
//            if (0 == tickDelta)
//               return ::music::success;
//
//            /* If we got here with a real delta, that means smfReadEvents screwed
//            ** up calculating left space and we should flag it somehow.
//            */
//            information( "Can't fit initial piece of SysEx into buffer!");
//            return ::music::EInvalidFile;
//         }
//
//         lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//
//         dwLength = lpmh->dwBufferLength - lpmh->dwBytesRecorded - 3*sizeof(unsigned int);
//         dwLength = min(dwLength, m_cbPendingUserEvent);
//
//         *lpdw++ = (unsigned int)tickDelta;
//         *lpdw++ = 0L;
//         *lpdw++ = (m_dwPendingUserEvent & 0xFF000000L) | (dwLength & 0x00FFFFFFL);
//
//         dwRounded = (dwLength + 3) & (~3L);
//
//         if (GetFlags().is_signalized(::music::midi::file::InsertSysEx))
//         {
//            LPBYTE lpb = (LPBYTE) lpdw;
//            *lpb++ = ::music::midi::SysEx;
//            GetFlags().unsignalize(::music::midi::file::InsertSysEx);
//            --dwLength;
//            --m_cbPendingUserEvent;
//            lpdw = (LPDWORD) lpb;
//         }
//
//         if (dwLength & 0x80000000L)
//         {
//            information( "dwLength %08lX  dwBytesRecorded %08lX  dwBufferLength %08lX", dwLength, lpmh->dwBytesRecorded, lpmh->dwBufferLength);
//            information( "cbPendingUserEvent %08lX  dwPendingUserEvent %08lX dwRounded %08lX", m_cbPendingUserEvent, m_dwPendingUserEvent, dwRounded);
//            information( "offset into MIDI image %08lX", (unsigned int)(m_hpbPendingUserEvent - GetImage()));
//            information( "!hmemcpy is about to fault");
//         }
//
//         memory_copy(lpdw, m_hpbPendingUserEvent, dwLength);
//         if (0 == (m_cbPendingUserEvent -= dwLength))
//            m_dwPendingUserEvent = 0;
//
//         lpmh->dwBytesRecorded += 3*sizeof(unsigned int) + dwRounded;
//
//         return ::music::success;
//      }
//
//      /******************************************************************************
//      *
//      * smfSeek
//      *
//      * This function moves the file pointer within a track
//      * and gets the state of the track at the aaa_primitive_new position. It returns a buffer of
//      * state information which can be used to set up to play from the aaa_primitive_new position.
//      *
//      * hSmf                      - Handle of file to seek within
//      *
//      * tickPosition                - The position to seek to in the track.
//      *
//      * lpmh                      - A buffer to contain the state information.
//      *
//      * Returns
//      *   ::music::success | The state was successfully read.
//      *   SMF_END_OF_TRACK | The pointer was moved to end of track and no state
//      *     information was returned.
//      *   SMF_INVALID_PARM | The given handle or buffer was invalid.
//      *   ::music::ENoMemory | There was insufficient primitive::memory in the given buffer to
//      *     contain all of the state data.
//      *
//      * The state information in the buffer includes patch changes, tempo changes,
//      * time signature, key signature,
//      * and controller information. Only the most recent of these paramters before
//      * the current position will be stored. The state buffer will be returned
//      * in polymsg format so that it may be directly transmitted over the MIDI
//      * bus to bring the state up to date.
//      *
//      * The buffer is mean to be sent as a streaming buffer; i.e. immediately
//      * followed by the first data buffer. If the requested tick position
//      * does not exist in the file, the last event in the buffer
//      * will be a MEVT_NOP with a delta time calculated to make sure that
//      * the next stream event plays at the proper time.
//      *
//      * The meta events (tempo, time signature, key signature) will be the
//      * first events in the buffer if they exist.
//      *
//      * Use smfGetStateMaxSize to determine the maximum size of the state
//      * information buffer. State information that will not fit into the given
//      * buffer will be lost.
//      *
//      * On return, the dwBytesRecorded field of lpmh will contain the
//      * actual number of bytes stored in the buffer.
//      *
//      *****************************************************************************/
//
//
//      ::e_status file::seek(
//         imedia::position                   tickPosition,
//         LPMIDIHDR               lpmh)
//      {
//         ::e_status     smfrc;
//         ::music::midi::event *        pevent;
//         LPDWORD                 lpdw;
//         unsigned char                    bEvent;
//         unsigned int                    idx;
//         unsigned int                    idxChannel;
//         unsigned int                    idxController;
//
//         _SyncSeek(tickPosition);
//
//         memset(&m_keyframe, 0, sizeof(m_keyframe));
//
//
//
//         memset(&m_keyframe, 0xFF, sizeof(m_keyframe));
//         memset(&m_keyframe.rbProgram, 0x00, sizeof(m_keyframe.rbProgram));
//
//         m_ptracks->m_tkPosition = 0;
//         GetFlags().unsignalize(::music::midi::file::EndOfFile);
//         m_ptracks->GetFlags().unsignalize(::music::midi::file::EndOfFile);
//
//         m_ptracks->seek_begin();
//         //for (ptrk = m_rTracks, idxTrack = m_dwTracks; idxTrack--; ptrk++)
//
//         while (::music::success == (smfrc = GetNextEvent(pevent, tickPosition, FALSE)))
//         {
//
//            if (::music::midi::Meta == (bEvent = pevent->GetFullType()))
//            {
//               if (pevent->GetMetaType() == ::music::midi::MetaTempo)
//               {
//                  if (pevent->GetParamSize() != sizeof(m_keyframe.rbTempo))
//                     return ::music::EInvalidFile;
//
//                  memory_copy((unsigned char *)m_keyframe.rbTempo, pevent->GetParam(), pevent->GetParamSize());
//               }
//            }
//            if((bEvent & 0xF0) == ::music::midi::ProgramChange)
//            {
//               m_keyframe.rbProgram[bEvent & 0x0F] = pevent->GetChB1();
//            }
//            else if((bEvent & 0xF0) == ::music::midi::ControlChange)
//            {
//               m_keyframe.rbControl[(((unsigned short)bEvent & 0x0F)*120) + pevent->GetChB1()] =
//                  pevent->GetChB2();
//            }
//         }
//
//         if (::music::SReachedTkMax != smfrc)
//         {
//            return smfrc;
//         }
//
//         /* Build lpmh from keyframe
//         */
//         lpmh->dwBytesRecorded = 0;
//         lpdw = (LPDWORD)lpmh->lpData;
//
//         /* Tempo change event?
//         */
//         if (KF_EMPTY != m_keyframe.rbTempo[0] ||
//            KF_EMPTY != m_keyframe.rbTempo[1] ||
//            KF_EMPTY != m_keyframe.rbTempo[2])
//         {
//            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(unsigned int))
//               return ::music::ENoMemory;
//
//            *lpdw++ = 0;
//            *lpdw++ = 0;
//            //      *lpdw++ = (((unsigned int)m_keyframe.rbTempo[2])<<16)|
//            //                (((unsigned int)m_keyframe.rbTempo[1])<<8)|
//            //            ((unsigned int)m_keyframe.rbTempo[0])|
//            //            (((unsigned int)MEVT_SHORTMSG) << 24);
//            //
//            //      *lpdw++ = (((unsigned int)m_keyframe.rbTempo[0])<<16)|
//            //                (((unsigned int)m_keyframe.rbTempo[1])<<8)|
//            //             ((unsigned int)m_keyframe.rbTempo[2])|
//            //            (((unsigned int)MEVT_SHORTMSG) << 24);
//
//            unsigned int dwTempo =   (((unsigned int)m_keyframe.rbTempo[0])<<16)|
//               (((unsigned int)m_keyframe.rbTempo[1])<<8)|
//               ((unsigned int)m_keyframe.rbTempo[2]);
//            dwTempo = (unsigned int) ((double) dwTempo / GetTempoShiftRate());
//// xxx            unsigned int dw = (((unsigned int)MEVT_TEMPO)<<24)| dwTempo;
//
//
//            //*lpdw++ = (unsigned int)pEvent->_GetDelta();
//            //*lpdw++ = 0;
//            //*lpdw++ = dw;
//            //*lpdw++ = dw;
//
//            //*lpdw++ = (((unsigned int)m_keyframe.rbTempo[0])<<16)|
//            //        (((unsigned int)m_keyframe.rbTempo[1])<<8)|
//            //      ((unsigned int)m_keyframe.rbTempo[2])|
//            //    (((unsigned int)MEVT_TEMPO) << 24);
//            //        *lpdw++ = (((unsigned int)m_keyframe.rbTempo[2])<<16)|
//            //                (((unsigned int)m_keyframe.rbTempo[1])<<8)|
//            //              ((unsigned int)m_keyframe.rbTempo[0])|
//            ///            (((unsigned int)MEVT_TEMPO) << 24);
//
//            lpmh->dwBytesRecorded += 3*sizeof(unsigned int);
//         }
//
//         /* Program change events?
//         */
//         for (idx = 0; idx < 16; idx++)
//         {
//            if (KF_EMPTY != m_keyframe.rbProgram[idx])
//            {
//               if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(unsigned int))
//                  return ::music::ENoMemory;
//
//               *lpdw++ = 0;
//               *lpdw++ = 0;
//// xxx               *lpdw++ = (((unsigned int)MEVT_SHORTMSG) << 24)      |
//      //            ((unsigned int)::music::midi::ProgramChange)         |
//        //          ((unsigned int)idx)                        |
//          //        (((unsigned int)m_keyframe.rbProgram[idx]) << 8);
//
//               lpmh->dwBytesRecorded += 3*sizeof(unsigned int);
//            }
//         }
//
//         /* Controller events?
//         */
//         idx = 0;
//         for (idxChannel = 0; idxChannel < 16; idxChannel++)
//         {
//            for (idxController = 0; idxController < 120; idxController++)
//            {
//               if (KF_EMPTY != m_keyframe.rbControl[idx])
//               {
//                  if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(unsigned int))
//                     return ::music::ENoMemory;
//
//                  *lpdw++ = 0;
//                  *lpdw++ = 0;
//                  // xxx *lpdw++ = (((unsigned int)MEVT_SHORTMSG << 24)     |
//                     //((unsigned int)::music::midi::ControlChange)       |
//                     //((unsigned int)idxChannel)               |
//                     //(((unsigned int)idxController) << 8)     |
//                     //(((unsigned int)m_keyframe.rbControl[idx]) << 16)); */
//
//
//                  lpmh->dwBytesRecorded += 3*sizeof(unsigned int);
//               }
//
//               idx++;
//            }
//         }
//
//         /* Force all tracks to be at tickPosition. We are guaranteed that
//         ** all tracks will be past the event immediately preceding tickPosition;
//         ** this will force correct delta-ticks to be generated so that events
//         ** on all tracks will line up properly on a seek into the middle of the
//         ** file.
//         */
//         // ^^^^ This cause problems... tracks are already positioned...
//         // changing track position make all the song envents be shifted
//         // irregularly...
//         //    for (ptrk = m_rTracks, idxTrack = m_dwTracks; idxTrack--; ptrk++)
//         //   for (idxTrack = m_dwTracks; idxTrack--;)
//         //  {
//         //   ptrk = m_tracks[idxTrack];
//         //  ptrk->tickPosition        = tickPosition;
//         //}
//         //return seek(tickPosition);
//
//         return ::music::success;
//      }
//
//      ::e_status file::seek(
//         imedia::position                   tickPosition)
//      {
//         ::e_status  smfrc;
//         ::music::midi::event *     pevent;
//
//
//         m_ptracks->m_tkPosition = 0;
//         GetFlags().unsignalize(::music::midi::file::EndOfFile);
//         m_ptracks->GetFlags().unsignalize(::music::midi::file::EndOfFile);
//
//         m_ptracks->seek_begin();
//
//         while(::music::success == (smfrc = GetNextEvent(pevent, tickPosition, FALSE)));
//
//         if (::music::SReachedTkMax != smfrc)
//         {
//            return smfrc;
//         }
//
//         return ::music::success;
//      }
//
//      /******************************************************************************
//      *
//      * smfBuildFileIndex
//      *
//      * Preliminary parsing of a MIDI file.
//      *
//      * ppSmf                     - Pointer to a returned SMF structure if the
//      *                             file is successfully parsed.
//      *
//      * Returns
//      *   ::music::success The events were successfully read.
//      *   ::music::ENoMemory Out of primitive::memory to build key frames.
//      *   ::music::EInvalidFile A disk or parse error occured on the file.
//      *
//      * This function validates the format of and existing MIDI or RMI file
//      * and builds the handle structure which will refer to it for theytrhf b
//      * lifetime of the instance.
//      *
//      * The file header information will be read and verified, and
//      * smfBuildTrackIndices will be called on every existing track
//      * to build keyframes and validate the track format.
//      *
//      *****************************************************************************/
//      ::e_status file::Build()
//      {
//         ::e_status        smfrc = ::music::success;
//         UNALIGNED CHUNKHDR *       pCh;
//         int32_t                        iLeft;
//         int32_t                        iLeftInitial;
//         unsigned char *                     hpbImage;
//         unsigned char *                     hpbImageInitial;
//         unsigned int                      dwLength;
//         //   track_base *            pTrk = NULL;
//        ::music::midi::track *                pTrkMidi;
//         ::music::midi::event              event;
//         unsigned int                        cbLength;
//         int32_t                        iTrack;
//
//         GetTracks().remove_all();
//
//         /* MIDI data image is already in hpbImage (already extracted from
//         ** RIFF header if necessary).
//         */
//
//         /* Validate MIDI header
//         */
//         iLeft    = GetImageSize();
//         hpbImage = GetImage();
//
//         if (iLeft < sizeof(CHUNKHDR))
//            return ::music::EInvalidFile;
//
//         m_pMThd = (CHUNKHDR *)hpbImage;
//
//         iLeft   -= sizeof(CHUNKHDR);
//         hpbImage += sizeof(CHUNKHDR);
//
//         if (m_pMThd->fourccType != FOURCC_MThd)
//            return ::music::EInvalidFile;
//
//         dwLength = DWORDSWAP(m_pMThd->dwLength);
//         if (dwLength < sizeof(MIDIFILEHDR) || dwLength > (unsigned int) iLeft)
//            return ::music::EInvalidFile;
//
//         m_pFileHeader = (MIDIFILEHDR *)hpbImage;
//
//         iLeft    -= dwLength;
//         hpbImage += dwLength;
//
//         m_dwFormat       = (unsigned int)(WORDSWAP(m_pFileHeader->wFormat));
//         m_dwTracks       = (unsigned int)(WORDSWAP(m_pFileHeader->wTracks));
//         m_dwTimeDivision = (unsigned int)(WORDSWAP(m_pFileHeader->wDivision));
//
//         /*
//         ** We've successfully parsed the header. Now try to build the track
//         ** index.
//         **
//         ** We only check out the track header chunk here; the track will be
//         ** preparsed after we do a quick integretiy check.
//         */
//
//         iLeftInitial      = iLeft;
//         hpbImageInitial   = hpbImage;
//         iTrack            = 0;
//
//         for (int32_t i = 0; iLeft > 0; i++)
//         {
//            if (iLeft < sizeof(CHUNKHDR))
//               break;
//
//            pCh = (CHUNKHDR *)hpbImage;
//
//            iLeft       -= sizeof(CHUNKHDR);
//            hpbImage    += sizeof(CHUNKHDR);
//            cbLength    =  DWORDSWAP(pCh->dwLength);
//
//            if(cbLength > (unsigned int) iLeft)
//               break;
//
//
//            if (pCh->fourccType == FOURCC_MTrk
//               || pCh->fourccType == FOURCC_XFIH
//               || pCh->fourccType == FOURCC_XFKM)
//            {
//               pTrkMidi                      = m_ptracks->CreateTrack();
//               pTrkMidi->m_iIndex            = iTrack++;
//               pTrkMidi->m_offsetEventImage          = (unsigned int)(hpbImage - GetImage());
//               pTrkMidi->m_smti.m_cbLength   = cbLength;
//
//               pTrkMidi->Initialize(m_ptracks);
//            }
//
//            iLeft       -= cbLength;
//            hpbImage    += cbLength;
//
//         }
//
//         if((unsigned int) m_ptracks->GetTrackCount() < m_dwTracks)
//         {
//            return ::music::EInvalidFile;
//         }
//
//
//         /*   iLeft             = iLeftInitial;
//         hpbImage          = hpbImageInitial;
//
//         for (i = 0; iLeft > 0; i++)
//         {
//         if (iLeft < sizeof(CHUNKHDR))
//         break;
//
//         pCh = (CHUNKHDR *)hpbImage;
//
//         iLeft       -= sizeof(CHUNKHDR);
//         hpbImage    += sizeof(CHUNKHDR);
//         cbLength    =  DWORDSWAP(pCh->dwLength);
//
//         if(pCh->fourccType == FOURCC_XFIH ||
//         pCh->fourccType == FOURCC_XFKM)
//         {
//         pTrkMidi                      = m_ptracks->CreateTrack();
//         pTrkMidi->m_iIndex            = iTrack++;
//         pTrkMidi->m_offsetEventImage          = (unsigned int)(hpbImage - GetImage());
//         pTrkMidi->m_smti.m_cbLength   = cbLength;
//
//         if (pTrkMidi->m_smti.m_cbLength > (unsigned int) iLeft)
//         {
//         informationf("Track longer than file!");
//         return ::music::EInvalidFile;
//         }
//
//         pTrkMidi->Initialize(m_ptracks);
//         }
//
//         iLeft       -= cbLength;
//         hpbImage    += cbLength;
//
//         }*/
//
//         m_dwTracks = (unsigned int) m_ptracks->GetTrackCount();
//
//
//         /* File looks OK. Now preparse, doing the following:
//         ** (1) Build tempo map so we can convert to/from ticks quickly
//         ** (2) Determine actual tick length of file
//         ** (3) Validate all events in all tracks
//         */
//         m_ptracks->m_tkPosition = 0;
//         GetFlags().unsignalize(::music::midi::file::EndOfFile);
//         GetFlags().signalize(::music::midi::file::DisablePlayLevel1Operations);
//
////         m_ptracks->SetAutoAllocation(false);
//         if(m_iOpenMode != ::music::midi::file::OpenForHeaders)
//         {
//            m_ptracks->ToWorkStorage();
//         }
//
//         if(m_iOpenMode == ::music::midi::file::OpenForPlaying)
//         {
//            smfrc = CreateTempoMap();
//         }
//
//         if(m_iOpenMode != ::music::midi::file::OpenForHeaders
//            && smfrc == ::music::success)
//         {
//            smfrc = CalcTkLength();
//         }
//
//         //GetFlags().unsignalize(DisablePlayLevel1Operations);
//
//         return smfrc;
//      }
//
//
//      ::e_status file::GetNextEvent(
//         ::music::midi::event *&  pevent,
//         imedia::position             tickMax,
//         bool               bTkMaxInclusive)
//      {
//         if (GetFlags().is_signalized(::music::midi::file::EndOfFile))
//         {
//            return ::music::SEndOfFile;
//         }
//         if(!GetFlags().is_signalized(::music::midi::file::DisablePlayLevel1Operations))
//         {
//            if(m_mepaImmediate.get_size() > 0)
//            {
//               ::music::midi::event * peventImmediate = m_mepaImmediate.element_at(0);
//               *pevent = *peventImmediate;
//               delete peventImmediate;
//               m_mepaImmediate.remove_at(0);
//               return ::music::success;
//            }
//            if(m_mepaOnQuarterNote.get_size() > 0)
//            {
//               imedia::position tickMod = m_ptracks->m_tkPosition  % WORDSWAP(m_pFileHeader->wDivision);
//               imedia::position tickQuarterNote;
//               if(tickMod == 0)
//               {
//                  tickQuarterNote = m_ptracks->m_tkPosition;
//               }
//               else
//               {
//                  tickQuarterNote = m_ptracks->m_tkPosition + WORDSWAP(m_pFileHeader->wDivision) - tickMod;
//               }
//               imedia::position tickPosition;
//               ::e_status smfrc = GetNextEventTkPosition(&tickPosition, tickMax);
//               if(smfrc == ::music::SEndOfFile)
//                  GetFlags().signalize(::music::midi::file::EndOfFile);
//               if(tickPosition > tickQuarterNote)
//               {
//                  m_ptracks->m_tkPosition  = tickQuarterNote;
//                  *pevent = *m_mepaOnQuarterNote.element_at(0);
//                  delete m_mepaOnQuarterNote.element_at(0);
//                  m_mepaOnQuarterNote.remove_at(0);
//                  return ::music::success;
//               }
//            }
//         }
//
//         ::e_status smfrc   = m_ptracks->GetNextEvent(
//            pevent,
//            tickMax,
//            bTkMaxInclusive,
//            false,
//            false);
//
//         if(!GetFlags().is_signalized(::music::midi::file::DisablePlayLevel1Operations))
//         {
//            if(pevent->GetType() == ::music::midi::NoteOn &&
//               pevent->GetNoteVelocity() != 0)
//            {
//               m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack())++;
//               m_ptracks->m_iaLevel.element_at(pevent->GetTrack())
//                  = pevent->GetNoteVelocity();
//            }
//            else if((pevent->GetType() == ::music::midi::NoteOn &&
//               pevent->GetNoteVelocity() == 0) ||
//               pevent->GetType() == ::music::midi::NoteOff)
//            {
//               int32_t iCount = m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack());
//               if(iCount > 0)
//                  iCount--;
//               m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack()) =
//                  iCount;
//               if(iCount == 0)
//                  m_ptracks->m_iaLevel.element_at(pevent->GetTrack())
//                  = 0;
//            }
//         }
//         if(smfrc == ::music::SEndOfFile)
//            GetFlags().signalize(::music::midi::file::EndOfFile);
//         return smfrc;
//
//
//
//      }
//
//      ::e_status file::GetNextEventTkPosition(
//         imedia::position * pTkPosition,
//         imedia::position tickMax)
//      {
//
//         if (GetFlags().is_signalized(::music::midi::file::EndOfFile))
//         {
//            return ::music::SEndOfFile;
//         }
//
//         return m_ptracks->GetNextEventTkPosition(
//            pTkPosition,
//            tickMax);
//      }
//
//
//
//
//      /*
//      *   mysmfGetTrackEventData
//      *
//      *
//      *
//      *
//      ****/
//      /*unsigned int mysmfGetTrackEventData(
//         sp(::music::midi::file::buffer) pSmf,
//         ::music::midi::event *      pEvent,
//         unsigned char *            pData[])
//      {
//         unsigned int               len;
//         unsigned char *                  hpbImage;
//         unsigned int index;
//
//         ASSERT(pSmf != NULL);
//         ASSERT(pEvent != NULL);
//
//         len = pEvent->m_iParamSize;
//
//         *pData = (uchar *) LocalAlloc(LPTR,len);
//
//         hpbImage = pEvent->m_pParam;
//
//         for(index = 0; len; index++)
//         {
//            *pData[index] = *hpbImage++;
//         }
//
//         return len;
//      }
//*/
//
//
//      ::e_status file::WorkMergeTracks()
//      {
//         ::music::midi::track * ptrack;
//         for(int32_t i = 0; i < m_ptracks->GetMidiTrackCount(); i++)
//         {
//            ptrack = m_ptracks->MidiTrackAt(i);
//            ptrack->FromWorkTrack(false);
//         }
//         return MergeTracks();
//      }
//
//
//
//      int32_t file::CalcMelodyTrack(::music::midi::events **ppEvents, imedia::position_array & ticka)
//      {
//         //    return -1;
//         return m_ptracks->CalcMelodyTrack(ppEvents, pTicks, m_pFileHeader->wFormat);
//      }
//
//      int32_t file::WorkCalcMelodyTrack(
//        ::music::midi::events ** ppEvents,
//         imedia::position_array & positiona,
//         ::int_array & iaTokenLine)
//      {
//         return m_ptracks->WorkCalcMelodyTrack(
//            ppEvents,
//            positiona,
//            iaTokenLine,
//            m_pFileHeader->wFormat);
//      }
//
//      ::e_status file::SaveFile(const char * lpcFilePath)
//      {
///*         HMMIO                   hmmio = (HMMIO)NULL;
//         //    ::e_status               smfrc = ::music::success;
//         MMIOINFO                mmioinfo;
//
//         ASSERT(lpcFilePath != NULL);
//
//         char * lpFilePath = _tcsdup(lpcFilePath);
//
//         /* Verify that the file can be opened or created
//         */
//         /*memset(&mmioinfo, 0, sizeof(mmioinfo));
//
//         hmmio = mmioOpen(lpFilePath, &mmioinfo, MMIO_WRITE |MMIO_ALLOCBUF);
//         if ((HMMIO)NULL == hmmio)
//         {
//            information(_T( "smfOpenFile: mmioOpen failed!"));
//            return ::music::ESaveFailed;
//         }
//
//         if(mmioWrite(hmmio, (char _huge* ) GetImage(), GetImageSize()) != (int32_t) GetImageSize())
//         {
//            information(_T( "smfOpenFile: mmioOpen failed!"));
//            return ::music::ESaveFailed;
//         }*/
//
//         return ::music::success;
//      }
//
//      ::e_status file::SaveFile(::file::stream_buffer &ar)
//      {
//         ar.write(GetImage(), GetImageSize());
//         return ::music::success;
//      }
//
//      bool file::IsTune1000File()
//      {
//         return m_ptracks->IsTune1000File();
//      }
//
//      bool file::IsSoftKaraokeFile(bool bWork, string_array * pstra)
//      {
//         return m_ptracks->IsSoftKaraokeFile(bWork, pstra);
//      }
//
//      /*file::e_status file::DeleteEvent(::music::midi::event *pEvent)
//      {
//      file::e_status   smfrc;
//      if(pEvent->GetImage() > 0)
//      {
//      if(pEvent->_GetDelta() != 0)
//      {
//      // if this event being deleted has non-zero delta,
//      // the previous event must have it delta corrected;
//      event_v1   previousEvent;
//      if(file::music::success != (smfrc = GetPreviousEvent(
//      &previousEvent,
//      pEvent)))
//      {
//      return smfrc;
//      }
//      if(file::music::success != (smfrc = ChangeEventDelta(
//      &previousEvent,
//      previouspevent->m_tkDelta + pEvent->_GetDelta())))
//      {
//      return smfrc;
//      }
//      }
//      track * pTrack = m_ptracks->GetEventTrack(pEvent);
//      if(pTrack == NULL)
//      return TrackNotFound;
//      pTrack->m_smti.m_cbLength -= pEvent->GetImageSize();
//      pTrack->WriteHeaderLength();
//      m_cbImage -= pEvent->GetImageSize();
//      memory_transfer(
//      pEvent->GetImage(),
//      pEvent->GetImage() + pEvent->GetImageSize(),
//      m_cbImage - (pEvent->GetImage() - m_hpbImage) - pEvent->GetImageSize());
//      if(file::music::success != (smfrc = BuildIndex()))
//      {
//      return smfrc;
//      }
//
//      return file::music::success;
//      }
//      else
//      {
//      return file::music::success;
//      }
//
//      } */
//
//      ::e_status file::GetPreviousEvent(
//         ::music::midi::event  * pPreviousEvent,
//         ::music::midi::event  * pEvent)
//      {
//         __UNREFERENCED_PARAMETER(pPreviousEvent);
//
//         ::e_status               smfrc;
//         ::music::midi::event *           pevent;
//         ::music::midi::event *           peventPrevious;
//
//         m_ptracks->m_tkPosition = 0;
//         GetFlags().unsignalize(::music::midi::file::EndOfFile);
//         m_ptracks->GetFlags().unsignalize(::music::midi::file::EndOfFile);
//
//         m_ptracks->seek_begin();
//         //for (ptrk = m_rTracks, idxTrack = m_dwTracks; idxTrack--; ptrk++)
//
//         while(::music::success == (smfrc = GetNextEvent(pevent, pEvent->GetPosition(), TRUE)))
//         {
//            if(pevent->GetImage() == pEvent->GetImage())
//            {
//               pEvent->operator =(*peventPrevious);
//               return ::music::success;
//            }
//            peventPrevious = pevent;
//         }
//
//         if (::music::SReachedTkMax != smfrc)
//         {
//            return smfrc;
//         }
//
//         return ::music::success;
//
//      }
//
//      ::e_status file::ReplaceSameDeltaEvent(::music::midi::event &eventNew)
//      {
//         int32_t iCurrentTrack = m_ptracks->m_iCurrentTrack;
//         if(iCurrentTrack < 0)
//            return ::music::EError;
//         ::music::midi::track * pTrkMidi = (::music::midi::track *) m_ptracks->TrackAt(iCurrentTrack);
//         ASSERT(pTrkMidi->GetType() == ::music::midi::track_base::TypeMidi);
//         int32_t iCurrentEvent = pTrkMidi->GetCurrentEvent();
//         if(iCurrentEvent < 0)
//            return ::music::EError;
//
//         ::music::midi::track_v8 & trackWork = pTrkMidi->GetWorkTrack();
//
//         ::music::midi::event & event = trackWork.EventAt(iCurrentEvent);
//
//         event = eventNew;
//         return ::music::success;
//      }
//      /*::e_status ReplaceSameDeltaEvent(::music::midi::event *pEventOld, CMidiEventV007 *pEventNew)
//      {
//      ASSERT(pEventOld->_GetDeltaTicks() == pEventNew->_GetDeltaTicks());
//      ASSERT(pEventNew->IsAutoAllocated());
//      track * pTrack = m_ptracks->GetEventTrack(pEventOld);
//      if(pTrack == NULL)
//      return TrackNotFound;
//      unsigned char * hpbImage = pEventOld->GetImage();
//      unsigned char * hpbFileImage = m_hpbImage;
//      if(pEventOld->GetImageSize() != pEventNew->m_cbImage)
//      {
//      int32_t iAddUp = pEventNew->m_cbImage - pEventOld->GetImageSize();
//      pEventNew->m_pTrack = pTrack;
//      allocate_add_up(iAddUp);
//      hpbImage += hpbFileImage - m_hpbImage;
//      pTrack->m_smti.m_cbLength += iAddUp;
//      pTrack->WriteHeaderLength();
//      memory_transfer(
//      hpbImage + iAddUp,
//      hpbImage,
//      m_cbImage - (hpbImage - m_hpbImage));
//      m_cbImage += iAddUp;
//      }
//      memory_copy(hpbImage, pEventNew->GetImage(), pEventNew->m_cbImage);
//
//      WriteHeader();
//
//      return ::music::success;*/
//
//      /*   ASSERT(pEventOld->_GetDeltaTicks() == pEventNew->_GetDeltaTicks());
//      ASSERT(pEventNew->IsAutoAllocated());
//      track * pTrack = m_ptracks->GetEventTrack(pEventOld);
//      if(pTrack == NULL)
//      return TrackNotFound;
//      unsigned char * hpbImage = pEventOld->GetImage();
//      unsigned char * hpbFileImage = m_hpbImage;
//      if(pEventOld->GetImageSize() != pEventNew->m_cbImage)
//      {
//      int32_t iAddUp = pEventNew->m_cbImage - pEventOld->GetImageSize();
//      pEventNew->m_pTrack = pTrack;
//      allocate_add_up(iAddUp);
//      hpbImage += hpbFileImage - m_hpbImage;
//      pTrack->m_smti.m_cbLength += iAddUp;
//      pTrack->WriteHeaderLength();
//      memory_transfer(
//      hpbImage + iAddUp,
//      hpbImage,
//      m_cbImage - (hpbImage - m_hpbImage));
//      m_cbImage += iAddUp;
//      }
//      memory_copy(hpbImage, pEventNew->GetImage(), pEventNew->m_cbImage);
//
//      WriteHeader();
//
//      return ::music::success;
//
//      }*/
//
//      /*::e_status ChangeEventDelta(::music::midi::event *pEvent, imedia::position tickNewDelta)
//      {
//      ::e_status smfrc;
//      if(pEvent->_GetDelta() != tickNewDelta)
//      {
//      track * pTrack = m_ptracks->GetEventTrack(pEvent);
//      if(pTrack == NULL)
//      return TrackNotFound;
//      unsigned char buffer[256];
//      unsigned int dwSetUsed = ::music::midi::event::SetVDWord(buffer, 256, tickNewDelta);
//      imedia::position tickOldDelta;
//      unsigned int dwGetUsed = ::music::midi::event::GetVDWord(pEvent->GetImage(), 256, &tickOldDelta);
//      ASSERT(tickOldDelta == pEvent->_GetDelta());
//      unsigned char * hpbImage = pEvent->GetImage();
//      if(dwSetUsed != dwGetUsed)
//      {
//      int32_t iAddUp = dwSetUsed - dwGetUsed;
//      if(iAddUp > 0)
//      {
//      if(!allocate(m_cbImage + iAddUp))
//      {
//      informationf("DeleteEvent No Memory for deleting\n");
//      return ::music::ENoMemory;
//      }
//      }
//      pTrack->m_smti.m_cbLength += iAddUp;
//      pTrack->WriteHeaderLength();
//      memory_transfer(
//      hpbImage + iAddUp,
//      hpbImage,
//      m_cbImage - (hpbImage - m_hpbImage));
//      m_cbImage += iAddUp;
//      if(::music::success != (smfrc = BuildIndex()))
//      {
//      return smfrc;
//      }
//      }
//      ::music::midi::event::SetVDWord(hpbImage, dwSetUsed, tickNewDelta);
//      return ::music::success;
//      }
//      else
//      return ::music::success;
//
//      }*/
//
//      ::e_status file::WriteHeader(MIDIFILEHDR * lpmfh)
//      {
//         m_pMThd = (CHUNKHDR *) GetImage();
//         //   unsigned int dwLength = m_cbImage - sizeof(CHUNKHDR);
//         //  m_pMThd->dwLength = DWORDSWAP(dwLength);
//         m_pMThd->fourccType = FOURCC_MThd;
//         m_pMThd->dwLength = DWORDSWAP(sizeof(MIDIFILEHDR));
//         m_pFileHeader = (LPMIDIFILEHDR) (GetImage() + sizeof(CHUNKHDR));
//         memory_copy(m_pFileHeader, lpmfh, sizeof(MIDIFILEHDR));
//         return ::music::success;
//      }
//
//
//
//      bool file::IsXFFile()
//      {
//         m_ptracks->seek_begin();
//         return m_ptracks->IsXFFile();
//      }
//
//      int32_t file::SetKeyShift(int32_t iKeyShift)
//      {
//         m_iKeyShift = iKeyShift;
//         return true;
//      }
//
//      int32_t file::GetKeyShift()
//      {
//         return m_iKeyShift;
//      }
//
//
//      void file::FromWorkStorage()
//      {
//         m_ptracks->FromWorkStorage();
//
//      }
//      void file::ToWorkStorage()
//      {
//         m_ptracks->ToWorkStorage();
//      }
//
//      ::e_status file::SetTempoShift(int32_t iTempoShift)
//      {
//         m_iTempoShift = iTempoShift;
//         return ::music::success;
//      }
//
//      int32_t file::GetTempoShift()
//      {
//         return m_iTempoShift;
//      }
//
//      double file::GetTempoShiftRate()
//      {
//         return exp((double) m_iTempoShift * log(3.0) / 10.0);
//      }
//
//
//      ::music::midi::tempo_map_entry * file::GetTempoMapEntry(const imedia::position & tick)
//      {
//         int32_t idx;
//         for (idx = 0; idx < m_tempomap.get_size(); idx++)
//         {
//            ::music::midi::tempo_map_entry & tempo = m_tempomap.element_at(idx);
//            if((int32_t) tick < (int32_t) tempo.tickTempo)
//               break;
//         }
//         if(idx <= 0)
//            return NULL;
//         else
//            return &m_tempomap.element_at(idx - 1);
//      }
//
//      // event must have space to put event data
//      ::e_status file::GetTempoEvent(::music::midi::event &event)
//      {
//         ::music::midi::tempo_map_entry * pmtme = GetTempoMapEntry(m_ptracks->m_tkPosition);
//         if(pmtme != NULL)
//         {
//            double dTempo;
//            dTempo = pmtme->dwTempo;
//            //dTempo = dTempo / GetTempoShiftRate();
//            union
//            {
//               unsigned int   dw;
//               unsigned char    ba[4];
//            } uA, uB;
//            uA.dw = (unsigned int) dTempo;
//            uB.ba[0] = uA.ba[2];
//            uB.ba[1] = uA.ba[1];
//            uB.ba[2] = uA.ba[0];
//
//            event.SetFullType(::music::midi::Meta);
//            event.SetMetaType(::music::midi::MetaTempo);
//            event.SetParam(&uB.dw, 3);
//         }
//         return ::music::success;
//
//      }
//
//      ::e_status file::InsertTempoEvent()
//      {
//         ::music::midi::tempo_map_entry * pmtme = GetTempoMapEntry(m_ptracks->m_tkPosition);
//         if(pmtme != NULL)
//         {
//            ::music::midi::event * pevent = aaa_primitive_new ::music::midi::event();
//            GetTempoEvent(*pevent);
//            m_mepaOnQuarterNote.add(pevent);
//         }
//         return ::music::success;
//      }
//
//      ::e_status file::Format0()
//      {
//         MIDIFILEHDR fileHdr;
//
//         fileHdr.wFormat = WORDSWAP(0);
//         fileHdr.wDivision = m_pFileHeader->wDivision ;
//         fileHdr.wTracks = WORDSWAP(1) ;
//
//         ::music::midi::track * pTrackUnion = aaa_primitive_new ::music::midi::track(get_app());
//         pTrackUnion->Initialize(m_ptracks);
//         m_ptracks->CompactTracks(*pTrackUnion, true, true);
//
//         m_ptracks->RemoveAllMidiTracks();
//         ::music::midi::track * ptrack = m_ptracks->CreateTrack();
//         *ptrack = *pTrackUnion;
//
//
//         ::e_status smfrc;
//         if(::success != (smfrc = MergeTracks()))
//            return smfrc;
//
//         WriteHeader(&fileHdr);
//
//         if(::success != (smfrc = Build()))
//            return smfrc;
//
//         return ::music::success;
//      }
//
//      LPBYTE file::GetImage()
//      {
//         return get_data();
//      }
//
//      unsigned int file::GetImageSize()
//      {
//         return (unsigned int) this->get_size();
//      }
//
//      void file::OnStop()
//      {
//         m_ptracks->OnStop();
//      }
//
//
//      ::e_status file::ImmediatePutTempoChange()
//      {
//         ::music::midi::event * pevent = aaa_primitive_new ::music::midi::event;
//         GetTempoEvent(*pevent);
//         m_mepaImmediate.add(pevent);
//         return ::success;
//      }
//
//
//
//      ::e_status file::WorkStreamRender(
//         LPMIDIHDR               lpmh,
//         imedia::position                   tickMax,
//         unsigned int                   cbPrerollNominalMax)
//      {
//         ::e_status       smfrc;
//         ::music::midi::event *           pevent;
//         array < ::music::midi::event *, ::music::midi::event * > eventptraPositionCB;
//         LPDWORD                    lpdw;
//         imedia::position                        tickDelta;
//         imedia::position                        tickLastDelta = 0 ;
//         imedia::position                      tickOnQuarterNoteDelta = 0;
//         //   imedia::position                        tickLastPosition;
//         imedia::position      tickPosition;
//         imedia::position      tickPositionF1;
//         imedia::position &    tickLastPosition = m_positionLastWorkRender;
//         ASSERT(lpmh != NULL);
//
//         /////////////////////////////////////////////////////////////////////////////
//         // read events from the track and pack them into the buffer in polymsg
//         // format.
//         //
//         // If a SysEx or meta would go over a buffer boundry, split it.
//         /////////////////////////////////////////////////////////////////////////////
//
//         lpmh->dwBytesRecorded = 0;
//         if(m_dwPendingUserEvent)
//         {
//            smfrc = InsertParmData((imedia::position)0, lpmh);
//            if(::music::success != smfrc)
//            {
//               information( "smfInsertParmData() -> %u", (unsigned int)smfrc);
//               return smfrc;
//            }
//         }
//
//         lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//
//         if (GetFlags().is_signalized(::music::midi::file::EndOfFile))
//         {
//            return ::music::SEndOfFile;
//         }
//
//         if(tickLastPosition > GetPosition())
//         {
//            tickLastPosition = GetPosition();
//         }
//         while(true)
//         {
//            ASSERT(lpmh->dwBytesRecorded <= lpmh->dwBufferLength);
//            if(lpmh->dwBytesRecorded > cbPrerollNominalMax
//               && eventptraPositionCB.get_size() <= 0)
//            {
//               break;
//            }
//
//            // If we know ahead of time we won't have room for the
//            // event, just break out now. We need 2 unsigned int's for the
//            // terminator event and at least 2 unsigned int's for any
//            // event we might store - this will allow us a full
//            // int16_t event or the delta time and stub for a long
//            // event to be split.
//            //
//            //
//
//
//            // now 16 DWORDS
//            //
//            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(unsigned int))
//            {
//               break;
//            }
//
//            tickLastDelta = 0;
//
//            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 4*sizeof(unsigned int))
//            {
//               //         m_ptracks->m_tkPosition += tickDelta;
//               break;
//            }
//
//            smfrc = WorkGetNextEvent(pevent, tickMax, TRUE);
//            if (::music::success != smfrc)
//            {
//               // smfGetNextEvent doesn't set this because smfSeek uses it
//               // as well and needs to distinguish between reaching the
//               // seek point and reaching end-of-file.
//               //
//               // To the ::fontopus::user, however, we present the selection between
//               // their given tickBase and tickEnd as the entire file, therefore
//               // we want to translate this into EOF.
//               //
//               return smfrc;
//
//               information( "smfReadEvents: ReadEvents() -> %u", (unsigned int)smfrc);
//               break;
//            }
//
//            ASSERT(GetPosition() >= tickLastPosition);
//
//            tickPosition  = GetPosition();
//            tickDelta     = tickPosition - tickLastPosition;
//
//            // The position CB events are grouped in a single position CB
//            // event after other type of simultaneous events.
//            // The {if block} change the order of simultaneous events.
//            // position CB events ( pevent->GetFlags() & 1 )
//            // are streamed together in a single position CB event, through
//            // StreamEventF1 member function.
//            // These position CB events are put after any other kind of event
//            // that have the same position.
//            // The order of the non PositionCB events are not altered.
//
//            if(pevent->GetFlags() & 1)
//            {
//               if(eventptraPositionCB.get_size() <= 0)
//               {
//                  // This is the first PositionCB event
//                  // at the F1 position.
//                  eventptraPositionCB.add(pevent);
//                  tickPositionF1   = tickPosition;
//               }
//               else if(tickPosition == tickPositionF1)
//               {
//                  // This is another PositionCB event
//                  // at the F1 position.
//                  eventptraPositionCB.add(pevent);
//               }
//               else
//               {
//                  // This is another PositionCB event
//                  // at another position.
//
//                  ASSERT(tickPositionF1 >= tickLastPosition);
//
//                  tickDelta = tickPositionF1 - tickLastPosition;
//                  StreamEventF1(tickDelta, eventptraPositionCB, lpmh, tickMax, cbPrerollNominalMax);
//                  tickLastPosition = tickPositionF1;
//                  eventptraPositionCB.remove_all();
//
//                  eventptraPositionCB.add(pevent);
//                  tickPositionF1   = tickPosition;
//               }
//            }
//            else
//            {
//               if(eventptraPositionCB.get_size() > 0)
//               {
//                  if(pevent->GetPosition() != eventptraPositionCB[0]->GetPosition())
//                  {
//                     ASSERT(tickPositionF1 >= tickLastPosition);
//
//                     tickDelta = tickPositionF1 - tickLastPosition;
//                     StreamEventF1(tickDelta, eventptraPositionCB, lpmh, tickMax, cbPrerollNominalMax);
//                     tickDelta = tickPosition - tickPositionF1;
//                     eventptraPositionCB.remove_all();
//                  }
//                  else
//                  {
//                     // The event to be streamed in the following StreamEvent function
//                     // has the same position of the eventptraPositionCB events.
//                     // So, when these eventptraPositionCB events are streamed,
//                     // the event delta will be zero.
//                     tickDelta = tickPosition - tickPositionF1;
//                     tickPositionF1   = tickPosition;
//                  }
//               }
//               /*         if(pevent->get_type() == NoteOn)
//               {
//               informationf("WorkStreamRender: NoteOn     position %d Delta %d Track %d\n",
//               m_ptracks->GetPosition(),
//               tickDelta,
//               pevent->GetTrack());
//               }
//               else
//               {
//               informationf("WorkStreamRender: Type Other position %d Delta %d\n",
//               m_ptracks->GetPosition(),
//               tickDelta);
//               }*/
//
//               StreamEvent(tickDelta, pevent, lpmh, tickMax, cbPrerollNominalMax);
//               tickLastPosition = tickPosition;
//            }
//
//         }
//
//         return (GetFlags().is_signalized(::music::midi::file::EndOfFile)) ? ::music::SEndOfFile : ::music::success;
//      }
//
//      ::e_status file::WorkGetNextRawEvent(
//         ::music::midi::event *&      pevent,
//         imedia::position                tickMax,
//         bool                  bTkMaxInclusive)
//      {
//         if(GetFlags().is_signalized(::music::midi::file::EndOfFile))
//         {
//            return ::music::SEndOfFile;
//         }
//         ::e_status smfrc = m_ptracks->WorkGetNextRawEvent(
//            pevent,
//            tickMax,
//            bTkMaxInclusive,
//            false);
//         if(smfrc == ::music::SEndOfFile)
//         {
//            GetFlags().signalize(::music::midi::file::EndOfFile);
//         }
//         return smfrc;
//      }
//
//      ::e_status file::WorkGetNextRawMidiEvent(
//         ::music::midi::event *&      pevent,
//         imedia::position                tickMax,
//         bool                  bTkMaxInclusive)
//      {
//         if(GetFlags().is_signalized(::music::midi::file::EndOfFile))
//         {
//            return ::music::SEndOfFile;
//         }
//         ::e_status smfrc = m_ptracks->WorkGetNextRawMidiEvent(
//            pevent,
//            tickMax,
//            bTkMaxInclusive,
//            false);
//         if(smfrc == ::music::SEndOfFile)
//         {
//            GetFlags().signalize(::music::midi::file::EndOfFile);
//         }
//         return smfrc;
//      }
//
//      ::e_status file::WorkGetNextEvent(
//         ::music::midi::event *&      pevent,
//         imedia::position                tickMax,
//         bool                  bTkMaxInclusive)
//      {
//         if (GetFlags().is_signalized(::music::midi::file::EndOfFile))
//         {
//            return ::music::SEndOfFile;
//         }
//         // XXX
//         /*   if(!GetFlags().is_signalized(DisablePlayLevel1Operations))
//         {
//         if(m_mepaImmediate.get_size() > 0)
//         {
//         event_v5 * peventImmediate = m_mepaImmediate.element_at(0);
//         pevent = peventImmediate;
//         delete peventImmediate;
//         m_mepaImmediate.remove_at(0);
//         return ::music::success;
//         }
//         if(m_mepaOnQuarterNote.get_size() > 0)
//         {
//         imedia::position tickMod = m_ptracks->m_tkPosition  % WORDSWAP(m_pFileHeader->wDivision);
//         imedia::position tickQuarterNote;
//         if(tickMod == 0)
//         {
//         tickQuarterNote = m_ptracks->m_tkPosition;
//         }
//         else
//         {
//         tickQuarterNote = m_ptracks->m_tkPosition + WORDSWAP(m_pFileHeader->wDivision) - tickMod;
//         }
//         imedia::position tickPosition;
//         ::e_status smfrc = GetNextEventTkPosition(&tickPosition, tickMax);
//         if(smfrc == ::music::SEndOfFile)
//         GetFlags().signalize(::music::midi::file::EndOfFile);
//         if(tickPosition > tickQuarterNote)
//         {
//         m_ptracks->m_tkPosition  = tickQuarterNote;
//         pevent = m_mepaOnQuarterNote.element_at(0);
//         delete m_mepaOnQuarterNote.element_at(0);
//         m_mepaOnQuarterNote.remove_at(0);
//         return ::music::success;
//         }
//         }
//         }*/
//
//         ::e_status smfrc;
//         while(true)
//         {
//            smfrc   = m_ptracks->WorkGetNextEvent(
//               pevent,
//               tickMax,
//               bTkMaxInclusive,
//               false);
//            if(smfrc != ::music::success)
//            {
//               break;
//            }
//            //      if(GetFlags().is_signalized(DisablePlayLevel1Operations))
//            //    {
//            //     break;
//            //      }
//            if(GetFlags().is_signalized(::music::midi::file::DisableMute))
//            {
//               break;
//            }
//            else
//            {
//               if(pevent->GetType() == ::music::midi::NoteOn
//                  && pevent->GetNoteVelocity() > 0
//                  && m_iaMuteTrack.contains(pevent->GetTrack()))
//               {
//                  ASSERT(TRUE);
//               }
//               else
//               {
//                  break;
//               }
//            }
//         }
//
//         if(!GetFlags().is_signalized(::music::midi::file::DisablePlayLevel1Operations))
//         {
//            if(pevent->GetType() == ::music::midi::NoteOn &&
//               pevent->GetNoteVelocity() != 0)
//            {
//               m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack())++;
//               m_ptracks->m_iaLevel.element_at(pevent->GetTrack())
//                  = pevent->GetNoteVelocity();
//            }
//            else if((pevent->GetType() == ::music::midi::NoteOn &&
//               pevent->GetNoteVelocity() == 0) ||
//               pevent->GetType() == ::music::midi::NoteOff)
//            {
//               int32_t iCount = m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack());
//               if(iCount > 0)
//                  iCount--;
//               m_ptracks->m_iaNoteOn.element_at(pevent->GetTrack()) =
//                  iCount;
//               if(iCount == 0)
//                  m_ptracks->m_iaLevel.element_at(pevent->GetTrack())
//                  = 0;
//            }
//         }
//         if(smfrc == ::music::SEndOfFile)
//         {
//            GetFlags().signalize(::music::midi::file::EndOfFile);
//         }
//         return smfrc;
//
//
//
//      }
//
//
//      ::e_status file::WorkSeek(
//         imedia::position                   tickPosition,
//         LPMIDIHDR               lpmh)
//      {
//
//         ::e_status        smfrc;
//         ::music::midi::event *           pevent;
//         LPDWORD                    lpdw;
//         unsigned char                       bEvent;
//         unsigned int                       idx;
//         unsigned int                       idxChannel;
//         unsigned int                       idxController;
//
//         _SyncSeek(tickPosition);
//
//         m_positionLastWorkRender.set_maximum();
//
//         memset(&m_keyframe, 0xFF, sizeof(m_keyframe));
//         memset(&m_keyframe.rbProgram, 0x00, sizeof(m_keyframe.rbProgram));
//
//         m_ptracks->m_tkPosition = 0;
//         GetFlags().unsignalize(::music::midi::file::EndOfFile);
//         m_ptracks->GetFlags().unsignalize(::music::midi::file::EndOfFile);
//
//         m_ptracks->WorkSeekBegin();
//
//         while (::music::success == (smfrc = WorkGetNextEvent(pevent, tickPosition, FALSE)))
//         {
//            if (::music::midi::Meta == (bEvent = pevent->GetFullType()))
//            {
//               if (pevent->GetMetaType() == ::music::midi::MetaTempo)
//               {
//                  if (pevent->GetParamSize() != sizeof(m_keyframe.rbTempo))
//                     return ::music::EInvalidFile;
//
//                  memory_copy((unsigned char *)m_keyframe.rbTempo, pevent->GetParam(), pevent->GetParamSize());
//               }
//            }
//            if((bEvent & 0xF0) == ::music::midi::ProgramChange)
//            {
//               m_keyframe.rbProgram[bEvent & 0x0F] = pevent->GetChB1();
//            }
//            else if((bEvent & 0xF0) == ::music::midi::ControlChange)
//            {
//               m_keyframe.rbControl[(((unsigned short)bEvent & 0x0F)*120) + pevent->GetChB1()] =
//                  pevent->GetChB2();
//            }
//         }
//
//         if (::music::SReachedTkMax != smfrc)
//         {
//            return smfrc;
//         }
//
//         /* Build lpmh from keyframe
//         */
//         //lpmh->dwBytesRecorded = 0;
//         lpdw = (LPDWORD)(lpmh->lpData + lpmh->dwBytesRecorded);
//
//         /* Tempo change event?
//         */
//         if (KF_EMPTY != m_keyframe.rbTempo[0] ||
//            KF_EMPTY != m_keyframe.rbTempo[1] ||
//            KF_EMPTY != m_keyframe.rbTempo[2])
//         {
//            if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(unsigned int))
//               return ::music::ENoMemory;
//
//            *lpdw++ = 0;
//            *lpdw++ = 0;
//            unsigned int dwTempo =   (((unsigned int)m_keyframe.rbTempo[0])<<16)|
//               (((unsigned int)m_keyframe.rbTempo[1])<<8)|
//               ((unsigned int)m_keyframe.rbTempo[2]);
//            dwTempo = (unsigned int) ((double) dwTempo / GetTempoShiftRate());
//// xxx            unsigned int dw = (((unsigned int)MEVT_TEMPO)<<24)| dwTempo;
//
//   // xxx         *lpdw++ = dw;
//
//            lpmh->dwBytesRecorded += 3*sizeof(unsigned int);
//         }
//
//         /* Program change events?
//         */
//         for (idx = 0; idx < 16; idx++)
//         {
//            if (KF_EMPTY != m_keyframe.rbProgram[idx])
//            {
//               if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(unsigned int))
//                  return ::music::ENoMemory;
//
//               *lpdw++ = 0;
//               *lpdw++ = 0;
////               *lpdw++ = (((unsigned int)MEVT_SHORTMSG) << 24)      |
//  //                ((unsigned int)::music::midi::ProgramChange)         |
//    //              ((unsigned int)idx)                        |
//      //            (((unsigned int)m_keyframe.rbProgram[idx]) << 8);
//
//               lpmh->dwBytesRecorded += 3*sizeof(unsigned int);
//            }
//         }
//
//         /* Controller events?
//         */
//         idx = 0;
//         for (idxChannel = 0; idxChannel < 16; idxChannel++)
//         {
//            for (idxController = 0; idxController < 120; idxController++)
//            {
//               if (KF_EMPTY != m_keyframe.rbControl[idx])
//               {
//                  if (lpmh->dwBufferLength - lpmh->dwBytesRecorded < 3*sizeof(unsigned int))
//                     return ::music::ENoMemory;
//
//                  *lpdw++ = 0;
//                  *lpdw++ = 0;
///*                  *lpdw++ = (((unsigned int)MEVT_SHORTMSG << 24)     |
//                     ((unsigned int)::music::midi::ControlChange)       |
//                     ((unsigned int)idxChannel)               |
//                     (((unsigned int)idxController) << 8)     |
//                     (((unsigned int)m_keyframe.rbControl[idx]) << 16));*/
//
//
//                  lpmh->dwBytesRecorded += 3*sizeof(unsigned int);
//               }
//
//               idx++;
//            }
//         }
//
//         /* Force all tracks to be at tickPosition. We are guaranteed that
//         ** all tracks will be past the event immediately preceding tickPosition;
//         ** this will force correct delta-ticks to be generated so that events
//         ** on all tracks will line up properly on a seek into the middle of the
//         ** file.
//         */
//         // ^^^^ This cause problems... tracks are already positioned...
//         // changing track position make all the song envents be shifted
//         // irregularly...
//         //    for (ptrk = m_rTracks, idxTrack = m_dwTracks; idxTrack--; ptrk++)
//         //   for (idxTrack = m_dwTracks; idxTrack--;)
//         //  {
//         //   ptrk = m_tracks[idxTrack];
//         //  ptrk->tickPosition        = tickPosition;
//         //}
//         //return seek(tickPosition);
//
//         return ::music::success;
//      }
//
//      ::e_status file::CreateTempoMap()
//      {
//         bool bFirst = true;
//         ::music::midi::tempo_map_entry tempo;
//         ::e_status smfrc;
//         ::music::midi::event * pevent;
//         m_ptracks->WorkSeekBegin();
//         while (::music::success
//            == (smfrc = WorkGetNextRawMidiEvent(pevent, MAX_TICKS, TRUE)))
//         {
//            if (::music::midi::Meta == pevent->GetFullType() &&
//               ::music::midi::MetaTempo == pevent->GetMetaType() &&
//               (pevent->GetFlags() != 1))
//            {
//               if (3 != pevent->GetParamSize())
//               {
//                  return ::music::EInvalidFile;
//               }
//
//               if (bFirst && m_ptracks->m_tkPosition != 0)
//               {
//                  /* Inserting first event and the absolute time is zero.
//                  ** Use defaults of 500,000 uSec/qn from MIDI spec
//                  */
//
//                  tempo.tickTempo = 0;
//                  tempo.msBase  = 0;
//                  tempo.dwTempo = ::music::midi::DefaultTempo;
//                  m_tempomap.add(tempo);
//
//
//                  bFirst = false;
//               }
//
//               tempo.tickTempo = m_ptracks->m_tkPosition;
//
//               if (bFirst)
//                  tempo.msBase = 0;
//               else
//               {
//                  ::music::midi::tempo_map_entry * pLastTempo = &m_tempomap.element_at(m_tempomap.get_size() - 1) ;
//                  /* NOTE: Better not be here unless we're q/n format!
//                  */
//                  //                ptempo->msBase = (ptempo-1)->msBase +
//                  //                               muldiv32(ptempo->tickTempo-((ptempo-1)->tickTempo),
//                  //                                      (ptempo-1)->dwTempo,
//                  //                                    1000L*m_dwTimeDivision);
//                  tempo.msBase = (pLastTempo)->msBase +
//                     muldiv32((int32_t) (tempo.tickTempo-((pLastTempo)->tickTempo)),
//                     (pLastTempo)->dwTempo,
//                     1000L * m_dwTimeDivision);
//               }
//
//               tempo.dwTempo = (((unsigned int)pevent->GetParam()[0])<<16) |
//                  (((unsigned int)pevent->GetParam()[1])<<8) |
//                  ((unsigned int)pevent->GetParam()[2]);
//
//               m_tempomap.add(tempo);
//            }
//         }
//         if (0 == m_tempomap.get_size())
//         {
//            informationf("File contains no tempo map! Insert default tempo.");
//
//            ::music::midi::tempo_map_entry * ptempo = &m_tempomap.add_new();
//            ptempo->tickTempo = 0;
//            ptempo->msBase  = 0;
//            //      ptempo->dwTempo = DefaultTempo;
//            ptempo->dwTempo = ::music::midi::DefaultTempo;
//         }
//
//         return ::music::success;
//
//      }
//
//      ::e_status file::CalcTkLength()
//      {
//         m_tkLength = m_ptracks->CalcTkLength();
//         return ::music::success;
//
//      }
//
//      ::e_status file::WorkSeekBegin()
//      {
//         m_ptracks->WorkSeekBegin();
//         GetFlags().unsignalize(::music::midi::file::EndOfFile);
//         m_tkLastDelta = 0;
//         m_positionLastWorkRender.set_maximum();
//         return ::music::success;
//      }
//
//      void file::MuteTrack(int32_t iIndex, bool bMute)
//      {
//         if(bMute)
//         {
//            m_iaMuteTrack.add_unique(iIndex);
//         }
//         else
//         {
//            m_iaMuteTrack.remove(iIndex);
//         }
//      }
//
//      void file::MuteAll(bool bMute, int32_t iExcludeTrack)
//      {
//         for(int32_t i = 0; i < 16; i++)
//         {
//            if(i == iExcludeTrack)
//            {
//               MuteTrack(i, !bMute);
//            }
//            else
//            {
//               MuteTrack(i, bMute);
//            }
//         }
//      }
//
//      bool file::IsTrackMute(int32_t iIndex)
//      {
//         return m_iaMuteTrack.contains(iIndex);
//      }
//
//
//      bool file::IsNull()
//      {
//         if(this == NULL)
//            return true;
//         return false;
//      }
//
//      void file::WorkSeekEnd()
//      {
//         GetTracks().WorkSeekEnd();
//      }
//
//      void file::AttachSeekSync(::ikaraoke::events_tracks_v1 *ptracksv1)
//      {
//         m_evtrkv1ptraSeek.add(ptracksv1);
//      }
//
//      void file::_SyncSeek(imedia::position tickPosition)
//      {
//         for(int32_t i = 0; i < m_evtrkv1ptraSeek.get_size(); i++)
//         {
//            _SyncSeek(tickPosition, m_evtrkv1ptraSeek.element_at(i));
//         }
//      }
//
//      void file::_SyncSeek(
//         imedia::position tickPosition,
//         ::ikaraoke::events_tracks_v1 *ptracksv1)
//      {
//         ASSERT(ptracksv1 != NULL);
//         ::ikaraoke::lyric_events_v1 * pEventsV1;
//         ::ikaraoke::lyric_events_v2 * pEventsV2;
//
//         ::collection::index iTokenIndex = -1;
//         ::collection::index iNoteIndex = -1;
//         ::collection::index i;
//         for(i = 0; i < ptracksv1->get_size(); i++)
//         {
//            pEventsV1 =   ptracksv1->get_at(i);
//            if(pEventsV1->GetClassOrder() == 2)
//            {
//               pEventsV2 = (::ikaraoke::lyric_events_v2 *) pEventsV1;
//               iNoteIndex = pEventsV2->GetPositionNote(tickPosition);
//               if(iNoteIndex >= 0)
//               {
//                  break;
//               }
//               iTokenIndex = pEventsV2->GetPositionToken(tickPosition);
//               if(iTokenIndex >= 0)
//               {
//                  break;
//               }
//            }
//         }
//         if(iTokenIndex < 0 && iNoteIndex < 0)
//         {
//            iTokenIndex = 0;
//            iNoteIndex = 0;
//         }
//         else if(iNoteIndex < 0)
//         {
//            iNoteIndex = pEventsV2->GetTokenFirstNote(iTokenIndex);
//            if(iNoteIndex < 0)
//               iNoteIndex = 0;
//         }
//         else if(iTokenIndex < 0)
//         {
//            iTokenIndex = pEventsV2->GetNoteFirstToken(iNoteIndex);
//            if(iTokenIndex < 0)
//               iTokenIndex = 0;
//         }
//         for(i = 0; i < ptracksv1->get_size(); i++)
//         {
//            ptracksv1->get_at(i)->m_iCurrentToken = iTokenIndex;
//            ptracksv1->get_at(i)->m_iCurrentNote = iNoteIndex;
//         }
//      }
//
//
//
//      imedia::position file::GetPosition()
//      {
//         return m_ptracks->GetPosition();
//      }
//
//      int32_t file::GetDivision()
//      {
//         return WORDSWAP(m_pFileHeader->wDivision);
//      }
//
//      int32_t file::GetFormat()
//      {
//         return WORDSWAP(m_pFileHeader->wFormat);
//      }
//
//
//      ::e_status file::WorkWriteXFTracks(
//         string_array &  tokena,
//         imedia::position_array & positiona,
//         ::music::xf::info_header & xfinfoheader)
//      {
//         ::music::midi::tracks & tracka = GetTracks();
//
//         while(tracka.GetTrackCount() > 1)
//         {
//            tracka.remove_at(1);
//         }
//
//
//
//         ::music::midi::track & track = *(class ::music::midi::track *) tracka.TrackAt(0);
//         if(!track.IsXFFile())
//         {
//            unsigned char XFVERSIONID[] = {
//               0x43,  // YAMAHA ID
//               0x7B,  //
//               0x00,  //
//               0x58,  // X
//               0x46,  // F
//               0x30,  // 0
//               0x32,   // 2
//               0x00,
//               0x11};
//            track.seek_begin();
//            ::music::midi::event eventV008;
//            eventV008.SetPosition(0);
//            eventV008.SetFullType(::music::midi::Meta);
//            eventV008.SetMetaType(::music::midi::MetaSeqSpecific);
//            eventV008.SetParam(XFVERSIONID, sizeof(XFVERSIONID));
//            track.GetWorkTrack().insert_at(0, eventV008);
//         }
//
//         ::music::xf::info_header xfInfoHeader;
//
//         class ::music::midi::track * pmiditrack = tracka.CreateTrack(FOURCC_XFIH);
//
//         pmiditrack->WorkWriteXFInfoHeader(
//            NULL,
//            &xfinfoheader,
//            NULL);
//         pmiditrack->GetEvent().SetFullType(::music::midi::Meta);
//         pmiditrack->GetEvent().SetMetaType(::music::midi::MetaEOT);
//         pmiditrack->GetEvent().SetParam(NULL, 0);
//         pmiditrack->GetEvent().SetDelta(0);
//         pmiditrack->WorkWriteEvent();
//
//         pmiditrack = tracka.CreateTrack(FOURCC_XFIH);
//
//         pmiditrack->WriteXFLyricTrack(tokena, positiona, "L1");
//
//         return ::music::success;
//      }
//
//
//      bool file::IsOpened()
//      {
//         return GetFlags().is_signalized(::music::midi::file::Opened);
//      }
//
//      void file::SetOpened(bool bOpened)
//      {
//         if(bOpened)
//         {
//            GetFlags().signalize(::music::midi::file::Opened);
//         }
//         else
//         {
//            GetFlags().unsignalize(::music::midi::file::Opened);
//         }
//      }


      } // namespace alsa


   } // namespace midi


} // namespace music









