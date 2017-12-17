//------------------------COMEÇO ULTRASOM------------------------/
#include <Ultrasonic.h>
//HC-SR04 - 1
#include <SdFat.h>

#define pino_trigger1 A0
#define pino_echo1 A1
//HC-SR04 - 2
#define pino_trigger2 A2
#define pino_echo2 A3
//HC-SR04 - 3
#define pino_trigger3 A4
#define pino_echo3 A5 
//HC-SR04 - 4
#define pino_trigger4 A14
#define pino_echo4 A15
//HC-SR04 - 5
#define pino_trigger5 A7
#define pino_echo5 A8
//HC-SR04 - 6
#define pino_trigger6 A10
#define pino_echo6 A11
//HC-SR04 - 7
#define pino_trigger7 A12
#define pino_echo7 A13

//define as variaveis que recebem as distancias lidas pelos sensores
Ultrasonic ultrasonic1(pino_trigger1, pino_echo1);
Ultrasonic ultrasonic2(pino_trigger2, pino_echo2);
Ultrasonic ultrasonic3(pino_trigger3, pino_echo3);
Ultrasonic ultrasonic4(pino_trigger4, pino_echo4);
Ultrasonic ultrasonic5(pino_trigger5, pino_echo5);
Ultrasonic ultrasonic6(pino_trigger6, pino_echo6);
Ultrasonic ultrasonic7(pino_trigger7, pino_echo7);

bool b_cmMsec1, b_cmMsec2, b_cmMsec3, b_cmMsec4, b_cmMsec5, b_cmMsec6, b_cmMsec7, b_cmMsec8, b_IR;

int pos1 = 0.6, pos2 = 1.20/*IR*/, pos3 = 1.80, pos4 = 0, pos5 = 0.9, pos6 = 1.8, pos7 = 1.0, pos8 = 1.5;
float comprimento1, largura1, altura1, comprimento2, largura2, altura2;
int Acionamento; //Variavel para guardar valor do sensor
int circmin, circmax, pesomin, pesomax;
//------------------------FIM ULTRASOM-------------------------/

#include <VirtualWire.h>

#define Sensor_Pir 2
char recebido_RF_char[6];
 
SdFat sdCard;
SdFile meuArquivo;
 
// Pino ligado ao CS do modulo
const int chipSelect = 4;

void setup()
{
  Serial.begin(2000000);
  //Pino ligado ao pino DATA do receptor RF
  vw_set_rx_pin(7);
  //Velocidade de comunicacao (bits por segundo)
  vw_setup(500);
  //Inicia a recepcao
  vw_rx_start();
  Serial.println("Recepcao modulo RF - Aguardando...");
  pinMode(Sensor_Pir, INPUT);
    // Inicializa o modulo SD
  if(!sdCard.begin(chipSelect,SPI_HALF_SPEED))sdCard.initErrorHalt();
  // Abre o arquivo LER_POT.TXT
  if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
  {
    sdCard.errorHalt("Erro na abertura do arquivo DADOS.TXT!");
  }

}

