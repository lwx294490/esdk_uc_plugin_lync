@echo off
echo －－－－－ 1-1编译 UCService Release版本 －－－－－－－－－－－－－
@"%VS90COMNTOOLS%\..\IDE\devenv.com" ..\UCService\UCService.sln /Rebuild "Release|Win32"
echo －－－－－ 1-2编译 UCService Release版本成功 －－－－－－－－－－－

echo －－－－－ 2-1创建打包文件夹－－－－－
	::获得当前时间，作为生成版本的目录名
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

	::设置各变量名
	set   	DateTime=%Year%-%Month%-%Day%-%Hour%-%Minute%	
	set	WinRarRoot=C:\Program Files\WinRAR
	set	ProjectPath=%cd%
	set	Version=V1.3.30

    mkdir .\build\%DateTime%

echo －－－－－2-2创建打包文件夹成功－－－－－

echo －－－－－3-1 拷贝 HWUCSDK DLL－－－－－－－－－－－－－
xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\Call\vs2008.release.dll\*     .\build\%DateTime%
xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\IM\vs2012.release.dll\*       .\build\%DateTime%
xcopy /Y /S .\..\..\third_party_groupware\Microsoft\* 	                          .\build\%DateTime%
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\release\*.dll	                  .\build\%DateTime%
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\release\*.ini	                  .\build\%DateTime%
echo －－－－－3-2拷贝 HWUCSDK DLL 成功－－－－－－－－－－－－

echo －－－－－4-1 拷贝 UCService依赖的资源文件 －－－－－－－－－－－－－
xcopy /Y /S .\UCResource\*  	                                                  .\build\%DateTime%
echo －－－－－4-2拷贝 UCService依赖的资源文件 成功－－－－－－－－－－－－

echo －－－－－ 5-1拷贝 UCService Release版本 －－－－－－－－－－－－－
xcopy /Y ..\UCService\output\release\UCService.dll 	                          .\build\%DateTime%
xcopy /Y ..\UCService\output\release\UCService.pdb 	                          .\build\%DateTime%
xcopy /Y ..\UCService\output\release\UCService.ini 	                          .\build\%DateTime%
echo －－－－－ 5-2拷贝 UCService Release版本成功－－－－－－－－－－－－

echo.
echo －－－－－ 5-3拷贝 Log4Net －－－－－－－－－－－－
xcopy /Y .\..\..\open_src\client\log4net.dll                                       .\build\%DateTime%
echo.
echo －－－－－ 5-4拷贝 Log4Net成功 －－－－－－－－－－

echo －－－－－ 6-1拷贝 include头文件－－－－－－－－－－－－
xcopy /Y /S .\output\include\*                                                     .\build\%DateTime%

echo －－－－－ 6-2拷贝 include头文件成功－－－－－－－－－－－－

echo －－－－－ －－完成 －－－－－－－－－－	
pause