#include <LiquidCrystal.h> // LCDのライブラリを使う

const int TrigPin = 2;  // 超音波センサーのTrigPinを2ピンに指定
const int EchoPin = 3;  // 超音波センサーのEchoPinを3ピンに指定
float TimeOfFlight = 0; // 超音波が飛んでいる時間を格納する変数
float distance = 0;     // 計算した距離を格納する変数
int count = 0;          // 通行人数を格納する変数
bool passing = false;   // 人が通過しているかを格納するフラグ変数

LiquidCrystal lcd( 5, 6, 9, 10, 11, 12 ); // LiquidCrystal型の変数を生成、使うピンの設定をしている

void setup() {
    lcd.begin(16, 2);            // ディスプレイの列数と行数を設定, (列, 行)
    lcd.clear();                 // LCDをクリアする
    lcd.setCursor(0, 0);         // カーソルの位置を(列, 行)に合わせる

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
        
        /*
        // 距離が0~20cmのとき
        if(distance >= 0 && distance < 20){
            lcd.clear();                            // LCDをクリアする
            lcd.setCursor(0, 0);                    // カーソルの位置を(0, 0)に合わせる
            lcd.print("\xc4\xc3\xd3\xc1\xb6\xb2!"); // LCDに トテモチカイ! を表示
        }

        // 距離が20~60cmのとき
        else if(distance >= 20 && distance < 60){
            lcd.clear();                            // LCDをクリアする
            lcd.setCursor(0, 0);                    // カーソルの位置を(0, 0)に合わせる
            lcd.print("\xc1\xb6\xb2!");             // LCDに チカイ! を表示
        }
        
        // 距離が60~100cmのとき
        else if(distance >= 60 && distance < 100){
            lcd.clear();                            // LCDをクリアする
            lcd.setCursor(0, 0);                    // カーソルの位置を(0, 0)に合わせる
            lcd.print("\xc4\xb5\xb2!");             // LCDに トオイ! を表示
        }

        // その他(距離が100cm以上のとき)
        else{
            lcd.clear();                            // LCDをクリアする
            lcd.setCursor(0, 0);                    // カーソルの位置を(0, 0)に合わせる
            lcd.print("\xc4\xc3\xd3\xc4\xb5\xb2!"); // LCDに トテモトオイ! を表示
        }
        */

        // もし距離が60cm未満なら
        if(distance < 60){

          // もしpassingがfalseなら
          if(passing == false){
            passing = true;  // passingをtrueにする
            count++;         // countを１増やす(通行人を1人カウントする)
          }
        }

        // それ以外なら(距離が60cm以上なら)
        else{
          passing = false;   // passingをfalseにする
        }

        // 表示する文章を作成, int型のcountをString型に変換
        String str = "\xc2\xb3\xba\xb3\xc6\xdd\xca " + String(count) + " \xc6\xdd"; // ツウコウニンハ count ニン
        lcd.clear();         // LCDをクリアする
        lcd.setCursor(0, 0); // カーソルの位置を(0, 0)に合わせる
        lcd.print(str);      // LCDにstrを出力する
    }
    delay(500); //500ms待機
}