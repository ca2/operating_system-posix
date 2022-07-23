#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


__FACTORY_EXPORT void audio_alsa_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::multimedia::audio_alsa::wave_in  , ::wave::in                  > ();

   pfactory->add_factory_item < ::multimedia::audio_alsa::wave_out ,::wave::out                 > ();

}



