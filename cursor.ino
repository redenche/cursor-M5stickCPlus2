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
//многое тут я не написал но мб позже
#include <M5StickCPlus2.h>
float sens = 2.5;//чувствительность гироскопа/скорость курсора... можешь поменять если не понравится мои настройки
int y, x;//координаты курсора
float accX, accY, accZ;//переменные для акселиометра
bool t = false;//переменная для переключателя
int xswitch, c;//переменная для отображеия переключателя
int xregulator = 20;//переменная для размещения ползунка
bool r = false;//переменная для регулировки ползунка
bool s = false;//переменная для цикла всплывашки
bool h = false;//переменная для чекбокса
//координаты для всплывашки
  int xs;
  int ys;
//переменные для кнопки
const int BTNX = 45;
const int BTNY = 10;
const int BTNWEIGHT = 30;
const int BTNHEIGHT = 30;
const int BTNCOLOR = BLUE;
const int BTNCOLOR1 = GREEN; 
unsigned long ltime; 
void setup() {
  //инициализация стика и акселиометра
  M5.begin();
  M5.Imu.init();
  //"интро"
  Serial.begin(9600);
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(RED);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println("cursor test");
   M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.println("binds: ");
      M5.Lcd.println("Btn A - standart click");
         M5.Lcd.println("Btn B - alt click");
            M5.Lcd.println("start in 5 seconds");
  delay(5000);
     M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE);
}
//спрайт курсора
const uint16_t cursoridl [] PROGMEM = {
0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0x0000,
0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0x0000, 0xffff, 0xffff
};
//отладочный спрайт
const uint16_t cursorprs [] PROGMEM = {
BLUE, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0x0000,
0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0x0000, 0xffff, 0xffff
};
//0xfff1 = 65521
//0xffff = 65535
void loop() {
  if(millis() - ltime >= 100){
    ltime = millis();
  M5.Lcd.clear();
  }
  //выводим интерфейс
 UI();
 //получаем координаты крч
  M5.Imu.getAccelData(&accX, &accY, &accZ);
 y = map(accY * sens * 10000, -10000, 10000, 0, 240);
 x = map(accX * sens * 10000, -10000, 10000, 0, 135);
//плотно ограничиваем чтоб багов не было... можешь удалить и проверить о чем я говорю
 y = constrain(y, 0, 230);
x = constrain(x, 0, 125);
//выводим курсор и обработка нажатий
cursor1();
//отладочная информация
 uint16_t o = M5.Lcd.readPixel(y, x);
M5.Lcd.setCursor(0,0);
M5.Lcd.setTextSize(1);
M5.Lcd.println(x);
M5.Lcd.print(y);
Serial.println(o);
delay(90);
}
void UI(){
  //предварительные настройки переключателя
   switch(t){
case true:
  xswitch = 130;
  c = RED;
  break;

    case false:
      xswitch = 90;
      c = BLUE;
      break;
    
   }
   if(h == true){
       M5.Lcd.fillCircle(150, 20, 5, BLUE);
   }
   //цикл для регулировки ползунка
   for( ; r == true ; ){
          M5.Imu.getAccelData(&accX, &accY, &accZ);
      M5.Lcd.clear();
       StickCP2.update();
     xregulator = map(accY * sens * 10000, -10000, 10000, 20, 130);
     xregulator = constrain(xregulator, 20, 130);
     M5.Lcd.setCursor(20, 75);
     M5.Lcd.print("Hold BtnA to exit");
     M5.Lcd.drawLine(20, 60, 130, 60, 31);
      M5.Lcd.fillCircle(xregulator, 60, 5, RED);
      if(StickCP2.BtnA.wasHold()){
        r = false;
        break;
      }
      delay(90);
    }
   

   //вывод интерфейса
      M5.Lcd.fillRect(BTNX, BTNY, BTNHEIGHT, BTNWEIGHT, BTNCOLOR);
      M5.Lcd.setCursor(45, 30);
      M5.Lcd.print("Btn1");
      M5.Lcd.drawLine(100, 20, 130, 20, c);
      M5.Lcd.fillRect(xswitch, 15, 10, 10, c);
      M5.Lcd.setCursor(90, 30);
      M5.Lcd.print("Switch1");
       M5.Lcd.drawLine(20, 60, 130, 60, 31);
        M5.Lcd.fillCircle(xregulator, 60, 5, 31);
           M5.Lcd.setCursor(20, 75);
     M5.Lcd.print("Slider1");
     M5.Lcd.drawCircle(150, 20, 7, BLUE);
                M5.Lcd.setCursor(150, 35);
     M5.Lcd.print("checkbox1");
     if(s == true){
  M5.Lcd.fillRect(ys, xs, 80, 40, 0xbbbb);
  M5.Lcd.fillRect(ys + 2, xs + 2, 10, 10, BLUE);
  M5.Lcd.setCursor(ys + 2, xs + 12);
  M5.Lcd.print("hold BtnA to exit");
 if(M5.BtnA.wasPressed() && y >= ys + 2 && y <= ys +12 && x >= xs + 2 && x <= xs + 12){
   M5.Lcd.drawRect(ys + 2, xs + 2, 10, 10,  GREEN);
 }
   }
}    
void cursor1(){
  //обновление кнопок и прочего
        StickCP2.update();
//выводим курсор
 M5.Lcd.drawBitmap(y, x, 4, 4, cursoridl);

 //обработка нажатий
 if(StickCP2.BtnA.wasPressed()){
  StickCP2.Speaker.tone(5000, 60);
  }
  if(StickCP2.BtnB.wasPressed()){
  s = true;
   xs = x;
   ys = y;
}
if(StickCP2.BtnA.wasPressed() && y >= 143 && y <= 157 && x >= 13 && x <= 27){
  h = !h;
}
 if(StickCP2.BtnA.wasPressed() && y >= BTNX && y <= BTNX + BTNHEIGHT && x >= BTNY && x <= BTNY + BTNWEIGHT){
      M5.Lcd.drawRect(BTNX, BTNY, BTNHEIGHT, BTNWEIGHT, BTNCOLOR1);
  }
  if(StickCP2.BtnA.wasPressed() && x >= 60 && x <= 65 && y >= xregulator - 5&& y <= xregulator + 5){
   r = true;
    }
if(StickCP2.BtnA.wasPressed() && y >= xswitch && y <= xswitch+10 && x >= 15 && x <= 25){
  t = !t;
}
 if(M5.BtnA.wasHold()){
    s = false;
 }
}
