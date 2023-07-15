#include "framework.h"
#include "midi.h"

#if !BROAD_PRECOMPILED_HEADER
//#include "acme/_defer.h"
#endif
//
//namespace music
//{
//
//
//   namespace midi
//   {
//
//
//      namespace alsa
//      {
//
//
//         factory_exchange::factory_exchange()
//         {
//
//            //create_factory < sequence, ::music::midi::sequence > ();
//            //create_factory < file, ::music::midi::file > ();
//            //create_factory < sequence_thread, ::music::midi::sequence_thread > ();
//            //create_factory < player, ::music::midi::player > ();
//            // create_factory < ::music::midi_alsa::player::player_interface , ::music::midi::player::player_interface > ();
//            create_factory < midi, ::music::midi::midi > ();
//
//         }
//
//
//         factory_exchange::~factory_exchange()
//         {
//         }
//
//
//      } // namespace alsa
//
//
//   } // namespace midi
//
//
//} // namespace music
//

__FACTORY_EXPORT void music_midi_alsa_factory(factory::factory * pfactory)
{

   //::music::midi::alsa::factory_exchange factoryexchange();
   pfactory->add_factory_item < ::music::midi::alsa::midi, ::music::midi::midi > ();

}









