# source paths
LDKSDK=src\include
GAMESRC=game\game.cpp

#build targets
OUTDIR=build
LDK_GAME=$(OUTDIR)\ldk_game.dll

#DEBUG OPTIONS
LIBS=user32.lib gdi32.lib Opengl32.lib Msimg32.lib Ole32.lib
DEBUG_DEFINES=/D "_LDK_DEBUG_" 
DEBUG_COMPILE_OPTIONS=/nologo /EHsc /MT /I$(LDKSDK) $(DEBUG_DEFINES) /Zi
DEBUG_LINK_OPTIONS=/link /subsystem:console $(LIBS)

#RELEASE OPTIONS
RELEASE_DEFINES=
RELEASE_COMPILE_OPTIONS=/nologo /EHsc /MT /I$(LDKSDK) $(RELEASE_DEFINES) /Zi
RELEASE_LINK_OPTIONS=/link /subsystem:windows $(LIBS)

CFLAGS=$(DEBUG_COMPILE_OPTIONS)
LINKFLAGS=$(DEBUG_LINK_OPTIONS)

.PHONY: game ldk assets

all: outdirfolder editor

game: assets

game: ldk
	@echo Building game dll...
	cl game\game.cpp /Fo$(OUTDIR)\ /Fe$(LDK_GAME) /LD $(CFLAGS) /link /subsystem:windows /EXPORT:gameInit /EXPORT:gameStart /EXPORT:gameUpdate /EXPORT:gameStop /PDB:$(OUTDIR)\ldare_game_%random%.pdb $(OUTDIR)/ldk.lib

assets:
	@echo copying game assets ...
	xcopy game\assets $(OUTDIR)\assets /Y /I /E /F > NUL
	@echo copying standard assets ...
	xcopy assets $(OUTDIR)\assets /Y /I /E /F > NUL

ldk:
	@echo Building ldk...
	cl src\ldk.cpp /Fo$(OUTDIR)\ /Fe$(OUTDIR)\ldk.dll /LD $(CFLAGS) /link /DLL /subsystem:windows $(LIBS)

editor: ldk game
	cl src\ldk_editor.cpp /Fe$(OUTDIR)/ $(CFLAGS) $(LINKFLAGS) $(OUTDIR)/ldk.lib

tool: src\win32\tools\ldk_tool_font.cpp
	cl src\win32\tools\ldk_tool_font.cpp /Fe$(OUTDIR)\makefont.exe /Fo$(OUTDIR)\ $(CFLAGS) $(LINKFLAGS)

outdirfolder:
	IF NOT EXIST "$(OUTDIR)" mkdir $(OUTDIR)

clean:
	@IF EXIST "$(OUTDIR)" del /S /Q .\$(OUTDIR)\* > NUL
	@IF EXIST "$(OUTDIR)\assets" rd /S /Q .\$(OUTDIR)\assets > NUL
