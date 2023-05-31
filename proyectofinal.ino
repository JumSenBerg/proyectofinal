const int bombaPin = 2;
const int triggerPin = 3;
const int echoPin = 4;

// Definición de la clase SistemaRiego
class SistemaRiego {
private:
  int humedad;
  long duracion;
  float distancia;

public:
  // Constructor de la clase
  SistemaRiego() {
    // Configuración de pines
    pinMode(bombaPin, OUTPUT);
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Inicialización de la comunicación serial
    Serial.begin(9600);
  }

  // Método principal para ejecutar el sistema de riego
  void ejecutar() {
    leerHumedad();
    controlarBomba();
    medirDistancia();
    mostrarDatos();
    delay(1000);
  }

private:
  // Método para leer la humedad del suelo
  void leerHumedad() {
    humedad = analogRead(A0);
    Serial.print("Humedad: ");
    Serial.println(humedad);
    
  }

  // Método para controlar el estado de la bomba según la humedad
  void controlarBomba() {
    if (humedad >= 721 && humedad <= 1024) {
      digitalWrite(bombaPin, LOW);
    } else {
      digitalWrite(bombaPin, HIGH);
    }
  }

  // Método para medir la distancia utilizando un sensor ultrasónico
  void medirDistancia() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
  
    // Mide el tiempo que tarda en recibir el eco
    duracion = pulseIn(echoPin, HIGH);
  
    // Calcula la distancia en cm
    distancia = duracion * 0.034 / 2;
  }

  // Método para mostrar los datos de distancia y volumen en el monitor serial
  void mostrarDatos() {
    // Calcula el volumen en ml
    float volumen = calcularVolumen(distancia);

    // Muestra la distancia y el volumen en el monitor serial
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.print(" cm = ");
    Serial.print(volumen);
    Serial.println(" mL");
  }

  // Método para calcular el volumen según la distancia
  int calcularVolumen(float distancia) {
    // Calcula el volumen utilizando una fórmula aproximada
    if (distancia >= 21.51) {
      return 473;
    } else if (distancia >= 19.33) {
      return 946;
    } else if (distancia >= 14.50) {
      return 1892;
    } else if (distancia >= 9.21) {
      return 2838;
    } else if (distancia >= 4.68) {
      return 3785;
    }
  }
};

// Creación de una instancia de la clase SistemaRiego
SistemaRiego sistemaRiego;

void setup() {
  // Inicialización del sistema de riego
  sistemaRiego = SistemaRiego();
}

void loop() {
  // Ejecución continua del sistema de riego
  sistemaRiego.ejecutar();
}

