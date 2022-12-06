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

        void Quit();

        void SetVolume(int volume);

        void LoadMusic(const std::string &musicName, const std::string &fileName);

        void LoadSound(const std::string &soundName, const std::string &fileName);

        void PlayMusic(const std::string &musicName);

        void PlaySound(const std::string &soundName);

        void TogglePlay();

        void StopMusic();

        AudioFacade();

    private:

        std::map<std::string, std::unique_ptr<Mix_Music, std::function<void(
                Mix_Music *)>>> _music;
        std::map<std::string, std::unique_ptr<Mix_Chunk, std::function<void(
                Mix_Chunk *)>>> _sounds;
        int _volume = MIX_MAX_VOLUME;
    };


}

#endif //PLATFORMER_ENGINE_AUDIOFACADE_HPP
