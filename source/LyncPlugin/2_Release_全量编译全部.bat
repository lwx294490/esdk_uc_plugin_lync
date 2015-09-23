@echo off
del /Q LyncWpfApp\LyncSetUp\Release\*.*
echo.
echo ���������� 5-1���� UCService Release�汾 ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" ..\UCService\UCService.sln /Rebuild "Release|Win32"
echo ���������� 5-1���� UCService Release�汾�ɹ� ����������������������

echo ���������� 5-2���� UCService Release�汾 ��������������������������
xcopy /Y ..\UCService\output\release\UCService.dll 	.\LyncWpfApp\LyncWpfApp\bin\
xcopy /Y ..\UCService\output\release\UCService.pdb 	.\LyncWpfApp\LyncWpfApp\bin\
xcopy /Y /S ..\UCService\output\release\* 			.\LyncWpfApp\LyncWpfApp\bin\
echo ���������� 5-2���� UCService Release�汾�ɹ�������������������������

echo ���������� 5-2-1����Lync dll�汾 ��������������������������
xcopy /Y .\..\..\LyncSDK\Microsoft.Lync.Controls.dll   	   .\LyncWpfApp\LyncWpfApp\bin\
xcopy /Y .\..\..\LyncSDK\Microsoft.Lync.Controls.Framework.dll   	   .\LyncWpfApp\LyncWpfApp\bin\
xcopy /Y .\..\..\LyncSDK\Microsoft.Lync.Model.dll   	   .\LyncWpfApp\LyncWpfApp\bin\
xcopy /Y .\..\..\LyncSDK\Microsoft.Lync.Utilities.dll   	   .\LyncWpfApp\LyncWpfApp\bin\
xcopy /Y .\..\..\LyncSDK\Microsoft.Office.Uc.dll   	   .\LyncWpfApp\LyncWpfApp\bin\
xcopy /Y .\..\..\LyncSDK\Microsoft.Lync.Controls.dll   	   .\LyncWpfApp\LyncWpfApp\Reference\
xcopy /Y .\..\..\LyncSDK\Microsoft.Lync.Controls.Framework.dll   	  .\LyncWpfApp\LyncWpfApp\Reference\
xcopy /Y .\..\..\LyncSDK\Microsoft.Lync.Model.dll   	   .\LyncWpfApp\LyncWpfApp\Reference\
xcopy /Y .\..\..\LyncSDK\Microsoft.Lync.Utilities.dll   	   .\LyncWpfApp\LyncWpfApp\Reference\
echo ���������� 5-2-1����Lync dll�汾�ɹ�������������������������

echo.
echo ���������� 5-3���� WpfSendMessage Release�汾 ��������������������
@"%VS100COMNTOOLS%\..\IDE\devenv.com" .\WpfSendMessage\WpfSendMessage.sln /Rebuild "Release"
echo.
echo ���������� 5-3���� WpfSendMessage Release�汾�ɹ� ����������������

echo.
echo ���������� 5-4���� Log4Net ������������������������
xcopy /Y .\..\..\open_src\client\log4net.dll .\LyncWpfApp\LyncWpfApp\Reference\
echo.
echo ���������� 5-4���� Log4Net�ɹ� ��������������������

echo.
echo ���������� 5-5���� LyncWpfApp Release�汾 ������������������������
@"%VS100COMNTOOLS%\..\IDE\devenv.com" .\LyncWpfApp\LyncWpfApp.sln /Rebuild "Release"
echo.
echo ���������� 5-5���� LyncWpfApp Release�汾�ɹ� ��������������������

echo.
echo ���������� ������װ�ļ� ��������������������
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
	set	Version=V1.5.30

	mkdir .\build\%DateTime%
    xcopy  /y/i/r/s .\LyncWpfApp\LyncSetUp\Release\LyncPluginSetup.msi .\build\%DateTime%
 	xcopy /Y ..\UCService\output\release\UCService.pdb .\build\%DateTime%
	xcopy /Y ..\UCService\output\release\UCService.dll .\build\%DateTime%
echo ���������� ����汾 ��������������������
	cd .\build\%DateTime%
	"%WinRarRoot%\WinRAR.exe" a -r eSDK_UC_Lync_Plugin_%Version%.zip .\LyncPluginSetup.msi
	move eSDK_UC_Lync_Plugin_%Version%.zip ..\
	cd ..\..\
echo ���������� ������� ��������������������	
pause