#最終ファイル
PROGRAM       :=plugin_dynamic_take.so

#コンパイル対象
SRCS     := plugin_take.c

#インクルードファイルディレクトリ
INCFLG   := -I./inc -I../../manager/inc

#CC,CFLAGはmake内で定義済みマクロ
#コンパイラのシェルを指定
CC      := gcc
#コンパイルオプションを指定
#  -Wallはすべてのワーニングを省略せずに要求するオプション
#  -O2は最適化レベル2を表す。2は最適化の推奨レベル。
CFLAGS  := -Wall -O2


ifeq ($(TOHRI_SDK_USE),true)
	#--------------------------------------
	# TohriSDK build
	#--------------------------------------
	PROJECT    :=plugin-dynamic-lib
	include $(TOHRI_SDK_BUILD_PATH)/Makefile_set_env.in
	OBJDIR     :=$(SDK_OUT_OBJ_BIN_DIR)/$(PROJECT)/take
	INSTALLDIR :=$(SDK_OUT_BIN_DIR)

	include $(TOHRI_SDK_BUILD_PATH)/Makefile_build_shared_lib.in
else
	#--------------------------------------
	# local build
	#--------------------------------------
	#Set a directory of object files
	OBJDIR     := obj
	#Set a directory to install
	INSTALLDIR := ../..
	include ../../../../../../build/Makefile_build_shared_lib.in
endif
