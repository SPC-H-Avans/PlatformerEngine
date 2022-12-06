#ifndef PLATFORMER_ENGINE_AUDIOMANAGER_HPP
#define PLATFORMER_ENGINE_AUDIOMANAGER_HPP

#include "Facade/AudioFacade.hpp"

namespace platformer_engine {
    class AudioManager {
    public:
        AudioManager() {
            _audioFacade = std::make_unique<AudioFacade>();
        }

        void SetVolume(int volume) {
            _audioFacade->SetVolume(volume);
        }

        void LoadMusic(const std::string &musicName, const std::string &fileName) {
            _audioFacade->LoadMusic(musicName, fileName);
        }

        void LoadSound(const std::string &soundName, const std::string &fileName) {
            _audioFacade->LoadSound(soundName, fileName);
        }

        void PlayMusic(const std::string &musicName) {
            _audioFacade->PlayMusic(musicName);
        }

        void PlaySound(const std::string &soundName) {
            _audioFacade->PlaySound(soundName);
        }

        void TogglePlay() {
            _audioFacade->TogglePlay();
        }

        void StopMusic() {
            _audioFacade->StopMusic();
        }

    private:
        std::unique_ptr<AudioFacade> _audioFacade;
    };
}

#endif //PLATFORMER_ENGINE_AUDIOMANAGER_HPP
