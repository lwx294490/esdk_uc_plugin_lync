@echo off

echo.
echo ���������� 4-1���� UCService Debug�汾 ��������������������������
@"%VS90COMNTOOLS%\..\IDE\devenv.com" ..\UCService\UCService.sln /Rebuild "Debug|Win32"
echo.
echo ���������� 4-1���� UCService Debug�汾�ɹ�������������������������

echo ���������� 4-2���� UCService Debug�汾 ��������������������������
xcopy /Y ..\UCService\output\debug\UCService.dll .\LyncWpfApp\LyncWpfApp\output\Debug\
xcopy /Y ..\UCService\output\debug\UCService.pdb .\LyncWpfApp\LyncWpfApp\output\Debug\
echo ���������� 4-2���� UCService Debug�汾�ɹ�������������������������

echo.
echo ���������� 4-3���� WpfSendMessage Debug�汾 ��������������������������
@"%VS100COMNTOOLS%\..\IDE\devenv.com" .\WpfSendMessage\WpfSendMessage.sln /Rebuild "Debug"
echo.
echo ���������� 4-3���� WpfSendMessage Debug�汾�ɹ�����������������������

echo.
echo ���������� 4-4���� LyncWpfApp Debug�汾 ��������������������������
@"%VS100COMNTOOLS%\..\IDE\devenv.com" .\LyncWpfApp\LyncWpfApp.sln /Rebuild "Debug"
echo.
echo ���������� 4-4���� LyncWpfApp Debug�汾�ɹ�������������������������

pause