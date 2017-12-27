#TEST build start
PROGRAM=test_libsbt
SRCS=test.c


# 定義済みマクロの再定義
CC      := gcc                      #コンパイラのシェルを指定
AR      := ar
CFLAGS  += -Wall -O2                #コンパイルオプションを指定
                                    #  -Wallはすべてのワーニングを省略せずに要求するオプション
                                    #  -O2は最適化レベル2を表す。2は最適化の推奨レベル。
								    #
CFLAGS  += -pthread                 # libsbt.aはpthread APIを使用している

ARFLAG  := crsv

ifeq ($(TOHRI_SDK_USE),true)
	#--------------------------------------
	# TohriSDK
	#--------------------------------------
	PROJECT    :=test_libsbt
	include $(TOHRI_SDK_BUILD_PATH)/Makefile_set_env.in
	STATIC_LIBS:=$(SDK_OUT_OBJ_LIB_DIR)/libsbt/libsbt.a
	include $(TOHRI_SDK_BUILD_PATH)/Makefile_build_app.in
else
	#--------------------------------------
	# local build 
	#--------------------------------------
	INCFLG     :=-I../../../sources/libs/libsbt/inc
	STATIC_LIBS:=../../../sources/libs/libsbt/obj/libsbt.a
	OBJDIR     := obj
	INSTALLDIR :=.
	include ../../../build/Makefile_build_app.in
endif

