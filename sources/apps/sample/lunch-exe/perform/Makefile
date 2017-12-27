
SRCS          =	main.c

CROSS         =gcc
CC            =$(CROSS)

CFLAGS        =-O2 -g -DDEBUG

PROGRAM       =lunch_exe

INCFLG        =-I./inc

ifeq ($(TOHRI_SDK_USE),true)
	#--------------------------------------
	# TohriSDK
	#--------------------------------------
	PROJECT    :=lunch-exe/perform
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
