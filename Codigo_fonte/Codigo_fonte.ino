#include <DS1307.h>
#include <LiquidCrystal.h>

//Autores: Jeovane Santos e Joel Vasconcelos, Colegio Dr. Antonio Ricaldi 2018;

//INSTANCIAR OBJETOS;
LiquidCrystal TELA(12, 11, 5, 4, 3, 2);
DS1307 RELOGIO(A4, A5);
const int BOIA = 0;
const int RELE1 = 7;
const int RELE2 = 8;
const int RELE3 = 9;

unsigned long UM_SEGUNDO = 1000L;
unsigned long UM_MINUTO = UM_SEGUNDO * 60;
unsigned long UMA_HORA = UM_MINUTO * 60;

bool CONFIGURAR_O_RELOGIO = false;

void setup() {
  //DESLIGAR OS RELES;
  digitalWrite(RELE1, HIGH);
  digitalWrite(RELE2, HIGH);
  digitalWrite(RELE3, HIGH);
  
  //CONEXÃO SERIAL NA VELOCIDADE 9600;
  Serial.begin(9600);
  
  //LIGAR A TELA LCD 16X2;
  TELA.begin(16, 2);
  TELA.print("Ola mundo :)");
  delay(UM_SEGUNDO*2);

  //DEFINIR COMO SAIDA O PINO DO RELE;
  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
  pinMode(RELE3, OUTPUT);

  //LIGAR O RELOGIO, E DEFINIR HORA E DATA COM OS DADOS ABAIXO;
  if(CONFIGURAR_O_RELOGIO) {
    RELOGIO.halt(true);
    RELOGIO.setDOW(THURSDAY);
    RELOGIO.setDate(30, 8, 2018);
    RELOGIO.setTime(16, 26, 00);
  }

  RELOGIO.setSQWRate(SQW_RATE_1);
  RELOGIO.enableSQW(true);

}

void loop() {
  //PEGAR O NIVEL DA AQUA DO RESERVATORIO;
  int VALOR_DA_BOIA = analogRead(BOIA);
  
  //PEGAR HORARIO ATUAL;
  String AGORA = RELOGIO.getTimeStr(FORMAT_LONG);
  Serial.println(AGORA);
  TELA.clear();
  TELA.print("HORARIO:");
  TELA.setCursor(0,1);
  TELA.print(AGORA);

  //IRRIGAÇÃO = RELE2, REGISTRO = RELE3;
  if(AGORA == "07:00:00") {
    //ABRIR REGISTRO;
    digitalWrite(RELE3, LOW);
    delay(UM_SEGUNDO*5);
    digitalWrite(RELE3, HIGH);

    //LIGAR BOMBA DE IRRIGAÇÃO;
    digitalWrite(RELE2, LOW);
    delay(UM_MINUTO);
    digitalWrite(RELE2, HIGH);
    
    //FECHAR REGISTRO;
    digitalWrite(RELE3, LOW);
    delay(UM_SEGUNDO*5);
    digitalWrite(RELE3, HIGH);
    
  } else if(AGORA == "17:00:00") {
    //ABRIR REGISTRO;
    digitalWrite(RELE3, LOW);
    delay(UM_SEGUNDO*5);
    digitalWrite(RELE3, HIGH);

    //LIGAR BOMBA DE IRRIGAÇÃO;
    digitalWrite(RELE2, LOW);
    delay(UM_MINUTO);
    digitalWrite(RELE2, HIGH);
    
    //FECHAR REGISTRO;
    digitalWrite(RELE3, LOW);
    delay(UM_SEGUNDO*5);
    digitalWrite(RELE3, HIGH);

  }
  
  //RESERVATORIO = RELE1;
  if(VALOR_DA_BOIA == 0) {
    digitalWrite(RELE1, LOW);
    delay(UM_MINUTO+UM_SEGUNDO*30);
    digitalWrite(RELE1, HIGH);
    
  }
}
