// -------------------------------------------------------- KAH -------------------------------------------------------- \\
//                                                                                                                       \\
//                                    //---------- ARDUÍNO BLUETOOTH CAR ----------\\                                    \\
//                                   || ------------- By PAULO XAVIER ------------- ||                                   \\
//                                    \\------------------- ... -------------------//                                    \\
//                                                                                                                       \\
// --------------------------------------------- Valores Enviados Pelo App --------------------------------------------- \\
//        'W' -> RED    |    'U' -> GREEN    |    'V' --> BLUE    |    'X' -> "Pescoço"    |    'D' -> Stop Geral        \\
// --------------------------------------------------------------------------------------------------------------------- \\


/* ____________________________________________________ BIBLIOTECAS ____________________________________________________ */
#include <AFMotor.h>                                               // Biblioteca p/ Módulo Shield Ponte H.               //
#include "SoftwareSerial.h"                                        // Biblioteca p/ Módulo de Comunicação Bluetooth      //
/* __________________________________________________ FIM BIBLIOTECAS __________________________________________________ */


/* _____________________________________________________ VARIÁVEIS _____________________________________________________ */
char x;                                                            // Recebe Leitura da Serial/Bluetooth                 //
int v = 150;                                                       // Velocidade Inicial dos Motores                     //
int rR = 51;                                                       // Porta para Acionar Relé da Luz Vermelha            //
int rG = 52;                                                       // Porta para Acionar Relé da Luz Verde               //
int rB = 53;                                                       // Porta para Acionar Relé da Luz Azul                //
/* ___________________________________________________ FIM VARIÁVEIS ___________________________________________________ */


/* ______________________________________________ OBJETOS DAS BIBLIOTECAS ______________________________________________ */
AF_DCMotor mE(1);                                                  // Motor DC de Movimento Lado Esquerdo                //
AF_DCMotor mD(2);                                                  // Motor DC de Movimento Lado Direito                 //
AF_DCMotor mP(3);                                                  // Motor DC Pescoço                                   //
AF_DCMotor mL(4);                                                  // Controle de Intensidade da Luz                     //
SoftwareSerial bluetooth(14, 15);                                  // Pinos TX & RX p/ Comunicação Bluetooth             //
/* __________________________________________________ FIM BIBLIOTECAS __________________________________________________ */


// ******************************************************* SETUP ******************************************************* //
void setup() {                                                     // Função void setup                                  //
  pinMode(rR, OUTPUT);                                             // Define a Porta p/ Variável como Saída              //
  pinMode(rG, OUTPUT);                                             // Define a Porta p/ Variável como Saída              //
  pinMode(rB, OUTPUT);                                             // Define a Porta p/ Variável como Saída              //
  Serial.begin(9600);                                              // Inicializa a Serial                                //
  Serial3.begin(9600);                                             // Inicializa a Serial 3                              //
}// -------------------------------------------------- FIM void setup -------------------------------------------------- //

// ******************************************************* LOOP. ******************************************************* //
void loop() {                                                      // Função void setup                                  //
  conect();                                                        // Chama função void conect() p/ conexão bluetooth    //
  control();                                                       // Chama função void control() p/ controle geral      //
  fast();                                                          // Chama função void velocidad() p/ velocidade        //
}// -------------------------------------------------- FIM void setup -------------------------------------------------- //

/* ----------------------------------------- Função p/ Comunicação Bluetooth ----------------------------------------- | */
void conect() {                                                    // | Função Void P/ Conexão Bluetooth               | //
  if (Serial3.available()) {                                       // | Verifica Leituras da Comunicação Serial 3      | //
    x = Serial3.read();                                            // | Lê e Atribui a "x" o Valor na Serial 3, Módulo | //
    Serial.println(x);                                             // | Passa P/ a Serial o Valor de "x", da Serial 3  | //
  }
} // ------------------------------------------------- FIM void conect ------------------------------------------------- //

