
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <time.h>

// =====================================
// 1. PINAGEM
// =====================================

#define PINO_DHT 10
#define PINO_LED_VERMELHO 3
#define PINO_LED_VERDE 2

#define TIPO_DHT DHT11

DHT dht(PINO_DHT, TIPO_DHT);

// =====================================
// 2. CONFIGURACAO WI-FI
// =====================================

const char* WIFI_SSID = "BRUNO";
const char* WIFI_SENHA = "123456789";

// =====================================
// 3. CONFIGURACAO HIVEMQ
// =====================================

const char* MQTT_SERVIDOR =
  "125e4c5cf1a84e15a472be4cda4c9761.s1.eu.hivemq.cloud";

const int MQTT_PORTA = 8883;

const char* MQTT_USUARIO = "perabru";
const char* MQTT_SENHA = "123456789";

// =====================================
// 4. TOPICOS MQTT
// =====================================

const char* TOPICO_TEMPERATURA =
  "perabru/mofo/temperatura";

const char* TOPICO_UMIDADE =
  "perabru/mofo/umidade";

const char* TOPICO_RISCO =
  "perabru/mofo/risco";

const char* TOPICO_LED_VERMELHO =
  "perabru/mofo/led_vermelho";

const char* TOPICO_LED_VERDE =
  "perabru/mofo/led_verde";

const char* TOPICO_STATUS =
  "perabru/mofo/status";

// =====================================
// 5. CERTIFICADO TLS
// ISRG Root X1 - Let's Encrypt
// =====================================

static const char ROOT_CA[] = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";

// =====================================
// 6. CLIENTES WI-FI E MQTT
// =====================================

WiFiClientSecure wifiSeguro;
PubSubClient mqtt(wifiSeguro);

String mqttClientId;

// =====================================
// 7. CONFIGURACAO DOS LIMITES
// =====================================

const float UMIDADE_ALTA = 70.0;
const float UMIDADE_MODERADA = 65.0;

const float TEMP_MIN = 20.0;
const float TEMP_MAX = 30.0;

// Intervalo das leituras: 5 segundos
const unsigned long INTERVALO_LEITURA = 5000;

// Intervalo de reconexao: 5 segundos
const unsigned long INTERVALO_RECONEXAO = 5000;

unsigned long ultimaLeitura = 0;
unsigned long ultimaTentativaMQTT = 0;
unsigned long ultimaTentativaWiFi = 0;

// =====================================
// 8. CONECTAR AO WI-FI
// =====================================

void conectarWiFi() {

  Serial.println("Conectando ao Wi-Fi...");

  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_SENHA);

}

// =====================================
// 9. CONECTAR AO HIVEMQ
// =====================================

void conectarMQTT() {

  if (mqtt.connected()) {
    return;
  }

  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  // Aguarda o relogio estar sincronizado.
  // Necessario para validar o certificado TLS.
  if (time(nullptr) < 1700000000) {
    Serial.println("Aguardando sincronizacao NTP...");
    return;
  }

  Serial.println("Conectando ao HiveMQ Cloud...");

  // O ultimo argumento configura a mensagem
  // de ultimo desejo (Last Will).
  bool conectado = mqtt.connect(
    mqttClientId.c_str(),
    MQTT_USUARIO,
    MQTT_SENHA,
    TOPICO_STATUS,
    1,
    true,
    "offline"
  );

  if (conectado) {

    Serial.println("HiveMQ conectado!");

    // Publicacao retida do estado online
    mqtt.publish(
      TOPICO_STATUS,
      "online",
      true
    );

    // Forca uma nova leitura apos reconectar
    ultimaLeitura = millis() - INTERVALO_LEITURA;

  } else {

    Serial.print("Erro MQTT. Codigo: ");
    Serial.println(mqtt.state());

  }

}

// =====================================
// 10. PUBLICAR DADOS NO HIVEMQ
// =====================================

void publicarDados(
  float temperatura,
  float umidade,
  bool riscoMofo
) {

  if (!mqtt.connected()) {
    Serial.println("MQTT desconectado. Dados nao enviados.");
    return;
  }

  // Converte valores para texto
  String tempTexto = String(temperatura, 2);
  String umidTexto = String(umidade, 2);

  const char* estadoRisco =
    riscoMofo ? "RISCO" : "SEGURO";

  const char* estadoVermelho =
    riscoMofo ? "ON" : "OFF";

  const char* estadoVerde =
    riscoMofo ? "OFF" : "ON";

  // Publicar temperatura
  mqtt.publish(
    TOPICO_TEMPERATURA,
    tempTexto.c_str(),
    true
  );

  // Publicar umidade
  mqtt.publish(
    TOPICO_UMIDADE,
    umidTexto.c_str(),
    true
  );

  // Publicar classificacao
  mqtt.publish(
    TOPICO_RISCO,
    estadoRisco,
    true
  );

  // Publicar estado do LED vermelho
  mqtt.publish(
    TOPICO_LED_VERMELHO,
    estadoVermelho,
    true
  );

  // Publicar estado do LED verde
  mqtt.publish(
    TOPICO_LED_VERDE,
    estadoVerde,
    true
  );

  Serial.println("Dados publicados no HiveMQ!");

}

