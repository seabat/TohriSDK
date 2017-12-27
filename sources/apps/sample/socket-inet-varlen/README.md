socket-inet-varlen
====================

---

サーバー側
-----------

### 設定  

1. ソケットのネットワークアドレス種別を設定  
   以下のdefineのうち、１つだけを有効にする。  

		FEATURE_SOCKET_ANY_ADDRESS
		FEATURE_SOCEKT_ONE_ADDRESS
		FEATURE_SOCKET_NO_ADDRESS

   ソースファイルで指定する場合、以下のようにコーディングする。  
   例：FEATURE_SOCKET_NO_ADDRESS  

		#define FEATURE_SOCKET_NO_ADDRESS

   Makefileで指定する場合は socket-inet/server/Makefilem に以下を設定する。
   例：FEATURE_SOCKET_ONE_ADDRESS  

		CFLAGS +=-DFEATURE_SOCEKT_ONE_ADDRESS

2. サーバー側のネットワークアドレスを設定  
   FEATURE\_SOCKET\_ONE\_ADDRESSを指定した場合、 
   socket-inet/server/src/main.c の以下のdefineにサーバーのネットワークカードに割り当てられたアドレスを設定する。  

		#define SERVER_ADDRESS "192.168.11.2"

   ただし、実行ファイル起動時の第一引数にアドレスが指定されれば、その値で上書きされる。  

3. サーバー側のソケット通信用のポート番号を設定  
   FEATURE\_SOCEKT\_ONE\_ADDRESSを指定した場合、 
   socket-inet/server/src/main.c の以下のdefineにサーバーのport番号を設定する。  

		#define SERVER_PORT 数値

4. サーバー側のコマンドのバッファ  
   socket-inet/server/src/main.c の以下のdefineに値を設定する。  

		#define BUFFER_SIZE 数値

### ビルド  

1. server側をビルド  

		$ ./server/make

### 実行 ###
1. server側を実行  

		$ ./server/socket_inet_varlen-server

---

クライアント側
---------------

### 設定  

1. ソケットのネットワークアドレス種別を設定  
   サーバー側と同じdefineを設定  

   ソースファイルで指定する場合、以下のようにコーディングする。  
   例：FEATURE_SOCKET_NO_ADDRESS  

		#define FEATURE_SOCKET_NO_ADDRESS

   Makefileで指定する場合は socket-inet/client/Makefile に以下を設定する。  
   例：FEATURE_SOCKET_ONE_ADDRESS  

		CFLAGS +=-DFEATURE_SOCEKT_ONE_ADDRESS

3. サーバー側のネットワークアドレスを設定  
   FEATURE\_SOCKET\_ONE\_ADDRESSを指定した場合、 
   socket-inet/client/src/main.c の以下のdefineにサーバーのネットワークカードに割り当てられたアドレスを設定する。  

		#define SERVER_ADDRESS "192.168.11.2"

   ただし、実行ファイル起動時の第一引数にアドレスが指定されれば、その値で上書きされる。  

4. サーバー側のソケット通信用のポート番号を設定  
   FEATURE\_SOCEKT\_ONE\_ADDRESSを指定した場合、 
   socket-inet/client/src/main.c の以下のdefineにサーバーのport番号を設定する。  

		#define SERVER_PORT 数値

   ただし、実行ファイル起動時の第二引数にポート番号が指定されれば、その値で上書きされる。  

### ビルド  

1. client側をビルド  

		$ ./client/make

### 実行 ###
1. client側を実行  

		$ ./client/socket_inet_varlen-client

