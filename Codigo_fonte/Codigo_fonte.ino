#include <DS1307.h>
#include <LiquidCrystal.h>

//Autores: Jeovane Santos e Joel Vasconcelos, Colegio Dr. Antonio Ricaldi 2018

//Instanciar objetos
LiquidCrystal TELA(12, 11, 5, 4, 3, 2);
DS1307 RELOGIO(A4, A5);
const int BOIA = 0;

//Informação dos reles 1 ao 4
const int RELE1 = 6;
bool RELE1_ON = false;
unsigned long RELE1_ATIVADO_AS;

const int RELE2 = 7;
bool RELE2_ON = false;
unsigned long RELE2_ATIVADO_AS;

const int RELE3 = 8;
bool RELE3_ON = false;
unsigned long RELE3_ATIVADO_AS;

const int RELE4 = 9;
bool RELE4_ON = false;
unsigned long RELE4_ATIVADO_AS;

//Variaveis de tempo
unsigned long UM_SEGUNDO = 1000L;
unsigned long UM_MINUTO = UM_SEGUNDO * 60;
unsigned long UMA_HORA = UM_MINUTO * 60;

//Se você quiser configurar o relogio mude a variavel para "true"
bool CONFIGURAR_O_RELOGIO = false;

void setup() {
  
  //Desligar os reles
  digitalWrite(RELE1, HIGH);
  digitalWrite(RELE2, HIGH);
  digitalWrite(RELE3, HIGH);
  digitalWrite(RELE4, HIGH);
  
  //Conexão serial na velocidade 9600
  Serial.begin(9600);
  
  //Ligar LCD 16x2
  TELA.begin(16, 2);
  TELA.print("Ola mundo :D");
  delay(UM_SEGUNDO*2);

  //Definir como saida os pinos dos reles
  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
  pinMode(RELE3, OUTPUT);
  pinMode(RELE4, OUTPUT);

  //Ativar o relogio
  RELOGIO.halt(false);
  RELOGIO.setSQWRate(SQW_RATE_1);
  RELOGIO.enableSQW(true);

  //Configurar o relogio com os dados abaixo
  if(CONFIGURAR_O_RELOGIO) {
    RELOGIO.setDOW(THURSDAY);
    RELOGIO.setDate(04, 9, 2018);
    RELOGIO.setTime(17, 51, 00);
  }
}

void loop() {
  
  //Pegar o valor do bluetooth
  char BT = Serial.read();

  //Pegar o nivel da boia do reservatorio
  int VALOR_DA_BOIA = analogRead(BOIA);
  
  //Pegar horario atual
  String AGORA = RELOGIO.getTimeStr(FORMAT_LONG);
  Serial.println(AGORA);

  //Oque vai ser mostrado na tela
  TELA.clear();
  TELA.print("I: " + boolString(RELE2_ON) + " R: " + boolString(RELE1_ON));
  TELA.setCursor(0,1);
  TELA.print(AGORA + 'h');

  //Irrigação = RELE2, Solenoide = RELE3
  if(AGORA == "07:00:00" || AGORA == "17:00:00" || BT == 'I') {
    
    //Ligar o solenoide e a bomba
    digitalWrite(RELE3, LOW);
    digitalWrite(RELE2, LOW);
    RELE3_ON = true;
    RELE2_ON = true;
    RELE2_ATIVADO_AS = millis();
  }

  //Quando a bomba estiver ativa verificar se já passou 1 minuto, para desligar
  if(RELE2_ON) {
    if(millis() >= RELE2_ATIVADO_AS + UM_MINUTO) {
      digitalWrite(RELE3, HIGH);
      digitalWrite(RELE2, HIGH);
      RELE3_ON = false;
      RELE2_ON = false;
    }
  }
  
  //Reservatorio = RELE1
  //Ligar a bomba do reservatorio, quando estiver cheio
  if(VALOR_DA_BOIA == 0) {
    digitalWrite(RELE1, LOW);
    RELE1_ON = true;
    RELE1_ATIVADO_AS = millis();
  } else if(BT == 'R') { 
    digitalWrite(RELE1, LOW);
  } else if(BT == 'r') {
    digitalWrite(RELE1, HIGH);
  }

  //Quando a bomba do reservatorio estiver ativa verificar se já passou 1 minuto, para desligar
  if(RELE1_ON) {
    if(millis() >= RELE1_ATIVADO_AS + UM_MINUTO) {
      digitalWrite(RELE1, HIGH);
      RELE1_ON = false;
    }
  }
  
  //Delay de 100ms para inicar o loop novamente
  delay(100);
  
}

//Transformar Bool em String
String boolString(bool b) {
  if(b) {
    return "true";
  } else return "false";
}
