# 使い方
* `.secret/atcoder_login.json`に以下のように入力する。
```
{
    "username": (ユーザー名),
    "password": (パスワード)
}
```
* `config/thismatch.json`にウェブサイトのアドレスから必要な情報を入力する。フォーマットは以下のとおり。
```
https://atcoder.jp/contests/ (contest) /tasks/ (taskname) _ (問題番号)
```
* `python ./sandbox.py -judge [a,b,c,...]`で
    * `[a,b,c,...]`問題の入出力例をダウンロード
    * `[a,b,c,...].cpp`から`exe`ファイルを作成
    * 各入出力を実行し、すべて`AC`なら提出

## ショートカットの登録
* `F1`キーを押し、出てきた欄に`keyboard`と入力する。
* 「基本設定：キーボードショートカットを開く(JSON)」（JSONがついているほう）を開く
* `keybindings.json`が出てくるので以下のように設定する。
```
[
    {
        "key": "ctrl+shift+t",
        "command": "workbench.action.tasks.runTask",
        "args": "submit"
    },
    {
        "key": "ctrl+shift+c",
        "command": "workbench.action.tasks.runTask",
        "args": "cleanio"
    }
]
```
* 上記の設定後`ctrl+shift+t`キーを押すと、アクティブなウインドウにあるプログラムに対して（コンパイルされたのち）`sandbox.py -judge`が実行される。

## ライブラリの利用
* テストのときは`#include"lib/graph.hpp"`等と付け加える
* submitではベタでコピペしないと使えない