@echo off

echo －－－－－ 拷贝 LOGNETDLL －－－－－－－－－－－－－
xcopy /Y /S ..\..\open_src\client\log4net.dll 	LyncWpfApp\LyncWpfApp\Reference\

echo －－－－－ 拷贝 HWUCSDK DLL－－－－－－－－－－－－－
xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\Call\vs2008.debug.dll\* 	  .\output\debug\
xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\IM\vs2012.debug.dll\* 	  .\output\debug\
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\debug\*.dll 	                  .\output\debug
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\debug\*.ini	                  .\output\debug\

xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\Call\vs2008.release.dll\*     .\output\release\
xcopy /Y /S .\..\..\platform\TUPSDK\TUP_V100R001C30\IM\vs2012.release.dll\*       .\output\release\
xcopy /Y /S .\..\..\third_party_groupware\Microsoft\* 	                          .\output\release\
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\release\*.dll	                  .\output\release\
xcopy /Y /S .\..\..\self_dev\eSDKClientLogAPI\release\*.ini	                  .\output\release\
echo －－－－－ 拷贝 HWUCSDK DLL 成功－－－－－－－－－－－－

echo －－－－－ 拷贝 UCService依赖的资源文件 －－－－－－－－－－－－－
xcopy /Y /S ..\UCService\UCResource\* 			..\UCService\output\debug\
xcopy /Y /S ..\UCService\UCResource\*  			..\UCService\output\release\
echo －－－－－ 拷贝 UCService依赖的资源文件 成功－－－－－－－－－－－－

pause