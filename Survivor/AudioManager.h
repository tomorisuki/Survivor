#pragma once

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

class AudioManager
{
private:

	/* MIX_Track删除器 */
	struct MIXTrackDeleter {
		MIXTrackDeleter() = default;
		void operator()(MIX_Track* music_track) {
			if (music_track) MIX_DestroyTrack(music_track);
		}
	};

	/* MIX_Audio删除器 */
	struct MIXAudioDeleter {
		MIXAudioDeleter() = default;
		void operator()(MIX_Audio* mix_audio) {
			if (mix_audio) MIX_DestroyAudio(mix_audio);
		}
	};

	bool LoadAudio(const std::string& name, const std::string& file_path, bool predecode);


public:
	AudioManager();
	~AudioManager();

	bool LoadAudioResources();
	bool InitResources();
	void PlayAudio(const std::string& name, long long times = 0);
	bool IsPlaying(const std::string& name);
	void SetVolume(float volume);

	void Clear();

private:
	SDL_PropertiesID play_props;

	std::vector<MIX_Track*> track_pool;
	std::unordered_map<std::string, std::unique_ptr<MIX_Audio, MIXAudioDeleter>> audio_pool;
	std::unordered_map<std::string, MIX_Track*> track_query;
	MIX_Mixer* mixer{ nullptr };
};

