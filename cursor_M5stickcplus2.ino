/*.
⠄⠄⠄⠸⣿⡛⠷⣦
⢀⣄⠄⠄⠈⠻⣦⡀⢙⣤
⢸⡟⢷⣄⠄⠄⣨⡷⠄⢻⡇
⠘⣷⡀⠙⠷⠾⠋⠄⠄⠺⣧⣀⣴⠶⢶⡄
 ⠈⠻⢶⣤⣤⣤⣄⣀⣀⣼⠟⠁⠄⢠⣿⠶⣦⡀
       ⠈⢩⡿⠋⠙⠛⠷⣦⣴⣟⠁⠄⣸⣧⣤⣄
      ⣰⡟⠁⠄⠄⠄⠄⠄⠉⠛⢷⣾⠋⠄⠄⣿⣤⣄⡀
     ⣼⠏⠄⠄⠄⣠⡶⠶⣶⣤⣤⣾⡃⠄⣠⡾⠋⠄⢙⣷
     ⢿⡄⠄⠄⠄⠉⠁⠄⠈⠻⣿⣌⠻⢿⣿⠄⠄⣠⣾⡇
     ⠈⢿⣆⠄⠄⠄⠄⠄⠄⠄⠈⠻⣷⡀⠻⠷⠾⢿⣼⣧
        ⠙⣷⠄⠄⠄⠄⠄⠄⠄⠄⠈⠻⣧⡀⠄⠄⠙⠛⠛⠛⠷⣦⡀
          ⢿⣄⠄⠄⠄⠄⠄⠄⠄⠄⠈⢻⣦⠄⠄⣠⡶⢷⣄⠈⢿⡄
           ⠹⣧⠄⠄⠄⠄⠄⠄⠄⠄⢸⣿⠄⢼⡋⠄⠄⠙⢷⣼⡇
            ⢹⡇⠄⠄⠄⠄⠄⠄⠄⠄⢻⣆⠈⠻⣦⡀⠄⠄⠙⠃
            ⢸⡇⠄⠄⠄⠄⠄⠄⠄⠄⢸⡟⠻⣶⣬⣿⡆
           ⢠⡾⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⣧⡀
           ⣿   ЫЫЫ,       ⢸⡇
           ⣿              ⢸⡇
           ⠿  Мы профи    ⠸⠇
*/
#include <M5StickCPlus2.h>
float accX, accY, accZ;
const uint16_t cursoridl [] PROGMEM = {
0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0x0000,
0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0x0000, 0xffff, 0xffff
};
void setup() {
 auto cfg = M5.config();
StickCP2.begin(cfg);
M5.Imu.init();
  Serial.begin(9600);
  M5.Lcd.setRotation(1);
}

void loop() {
   M5.Lcd.clear();
    M5.Imu.getAccelData(&accX, &accY, &accZ);
int y = map(accY * 10000, -10000, 10000, 0, 240);
int x = map(accX * 10000, -10000, 10000, 0, 135);
 M5.Lcd.drawBitmap(y, x, 4, 4, cursoridl);

}

