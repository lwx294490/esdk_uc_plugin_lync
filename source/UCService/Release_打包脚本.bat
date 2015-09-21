@echo off
echo ���������� 1-1���� UCService Release�汾 ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" ..\UCService\UCService.sln /Rebuild "Release|Win32"
echo ���������� 1-2���� UCService Release�汾�ɹ� ����������������������

echo ���������� 2-1��������ļ��У���������
	::��õ�ǰʱ�䣬��Ϊ���ɰ汾��Ŀ¼��
	for /F "tokens=1-4 delims=-/ " %%i in ('date /t') do (
	   set Year=%%i
	   set Month=%%j
	   set Day=%%k
	   set DayOfWeek=%%l
	)
	for /F "tokens=1-2 delims=: " %%i in ('time /t') do (
	   set Hour=%%i
	   set Minute=%%j
	)

	::���ø�������
	set   	DateTime=%Year%-%Month%-%Day%-%Hour%-%Minute%	
	set	WinRarRoot=C:\Program Files\WinRAR
	set	ProjectPath=%cd%
	set	Version=V1.3.30

    mkdir .\build\%DateTime%

echo ����������2-2��������ļ��гɹ�����������

echo ����������3-1 ���� HWUCSDK DLL��������������������������
xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\Call\vs2008.release.dll\*     .\build\%DateTime%
xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\IM\vs2012.release.dll\*       .\build\%DateTime%
xcopy /Y /S .\..\..\third_party_groupware\Microsoft\* 	                          .\build\%DateTime%
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\release\*.dll	                  .\build\%DateTime%
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\release\*.ini	                  .\build\%DateTime%
echo ����������3-2���� HWUCSDK DLL �ɹ�������������������������

echo ����������4-1 ���� UCService��������Դ�ļ� ��������������������������
xcopy /Y /S .\UCResource\*  	                                                  .\build\%DateTime%
echo ����������4-2���� UCService��������Դ�ļ� �ɹ�������������������������

echo ���������� 5-1���� UCService Release�汾 ��������������������������
xcopy /Y ..\UCService\output\release\UCService.dll 	                          .\build\%DateTime%
xcopy /Y ..\UCService\output\release\UCService.pdb 	                          .\build\%DateTime%
xcopy /Y ..\UCService\output\release\UCService.ini 	                          .\build\%DateTime%
echo ���������� 5-2���� UCService Release�汾�ɹ�������������������������

echo.
echo ���������� 5-3���� Log4Net ������������������������
xcopy /Y .\..\..\open_src\client\log4net.dll                                       .\build\%DateTime%
echo.
echo ���������� 5-4���� Log4Net�ɹ� ��������������������

echo ���������� 6-1���� includeͷ�ļ�������������������������
xcopy /Y /S .\output\include\*                                                     .\build\%DateTime%

echo ���������� 6-2���� includeͷ�ļ��ɹ�������������������������

echo ���������� ������� ��������������������	
pause