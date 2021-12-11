#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace alsa
      {


         factory_exchange::factory_exchange()
         {

            //create_factory < sequence, ::music::midi::sequence > ();
            //create_factory < file, ::music::midi::file > ();
            //create_factory < sequence_thread, ::music::midi::sequence_thread > ();
            //create_factory < player, ::music::midi::player > ();
            // create_factory < ::music::midi_alsa::player::player_interface , ::music::midi::player::player_interface > ();
            create_factory < midi, ::music::midi::midi > ();

         }


         factory_exchange::~factory_exchange()
         {
         }


      } // namespace alsa


   } // namespace midi


} // namespace music


extern "C"
void music_midi_alsa_factory_exchange(factory_map * pfactorymap)
{

   //::music::midi::alsa::factory_exchange factoryexchange();
   pfactorymap->create_factory < ::music::midi::alsa::midi, ::music::midi::midi > ();

}









