cls

del *.exe

g++ -mwindows -m64 -static -Wall -Wextra Internet.cpp FileClass.cpp InternetClass.cpp InternetFileClass.cpp ListBoxWindow.cpp ButtonWindow.cpp EditWindow.cpp StatusBarWindow.cpp -o Internet.exe -lwininet
