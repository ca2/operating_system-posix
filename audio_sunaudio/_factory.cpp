#include "framework.h"
//#include "wave_in.h"
#include "wave_out.h"


__FACTORY_EXPORT void audio_sunaudio_factory(::factory::factory * pfactory)
{

   //pfactory->add_factory_item < ::multimedia::audio_alsa::wave_in  , ::wave::in                  > ();

   pfactory->add_factory_item < ::multimedia::audio_sunaudio::wave_out ,::wave::out                 > ();

}



