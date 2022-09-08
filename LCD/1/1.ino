#include <LiquidCrystal.h> // LCDのライブラリを使う

LiquidCrystal lcd( 5, 6, 9, 10, 11, 12 ); // LiquidCrystal型の変数を生成、使うピンの設定をしている

void setup() {
    lcd.begin(16, 2);            // ディスプレイの列数と行数を設定, (列, 行)
    lcd.clear();                 // LCDをクリアする
    lcd.setCursor(0, 0);         // カーソルの位置を(列, 行)に合わせる
    lcd.print("Hello, wonder!"); // LCDに文字を出力する
}

void loop() {
   
}