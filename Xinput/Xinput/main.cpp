#include <stdio.h>
#include <stdlib.h>
#include "input.h"
void main(void)
{
	
	CInput* pInput = CInput::Create();
	pInput->StartVibration(0, 65535, 65535);
	while (1)
	{
		printf("接続されているコントローラー:%d\n", pInput->GetConnectedPadNum());
		printf("押されているボタンのビット\n");
		for (int nCount = 0; nCount < 2; nCount++)
		{
			printf("スティック%dのX値:%.0f\n", nCount, pInput->GetStickValue(0, nCount).x);
			printf("スティック%dのY値:%.0f\n", nCount, pInput->GetStickValue(0, nCount).y);
		}
		for (int nCount = 1; nCount <= XINPUT_GAMEPAD_RIGHT_SHOULDER; nCount *= 2)
		{
			if (pInput->GetButtonState(0, nCount))
			{
				printf("0x%x\n", nCount);
			}
		}
		for (int nCount = 0x1000; nCount <= XINPUT_GAMEPAD_Y; nCount *= 2)
		{
			if (pInput->GetButtonState(0, nCount))
			{
				printf("0x%x\n", nCount);
			}
		}
		for (int nCount = 0; nCount < 2; nCount++)
		{
			if (pInput->GetTriggerState(0, nCount))
			{
				printf("トリガー%d\n", nCount);
			}
		}
		Sleep(100);
		system("cls");
	}
}