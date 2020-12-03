# 課題１
第7回、第8回で作成したデバイスドライバをベースに、オリジナリティーのある改造をして提出する。

## 改造内容
4個のLEDがくるくる回るように点灯します。回る方向は右と左で変更可能です。
10秒、30秒、60秒のタイマー機能を追加しました。

## 動作環境
以下の環境で動作確認を行っています。
* OS:Ubuntu 20.04.1 LTS

## 用意したもの
* Raspberry Pi 4 Model B (4GB RAM)
* ユニバーサル基盤(片面プリント)
* リード線
* 赤色LED 4個
* 抵抗220Ω　4個

## 回路について
![システム学　課題１　回路](https://user-images.githubusercontent.com/72900623/100960483-b46cdd80-3563-11eb-943d-fc8a9e206f0b.jpg)

画像で見て上のLEDをGPIO25,右のLEDをGPIO24,下のLEDをGPIO23,左のLEDをGPIO22にそれぞれに抵抗を付けて接続しています。

## 実行の準備
実行までの準備は以下の手順で行ってください。
* git clone https://github.com/wadordi/wado.git
* cd wado
* make
* sudo rmmod myled
* sudo insmod myled.ko
* sudo chmod 666 /dev/myled0

## 実行方法および動作
以下のように入力してください。echoの後の文字によって動作が変わります。
* echo 1 > /dev/myled0 
LEDが'0'で消灯、'1'で全点灯、'r'で右回りに点灯、'l'で左回りに点灯、'a'で10秒のタイマー、'b'で30秒のタイマー、'c'で60秒のタイマーといった具合です。
### rを入力した場合
https://youtu.be/DAnRMG6kbvo
'r'、'l'とした場合はその方向にLEDが回転しているように点灯します。
### aを入力した場合
https://youtu.be/PlpwtSiH110
'a'、'b'、'c'と入力した場合は1秒でLEDの光が回転し時間になるとすべてのLEDが点滅します。


