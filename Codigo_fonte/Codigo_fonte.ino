#include <DS1307.h>
#include <LiquidCrystal.h>

//Autores: Jeovane Santos e Joel Vasconcelos, Colegio Dr. Antonio Ricaldi 2018;

//INSTANCIAR OBJETOS;
LiquidCrystal TELA(12, 11, 5, 4, 3, 2);
DS1307 RELOGIO(A4, A5);
const int BOIA = 0;
const int RELE1 = 6;
const int RELE2 = 7;
const int RELE3 = 8;
const int RELE4 = 9;

//VARIAVEIS DE TEMPO;
unsigned long UM_SEGUNDO = 1000L;
unsigned long UM_MINUTO = UM_SEGUNDO * 60;
unsigned long UMA_HORA = UM_MINUTO * 60;

bool CONFIGURAR_O_RELOGIO = false;

void setup() {
  //DESLIGAR OS RELES;
  digitalWrite(RELE1, HIGH);
  digitalWrite(RELE2, HIGH);
  digitalWrite(RELE3, HIGH);
  digitalWrite(RELE4, HIGH);
  
  //CONEXÃO SERIAL NA VELOCIDADE 9600;
  Serial.begin(9600);
  
  //LIGAR A TELA LCD 16X2;
  TELA.begin(16, 2);
  TELA.print("Ola mundo :D");
  delay(UM_SEGUNDO*2);

  //DEFINIR COMO SAIDA O PINO DO RELE;
  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
  pinMode(RELE3, OUTPUT);
  pinMode(RELE4, OUTPUT);

  //ATIVAR RELOGIO;
  RELOGIO.halt(false);
  RELOGIO.setSQWRate(SQW_RATE_1);
  RELOGIO.enableSQW(true);

  //LIGAR O RELOGIO, E DEFINIR HORA E DATA COM OS DADOS ABAIXO;
  if(CONFIGURAR_O_RELOGIO) {
    RELOGIO.setDOW(THURSDAY);
    RELOGIO.setDate(04, 9, 2018);
    RELOGIO.setTime(17, 51, 00);
    
  }

}

void loop() {
  //PEGAR VALOR DO BLUETOOTH;
  char BT = Serial.read();

  //PEGAR O NIVEL DA AQUA DO RESERVATORIO;
  int VALOR_DA_BOIA = analogRead(BOIA);
  
  //PEGAR HORARIO ATUAL;
  String AGORA = RELOGIO.getTimeStr(FORMAT_LONG);
  Serial.println(AGORA);
  TELA.clear();
  TELA.print("AUTO - AGRO");
  TELA.setCursor(0,1);
  TELA.print("HORA: " + AGORA);

  //IRRIGAÇÃO = RELE2, REGISTRO = RELE3;
  if(AGORA == "07:00:00" || AGORA == "17:00:00" || BT == 'I') {
    //ABRIR REGISTRO;
    digitalWrite(RELE3, LOW);
    TELA.clear();
    TELA.print("REGISTRO: ON");
    delay(UM_SEGUNDO*5+275);
    digitalWrite(RELE3, HIGH);

    //LIGAR BOMBA DE IRRIGAÇÃO;
    digitalWrite(RELE2, LOW);
    TELA.clear();
    TELA.print("IRRIGACAO: ON");
    delay(UM_SEGUNDO*45);
    digitalWrite(RELE2, HIGH);
    
    //FECHAR REGISTRO;
    digitalWrite(RELE3, LOW);
    TELA.clear();
    TELA.print("REGISTRO: OFF");
    delay(UM_SEGUNDO*5+275);
    digitalWrite(RELE3, HIGH);
    
  }
  
  //RESERVATORIO = RELE1;
  if(VALOR_DA_BOIA == 0) {
    digitalWrite(RELE1, LOW);
    TELA.clear();
    TELA.print("RESERVATORIO: ON");
    delay(UM_MINUTO+UM_SEGUNDO*30);
    digitalWrite(RELE1, HIGH);

  } else if(BT == 'R') { 
    digitalWrite(RELE1, LOW);

  } else if(BT == 'r') {
    digitalWrite(RELE1, HIGH);

  }
  
  //DELAY DE 100MS PARA CONTINUAR O LOOP;
  delay(100);
  
}
