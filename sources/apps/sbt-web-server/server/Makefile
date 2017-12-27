#最終ファイル
PROGRAM := sbt_web_server

#コンパイル対象
SRCS    := src/main.c \
		   src/sws_socket.c \
		   src/sws_command.c \
		   src/sws_util.c

#インクルードファイルディレクトリ
INCFLG  := -I./inc

#CC,CFLAGはmake内で定義済みマクロ
#コンパイラのシェルを指定
CC      := gcc

#コンパイルオプションを指定
#  -Wallはすべてのワーニングを省略せずに要求するオプション
#  -O2は最適化レベル2を表す。2は最適化の推奨レベル。
CFLAGS  := -Wall -O2 -pthread

CFLAGS  +=-DFEATURE_SOCKET_ONE_ADDRESS

COPY_FILES := ../data/sbt-web-server/*.*

ifeq ($(TOHRI_SDK_USE),true)
	#--------------------------------------
	# TohriSDK build
	#--------------------------------------
	PROJECT    :=sbt-web-server
	include $(TOHRI_SDK_BUILD_PATH)/Makefile_set_env.in
	STATIC_LIBS:=$(SDK_OUT_OBJ_LIB_DIR)/libsbt/libsbt.a
	OBJDIR     :=$(SDK_OUT_OBJ_BIN_DIR)/$(PROJECT)/server
	include $(TOHRI_SDK_BUILD_PATH)/Makefile_build_app.in
else
	#--------------------------------------
	# local build 
	#--------------------------------------
	#Set a directory of object files
	INCFLG     +=-I../../../../out/aaa/obj/include
	STATIC_LIBS:=../../../../out/aaa/obj/lib/libsbt/libsbt.a
	#Set a directory to compile
	OBJDIR     := obj
	#Set a directory to install
	INSTALLDIR := .
	#Set a directory for data
	COPY_FILES :=
	include ../../../../build/Makefile_build_app.in
endif
