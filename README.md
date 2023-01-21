# MedievalDynasty-RestoreCheatMenu

NOTE:  As of Medieval Dynasty v1.5+, the DLL is not enough on its own to restore the Cheat Menu.

A YT video detailing the updated instructions, involving extracting files from an old game version to mix with the new version can be viewed here - https://www.youtube.com/watch?v=06n0JKxKDGk



DLL to restore the ingame cheat menu.


Steam will want xinput1_3.dll, MS Store version will want xinput1_4.dll.

When launching the game with the DLL in place a black console window should appear.  If you do not see this window, the game likely failed to find the DLL.

For the MS Store version, drop xinput1_4.dll in the folder:
	C:\XboxGames\Medieval Dynasty\Content

For the Steam version, drop xinput1_3.dll in the folder:
	....Wherever Steam wants it.  Let me know where works and I'll update this.
	
NOTE:  For Steam/GOG do not drop xinput1_3.dll in the folder with the Medieval_Dynasty.exe, it should go in the subfolder "Medieval_Dynasty\Binaries\Win64" alongside Medieval_Dynasty-Win64-Shipping.exe.
