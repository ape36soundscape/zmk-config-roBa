# roBa運用モードと設計記録

## 全体像

```text
Prospector mode
roBa_L peripheral ─┐
                   ├─ BLE split ─> Prospector central ─ USB HID ─> PC
roBa_R peripheral ─┘
  └─ PMW3610 raw input forwarding

No-Prospector mode
roBa_L peripheral ─ BLE split ─> roBa_R central ─ USB/BLE HID ─> PC

Left standalone mode
roBa_L standalone ─ USB/BLE HID ─> PC
```

## 固定バージョン

| 要素 | commit |
|---|---|
| ZMK | `acfd8e5ea76cf23ad1c9b6b99848f97a95224257` |
| Zephyr | `dacab4875df72109b96cc8977547a0dc04875bcd` |
| PMW3610 driver | `5e04553ab803d24405bd45621a41310ea3050e59` |
| Prospector module | `77a852293532879c992847e01db27abe4f94fa9f` |

## Prospector mode

Prospectorをキーなしsplit centralとし、左右を2台のBLE peripheralとして接続する。PCへの出力はProspectorのUSB HID。右PMW3610のraw input eventは`zmk,input-split`でcentralへ送り、pointer、700 msの一時MOUSE layer、16 count単位のscrollをcentral側で処理する。

Prospector画面ではactive layer、左右接続状態、battery proxyを有効化している。左右表示slotはbond順に依存するため、settings reset後は左、右の順に接続する。

## Prospectorなし mode

公式構成と同様にroBa_Rをsplit centralとして残した。左はBLE peripheral、右がPC用USB/Bluetooth HIDとPMW3610処理を担当する。Prospectorがなくても左右分割として機能するが、左peripheral単体ではPCへ接続しない。

## 左手単体CODEX mode

underscoreを含まない専用shield名`roBaCodexL`を使用する。これはZMKのkeymap prefix探索で通常`roBa_L`と衝突するのを避けるためである。

- split無効。
- USB/Bluetooth HID、ZMK Studio、左EC11有効。
- デバイス名`roBa CODEX Left`。
- `config/roBaCodexL.keymap`が専用マクロを定義して共有`roBa.keymap`をincludeする。
- CODEX toggleはposition `34 39`、承認予約F23は`10 14`。
- SETTINGS layerからBluetooth profile 0〜4、bootloader、profile clear、clear allへ左手だけで到達できる。

## CODEX layer 7

既存layer 0〜6、automouse layer 4、scroll layer 5を維持し、CODEXをlayer 7へ追加した。

確認済みの直接shortcut:

- Quick Chat: Ctrl+Alt+N
- New Chat: Ctrl+N
- Previous/Next Chat: Ctrl+Shift+[ / ]
- Command menu: Ctrl+Shift+P
- Settings: Ctrl+,
- Dictation: Ctrl+Shift+D
- Send: Enter

`F13`〜`F24`はFocus、Interrupt、Voice、Reasoning、Review、Debug、Refactor、agent移動、Approve、Decline等の予約キーを含む。ファームウェアだけではCodex操作にならず、Codex/OS側で明示的な割り当てが必要。承認予約F23は常に2キーcomboで、単一キーへ置かない。

## 検証結果

- Prospector左右peripheral、dongle、settings resetをクリーンビルド済み。
- Prospectorなし左右、左手単体をクリーンビルド済み。
- 通常keymap: toggle `35 42`、approval `15 16`。
- 左手単体keymap: toggle `34 39`、approval `10 14`。
- 左peripheral: split/BLE、centralなし、EC11有効。
- 右central: split central、USB/BLE、Studio、PMW3610有効。
- 左単体: split無効、USB/BLE、Studio、EC11有効。

## 既知の制限

- 実機への書き込みとBLE接続は未検証。
- Prospector画面とPMW3610 input forwardingは静的検証およびリンク成功まで。
- 公式Devicetreeで実ピンが定義されているエンコーダーは左だけ。右EC11のGPIOは推測していない。
- Codexの実行中／待機中／完了状態との双方向同期は未実装。
- 固定したZMK v0.3 / Zephyr 3.5由来のdeprecated警告は残る。
