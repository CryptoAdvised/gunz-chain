#ifndef REALSOUNDBGM_H
#define REALSOUNDBGM_H

/**
	Background Music Class
	������ Streaming�Ͽ� �����Ѵ�.
*/

#include "RealSound.h"
#include "RealSoundWaveFile.h"
#include "MMTimer.h"
#include "GlobalTypes.h"
#include <dsound.h>

class RealSoundBgm
{
protected:
    void Cue ();
    bool WriteWaveData (u32 cbSize);
    bool WriteSilence (u32 cbSize);
    u32 GetMaxWriteSize (void);
    bool ServiceBuffer (void);
    static bool TimerCallback (uintptr_t dwUser);

    RealSound* m_pRealSound;
    LPDIRECTSOUNDBUFFER m_pdsb;
    RSMWaveFile* m_pwavefile;
    MMTimer * m_ptimer;

	///////////////////////////////////////
	// Semaphore
	///////////////////////////////////////
    bool m_fCued;					// semaphore (stream cued)
    bool m_fPlaying;				// semaphore (stream playing)
    long m_lInService;				// reentrancy semaphore

	DSBUFFERDESC m_dsbd;			// sound buffer description
	    
    u32 m_cbBufOffset;				// last write position
    u32 m_nBufLength;				// length of sound buffer in msec
    u32 m_cbBufSize;				// size of sound buffer in bytes
    u32 m_nBufService;				// service interval in msec
    u32 m_nDuration;				// duration of wave file
    u64	 m_nTimeStarted;			// time (in system time) playback started
    u64	 m_nTimeElapsed;			// elapsed time in msec since playback started

	bool m_bLooped;					// Loop control

public:
    RealSoundBgm (void);
    virtual ~RealSoundBgm (void);

	// BGM��ü�� ����
	bool Create (LPSTR pszFilename, RealSound* pRealSound);
    void Destroy();

	// ������ BGM��ü�� ���� �Ѵ�.
    void Play(bool bLoop);

	// ���ָ� ������Ű�� ���� ��ġ�� ó������ ������.
    void Stop(void);
	//void Pause();

	bool IsPlaying(void);
	void SetVolume(float t);
};


#endif