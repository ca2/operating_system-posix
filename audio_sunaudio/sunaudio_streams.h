#pragma once

// Keep STREAMS system types out of translation units including ca2 headers.
extern "C" int audio_sunaudio_flush_stream(int fd);
