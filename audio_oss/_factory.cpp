#include "platform.h"
#include "wave_out.h"

__FACTORY_EXPORT void audio_oss_factory(::factory::factory * pfactory)
{
   pfactory->add_factory_item<::multimedia::audio_oss::wave_out, ::wave::out>();
}
