//=====================================================
//	dShiwMovie.h
//-----------------------------------------------------
//	DirectShow���g���ē�����Đ�����
//===�@�Ή��t�H�[�}�b�g ===
//--- �t�@�C���^�C�v ---
//	WMA , WMV , ASF , MPEG , AVI
//	WAV , AIFF , AU , SND , MIDI
//--- ���k�t�H�[�}�b�g ---
//	
//
//--- �X�V���� ---
//	20/08/05	����J�n
//				�Ƃ肠�����ʃE�B���h�E�ɓ��悪�o��悤�ɂȂ���
//	20/08/07	�񓯊��Đ��H�ł���悤�ɂȂ���
//				���悪�w�肵���E�B���h�E�ɏo��悤�ɂȂ���
//				�ʒu�A�T�C�Y���E�B���h�E�ɍ��킹��悤��
//	20/08/08	����̃t���[�����|���S���ɒ���t������e�N�X�`����
//					�ϊ��������������A��U�f�O
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
	IGraphBuilder	*m_pGraph;			// �O���t�r���_
	IMediaControl	*m_pContorol;		// �R���g���[��
	IMediaEvent		*m_pEvent;			// �C�x���g�I�u�W�F�N�g
	IMediaSeeking	*m_pSeek;			// ���f�B�A�̍Đ��ʒu�𑀍�
	IBasicAudio		*m_pAudio;			// ���ʊǗ��I�u�W�F�N�g
	IBasicVideo		*m_pVideo;			// �r�f�I�̏����Ǘ�����
	IVideoWindow	*m_pVideoWindow;	// �E�B���h�E�Ǘ�


	void ReleaseVideo();
	void ReleaseAudio();
	void ReleaseSeek();
	void ReleaseEvent();
	void ReleaseControl();
	void ReleaseBuilderGraph();
};