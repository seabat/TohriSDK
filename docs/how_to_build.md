Requirements
------------

+ Compiler  
+ C standard library  

### Compiler

GNU Compiler Collection (GCC)  
The gcc command can be used to confirm that the GCC is already installed on the system:

	gcc

An error message such as gcc: no input files indicates that the GCC is installed and ready to use.  

	gcc: no input files

If there is a message such as command not found, which usually indicates that it has not been installed.  

	such as command not found

### C standard library

glibc  
The locate command can be used to confirm that the glibc is already installed on the system:

	locate glibc

If it is on the system, the above command will probably generate many lines on the monitor screen.

---

How to build
------------

This section describes how to build all TohriSDK.  
Initialize the TohriSDK build environmnt.  

		$ source build/setup_env.sh

Build everything with make.  

		$ make
 
All builded objects are placed in $(SDK_OUT_OBJ_DIR).  
All application objects are placed in $(SDK_OUT_OBJ_BIN_DIR).  
All libbrary objects are placed in $(SDK_OUT_OBJ_LIB_DIR).  
All include files are placed in $(SDK_OUT_OBJ_INC_DIR).  

	TohriSDK/
	└ -PROJECT
	   └ - obj/ 
	       |- bin/
	       |- lib/ 
	       └ - include/ 

---

How to install
--------------

This section describes how to install all applications and librariess to a target directory.  
Initialize the TohriSDK build environmnt.  

		$ source build/setup_env.sh

 Install everything with make install.  

		$ make install  

All installed binaries are placed in $(SDK_OUT_BIN_DIR).  
All installed libraries are placed in $(SDK_OUT_LIB_DIR).  
All include files are placed in $(SDK_OUT_INC_DIR).  

	TohriSDK/
	└ -PROJECT
	    |- bin/
	    |- lib/ 
	    └ - include/ 

---

How to clean
------------

This section dessripbes how to clean all bins, libs and objs in TohriSDK.


		$ source build/setup_env.sh
		$ make clean  

---

How to add a application
------------------------

This section describes how to add a application in the TohriSDK.

### Create a new directry

Create a new directry under sources/apps/.  

   ex. sources/apps/newapp/  

### Put Makefile and sources  

Put Makefile and sources to the new directory.  

   ex.  
       sources/apps/newapp/Makefile  
       sources/apps/newapp/src/main.c  
       sources/apps/newapp/inc/common.h  

### Edit Makefile

See How to edit Makefile.  

### Add a new line in the root Makefile

Add a new line to each of three targets(all, clean and install) in Makefile under the root directory.  

	---- Makefile -----
	all : 
		cd $(SDK_SOURCES_APPS_DIR)/sampleApp; make
	clean : 
		cd $(SDK_SOURCES_APPS_DIR)/sampleApp; make clean
	install : 
		cd $(SDK_SOURCES_APPS_DIR)/sampleApp; make install
	-------------------

---

How to edit Makefile
--------------------

### common

<table>
    <tr>
        <th>item</th>
        <th>type</th>
        <th>deccription</th>
        </tr>
    <tr>
        <td>PROGRAM</td>
        <td>must</td>
        <td>アプリケーション名、ライブラリ名</td>
    </tr>
    <tr>
        <td>SRCS</td>
        <td>must</td>
        <td>ソースファイル名。Makefileからの相対パス。</td>
    </tr>
    <tr>
        <td>INCS</td>
        <td>optional</td>
        <td>インクルードファイル名。Makefileからの相対パス。<br> ライブラリをビルド際に設定する。設定したファイルは、ビルド後、アプリケーションからincludeされる。</td>
    </tr>
    <tr>
        <td>INCFLG</td>
        <td>optional</td>
        <td>includeファイルパス。<br>
		    TohriSDK/out/プロジェクト名/obj/includeがデフォルトでINCFLGに設定される。<br>
			ex. -I./inc
		</td>
    </tr>
    <tr>
        <td>CC</td>
        <td>must</td>
        <td>コンパイラを指定する。　ex. gcc</td>
    </tr>
    <tr>
        <td>AR</td>
        <td>optional</td>
        <td>arコマンドを指定する。スタティックビルドの際に使用する。　<br>ex. ar</td>
    </tr>
    <tr>
        <td>CFLAG</td>
        <td>optional</td>
        <td>make オプション　<br>ex. -W, -D_WIN32</td>
    </tr>
    <tr>
        <td>ARFLAG</td>
        <td>optional</td>
        <td>arオプション。スタティックビルドの際に使用する。　<br>ex. crsv</td>
    </tr>
    <tr>
        <td>COPY_FILES</td>
        <td>optional</td>
        <td>アプリケーションから参照するファイル。Makefileからの相対パス。<br> 
            SDKビルドの場合は、TohriSDK/out/プロジェクト名/data/$(PROJECT)/にファイルをコピーする。<br>
			ローカルビルドの場合、DATADIRに指定したディレクトリにファイルをコピーする。
        </td>
    </tr>
</table>

### SDK build

This build means the way of the section "How to buile" in this page.  

<table>
    <tr>
        <th>item</th>
        <th>type</th>
        <th>deccription</th>
        </tr>
    <tr>
        <td>PROJECT</td>
        <td>must</td>
        <td>アプリケーション名、ライブラリ名。ビルド時に生成されるオブジェクトのディレクトリとして使用する。</td>
    </tr>
    <tr>
        <td>INCFLG</td>
        <td>optional</td>
        <td>SDKにビルトインしているincludeファイルパス。　SDKのライブラリをリンクする際に使用する。<br>ex. -I$(SDK_OUT_OBJ_INC_DIR)/libsbt/inc</td>
    </tr>
    <tr>
        <td>STATIC_LIBS</td>
        <td>optional</td>
        <td>SDKにビルトインしているlibファイルパス。　SDKのライブラリをリンクする際に使用する。<br>ex. $(SDK_OUT_OBJ_LIB_DIR)/libsbt/libsbt.a</td>
    </tr>
    <tr>
        <td>OBJDIR</td>
        <td>option</td>
        <td>ビルド時に生成されるオブジェクトを格納するディレクトリとして使用する。<br>
            TohriSDK/out/プロジェクト名/obj/$(PROJECT)がデフォルトでOBJDIRに設定されるが、さらにオブジェクトを細分化したディレクトリに配置したいときは
            本変数を設定する。<br>
            ex. OBJDIR:=$(SDK_OUT_OBJ_BIN_DIR)/$(PROJECT)/server
        </td>
    </tr>
</table>

### Local build

This build uses a Makefile under an application or a library directory.  
A binary file and object files are created under an applicaton or a libaray directory.  

<table>
    <tr>
        <th>item</th>
        <th>type</th>
        <th>deccription</th>
        </tr>
    <tr>
        <td>OBJDIR</td>
        <td>must</td>
        <td>ビルド時に生成されるオブジェクトを格納するディレクトリとして使用する。</td>
    </tr>
    <tr>
        <td>INSTALLDIR</td>
        <td>must</td>
        <td>ビルド時に生成されるbin,libを格納するディレクトリとして使用する。</td>
    </tr>
    <tr>
        <td>DATADIR</td>
        <td>optional</td>
        <td>アプリケーションが使用するデータを格納するディレクトリを指定する。COPY_FILEと一緒に使用する。</td>
    </tr>
</table>
