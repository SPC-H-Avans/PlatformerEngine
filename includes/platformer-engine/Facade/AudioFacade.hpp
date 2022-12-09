#ifndef PLATFORMER_ENGINE_AUDIOFACADE_HPP
#define PLATFORMER_ENGINE_AUDIOFACADE_HPP

#include <map>
#include <functional>
#include <memory>
#include "SDL_mixer.h"

namespace platformer_engine {
    class AudioFacade {
    public:
        ~AudioFacade();

        /**
         * @brief Quit the audio system
         */
        void Quit();

        /**
         * @brief Set the volume of the audio system (use this before playing music)
         * @param volume The volume to set
         */
        void SetVolume(int volume);

        /**
         * @brief Set the volume of the music (that is already playing)
         * @param volume The volume to set
         */
        void SetVolumeMusic(int volume);

        /**
         * @brief Load a music file
         * @param musicName The name of the music
         * @param fileName The file name of the music file
         */
        void LoadMusic(const std::string &musicName, const std::string &fileName);

        /**
         * @brief Load a sound file
         * @param soundName The name of the sound
         * @param fileName The file name of the sound file
         */
        void LoadSound(const std::string &soundName, const std::string &fileName);

        /**
         * @brief Play a music file
         * @param musicName The name of the music
         * @param loopMusic Whether to loop the music
         */
        void PlayMusic(const std::string &musicName, bool loopMusic);

        /**
         * @brief Play a sound file
         * @param soundName The name of the sound
         */
        void PlaySound(const std::string &soundName);

        /**
         * @brief Toggle the play state of the music
         */
        void TogglePlay();

        /**
         * @brief Stop the music
         */
        void StopMusic();

        AudioFacade();

    private:

        std::map<std::string, std::unique_ptr<Mix_Music, std::function<void(
                Mix_Music * )>>> _music;
        std::map<std::string, std::unique_ptr<Mix_Chunk, std::function<void(
                Mix_Chunk * )>>> _sounds;
        int _volume = MIX_MAX_VOLUME;
    };


}

#endif //PLATFORMER_ENGINE_AUDIOFACADE_HPP
