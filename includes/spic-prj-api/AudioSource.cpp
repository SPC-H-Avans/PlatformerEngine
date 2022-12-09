#include "AudioSource.hpp"
#include "Audio/AudioManager.hpp"

namespace spic {
    void AudioSource::PlayMusic(const std::string &musicName, bool looping) {
        if (_audioClips.contains(musicName)) {
            platformer_engine::AudioManager::GetInstance().SetVolume(_audioClips[musicName]);
            platformer_engine::AudioManager::GetInstance().PlayMusic(musicName, looping);
        }
    }

    void AudioSource::PlaySound(const std::string &soundName) {
        if (_audioClips.contains(soundName)) {
            platformer_engine::AudioManager::GetInstance().SetVolumeMusic(_audioClips[soundName]);
            platformer_engine::AudioManager::GetInstance().PlaySound(soundName);
        }
    }

    void AudioSource::Stop() {
        platformer_engine::AudioManager::GetInstance().StopMusic();
    }

    void AudioSource::AddAudioClip(const std::string &musicName, int volume) {
        if (!_audioClips.contains(musicName)) {
            _audioClips[musicName] = volume;
        }
    }
}