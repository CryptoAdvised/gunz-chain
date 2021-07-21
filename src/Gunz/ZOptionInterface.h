#pragma once

#include "RTypes.h"
#include "ZInterfaceListener.h"

class ZOptionInterface
{

	int		mOldScreenWidth;
	int		mOldScreenHeight;

	RPIXELFORMAT	mnOldBpp;

	bool	mbTimer;
	DWORD	mTimerTime;

	int Sensitivity{};


public:
	ZOptionInterface(void);

	void Update(void);

	void SetListeners();

	void InitInterfaceOption(void);
	bool SaveInterfaceOption(void);

	void OptimizationVideoOption();

	// �������� ����
	void Resize(int w, int h);		/// ������� ���� �ػ󵵿� �����ϴ� �������̽��� �����Ѵ�.
	bool ResizeWidgetRecursive( MWidget* pWidget, int w, int h);
	bool ResizeWidget(const char* szName, int w, int h);

	void ShowResizeConfirmDialog( bool Resized );
	bool IsDiffScreenResolution();
	bool TestScreenResolution();
	void GetOldScreenResolution();
	bool SetTimer( bool b = false,  float time = 0.0f );

	// ��Ʈ��ũ ��Ʈ����
	void ShowNetworkPortConfirmDialog();
	bool IsDiffNetworkPort();

	// �׼�Ű �ߺ� Ȯ��
	void OnActionKeySet(class ZActionKey* pActionKey, int key);
};



///////////////////// ���� interface listener

// �ɼ�
DECLARE_LISTENER(ZGetOptionGammaSliderChangeListener)
DECLARE_LISTENER(ZGetLoadDefaultKeySettingListener)
DECLARE_LISTENER(ZSetOptimizationListener)
DECLARE_LISTENER(ZGetSaveOptionButtonListener)
DECLARE_LISTENER(ZGetCancelOptionButtonListener)
DECLARE_LISTENER(ZGetGammaOption)
DECLARE_LISTENER(ZGetCancelResizeConfirmListener)
DECLARE_LISTENER(ZGetRequestResizeListener)
DECLARE_LISTENER(ZGetNetworkPortChangeRestartListener)
DECLARE_LISTENER(ZGetNetworkPortChangeCancelListener)
DECLARE_LISTENER(ZGetViewConfirmCancelListener)
DECLARE_LISTENER(ZGetViewConfrimAcceptListener)
DECLARE_LISTENER(ZGet8BitSoundListener)
DECLARE_LISTENER(ZGet16BitSoundListener)
DECLARE_LISTENER(ZGetBGMVolumeSizeSliderListener)
DECLARE_LISTENER(ZGetEffectVolumeSizeSliderListener)
