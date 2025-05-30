#include <BleKeyboard.h>
#include <Bounce2.h>

BleKeyboard bleKeyboard;
Bounce debouncer = Bounce();

const int cols[] = { 32, 33, 27 };
const int rows[] = { 25, 26 };

#define NUM_COLS (sizeof(cols) / sizeof(cols[0]))
#define NUM_ROWS (sizeof(rows) / sizeof(rows[0]))

void setup() {
  const char* keymap[2][3] = {
    { "q", "w", "e" },
    { "a", "s", "d" }
  };

  Serial.begin(9600);

  bleKeyboard.begin();
  // Establecemos las salidas
  for (int c = 0; c < NUM_COLS; c++) {
    pinMode(cols[c], OUTPUT);
  }
  // Establecemos las entradas
  for (int r = 0; r < NUM_ROWS; r++) {
    pinMode(rows[r], INPUT_PULLDOWN);
  }
}

void loop() {
  delay(1500);
  if (!bleKeyboard.isConnected()) return;

  for (int c = 0; c < NUM_COLS; c++) {
    Serial.println(c);
    // Prendemos la columna
    digitalWrite(cols[c], HIGH);
    //? Aqui deberiamos agregar un delay?

    // Recorremos las rows en busca de la activada
    for (int r = 0; r < NUM_ROWS; r++) {
      bool asd = digitalRead(rows[r]);
      if (asd) {
        Serial.println(": on");
      } else {
        Serial.println(": off");
      }
    }

    // Limpiamos la columna
    digitalWrite(cols[c], LOW);
  }
}