/* --------------------------------------- Função lógica p/ Movimentos do Robô --------------------------------------- | */
void control() {                                                   // | Função Void P/ Controle de Movimentos          | //
  if (x == 'F') {                                                  // | Se/enquanto 'F' pressionado -> Avante          | //
    seguir();                                                      // | Chama/Executa Função void de Movimento         | //
  } else if (x == 'B') {                                           // | Se/enquanto 'B' pressionado -> Ré              | //
    recuar();                                                      // | Chama/Executa Função void de Movimento         | //
  } else if (x == 'L') {                                           // | Se/enquanto 'L' pressionado -> Vira Esquerda   | //
    left();                                                        // | Chama/Executa Função void de Movimento         | //
  } else if (x == 'R') {                                           // | Se/enquanto 'R' pressionado -> Vira Direita    | //
    right();                                                       // | Chama/Executa Função void de Movimento         | //
  } else if (x == 'G') {                                           // | Se/enquanto 'G' pressionado -> Frente Esquerda | //
    fLeft();                                                       // | Chama/Executa Função void de Movimento         | //
  } else if (x == 'I') {                                           // | Se/enquanto 'I' pressionado -> Frente Direita  | //
    fRight();                                                      // | Chama/Executa Função void de Movimento         | //
  } else if (x == 'H') {                                           // | Se/enquanto 'H' pressionado -> Trás Esquerda   | //
    tLeft();                                                       // | Chama/Executa Função void de Movimento         | //
  } else if (x == 'J') {                                           // | Se/enquanto 'J' pressionado -> Trás Direita    | //
    tRight();                                                      // | Chama/Executa Função void de Movimento         | //
  } else if (x == 'S') {                                           // | Se/enquanto 'S' (Nada Pressionado) -> Para!    | //
    parar();                                                       // | Chama/Executa Função void de Não Movimento     | //
  } /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - | */
  if (x == 'W' || x == 'w') {                                      // | Se/enquanto 'W' ou 'w' -> Estado do LED        | //
    if (x == 'W') {                                                // | Se/enquanto 'W' maiúsculo -> Acende o LED      | //
      digitalWrite(rR, HIGH);                                      // | Executa comando p/ acender o LED Vermelho      | //
    } else if (x == 'w') {                                         // | Se/enquanto 'w' minúsculo -> Apaga LED         | //
      digitalWrite(rR, LOW);                                       // | Executa comando p/ apagar o LED Vermelho       | //
    }
  } /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - | */
  if (x == 'U' || x == 'u') {                                      // | Se/enquanto 'U' ou 'u' -> Estado do LED        | //
    if (x == 'U') {                                                // | Se/enquanto 'U' maiúsculo -> Acende o LED      | //
      digitalWrite(rG, HIGH);                                      // | Executa comando p/ acender o LED Verde         | //
    } else if (x == 'u') {                                         // | Se/enquanto 'u' minúsculo -> Apaga LED         | //
      digitalWrite(rG, LOW);                                       // | Executa comando p/ apagar o LED Verde          | //
    }
  } /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - | */
  if (x == 'V' || x == 'v') {                                      // | Se/enquanto 'V' ou 'v' -> Estado do LED        | //
    if (x == 'V') {                                                // | Se/enquanto 'V' maiúsculo -> Acende o LED      | //
      digitalWrite(rB, HIGH);                                      // | Executa comando p/ acender o LED Azul          | //
    } else if (x == 'v') {                                         // | Se/enquanto 'v' minúsculo -> Apaga LED         | //
      digitalWrite(rB, LOW);                                       // | Executa comando p/ apagar o LED Azul           | //
    }
  } /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - | */
  
  if (x == 'X' || x == 'x') {                                      // | Se/enquanto 'U' ou 'u' -> Estado do Buzzer     | //
    if (x == 'X') {                                                // | Se/enquanto 'U' maiúsculo -> Aciona Buzzer     | //
      gogo();                                                      // | Frequência de toque do Buzzer                  | //
    } else if (x == 'x') {                                         // | Se/enquanto 'u' minúsculo -> Desliga Buzzer    | //
      gogo();                                                      // | Sem toque no Buzzer, desligado                 | //
    }
  } /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - | */

}/* ------------------------------------------------- FIM void CONTROL ------------------------------------------------- */

