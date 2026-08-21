# roBa + Prospector + CODEX 初心者向け導入ガイド

更新日: 2026-08-21

このNOTEは、ファームウェアに慣れていない方が「どれを選ぶか」「どのUF2をどこへ書くか」「動かないとき何を戻すか」を上から順に確認できるようにした案内です。

この派生版は、[kumaさん（@kumamuk-git）が設計・公開しているroBa](https://github.com/kumamuk-git/roBa)と公式設定を基に、[carrefinhoさんのProspector](https://github.com/carrefinho/prospector)、[ZMK Firmware](https://github.com/zmkfirmware/zmk)などのオープンソース成果を組み合わせています。原作者とcontributorの皆さまに感謝します。詳しい謝辞と参照先は末尾にあります。

> [!IMPORTANT]
> この派生版はビルドと生成設定まで確認済みですが、実機での全構成の動作確認はまだ完了していません。最初は必ずUSB接続で確認し、元のUF2を手元に残してください。

## まず結論：どれを選べばよいか

| 手元の機器・目的 | 選ぶ構成 | 難しさ | PCへ接続する機器 |
|---|---|---:|---|
| roBa左右を普通に使いたい。Prospectorは使わない | **B. Prospectorなし左右分割** | 低 | roBa右 |
| roBa左だけを小型CODEXキーボードとして使いたい | **C. 左手単体CODEX** | 低 | roBa左 |
| Prospector画面、左右battery表示、dongle運用を使いたい | **A. Prospector構成** | 中 | Prospector |

迷った場合は、まず**B. Prospectorなし左右分割**を選んでください。従来のroBaに最も近く、問題の切り分けが簡単です。

## 用語は3つだけ

- **UF2**: 基板へコピーするファームウェアファイル。
- **central**: 左右の入力をまとめてPCへ送る親機。
- **peripheral**: キーやセンサーの入力をcentralへ送る子機。peripheralだけではPCへ文字を送れません。

## 用意するもの

- roBa左・右。左単体構成では左だけでよい。
- Prospector構成を選ぶ場合はProspector。
- Windows PC。
- **データ通信対応**USB Type-Cケーブル。充電専用ケーブルでは書き込めない。
- このrepositoryの[`firmware`](firmware)フォルダー。
- 念のため、現在正常に動いている元のUF2。

ローカルでZMKやwestをビルドする必要はありません。掲載済みUF2を書き込むだけなら、特別な開発環境は不要です。

## UF2対応表

### A. Prospector構成

| 書き込む機器 | UF2 |
|---|---|
| Prospector | [`firmware/prospector/roBa_prospector_dongle.uf2`](firmware/prospector/roBa_prospector_dongle.uf2) |
| roBa左 | [`firmware/prospector/roBa_L_peripheral.uf2`](firmware/prospector/roBa_L_peripheral.uf2) |
| roBa右 | [`firmware/prospector/roBa_R_peripheral.uf2`](firmware/prospector/roBa_R_peripheral.uf2) |

### B. Prospectorなし左右分割

| 書き込む機器 | UF2 |
|---|---|
| roBa左 | [`firmware/no-prospector/roBa_L_no_prospector_peripheral.uf2`](firmware/no-prospector/roBa_L_no_prospector_peripheral.uf2) |
| roBa右 | [`firmware/no-prospector/roBa_R_no_prospector_central.uf2`](firmware/no-prospector/roBa_R_no_prospector_central.uf2) |

### C. 左手単体CODEX

| 書き込む機器 | UF2 |
|---|---|
| roBa左 | [`firmware/left-standalone/roBa_L_codex_standalone.uf2`](firmware/left-standalone/roBa_L_codex_standalone.uf2) |

設定消去用UF2は全構成共通です。

- [`firmware/settings_reset.uf2`](firmware/settings_reset.uf2)

## UF2の書き込み方

1. 書き込む機器以外の電源を切る。取り違え防止のため、1台ずつ作業する。
2. 対象をUSBケーブルでPCへ接続する。
3. XIAO nRF52840のresetボタンを素早く2回押す。
4. WindowsにUSBメモリーのようなbootloader driveが表示されるまで待つ。
5. 対応表のUF2をdriveの一番上へコピーする。
6. コピー後にdriveが自動的に消え、基板が再起動すれば書き込み完了。

UF2コピー終了時にWindowsがエラーを表示することがあります。driveが自動で消えたために表示される既知の現象で、正常に再起動していれば書き込み成功の場合があります。ZMK公式の[Flashing Issues](https://zmk.dev/docs/troubleshooting/flashing-issues)も参照してください。

> [!CAUTION]
> UF2名と書き込み先を取り違えないでください。特に`peripheral`版をPC接続側へ書くと、故障ではなく役割の違いによってPCへ入力できません。

## B. Prospectorなし左右分割：おすすめ導入手順

1. 以前に別のcentralやProspectorを使っていた場合は、左右の両方へ`settings_reset.uf2`を書き込む。
2. reset後、左へ`roBa_L_no_prospector_peripheral.uf2`を書き込む。
3. 右へ`roBa_R_no_prospector_central.uf2`を書き込む。
4. 右の電源を先に入れ、数秒後に左を起動する。
5. 最初はPCと右をUSB接続し、キーとトラックボールを確認する。
6. USBで動いたら、必要に応じてWindowsのBluetooth設定で`roBa`をペアリングする。

この構成では、左はPCへ直接ペアリングしません。左は右centralへ入力を送り、右がPCへ出力します。

## C. 左手単体CODEX：おすすめ導入手順

1. 以前に左右分割で使っていた左には、最初に`settings_reset.uf2`を書き込む。
2. 再起動後、左へ`roBa_L_codex_standalone.uf2`を書き込む。
3. まずUSB接続で通常キーを確認する。
4. Bluetoothを使う場合は、Windowsから`roBa CODEX Left`を選ぶ。

Prospectorも右手も不要です。右側に物理的に付いているPMW3610トラックボールは使えません。

### 左手単体のCODEX操作

- CODEX layer切替: 左親指列の`LCTRL + MUHENKAN`を同時押し。
- CODEX layerから戻る: 同じ2キーをもう一度同時押し。
- 承認予約: CODEX layerで`A + G`を同時押しすると`F23`。
- CODEX layer中の左エンコーダー: `F17 / F16`。

`F13`〜`F24`の多くは予約キーです。CodexやOS側で割り当てるまでは、押しても目的のCodex操作にならないのが正常です。`F23`も自動承認ではありません。

## A. Prospector構成：おすすめ導入手順

Prospectorはcentralが入れ替わるため、3構成の中では手順が少し多くなります。

1. Prospector、roBa左、roBa右の**3台すべて**へ`settings_reset.uf2`を書き込む。
2. Prospectorへ`roBa_prospector_dongle.uf2`を書き込む。
3. 左へ`roBa_L_peripheral.uf2`を書き込む。
4. 右へ`roBa_R_peripheral.uf2`を書き込む。
5. ProspectorをUSBでPCへ接続し、先に起動する。
6. roBa左だけを起動し、数十秒待つ。
7. 次にroBa右を起動する。
8. 通常キー、左エンコーダー、右トラックボール、クリック、scroll、CODEX layer、画面を順に確認する。

左を先、右を後に起動するのは、Prospector画面の左右battery slotを安定させるためです。表示が逆になった場合は3台をsettings resetし、同じ順でやり直します。

## settings resetが必要なとき

次の場合に使います。

- Prospectorあり／なしを切り替えた。
- 左手単体と左右分割を切り替えた。
- 左右が接続しなくなった。
- 古いBluetooth登録を消して最初からやり直したい。

手順:

1. 構成に含まれる全機器へ`settings_reset.uf2`を書き込む。
2. reset後、各機器へ目的の通常UF2を書き戻す。
3. WindowsのBluetooth設定から古い`roBa`または`roBa CODEX Left`を削除する。
4. centralを先に起動し、peripheralを後から起動する。
5. Windowsと再ペアリングする。

`settings_reset.uf2`だけを書いた状態では通常キーボードとして動きません。必ず通常UF2を書き戻してください。ZMK公式も、splitのpairing情報を消すときは全パーツをresetし、その後通常ファームウェアへ戻すよう案内しています。

## 動かないときの確認表

| 症状 | 最初に確認すること |
|---|---|
| bootloader driveが出ない | resetを素早く2回押す。別のデータ対応USBケーブル／USBポートを試す |
| 左だけでは文字が出ない | 左にperipheral版を入れていないか確認。左右分割では右またはProspector centralが必要 |
| 左右がつながらない | 構成内の全機器をsettings resetし、通常UF2を書き戻す |
| Bluetoothで見つからない | 先にUSBで動作確認。Windowsの古い登録を削除し、centralを再起動 |
| 右トラックボールが動かない | Prospector構成とProspectorなし構成で、右用UF2を取り違えていないか確認 |
| 左手単体でトラックボールが動かない | 正常。トラックボールは右側にあるため左単体では使えない |
| Prospectorの左右表示が逆 | 3台をresetし、Prospector→左→右の順で起動・接続 |
| UF2コピー時にエラーが出る | driveが消えて再起動したなら正常終了の可能性。動作で確認 |
| 元に戻したい | settings reset後、保管していた公式／以前のUF2を書き戻す |

## どこまで確認済みか

確認済み:

- GitHub Actionsの7ターゲットすべて成功。
- ローカルWSLで対象UF2をクリーンビルド。
- 生成`.config`でcentral/peripheral、USB/BLE、Studio、EC11、PMW3610を確認。
- 生成`zephyr.dts`で通常CODEX comboと左手単体comboを確認。
- 掲載UF2のSHA-256一致。

未確認:

- 実機への全UF2書き込み。
- 実機でのBLE bondと長時間安定性。
- split経由のPMW3610 movement/scroll/click。
- Prospector実画面の表示順とbattery更新。
- CODEX予約キーを割り当てた後の実アプリ操作。

問題が起きた場合は、まずこの派生repository側で再現条件を整理してください。派生版固有の変更について、roBa、Prospector、ZMKの原作者へ直接サポートを求めないようお願いします。

## 技術記録

### 固定している依存revision

| 要素 | revision |
|---|---|
| ZMK | `acfd8e5ea76cf23ad1c9b6b99848f97a95224257` |
| Zephyr | `dacab4875df72109b96cc8977547a0dc04875bcd` |
| PMW3610 driver | `5e04553ab803d24405bd45621a41310ea3050e59` |
| Prospector module | `77a852293532879c992847e01db27abe4f94fa9f` |

現行roBaとの互換性を優先し、ZMK v0.3／Zephyr 3.5世代へ固定しています。Prospectorの新しいstatus screen branchは別世代を対象とするため混在させていません。

### CODEX layer

既存layer 0〜6を維持し、CODEXをlayer 7へ追加しています。通常構成のtoggleはposition`35 + 42`、承認予約は`15 + 16`。左手単体ではtoggleを`34 + 39`、承認予約を`10 + 14`へ変更しています。

直接割り当てている確認済みshortcut:

| 操作 | Windows |
|---|---|
| Quick Chat | Ctrl+Alt+N |
| 新しいchat/task | Ctrl+N |
| 前／次のchat | Ctrl+Shift+[ / Ctrl+Shift+] |
| Command menu | Ctrl+Shift+P |
| Settings | Ctrl+, |
| Dictation | Ctrl+Shift+D |
| 送信 | Enter |

未確認の操作を推測shortcutへせず、F13〜F24予約にしています。Codex Microのような実行中／待機中／完了状態との双方向連携は未実装です。

## 作者・謝辞・参照先

この派生版は、以下の方々とprojectが公開してくださった設計、firmware、driver、documentationの上に成り立っています。

### roBa

- 作者: **kumaさん / [@kumamuk-git](https://github.com/kumamuk-git)**
- roBa hardware、case、PCB、build guide: [kumamuk-git/roBa](https://github.com/kumamuk-git/roBa)
- 公式ZMK設定: [kumamuk-git/zmk-config-roBa](https://github.com/kumamuk-git/zmk-config-roBa)
- roBa v2 build guide: [doc/v2/buildguide_v2.md](https://github.com/kumamuk-git/roBa/blob/main/doc/v2/buildguide_v2.md)

roBaはKeyballから影響を受けた、BLE、分割カラムスタッガード、トラックボール、水平ロータリーエンコーダーを備えるキーボードとして公開されています。本派生版は公式設定を置き換えるものではなく、用途を追加するforkです。

### Prospector

- 作者: **[@carrefinho](https://github.com/carrefinho)**
- Prospector hardware、case、BOM、assembly資料: [carrefinho/prospector](https://github.com/carrefinho/prospector)
- ZMK moduleと表示機能: [carrefinho/prospector-zmk-module](https://github.com/carrefinho/prospector-zmk-module)

Prospector repository内には、さらにdongle displayやmodule documentationなど着想・実装元へのcreditsがあります。そちらのcreditsもあわせて尊重してください。

### ZMK Firmware

- 開発: **[ZMK contributors](https://github.com/zmkfirmware/zmk/graphs/contributors)**
- Repository: [zmkfirmware/zmk](https://github.com/zmkfirmware/zmk)
- 公式導入ガイド: [Installing ZMK](https://zmk.dev/docs/user-setup)
- 接続問題とsettings reset: [Connection Issues](https://zmk.dev/docs/troubleshooting/connection-issues)
- 永続設定: [Persistent Settings](https://zmk.dev/docs/config/settings)
- UF2書き込み問題: [Flashing Issues](https://zmk.dev/docs/troubleshooting/flashing-issues)

### PMW3610 driver

- この設定が参照するfork: [kumamuk-git/zmk-pmw3610-driver](https://github.com/kumamuk-git/zmk-pmw3610-driver)
- fork元: **[@inorichi](https://github.com/inorichi)** / [inorichi/zmk-pmw3610-driver](https://github.com/inorichi/zmk-pmw3610-driver)
- さらに基となった実装: **[@ufan](https://github.com/ufan)** / [ZMK pointer/trackpad work](https://github.com/ufan/zmk/tree/support-trackpad)

派生元の流れを省略せず、各実装者へ敬意を表します。

### Controller hardware

- XIAO nRF52840: [Seeed Studio公式Getting Started](https://wiki.seeedstudio.com/XIAO_BLE/)

### 本派生版

- 統合・構成・検証記録: [@ape36soundscape](https://github.com/ape36soundscape)
- 作業支援: OpenAI Codex
- Repository: [ape36soundscape/zmk-config-roBa](https://github.com/ape36soundscape/zmk-config-roBa)
- Branch: `feature/roba-prospector-codex-20260820`
- ファームウェア: [`firmware/`](firmware)
- 詳細設計: [`docs/OPERATING_MODES.md`](docs/OPERATING_MODES.md)

## ライセンスについて

- roBa hardware repositoryはGPL-3.0。
- Prospector hardware repositoryはCERN-OHL-P-2.0。
- Prospector ZMK moduleとZMK FirmwareはMIT。
- `zmk-config-roBa`およびPMW3610 forkでは、repository全体のライセンス表示や各ファイルのSPDXを個別に確認してください。

ライセンス、著作権、商標は各原作者・projectに帰属します。本NOTEのリンク先にある`LICENSE`、README、各ソースファイルのSPDX表記を常に優先してください。

## ファイルの正しさを確認する

掲載UF2のSHA-256は[`firmware/SHA256SUMS.txt`](firmware/SHA256SUMS.txt)にあります。

PowerShell例:

```powershell
Get-FileHash -Algorithm SHA256 .\roBa_L_codex_standalone.uf2
```

表示されたHashが`SHA256SUMS.txt`と一致すれば、ダウンロード中の破損がないことを確認できます。
