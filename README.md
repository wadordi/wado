# 課題１
第7回、第8回で作成したデバイスドライバをベースに、オリジナリティーのある改造をして提出する。

# 動作環境
以下の環境で動作確認を行っています。
* OS:Ubuntu 20.04.1 LTS

# 用意したもの
* Raspberry Pi 4 Model B (4GB RAM)
* ユニバーサル基盤(片面プリント)
* リード線
* 赤色LED 4個
* 抵抗220Ω　4個

# 回路について
![システム学　課題１　回路](https://user-images.githubusercontent.com/72900623/100960483-b46cdd80-3563-11eb-943d-fc8a9e206f0b.jpg)

画像で見て上のLEDをGPIO25,右のLEDをGPIO24,下のLEDをGPIO23,左のLEDをGPIO22にそれぞれに抵抗を付けて接続しています。

# 実行の準備
実行までの準備は以下の手順で行ってください。
* git clone https://github.com/wadordi/wado.git
* cd wado
* make
* sudo rmmod myled
* sudo insmod myled.ko
* sudo chmod 666 /dev/myled0
