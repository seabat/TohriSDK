c-mock-object
=============

introduction
------------

Wikipediaでは、オブジェクトについて以下のような定義がされている。  

	関連するデータを束ね、代入、演算、手続き（関数やメソッドなど）を介した受け渡しといった操作の対象にでき、またメッセージの受け手になれる実体をオブジェクトと呼ぶ

また、オブジェクト指向プログラミングの特徴については以下のような定義がされている。

	オブジェクト指向プログラミングとは、オブジェクトと呼ばれる機能の部品でソフトウェアを構成させるものであり、一般的に以下の機能や特徴を活用したプログラミング技法のことをいう。
	カプセル化（振る舞いの隠蔽とデータ隠蔽）
	インヘリタンス（継承） -- クラスベースの言語
	ポリモフィズム（多態性、多相性） -- 型付きの言語
	ダイナミックバインディング（動的束縛） -- 動的型付言語
	この機能を文法的に提供するプログラミング言語は、オブジェクト指向プログラミング言語 (OOPL; object-oriented programming language) と呼ばれる。これらの機能のうち、オブジェクト指向の考え方で不可欠なのは「カプセル化」の機能だけである。そのため、オブジェクト指向プログラミング言語の中には、カプセル化以外の機能については一部を提供していないものもある。

c-mock-objectは、上記"オブジェクト"に"カプセル化"の特徴を持たせたC言語で記述されたソースコード群である。  
インヘリタンスやポリモフィズム等の機能はC言語で実現可能であるが、ソースコードの可読性や生産性を低下せるものと考える。よって、c-mock-objectsには採用しない。  
それらの特徴を活かしたい場合は、もはやC++でプログラミングするべきである。  

architechar
-----------

+ I/F部  
+ implement部  

### I/F部  

+ オブジェクト公開ヘッダー  
+ implement部呼び出しソース  

sample  

	file_control.h
	file_control.c

### implement部  

+ データ部、関数部定義ヘッダー  
+ 関数実装ソース  

sample  

	file_control_impl.h
	file_control_impl.c

sample code
-----------

	#include "file_access.h"
	
	unsigned char      buf[50]       = {0};
	unsigned char      total_buf[256]= {0};
	int                ret           = 0;
	FileAccess*        pFileAccess   = NULL;
	
	pFileAccess = FileAccess_New( );
	ret = FileAccess_Open( pFileAccess, "rb", src_path );
	while(-1 < FileAccess_Read( pFileAccess, buf, total_buf, 50 )){
	}
	FileAccess_Close( pFileAccess );
	FileAccess_Delete( &pFileAccess );






