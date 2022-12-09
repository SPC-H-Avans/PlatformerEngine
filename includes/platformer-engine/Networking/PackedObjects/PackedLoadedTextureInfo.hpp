#ifndef PLATFORMER_ENGINE_PACKEDLOADEDTEXTUREINFO_HPP
#define PLATFORMER_ENGINE_PACKEDLOADEDTEXTUREINFO_HPP

#include "Texture/LoadedTextureInfo.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include "Networking/boost/portable_binary_iarchive.hpp"
#include "Networking/boost/portable_binary_oarchive.hpp"
#include <vector>

namespace platformer_engine {
    class PackedLoadedTextureInfo {
    public:
        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & _loadedTextureInfos;
        }

        PackedLoadedTextureInfo() = default;

        void LoadTextures();

        inline auto GetLoadedTextureInfos() -> std::vector<LoadedTextureInfo> { return _loadedTextureInfos; };
    private:
        std::vector<LoadedTextureInfo> _loadedTextureInfos;
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_PACKEDLOADEDTEXTUREINFO_HPP
