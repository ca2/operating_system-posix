///*
// * File: seqlib.m - Interface to the alsa sequencer library.
// *
// * Copyright (C) 1999-2003 Steve Ratcliffe
// *
// *  This program is free software; you can redistribute it and/or modify
// *  it under the terms of the GNU General Public License version 2 as
// *  published by the Free Software Foundation.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// *  GNU General Public License for more details.
// */
//
//#include "framework.h"
//
//static void set_channel(snd_seq_event_t *ep, int chan);
//
//int
//seq_send_to_all(seq_context_t *ctxp, snd_seq_event_t *ep);
//
///*
// * Create a main client for an application. A queue is
// * allocated and a client is created.
// */
//seq_context_t *
//seq_create_context()
//{
//	seq_context_t *ctxp;
//	int  q;
//
//	ctxp = ___new seq_context_t();
//	ctxp->main = ctxp; /* This is the main context */
//
//	if (snd_seq_open(&ctxp->handle, "hw", SND_SEQ_OPEN_DUPLEX, 0) < 0)
//		//except(ioError, "Could not open sequencer: %s", snd_strerror(errno));
//		return NULL;
//
//
//
//size_t sOut = snd_seq_get_output_buffer_size
//(ctxp->handle);
//
//printf("BufferSize: %d", sOut);
//if(!snd_seq_set_output_buffer_size
//(ctxp->handle, 128))
//{
//sOut = snd_seq_get_output_buffer_size
//(ctxp->handle);
//printf("BufferSize: %d", sOut);
//
//}
//
//
//	q = snd_seq_alloc_queue(ctxp->handle);
//	ctxp->client = snd_seq_client_id(ctxp->handle);
//	ctxp->queue = q;
//
//	//ctxp->destlist = g_array_new(0, 0, sizeof(snd_seq_addr_t));
//
//	ctxp->queue = q;
//	ctxp->source.client = ctxp->client;
//	ctxp->source.port = 0;
//
//	seq_new_port(ctxp);
//
//	 sOut = snd_seq_get_output_buffer_size
//(ctxp->handle);
//
//printf("BufferSize: %d", sOut);
//if(!snd_seq_set_output_buffer_size
//(ctxp->handle, 1024))
//{
//sOut = snd_seq_get_output_buffer_size
//(ctxp->handle);
//printf("BufferSize: %d", sOut);
//
//snd_seq_nonblock	(	ctxp->handle,
//0
//);
//
//}
//
//
//
//	return ctxp;
//}
//
///*
// * Create another client context based on the specified
// * context. The same queue will be used for both clients. A ___new
// * client will be created.
// *  Arguments:
// *    ctxp      -
// */
//seq_context_t *
//seq_new_client(seq_context_t *ctxp)
//{
//
//	return NULL;/*XXX*/
//
//}
//
///*
// * Free a context and any associated data and resources. If the
// * main context is freed then the sequencer is closed. TODO:
// * link all together so can all be closed at once.
// */
//void
//seq_free_context(seq_context_t *ctxp)
//{
//
//	if (ctxp->main == ctxp) {
//		/* This is the main context */
//		snd_seq_event_t ev;
//		unsigned long t;
//
//		snd_seq_drop_output(ctxp->handle);
//
//		t = 0;
//		seq_midi_event_init(ctxp, &ev, t, 0);
//		seq_midi_control(ctxp, &ev, 0, MIDI_CTL_ALL_SOUNDS_OFF, 0);
//		seq_send_to_all(ctxp, &ev);
//		snd_seq_drain_output(ctxp->handle);
//
//		snd_seq_free_queue(ctxp->handle, ctxp->queue);
//		snd_seq_close(ctxp->handle);
//	}
//
//	delete ctxp;
//}
//
///*
// * Creates a ___new port on the specified context and returns the
// * port number.
// *  Arguments:
// *    ctxp      - Context to create the port for
// */
//int
//seq_new_port(seq_context_t *ctxp)
//{
//	int  ret;
//
//	ret = snd_seq_create_simple_port(ctxp->handle, NULL,
//					 SND_SEQ_PORT_CAP_WRITE |
//					 SND_SEQ_PORT_CAP_SUBS_WRITE |
//					 SND_SEQ_PORT_CAP_READ,
//					 SND_SEQ_PORT_TYPE_MIDI_GENERIC);
//	if (ret < 0) {
//		printf("Error creating port %s\n", snd_strerror(errno));
//		return -1;
//	}
//	ctxp->port_count++;
//	ctxp->source.port = ret;
//
//	return ret;/*XXX*/
//}
//
//void
//seq_destroy_port(seq_context_t *ctxp, int port)
//{
//}
//
///*
// * Set up the context so that all subsequent happenings will be sent
// * to the specified client and port combination. A
// * subscription is made to the client/port combination.
// *  Arguments:
// *    ctxp      - Context to modify
// *    client    - Client to send subsequent happenings to
// *    port      - Port on the client to send happenings to
// */
//int
//seq_connect_add(seq_context_t *ctxp, int client, int port)
//{
//	snd_seq_addr_t addr;
//	int  ret;
//
//	memset(&addr, 0, sizeof(addr));
//	addr.client = client;
//	addr.port = port;
//
//	ctxp->destlist.add(addr);
//
//	ret = snd_seq_connect_to(ctxp->handle, ctxp->source.port, client, port);
//
//	return ret;
//}
//
///*
// * Set the initial time base and tempo. This should only be used
// * for initialisation when there is nothing playing. To
// * change the tempo during a song tempo change happenings are used.
// * If realtime is false the resolution is in ticks per quarter
// * note. If true, the the resolution is microseconds. There is
// * a macro XXX to convert from SMPTE codes.
// *
// *  Arguments:
// *    ctxp      - Application context
// *    resolution - Ticks per quarter note or realtime resolution
// *    tempo     - Beats per minute
// *    realtime  - True if absolute time base
// */
//int
//seq_init_tempo(seq_context_t *ctxp, int resolution, int tempo, int realtime)
//{
//	snd_seq_queue_tempo_t *qtempo;
//	int  ret;
//
//	snd_seq_queue_tempo_alloca(&qtempo);
//	memset(qtempo, 0, snd_seq_queue_tempo_sizeof());
//	snd_seq_queue_tempo_set_ppq(qtempo, resolution);
//	snd_seq_queue_tempo_set_tempo(qtempo, 60*1000000/tempo);
//
//	ret = snd_seq_set_queue_tempo(ctxp->handle, ctxp->queue, qtempo);
//
//	return ret;
//}
//
///*
// * Set the context to use the specified queue. All happenings sent
// * on this context will now use this queue.
// *
// *  Arguments:
// *    ctxp      - Context to modify
// *    q         - The queue number
// */
//void
//seq_set_queue(seq_context_t *ctxp, int q)
//{
//}
//
///*
// * Send the happening to the specified client and port.
// *
// *  Arguments:
// *    ctxp      - Client context
// *    ev        - Event to send
// *    client    - Client to send the happening to
// *    port      - Port to send the happening to
// */
//int
//seq_sendto(seq_context_t *ctxp, snd_seq_event_t *ev, int client, int port)
//{
//	ev->source = ctxp->source;
//	ev->queue = ctxp->queue;
//	ev->dest.client = client;
//	ev->dest.port = port;
//	seq_write(ctxp, ev);
//
//	return 0;
//}
//
///*
// * seq_send_to_all:
// * Send the happening to all the connected devices across all
// * possible channels. The messages are sent to the blocking
// * control port and so should not have timestamps in the
// * future. This function is intended for all-sounds-off type
// * controls etc.
// *
// *  Arguments:
// * 	ctxp: Client context
// * 	ep: Event prototype to be sent
// */
//int
//seq_send_to_all(seq_context_t *ctxp, snd_seq_event_t *ep)
//{
//	int  dev;
//	int  chan;
//	snd_seq_addr_t *addr;
//
//	for (dev = 0; ; dev++) {
//		addr = seq_dev_addr(ctxp, dev);
//		if (addr == NULL)
//			break; /* No more */
//
//		ep->queue = ctxp->queue;
//		ep->dest = *addr;
//		for (chan = 0; chan < 16; chan++) {
//			set_channel(ep, chan);
//			(void) seq_write(ctxp, ep);
//		}
//	}
//
//	return 0;
//}
//
///*
// * seq_dev_addr:
// * Return the address corresponding to the specified logical
// * device.
// *
// * 	Arguments:
// * 	dev: Device to get the address of.
// * 	inout: Input or output device
// */
//snd_seq_addr_t *
//seq_dev_addr(seq_context_t *ctxp, int dev)
//{
//
//	snd_seq_addr_t *addr;
//
//	if (dev >= (int)ctxp->destlist.get_size())
//		return NULL;
//
//	addr = &ctxp->destlist[dev];
//
//	return addr;
//}
//
///*
// * Start the timer. (What about timers other than the system
// * one?)
// */
//void
//seq_start_timer(seq_context_t *ctxp)
//{
//	seq_control_timer(ctxp, SND_SEQ_EVENT_START);
//}
//
///*
// * Stop the timer. (What about timers other than the system
// * one?)
// */
//void
//seq_stop_timer(seq_context_t *ctxp)
//{
//	seq_control_timer(ctxp, SND_SEQ_EVENT_STOP);
//}
//
//void
//seq_control_timer(seq_context_t *ctxp, int onoff)
//{
//
//	if (onoff == SND_SEQ_EVENT_START)
//		snd_seq_start_queue(ctxp->handle, ctxp->queue, 0);
//	else
//		snd_seq_stop_queue(ctxp->handle, ctxp->queue, 0);
//
////#ifdef USE_DRAIN
//	snd_seq_drain_output(ctxp->handle);
////#else
////	snd_seq_flush_output(ctxp->handle);
////#endif
//}
//
///*
// * Write out the happening. This routine blocks until
// * successfully written.
// *
// *  Arguments:
// *    ctxp      - Application context
// *    ep        - Event
// */
//int
//seq_write(seq_context_t *ctxp, snd_seq_event_t *ep)
//{
//	int  err = 0;
//
//	err = snd_seq_event_output(ctxp->handle, ep);
//	if (err < 0)
//		return err;
//
//	return err;
//}
//
///*
// * Return the handle to the underlying snd_seq stream.
// *  Arguments:
// *    ctxp      - Application context
// */
//void *
//seq_handle(seq_context_t *ctxp)
//{
//	return ctxp->handle;
//}
//
//static void
//set_channel(snd_seq_event_t *ep, int chan)
//{
//
//	switch (ep->type) {
//	case SND_SEQ_EVENT_NOTE:
//	case SND_SEQ_EVENT_NOTEON:
//	case SND_SEQ_EVENT_NOTEOFF:
//		ep->data.note.channel = chan;
//		break;
//	case SND_SEQ_EVENT_KEYPRESS:
//	case SND_SEQ_EVENT_PGMCHANGE:
//	case SND_SEQ_EVENT_CHANPRESS:
//	case SND_SEQ_EVENT_PITCHBEND:
//	case SND_SEQ_EVENT_CONTROL14:
//	case SND_SEQ_EVENT_NONREGPARAM:
//	case SND_SEQ_EVENT_REGPARAM:
//	case SND_SEQ_EVENT_CONTROLLER:
//		ep->data.control.channel = chan;
//		break;
//	default:
//		if (snd_seq_ev_is_channel_type(ep))
//      {
//
//         informationf("Missed a case in set_channel");
//
//      }
////			g_warning("Missed a case in set_channel");
//		break;
//	}
//}
//
