# SunOS audio backends

SunOS builds provide both `audio_sunaudio` (Sun audio API, /dev/audio) and
`audio_oss` (OSS API, /dev/dsp). The CMake cache string `default_audio`
offers both values and defaults to `audio_sunaudio`.

On OpenIndiana, install the development headers for both APIs with:
`sudo pkg install system/header/header-audio`.

To override the default for an application, put `sunaudio` or `oss` in
`appconfig://audio.txt` and restart the application. The full target names
`audio_sunaudio` and `audio_oss` are also accepted. An empty or unknown
value falls back to the CMake default.

Both backends honor ~/audio_device.txt, then AUDIODEV, then their own
default device. Remove a backend-specific device override when switching APIs.

Both modules inherit wave::buffered_wave_out in the platform-independent
audio component. Each implements its own device operations; OSS does not
include or link the Sun audio backend. It supports playback,
not capture. On illumos, pause drains queued samples before pausing further
submissions, because SETTRIGGER is a compatibility no-op.

NetBSD's audio_sunaudio retains audiodev/drvctl discovery and proplib.
The SunOS path uses AUDIO_SETINFO/GETINFO and STREAMS I_FLUSH instead of
NetBSD-specific format, mode, and blocksize controls.
