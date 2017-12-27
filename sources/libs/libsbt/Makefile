PROGRAM :=libsbt.a

#コンパイル対象
SRCS    :=src/sbt_log.c \
		src/sbt_file.c \
		src/sbt_string.c \
		src/sbt_thread.c \
		src/sbt_alloc.c \
		src/sbt_web.c \
		src/sbt_androidxml.c 

INCS    :=inc/sbt_alloc.h \
		inc/sbt_file.h \
		inc/sbt_log.h \
		inc/sbt_string.h \
		inc/sbt_thread.h \
		inc/sbt_web.h \
		inc/sbt_androidxml.h 

INCFLG :=-I./inc

# 定義済みマクロの再定義
CC     :=gcc                      #コンパイラのシェルを指定
AR     :=ar
CFLAGS :=-Wall -O2                #コンパイルオプションを指定
                                   #  -Wallはすべてのワーニングを省略せずに要求するオプション
                                   #  -O2は最適化レベル2を表す。2は最適化の推奨レベル。
CFLAGS +=-DUSE_SBT_LOG_MACRO
ARFLAG :=crsv

ifeq ($(TOHRI_SDK_USE),true)
	#--------------------------------------
	# TohriSDK
	#--------------------------------------
	PROJECT    :=libsbt
	include $(TOHRI_SDK_BUILD_PATH)/Makefile_set_env.in
	include $(TOHRI_SDK_BUILD_PATH)/Makefile_build_static_lib.in
else
	#--------------------------------------
	# local build 
	#--------------------------------------
	#Set a directory of object files
	OBJDIR:= obj
	#Set a directory to install
	INSTALLDIR :=.
	include ../../../build/Makefile_build_static_lib.in
endif

