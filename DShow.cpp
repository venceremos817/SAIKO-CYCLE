#include "DShow.h"



DShow::DShow()
{
	m_pGraph = NULL;
	m_pContorol = NULL;
	m_pEvent = NULL;
	m_pSeek = NULL;
	m_pAudio = NULL;
	m_pVideo = NULL;
	m_pVideoWindow = NULL;
}


DShow::~DShow()
{
	Uninit();
}


// ������
// �O���t�I�u�W�F�N�g�𐶐�����
HRESULT DShow::Init()
{
	HRESULT hr = S_OK;

	// COM��������
	hr = CoInitialize(NULL);

	// FilterGraph���쐬
	hr = CoCreateInstance(
		CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(void**)&m_pGraph
	);
	if (FAILED(hr))
		return hr;

	//--- MediaControl�C���^�[�t�F�[�X�擾
	// �O���t�̓����Ԃ��Ǘ�����I�u�W�F�N�g�A�Đ����~�̎w�����s��
	hr = m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pContorol);
	if (FAILED(hr))
		return hr;

	// �O���t����^������C�x���g(�Đ���������)���Ǘ�
	hr = m_pGraph->QueryInterface(IID_IMediaEventEx, (void**)&m_pEvent);
	if (FAILED(hr))
		return hr;

	// ���f�B�A�̍Đ��ʒu�𑀍삷��I�u�W�F�N�g�A�V�[�N�����⃁�f�B�A�̎��ԊǗ�
	hr = m_pGraph->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeek);
	if (FAILED(hr))
		return hr;

	// ���f�B�A���r�f�I�����Ƃ����̃r�f�I�̏����Ǘ�
	hr = m_pGraph->QueryInterface(IID_IBasicVideo, (void**)&m_pVideo);
	if (FAILED(hr))
		return hr;

	// ���f�B�A���I�[�f�B�I�����Ƃ��Ɏg�p�ł��鉹�ʊǗ�
	hr = m_pGraph->QueryInterface(IID_IBasicAudio, (void**)&m_pAudio);
	if (FAILED(hr))
		return hr;

	// ���f�B�A���r�f�I�E�B���h�E�����Ƃ��Ɏg�p�ł���E�B���h�E�Ǘ�
	hr = m_pGraph->QueryInterface(IID_IVideoWindow, (void**)&m_pVideoWindow);
	if (FAILED(hr))
		return hr;
	
	// �Đ��ʒu�̕ύX���s���^�C���t�H�[�}�b�g�����f�B�A�^�C��(100�i�ms��1�Ƃ���P�ʌn)�ɂ���
	hr = m_pSeek->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
	if (FAILED(hr))
		return hr;
	
	

	return hr;
}


// �Đ�����E�B���h�E���w�肷��
HRESULT DShow::SetWindow(HWND hWnd,long ScreenWidth,long ScreenHeight)
{
	HRESULT hr;

	// �r�f�I�̃E�B���h�E�����C���E�B���h�E�ɐݒ肷��
	if (hWnd != NULL)
	{
		hr = m_pVideoWindow->put_Owner((OAHWND)hWnd);
		if (FAILED(hr))
			return hr;
	}
	hr = m_pVideoWindow->put_MessageDrain((OAHWND)hWnd);
	if (FAILED(hr))
		return hr;
	hr = m_pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
	if (FAILED(hr))
		return hr;

	// �ʒu�E�T�C�Y
	hr = m_pVideoWindow->SetWindowPosition(0, 0, ScreenWidth, ScreenHeight);
	if (FAILED(hr))
		return hr;

	hr = m_pVideoWindow->SetWindowForeground(OATRUE);
	if (FAILED(hr))
		return hr;
	hr = m_pVideoWindow->put_Visible(OATRUE);
	if (FAILED(hr))
		return hr;

	return hr;
}


// �t�@�C�������w�肵�ăO���t���쐬����
HRESULT DShow::Create(const wchar_t* filename)
{
	HRESULT hr;

	// Graph���쐬
	hr = m_pGraph->RenderFile(filename, NULL);
	if (FAILED(hr))
		return hr;		// �t�@�C�������݂��Ȃ��A�t�@�C���`�����Ή����Ă��Ȃ�

	return hr;
}


// �쐬����Ă���O���t���Đ�����
HRESULT DShow::Play()
{
	HRESULT hr;

	// ���f�B�A�̍Đ�
	hr = m_pContorol->Run();
	if (FAILED(hr))
		return hr;

	return hr;
}


// �t�@�C�������w�肵�O���t���쐬���A�Đ�����
HRESULT DShow::Play(const wchar_t* filename)
{
	HRESULT hr;

	// �ǂݍ���
	hr = m_pGraph->RenderFile(filename, NULL);
	if (SUCCEEDED(hr))
	{
		// �Đ�
		hr = m_pContorol->Run();
		if (SUCCEEDED(hr))
		{
			// �Đ��I���܂őҋ@
			long evCode;
			m_pEvent->WaitForCompletion(INFINITE, &evCode);
		}
		else
		{
			return hr;
		}
	}
	else
	{
		return hr;
	}

	return hr;
}



