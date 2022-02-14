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


// 初期化
// グラフオブジェクトを生成する
HRESULT DShow::Init()
{
	HRESULT hr = S_OK;

	// COMを初期化
	hr = CoInitialize(NULL);

	// FilterGraphを作成
	hr = CoCreateInstance(
		CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(void**)&m_pGraph
	);
	if (FAILED(hr))
		return hr;

	//--- MediaControlインターフェース取得
	// グラフの動作状態を管理するオブジェクト、再生や停止の指示を行う
	hr = m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pContorol);
	if (FAILED(hr))
		return hr;

	// グラフから与えられるイベント(再生が完了等)を管理
	hr = m_pGraph->QueryInterface(IID_IMediaEventEx, (void**)&m_pEvent);
	if (FAILED(hr))
		return hr;

	// メディアの再生位置を操作するオブジェクト、シーク処理やメディアの時間管理
	hr = m_pGraph->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeek);
	if (FAILED(hr))
		return hr;

	// メディアがビデオを持つときそのビデオの情報を管理
	hr = m_pGraph->QueryInterface(IID_IBasicVideo, (void**)&m_pVideo);
	if (FAILED(hr))
		return hr;

	// メディアがオーディオを持つときに使用できる音量管理
	hr = m_pGraph->QueryInterface(IID_IBasicAudio, (void**)&m_pAudio);
	if (FAILED(hr))
		return hr;

	// メディアがビデオウィンドウを持つときに使用できるウィンドウ管理
	hr = m_pGraph->QueryInterface(IID_IVideoWindow, (void**)&m_pVideoWindow);
	if (FAILED(hr))
		return hr;
	
	// 再生位置の変更を行うタイムフォーマットをメディアタイム(100ナノsを1とする単位系)にする
	hr = m_pSeek->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
	if (FAILED(hr))
		return hr;
	
	

	return hr;
}


// 再生するウィンドウを指定する
HRESULT DShow::SetWindow(HWND hWnd,long ScreenWidth,long ScreenHeight)
{
	HRESULT hr;

	// ビデオのウィンドウをメインウィンドウに設定する
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

	// 位置・サイズ
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


// ファイル名を指定してグラフを作成する
HRESULT DShow::Create(const wchar_t* filename)
{
	HRESULT hr;

	// Graphを作成
	hr = m_pGraph->RenderFile(filename, NULL);
	if (FAILED(hr))
		return hr;		// ファイルが存在しない、ファイル形式が対応していない

	return hr;
}


// 作成されているグラフを再生する
HRESULT DShow::Play()
{
	HRESULT hr;

	// メディアの再生
	hr = m_pContorol->Run();
	if (FAILED(hr))
		return hr;

	return hr;
}


// ファイル名を指定しグラフを作成し、再生する
HRESULT DShow::Play(const wchar_t* filename)
{
	HRESULT hr;

	// 読み込み
	hr = m_pGraph->RenderFile(filename, NULL);
	if (SUCCEEDED(hr))
	{
		// 再生
		hr = m_pContorol->Run();
		if (SUCCEEDED(hr))
		{
			// 再生終了まで待機
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



// 停止
HRESULT DShow::Stop()
{
	return m_pContorol->Stop();
}


// 一時停止
HRESULT DShow::Pause()
{
	return m_pContorol->Pause();
}


// グラフビルダー取得
IGraphBuilder* DShow::GetBuilder()
{
	return m_pGraph;
}


// メディアコントロールオブジェクト取得
IMediaControl* DShow::GetControl()
{
	return m_pContorol;
}


// イベントオブジェクト取得
IMediaEvent* DShow::GetEvent()
{
	return m_pEvent;
}


void DShow::Uninit()
{
	// ビデオウィンドウ解放・終了
	ReleaseWindow();

	// ビデオオブジェクトの終了
	ReleaseVideo();

	// オーディオオブジェクトの終了
	ReleaseAudio();

	// シークオブジェクトの終了
	ReleaseSeek();

	// イベントオブジェクトの終了
	ReleaseEvent();

	// コントロールオブジェクトの終了
	ReleaseControl();

	// グラフオブジェクトの終了
	ReleaseBuilderGraph();
}


// ビデオウィンドウの解放・終了
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


// ビデオオブジェクトの終了
void DShow::ReleaseVideo()
{
	if (m_pVideo != NULL)
	{
		m_pVideo->Release();
		m_pVideo = NULL;
	}
}


// オーディオオブジェクトの終了
void DShow::ReleaseAudio()
{
	if (m_pAudio != NULL)
	{
		m_pAudio->Release();
		m_pAudio = NULL;
	}
}


// シークオブジェクトの終了
void DShow::ReleaseSeek()
{
	if (m_pSeek != NULL)
	{
		m_pSeek->Release();
		m_pSeek = NULL;
	}
}


// イベントオブジェクトの終了
void DShow::ReleaseEvent()
{
	if (m_pEvent != NULL)
	{
		m_pEvent->Release();
		m_pEvent = NULL;
	}
}


// コントロールオブジェクトの終了
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


// グラフオブジェクトの終了
void DShow::ReleaseBuilderGraph()
{
	if (m_pGraph != NULL)
	{
		m_pGraph->Release();
		m_pGraph = NULL;
	}
}


// 再生中かどうか
bool DShow::isPlaying()
{
	//bool isPlaying;		// 再生中かどうか
	long EventCode;	// イベントコード受け取り
	LONG_PTR EvParam1, EvParam2;

	// イベントを取得
	m_pEvent->GetEvent(&EventCode, &EvParam1, &EvParam2, 0);

	// 再生完了時
	if (EventCode == EC_COMPLETE)
		return false;

	return true;
}


// 先頭から再生し直す
HRESULT DShow::RePlay()
{
	HRESULT hr;

	// 再生停止
	hr = m_pContorol->Stop();
	//if (FAILED(hr))	// すでに停止時は失敗するため、returnはしないほうがよさそう
	//	return hr;

	// 先頭に移動
	LONGLONG AbsoluteTime = 0;
	hr = m_pSeek->SetPositions(&AbsoluteTime,
		AM_SEEKING_AbsolutePositioning,
		NULL,
		AM_SEEKING_NoPositioning);
	if (FAILED(hr))
		return hr;

	// 再生
	hr = m_pContorol->Run();

	return hr;
}


// 音量設定(0.0f ~ 1.0f)
HRESULT DShow::SetVolume(float fVol)
{
	HRESULT hr;
	long lVol;

	if (fVol < 0.0f)
		fVol = 0.0f;
	else if (1.0 < fVol)
		fVol = 1.0f;

	// ボリュームを変換
	lVol = -10000.0f + 10000.0f * fVol;
	
	// lVol = -10000 ~ 0	-10000 無音 0 最大
	hr = m_pAudio->put_Volume(lVol);
	if (FAILED(hr))
		return hr;

	return hr;
}