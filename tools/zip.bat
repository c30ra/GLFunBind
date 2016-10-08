@echo off

"C:\Program Files\7-Zip\7z.exe" u -t7z -r "../build/x86/Release/GLFunBind v1.1 win32.7z" "../build/x86/Release/*.exe"  "../build/x86/Release/include/" "../README" "../gpl-3.0.txt"
