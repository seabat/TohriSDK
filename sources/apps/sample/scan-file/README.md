
scan-file
=========

概要
-------------

ディレクトリの階層を再帰的に巡回し、キーワードで開始する行を表示する

    search_file keyword [directory]

- keyword: 検索文字列
- directory: 巡回を解するディレクトリ。フルパスで指定する。引数がない場合は、カレントディレクトリから巡回を開始。

カスタマイズ
-------------

### ファイルツリー表示 ###

スキャンしたディレクトリとファイルを ディスプレイすれば tree コマンド実行結果のような
ファイルツリーを表示できる。

1. scan_dir() の printf(3) がコメントアウトしているので解除する
2. scan_dir() の scan_file() 呼び出し行をコメントアウトする。


### キーワードを含む行を表示

キーワードが行のどこかに存在する場合はその行を表示する。

scan_file() を以下の用に変更する

         ret = strstr(buf, KEYWORD);
         if (ret != NULL) {
    -        if (0 == (ret - buf)) {
                // Check if the searching string starts the beginning of the line 
                printf("%s", buf);
    -        }
         }


