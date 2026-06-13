#include "AudioManager.h"


AudioManager::AudioManager() :play_props(0)
{
}

AudioManager::~AudioManager()
{
	if (!mixer) return;

	MIX_StopAllTracks(mixer, 0);

	audio_pool.clear();

	track_pool.clear(); // 不手动 destroy

	if (play_props != 0) {
		SDL_DestroyProperties(play_props);
	}

	MIX_DestroyMixer(mixer);
	mixer = nullptr;
}

bool AudioManager::InitResources()
{

	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);


	play_props = SDL_CreateProperties();
	if (play_props == 0) {
		return false;
	}
	/* 设置默认值，无限循环 */
	SDL_SetNumberProperty(play_props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);

	for (int i = 0; i < 64; ++i) {
		MIX_Track* track = MIX_CreateTrack(mixer);
		if (!track) {
			return false;
		}
		track_pool.emplace_back(track);
	}

	if (!LoadAudioResources()) return false;
	return true;
}

void AudioManager::PlayAudio(const std::string& name, long long times)
{


	SDL_SetNumberProperty(play_props, MIX_PROP_PLAY_LOOPS_NUMBER, times);
	for (auto* track : track_pool) {
		if (!MIX_TrackPlaying(track)) {
			MIX_SetTrackAudio(track, audio_pool[name] .get());
			MIX_PlayTrack(track, play_props);
			track_query[name] = track;
			return;
		}
	}
}

bool AudioManager::IsPlaying(const std::string& name)
{
	if (track_query.find(name) == track_query.end()) return false;

	return MIX_TrackPlaying(track_query[name]);
}

void AudioManager::SetVolume(float volume)
{
	MIX_SetMixerGain(mixer, volume);
}

bool AudioManager::LoadAudioResources()
{
	if (!LoadAudio("blossom", "assets/audio/blossom.wav", true)) return false;
	if (!LoadAudio("grass_walk", "assets/audio/grass_walk.wav", false)) return false;

	return true;
}

bool AudioManager::LoadAudio(const std::string& name, const std::string& file_path, bool predecode)
{
	MIX_Audio* audio_data = MIX_LoadAudio(mixer, file_path.c_str(), predecode);
	if (!audio_data) {
		return false;
	}

	audio_pool.emplace(name, std::unique_ptr<MIX_Audio, MIXAudioDeleter>{audio_data});
	return true;
}

void AudioManager::Clear()
{
	audio_pool.clear();
}