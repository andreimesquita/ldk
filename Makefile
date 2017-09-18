# source paths
LDARESDK=src\sdk
LDARESRC=src\win32\win32_ldare.cpp
GAMESRC=game\test_game.cpp

#build targets
TARGET=ldare.exe
OUTDIR=build
LDARE_GAME=$(OUTDIR)\ldare_game.dll

#DEBUG OPTIONS
LIBS=user32.lib gdi32.lib Opengl32.lib
DEBUG_COMPILE_OPTIONS=/nologo /EHsc /MT /I$(LDARESDK) /D "WIN32" /D "DEBUG" /Zi 
DEBUG_LINK_OPTIONS=/link /subsystem:console $(LIBS)

#RELEASE OPTIONS
RELEASE_COMPILE_OPTIONS=/nologo /EHsc /MT /I$(LDARESDK) /D "WIN32" 
RELEASE_LINK_OPTIONS=/link /subsystem:windows $(LIBS)

CFLAGS=$(DEBUG_COMPILE_OPTIONS)
LINKFLAGS=$(DEBUG_LINK_OPTIONS)

.PHONY: game engine 

all: game engine

game: $(LDARE_GAME)

$(LDARE_GAME): $(GAMESRC)
	@echo Building game dll...
	cl $(GAMESRC) /Fo$(OUTDIR)\ /Fe$(LDARE_GAME) /LD $(CFLAGS) /link /subsystem:windows /EXPORT:gameInit /EXPORT:gameStart /EXPORT:gameUpdate /EXPORT:gameStop /PDB:$(OUTDIR)\ldare_game_%random%.pdb

engine: $(LDARE_GAME) $(LDARE_CORE)
	@echo Building ldare engine...
	cl $(LDARESRC) /Fe$(OUTDIR)\$(TARGET) /Fo$(OUTDIR)\ $(CFLAGS) $(LINKFLAGS)

clean:
	del /S /Q .\$(OUTDIR)\*
