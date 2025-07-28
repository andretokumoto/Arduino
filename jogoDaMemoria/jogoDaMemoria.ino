//definição de pinos
const int led1 = 7;
const int led2 = 5;
const int led3 = 3;
const int botao1 = 13;
const int botao2 = 11;
const int botao3 = 9;

//debounce botões
unsigned long lastDebounce = 0;
unsigned long debounceDelay = 50;
boolean lastButton1State = HIGH;
boolean lastButton2State = HIGH;
boolean lastButton3State = HIGH;

boolean button1State = HIGH;
boolean button2State = HIGH;
boolean button3State = HIGH;

//variáveis que guardam entrada do usuário e sequência certa
String entradaDoUsuario = "";
String sequencia = "";

//contador de nível
int contador = 0;

void setup() {
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP); 
  pinMode(botao3, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void loop() {

  //gera um valor aleatório para próxima sequência
  int novoValor = random(1, 4);
  char ent = (char)(novoValor + '0');
  sequencia += ent;
  Serial.print("sequencia atual: ");
  Serial.println(sequencia);
  
  //mostra a sequência
  contador++;
  for (int i = 0; i < contador; i++) {
    switch(sequencia[i]) {
      case '1':
        digitalWrite(led1, HIGH);
        delay(500);
        digitalWrite(led1, LOW);
        break;
      case '2':
        digitalWrite(led2, HIGH);
        delay(500);
        digitalWrite(led2, LOW);
        break;
      case '3':
        digitalWrite(led3, HIGH);
        delay(500);
        digitalWrite(led3, LOW);
        break;
    }
    delay(250);
  }

  //espera entrada do usuário
  entradaDoUsuario = "";
     Serial.print("minha sequencia: ");
  while (entradaDoUsuario.length() < contador) {
    int estadoBotao1 = digitalRead(botao1);
    int estadoBotao2 = digitalRead(botao2);
    int estadoBotao3 = digitalRead(botao3);

  
    if (estadoBotao1 != lastButton1State || estadoBotao2 != lastButton2State || estadoBotao3 != lastButton3State) {
      lastDebounce = millis();
    }

    if ((millis() - lastDebounce) > debounceDelay) {
      if (estadoBotao1 != button1State) {
        button1State = estadoBotao1;
        if (button1State == LOW) {
          entradaDoUsuario += '1'; 
          delay(250);
         
        }
      } else if (estadoBotao2 != button2State) {
        button2State = estadoBotao2;
        if (button2State == LOW) {
          entradaDoUsuario += '2';
           Serial.println(entradaDoUsuario);
          delay(250);
        }
      } else if (estadoBotao3 != button3State) {
        button3State = estadoBotao3;
        if (button3State == LOW) {
          entradaDoUsuario += '3';
           Serial.println(entradaDoUsuario);
          delay(250);
        }
      }
    }

    lastButton1State = estadoBotao1;
    lastButton2State = estadoBotao2;
    lastButton3State = estadoBotao3;
  }
 
 
  
  //verifica se a entrada está correta
  if (sequencia != entradaDoUsuario) {//usuário errou a sequência

    Serial.println("PERDEU");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    sequencia = "";
    contador = 0;
  }

  delay(500); // pausa antes de nova rodada
}
