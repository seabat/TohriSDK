
ifeq ($(TOHRI_SDK_USE),true)
include build/Makefile_set_env.in

all : 
	@echo "******************************"
	@echo " BUILD START                 *"
	@echo "******************************"
	cd $(SDK_SOURCES_APPS_DIR)/sample/plugin-dynamic-lib; make
	cd $(SDK_SOURCES_APPS_DIR)/sample/plugin-fp; make
	cd $(SDK_SOURCES_APPS_DIR)/sample/sample-table; make
	cd $(SDK_SOURCES_APPS_DIR)/sample/skelton-program; make
	cd $(SDK_SOURCES_APPS_DIR)/sample/socket-inet; make
	cd $(SDK_SOURCES_APPS_DIR)/sample/socket-inet-varlen; make
	cd $(SDK_SOURCES_APPS_DIR)/sample/thread-join; make
	cd $(SDK_SOURCES_LIBS_DIR)/libsbt; make
	cd $(SDK_SOURCES_APPS_DIR)/test-libsbt; make
	cd $(SDK_SOURCES_CMOS_DIR)/file-access; make
	cd $(SDK_SOURCES_APPS_DIR)/sample/lunch-exe; make
	cd $(SDK_SOURCES_APPS_DIR)/sbt-web-server; make
	@echo "******************************"
	@echo " BUILD END                   *"
	@echo "******************************"

install : 
	@echo "******************************"
	@echo " INSTALL START               *"
	@echo "******************************"
	cd $(SDK_SOURCES_APPS_DIR)/sample/plugin-dynamic-lib; make install
	cd $(SDK_SOURCES_APPS_DIR)/sample/plugin-fp; make install
	cd $(SDK_SOURCES_APPS_DIR)/sample/sample-table; make install
	cd $(SDK_SOURCES_APPS_DIR)/sample/skelton-program; make install
	cd $(SDK_SOURCES_APPS_DIR)/sample/socket-inet; make install
	cd $(SDK_SOURCES_APPS_DIR)/sample/socket-inet-varlen; make install
	cd $(SDK_SOURCES_APPS_DIR)/sample/thread-join; make install
	cd $(SDK_SOURCES_LIBS_DIR)/libsbt; make install
	cd $(SDK_SOURCES_APPS_DIR)/test-libsbt; make install
	cd $(SDK_SOURCES_CMOS_DIR)/file-access; make install
	cd $(SDK_SOURCES_APPS_DIR)/sample/lunch-exe; make install
	cd $(SDK_SOURCES_APPS_DIR)/sbt-web-server; make install
	@echo "******************************"
	@echo " INSTALL END                 *"
	@echo "******************************"

clean :
	@echo "******************************"
	@echo " CLEAN START                 *"
	@echo "******************************"
	cd $(SDK_SOURCES_APPS_DIR)/sample/plugin-dynamic-lib; make clean
	cd $(SDK_SOURCES_APPS_DIR)/sample/plugin-fp; make clean
	cd $(SDK_SOURCES_APPS_DIR)/sample/sample-table; make clean 
	cd $(SDK_SOURCES_APPS_DIR)/sample/skelton-program; make clean
	cd $(SDK_SOURCES_APPS_DIR)/sample/socket-inet; make clean
	cd $(SDK_SOURCES_APPS_DIR)/sample/socket-inet-varlen; make clean
	cd $(SDK_SOURCES_APPS_DIR)/sample/thread-join; make clean
	cd $(SDK_SOURCES_LIBS_DIR)/libsbt; make clean
	cd $(SDK_SOURCES_APPS_DIR)/test-libsbt; make clean
	cd $(SDK_SOURCES_CMOS_DIR)/file-access; make clean
	cd $(SDK_SOURCES_APPS_DIR)/sample/lunch-exe; make clean
	cd $(SDK_SOURCES_APPS_DIR)/sbt-web-server; make clean
	rm -rf $(SDK_OUT_BIN_DIR)
	rm -rf $(SDK_OUT_LIB_DIR)
	rm -rf $(SDK_OUT_INC_DIR)
	rm -rf $(SDK_OUT_DATA_DIR)
	rm -rf $(SDK_OUT_OBJ_DIR)
#	rm -rf out/$(BUILD_TARGET)
	@echo "******************************"
	@echo " CLEAN END                   *"
	@echo "******************************"
else
all : 
	@echo "Please execute \"source build/setup_env.sh\""
install : 
	@echo "Please execute \"source build/setup_env.sh\""
clean :
	@echo "Please execute \"source build/setup_env.sh\""
endif

