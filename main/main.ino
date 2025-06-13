#include <BleKeyboard.h>
#include <Bounce2.h>

BleKeyboard bleKeyboard;
Bounce debouncer = Bounce();

const int cols[] = { 36, 39, 34, 35, 32, 33 };
const int rows[] = { 25, 26, 27, 14 };

#define NUM_COLS (sizeof(cols) / sizeof(cols[0]))
#define NUM_ROWS (sizeof(rows) / sizeof(rows[0]))

const char* keymap[3][3] = {
  { "1", "q", "w", "e", "r", "t" },
  { "2", "a", "s", "d" },
  { "3", "z", "x", "c" }
};

void setup() {

  Serial.begin(9600);

  bleKeyboard.begin();
  // Establecemos las salida
  for (int c = 0; c < NUM_COLS; c++) {
    pinMode(cols[c], OUTPUT);
  }
  // Establecemos las entradas
  for (int r = 0; r < NUM_ROWS; r++) {
    pinMode(rows[r], INPUT_PULLDOWN);
  }
}

void loop() {
  //delay(1500);
  if (!bleKeyboard.isConnected()) return;

  //Serial.println("BT Connected");

  for (int c = 0; c < NUM_COLS; c++) {
    // Serial.println(c);
    // Prendemos la columna
    digitalWrite(cols[c], HIGH);
    //? Aqui deberiamos agregar un delay?

    // Recorremos las rows en busca de la activada
    for (int r = 0; r < NUM_ROWS; r++) {
      bool asd = digitalRead(rows[r]);
      if (asd) {
        Serial.print("Key: ");
        Serial.println(keymap[r][c]);
      }
    }

    // Limpiamos la columna
    digitalWrite(cols[c], LOW);
  }
}
