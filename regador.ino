#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  

int bomba = 10;

int pino_sinal_analogico = A0;

int pino_led_vermelho = 13;
int pino_led_amarelo = 8;
int pino_led_verde = 9;

int valor_analogico;

void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(2,0 );
  lcd.print("Regador Pronto!");
 
  Serial.begin(9600);
  
  pinMode(pino_sinal_analogico, INPUT);
  
  pinMode(pino_led_vermelho, OUTPUT);
  pinMode(pino_led_amarelo, OUTPUT);
  pinMode(pino_led_verde, OUTPUT);
  
  pinMode(bomba, OUTPUT); 
  delay(2000);
}

void loop()
{
  //Le o valor do pino A0 do sensor
  valor_analogico = analogRead(pino_sinal_analogico);

  //Mostra o valor da porta analogica no serial monitor
  Serial.print("Porta analogica: ");
  Serial.println(valor_analogico);

  //Solo umido, acende o led verde
  if (valor_analogico > 0 && valor_analogico < 400)
  {
    Serial.println(" Status: Solo umido");
    apagaleds();
    digitalWrite(pino_led_verde, HIGH);
     digitalWrite(bomba, LOW);
  }

  //Solo com umidade moderada, acende led amarelo
  if (valor_analogico > 400 && valor_analogico < 800)
  {
    Serial.println(" Status: Umidade moderada");
    apagaleds();
    digitalWrite(pino_led_amarelo, HIGH);
     digitalWrite(bomba, LOW);
  }

  //Solo seco, acende led vermelho
  if (valor_analogico > 800 && valor_analogico < 2000)
  {
    Serial.println(" Status: Solo seco");
    apagaleds();
    digitalWrite(pino_led_vermelho, HIGH);
    digitalWrite(bomba, HIGH);
  }
  delay(100);
}

void apagaleds()
{
  digitalWrite(pino_led_vermelho, LOW);
  digitalWrite(pino_led_amarelo, LOW);
  digitalWrite(pino_led_verde, LOW);
}
