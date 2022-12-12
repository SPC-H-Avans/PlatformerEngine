#include "AudioSource.hpp"
#include "Audio/AudioManager.hpp"

void spic::AudioSource::PlayMusic(const std::string &musicName, bool looping) {
    if (_audioClips.contains(musicName)) {
        platformer_engine::AudioManager::GetInstance().SetVolume(_audioClips[musicName]);
        platformer_engine::AudioManager::GetInstance().PlayMusic(musicName, looping);
    }
}

void spic::AudioSource::PlaySound(const std::string &soundName) {
    if (_audioClips.contains(soundName)) {
        platformer_engine::AudioManager::GetInstance().SetVolumeMusic(_audioClips[soundName]);
        platformer_engine::AudioManager::GetInstance().PlaySound(soundName);
    }
}

void spic::AudioSource::Stop() {
    platformer_engine::AudioManager::GetInstance().StopMusic();
}

void spic::AudioSource::AddAudioClip(const std::string &musicName, int volume) {
    if (!_audioClips.contains(musicName)) {
        _audioClips[musicName] = volume;
    }
}

BOOST_CLASS_EXPORT(spic::AudioSource);