// ��~
HRESULT DShow::Stop()
{
	return m_pContorol->Stop();
}


// �ꎞ��~
HRESULT DShow::Pause()
{
	return m_pContorol->Pause();
}


// �O���t�r���_�[�擾
IGraphBuilder* DShow::GetBuilder()
{
	return m_pGraph;
}


// ���f�B�A�R���g���[���I�u�W�F�N�g�擾
IMediaControl* DShow::GetControl()
{
	return m_pContorol;
}


// �C�x���g�I�u�W�F�N�g�擾
IMediaEvent* DShow::GetEvent()
{
	return m_pEvent;
}


void DShow::Uninit()
{
	// �r�f�I�E�B���h�E����E�I��
	ReleaseWindow();

	// �r�f�I�I�u�W�F�N�g�̏I��
	ReleaseVideo();

	// �I�[�f�B�I�I�u�W�F�N�g�̏I��
	ReleaseAudio();

	// �V�[�N�I�u�W�F�N�g�̏I��
	ReleaseSeek();

	// �C�x���g�I�u�W�F�N�g�̏I��
	ReleaseEvent();

	// �R���g���[���I�u�W�F�N�g�̏I��
	ReleaseControl();

	// �O���t�I�u�W�F�N�g�̏I��
	ReleaseBuilderGraph();
}


// �r�f�I�E�B���h�E�̉���E�I��
void DShow::ReleaseWindow()
{
	if (m_pVideoWindow != NULL)
	{
		m_pVideoWindow->put_Visible(OAFALSE);
		m_pVideoWindow->put_MessageDrain(NULL);
		m_pVideoWindow->put_Owner(NULL);
		m_pVideoWindow->Release();
		m_pVideoWindow = NULL;
	}
}


// �r�f�I�I�u�W�F�N�g�̏I��
void DShow::ReleaseVideo()
{
	if (m_pVideo != NULL)
	{
		m_pVideo->Release();
		m_pVideo = NULL;
	}
}


// �I�[�f�B�I�I�u�W�F�N�g�̏I��
void DShow::ReleaseAudio()
{
	if (m_pAudio != NULL)
	{
		m_pAudio->Release();
		m_pAudio = NULL;
	}
}


// �V�[�N�I�u�W�F�N�g�̏I��
void DShow::ReleaseSeek()
{
	if (m_pSeek != NULL)
	{
		m_pSeek->Release();
		m_pSeek = NULL;
	}
}


// �C�x���g�I�u�W�F�N�g�̏I��
void DShow::ReleaseEvent()
{
	if (m_pEvent != NULL)
	{
		m_pEvent->Release();
		m_pEvent = NULL;
	}
}


// �R���g���[���I�u�W�F�N�g�̏I��
void DShow::ReleaseControl()
{
	if (m_pContorol != NULL)
	{
		m_pContorol->StopWhenReady();
		//m_pContorol->Stop();
		m_pContorol->Release();
		m_pContorol = NULL;
	}
}


// �O���t�I�u�W�F�N�g�̏I��
void DShow::ReleaseBuilderGraph()
{
	if (m_pGraph != NULL)
	{
		m_pGraph->Release();
		m_pGraph = NULL;
	}
}


// �Đ������ǂ���
bool DShow::isPlaying()
{
	//bool isPlaying;		// �Đ������ǂ���
	long EventCode;	// �C�x���g�R�[�h�󂯎��
	LONG_PTR EvParam1, EvParam2;

	// �C�x���g���擾
	m_pEvent->GetEvent(&EventCode, &EvParam1, &EvParam2, 0);

	// �Đ�������
	if (EventCode == EC_COMPLETE)
		return false;

	return true;
}


// �擪����Đ�������
HRESULT DShow::RePlay()
{
	HRESULT hr;

	// �Đ���~
	hr = m_pContorol->Stop();
	//if (FAILED(hr))	// ���łɒ�~���͎��s���邽�߁Areturn�͂��Ȃ��ق����悳����
	//	return hr;

	// �擪�Ɉړ�
	LONGLONG AbsoluteTime = 0;
	hr = m_pSeek->SetPositions(&AbsoluteTime,
		AM_SEEKING_AbsolutePositioning,
		NULL,
		AM_SEEKING_NoPositioning);
	if (FAILED(hr))
		return hr;

	// �Đ�
	hr = m_pContorol->Run();

	return hr;
}


// ���ʐݒ�(0.0f ~ 1.0f)
HRESULT DShow::SetVolume(float fVol)
{
	HRESULT hr;
	long lVol;

	if (fVol < 0.0f)
		fVol = 0.0f;
	else if (1.0 < fVol)
		fVol = 1.0f;

	// �{�����[����ϊ�
	lVol = -10000.0f + 10000.0f * fVol;
	
	// lVol = -10000 ~ 0	-10000 ���� 0 �ő�
	hr = m_pAudio->put_Volume(lVol);
	if (FAILED(hr))
		return hr;

	return hr;
}