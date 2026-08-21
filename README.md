# zmk-config-roBa — Prospector / CODEX variants

<img src="keymap-drawer/roBa.svg" alt="roBa keymap" >

このブランチは公式roBa設定を基に、既存の右central構成を残したままProspector dongleと左手単体CODEX構成を追加したものです。

初めて導入する方は、最初に[初心者向け導入ガイド（NOTE.md）](NOTE.md)を読んでください。構成の選び方、UF2の対応表、書き込み、ペアリング、復旧方法、原作者と参照先を1ページにまとめています。

## 選べる3つの構成

| 構成 | PCへ接続する機器 | roBa左 | roBa右 | 特徴 |
|---|---|---|---|---|
| Prospector | Prospector | BLE peripheral | BLE peripheral | 画面、左右battery表示、右PMW3610入力転送 |
| Prospectorなし | roBa右 | BLE peripheral | central | 従来に近い左右分割。USB/Bluetooth対応 |
| 左手単体CODEX | roBa左 | standalone | 不要 | USB/Bluetooth、左EC11、CODEX layer 7 |

書き込み用UF2と具体的な手順は、[firmware/README.md](firmware/README.md)にまとめています。

## ドキュメント

- [運用モードと設計](docs/OPERATING_MODES.md)
- [再実装・再検証用のCodex指示文](docs/CODEX_IMPLEMENTATION_PROMPT.md)
- [ファームウェアのSHA-256](firmware/SHA256SUMS.txt)

## 重要事項

- centralを切り替える場合は、対象機器へ`settings_reset.uf2`を書き、Bluetoothを再ペアリングしてください。
- 左手peripheralはPCへ直接ペアリングしません。Prospectorなし構成では右centralへ接続します。
- 左手単体版のBluetooth名は`roBa CODEX Left`です。
- `F13`〜`F24`にはCodex機能の予約キーが含まれます。OSまたはCodex側で割り当てるまでは通常のFキーです。
- ビルドと生成設定の静的検証は完了していますが、実機への書き込みと無線接続は未検証です。

## ビルド

GitHub Actionsのmatrixは`build.yaml`にあります。依存commitは`config/west.yml`で固定しています。

主要artifact:

- `roBa_L_peripheral`
- `roBa_R_peripheral`
- `roBa_prospector_dongle`
- `roBa_L_no_prospector_peripheral`
- `roBa_R_no_prospector_central`
- `roBa_L_codex_standalone`
- `settings_reset`
