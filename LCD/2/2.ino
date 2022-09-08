#include <LiquidCrystal.h> // LCDのライブラリを使う

const int TrigPin = 2;  // 超音波センサーのTrigPinを2ピンに指定
const int EchoPin = 3;  // 超音波センサーのEchoPinを3ピンに指定
float TimeOfFlight = 0; // 超音波が飛んでいる時間を格納する変数
float distance = 0;     // 計算した距離を格納する変数

LiquidCrystal lcd( 5, 6, 9, 10, 11, 12 ); // LiquidCrystal型の変数を生成、使うピンの設定をしている

void setup() {
    lcd.begin(16, 2);            // ディスプレイの列数と行数を設定, (列, 行)
    lcd.clear();                 // LCDをクリアする
    lcd.setCursor(0, 0);         // カーソルの位置を(列, 行)に合わせる
    lcd.print("Hello, wonder!"); // LCDに文字を出力する

    Serial.begin( 9600 );
    pinMode( TrigPin, OUTPUT );  // TrigPinをOUTPUTに指定
    pinMode( EchoPin, INPUT );   // EchoPinをINPUTに指定
}

void loop() {
    // Pinの初期化
    digitalWrite(TrigPin, LOW);  
    delayMicroseconds(10);       // 10μs待機

    // 超音波を出力
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);

    // 超音波が帰ってくる時間を計測
    TimeOfFlight = pulseIn(EchoPin, HIGH);

    // 計測した時間が0越えていたら実行
    if (TimeOfFlight > 0) {
        TimeOfFlight = TimeOfFlight / 2;       // 往復する時間になっているので半分にする

        // 音速を340m/sとして距離の計算, cmへの換算
        distance = 340 * TimeOfFlight / 10000; //距離 = 速さ × 時間
        
        // 表示する文章を作成, float型のdistanceをString型に変換(小数点以下切り捨て)
        String str = "Distance:" + String(distance, 0) + " cm";

        lcd.clear();         // LCDをクリアする
        lcd.setCursor(0, 0); // カーソルの位置を(0, 0)に合わせる
        lcd.print(str);      // LCDにstrを出力する
    }
    
    delay(500); //500ms待機
}