/* ---------------------------------- Função p/ Definição de Velocidade dos Motores ---------------------------------- | */
void fast() {                                                      // | Função Void P/ Velocidade dos Motores          | //
  if (x == '0') {                                                  // | Barra no Valor 0 -> Define Velocidade em 50    | //
    v = 50;                                                        // | Definição da Força do Motor na Ponte H         | //
  } else if (x == '1') {                                           // | Barra no Valor 1 -> Define Velocidade em 70    | //
    v = 70;                                                        // | Definição da Força do Motor na Ponte H         | //
  } else if (x == '2') {                                           // | Barra no Valor 2 -> Define Velocidade em 90    | //
    v = 90;                                                        // | Definição da Força do Motor na Ponte H         | //
  } else if (x == '3') {                                           // | Barra no Valor 3 -> Define Velocidade em 110   | //
    v = 110;                                                       // | Definição da Força do Motor na Ponte H         | //
  } else if (x == '4') {                                           // | Barra no Valor 4 -> Define Velocidade em 130   | //
    v = 130;                                                       // | Definição da Força do Motor na Ponte H         | //
  } else if (x == '5') {                                           // | Barra no Valor 5 -> Define Velocidade em 150   | //
    v = 150;                                                       // | Definição da Força do Motor na Ponte H         | //
  } else if (x == '6') {                                           // | Barra no Valor 6 -> Define Velocidade em 170   | //
    v = 170;                                                       // | Definição da Força do Motor na Ponte H         | //
  } else if (x == '7') {                                           // | Barra no Valor 7 -> Define Velocidade em 190   | //
    v = 190;                                                       // | Definição da Força do Motor na Ponte H         | //
  } else if (x == '8') {                                           // | Barra no Valor 8 -> Define Velocidade em 210   | //
    v = 210;                                                       // | Definição da Força do Motor na Ponte H         | //
  } else if (x == '9') {                                           // | Barra no Valor 9 -> Define Velocidade em 230   | //
    v = 230;                                                       // | Definição da Força do Motor na Ponte H         | //
  } else if (x == 'q') {                                           // | Barra no Valor 10 -> Define Velocidade em 255  | //
    v = 255;                                                       // | Definição da Força do Motor na Ponte H         | //
  }
}/* -------------------------------------------------- FIM void Fast. -------------------------------------------------- */