// =====================================
// 11. CONFIGURACAO INICIAL
// =====================================

void setup() {

  Serial.begin(115200);

  pinMode(PINO_LED_VERMELHO, OUTPUT);
  pinMode(PINO_LED_VERDE, OUTPUT);

  digitalWrite(PINO_LED_VERMELHO, LOW);
  digitalWrite(PINO_LED_VERDE, LOW);

  dht.begin();

  Serial.println();
  Serial.println("============================");
  Serial.println(" DETECTOR DE RISCO DE MOFO");
  Serial.println(" ESP32-C3 + HIVEMQ CLOUD");
  Serial.println("============================");

  conectarWiFi();

  // Sincroniza a hora via internet
  configTime(
    0,
    0,
    "pool.ntp.org",
    "time.google.com"
  );

  // Configura TLS com validacao de certificado
  wifiSeguro.setCACert(ROOT_CA);

  // Configura servidor MQTT
  mqtt.setServer(
    MQTT_SERVIDOR,
    MQTT_PORTA
  );

  // Identificador unico por ESP32
  mqttClientId = "ESP32C3-MOFO-" +
    String((uint32_t)ESP.getEfuseMac(), HEX);

  Serial.print("Cliente MQTT: ");
  Serial.println(mqttClientId);

  // Primeira leitura imediata
  ultimaLeitura = millis() - INTERVALO_LEITURA;

}

// =====================================
// 12. LOOP PRINCIPAL
// =====================================

void loop() {

  unsigned long agora = millis();

  // ---------------------------------
  // VERIFICAR WI-FI
  // ---------------------------------

  if (WiFi.status() != WL_CONNECTED) {

    if (agora - ultimaTentativaWiFi >=
        INTERVALO_RECONEXAO) {

      ultimaTentativaWiFi = agora;

      Serial.println("Wi-Fi desconectado.");

      conectarWiFi();

    }

  } else {

    // ---------------------------------
    // VERIFICAR MQTT
    // ---------------------------------

    if (!mqtt.connected()) {

      if (agora - ultimaTentativaMQTT >=
          INTERVALO_RECONEXAO) {

        ultimaTentativaMQTT = agora;

        conectarMQTT();

      }

    } else {

      mqtt.loop();

    }

  }

  // ---------------------------------
  // LER SENSOR A CADA 5 SEGUNDOS
  // ---------------------------------

  if (agora - ultimaLeitura >=
      INTERVALO_LEITURA) {

    ultimaLeitura = agora;

    float temperatura =
      dht.readTemperature();

    float umidade =
      dht.readHumidity();

    // ---------------------------------
    // VALIDAR LEITURAS
    // ---------------------------------

    if (isnan(temperatura) ||
        isnan(umidade)) {

      Serial.println("Erro ao ler DHT11!");

      digitalWrite(
        PINO_LED_VERMELHO,
        LOW
      );

      digitalWrite(
        PINO_LED_VERDE,
        LOW
      );

      if (mqtt.connected()) {

        mqtt.publish(
          TOPICO_RISCO,
          "ERRO",
          true
        );

        mqtt.publish(
          TOPICO_LED_VERMELHO,
          "OFF",
          true
        );

        mqtt.publish(
          TOPICO_LED_VERDE,
          "OFF",
          true
        );

      }

      return;
    }

    // ---------------------------------
    // MOSTRAR TEMPERATURA E UMIDADE
    // ---------------------------------

    Serial.println("----------------------------");

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" C");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");

    // ---------------------------------
    // CALCULAR RISCO DE MOFO
    // ---------------------------------

    bool riscoMofo = false;

    if (umidade >= UMIDADE_ALTA) {

      riscoMofo = true;

    }

    else if (
      umidade >= UMIDADE_MODERADA &&
      temperatura >= TEMP_MIN &&
      temperatura <= TEMP_MAX
    ) {

      riscoMofo = true;

    }

    // ---------------------------------
    // ACIONAR LEDS
    // ---------------------------------

    if (riscoMofo) {

      digitalWrite(
        PINO_LED_VERMELHO,
        HIGH
      );

      digitalWrite(
        PINO_LED_VERDE,
        LOW
      );

      Serial.println("ALERTA: RISCO DE MOFO!");
      Serial.println("LED VERMELHO ACESO");

    } else {

      digitalWrite(
        PINO_LED_VERMELHO,
        LOW
      );

      digitalWrite(
        PINO_LED_VERDE,
        HIGH
      );

      Serial.println("AMBIENTE SEM ALERTA");
      Serial.println("LED VERDE ACESO");

    }

    // ---------------------------------
    // ENVIAR DADOS PARA HIVEMQ
    // ---------------------------------

    publicarDados(
      temperatura,
      umidade,
      riscoMofo
    );

  }

}