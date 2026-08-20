# Codexへ渡す再実装・再検証用指示文

以下を新しいCodexセッションへ渡す。`[PATH]`だけ実際の環境に置き換える。

---

`[REPOSITORY_PATH]`のroBa ZMK設定を、既存機能を壊さず次の3モードで保守し、すべてクリーンビルドしてください。

1. Prospector central: roBa左右はBLE peripheral、ProspectorがUSB central。画面、左右battery、layer、右PMW3610 input forwardingを維持する。
2. Prospectorなし: roBa_LはBLE peripheral、roBa_RはPCへUSB/Bluetooth接続するcentral。PMW3610を維持する。
3. 左手単体: 専用shield`roBaCodexL`でsplitを無効化し、左手自身をUSB/Bluetooth HID、ZMK Studio端末にする。デバイス名は`roBa CODEX Left`。

依存commitを次へ固定し、branch追従へ戻さないでください。

- ZMK `acfd8e5ea76cf23ad1c9b6b99848f97a95224257`
- Zephyr `dacab4875df72109b96cc8977547a0dc04875bcd`
- PMW3610 `5e04553ab803d24405bd45621a41310ea3050e59`
- Prospector `77a852293532879c992847e01db27abe4f94fa9f`

実装条件:

- 最初にAGENTS.md、git status、manifest、build matrix、shield、keymapをまとめて確認する。
- ユーザーの未コミット変更と`NOTE.md`を編集・stageしない。
- 既存DevicetreeにないGPIOを推測しない。右EC11の実ピンは追加しない。
- `roBaCodexL.overlay`は`roBa_L.overlay`を再利用する。
- `config/roBaCodexL.keymap`で`ROBA_CODEX_LEFT_STANDALONE`を定義し、共有`roBa.keymap`をincludeする。
- `roBa_L_codex`や`roBa_L.keymap`という専用名は、通常`roBa_L`と候補探索が衝突するため使わない。
- 通常CODEX toggleはposition`35 42`、approval F23はCODEX限定`15 16`。
- 左単体だけtoggleを`34 39`、approvalをA+Gの`10 14`へ変更する。
- 承認は単一キーへ置かず、F23予約のままにする。
- 左単体SETTINGS layerからBT profile 0〜4、bootloader、clear、clear allへ到達可能にする。
- CODEX layer 7と`codex_shortcuts.h`を維持し、確認済みshortcutとF13〜F24予約を区別する。
- build.yamlへProspector一式、Prospectorなし左右、左単体、settings resetを含める。

ビルドはWindowsの`/mnt/c`ではなくWSL native filesystem上の隔離workspaceで行う。Pythonは専用venvを使う。ZMK v0.3 nanopbで互換問題が出た場合はvenvへ`grpcio-tools`を入れ、`setuptools<81`へ固定し、OS全体のPythonを変更しない。

ビルド成功だけで完了にせず、生成`.config`と`zephyr.dts`で役割、USB/BLE、Studio、EC11、PMW3610、keymap combo座標を確認する。`git diff --check`とSHA-256検証も行う。

成果物は`[OUTPUT_PATH]`へUF2、settings reset、SHA256SUMS、書き込み手順、制限事項とともに保存する。同種の安全な読み取り・ビルド確認はまとめて進め、細切れの確認を減らす。

Git stage、commit、push、PR、実機書き込みは別の外部変更として扱い、ユーザーの明示的な許可がある場合だけ実行する。

---
