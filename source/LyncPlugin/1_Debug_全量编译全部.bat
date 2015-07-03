@echo off

echo.
echo гнгнгнгнгн 4-1▒р╥ы UCService Debug░ц▒╛ гнгнгнгнгнгнгнгнгнгнгнгнгн
@"%VS90COMNTOOLS%\..\IDE\devenv.com" ..\UCService\UCService.sln /Rebuild "Debug|Win32"
echo.
echo гнгнгнгнгн 4-1▒р╥ы UCService Debug░ц▒╛│╔╣жгнгнгнгнгнгнгнгнгнгнгнгн

echo гнгнгнгнгн 4-2┐╜▒┤ UCService Debug░ц▒╛ гнгнгнгнгнгнгнгнгнгнгнгнгн
xcopy /Y ..\UCService\output\debug\UCService.dll .\LyncWpfApp\LyncWpfApp\output\Debug\
xcopy /Y ..\UCService\output\debug\UCService.pdb .\LyncWpfApp\LyncWpfApp\output\Debug\
echo гнгнгнгнгн 4-2┐╜▒┤ UCService Debug░ц▒╛│╔╣жгнгнгнгнгнгнгнгнгнгнгнгн

echo.
echo гнгнгнгнгн 4-3▒р╥ы WpfSendMessage Debug░ц▒╛ гнгнгнгнгнгнгнгнгнгнгнгнгн
@"%VS100COMNTOOLS%\..\IDE\devenv.com" .\WpfSendMessage\WpfSendMessage.sln /Rebuild "Debug"
echo.
echo гнгнгнгнгн 4-3▒р╥ы WpfSendMessage Debug░ц▒╛│╔╣жгнгнгнгнгнгнгнгнгнгнгн

echo.
echo гнгнгнгнгн 4-4▒р╥ы LyncWpfApp Debug░ц▒╛ гнгнгнгнгнгнгнгнгнгнгнгнгн
@"%VS100COMNTOOLS%\..\IDE\devenv.com" .\LyncWpfApp\LyncWpfApp.sln /Rebuild "Debug"
echo.
echo гнгнгнгнгн 4-4▒р╥ы LyncWpfApp Debug░ц▒╛│╔╣жгнгнгнгнгнгнгнгнгнгнгнгн

pause