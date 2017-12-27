#コンパイル対象
SRCS     := main.c \
			plugin_manager.c \
			plugin_matsu.c \
			plugin_take.c 

#最終ファイル
PROGRAM  := plugin_function 

#インクルードファイルディレクトリ
INCFLG := -I./inc

#CC,CFLAGはmake内で定義済みマクロ
#コンパイラのシェルを指定
CC     := gcc

#コンパイルオプションを指定
#  -Wallはすべてのワーニングを省略せずに要求するオプション
#  -O2は最適化レベル2を表す。2は最適化の推奨レベル。
CFLAGS := -Wall -O2

ifeq ($(TOHRI_SDK_USE),true)
	#--------------------------------------
	# TohriSDK
	#--------------------------------------
	PROJECT    :=plugin-function
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
