#ifndef AUDIOSOURCE_H_
#define AUDIOSOURCE_H_

#include "Component.hpp"
#include <string>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/map.hpp>

namespace spic {

    /**
     * @brief Component which can play audio.
     */
    class AudioSource : public Component {
    public:
        AudioSource() {
            _audioClips = std::map<std::string, int>();
        }

        AudioSource(std::map<std::string, int> audioClips) : _audioClips(std::move(audioClips)) {}

        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & boost::serialization::base_object<Component, AudioSource>(*this);
            boost::serialization::void_cast_register<AudioSource, Component>();
            ar & _audioClips;
        }

        /**
         * @brief Call this method to start playing audio (make sure the audio file is loaded)
         * @param looping Automatically start over when done.
         * @spicapi
         */
        void PlayMusic(const std::string &musicName, bool looping);

        /**
         * @brief Play a sound
         * @param soundName Name of the sound you want to play
         */
        void PlaySound(const std::string &soundName);

        /**
         * @brief Call this method to stop playing audio.
         * @spicapi
         */
        void Stop();

        /**
         * @brief Add an audio clip that can be played by this component
         * @param musicName
         * @param volume
         */
        void AddAudioClip(const std::string &musicName, int volume);

    private:
        /**
         * @brief Name of the audio clip and the volume
         */
        std::map<std::string, int> _audioClips;
    };
}

#endif // AUDIOSOURCE_H_
