const int buttonPin = 2;  // Pino do botão
const int ledPin = 13;    // Pino do LED

void setup() {
  pinMode(ledPin, OUTPUT);      // Configura o pino do LED como saída
  pinMode(buttonPin, INPUT);    // Configura o pino do botão como entrada
}

void loop() {
  int buttonState = digitalRead(buttonPin); // Lê o estado do botão
  if (buttonState == HIGH) {                // Se o botão estiver pressionado
    digitalWrite(ledPin, HIGH);             // Liga o LED
  } else {
    digitalWrite(ledPin, LOW);              // Desliga o LED
  }
}