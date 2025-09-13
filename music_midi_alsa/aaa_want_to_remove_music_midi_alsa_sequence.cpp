#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace alsa
      {


         sequence::sequence(::particle * pparticle) :
            ::object(pparticle),
            ::music::midi::object(pparticle),
            ::ikaraoke::karaoke(pparticle),
            ::music::midi::sequence(pparticle)
         {

            m_bPlay = false;
            m_pseq = NULL;

            m_buffera.Initialize(16, 4 * 1024, 0);
            m_midicallbackdata.m_psequence = this;

            m_iClient = 129;
            //m_iClient = 16;
            m_iPort = 1;


         }

         sequence::~sequence()
         {

            CloseFile();

            //::aura::del(m_pmidiout);

         }


         /***************************************************************************
         *
         * seqAllocBuffers
         *
         * allocate buffers for this instance.
         *
         * pSeq                      - The sequencer instance to allocate buffers for.
         *
         * Returns
         *   ::success If the operation was successful.
         *
         *   MCIERR_OUT_OF_MEMORY  If there is insufficient primitive::memory for
         *     the requested number and size of buffers.
         *
         * seqAllocBuffers allocates playback buffers based on the
         * cbBuffer and cBuffer fields of pSeq. cbBuffer specifies the
         * number of bytes in each buffer, and cBuffer specifies the
         * number of buffers to allocate.
         *
         * seqAllocBuffers must be called before any other sequencer call
         * on a newly allocted SEQUENCE structure. It must be paired with
         * a call to seqFreeBuffers, which should be the last call made
         * before the SEQUENCE structure is discarded.
         *
         ***************************************************************************/
         ::e_status sequence::AllocBuffers()
         {
            ASSERT(FALSE);
            /*
            unsigned int                   dwEachBufferSize;
            unsigned int                   dwAlloc;
            unsigned int                    i;
            LPBYTE                  lpbWork;

            //    assert(pSeq != NULL);

            set_state(e_state_no_file);
            m_lpmhFree  = NULL;
            m_lpbAlloc  = NULL;
            //    m_hSmf      = (HSMF)NULL;

            // First make sure we can allocate the buffers they asked for
            //
            dwEachBufferSize = sizeof(MIDIHDR) + (unsigned int)(m_cbBuffer);
            dwAlloc          = dwEachBufferSize * (unsigned int)(m_cBuffer);

            //m_lpbAlloc = (uchar *) GlobalAllocPtr(GMEM_MOVEABLE|GMEM_SHARE, dwAlloc);
            m_lpbAlloc = (uchar *) HeapAlloc(GetProcessHeap(), 0, dwAlloc);
            if (NULL == m_lpbAlloc)
            return MCIERR_OUT_OF_MEMORY;

            // Initialize all MIDIHDR's and throw them into a free list
            //
            m_lpmhFree = NULL;

            lpbWork = m_lpbAlloc;
            for (i=0; i < m_cBuffer; i++)
            {
            ((LPMIDIHDR)lpbWork)->lpNext            = m_lpmhFree;

            ((LPMIDIHDR)lpbWork)->lpData            = (char *) (lpbWork + sizeof(MIDIHDR));
            ((LPMIDIHDR)lpbWork)->dwBufferLength    = m_cbBuffer;
            ((LPMIDIHDR)lpbWork)->dwBytesRecorded   = 0;
            ((LPMIDIHDR)lpbWork)->dwUser            = (unsigned int)(unsigned int)this;
            ((LPMIDIHDR)lpbWork)->dwFlags           = 0;

            m_lpmhFree = (LPMIDIHDR)lpbWork;

            lpbWork += dwEachBufferSize;
            }

            return ::success;*/
            return ::success;
         }

         /***************************************************************************
         *
         * seqFreeBuffers
         *
         * Free buffers for this instance.
         *
         * pSeq                      - The sequencer instance to free buffers for.
         *
         * seqFreeBuffers frees all allocated primitive::memory belonging to the
         * given sequencer instance pSeq. It must be the last call
         * performed on the instance before it is destroyed.
         *
         ****************************************************************************/
         VOID sequence::FreeBuffers()
         {
            ASSERT(FALSE);
            /*
            LPMIDIHDR               lpmh;

            //    assert(pSeq != NULL);

            if (NULL != m_lpbAlloc)
            {
            lpmh = (LPMIDIHDR)m_lpbAlloc;
            ASSERT(!(lpmh->dwFlags & MHDR_PREPARED));

            //GlobalFreePtr(m_lpbAlloc);
            HeapFree(GetProcessHeap(), 0, m_lpbAlloc);
            }*/
         }

         /***************************************************************************
         *
         * seqOpenFile
         *
         * Associates a MIDI file with the given sequencer instance.
         *
         * pSeq                      - The sequencer instance.
         *
         * Returns
         *   ::success If the operation is successful.
         *
         *   ::music::EFunctionNotSupported If there is already a file open
         *     on this instance.
         *
         *   MCIERR_OUT_OF_MEMORY If there was insufficient primitive::memory to
         *     allocate internal buffers on the file.
         *
         *   MCIERR_INVALID_FILE If initial attempts to parse the file
         *     failed (such as the file is not a MIDI or RMI file).
         *
         * seqOpenFile may only be called if there is no currently open file
         * on the instance. It must be paired with a call to seqCloseFile
         * when operations on this file are complete.
         *
         * The pstrFile field of pSeq contains the name of the file
         * to open. This name will be passed directly to mmioOpen; it may
         * contain a specifcation for a custom MMIO file handler. The task
         * context used for all I/O will be the task which calls seqOpenFile.
         *
         ***************************************************************************/

   //      ::e_status sequence::OpenFile(::music::midi::sequence & sequence, int32_t openMode)
   //      {
   //
   //         return ::music::midi::sequence::OpenFile(sequuence, openMode);
   //
   ////         SMFFILEINFO                sfi;
   ////         ::e_status          smfrc;
   ////         unsigned int                   cbBuffer;
   ////
   ////         if (get_state() != e_state_no_file)
   ////         {
   ////
   ////            return ::music::EFunctionNotSupported;
   ////
   ////         }
   ////
   ////         m_iOpenMode = openMode;
   ////
   ////         smfrc = file()->OpenFile(*sequence.get_file(), openMode);
   ////
   ////         if (::music::success != smfrc)
   ////         {
   ////
   ////            goto Seq_Open_File_Cleanup;
   ////
   ////         }
   ////
   ////         file()->GetFileInfo(&sfi);
   ////
   ////         m_dwTimeDivision = sfi.dwTimeDivision;
   ////         m_tkLength       = sfi.tickLength;
   ////         if(m_iOpenMode == ::music::midi::file::OpenForPlaying)
   ////         {
   ////            m_msLength      = TicksToMillisecs(m_tkLength);
   ////         }
   ////         /* Track buffers must be big enough to hold the state data returned
   ////         ** by smfSeek()
   ////         */
   ////         cbBuffer = MIN(m_cbBuffer, ::music::midi::GetStateMaxSize());
   ////
   ////
   ////Seq_Open_File_Cleanup:
   ////
   ////         if (::music::success != smfrc)
   ////            CloseFile();
   ////         else
   ////            set_state(e_state_opened);
   ////
   ////         return smfrc;
   ////
   //      }


   //      ::e_status sequence::OpenFile(const char * lpFileName, int32_t openMode)
   //      {
   //
   //         return ::music::midi::sequence::OpenFile(lpFileName, openMode);
   //
   ////         ::file::file_sp file(
   ////            get_app());
   ////         file->open(lpFileName,
   ////            ::file::mode_read |
   ////            ::file::share_deny_write |
   ////            ::file::type_binary);
   ////         return OpenFile(*file, openMode);
   //      }
   //
   //
   //      ::e_status sequence::OpenFile(memory * pmemorystorage, int32_t openMode, e_storage estorage)
   //      {
   //         SMFFILEINFO             sfi;
   //         ::e_status    smfrc;
   //         unsigned int                   cbBuffer;
   //
   //         if (get_state() != e_state_no_file)
   //         {
   //            CloseFile();
   //            //return ::music::EFunctionNotSupported;
   //         }
   //
   //         m_iOpenMode = openMode;
   //
   //         smfrc = file()->OpenFile(pmemorystorage, openMode, estorage);
   //
   //         if (::music::success != smfrc)
   //         {
   //         }
   //         else
   //         {
   //            file()->GetFileInfo(&sfi);
   //
   //            m_dwTimeDivision = sfi.dwTimeDivision;
   //            m_tkLength       = sfi.tickLength;
   //            if(m_iOpenMode == ::music::midi::file::OpenForPlaying)
   //            {
   //               m_msLength      = TicksToMillisecs(m_tkLength);
   //            }
   //            /* Track buffers must be big enough to hold the state data returned
   //            ** by smfSeek()
   //            */
   //            cbBuffer = MIN(m_cbBuffer, ::music::midi::GetStateMaxSize());
   //         }
   //
   //         if(::music::success != smfrc)
   //            CloseFile();
   //         else
   //            set_state(e_state_opened);
   //
   //         return smfrc;
   //      }
   //
   //      ::e_status sequence::OpenFile(
   //         ::file::file & ar,
   //         int32_t openMode)
   //      {
   //         ::e_status                rc      = ::success;
   //         //    SMFOPENFILESTRUCT       sofs;
   //         SMFFILEINFO             sfi;
   //         ::e_status               smfrc;
   //         unsigned int                   cbBuffer;
   //         //    assert(pSeq != NULL);
   //
   //         if (get_state() != e_state_no_file)
   //         {
   //            return ::music::EFunctionNotSupported;
   //         }
   //
   //
   //
   //         //   m_pstrFile = _tcsdup(lpFileName);
   //         //   m_strFile = lpFileName;
   //
   //         //    ASSERT(m_pstrFile != NULL);
   //
   //         m_iOpenMode = openMode;
   //
   //         //    sofs.pstrName     = m_pstrFile;
   //
   //         //PSMF pSmf = aaa_primitive_new SMF();
   //
   //         //smfrc = file()->OpenFile(&sofs);
   //         smfrc = file()->OpenFile(ar, openMode);
   //
   //         //smfrc = smfOpenFile(&sofs);
   //         if (::music::success != smfrc)
   //         {
   //            //      delete pSmf;
   //            rc = ::music::translate(smfrc);
   //         }
   //         else
   //         {
   //            //    m_hSmf = sofs.hSmf;
   //            //    ((PSMF) m_hSmf)->GetFileInfo(&sfi);
   //            file()->GetFileInfo(&sfi);
   //
   //            m_dwTimeDivision = sfi.dwTimeDivision;
   //            m_tkLength       = sfi.tickLength;
   //            if(m_iOpenMode == ::music::midi::file::OpenForPlaying)
   //            {
   //               m_msLength      = TicksToMillisecs(m_tkLength);
   //            }
   //            /* Track buffers must be big enough to hold the state data returned
   //            ** by smfSeek()
   //            */
   //            cbBuffer = MIN(m_cbBuffer, ::music::midi::GetStateMaxSize());
   //         }
   //
   //         if (::music::success != smfrc)
   //            CloseFile();
   //         else
   //            set_state(e_state_opened);
   //
   //         return smfrc;
   //      }
         /***************************************************************************
         *
         * seqCloseFile
         *
         * Deassociates a MIDI file with the given sequencer instance.
         *
         * pSeq                      -  The sequencer instance.
         *
         * Returns
         *   ::success If the operation is successful.
         *
         *   ::music::EFunctionNotSupported If the sequencer instance is not
         *     stopped.
         *
         * A call to seqCloseFile must be paired with a prior call to
         * seqOpenFile. All buffers associated with the file will be
         * freed and the file will be closed. The sequencer must be
         * stopped before this call will be accepted.
         *
         ***************************************************************************/
         ::e_status sequence::CloseFile()
         {

            synchronous_lock sl(m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //         if (m_pseq)
   //         {
   //
   //            seq_free_context(m_pseq);
   //
   //         }

            ::e_status eresult = ::music::midi::sequence::close_file();

            return eresult;

         }


         /***************************************************************************
         *
         * seqPreroll
         *
         * Prepares the file for playback at the given position.
         *
         * pSeq                      - The sequencer instance.
         *
         * lpPreroll                 - Specifies the starting and ending tick
         *                             positions to play between.
         *
         * Returns
         *   ::success If the operation is successful.
         *
         *   ::music::EFunctionNotSupported If the sequencer instance is not
         *     opened or prerolled.
         *
         * open the device so we can initialize channels.
         *
         * Loop through the tracks. For each track, seek to the given position and
         * send the init data SMF gives us to the handle.
         *
         * Wait for all init buffers to finish.
         *
         * Unprepare the buffers (they're only ever sent here; the sequencer
         * engine merges them into a single stream during normal playback) and
         * refill them with the first chunk of data from the track.
         *
         *
         ****************************************************************************/
   //      ::e_status sequence::Preroll(::thread * pthread, ::music::midi::LPPREROLL lpPreroll, bool bThrow)
   //      {
   //
   //         __UNREFERENCED_PARAMETER(pthread);
   //         single_lock sl(m_pmutex, TRUE);
   //         int32_t i;
   //         ::e_status     smfrc;
   //         ::e_status                mmrc        = ::success;
   ////         MIDIPROPTIMEDIV         mptd;
   //         LPMIDIHDR               lpmh = NULL;
   //         //   LPMIDIHDR               lpmhPreroll = NULL;
   //         unsigned int                    uDeviceID;
   //
   //
   //         ASSERT(m_iOpenMode == ::music::midi::file::OpenForPlaying
   //            || IsInSpecialModeV001());
   //
   //         m_flags.unsignalize(e_flag_end_of_file);
   //
   //         m_mmrcLastErr = ::success;
   //
   //         if(get_state() != e_state_opened &&
   //            get_state() != e_state_pre_rolled &&
   //            !IsInSpecialModeV001())
   //            return ::music::translate(::music::EFunctionNotSupported);
   //
   //         m_tkBase = lpPreroll->tickBase;
   //         m_tkEnd = lpPreroll->tickEnd;
   //         if(m_pseq != NULL)
   //         {
   //            // Recollect buffers from MMSYSTEM back into free queue
   //            //
   //            set_state(::music::midi::sequence::e_state_reset);
   //
   ////            seq_free_context(m_pseq);
   ////
   //            m_pseq = NULL;
   //
   //         }
   //
   //         set_state(::music::midi::sequence::e_state_pre_rolling);
   //
   //         //
   //         // We've successfully opened the file and all of the tracks; now
   //         // open the MIDI device and set the time division.
   //         //
   //         // NOTE: seqPreroll is equivalent to seek; device might already be open
   //         //
   //
   //
   //         mmrc = ::success;
   //
   //
   //
   //         m_buffera.Reset();
   //         lpmh = &m_buffera[0].m_midihdr;
   //
   //         if(IsInSpecialModeV001())
   //         {
   //
   //            if(m_uiSpecialModeV001Operation == SPMV001GMReset)
   //            {
   //               /*const uchar gmModeOn[] = {
   //                  //        0x00, 0x00, 0x00, 0x00,
   //                  //        0x00, 0x00, 0x00, 0x00,
   //                  //        0x1b, 0x8a, 0x06, MEVT_TEMPO,
   //                  0x00, 0x00, 0x00, 0x00,
   //                  0x00, 0x00, 0x00, 0x00,
   //                  0x06, 0x00, 0x00, MEVT_LONGMSG,
   //                  0xf0, 0x7e, 0x7f, 0x09,
   //                  0x01, 0xf7, 0x00, 0x00};
   //               char * lpch = lpmh->lpData + lpmh->dwBytesRecorded;
   //               lpmh->dwBytesRecorded += sizeof(gmModeOn);
   //               memory_copy(lpch, gmModeOn, sizeof(gmModeOn));
   //               SetSpecialModeV001Flag(false);*/
   //            }
   //
   //         }
   //
   //         smfrc = file()->WorkSeek(m_tkBase);
   //
   //         m_tkPrerollBase = get_file()->GetPosition();
   //
   //         m_flags.unsignalize(e_flag_end_of_file);
   //
   //         file()->m_ulFlags &= ~::music::midi::file::EndOfFile;
   //
   //
   ///*
   //
   //         for(i = 1; i < m_buffera.get_size(); i++)
   //         {
   //
   //            lpmh = m_buffera[i].GetMidiHdr();
   //
   //            smfrc = file()->WorkStreamRender(lpmh, m_tkEnd, m_cbPrerollNominalMax);
   //
   //            if(::music::success != smfrc && ::music::SEndOfFile != smfrc)
   //            {
   //               information( "SFP: smfReadEvents() -> %u", (unsigned int)smfrc);
   //               mmrc = ::music::translate(smfrc);
   //               /*if(bThrow)
   //               {
   //               set_state(e_state_opened);
   //               throw aaa_primitive_new exception(mmrc, MIDIPLAYERPRERROLLREADEVENTSEXCEPTION);
   //               }*/
   ///*               goto seq_Preroll_Cleanup;
   //            }
   //
   //
   //
   //            if (::music::SEndOfFile == smfrc)
   //            {
   //               m_flags.signalize(e_flag_end_of_file);
   //               break;
   //            }
   //         }
   //*/
   //
   ///*         mmrc = m_buffera.midiOutPrepareHeader((HMIDIOUT) m_hstream);
   //         if (mmrc != ::success)
   //         {
   //            information( "midiOutPrepare(preroll) -> %lu!", (unsigned int)mmrc);
   //            mmrc = MCIERR_DEVICE_NOT_READY;
   //            if(bThrow)
   //            {
   //               set_state(e_state_opened);
   //               throw aaa_primitive_new exception(get_app(), mmrc, MIDIPLAYERPRERROLLPREPAREHEADEREXCEPTION);
   //            }
   //            else
   //            {
   //               goto seq_Preroll_Cleanup;
   //            }
   //         }
   //*/
   //
   //         //mmrc = m_buffera.midiStreamOut(m_hstream);
   //         if (mmrc != ::success)
   //         {
   //            information( "midiOutPrepare(preroll) -> %lu!", (unsigned int)mmrc);
   //            //mmrc = MCIERR_DEVICE_NOT_READY;
   //            if(bThrow)
   //            {
   //               set_state(e_state_opened);
   //               throw aaa_primitive_new exception(get_app(), ::music::EMidiPlayerPrerollPrepareHeader);
   //            }
   //            else
   //            {
   //               goto seq_Preroll_Cleanup;
   //            }
   //         }
   ////         m_uBuffersInMMSYSTEM +=(unsigned int)  m_buffera.get_size();
   //
   //seq_Preroll_Cleanup:
   //
   //         if (mmrc != ::success)
   //         {
   //            set_state(e_state_opened);
   //            m_flags.unsignalize(::music::midi::sequence::e_flag_waiting);
   //         }
   //         else
   //         {
   //            set_state(e_state_pre_rolled);
   //         }
   //
   //         return mmrc;
   //      }

         /***************************************************************************
         *
         * seqStart
         *
         * Starts playback at the current position.
         *
         * pSeq                      - The sequencer instance.
         *
         * Returns
         *   ::success If the operation is successful.
         *
         *   ::music::EFunctionNotSupported If the sequencer instance is not
         *     stopped.
         *
         *   MCIERR_DEVICE_NOT_READY If the underlying MIDI device could
         *     not be opened or fails any call.
         *
         * The sequencer must be prerolled before seqStart may be called.
         *
         * Just feed everything in the ready queue to the device.
         *
         ***************************************************************************/
         ::e_status sequence::Start()
         {

            single_lock sl(m_pmutex, TRUE);

            if (::music::midi::sequence::e_state_pre_rolled != get_state())
            {

               information( "seqStart(): State is wrong! [%u]", get_state());

               return error_wrong_state;

            }

            m_happeningMmsgDone.reset_happening();

            ::e_status mmrc = ::success;

            sl.unlock();

            if(mmrc == ::success)
            {

               thread()->PostMidiSequenceEvent(this, ::music::midi::sequence::e_event_midi_playback_start);

            }

            return mmrc;

         }


         sp(message_out) sequence::get_message_out()
         {

            if(m_pmidiout == nullptr)
            {

               string strDriver;

               strDriver = Application.midi()->get_midi_out_device();

               //strDriver = file_as_string(dir::localconfig() / "rawmidi.txt");

               //if(strDriver.is_empty())
               //{

                 // strDriver = "hw:0,0";

               //}

               m_pmidiout = __sp(aaa_primitive_new midi_out(get_app(), strDriver));

            }

            return m_pmidiout;

         }

   //      ::e_status sequence::seq_start()
   //      {
   //
   //
   //
   //         single_lock sl(m_pmutex, TRUE);
   //
   //         if(get_state() != e_state_pre_rolled)
   //         {
   //
   //            return ::music::translate(::music::EFunctionNotSupported);
   //
   //         }
   //
   //         if (m_pseq == NULL)
   //         {
   //
   //            m_pseq = seq_create_context();
   //
   //            if(m_pseq == NULL)
   //            {
   //
   //               return ::error_failed;
   //
   //            }
   //
   //         }
   //
   //         int  err;
   //
   //         err = seq_connect_add(m_pseq, m_iClient, m_iPort);
   //
   //         if (err < 0)
   //         {
   //
   //            informationf("Could not connect to port "+::unicode_from(m_iClient)+":"+::unicode_from(m_iPort)+"\n");
   //
   //            return ::error_failed;
   //
   //         }
   //
   //         set_state(e_state_playing);
   //
   //         seq_init_tempo(m_pseq, m_dwTimeDivision, 120, 1);
   //
   //         snd_seq_event_t ev;
   //
   //         KEYFRAME & keyframe = get_file()->m_keyframe;
   //
   //         if (KF_EMPTY != keyframe.rbTempo[0] || KF_EMPTY != keyframe.rbTempo[1] || KF_EMPTY != keyframe.rbTempo[2])
   //         {
   //
   //            unsigned int dwTempo =  (((unsigned int)keyframe.rbTempo[0])<<16) | (((unsigned int)keyframe.rbTempo[1])<<8) | ((unsigned int)keyframe.rbTempo[2]);
   //
   //            dwTempo = (unsigned int) ((double) dwTempo / get_file()->GetTempoShiftRate());
   //
   //            seq_midi_event_init(m_pseq, &ev, 0, 0);
   //
   //            seq_midi_tempo(m_pseq, &ev, dwTempo);
   //
   //         }
   //
   //         for (::collection::index idxChannel = 0; idxChannel < 16; idxChannel++)
   //         {
   //
   //            if (KF_EMPTY != keyframe.rbProgram[idxChannel])
   //            {
   //
   //               seq_midi_event_init(m_pseq, &ev, 0, idxChannel);
   //
   //               seq_midi_program(m_pseq, &ev, idxChannel, keyframe.rbProgram[idxChannel]);
   //
   //            }
   //
   //         }
   //
   //         for (::collection::index idxChannel = 0; idxChannel < 16; idxChannel++)
   //         {
   //
   //            for (::collection::index idxController = 0; idxController < 120; idxController++)
   //            {
   //
   //               if (KF_EMPTY != keyframe.rbControl[idxChannel][idxController])
   //               {
   //
   //                  seq_midi_event_init(m_pseq, &ev, 0, idxChannel);
   //
   //                  seq_midi_control(m_pseq, &ev, idxChannel, idxController, keyframe.rbControl[idxChannel][idxController]);
   //
   //               }
   //
   //            }
   //
   //         }
   //
   //         m_iaBuffered.remove_all();
   //
   //         m_iBuffered = 0;
   //
   //         m_evptra.remove_all();
   //
   //         fork([&]()
   //         {
   //
   //            seq_run();
   //
   //         });
   //
   //         return ::success;
   //
   //      }


         /***************************************************************************
         *
         * seqPause
         *
         * Pauses playback of the instance.
         *
         * pSeq                      - The sequencer instance.
         *
         * Returns
         *   ::success If the operation is successful.
         *
         *   ::music::EFunctionNotSupported If the sequencer instance is not
         *     playing.
         *
         * The sequencer must be playing before seqPause may be called.
         * Pausing the sequencer will cause all currently on notes to be turned
         * off. This may cause playback to be slightly inaccurate on restart
         * due to missing notes.
         *
         ***************************************************************************/
         ::e_status sequence::Pause()
         {

            synchronous_lock sl(m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            if (e_state_playing != get_state())
            {

               return error_wrong_state;

            }

            set_state(e_state_paused);

            ::e_status mmrc = ::success;
            //    single_lock slStream(&m_csStream, false);
            //  slStream.lock();
   //         if(m_pseq != NULL)
   //         {
   //            seq_stop_timer(m_pseq);
   //         }
            //slStream.unlock();

            SetLevelMeter(0);

            return ::success;
         }

         /***************************************************************************
         *
         * seqRestart
         *
         * Restarts playback of an instance after a pause.
         *
         * pSeq                      - The sequencer instance.
         *
         * Returns
         *    ::success If the operation is successful.
         *
         *    ::music::EFunctionNotSupported If the sequencer instance is not
         *     paused.
         *
         * The sequencer must be paused before seqRestart may be called.
         *
         ***************************************************************************/
         ::e_status sequence::Restart()
         {
            //    assert(NULL != pSeq);

            single_lock sl(m_pmutex, TRUE);

            if (e_state_paused != get_state())
            {

               return error_wrong_state;

            }

            set_state(e_state_playing);
            m_happeningMmsgDone.reset_happening();

            //    ::e_status mmrc = 0;
            //    single_lock slStream(&m_csStream, false);
            //  slStream.lock();
   //         if(m_pseq != NULL)
   //         {
   //            seq_start_timer(m_pseq);
   //         }
            //slStream.unlock();
            return ::success;
         }

         /***************************************************************************
         *
         * seqStop
         *
         * Totally stops playback of an instance.
         *
         * pSeq                      - The sequencer instance.
         *
         * Returns
         *   ::success If the operation is successful.
         *
         *   ::music::EFunctionNotSupported If the sequencer instance is not
         *     paused or playing.
         *
         * The sequencer must be paused or playing before seqStop may be called.
         *
         ***************************************************************************/
         ::e_status sequence::Stop()
         {

            synchronous_lock sl(m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            if(get_state() == e_state_stopping)
            {

               return ::success;

            }

            if (get_state() != e_state_playing && get_state() != e_state_paused)
            {

               m_flags.unsignalize(::music::midi::sequence::e_flag_waiting);

               GetPlayerLink().OnFinishCommand(::music::midi::command_stop);

               return ::success;

            }

            set_state(e_state_stopping);

            m_flags.signalize(::music::midi::sequence::e_flag_waiting);

            m_happeningMidiPlaybackEnd.reset_happening();

            m_bPlay = false;

            SetLevelMeter(0);

   //         if(m_pseq != NULL)
   //         {
   //
   ////            Sleep(250);
   ////
   //////            seq_stop_timer(m_pseq);
   //////
   ////            if(m_pseq != NULL)
   ////            {
   ////
   ////               seq_stop_timer(m_pseq);
   ////
   ////               seq_free_context(m_pseq);
   ////
   ////               m_pseq = NULL;
   ////
   ////            }
   //
   //
   //            if(::success != m_mmrcLastErr)
   //            {
   //
   //               information( "::music::midi::sequence::Stop() -> midiOutStop() returned %lu in seqStop()!\n", (unsigned int)m_mmrcLastErr);
   //
   //               m_flags.unsignalize(e_flag_waiting);
   //
   //               return ::multimedia::result_not_ready;
   //
   //            }
   //
   //         }

   //         m_happeningMidiPlaybackEnd.lock();

            return ::success;

         }


         /***************************************************************************
         *
         * seqTime
         *
         * Determine the current position in playback of an instance.
         *
         * pSeq                      - The sequencer instance.
         *
         & ticka                    - A pointer to a unsigned int where the current position
         *                             in ticks will be returned.
         *
         * Returns
         *   ::success If the operation is successful.
         *
         *   MCIERR_DEVICE_NOT_READY If the underlying device fails to report
         *     the position.
         *
         *   ::music::EFunctionNotSupported If the sequencer instance is not
         *     paused or playing.
         *
         * The sequencer must be paused, playing or prerolled before seqTime
         * may be called.
         *
         ***************************************************************************/
   //      ::e_status sequence::get_ticks(imedia_position &  pTicks)
   //      {
   //
   //      return ::music::midi::sequence::get_ticks(pTicks);
   //
   //         synchronous_lock sl(m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
   //
   //         ::e_status                mmr;
   //
   //         if (::music::midi::sequence::e_state_playing != get_state() &&
   //            ::music::midi::sequence::e_state_paused != get_state() &&
   //            ::music::midi::sequence::e_state_pre_rolling != get_state() &&
   //            ::music::midi::sequence::e_state_pre_rolled != get_state() &&
   //            ::music::midi::sequence::e_state_opened != get_state() &&
   //            ::music::midi::sequence::e_state_stopping != get_state())
   //         {
   //            information( "seqTime(): State wrong! [is %u]", get_state());
   //            return ::music::translate(::music::EFunctionNotSupported);
   //         }
   //
   //         pTicks = 0;
   //         if (e_state_opened != get_state())
   //         {
   //            pTicks = m_tkBase;
   //            if (e_state_pre_rolled != get_state())
   //            {
   ////               mmt.wType = TIME_TICKS;
   //               //            single_lock slStream(&m_csStream, false);
   //               //          slStream.lock();
   //               snd_seq_tick_time_t ticks;
   //               if(m_pseq == NULL)
   //               {
   //                  informationf("m_hmidi == NULL!!!!");
   //                  return ::multimedia::result_not_ready;
   //               }
   //               else
   //               {
   //                  try
   //                  {
   //
   //                     snd_seq_queue_status_t * pstatus = NULL;
   //
   //                     snd_seq_queue_status_malloc(&pstatus);
   //
   //                     if(pstatus == NULL)
   //                        return ::multimedia::result_internal;
   //
   //                     if(snd_seq_get_queue_status(m_pseq->handle, m_pseq->queue, pstatus) < 0)
   //                        return ::multimedia::result_internal;
   //
   //                     ticks = snd_seq_queue_status_get_tick_time(pstatus);
   //
   //                     snd_seq_queue_status_free(pstatus);
   //
   //                  }
   //                  catch(...)
   //                  {
   //                     return ::multimedia::result_internal;
   //                  }
   //                  pTicks += ticks;
   //               }
   //               //        slStream.unlock();
   //            }
   //         }
   //
   //         return ::success;
   //      }

   //      void sequence::get_time(imedia_time & time)
   //      {
   //         get_millis(time);
   //      }

   //      ::e_status sequence::get_millis(imedia_time & time)
   //      {
   //
   //      return ::music::midi::sequence::get_millis(time);
   //         single_lock sl(m_pmutex);
   //         if(!sl.lock(millis(184)))
   //            return ::multimedia::result_internal;
   //
   //         ::e_status                mmr;
   //         //MMTIME                  mmt;
   //
   //         if (e_state_playing != get_state() &&
   //            e_state_paused != get_state() &&
   //            e_state_pre_rolling != get_state() &&
   //            e_state_pre_rolled != get_state() &&
   //            e_state_opened != get_state() &&
   //            e_state_stopping != get_state())
   //         {
   //            information( "seqTime(): State wrong! [is %u]", get_state());
   //            return ::music::translate(::music::EFunctionNotSupported);
   //         }
   //
   //         time = 0;
   //         if (e_state_opened != get_state())
   //         {
   //            time = (int_ptr) TicksToMillisecs(m_tkBase);
   //            if (e_state_pre_rolled != get_state())
   //            {
   //               const snd_seq_real_time_t * prt = NULL;
   //               //            single_lock slStream(&m_csStream, false);
   //               //          slStream.lock();
   //               if(m_pseq == NULL)
   //               {
   //                  informationf("m_hmidi == NULL!!!!");
   //                  return ::multimedia::result_not_ready;
   //               }
   //               else
   //               {
   //                  try
   //                  {
   //
   //                     snd_seq_queue_status_t * pstatus = NULL;
   //
   //                     snd_seq_queue_status_malloc(&pstatus);
   //
   //                     if(pstatus == NULL)
   //                        return ::multimedia::result_internal;
   //
   //                     if(snd_seq_get_queue_status(m_pseq->handle, m_pseq->queue, pstatus) < 0)
   //                        return ::multimedia::result_internal;
   //
   //                     prt = snd_seq_queue_status_get_real_time(pstatus);
   //
   //                     snd_seq_queue_status_free(pstatus);
   //
   //                  }
   //                  catch(...)
   //                  {
   //                     return ::multimedia::result_internal;
   //                  }
   //                  if(prt == NULL)
   //                     return ::multimedia::result_internal;;
   //                  time += (prt->tv_nsec / (1000 * 1000)) + (prt->tv_sec * 1000);
   //               }
   //               //        slStream.unlock();
   //            }
   //         }
   //
   //         return ::success;
   //      }

         /***************************************************************************
         *
         * seqMillisecsToTicks
         *
         * Given a millisecond offset in the output stream, returns the associated
         * tick position.
         *
         * pSeq                      - The sequencer instance.
         *
         * msOffset                  - The millisecond offset into the stream.
         *
         * Returns the number of ticks into the stream.
         *
         ***************************************************************************/
   //      imedia_position sequence::MillisecsToTicks(imedia_time msOffset)
   //      {
   //         return file()->MillisecsToTicks(msOffset);
   //      }

         /***************************************************************************
         *
         * seqTicksToMillisecs
         *
         * Given a tick offset in the output stream, returns the associated
         * millisecond position.
         *
         * pSeq                      - The sequencer instance.
         *
         * tickOffset                  - The tick offset into the stream.
         *
         * Returns the number of milliseconds into the stream.
         *
         ***************************************************************************/
   //      imedia_time sequence::TicksToMillisecs(imedia_position tickOffset)
   //      {
   //         return file()->TicksToMillisecs(tickOffset);
   //      }

         void sequence::OnDone(seq_context_t * hmidistream, LPMIDIHDR lpmidihdr)
         {
            __UNREFERENCED_PARAMETER(hmidistream);
            ::e_status               smfrc;
            midi_callback_data *      lpData;
            ASSERT(lpmidihdr != NULL);
            lpData = (midi_callback_data *) lpmidihdr->dwUser;
            ASSERT(lpData != NULL);

            ::music::midi::sequence * psequence = lpData->m_psequence;

            sequence_thread * pthread = dynamic_cast < sequence_thread * > (psequence->m_pthread);

            ASSERT(NULL != lpmidihdr);

   ///         --m_uBuffersInMMSYSTEM;

   /*         if(m_uBuffersInMMSYSTEM <= 0)
            {
               m_happeningBuffersZero.set_happening();
            }*/

            if (e_state_reset == get_state())
            {
               // We're recollecting buffers from MMSYSTEM
               //
               //      if (lpmidihdr != m_lpmhPreroll)
               //    {
               //     lpmidihdr->lpNext    = m_lpmhFree;
               //   m_lpmhFree           = lpmidihdr;
               //      }
               return;
            }

            bool bStopping = e_state_stopping == get_state();

            bool bSpecialModeV001End = m_flags.is_signalized(e_flag_operation_end);

            //if (bStopping || bEndOfPlay || bSpecialModeV001End)
            if (bStopping || bSpecialModeV001End)
            {
               //
               // Reached EOF, just put the buffer back on the free
               // list
               //
               if(bSpecialModeV001End)
               {
                  m_flags.unsignalize(e_flag_operation_end);
                  informationf("void CALLBACK ::music::midi::sequence::MidiOutProc m_flags.is_signalized(FlagSpecialModeV001End\n");
                  pthread->PostMidiSequenceEvent(
                     this,
                     ::music::midi::sequence::e_event_operation,
                     lpmidihdr);
               }
               else if(bStopping)
               {
   /*               if(m_uBuffersInMMSYSTEM == 0)
                  {
                     informationf("void CALLBACK ::music::midi::sequence::MidiOutProc e_state_stopping == pSeq->get_state()\n");
                     pthread->PostMidiSequenceEvent(
                        this,
                        ::music::midi::sequence::EventStopped,
                        lpmidihdr);
                  }*/
               }
               else
               {
                  if(m_flags.is_signalized(e_flag_end_of_file))
                  {
                     informationf("void CALLBACK ::music::midi::sequence::MidiOutProc m_flags.is_signalized(e_flag_end_of_file\n");
                  }
                  //       if (lpmidihdr != m_lpmhPreroll)
                  //     {
                  //      lpmidihdr->lpNext = m_lpmhFree;
                  //    m_lpmhFree        = lpmidihdr;
                  //}
   /*               if(m_uBuffersInMMSYSTEM <= 0)
                  {
                     pthread->PostMidiSequenceEvent(
                        this,
                        ::music::midi::sequence::e_event_midi_playback_end,
                        lpmidihdr);
                  }*/
               }
            }
            else
            {
               if(IsInSpecialModeV001())
               {
                  if(m_eoperation == operation_general_midi_reset)
                  {
//                     const uchar gmModeOn[] = {
//                        //        0x00, 0x00, 0x00, 0x00,
//                        //        0x00, 0x00, 0x00, 0x00,
//                        //        0x1b, 0x8a, 0x06, MEVT_TEMPO,
//                        0x00, 0x00, 0x00, 0x00,
//                        0x00, 0x00, 0x00, 0x00,
//                        0x06, 0x00, 0x00, MEVT_LONGMSG,
//                        0xf0, 0x7e, 0x7f, 0x09,
//                        0x01, 0xf7, 0x00, 0x00};
//                     lpmidihdr->dwBytesRecorded = sizeof(gmModeOn);
//                     memory_copy(lpmidihdr->lpData, gmModeOn, sizeof(gmModeOn));
                  }
                  else if(m_eoperation == operation_tempo_change)
                  {
                     ::music::midi::happening happening;
                     file()->GetTempoEvent(happening);
   //                  file()->StreamEvent(happening.GetDelta(), &happening, lpmidihdr, I32_MAXIMUM, 256);
                     // lpmidihdr->dwBytesRecorded = sizeof(gmModeOn);
                     // memory_copy(lpmidihdr->lpData, gmModeOn, sizeof(gmModeOn));
                  }
                  else
                  {
                     ASSERT(FALSE);
                  }
                  //post_thread_message(lpData->dwThreadID, MIDIPLAYERMESSAGE_STREAMOUT, (WPARAM) pSeq, (LPARAM) lpmidihdr);
                  pthread->PostMidiSequenceEvent(
                     this,
                     e_event_midi_playback_out,
                     lpmidihdr);
                  m_flags.signalize(e_flag_operation_end);
                  smfrc = ::success;
                  return;
               }
               //
               // Not EOF yet; attempt to fill another buffer
               //
               pthread->PostMidiSequenceEvent(
                  this,
                  e_event_midi_playback_out,
                  lpmidihdr);
            }

         }

         void sequence::OnPositionCB(LPMIDIHDR lpmidihdr)
         {
            /*ASSERT(lpmidihdr != NULL);
            LPBYTE lpbData = (LPBYTE) (lpmidihdr->lpData + lpmidihdr->dwOffset);
            MIDIEVENT * lpme = (MIDIEVENT *) lpbData;
            file::midi_stream_happening_header * pheader = (file::midi_stream_happening_header *) &lpme->dwParms[0];
            lpbData = (LPBYTE) pheader;
            LPDWORD lpdwParam;

            int32_t iSize = pheader->m_dwLength;
            switch(pheader->m_dwType)
            {
            case 0:
               {
                  array < ::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1 &> * plyriceventa = NULL;
                  array < ::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1 &> lyriceventa;
                  for(int32_t i = sizeof(file::midi_stream_happening_header); i < iSize;)
                  {
                     pheader = (file::midi_stream_happening_header *) &lpbData[i];
                     lpdwParam = (LPDWORD) &lpbData[i + sizeof(file::midi_stream_happening_header)];
                     ASSERT(*lpdwParam == pheader->m_dwType);
                     switch(pheader->m_dwType)
                     {
                     case EVENT_ID_LYRIC_V1:
                        {
                           if(plyriceventa == NULL)
                           {
                              plyriceventa = aaa_primitive_new array <::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1 &>;
                           }
                           ::file::memory_buffer memFile(get_app(), (LPBYTE) &lpdwParam[1], pheader->m_dwLength - sizeof(unsigned int));
                           /* x2x                  CArchive ar(&memFile, CArchive::load);
                           lyriceventa.Serialize(ar);
                           plyriceventa->append(lyriceventa); */
              /*          }
                        break;
                     case EVENT_ID_PAD:
                        {
                        }
                        break;
                     case EVENT_ID_NOTE_ON:
                        {
                           ::file::byte_stream_memory_buffer memFile(get_app(), (LPBYTE) &lpdwParam[1], pheader->m_dwLength - sizeof(unsigned int));
                           for(int32_t i = 0; i < m_iaLevel.get_size(); i++)
                           {
                              unsigned char b;
                              memFile >> b;
                              m_iaLevel.element_at(i) = b;
                           }
                        }
                        break;
                     }
                     i += pheader->m_dwLength + sizeof(file::midi_stream_happening_header);
                  }
                  /*         if(plyriceventa != NULL)
                  {
                  ::PostMessage(m_midicallbackdata.oswindow, WM_APP + 3388, 3388, (LPARAM) plyriceventa);
                  }*/
               /*}
               break;
            case EVENT_ID_PAD:
               break;
            default:
               ASSERT(FALSE);
               break;
            }*/

         }

         //void CALLBACK sequence::MidiOutProc(HMIDIOUT hmo, unsigned int wMsg, unsigned int dwInstance, unsigned int dwParam1, unsigned int dwParam2)
         //{

            /*__UNREFERENCED_PARAMETER(hmo);
            __UNREFERENCED_PARAMETER(dwInstance);
            __UNREFERENCED_PARAMETER(dwParam2);

            LPMIDIHDR               lpmh         = (LPMIDIHDR) dwParam1;

            switch(wMsg)
            {
            case MOM_POSITIONCB:
               ((midi_callback_data *) lpmh->dwUser)->m_psequence->OnPositionCB(lpmh);
               break;
            case MOM_DONE:
               ((midi_callback_data *) lpmh->dwUser)->m_psequence->OnDone(NULL,lpmh);
               return;
            }*/

         //}


         bool sequence::IsPlaying()
         {
            return get_state() == e_state_playing ||
               get_state() == e_state_stopping;
         }





   //      unsigned int sequence::set_state(unsigned int uiState)
   //      {
   //         m_uiPreviousState = m_uiState;
   //         m_uiState = uiState;
   //         return m_uiPreviousState;
   //      }
   //
   //      void sequence::SetSpecialModeV001Flag(bool bSet)
   //      {
   //         if(m_flags.is_signalized(FlagIsInSpecialModeV001))
   //            m_flags.signalize(FlagWasInSpecialModeV001);
   //         else
   //            m_flags.unsignalize(FlagWasInSpecialModeV001);
   //
   //         if(bSet)
   //            m_flags.signalize(FlagIsInSpecialModeV001);
   //         else
   //            m_flags.unsignalize(FlagIsInSpecialModeV001);
   //      }

   //      void sequence::SetSpecialModeV001Operation(unsigned int uiOperation)
   //      {
   //         m_estatusPreSpecialModeV001 = m_uiState;
   //         SetSpecialModeV001Flag();
   //         m_uiSpecialModeV001Operation = uiOperation;
   //      }

         bool sequence::IsInSpecialModeV001()
         {
            return m_flags.is_signalized(e_flag_operation);
         }

         bool sequence::WasInSpecialModeV001()
         {
            return m_flags.is_signalized(e_flag_was_operation);
         }


   //      void sequence::GetMidiDoneData(::music::midi::LPMIDIDONEDATA lpmdd)
   //      {
   //         lpmdd->m_flags = m_flags;
   //         lpmdd->m_uiSeqPreviousState = m_uiPreviousState;
   //         lpmdd->m_uiSeqState = m_uiState;
   //      }

         int32_t sequence::GetKeyShift()
         {

            if(m_pfile == nullptr)
               return 0;

            return file()->GetKeyShift();

         }

         int32_t sequence::SetKeyShift(int32_t iKeyShift)
         {
            /*//    single_lock slStream(&m_csStream, false);
            //  slStream.lock();
            if(m_hstream)
            {
            midiStreamPause(m_hstream);
            if(!file()->SetKeyShift(iKeyShift))
            return false;
            midiStreamRestart(m_hstream);
            }
            //slStream.unlock();
            return true;
            void ::music::midi::sequence::SetKeyShift(int32_t iShift)
            {*/
            bool bPlay = IsPlaying();
            imedia_position ticks = 0;
            if(bPlay)
            {
               ticks = get_position_ticks();
               Stop();
            }
            get_file()->SetKeyShift(iKeyShift);
            if(bPlay)
            {
               m_pthread->PrerollAndWait(ticks);
               Start();
            }
            //}
            return true;
         }

         double sequence::GetTempoShift()
         {
            return file()->GetTempoShift();
         }



         int32_t sequence::SetTempoShift(int32_t iTempoShift)
         {

            //midiStreamPause(m_hstream);
            if(::failed(file()->SetTempoShift(iTempoShift)))
               return false;
            //midiStreamRestart(m_hstream);
            return true;
         }



         ::e_status sequence::CloseStream()
         {
            single_lock sl(m_pmutex, TRUE);
            if(IsPlaying())
            {
               Stop();
            }

            /* If we were prerolled, need to clean up -- have an open MIDI handle
            ** and buffers in the ready queue
            */

   //         m_buffera.midiOutUnprepareHeader((HMIDIOUT) m_hstream);

            if (m_pseq != NULL)
            {
   //            seq_free_context(m_pseq);
               m_pseq = NULL;
            }

            set_state(e_state_opened);

            return ::success;
         }

         void sequence::SetLevelMeter(int32_t iLevel)
         {
            for(int32_t i = 0; i < m_iaLevel.get_size(); i++)
            {
               m_iaLevel.element_at(i) = iLevel;
            }
         }

         void sequence::OnMidiPlaybackEnd(::music::midi::sequence::happening * pevent)
         {
            __UNREFERENCED_PARAMETER(pevent);
            single_lock sl(m_pmutex, TRUE);
            //   LPMIDIHDR lpmh = pevent->m_lpmh;
            //   midi_callback_data * lpData = &m_midicallbackdata;
            ::e_status mmrc;


   //         if(0 == m_uBuffersInMMSYSTEM)
            {
               information( "seqBufferDone: normal sequencer shutdown.");

               /* Totally done! Free device and notify.
               */
               if(m_pseq != NULL)
               {
                  /*if((mmrc = m_buffera.midiOutUnprepareHeader((HMIDIOUT) m_hstream))
                     != ::success)
                  {
                     information( "midiOutUnprepareHeader failed in seqBufferDone! (%lu)", (unsigned int)mmrc);
                  }*/
   //               seq_free_context(m_pseq);
                  m_pseq = NULL;
               }

               m_estatusLastError = ::success;
               m_flags.unsignalize(e_flag_waiting);

               m_happeningMmsgDone.set_happening();
            }
         }

         void sequence::OnHappening(::music::midi::sequence::happening * pevent)
         {
            switch(pevent->m_ehappening)
            {
            case e_flag_operation_end:
               {
                  set_operation_on(false);
                  OnMidiPlaybackEnd(pevent);
                  set_state(m_estatePreOperation);
               }
               break;
            case e_event_midi_playback_end:
               {
                  OnMidiPlaybackEnd(pevent);
                  set_state(e_state_opened);
               }
               break;
            default:
               break;
            }
         }

         /*imedia_position sequence::GetPositionTicks()
         {
            single_lock sl(m_pmutex);
            if(!sl.lock(millis(0)))
               return -1;
            MMTIME mmt;
            mmt.wType = TIME_TICKS;
            if(::success ==
               midiStreamPosition(
               m_hstream,
               &mmt,
               sizeof(mmt)))
               return mmt.u.ticks + m_tkPrerollBase;
            else
               return -1;
         }*/


         bool sequence::IsChangingTempo()
         {
            return m_flags.is_signalized(::music::midi::sequence::e_flag_tempo_change);
         }
         void sequence::SetTempoChangeFlag(bool bSet)
         {
            if(bSet)
               m_flags.signalize(::music::midi::sequence::e_flag_tempo_change);
            else
               m_flags.unsignalize(::music::midi::sequence::e_flag_tempo_change);
         }




         bool sequence::IsNull()
         {
            if(this == NULL)
               return true;
            return false;
         }

         imedia_position sequence::TimeToPosition(imedia_time millis)
         {
            return imedia_position(MillisecsToTicks((int_ptr) millis));
         }

         imedia_time sequence::PositionToTime(imedia_position tick)
         {
            return imedia_time(TicksToMillisecs((imedia_position) (int_ptr) tick));
         }

   //      void sequence::get_position(imedia_position & position)
   //      {
   //         get_ticks(position);
   //      }

         bool sequence::IsOpened()
         {
            return get_state() != e_state_no_file;
         }


         void sequence::GetTimeLength(imedia_time & time)
         {

            time = m_msLength;

         }


   //      void sequence::Prepare(
   //         string_array_array_base & straa,
   //         imedia_position_2darray & tickaaTokensTicks,
   //         int32_t iMelodyTrack,
   //         int2a & ia2TokenLine,
   //         ::ikaraoke::data & data)
   //      {
   //         __UNREFERENCED_PARAMETER(straa);
   //         ::music::midi::alsa::file & file = *this->file();
   //         ::music::midi::tracks & tracks = file.GetTracks();
   //
   //         ASSERT(!file.IsNull());
   //         file.GetTracks().seek_begin();
   //         imedia_position               tickMax = file.m_tkLength;
   //         imedia_position               tickLastPosition = 0;
   //
   //
   //         ::ikaraoke::static_data & staticdata = data.GetStaticData();
   //
   //         if(staticdata.m_LyricsDisplayOffset < 480)
   //         {
   //            staticdata.m_LyricsDisplayOffset = 480;
   //         }
   //         if(staticdata.m_LyricsDisplayOffset > 720)
   //         {
   //            staticdata.m_LyricsDisplayOffset = 720;
   //         }
   //         staticdata.m_LyricsDisplay = 30;
   //
   //         imedia_position_2darray tickaaNoteOnPositions(get_app());
   //         imedia_position_2darray tickaaNoteOffPositions(get_app());
   //         imedia_position_2darray tickaaBegPositions(get_app());
   //         imedia_position_2darray tickaaEndPositions(get_app());
   //         imedia_time_2darray ms2DTokensMillis(get_app());
   //         imedia_time_2darray ms2DNoteOnMillis(get_app());
   //         imedia_time_2darray ms2DNoteOffMillis(get_app());
   //         imedia_time_2darray ms2DBegMillis(get_app());
   //         imedia_time_2darray ms2DEndMillis(get_app());
   //         ::music::midi::happenings midiEvents;
   //
   //
   //
   //
   //         // Note on and off happenings
   //         // and maximum and minimum
   //         // pitch bend peaks.
   //         ::music::midi::happenings midiEventsLevel2;
   //
   //         ::music::midi::happenings noteOnHappenings;
   //         ::music::midi::happenings noteOffEvents;
   //
   //         ::music::midi::happenings eventsLevel2Beg;
   //         ::music::midi::happenings eventsLevel2End;
   //         ::ikaraoke::events_tracks_v1 lyricEventsForPositionCB;
   //         ::ikaraoke::events_tracks_v1 lyricEventsForBouncingBall;
   //         ::ikaraoke::events_tracks_v1 lyricEventsForScoring;
   //         ::ikaraoke::events_tracks_v1 lyricEvents;
   //
   //         //   tracks.seek_begin();
   //         // tracks.GetXFInfoHeaders(
   //         //  &m_xfInfoHeaders);
   //
   //
   //
   //         file.PositionToTime(
   //            ms2DTokensMillis,
   //            tickaaTokensTicks,
   //            0);
   //
   //         ::ikaraoke::lyric_events_v2 *pLyricEventsV2;
   //         ::ikaraoke::lyric_events_v2 *pLyricEventsV2_;
   //         ::ikaraoke::lyric_events_v2 *pLyricEventsV2B;
   //         ::ikaraoke::lyric_events_v2 *pLyricEventsV2C;
   //         ::music::midi::happenings *pMidiEventsV1;
   //
   //         tickaaNoteOnPositions.set_size_create(tickaaTokensTicks.get_size());
   //         tickaaNoteOffPositions.set_size_create(tickaaTokensTicks.get_size());
   //         tickaaBegPositions.set_size_create(tickaaTokensTicks.get_size());
   //         tickaaEndPositions.set_size_create(tickaaTokensTicks.get_size());
   //         int32_t i;
   //         for(i = 0; i < tickaaTokensTicks.get_size(); i++)
   //         {
   //            pLyricEventsV2 = aaa_primitive_new ::ikaraoke::lyric_events_v2();
   //            pLyricEventsV2B = aaa_primitive_new ::ikaraoke::lyric_events_v2();
   //            pLyricEventsV2C = aaa_primitive_new ::ikaraoke::lyric_events_v2();
   //            pLyricEventsV2_ = aaa_primitive_new ::ikaraoke::lyric_events_v2();
   //            staticdata.m_happeningsv1.add(pLyricEventsV2);
   //            staticdata.m_happeningsv1.add(pLyricEventsV2B);
   //            staticdata.m_happeningsv1.add(pLyricEventsV2C);
   //            staticdata.m_happeningsv1.add(pLyricEventsV2_);
   //            lyricEvents.add(pLyricEventsV2_);
   //            lyricEventsForScoring.add(pLyricEventsV2);
   //            lyricEventsForPositionCB.add(pLyricEventsV2B);
   //            lyricEventsForBouncingBall.add(pLyricEventsV2C);
   //            pLyricEventsV2->m_iType = 0;
   //            pLyricEventsV2->m_iOrder = i;
   //            pLyricEventsV2->m_iType = 2;
   //            pLyricEventsV2->m_iOrder = i;
   //            pLyricEventsV2B->m_iType = ikaraoke::EventRunningElement;
   //            pLyricEventsV2B->m_iOrder = i;
   //            pLyricEventsV2C->m_iType = 4;
   //            pLyricEventsV2C->m_iOrder = i;
   //            pMidiEventsV1 = NULL;
   //            if(iMelodyTrack < 0)
   //            {
   //               pLyricEventsV2->m_iTrack =
   //                  file.WorkCalcMelodyTrack(
   //                  &pMidiEventsV1,
   //                  tickaaTokensTicks.operator()(i),
   //                  ia2TokenLine[i]);
   //            }
   //            else
   //            {
   //               pLyricEventsV2->m_iTrack = iMelodyTrack;
   //            }
   //            pLyricEventsV2B->m_iTrack = pLyricEventsV2->m_iTrack;
   //            pLyricEventsV2C->m_iTrack = pLyricEventsV2->m_iTrack;
   //            pLyricEventsV2_->m_iTrack = pLyricEventsV2->m_iTrack;
   //            if(pLyricEventsV2->m_iTrack < 0)
   //            {
   //               pLyricEventsV2->m_iTrack = tracks.m_iMelodyTrackTipA;
   //               pLyricEventsV2B->m_iTrack = tracks.m_iMelodyTrackTipA;
   //               pLyricEventsV2C->m_iTrack = tracks.m_iMelodyTrackTipA;
   //               pLyricEventsV2_->m_iTrack = tracks.m_iMelodyTrackTipA;
   //            }
   //            staticdata.SetGuessMelodyTrack(pLyricEventsV2->m_iTrack);
   //            if(pLyricEventsV2->m_iTrack >= 0)
   //            {
   //               if(file.GetFormat() == 0)
   //               {
   //                  tracks.TrackAt(0)->WorkSeekBegin();
   //                  ((::music::midi::track *)tracks.TrackAt(0))->WorkGetNoteOnOffEventsV1(
   //                     &midiEvents,
   //                     (int32_t) pLyricEventsV2->m_iTrack,
   //                     file.GetFormat() == 1);
   //                  tracks.TrackAt(0)->WorkSeekBegin();
   //                  ((::music::midi::track *)tracks.TrackAt(0))->WorkGetLevel2Events(
   //                     &midiEventsLevel2,
   //                     (int32_t) pLyricEventsV2->m_iTrack,
   //                     file.GetFormat() == 1);
   //               }
   //               else
   //               {
   //                  tracks.TrackAt(pLyricEventsV2->m_iTrack)->seek_begin();
   //                  ((::music::midi::track *)tracks.TrackAt(pLyricEventsV2->m_iTrack))->GetLevel2Events(
   //                     &midiEvents,
   //                     (int32_t) pLyricEventsV2->m_iTrack,
   //                     file.GetFormat() == 1);
   //                  tracks.TrackAt(pLyricEventsV2->m_iTrack)->seek_begin();
   //                  ((::music::midi::track *)tracks.TrackAt(pLyricEventsV2->m_iTrack))->GetLevel2Events(
   //                     &midiEventsLevel2,
   //                     (int32_t) pLyricEventsV2->m_iTrack,
   //                     file.GetFormat() == 1);
   //               }
   //            }
   //
   //            ::music::midi::util miditutil(get_app());
   //
   //            miditutil.PrepareNoteOnOffEvents(
   //               &noteOnHappenings,
   //               &noteOffEvents,
   //               (int32_t) pLyricEventsV2->m_iTrack,
   //               file.GetFormat(),
   //               &midiEvents,
   //               tickaaTokensTicks.operator()(i));
   //
   //            miditutil.PrepareLevel2Events(
   //               &eventsLevel2Beg,
   //               &eventsLevel2End,
   //               (int32_t) pLyricEventsV2->m_iTrack,
   //               file.GetFormat(),
   //               &midiEventsLevel2,
   //               tickaaTokensTicks.operator()(i));
   //
   //
   //            tickaaNoteOnPositions(i)     = noteOnHappenings.m_tickaEventsPosition;
   //            tickaaNoteOffPositions(i)    = noteOffEvents.m_tickaEventsPosition;
   //            tickaaBegPositions(i)        = eventsLevel2Beg.m_tickaEventsPosition;
   //            tickaaEndPositions(i)        = eventsLevel2End.m_tickaEventsPosition;
   //            pLyricEventsV2->m_dwaNotesData.copy(noteOnHappenings.m_dwaEventsData);
   //            pLyricEventsV2B->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
   //            pLyricEventsV2C->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
   //            pLyricEventsV2_->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
   //            midiEvents.remove_all();
   //            noteOnHappenings.remove_all();
   //            noteOffEvents.remove_all();
   //            midiEventsLevel2.remove_all();
   //            eventsLevel2Beg.remove_all();
   //            eventsLevel2End.remove_all();
   //            delete pMidiEventsV1;
   //         }
   //
   //         file.PositionToTime(
   //            ms2DNoteOnMillis,
   //            tickaaNoteOnPositions,
   //            0);
   //
   //         file.PositionToTime(
   //            ms2DNoteOffMillis,
   //            tickaaNoteOffPositions,
   //            0);
   //
   //         file.PositionToTime(
   //            ms2DBegMillis,
   //            tickaaBegPositions,
   //            0);
   //
   //         file.PositionToTime(
   //            ms2DEndMillis,
   //            tickaaEndPositions,
   //            0);
   //
   //
   //         ::ikaraoke::lyric_events_v1 *pLyricEventsV1;
   //
   //
   //         for(i = 0; i < tickaaTokensTicks.get_size(); i++)
   //         {
   //            pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEvents.get_at(i);
   //            staticdata.m_happeningstracks.add(pLyricEventsV2);
   //            file.TimeToPosition(
   //               pLyricEventsV2->m_tickaTokensPosition,
   //               ms2DTokensMillis(i),
   //               0);
   //            file.TimeToPosition(
   //               pLyricEventsV2->m_tickaNotesPosition,
   //               ms2DNoteOnMillis(i),
   //               0);
   //
   //            imedia_time time1(0);
   //            imedia_time time2(0);
   //
   //            pLyricEventsV2->m_timeaTokensPosition.CopySorted(
   //               ms2DTokensMillis(i),
   //               time1,
   //               time2);
   //
   //            pLyricEventsV2->m_timeaNotesDuration.Diff(
   //               ms2DNoteOffMillis(i),
   //               ms2DNoteOnMillis(i));
   //
   //            imedia_time time3(0);
   //            imedia_time time4(0);
   //
   //            pLyricEventsV2->m_timeaNotesPosition.CopySorted(
   //               ms2DNoteOnMillis(i),
   //               time3,
   //               time4);
   //
   //            imedia_time time5(I32_MAXIMUM);
   //
   //            pLyricEventsV2->m_timeaTokensDuration.ElementDiff(
   //               ms2DTokensMillis(i),
   //               time5);
   //
   //         }
   //
   //
   //         for(i = 0; i < tickaaTokensTicks.get_size(); i++)
   //         {
   //            pLyricEventsV1 = aaa_primitive_new ::ikaraoke::lyric_events_v1();
   //            pLyricEventsV1->m_iType = ikaraoke::EventAdvanceShow;
   //            pLyricEventsV1->m_iOrder = i;
   //            //staticdata.m_happeningsTracksForPositionCB.add(pLyricEventsV1);
   //            file.TimeToPosition(
   //               pLyricEventsV1->m_tickaTokensPosition,
   //               ms2DTokensMillis(i),
   //               -1000);
   //            //lyric_track * pLyricTrk = file.GetTracks().CreateLyricTrack();
   //            //pLyricTrk->Prepare(*pLyricEventsV1);
   //         }
   //
   //
   //         for(i = 0; i < tickaaTokensTicks.get_size(); i++)
   //         {
   //            pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEventsForScoring.get_at(i);
   //            staticdata.m_happeningsTracksForScoring.add(pLyricEventsV2);
   //            file.TimeToPosition(
   //               pLyricEventsV2->m_tickaTokensPosition,
   //               ms2DTokensMillis(i),
   //               0);
   //            file.TimeToPosition(
   //               pLyricEventsV2->m_tickaNotesPosition,
   //               ms2DNoteOnMillis(i),
   //               0);
   //
   //            imedia_time time1(-100);
   //            imedia_time time2(0);
   //
   //            pLyricEventsV2->m_timeaTokensPosition.CopySorted(
   //               ms2DTokensMillis(i),
   //               time1,
   //               time2);
   //
   //            pLyricEventsV2->m_timeaNotesDuration.Diff(
   //               ms2DNoteOffMillis(i),
   //               ms2DNoteOnMillis(i));
   //
   //            imedia_time time3(-100);
   //            imedia_time time4(0);
   //
   //            pLyricEventsV2->m_timeaNotesPosition.CopySorted(
   //               ms2DNoteOnMillis(i),
   //               time3,
   //               time4);
   //
   //            imedia_time time5(I32_MAXIMUM);
   //
   //            pLyricEventsV2->m_timeaTokensDuration.ElementDiff(
   //               ms2DTokensMillis(i),
   //               time5);
   //
   //            pLyricEventsV2->PrepareForScoring(this);
   //         }
   //
   //
   //
   //
   //
   //
   //
   //         for(i = 0; i < tickaaTokensTicks.get_size(); i++)
   //         {
   //            pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEventsForPositionCB.get_at(i);
   //            staticdata.m_happeningsTracksForPositionCB.add(pLyricEventsV2);
   //
   //            staticdata.m_happeningstracksV002.add(pLyricEventsV2);
   //
   //            file.TimeToPosition(
   //               pLyricEventsV2->m_tickaTokensPosition,
   //               ms2DTokensMillis(i),
   //               -100);
   //
   //            file.TimeToPosition(
   //               pLyricEventsV2->m_tickaNotesPosition,
   //               ms2DNoteOnMillis(i),
   //               -100);
   //
   //            imedia_time time1(-100);
   //            imedia_time time2(0);
   //
   //            pLyricEventsV2->m_timeaTokensPosition.CopySorted(
   //               ms2DTokensMillis(i),
   //               time1,
   //               time2);
   //
   //            pLyricEventsV2->m_timeaNotesDuration.Diff(
   //               ms2DNoteOffMillis(i),
   //               ms2DNoteOnMillis(i));
   //
   //            /*
   //            pLyricEventsV2->m_timeaNotesDuration.Diff(
   //            ms2DNoteOffMillis(i),
   //            ms2DNoteOnMillis(i));
   //            */
   //
   //
   //            imedia_time time3(-100);
   //            imedia_time time4(0);
   //
   //            pLyricEventsV2->m_timeaNotesPosition.CopySorted(
   //               ms2DNoteOnMillis(i),
   //               time3,
   //               time4);
   //
   //            imedia_time time5(I32_MAXIMUM);
   //
   //            pLyricEventsV2->m_timeaTokensDuration.ElementDiff(
   //               ms2DTokensMillis(i),
   //               time5);
   //
   //            pLyricEventsV2->PrepareForLyricsDisplay(this);
   //            //lyric_track * pLyricTrk = file.GetTracks().CreateLyricTrack();
   //            //pLyricTrk->Prepare(*pLyricEventsV2);
   //         }
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //         for(i = 0; i < tickaaTokensTicks.get_size(); i++)
   //         {
   //            pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEventsForBouncingBall.get_at(i);
   //            staticdata.m_happeningsTracksForBouncingBall.add(pLyricEventsV2);
   //
   //            file.TimeToPosition(
   //               pLyricEventsV2->m_tickaTokensPosition,
   //               ms2DTokensMillis(i),
   //               -100);
   //
   //            file.TimeToPosition(
   //               pLyricEventsV2->m_tickaNotesPosition,
   //               ms2DNoteOnMillis(i),
   //               -100);
   //
   //            imedia_time time1(-100);
   //            imedia_time time2(0);
   //
   //            pLyricEventsV2->m_timeaTokensPosition.CopySorted(
   //               ms2DTokensMillis(i),
   //               time1,
   //               time2);
   //
   //            pLyricEventsV2->m_timeaNotesDuration.Diff(
   //               ms2DEndMillis(i),
   //               ms2DBegMillis(i));
   //
   //            /*
   //            pLyricEventsV2->m_timeaNotesDuration.Diff(
   //            ms2DNoteOffMillis(i),
   //            ms2DNoteOnMillis(i));
   //            */
   //
   //            imedia_time time3(-100);
   //            imedia_time time4(0);
   //
   //            pLyricEventsV2->m_timeaNotesPosition.CopySorted(
   //               ms2DNoteOnMillis(i),
   //               time3,
   //               time4);
   //
   //            imedia_time time5(I32_MAXIMUM);
   //
   //            pLyricEventsV2->m_timeaTokensDuration.ElementDiff(
   //               ms2DTokensMillis(i),
   //               time5);
   //
   //            pLyricEventsV2->PrepareForBouncingBall(this);
   //         }
   //
   //      }
   //
   //      void sequence::Prepare(int32_t iTrack, ::ikaraoke::data & data)
   //      {
   //         ::music::midi::alsa::file & file = *this->file();
   //         ::music::midi::tracks & tracks = file.GetTracks();
   //         string_array_array_base & straa = data.GetStaticData().m_straaRawTokens;
   //         imedia_position_2darray position2a;
   //         int2a ia2TokenLine;
   //
   //
   //         ia2TokenLine.add_new();
   //
   //         tracks.WorkSeekBegin();
   //         tracks.WorkGetEmptyXFTokens(
   //            iTrack,
   //            straa,
   //            position2a,
   //            NULL);
   //
   //         Prepare(
   //            straa,
   //            position2a,
   //            iTrack,
   //            ia2TokenLine,
   //            data);
   //
   //      }
   //
   //      void sequence::Prepare(::ikaraoke::data & data)
   //      {
   //         ::music::midi::alsa::file & file = *this->file();
   //         ::music::midi::tracks & tracks = file.GetTracks();
   //         string_array_array_base & straa = data.GetStaticData().m_straaRawTokens;
   //         imedia_position_2darray position2a;
   //         int2a iaaTokenLine;
   //
   //         ::music::xf::info_headers xfihs;
   //         get_file()->GetTracks().GetXFInfoHeaders(&xfihs);
   //
   //         ::ikaraoke::static_data & staticdata = data.GetStaticData();
   //         string str;
   //
   //         // add Title
   //         staticdata.m_straTitleFormat.add("%0");
   //         staticdata.m_straaTitle.set_app(get_app());
   //         staticdata.m_straaTitle.add_new();
   //         staticdata.m_straaTitle[0].add(xfihs.m_strSongName);
   //
   //         if(xfihs.m_xfInfoHeader.m_straComposer.get_size() > 0)
   //         {
   //            // add Performer
   //            staticdata.m_straTitleFormat.add("Performer: %0");
   //            xfihs.m_xfInfoHeader.m_straPerformer.get_format_string(str, ", ");
   //            staticdata.m_straaTitle.add_new();
   //            staticdata.m_straaTitle[1].add(str);
   //
   //            // add Composer
   //            staticdata.m_straTitleFormat.add("Composer: %0");
   //            xfihs.m_xfInfoHeader.m_straComposer.get_format_string(str, ", ");
   //            staticdata.m_straaTitle.add_new();
   //            staticdata.m_straaTitle[1].add(str);
   //
   //
   //            //      staticdata.m_straPerformer = xfihs.m_xfInfoHeader.m_straPerformer;
   //            //    staticdata.m_straArtist = xfihs.m_xfInfoHeader.m_straPerformer;
   //         }
   //
   //         staticdata.m_dwDefaultCodePage = 1252; // Latin (Default of All Default Code Pages)
   //
   //         if(xfihs.m_xfaInfoHeaderLS.get_count())
   //         {
   //            staticdata.m_dwDefaultCodePage = ::music::xf::SymbolCharCodeToCodePage(xfihs.m_xfaInfoHeaderLS[0].m_strLanguage);
   //         }
   //
   //         tracks.WorkSeekBegin();
   //         //tracks.WorkGetXFTokens(staticdata.m_dwDefaultCodePage, straa, position2a, iaaTokenLine, NULL);
   //         tracks.WorkGetXFTokens((unsigned int) -1, straa, position2a, iaaTokenLine, NULL, false);
   //
   //         Prepare(
   //            straa,
   //            position2a,
   //            -1,
   //            iaaTokenLine,
   //            data);
   //
   //         tracks.WorkSeekBegin();
   //         tracks.WorkGetLongestXFLyrics(staticdata.m_strLyrics, false);
   //         tracks.WorkGetLongestXFLyrics(staticdata.m_strLyricsEx1, true);
   //
   //
   //
   //      }


         void sequence::GetPositionLength(imedia_position &position)
         {
            position = m_tkLength;
         }

         void sequence::buffer::Initialize(int32_t iSize, unsigned int dwUser)
         {
            m_storage.allocate(iSize);
            m_midihdr.lpData           = (char *) m_storage.get_data();
            m_midihdr.dwBufferLength   = (unsigned int) m_storage.get_size();
            m_midihdr.dwUser           = dwUser;
            m_bPrepared                = false;

         }

         void sequence::buffer_array::Initialize(int32_t iCount, int32_t iSize, unsigned int dwUser)
         {
            set_size(iCount);

            int32_t i;

            /*   for(int32_t i = 0; i < this->get_size() - 1; i++)
            {
            this->element_at(i).SetNextMidiHdr(this->element_at(i + 1).GetMidiHdr());
            }

            if(this->get_size() > 1)
            {
            this->element_at(get_upper_bound()).SetNextMidiHdr(this->element_at(0).GetMidiHdr());
            }
            else
            {
            this->element_at(0).SetNextMidiHdr(NULL);
            }*/

            for(i = 0; i < this->get_size(); i++)
            {
               this->element_at(i).Initialize(iSize, dwUser);
            }
         }

         void sequence::buffer_array::Reset()
         {
            for(int32_t i = 0; i < this->get_size(); i++)
            {
               this->element_at(i).Reset();
            }
         }

         void sequence::buffer::Reset()
         {
            m_midihdr.dwBytesRecorded  = 0;
            m_midihdr.dwFlags          = 0;
         }

         bool sequence::buffer::IsPrepared()
         {
            return m_bPrepared;
         }


   /*      ::e_status sequence::buffer::midiOutPrepareHeader(HMIDIOUT hmidiout)
         {
            ::e_status mmr = 0;
            if(hmidiout == NULL)
               return mmr;
            if(m_bPrepared)
               return mmr;
            mmr = ::midiOutPrepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr));
            if(mmr == ::success)
            {
               m_bPrepared = true;
            }
            return mmr;
         }

         ::e_status sequence::buffer::midiOutUnprepareHeader(HMIDIOUT hmidiout)
         {
            ::e_status mmr = 0;
            if(hmidiout == NULL)
               return mmr;
            if(!m_bPrepared)
               return mmr;
            mmr = ::midiOutUnprepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr));
            if(mmr == ::success)
            {
               m_bPrepared = false;
            }
            return mmr;
         }

         ::e_status sequence::buffer_array::midiOutUnprepareHeader(HMIDIOUT hmidiout)
         {
            ::e_status mmr = ::success;

            for (int32_t i = 0; i < this->get_size(); i++)
            {
               ::e_status mmrBuffer = this->element_at(i).midiOutUnprepareHeader(hmidiout);
               if(mmrBuffer != ::success)
               {
                  mmr = mmrBuffer;
               }
            }
            return mmr;
         }

         ::e_status sequence::buffer_array::midiOutPrepareHeader(HMIDIOUT hmidiout)
         {
            ::e_status mmrc = ::success;
            for(int32_t i = 0; i < this->get_size(); i++)
            {
               mmrc = this->element_at(i).midiOutPrepareHeader(
                  hmidiout);
               if(mmrc != ::success)
               {
                  for(; i >= 0; i--)
                  {
                     this->element_at(i).midiOutUnprepareHeader(hmidiout);
                  }
                  return mmrc;
               }
            }
            return mmrc;
         }*/

         void sequence::buffer::SetNextMidiHdr(LPMIDIHDR lpNext)
         {
            m_midihdr.lpNext = lpNext;
         }


         ::e_status sequence::buffer::midiStreamOut(seq_context_t * hmidiout)
         {
   /*         ASSERT(hmidiout != NULL);
            return ::midiStreamOut(hmidiout, &m_midihdr, sizeof(m_midihdr));*/
            return ::success;
         }

         ::e_status sequence::buffer_array::midiStreamOut(seq_context_t * hmidiout)
         {
         /*
            ::e_status mmrc = ::success;
            for(int32_t i = 0; i < this->get_size(); i++)
            {
               mmrc = this->element_at(i).midiStreamOut(
                  hmidiout);
               if(mmrc != ::success)
               {
                  //         for(; i >= 0; i--)
                  //       {
                  //        this->element_at(i).midiOutUnprepareHeader(hmidiout);
                  //   }
                  return mmrc;
               }
            }
            return mmrc;*/
            return ::success;
         }


   //      void sequence::MuteAll(bool bMute, int32_t iExcludeTrack)
   //      {
   //         bool bPlay = IsPlaying();
   //         imedia_position ticks = 0;
   //         if(bPlay)
   //         {
   //            ticks = get_position_ticks();
   //            Stop();
   //         }
   //         get_file()->MuteAll(bMute, iExcludeTrack);
   //         if(bPlay)
   //         {
   //            m_pthread->PrerollAndWait(ticks);
   //            Start();
   //         }
   //      }
   //
   //      void sequence::MuteTrack(int32_t iIndex, bool bMute)
   //      {
   //         bool bPlay = IsPlaying();
   //         imedia_position ticks = 0;
   //         if(bPlay)
   //         {
   //            ticks = get_position_ticks();
   //            Stop();
   //         }
   //         get_file()->MuteTrack(iIndex, bMute);
   //         if(bPlay)
   //         {
   //            m_pthread->PrerollAndWait(ticks);
   //            Start();
   //         }
   //      }

         imedia_position sequence::GetQuarterNote()
         {
            return get_file()->m_pFileHeader->GetQuarterNoteTicks();
         }


   //      int32_t sequence::GetDefaultCodePage()
   //      {
   //         return 1252;
   //      }


         bool sequence::IsSettingPosition()
         {
            return m_flags.is_signalized(::music::midi::sequence::e_flag_setting_position);
         }


         void sequence::SetSettingPositionFlag(bool bSet)
         {
            if(bSet)
               m_flags.signalize(::music::midi::sequence::e_flag_setting_position);
            else
               m_flags.unsignalize(::music::midi::sequence::e_flag_setting_position);
         }

         ::music::midi::sequence::happening * sequence::create_new_event(::music::midi::sequence::e_happening ehappening, LPMIDIHDR lpmidihdr)
         {

            ASSERT(this != NULL);

            happening * pevent          = aaa_primitive_new happening();

            pevent->m_ehappening        = ehappening;
            pevent->m_psequence     = this;
            pevent->m_lpmh          = lpmidihdr;

            return pevent;

         }


   //      ::music::midi::happening * sequence::seq_get_next_event()
   //      {
   //
   //         ::music::midi::happening * pevent = NULL;
   //
   //         array < ::music::midi::happening * > & evptra = m_evptra;
   //
   //         if(evptra.get_size() > 0)
   //         {
   //            pevent = evptra[0];
   //            evptra.remove_at(0);
   //         }
   //         else
   //         {
   //
   //            imedia_position tickMax = ::numeric_info<imedia_position>::get_maximum_value  ();
   //
   //            get_file()->WorkGetNextEvent(pevent, tickMax, false);
   //
   //         }
   //
   //         return pevent;
   //
   //      }


   //      int sequence::seq_dump()
   //      {
   //
   //
   //         ::music::midi::happening * pevent = seq_get_next_event();
   //
   //         if(pevent == NULL)
   //         {
   //
   //            return -1;
   //
   //         }
   //
   //         array < ::music::midi::happening * > & evptra = m_evptra;
   //
   //         m_tkPosition = pevent->m_tkPosition;
   //
   ////         int iBufferIter = 1;
   ////
   ////         for(::collection::index iBuffer = 0; iBuffer < iBufferIter && m_bPlay; iBuffer++)
   ////         {
   ////
   ////            int iCount = 0;
   ////
   ////            int iMaxEventGroup = 8;
   ////
   ////            while(pevent != NULL && m_bPlay)
   ////            {
   ////
   //               if(pevent->GetType() == ::music::midi::NoteOn && pevent->GetNoteVelocity() > 0)
   //               {
   //
   //                  ::music::midi::happening * peventOff = NULL;
   //
   //                  bool bFound = false;
   //
   //                  for(::collection::index i = 0; i < evptra.get_size(); i++)
   //                  {
   //
   //                     peventOff = evptra[i];
   //
   //                     if(pevent->on_match_off(peventOff))
   //                     {
   //
   //                        bFound = true;
   //
   //                        break;
   //
   //                     }
   //
   //                  }
   //
   //                  if(!bFound)
   //                  {
   //
   //                     while(true)
   //                     {
   //
   //                        if(get_file()->WorkGetNextEvent(peventOff, ::numeric_info< imedia_position >::get_maximum_value  (), false) != ::music::success)
   //                           break;
   //
   //                        if(pevent->on_match_off(peventOff))
   //                        {
   //
   //                           bFound = true;
   //
   //                           break;
   //
   //                        }
   //
   //                        evptra.add(peventOff);
   //
   //                     }
   //
   //                  }
   //
   //                  if(bFound)
   //                  {
   //
   //                     snd_seq_event_t ev;
   //
   //                     imedia_position tickPosition = pevent->m_tkPosition - m_tkPrerollBase;
   //
   //                     seq_midi_event_init(m_pseq, &ev, tickPosition, pevent->GetTrack());
   //
   //                     imedia_position tickDuration = peventOff->m_tkPosition - pevent->m_tkPosition;
   //
   //                     seq_midi_note(
   //                        m_pseq,
   //                        &ev,
   //                        pevent->GetTrack(),
   //                        pevent->GetNotePitch(),
   //                        pevent->GetNoteVelocity(),
   //                        tickDuration,
   //                        peventOff->GetNoteVelocity());
   //
   ////                     iCount++;
   //
   //                  }
   //
   //               }
   //               else
   //               {
   //
   //                  //iCount += seq_play(pevent);
   //                  seq_play(pevent);
   //
   //               }
   //
   ////               if(iCount >= iMaxEventGroup && pevent != NULL && pevent->m_tkPosition != m_tkPosition)
   ////                  break;
   ////
   ////               pevent = seq_get_next_event();
   ////
   ////            }
   ////
   ////            if(pevent != NULL)
   ////            {
   ////
   ////               m_tkPosition = pevent->m_tkPosition;
   ////
   ////               m_iaBuffered.add(m_tkPosition);
   ////
   ////               m_iBuffered++;
   ////
   ////               //seq_midi_echo(m_pseq, m_tkPosition - m_tkPrerollBase);
   ////
   ////            }
   ////            else
   ////            {
   ////
   ////               m_iaBuffered.add(get_file()->m_tkLength);
   ////
   ////               m_iBuffered++;
   ////
   ////               //seq_midi_echo(m_pseq, get_file()->m_tkLength - m_tkPrerollBase);
   ////
   ////            }
   ////
   ////            if(m_bPlay)
   ////            {
   ////
   ////               //snd_seq_drain_output(m_pseq->handle);
   ////
   ////            }
   ////
   //////////            if(snd_seq_client_pool_get_output_free (m_pseq->ctlist->get_head()) < 64)
   //////////            {
   //////////
   //////////               break;
   //////////
   //////////            }
   //
   ////         }
   ////
   ////         if(!m_bPlay)
   ////         {
   ////
   ////            return -1;
   ////
   ////         }
   //
   //         return 1;
   //
   //      }
   //
   //
   //      void sequence::seq_run()
   //      {
   //
   //         m_bPlay = true;
   //
   //         seq_start_timer(m_pseq);
   //
   //         int npfd = snd_seq_poll_descriptors_count(m_pseq->handle, POLLOUT);
   //
   //         struct pollfd  * pfd = (struct pollfd *)alloca(npfd * sizeof(struct pollfd));
   //
   //         snd_seq_poll_descriptors(m_pseq->handle, pfd, npfd, POLLOUT);
   //
   //         if(seq_dump() >= 0)
   //         {
   //
   //         while (m_bPlay)
   //         {
   //
   //            if (poll(pfd, npfd, 100000) > 0)
   //            {
   //
   //               if(seq_dump()< 0)
   //               {
   //
   //                  break;
   //
   //               }
   //
   //            }
   //
   //         }
   //         }
   //
   //                  if(m_pseq != NULL)
   //                  {
   //
   //                     seq_stop_timer(m_pseq);
   //
   //                     seq_free_context(m_pseq);
   //
   //                     m_pseq = NULL;
   //
   //                  }
   //
   //                  m_happeningMidiPlaybackEnd.set_happening();
   //
   //                  sequence_thread * pthread = dynamic_cast < sequence_thread * > (m_pthread);
   //
   //                  pthread->PostMidiSequenceEvent(this, ::music::midi::sequence::e_event_midi_playback_end);
   //
   //                  return;
   ////         seq_start_timer(m_pseq);
   ////
   ////         snd_seq_event_t * pev = NULL;
   ////
   ////         imedia_position pos = 0;
   ////
   ////         while(true)
   ////         {
   ////
   ////            get_position(pos);
   ////
   ////            while(m_iaBuffered.get_count() > 0 && m_iaBuffered[0] <= pos)
   ////            {
   ////
   ////               m_iaBuffered.remove_at(0);
   ////
   ////            }
   ////
   ////            if(seq_dump() < 0 || !m_bPlay)
   ////            {
   ////
   ////               if(m_iaBuffered.get_count() <= 0 || !m_bPlay)
   ////               {
   ////
   ////                  if(m_pseq != NULL)
   ////                  {
   ////
   ////                     seq_stop_timer(m_pseq);
   ////
   ////                     seq_free_context(m_pseq);
   ////
   ////                     m_pseq = NULL;
   ////
   ////                  }
   ////
   ////                  m_happeningMidiPlaybackEnd.set_happening();
   ////
   ////                  sequence_thread * pthread = dynamic_cast < sequence_thread * > (m_pthread);
   ////
   ////                  pthread->PostMidiSequenceEvent(this, ::music::midi::sequence::e_event_midi_playback_end);
   ////
   ////                  return;
   ////
   ////               }
   ////
   ////               Sleep(84);
   ////
   ////            }
   ////            else
   ////            {
   ////
   ////               Sleep(5);
   ////
   ////            }
   ////
   ////         }
   //
   //      }


   //      int sequence::seq_play(::music::midi::happening * pevent)
   //      {
   //
   //         snd_seq_event_t ev;
   //
   //         seq_midi_event_init(m_pseq, &ev, pevent->m_tkPosition - m_tkPrerollBase, pevent->GetTrack());
   //
   //         int iCount = 1;
   //
   //         switch (pevent->GetType())
   //         {
   ///*         case ::music::midi::NoteOn:
   //            seq_midi_note_on(m_pseq, &ev, pevent->GetTrack(), pevent->GetNotePitch(), pevent->GetNoteVelocity());
   //            break;
   //         case ::music::midi::NoteOff:
   //            seq_midi_note_off(m_pseq, &ev, pevent->GetTrack(), pevent->GetNotePitch(), pevent->GetNoteVelocity());
   //            break;*/
   //         case ::music::midi::NoteOff:
   //            break;
   //         case ::music::midi::PolyPressure:
   //            seq_midi_keypress(m_pseq, &ev, pevent->GetTrack(), pevent->GetNotePitch(), pevent->GetNoteVelocity());
   //            break;
   //         case ::music::midi::ControlChange:
   //            seq_midi_control(m_pseq, &ev, pevent->GetTrack(), pevent->GetController(), pevent->GetControllerValue());
   //            break;
   //         case ::music::midi::ProgramChange:
   //            seq_midi_program(m_pseq, &ev, pevent->GetTrack(), pevent->GetProgram());
   //            break;
   //         case ::music::midi::PitchBend:
   //            seq_midi_pitchbend(m_pseq, &ev, pevent->GetTrack(),((int) pevent->GetPitchBendLevel())-8192);
   //            break;
   //         case ::music::midi::ChanPressure:
   //            seq_midi_chanpress(m_pseq, &ev, pevent->GetTrack(), pevent->GetChannelPressure());
   //            break;
   //         case 0xf0:
   //            {
   //               switch(pevent->GetFullType())
   //               {
   //               case ::music::midi::Meta:
   //                  {
   //                     switch(pevent->GetMetaType())
   //                     {
   //                     case ::music::midi::MetaTempo:
   //                        {
   //                           unsigned int dwTempo = (((unsigned int)pevent->GetData()[0])<<16)|
   //                           (((unsigned int)pevent->GetData()[1])<<8)|
   //                           ((unsigned int)pevent->GetData()[2]);
   //                           dwTempo = (unsigned int) ((double) dwTempo / get_file()->GetTempoShiftRate());
   //
   //                           seq_midi_tempo(m_pseq, &ev, dwTempo);
   //                        }
   //                        break;
   //                     case ::music::midi::MetaLyric:
   //                     case ::music::midi::MetaKarLyric:
   //                     case ::music::midi::MetaTimeSig:
   //                     case ::music::midi::MetaKeySig:
   //                     //case MD_TYPE_SMPTEOFFSET:
   //                        iCount = 0;
   //                        /* Ones that have no sequencer action */
   //                        break;
   //                     default:
   //                        iCount = 0;
   //                        printf("warning: play: not implemented yet Meta %d\n", pevent->GetMetaType());
   //                        break;
   //                     }
   //                  }
   //                  break;
   //               case ::music::midi::SysEx:
   //               case ::music::midi::SysExEnd:
   //                  seq_midi_sysex(m_pseq, &ev, pevent->GetFullType(), pevent->GetData(), pevent->GetDataSize());
   //                  break;
   //               default:
   //                  iCount = 0;
   //                  printf("warning: play: not implemented yet %d\n", pevent->GetFullType());
   //                  break;
   //               }
   //            }
   //            break;
   //         default:
   //            iCount = 0;
   //            printf("warning: play: not implemented yet %d\n", pevent->GetType());
   //            break;
   //         }
   //
   //         return iCount;
   //
   //      }


      } // namespace alsa


   } // namespace midi


} // namespace music