// ------------------------------------------- Funções p/ Movimento do Robô. ------------------------------------------- ||
void gogo() {                                                          //| Motores Movendo o Robô P/ Frente              ||
  mP.run(FORWARD);                                                     //| Motor Esquerdo, Movimento P/ Frente           ||
  mP.setSpeed(100);                                                    //| Definição do mE na Velocidade Atribuída a "v" ||
  delay(500);                                                          //| Delay/espera para movimento do pescoço        ||
  mP.run(BACKWARD);                                                    //| Motor Direito, Movimento P/ Frente            ||
  mP.setSpeed(100);                                                    //| Definição do mD na Velocidade Atribuída a "v" ||
  delay(1000);                                                         //| Delay/espera para movimento do pescoço        ||
  mP.run(FORWARD);                                                     //| Motor Esquerdo, Movimento P/ Frente           ||
  mP.setSpeed(100);                                                    //| Definição do mE na Velocidade Atribuída a "v" ||
  delay(500);                                                          //| Delay/espera para movimento do pescoço        ||
} // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ||
void seguir() {                                                        //| Motores Movendo o Robô P/ Frente              ||
  mE.run(FORWARD);                                                     //| Motor Esquerdo, Movimento P/ Frente           ||
  mE.setSpeed(v);                                                      //| Definição do mE na Velocidade Atribuída a "v" ||
  mD.run(FORWARD);                                                     //| Motor Direito, Movimento P/ Frente            ||
  mD.setSpeed(v);                                                      //| Definição do mD na Velocidade Atribuída a "v" ||
} // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ||
void recuar() {                                                        //| Motores Movendo o Robô P/ Trás                ||
  mE.run(BACKWARD);                                                    //| Motor Esquerdo, Movimento P/ Trás             ||
  mE.setSpeed(v);                                                      //| Definição do mE na Velocidade Atribuída a "v" ||
  mD.run(BACKWARD);                                                    //| Motor Direito, Movimento P/ Trás              ||
  mD.setSpeed(v - 15);                                                 //| Definição do mD na Velocidade Atribuída a "v" ||
} // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ||
void left() {                                                          //| Motores Movendo o Robô P/ Esquerda no Eixo    ||
  mE.run(FORWARD);                                                     //| Motor Esquerdo, Movimento P/ Frente           ||
  mE.setSpeed(v);                                                      //| Definição do mE na Velocidade Atribuída a "v" ||
  mD.run(BACKWARD);                                                    //| Definição do mD na Velocidade Atribuída a "v" ||
  mD.setSpeed(v);                                                      //| Definição do mD na Velocidade Atribuída a "v" ||
} // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ||
void right() {                                                         //| Motores Movendo o Robô P/ Direita no Eixo     ||
  mE.run(BACKWARD);                                                    //| Motor Esquerdo, Movimento P/ Trás             ||
  mE.setSpeed(v);                                                      //| Definição do mE na Velocidade Atribuída a "v" ||
  mD.run(FORWARD);                                                     //| Motor Direito, Movimento P/ Frente            ||
  mD.setSpeed(v);                                                      //| Definição do mD na Velocidade Atribuída a "v" ||
} // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ||
void tLeft() {                                                         //| Motores Movendo o Robô P/ Esquerda e Trás     ||
  mE.run(BACKWARD);                                                    //| Motor Esquerdo, Movimento P/ Trás             ||
  mE.setSpeed(v);                                                      //| Definição do mE na Velocidade Atribuída a "v" ||
  mD.run(BACKWARD);                                                    //| Definição do mD na Velocidade Atribuída a "v" ||
  mD.setSpeed(v / 2);                                                  //| Definição do mD Atribuída a metade de "v" v/2 ||
} // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ||
void tRight() {                                                        //| Motores Movendo o Robô P/ Direita e Trás      ||
  mE.run(BACKWARD);                                                    //| Motor Esquerdo, Movimento P/ Trás             ||
  mE.setSpeed(v / 2);                                                  //| Definição do mE Atribuída a metade de "v" v/2 ||
  mD.run(BACKWARD);                                                    //| Definição do mD na Velocidade Atribuída a "v" ||
  mD.setSpeed(v);                                                      //| Definição do mD na Velocidade Atribuída a "v" ||
} // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ||
void fLeft() {                                                         //| Motores Movendo o Robô P/ Esquerda e Frente   ||
  mE.run(FORWARD);                                                     //| Motor Esquerdo, Movimento P/ Frente           ||
  mE.setSpeed(v);                                                      //| Definição do mE na Velocidade Atribuída a "v" ||
  mD.run(FORWARD);                                                     //| Motor Direito, Movimento P/ Frente            ||
  mD.setSpeed(v / 2);                                                  //| Definição do mD Atribuída a metade de "v" v/2 ||
} // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ||
void fRight() {                                                        //| Motores Movendo o Robô P/ Direita e Frante    ||
  mE.run(FORWARD);                                                     //| Motor Esquerdo, Movimento P/ Frente           ||
  mE.setSpeed(v / 2);                                                  //| Definição do mE Atribuída a metade de "v" v/2 ||
  mD.run(FORWARD);                                                     //| Motor Direito, Movimento P/ Frente            ||
  mD.setSpeed(v);                                                      //| Definição do mD na Velocidade Atribuída a "v" ||
} // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ||
void parar() {                                                         //| Motores NÃO Giram, Robô Permanece Imóvel      ||
  mE.run(RELEASE);                                                     //| Motor Esquerdo Sem Movimentos: "Liberado"     ||
  mE.setSpeed(0);                                                      //| Definição do mE Atribuída a Zero, Motor Off   ||
  mD.run(RELEASE);                                                     //| Motor Esquerdo Sem Movimentos: "Liberado"     ||
  mD.setSpeed(0);                                                      //| Definição do mD Atribuída a Zero, Motor Off   ||
} // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ||