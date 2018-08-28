#include <DS1307.h>
#include <LiquidCrystal.h>

//Autores: Jeovane Santos e Joel Vasconcelos, Colegio Dr. Antonio Ricaldi 2018;

//INSTANCIAR OBJETOS;
LiquidCrystal TELA(12, 11, 5, 4, 3, 2);
DS1307 RELOGIO(A4, A5);
const int BOIA = 0;
const int RELE1 = 7;
const int RELE2 = 8;

unsigned long UM_SEGUNDO = 1000L;
unsigned long UM_MINUTO = UM_SEGUNDO * 60;
unsigned long UMA_HORA = UM_MINUTO * 60;

bool CONFIGURAR_O_RELOGIO = true;

void setup() {
  //CONEXÃO SERIAL NA VELOCIDADE 9600;
  Serial.begin(9600);
  
  //LIGAR A TELA LCD 16X2;
  TELA.begin(16, 2);

  //DEFINIR COMO SAIDA O PINO DO RELE;
  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);

  //LIGAR O RELOGIO, E DEFINIR HORA E DATA COM OS DADOS ABAIXO;
  if(CONFIGURAR_O_RELOGIO) {
    RELOGIO.halt(false);
    RELOGIO.setDOW(FRIDAY);
    RELOGIO.setDate(27, 8, 2018);
    RELOGIO.setTime(16, 31, 10);
  }
}

void loop() {
  //PEGAR O NIVEL DA AQUA;
  int VALOR_DA_BOIA = analogRead(BOIA);
  
  if(RELOGIO.getTimeStr(FORMAT_LONG) == "07:00:00" || "17:00:00") {
    TELA.setCursor(0,0);
    TELA.clear();
    digitalWrite(RELE1, LOW);
    TELA.print("R1: ON");
    delay(1*UM_MINUTO);
    digitalWrite(RELE1, HIGH);
    TELA.clear();
    TELA.print("R1: OFF");
  }

  if(VALOR_DA_BOIA == 0) {
    TELA.setCursor(0,1);
    TELA.clear();
    digitalWrite(RELE2, LOW);
    TELA.print("R2: ON");
    delay(UM_MINUTO+UM_SEGUNDO*30);
    digitalWrite(RELE2, HIGH);
    TELA.clear();
    TELA.print("R2: OFF");
  }
}
