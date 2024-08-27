# MCCPC 2024 Summer

**(2024/8/3 20:45)** このページを公開しました。\
**(2024/8/15 xx:xx)** ルールの追記などを行いました。

## 概要

- 本コンテストは東京農工大学 MCC による有志コンテストです。MOFE開発チームは作問などに一切関係がありません。
- 本コンテストは MCC の夏合宿のイベントの一環で行われるため、オンサイト会場は設けていません。
    - 外部から参加する場合は「オープン参加」で参加登録をお願いします。
- コンテスト時間は 180 分です。
- 問題数は 13 問です。配点などは**配点**の項を参照してください。
- Writer : <span style="color:#0000ff">log_K</span>
- Tester : ?

## ルール

- 個人またはチームで参加可能です。チームで参加する場合は以下の**チームルール**の項も併せて従ってください。
- 再提出によるペナルティは 5 分です。
- コンテスト中のインターネットの参照・自作ライブラリの利用は許可されています。
    - ただし、**生成 AI および GitHub Copilot などの使用は禁止します。**
- コンテスト中のネタバレ行為は禁止されています。具体的には [AtCoder のコンテスト中のルール](https://info.atcoder.jp/overview/contest/rules) の「禁止事項 - AtCoderの問題についてのコンテスト中の言及」に準拠します。
- 利用できる言語・ライブラリについては [提出できる言語についての情報 | MOFE](https://mofecoder.com/languages) を参照してください。
- 問題は Writer・Tester 陣の想定した難易度順に並んでいます。
- MOFEの難易度表記は**満点解法の難易度**に従って設定されています。正の得点の得やすさではないことに注意してください。(易 Milk < Assam < Benihuki < Ceylon < Darjeeling < Earlgray < Flavor < ผักชี 難)
- Assam 以上の難易度のすべての問題には部分点が設定されています。後半の問題にも易しい部分点が設定されていることがあるため、**すべての問題に目を通すことを強く推奨します**。

## チームルール

- 2024/9/23 時点の AtCoder の Algorithm レーティングに応じて、以下のコストを定義します。
    |レーティング|色|コスト|
    |:--:|:--:|:--:|
    |$[2000, 9999)$|黄以上|$6$|
    |$[1600, 2000)$|青|$4$|
    |$[1200, 1600)$|水|$3$|
    |$[400, 1200)$|茶・緑|$2$|
    |$[0, 400)$|灰・未参加|$1$|
- チームは次の制約を満たしていなければなりません。
    - チームを構成する人数は $3$ 人以下である。
    - チームを構成する人のコストの総和が $6$ 以下である。
    - MCC に関しては合宿参加者などの都合により、「コストの総和が $6$ 以下であるが人数が $4$ 人のチーム」が発生する可能性があります。予めご容赦ください。
- コンテスト中にチーム内において直接の対話・各種チャットツールなどを用いてコミュニケーションを取ることは許可されています。
- コンテスト中にチーム内で複数の PC を用いることは許可されています。同時コーディングも同様に許可されています。

## 配点

|Problem|Score|Subtask|Difficulty|
|:-:|:--:|:--:|:--:|
|A|-|-|-|
|B|-|-|-|
|C|-|-|-|
|D|-|-|-|
|E|-|-|-|
|F|-|-|-|
|G|-|-|-|
|H|-|-|-|
|I|-|-|-|
|J|-|-|-|
|K|-|-|-|
|L|-|-|-|
|M|-|-|-|

---

※最終更新 : 2024/7/12

|Problem|Score|Subtask|Difficulty|問題名|Tester|
|:-:|:--:|:--:|:--:|:--:|:--:|
|A|100|-|Milk|MCC|kichi2004|
|B|100|-|Milk|Worship|kichi2004|
|C|150|50+100|Assam|Multiplication Table|kichi2004|
|D|150|50+100|Assam|Addition and Division|Nerve|
|E|200|50+150|Benihuki|MCC Sequence (Calculate Version)|totori|
|F|200|75+50+75|Benihuki|Second Shortest Path in Pseudotree|qLethon|
|G|250|75+50+125|Ceylon|Let's Meet by the Promised Time|qLethon|
|H|250|10+15+15+20+20+35+35+100|Ceylon|Agricultual Expression|qLethon|
|I|300|50+100+150|Darjeeling|Passing the Trash|kichi2004|
|J|300|50+250|Darjeeling|TUAT String 4|Nerve|
|K|300|50+250|Darjeeling|MCC Sequence (Construct Version)|totori|
|L|350|75+125+150|Earlgray|Emotional View|Nerve|
|M|350|50+50+250|Earlgray|Even Even Path|totori|

## 難易度設計意図

- 難易度 Milk : 学部1年前期相当の学生が確実に解けるレベル(部長オーダー)
- 難易度 Assam : AtCoder 茶 Diff
- 難易度 Benihuki : AtCoder 緑 Diff
- 難易度 Ceylon : Benihuki よりはむずい(このへんからお気持ち)
- 難易度 Darjeeling : Ceylon よりはむずい
- 難易度 Earlgray : ボス枠

## 難易度評価と想定解法

|#|A|B|C|D|E|F|G|H|I|J|K|L|M|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|Final|-|-|-|-|-|-|-|-|-|-|-|-|DFS で差分更新を前計算 $O(N)$|
|Hard|-|-|下 2 桁|算数 $O(T)$|後ろから $O(N)$|貪欲|ダイクストラ+にぶたん $O((M + Q) \log N)$|気合 $O(N+Q)$|頑張る $O(NM)$|ダブリング+にぶたん $O(N \log M)$|構文解析|偏角ソート+遅延セグ木 $O(N \log N)$|愚直木DP $O(N^2)$|
|Normal|-|-|-|-|累積和 $O(N^2)$|-|愚直 $O(NQ)$|BFS $(N)$|DP $O(NM^2)$|ダブリング+にぶたん $O(N (\log M)^2)$|-|全探索 $O(N^2)$|愚直木DP $O(N^2)$|
|Easy|-|-|やる|シミュレーション|全探索 $O(N^3)$|埋め込み|算数 $O(NQ)$|算数|全探索 $O(N^4)$|シミュレーション $O(NM)$|-|場合分け $O(N)$|愚直計算 $O(N^3)$|

主観難易度評価 (1 が最も易しくて、数字が大きくなるほど難しい)

|#|A|B|C|D|E|F|G|H|I|J|K|L|M|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|問題名|MCC|Worship|Multiplication Table|Addition and Division|MCC Sequence (Calculate Version)|MCC Sequence (Construct Version)|Let's Meet by the Promised Time|Second Shortest Path in Pseudotree|TUAT String 4|Passing the Trash|Agricultual Expression|Emotional View|Subtree Flip Path Count|
|難易度|Milk|Milk|Assam|Assam|Benihuki|Benihuki|Ceylon|Ceylon|Darjeeling|Darjeeling|Darjeeling|Earlgray|Earlgray|
|配点|100|100|150|150|200|200|250|250|300|300|300|350|350|
|Final|-|-|-|-|-|-|-|-|-|-|-|-|10|
|Hard|-|-|2|3|5|5|6|7|7|8|*|9|9|
|Normal|-|-|-|-|4|-|4|4|6|6|-|5|7|
|Easy|1|1|1|1|2|3|3|3|2|2|-|2|4|

## 進捗表

※最終更新 : 2024/7/12

|#|問題名|問題ID|問題文初稿|サンプル作成|MOFE移植|ACコード|ケース生成|Validate|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|A|MCC|190|*|*|*|*|*|*|
|B|Worship|191|*|*|*|*|*|*|
|C|Multiplication Table|192|*|*|*|*|*|*|
|D|Addition and Division|193|*|*|*|*|*|*|
|E|MCC Sequence (Calculate Version)|194|*|*|*|*|*|*|
|F|Second Shortest Path in Pseudotree|195|*|*|*||||
|G|Let's Meet by the Promised Time|199|||||||
|H|Agricultural Expression|198|*|*|*|*|*|*|
|I|Passing Trash|197|*|*|*|*|*|*|
|J|TUAT String 4|196|*|*|*|*|*|*|
|K|MCC Sequence (Construct Version)|203|*|*|*|*|*|*|
|L|Emotional View|202|*|*|*|*|*|*|
|M|Even Even Path|201|*|*|*|*|*|*|
