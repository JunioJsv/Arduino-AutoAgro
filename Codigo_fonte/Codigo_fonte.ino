#include <DS1307.h>
#include <LiquidCrystal.h>

//Autores: Jeovane Santos e Joel Vasconcelos, Colegio Dr. Antonio Ricaldi 2018;

//INSTANCIAR OBJETOS;
LiquidCrystal TELA(12, 11, 5, 4, 3, 2);
DS1307 RELOGIO(A4, A5);
unsigned int RELE1 = 7;
unsigned long UM_SEGUNDO = 1000L;
unsigned long UM_MINUTO = UM_SEGUNDO * 60;
unsigned long UMA_HORA = UM_MINUTO * 60;

void setup() {
  //LIGAR A TELA LCD 16X2;
  TELA.begin(16, 2);

  //DEFINIR COMO SAIDA O PINO DO RELE;
  pinMode(RELE1, OUTPUT);
  
  //LIGAR O RELOGIO, E DEFINIR HORA E DATA COM OS DADOS ABAIXO;
  RELOGIO.halt(false);
  RELOGIO.setDOW(FRIDAY);
  RELOGIO.setDate(27, 8, 2018);
  RELOGIO.setTime(16, 31, 10);
}

void ligarBomba(bool VARIAVEL) {
  //LIMPAR A TELA;
  TELA.clear();
  //VERIFICAR SE É PARA LIGAR OU DESLIGAR A BOMBA D'AQUA;
  if(VARIAVEL) {
    //LIGAR BOMBA D'AQUA
    digitalWrite(RELE1, HIGH);
    TELA.print("LIGADO");
    //DELAY DE 1 MINUTO;
    delay(1*UM_MINUTO);
  } else if(!VARIAVEL) {
    //DESLIGAR BOM D'AQUA;
    digitalWrite(RELE1, LOW);
    TELA.print("DESLIGADO");
  }
}

void loop() {
  if(RELOGIO.getTimeStr(FORMAT_LONG) == "07:00:00" || "17:00:00") {
    ligarBomba(true);
    ligarBomba(false);
  }
}
