# 書き込み用ファームウェア

2026-08-21時点の固定依存からクリーンビルドしたUF2です。最初に利用する構成を1つ選び、対応しないUF2を混ぜないでください。

## 1. Prospector構成

| 機器 | UF2 |
|---|---|
| Prospector | [`prospector/roBa_prospector_dongle.uf2`](prospector/roBa_prospector_dongle.uf2) |
| roBa左 | [`prospector/roBa_L_peripheral.uf2`](prospector/roBa_L_peripheral.uf2) |
| roBa右 | [`prospector/roBa_R_peripheral.uf2`](prospector/roBa_R_peripheral.uf2) |

初回は3台すべてをsettings resetする。Prospectorを先に起動し、左を接続してから右を起動すると、画面の左右slotが安定しやすい。PCはProspectorへUSB接続する。

## 2. Prospectorなし・左右分割

| 機器 | UF2 |
|---|---|
| roBa左 | [`no-prospector/roBa_L_no_prospector_peripheral.uf2`](no-prospector/roBa_L_no_prospector_peripheral.uf2) |
| roBa右 | [`no-prospector/roBa_R_no_prospector_central.uf2`](no-prospector/roBa_R_no_prospector_central.uf2) |

1. 必要なら左右へ[`settings_reset.uf2`](settings_reset.uf2)を書き込む。
2. 左へperipheral UF2、右へcentral UF2を書き込む。
3. 右を先に起動し、次に左を起動する。
4. PCは右へUSB接続するか、Bluetooth名`roBa`とペアリングする。

左はPCへ直接接続せず、右centralだけを探す。Prospectorは不要。

## 3. 左手単体・疑似CODEX micro

roBa左へ[`left-standalone/roBa_L_codex_standalone.uf2`](left-standalone/roBa_L_codex_standalone.uf2)を書き込む。Prospectorと右手は不要で、USBまたはBluetooth名`roBa CODEX Left`として使用できる。

- CODEX layer切替: 左親指列の`LCTRL + MUHENKAN`（position 34 + 39）。
- 承認予約: CODEX layerで`A + G`（position 10 + 14）を同時押しすると`F23`。
- CODEX layer中の左EC11: `F17 / F16`。
- 右側にしかないPMW3610トラックボールは利用できない。

## settings reset

central/peripheralの役割を変更すると古いbondが接続を妨げることがある。その場合は次の順で行う。

1. resetを素早く2回押してbootloader driveを開く。
2. [`settings_reset.uf2`](settings_reset.uf2)をコピーする。
3. 自動再起動後、目的の通常UF2を書き込む。
4. Windows側の古いBluetooth登録を削除して再ペアリングする。

設定消去だけを書き込んだ状態では通常キーボードとして動かないため、必ず目的のUF2を書き戻す。

## ファイル検証

PowerShell例:

```powershell
Get-FileHash -Algorithm SHA256 .\roBa_L_codex_standalone.uf2
```

正しい値は[`SHA256SUMS.txt`](SHA256SUMS.txt)を参照する。

## 実機検証について

全対象はクリーンビルドし、生成`.config`と`zephyr.dts`を確認済み。実機への書き込み、BLE bond、トラックボール転送、Prospector実画面は未検証。
