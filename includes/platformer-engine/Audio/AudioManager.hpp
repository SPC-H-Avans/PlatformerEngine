#ifndef PLATFORMER_ENGINE_AUDIOMANAGER_HPP
#define PLATFORMER_ENGINE_AUDIOMANAGER_HPP

#include "Facade/AudioFacade.hpp"

namespace platformer_engine {
    class AudioManager {
    public:
        static auto GetInstance() -> AudioManager & {
            static AudioManager instance;
            return instance;
        }

        AudioManager(AudioManager const &) = delete;

        void operator=(AudioManager const &) = delete;

        AudioManager(AudioManager &&other) = delete;

        AudioManager &operator=(AudioManager &&other) = delete;

        ~AudioManager() = default;

        /**
         * @brief Set the volume of the audio system (use this before playing music)
         * @param volume The volume to set
         */
        void SetVolume(int volume) {
            _audioFacade->SetVolume(volume);
        }

        auto GetVolume() -> int{
            return _audioFacade->getVolume();
        }

        /**
         * @brief Set the volume of the music (that is already playing)
         * @param volume The volume to set
         */
        void SetVolumeMusic(int volume) {
            _audioFacade->SetVolumeMusic(volume);
        }

        /**
        * @brief Load a music file
        * @param musicName The name of the music
        * @param fileName The file name of the music file
        */
        void LoadMusic(const std::string &musicName, const std::string &fileName) {
            _audioFacade->LoadMusic(musicName, fileName);
        }

        /**
        * @brief Load a sound file
        * @param soundName The name of the sound
        * @param fileName The file name of the sound file
        */
        void LoadSound(const std::string &soundName, const std::string &fileName) {
            _audioFacade->LoadSound(soundName, fileName);
        }

        /**
         * @brief Play a music file
         * @param musicName The name of the music
         * @param loopMusic Whether to loop the music
         */
        void PlayMusic(const std::string &musicName, bool loopMusic) {
            _audioFacade->PlayMusic(musicName, loopMusic);
        }

        /**
         * @brief Play a sound file
         * @param soundName The name of the sound
         */
        void PlaySound(const std::string &soundName) {
            _audioFacade->PlaySound(soundName);
        }

        /**
         * @brief Toggle the play state of the music
         */
        void TogglePlay() {
            _audioFacade->TogglePlay();
        }

        /**
         * @brief Stop the music
         */
        void StopMusic() {
            _audioFacade->StopMusic();
        }

    private:
        AudioManager() {
            _audioFacade = std::make_unique<AudioFacade>();
        }

        std::unique_ptr<AudioFacade> _audioFacade;
    };
} // namespace platformer_engine

#endif //PLATFORMER_ENGINE_AUDIOMANAGER_HPP
