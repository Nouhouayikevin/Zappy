/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** audioManager.cpp
*/

#include "../include/AudioManager.hpp"

AudioManager::AudioManager() {}
AudioManager::~AudioManager() {}

void AudioManager::InitAudio() {
    SetTraceLogLevel(LOG_ERROR);
    InitAudioDevice();
    
    _loadingMusic = LoadMusicStream(GIVE_AUDIO_OBJECT("loading_music", ".mp3").c_str() );
    _mainMusic = LoadMusicStream(GIVE_AUDIO_OBJECT("main_music", "mp3").c_str() );
    
    _sfx[ECSTASY] = LoadSound(GIVE_AUDIO_OBJECT("ecstasy", "mp3").c_str() );
    _sfx[CANCEL] = LoadSound(GIVE_AUDIO_OBJECT("cancel", "mp3").c_str() );
    _sfx[WALK] = LoadSound(GIVE_AUDIO_OBJECT("walk", "mp3").c_str() );
    _sfx[PICK] = LoadSound(GIVE_AUDIO_OBJECT("pick", "mp3").c_str() );
    _sfx[DROP] = LoadSound(GIVE_AUDIO_OBJECT("drop", "mp3").c_str() );
    _sfx[LAY] = LoadSound(GIVE_AUDIO_OBJECT("lay", "mp3").c_str() );
    _sfx[SPAWN] = LoadSound(GIVE_AUDIO_OBJECT("spawn", "mp3").c_str() );
    _sfx[DIE] = LoadSound(GIVE_AUDIO_OBJECT("die", "mp3").c_str() );
    _sfx[EXPULSE] = LoadSound(GIVE_AUDIO_OBJECT("expulse", "mp3").c_str() );
    _sfx[IDLE] = LoadSound(GIVE_AUDIO_OBJECT("idle", "mp3").c_str() );
    _sfx[BROADCAST] = LoadSound(GIVE_AUDIO_OBJECT("broadcast", "mp3").c_str() );

    PlayMusicStream(_loadingMusic);
    SetMusicVolume(_loadingMusic, 0.5f);
}

void AudioManager::ShutdownAudio() {
    for (auto const& [key, val] : _sfx) {
        UnloadSound(val);
    }
    UnloadMusicStream(_loadingMusic);
    UnloadMusicStream(_mainMusic);
    CloseAudioDevice();
}



void AudioManager::PlayMainMusic() {
    StopMusicStream(_loadingMusic);
    PlayMusicStream(_mainMusic);
    SetMusicVolume(_mainMusic, 0.3f);
}

void AudioManager::UpdateMusicStreams() {
    UpdateMusicStream(_loadingMusic);

    UpdateMusicStream(_mainMusic);
}

void AudioManager::calculateVolumeAndPan(Vector3 soundPos, const Camera& camera, float& volume, float& pan) {
    float distance = Vector3Distance(soundPos, camera.position);
    
    volume = 1.0f - (distance / MAX_AUDIO_DISTANCE);
    volume = Clamp(volume, 0.0f, 1.0f);

    // Calcul du panoramique (gauche/droite)
    Vector3 toSound = Vector3Normalize(Vector3Subtract(soundPos, camera.position));
    Vector3 camRight = Vector3CrossProduct(Vector3Normalize(Vector3Subtract(camera.target, camera.position)), camera.up);
    
    pan = Vector3DotProduct(toSound, camRight); 
    pan = (pan + 1.0f) / 2.0f;
    pan = Clamp(pan, 0.0f, 1.0f);
}

void AudioManager::PlaySoundAt(actions_e action, Vector3 position, const Camera& camera) {
    if (_sfx.find(action) == _sfx.end()) return;

    Sound sound = _sfx.at(action);
    float volume, pan;

    calculateVolumeAndPan(position, camera, volume, pan);

    SetSoundVolume(sound, volume);
    SetSoundPan(sound, pan);
    PlaySound(sound);
}