void loop()
{
  float cmMsec1;
  float cmMsec2;
  float cmMsec3;
  float cmMsec4;
  float cmMsec5;
  float cmMsec6;
  float cmMsec7;
  float cmMsec8;
  long microsec1 = ultrasonic1.timing();
  long microsec2 = ultrasonic2.timing();
  long microsec3 = ultrasonic3.timing();
  long microsec4 = ultrasonic4.timing();
  long microsec5 = ultrasonic5.timing();
  long microsec6 = ultrasonic6.timing();
  long microsec7 = ultrasonic7.timing();
  cmMsec1 = ultrasonic1.convert(microsec1, Ultrasonic::CM);
  cmMsec2 = ultrasonic2.convert(microsec2, Ultrasonic::CM);
  cmMsec3 = ultrasonic3.convert(microsec3, Ultrasonic::CM);
  cmMsec4 = ultrasonic4.convert(microsec4, Ultrasonic::CM);
  cmMsec5 = ultrasonic5.convert(microsec5, Ultrasonic::CM);
  cmMsec6 = ultrasonic6.convert(microsec6, Ultrasonic::CM);
  cmMsec7 = ultrasonic7.convert(microsec7, Ultrasonic::CM);

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen))
  {
    for (int i = 0; i < buflen; i++)
    {
      //Armazena os caracteres recebidos
      recebido_RF_char[i] = char(buf[i]);
    }
    recebido_RF_char[buflen] = '\0';

    //Mostra no serial monitor o valor recebido
    Serial.print("Recebido: ");
    Serial.println(recebido_RF_char);
  }

  Acionamento = digitalRead(Sensor_Pir); //Le o valor do sensor PIR

  if (Acionamento == HIGH) //Caso seja detectado um movimento, aciona o rele
  {
    if (cmMsec1 > 200)
    {
      b_cmMsec1 = true;

    }
    else {
      b_cmMsec1 = false;
    }
    if (cmMsec2 > 200)
    {
      b_cmMsec2 = true;

    }
    else {
      b_cmMsec2 = false;
    }
    if ((cmMsec3 - 3125) > 200)
    {
      b_cmMsec3 = true;

    }
    else {
      b_cmMsec3 = false;
    }
    if (cmMsec4 > 200)
    {
      b_cmMsec4 = true;

    }
    else {
      b_cmMsec4 = false;
    }
    if (cmMsec5 > 200)
    {
      b_cmMsec5 = true;

    }
    else {
      b_cmMsec5 = false;
    }
    if (cmMsec6 > 200)
    {
      b_cmMsec6 = true;

    }
    else {
      b_cmMsec6 = false;
    }
    if (cmMsec7 > 200)
    {
      b_cmMsec7 = true;

    }
    else {
      b_cmMsec7 = false;
    }
    pesar_Boi();
    medir_alt();
    medir_com();
    medir_lar();
    circmin = (2 * altura1);
    circmax = (2 * altura2);
    pesomin = ((circmin * circmin) * comprimento1 * 87.5);
    pesomax = ((circmax * circmax) * comprimento2 * 87.5);
    Serial.println(pesomin);
    Serial.println(pesomax);
    meuArquivo.print("Identificação e Pesagem: ");
    meuArquivo.println("Peso Máximo");
    meuArquivo.println(pesomax);
    meuArquivo.println("Peso Mínimo");
    meuArquivo.println(pesomin);
 
  if (millis() == 300000)
  {
    // Interrompe o processo e fecha o arquivo
    Serial.println("Processo de gravacao interrompido. Retire o SD!");
    meuArquivo.close();
    while (1) {}
    }
  }
}

void medir_alt()
{
  //Eixo Z
  if (!b_cmMsec1) {
    if (!b_cmMsec2) {
      altura1 = 0.6;
      altura2 = 1.0;
    }
    if (!b_cmMsec3) {
      altura1 = 1.2;
      altura2 = 1.7;
      Serial.println(1);
      Serial.println(altura2);
    }
  }
}

void medir_com() {
  //Eixo Y
  if (!b_cmMsec4) {
    if (!b_cmMsec2)
    {
      comprimento1 = 1;
      comprimento2 = 1.9;
      Serial.println(2);
      Serial.println(comprimento2);
    }
    if (!b_cmMsec5)
    {
      comprimento1 = 1.8;
      comprimento2 = 1.9;

    }
  }
  if ((!b_cmMsec2) && (!b_cmMsec5))
  {
    comprimento1 = 0.9;
    comprimento2 = 1;

  }
}

void medir_lar() {
  //Eixo X
  if ((!b_cmMsec6) && (!b_cmMsec7)) {
    largura1 = 0.3;
  }
  else {
    largura2 = 0.6;
    Serial.println(3);
    Serial.println(largura2);
  }
}

void pesar_Boi() {
  float cmMsec1;
  float cmMsec2;
  float cmMsec3;
  float cmMsec4;
  float cmMsec5;
  float cmMsec6;
  float cmMsec7;
  float cmMsec8;
  long microsec1 = ultrasonic1.timing();
  long microsec2 = ultrasonic2.timing();
  long microsec3 = ultrasonic3.timing();
  long microsec4 = ultrasonic4.timing();
  long microsec5 = ultrasonic5.timing();
  long microsec6 = ultrasonic6.timing();
  long microsec7 = ultrasonic7.timing();
  cmMsec1 = ultrasonic1.convert(microsec1, Ultrasonic::CM);
  cmMsec2 = ultrasonic2.convert(microsec2, Ultrasonic::CM);
  cmMsec3 = ultrasonic3.convert(microsec3, Ultrasonic::CM);
  cmMsec4 = ultrasonic4.convert(microsec4, Ultrasonic::CM);
  cmMsec5 = ultrasonic5.convert(microsec5, Ultrasonic::CM);
  cmMsec6 = ultrasonic6.convert(microsec6, Ultrasonic::CM);
  cmMsec7 = ultrasonic7.convert(microsec7, Ultrasonic::CM);
}
