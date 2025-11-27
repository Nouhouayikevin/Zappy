/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** AudioManager.hpp
*/

#ifndef AUDIOMANAGER_HPP_
#define AUDIOMANAGER_HPP_

#include "my_include.hpp"
#include "my_define.hpp"
#include "struct.hpp"
#include <map>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void InitAudio();
    void ShutdownAudio();

    void PlayMainMusic();
    void UpdateMusicStreams();

    void PlaySoundAt(actions_e action, Vector3 position, const Camera& camera);

private:
    std::map<actions_e, Sound> _sfx;
    Music _loadingMusic;
    Music _mainMusic;

    void calculateVolumeAndPan(Vector3 soundPos, const Camera& camera, float& volume, float& pan);
    const float MAX_AUDIO_DISTANCE = 50.0f;
};

#endif