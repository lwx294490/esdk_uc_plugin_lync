@echo off

echo ���������� ���� LOGNETDLL ��������������������������
xcopy /Y /S ..\..\open_src\client\log4net.dll 	LyncWpfApp\LyncWpfApp\Reference\

echo ���������� ���� HWUCSDK DLL��������������������������
xcopy /Y /S .\..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C50SPC100B091\debug\dll\* 	..\UCService\output\debug\
xcopy /Y /S .\..\..\platform\HWUCSDK\windows\eSpace_Desktop_V200R001C50SPC100B091\release\dll\* ..\UCService\output\release\
echo ���������� ���� HWUCSDK DLL �ɹ�������������������������

echo ���������� ���� UCService��������Դ�ļ� ��������������������������
xcopy /Y /S ..\UCService\UCResource\* 			..\UCService\output\debug\
xcopy /Y /S ..\UCService\UCResource\*  			..\UCService\output\release\
echo ���������� ���� UCService��������Դ�ļ� �ɹ�������������������������

pause