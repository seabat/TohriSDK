sbt-web-server
==============

---

サーバー側
-----------

### 設定  

1. ソケットのネットワークアドレス種別を設定  
   以下のdefineのうち、１つだけを有効にする。  

		FEATURE_SOCKET_ANY_ADDRESS
		FEATURE_SOCEKT_ONE_ADDRESS
		FEATURE_SOCKET_NO_ADDRESS

   ソースファイル上で設定する場合、以下のようにコーディングする。  
   例：FEATURE_SOCKET_NO_ADDRESS  

		#define FEATURE_SOCKET_NO_ADDRESS

   Makefileで設定する場合は socket-inet/server/Makefilem に以下を設定する。
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

ビルド  

		$ ./server/make

### 実行 ###

実行  

		$ ./sbt_web_server

FEATURE_SOCEKT_ONE_ADDRESSが有効の状態でビルドした場合、引数にsocketのアドレスとポー番号を指定できる。  

		$ ./sbt_web_server 192.168.11.12 10000

---

クライアント側
---------------

sbt_web_serverのsocketに以下のデータを送信する。  

	"GET /index.html HTTP/1.0\r\n\r\n"

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

ビルド  

		$ ./client/make

### 実行 ###

実行  

		$ ./sbt_web_client

FEATURE_SOCEKT_ONE_ADDRESSが有効の状態でビルドした場合、引数にsocketのアドレスとポー番号を指定できる。  

		$ ./sbt_web_client 192.168.11.12 10000

テスト
-------

ブラウザを起動し、サーバー側のsocketのアドレスとポート番号にアクセスする。  

	http://192.168.11.2:10000/index.html

上記にアクセスするとアプリケーション"sbt_web_server"の"../data/index.html"を取得できる。  

