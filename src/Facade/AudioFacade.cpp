#include <SDL.h>
#include "Facade/AudioFacade.hpp"
#include "Exceptions/MixerNotInitializedException.hpp"
#include "Exceptions/AudioNotFoundException.hpp"
#include "Debug.hpp"


namespace platformer_engine {
    AudioFacade::AudioFacade() {
        Mix_Init(MIX_INIT_MP3);
        SDL_Init(SDL_INIT_AUDIO);
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            throw spic::MixerNotInitializedException(Mix_GetError());
        }
        SetVolume(_volume);
    }

    AudioFacade::~AudioFacade() {
        Quit();
    }

    void AudioFacade::Quit() {
        Mix_Quit();
    }

    void platformer_engine::AudioFacade::SetVolume(int volume) {
        _volume = volume;
    }

    void AudioFacade::SetVolumeMusic(int volume) {
        SetVolume(volume);
        Mix_VolumeMusic(_volume);
    }

    void AudioFacade::LoadMusic(const std::string &musicName, const std::string &fileName) {
        std::unique_ptr<Mix_Music, std::function<void(
                Mix_Music *)>> music = std::unique_ptr<Mix_Music, std::function<void(Mix_Music *)>>(
                Mix_LoadMUS(fileName.c_str()), Mix_FreeMusic);

        if (music == nullptr || musicName.empty()) {
            throw spic::AudioNotFoundException();
        }

        _music[musicName] = std::move(music);
    }

    void AudioFacade::LoadSound(const std::string &soundName, const std::string &fileName) {
        std::unique_ptr<Mix_Chunk, std::function<void(
                Mix_Chunk *)>> sound = std::unique_ptr<Mix_Chunk, std::function<void(Mix_Chunk *)>>(
                Mix_LoadWAV(fileName.c_str()), Mix_FreeChunk);

        if (sound == nullptr || soundName.empty()) {
            throw spic::AudioNotFoundException();
        }

        _sounds[soundName] = std::move(sound);
    }

    void AudioFacade::PlayMusic(const std::string &musicName, bool loopMusic) {
        if (!_music.contains(musicName)) {
            spic::Debug::LogWarning("Tried to play " + musicName + ", but this music is not loaded!");
        }

        if (Mix_PlayingMusic() == 0) {
            Mix_Volume(1, _volume);
            Mix_PlayMusic(_music[musicName].get(), (loopMusic ? INT_MAX : 0));
            Mix_VolumeMusic(_volume);
        } else {
            spic::Debug::LogWarning("Tried to play new music, while music was still playing");
        }
    }

    void AudioFacade::PlaySound(const std::string &soundName) {
        if (!_sounds.contains(soundName)) {
            spic::Debug::LogWarning("Tried to play " + soundName + ", but this sound is not loaded!");
        } else {
            Mix_Volume(-1, _volume);
            Mix_PlayChannel(-1, _sounds[soundName].get(), 0);
        }
    }

    void AudioFacade::TogglePlay() {
        if (Mix_PausedMusic() == 1) {
            Mix_ResumeMusic();
        } else {
            Mix_PauseMusic();
        }
    }

    void AudioFacade::StopMusic() {
        Mix_PauseMusic();
    }
}
