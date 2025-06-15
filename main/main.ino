#include <BleKeyboard.h>
#include <Bounce2.h>

BleKeyboard bleKeyboard;
Bounce debouncer = Bounce();

// GPIO6 a GPIO11 (flash)
// GPIO34 a GPIO39 (solo entrada analógica)
// GPIO36 y 39 (sin pull-up/down, solo ADC)
// GPIO0, 2, 12, 15 (boot sensibles)
// Evitar GPIO13 si no querés interferencias por el LED interno
// GPIO1, 3 (UART, cuidado si usás USB)

const int cols[] = { 14, 33, 25, 26, 27, 15 };
const int rows[] = { 12, 4, 17 };
#define NUM_COLS (sizeof(cols) / sizeof(cols[0]))
#define NUM_ROWS (sizeof(rows) / sizeof(rows[0]))

const char* keymap[4][6] = {
  { "1", "q", "w", "e", "r", "t" },
  { "2", "a", "s", "d", "f", "g" },
  { "3", "z", "x", "c", "v", "b" },
  { "4", "", "", "", "Enter", "Espacio" }
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
  Serial.print("!");
  //
  delay(400);
  if (!bleKeyboard.isConnected()) return;

  for (int c = 0; c < NUM_COLS; c++) {
    digitalWrite(cols[c], HIGH);

    for (int r = 0; r < NUM_ROWS; r++) {
      if (digitalRead(rows[r]) == HIGH) {
        Serial.println(keymap[r][c]);
        String key = keymap[r][c];
        if (key == "Enter") bleKeyboard.write(KEY_RETURN);
        else if (key == "Espacio") bleKeyboard.write(' ');
        else if (key.length() == 1) bleKeyboard.write(key[0]);
      }
    }

    digitalWrite(cols[c], LOW);
  }
}
