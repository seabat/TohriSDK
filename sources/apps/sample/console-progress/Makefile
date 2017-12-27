PROGRAM := console_progress

#コンパイル対象
SRCS    := src/main.c \
		   src/sub.c \
		   src/log.c

#インクルードファイルディレクトリ
INCFLG   = -I./inc

#CC,CFLAGはmake内で定義済みマクロ
#コンパイラのシェルを指定
CC      = gcc

#コンパイルオプションを指定
#  -Wallはすべてのワーニングを省略せずに要求するオプション
#  -O2は最適化レベル2を表す。2は最適化の推奨レベル。
#CFLAGS  = -Wall -O2 -DDEBUG
CFLAGS  = -Wall -O2

ifeq ($(TOHRI_SDK_USE),true)
	#--------------------------------------
	# TohriSDK
	#--------------------------------------
	PROJECT    :=console-progress
	include $(TOHRI_SDK_BUILD_PATH)/Makefile_set_env.in
	OBJDIR     :=$(SDK_OUT_OBJ_BIN_DIR)/$(PROJECT)
	INSTALLDIR :=$(SDK_OUT_BIN_DIR)
	
	include $(TOHRI_SDK_BUILD_PATH)/Makefile_build_app.in
else
	#--------------------------------------
	# local build 
	#--------------------------------------
	#Set a directory of object files
	OBJDIR:= obj
	#Set a directory to install
	INSTALLDIR :=.
	include ../../../../build/Makefile_build_app.in
endif
