//=====================================================
//	dShiwMovie.h
//-----------------------------------------------------
//	DirectShowを使って動画を再生する
//===　対応フォーマット ===
//--- ファイルタイプ ---
//	WMA , WMV , ASF , MPEG , AVI
//	WAV , AIFF , AU , SND , MIDI
//--- 圧縮フォーマット ---
//	
//
//--- 更新履歴 ---
//	20/08/05	製作開始
//				とりあえず別ウィンドウに動画が出るようになった
//	20/08/07	非同期再生？できるようになった
//				動画が指定したウィンドウに出るようになった
//				位置、サイズをウィンドウに合わせるように
//	20/08/08	動画のフレームをポリゴンに張り付けられるテクスチャに
//					変換したかったが、一旦断念
//=====================================================
#pragma once

#include <dshow.h>
#pragma comment ( lib, "strmiids.lib" )

class DShow
{
public:
	DShow();		
	~DShow();
	HRESULT Init();
	HRESULT Create(const wchar_t* filename);
	HRESULT SetWindow(HWND hWnd,long ScreenWidth,long ScreenHeight);
	void	ReleaseWindow();
	HRESULT Play();
	HRESULT Play(const wchar_t* filename);
	HRESULT Stop();
	HRESULT Pause();
	IGraphBuilder*	GetBuilder();
	IMediaControl*	GetControl();
	IMediaEvent*	GetEvent();
	void Uninit();

	bool isPlaying();
	HRESULT RePlay();
	HRESULT SetVolume(float);

private:
	IGraphBuilder	*m_pGraph;			// グラフビルダ
	IMediaControl	*m_pContorol;		// コントローラ
	IMediaEvent		*m_pEvent;			// イベントオブジェクト
	IMediaSeeking	*m_pSeek;			// メディアの再生位置を操作
	IBasicAudio		*m_pAudio;			// 音量管理オブジェクト
	IBasicVideo		*m_pVideo;			// ビデオの情報を管理する
	IVideoWindow	*m_pVideoWindow;	// ウィンドウ管理


	void ReleaseVideo();
	void ReleaseAudio();
	void ReleaseSeek();
	void ReleaseEvent();
	void ReleaseControl();
	void ReleaseBuilderGraph();
};