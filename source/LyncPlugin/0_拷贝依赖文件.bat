@echo off

echo ���������� ���� LOGNETDLL ��������������������������
xcopy /Y /S ..\..\open_src\client\log4net.dll 	LyncWpfApp\LyncWpfApp\Reference\

echo ���������� ���� HWUCSDK DLL��������������������������
xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\Call\vs2008.debug.dll\* 	  .\output\debug\
xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\IM\vs2012.debug.dll\* 	  .\output\debug\
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\debug\*.dll 	                  .\output\debug
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\debug\*.ini	                  .\output\debug\

xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\Call\vs2008.release.dll\*     .\output\release\
xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\IM\vs2012.release.dll\*       .\output\release\
xcopy /Y /S .\..\..\third_party_groupware\Microsoft\* 	                          .\output\release\
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\release\*.dll	                  .\output\release\
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\release\*.ini	                  .\output\release\
echo ���������� ���� HWUCSDK DLL �ɹ�������������������������

echo ���������� ���� UCService��������Դ�ļ� ��������������������������
xcopy /Y /S ..\UCService\UCResource\* 			..\UCService\output\debug\
xcopy /Y /S ..\UCService\UCResource\*  			..\UCService\output\release\
echo ���������� ���� UCService��������Դ�ļ� �ɹ�������������������������

pause