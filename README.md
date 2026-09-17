Segue o README.md completo, pronto para copiar e colar no seu repositório do GitHub. Incluí o modelo da ESP32-C3, pinagem, instalação dos drivers, comunicação MQTT, configuração do HiveMQ Cloud, funcionamento dos LEDs e instruções para publicar o dashboard no GitHub Pages.

Markdown

````
# 🍄 MofoSense — Monitoramento Inteligente de Risco de Mofo

![ESP32](https://img.shields.io/badge/ESP32--C3-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![MQTT](https://img.shields.io/badge/MQTT-HiveMQ-660066?style=for-the-badge)
![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)
![HTML5](https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white)
![CSS3](https://img.shields.io/badge/CSS3-1572B6?style=for-the-badge&logo=css3&logoColor=white)

## 📖 Sobre o projeto

O **MofoSense** é um sistema de monitoramento ambiental desenvolvido com ESP32-C3, sensor DHT11, LEDs indicadores e comunicação MQTT.

O projeto realiza medições de temperatura e umidade relativa do ar, identifica condições ambientais que podem favorecer o desenvolvimento de mofo e envia os dados para um dashboard web em tempo real.

As informações são transmitidas pela internet utilizando o protocolo MQTT e o serviço HiveMQ Cloud.

O dashboard permite acompanhar os dados por meio de indicadores visuais, gráficos e alertas.

> **Importante:** o sistema não detecta fungos ou esporos diretamente. Ele estima condições favoráveis ao desenvolvimento de mofo a partir da temperatura e da umidade relativa do ar. O LED verde indica apenas que os limites configurados não foram atingidos.

---

## 🎯 Objetivos

- Monitorar a temperatura ambiente.
- Monitorar a umidade relativa do ar.
- Identificar condições favoráveis ao desenvolvimento de mofo.
- Acionar um LED vermelho quando houver risco.
- Acionar um LED verde quando não houver alerta.
- Enviar os dados para o HiveMQ Cloud.
- Apresentar as informações em um dashboard web.
- Exibir gráficos atualizados em tempo real.
- Permitir o acompanhamento remoto do ambiente.

---

## 🧰 1. Componentes utilizados

| Quantidade | Componente | Função |
|---|---|---|
| 1 | ESP32-C3 | Microcontrolador principal |
| 1 | Sensor DHT11 | Leitura de temperatura e umidade |
| 1 | LED vermelho | Indicador de risco |
| 1 | LED verde | Indicador sem alerta |
| 2 | Resistores de 220 Ω ou 330 Ω | Limitação de corrente dos LEDs |
| 1 | Protoboard | Montagem do circuito |
| Diversos | Jumpers | Conexões elétricas |
| 1 | Cabo USB de dados | Alimentação e programação |

### Modelo do microcontrolador

**ESP32-C3 — Família Espressif ESP32-C3**

O projeto utiliza uma placa de desenvolvimento baseada no microcontrolador ESP32-C3.

Características principais:

- Processador RISC-V de 32 bits.
- Frequência de até 160 MHz.
- Wi-Fi de 2,4 GHz.
- Bluetooth Low Energy 5.
- Interfaces GPIO, UART, SPI e I²C.
- Suporte ao Arduino IDE.
- Comunicação MQTT por Wi-Fi.

Na Arduino IDE, a opção de placa utilizada é:

```text
ESP32C3 Dev Module
```

Essa opção atende a diversas placas genéricas baseadas no ESP32-C3. A identificação exata do fabricante e da versão da placa deve ser conferida na inscrição física do dispositivo.

---

## 🔌 2. Pinagem do projeto

### Sensor DHT11

| DHT11 | ESP32-C3 |
|---|---|
| VCC | 3V3 (recomendado, se compatível) |
| DATA | GPIO 10 |
| GND | GND |

Na montagem original, o VCC do DHT11 foi conectado ao pino de 5 V.

**Atenção:** os GPIOs da ESP32-C3 trabalham com sinais de 3,3 V e não são tolerantes a 5 V.

Se o DHT11 estiver alimentado com 5 V, verifique a tensão da saída DATA. Caso ela seja de 5 V, utilize um conversor de nível lógico para proteger o GPIO 10.

Quando o sensor ou módulo permitir alimentação em 3,3 V, essa é a opção recomendada para simplificar a conexão.

Caso utilize um DHT11 sem placa de circuito integrada, pode ser necessário um resistor pull-up de aproximadamente 10 kΩ entre DATA e 3V3.

### LED vermelho

| Terminal | Conexão |
|---|---|
| Ânodo (+) | GPIO 3, através de resistor |
| Cátodo (-) | GND |

### LED verde

| Terminal | Conexão |
|---|---|
| Ânodo (+) | GPIO 2, através de resistor |
| Cátodo (-) | GND |

Os dois LEDs devem utilizar resistores limitadores de corrente de 220 Ω ou 330 Ω.

O GPIO 2 é um pino de configuração de inicialização da ESP32-C3. Se ocorrerem dificuldades para iniciar ou gravar a placa, verifique o circuito conectado a esse pino e considere transferir o LED verde para outro GPIO disponível, ajustando também o código.

### Resumo da pinagem

```text
ESP32-C3
│
├── GPIO 10 ─── DATA DHT11
│
├── GPIO 3 ──── Resistor ─── LED Vermelho ─── GND
│
├── GPIO 2 ──── Resistor ─── LED Verde ────── GND
│
├── 3V3 ─────── VCC DHT11
│
└── GND ─────── GND DHT11
```

---

## 💻 3. Instalação do Arduino IDE

Faça o download do Arduino IDE:

https://www.arduino.cc/en/software

Após instalar o programa, será necessário adicionar o suporte às placas ESP32.

### Adicionando o suporte à ESP32

1. Abra o Arduino IDE.
2. Acesse **Arquivo → Preferências**.
3. Localize o campo de URLs adicionais para Gerenciadores de Placas.
4. Adicione a URL:

```text
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

5. Abra o Gerenciador de Placas.
6. Pesquise por `esp32`.
7. Instale o pacote **esp32 by Espressif Systems**.

Em seguida, selecione:

```text
Ferramentas → Placa → ESP32 Arduino → ESP32C3 Dev Module
```

Conecte a ESP32-C3 ao computador utilizando um cabo USB de dados.

Selecione a porta correspondente em:

```text
Ferramentas → Porta
```

---

## 🛠️ 4. Instalação de drivers da ESP32-C3

Se a ESP32-C3 não for reconhecida pelo computador ou não aparecer nenhuma porta serial no Arduino IDE, verifique inicialmente o cabo USB e a conexão com a placa.

Algumas placas ESP32-C3 utilizam USB nativo, enquanto outras possuem conversores USB-Serial que podem exigir drivers específicos.

### Instalador de drivers e ferramentas

Para auxiliar na instalação e configuração do ambiente, utilize o projeto:

**OneClickInstallerEspRasp**

https://github.com/perabru/OneClickInstallerEspRasp

Acesse o repositório e consulte as instruções de instalação disponíveis.

O instalador pode auxiliar na preparação do ambiente, conforme os dispositivos e drivers contemplados pelo projeto.

> O driver necessário depende do circuito USB utilizado pela sua placa. Verifique o modelo do conversor USB-Serial antes de instalar drivers de terceiros.

---

## 📚 5. Bibliotecas necessárias

No Arduino IDE, acesse:

```text
Sketch → Incluir Biblioteca → Gerenciar Bibliotecas
```

Instale as seguintes bibliotecas:

| Biblioteca | Desenvolvedor | Finalidade |
|---|---|---|
| DHT sensor library | Adafruit | Leitura do sensor DHT11 |
| Adafruit Unified Sensor | Adafruit | Dependência da biblioteca DHT |
| PubSubClient | Nick O'Leary | Comunicação MQTT |

O projeto também utiliza:

```cpp
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <time.h>
```

As bibliotecas de Wi-Fi e TLS fazem parte do pacote ESP32 instalado no Arduino IDE.

---

## 🌡️ 6. Funcionamento do detector

O sensor DHT11 coleta duas grandezas ambientais:

**Temperatura:** medida em graus Celsius (°C).

**Umidade relativa:** medida em porcentagem (%).

A ESP32-C3 processa os valores recebidos e aplica os limites configurados no firmware.

### Critérios de risco

Os critérios demonstrativos utilizados no projeto são:

| Condição | Classificação |
|---|---|
| Umidade ≥ 70% | RISCO |
| Umidade ≥ 65% e temperatura entre 20 °C e 30 °C | RISCO |
| Demais condições válidas | SEGURO |
| Falha na leitura do DHT11 | ERRO |

Os limites são heurísticos e podem ser ajustados de acordo com os objetivos do projeto.

O desenvolvimento de mofo também depende de fatores como umidade das superfícies, ventilação, material e tempo de exposição.

### Comportamento dos LEDs

#### 🔴 LED vermelho — Risco

Quando as condições atingem os limites estabelecidos:

```text
LED VERMELHO: LIGADO
LED VERDE: DESLIGADO
```

O MQTT publica:

```text
perabru/mofo/risco → RISCO
```

#### 🟢 LED verde — Sem alerta

Quando os valores não atingem os limites de risco:

```text
LED VERMELHO: DESLIGADO
LED VERDE: LIGADO
```

O MQTT publica:

```text
perabru/mofo/risco → SEGURO
```

#### ⚠️ Falha no sensor

Quando o DHT11 apresenta erro de leitura, os dois LEDs são desligados.

O MQTT publica:

```text
perabru/mofo/risco → ERRO
```

O estado `SEGURO` não significa ausência comprovada de mofo.

---

## ☁️ 7. Comunicação com HiveMQ Cloud

O sistema utiliza MQTT para transmitir dados da ESP32-C3 para o broker HiveMQ Cloud.

O broker recebe as mensagens publicadas pela placa e permite que o dashboard web acompanhe as atualizações.

### Endereço do broker

```text
125e4c5cf1a84e15a472be4cda4c9761.s1.eu.hivemq.cloud
```

### Configuração MQTT da ESP32-C3

| Parâmetro | Valor |
|---|---|
| Broker | HiveMQ Cloud |
| Protocolo | MQTT sobre TLS |
| Porta | 8883 |
| Usuário | perabru |
| Autenticação | Usuário e senha |
| Transporte | TCP seguro |

A senha não deve ser publicada no repositório.

Configure suas credenciais localmente no firmware antes de enviar o programa para a placa.

### Configuração MQTT do dashboard

O dashboard utiliza MQTT sobre WebSocket seguro.

| Parâmetro | Valor |
|---|---|
| Protocolo | WSS |
| Porta | 8884 |
| Biblioteca | MQTT.js |
| Usuário | perabru |
| Autenticação | Usuário e senha |

Endereço utilizado pelo navegador:

```text
wss://125e4c5cf1a84e15a472be4cda4c9761.s1.eu.hivemq.cloud:8884/mqtt
```

**Atenção:** a porta 8883 é utilizada pela ESP32-C3. O navegador utiliza a porta 8884 com WebSocket seguro.

Verifique se o endpoint de WebSocket está habilitado e disponível no seu serviço HiveMQ Cloud.

---

## 📡 8. Tópicos MQTT

O projeto utiliza os seguintes tópicos:

| Tópico | Descrição | Exemplo |
|---|---|---|
| `perabru/mofo/temperatura` | Temperatura ambiente | `27.00` |
| `perabru/mofo/umidade` | Umidade relativa | `78.00` |
| `perabru/mofo/risco` | Classificação ambiental | `RISCO` |
| `perabru/mofo/led_vermelho` | Estado do LED vermelho | `ON` |
| `perabru/mofo/led_verde` | Estado do LED verde | `OFF` |
| `perabru/mofo/status` | Estado da conexão MQTT | `online` |

### Tópico de assinatura

Para receber todos os dados, o dashboard deve assinar:

```text
perabru/mofo/#
```

O caractere `#` permite acompanhar todos os tópicos abaixo de `perabru/mofo/`.

### Exemplo de mensagens

```text
perabru/mofo/temperatura
27.00

perabru/mofo/umidade
78.00

perabru/mofo/risco
RISCO

perabru/mofo/led_vermelho
ON

perabru/mofo/led_verde
OFF

perabru/mofo/status
online
```

### Frequência das publicações

O firmware realiza uma leitura aproximadamente a cada 5 segundos.

Após uma leitura válida, os valores são enviados ao HiveMQ Cloud quando há conexão MQTT disponível.

As mensagens são publicadas com a opção `retained`.

Isso permite que novos clientes recebam os últimos valores publicados ao se inscreverem nos tópicos.

**Observação:** valores retidos podem ficar desatualizados se o dispositivo estiver offline. O dashboard deve considerar o estado de conexão e a idade das medições.

---

## 🌐 9. Dashboard web

O dashboard foi desenvolvido com:

- HTML5.
- CSS3.
- JavaScript.
- MQTT.js.
- Gráficos interativos.

O site se conecta ao HiveMQ Cloud por WebSocket seguro e recebe as mensagens publicadas pela ESP32-C3.

### Funcionalidades

- Exibição da temperatura atual.
- Exibição da umidade relativa.
- Gráficos de temperatura e umidade.
- Indicador visual de risco de mofo.
- Visualização do estado dos LEDs.
- Acompanhamento da conexão MQTT.
- Layout responsivo para computadores e celulares.

O dashboard não precisa de um servidor próprio para receber os dados MQTT.

A comunicação ocorre diretamente entre o navegador e o HiveMQ Cloud.

### Arquivo principal

O site está concentrado em um único arquivo:

```text
index.html
```

Esse arquivo contém a estrutura HTML, a estilização CSS e a lógica JavaScript.

As bibliotecas externas utilizadas pelo dashboard precisam estar disponíveis pela internet.

---

## 🚀 10. Publicação no GitHub Pages

O dashboard pode ser hospedado gratuitamente no GitHub Pages.

### Passo 1 — Criar o repositório

Acesse:

https://github.com

Crie um novo repositório para o projeto.

Exemplo de nome:

```text
MofoSense
```

### Passo 2 — Enviar o site

Adicione o arquivo `index.html` à raiz do repositório.

Exemplo de estrutura:

```text
MofoSense/
│
├── index.html
│
├── README.md
│
└── firmware/
    └── monitor_mofo.ino
```

A pasta `firmware` é opcional e pode ser utilizada para armazenar o código da ESP32-C3.

### Passo 3 — Habilitar o GitHub Pages

Dentro do repositório:

1. Acesse Settings.
2. Clique em Pages.
3. Em Build and deployment, escolha Deploy from a branch.
4. Selecione a branch main.
5. Selecione a pasta /(root).
6. Clique em Save.

Após a publicação, o site poderá ser acessado por um endereço semelhante a:

```text
https://SEU_USUARIO.github.io/MofoSense/
```

Substitua `SEU_USUARIO` pelo usuário proprietário do repositório.

### Passo 4 — Conectar ao HiveMQ

Abra o dashboard publicado.

Informe a senha do HiveMQ no formulário de conexão, quando solicitado.

Após a autenticação, o site deverá receber as mensagens publicadas pela ESP32-C3.

**Nunca coloque a senha do HiveMQ diretamente no JavaScript de um site público.**

O GitHub Pages disponibiliza os arquivos do site para qualquer visitante, e todo código JavaScript enviado ao navegador pode ser inspecionado.

Para um dashboard público sem exposição de credenciais MQTT, utilize um backend intermediário com autenticação e permissões apropriadas.

---

## 🔄 11. Fluxo de funcionamento

```text
           AMBIENTE
               |
               v
         +-----------+
         |   DHT11   |
         | Temp / UR |
         +-----------+
               |
               | GPIO 10
               v
         +-----------+
         | ESP32-C3  |
         +-----------+
               |
       +-------+-------+
       |               |
       v               v
   LED VERMELHO     LED VERDE
       |               |
      RISCO         SEM ALERTA
       |
       +-------+-------+
               |
               v
         REDE WI-FI
               |
               v
        HIVEMQ CLOUD
               |
        MQTT / TLS
               |
               v
       DASHBOARD WEB
               |
       +-------+-------+
       |               |
       v               v
    GRÁFICOS        ALERTAS
```

A ESP32-C3 é responsável pelas leituras, classificação ambiental e controle físico dos LEDs.

O HiveMQ Cloud atua como intermediário das mensagens.

O dashboard apresenta os dados recebidos.

---

## 🧪 12. Testando o sistema

### Teste 1 — Sensor DHT11

Conecte a ESP32-C3 ao computador.

Abra o Monitor Serial do Arduino IDE e configure:

```text
115200 baud
```

O sistema deverá apresentar mensagens semelhantes a:

```text
----------------------------
Temperatura: 24.00 C
Umidade: 48.00 %

AMBIENTE SEM ALERTA
LED VERDE ACESO

Dados publicados no HiveMQ!
```

### Teste 2 — Condição de risco

Para testar o acionamento do LED vermelho, aproxime o sensor de uma fonte de umidade sem molhar o componente.

Quando a umidade atingir os limites configurados, a saída esperada será semelhante a:

```text
----------------------------
Temperatura: 27.00 C
Umidade: 78.00 %

ALERTA: RISCO DE MOFO!
LED VERMELHO ACESO

Dados publicados no HiveMQ!
```

### Teste 3 — Recebimento MQTT

Utilize um cliente MQTT compatível com TLS.

Configure o endereço do broker, a porta 8883 e as credenciais.

Assine:

```text
perabru/mofo/#
```

Verifique se os valores de temperatura, umidade e risco estão chegando corretamente.

### Teste 4 — Dashboard

Abra o site publicado no GitHub Pages.

Conecte ao HiveMQ Cloud.

Verifique se:

- A temperatura é atualizada.
- A umidade é atualizada.
- O indicador de risco acompanha o firmware.
- Os gráficos recebem novas medições.
- O estado dos LEDs corresponde ao circuito físico.

---

## 🔧 13. Solução de problemas

### A ESP32-C3 não aparece no Arduino IDE

Verifique:

- Se o cabo USB transmite dados.
- Se a porta USB está funcionando.
- Se o pacote ESP32 foi instalado.
- Se a placa selecionada é ESP32C3 Dev Module.
- Se o driver USB necessário está instalado.

Consulte também:

https://github.com/perabru/OneClickInstallerEspRasp

### O sensor DHT11 não responde

Verifique:

- Alimentação do sensor.
- Conexão GND.
- DATA conectado ao GPIO 10.
- Compatibilidade da tensão de alimentação.
- Necessidade de resistor pull-up.
- Instalação da biblioteca DHT.

### Os LEDs não acendem

Verifique:

- Polaridade dos LEDs.
- Resistores limitadores de corrente.
- Conexões nos GPIOs 2 e 3.
- Continuidade das conexões da protoboard.

Se a ESP32-C3 não inicializar, verifique especialmente o circuito conectado ao GPIO 2.

### O Wi-Fi não conecta

Verifique:

- Nome da rede.
- Senha do Wi-Fi.
- Intensidade do sinal.
- Disponibilidade de uma rede de 2,4 GHz.

A ESP32-C3 não se conecta diretamente a redes exclusivamente de 5 GHz.

### O HiveMQ não conecta

Verifique:

- Endereço do broker.
- Porta 8883 no firmware.
- Usuário e senha.
- Conexão com a internet.
- Certificado TLS.
- Sincronização de horário NTP.

A sincronização de horário é importante para a validação do certificado digital.

### O dashboard não recebe dados

Verifique:

- Se a ESP32-C3 está publicando mensagens.
- Se o navegador conseguiu autenticar no HiveMQ.
- Se a conexão WebSocket utiliza a porta 8884.
- Se o tópico de assinatura está correto.
- Se o endpoint WebSocket está disponível no broker.

O tópico de assinatura deve ser:

```text
perabru/mofo/#
```

---

## 🔐 14. Segurança

O projeto utiliza conexões MQTT protegidas por TLS.

Recomendações:

1. Não publique senhas no GitHub.
2. Não armazene credenciais diretamente no HTML ou JavaScript público.
3. Utilize senhas fortes e exclusivas.
4. Troque credenciais que tenham sido compartilhadas publicamente.
5. Utilize permissões MQTT restritas aos tópicos necessários.
6. Mantenha as bibliotecas e o firmware atualizados.

O GitHub Pages é adequado para hospedar o dashboard estático, mas não oferece armazenamento secreto para credenciais executadas no navegador.

---

## 📈 15. Possíveis melhorias

O projeto pode ser expandido com:

- Armazenamento histórico em banco de dados.
- Alertas por e-mail ou Telegram.
- Notificações no celular.
- Relatórios de temperatura e umidade.
- Exportação de medições em CSV.
- Controle automático de ventiladores.
- Acionamento de desumidificadores.
- Integração com sensores adicionais.
- Monitoramento de diferentes ambientes.
- Identificação visual de mofo por câmera e inteligência artificial.

Para melhorar a avaliação ambiental, também é possível considerar a duração da exposição à umidade elevada e utilizar sensores adicionais para medir condições das superfícies.

---

## 👨‍💻 Autor

**Bruno Michel Pera**

GitHub: https://github.com/perabru

Projeto desenvolvido com ESP32-C3, DHT11, HiveMQ Cloud, HTML, CSS e JavaScript.

---

## 📌 Considerações finais

O MofoSense demonstra a integração entre sistemas embarcados, sensores ambientais, Internet das Coisas e desenvolvimento web.

A ESP32-C3 realiza as medições e controla os indicadores físicos, enquanto o HiveMQ Cloud permite a comunicação com o dashboard.

O resultado é um sistema de monitoramento remoto que auxilia na identificação de condições ambientais favoráveis ao desenvolvimento de mofo.

O projeto tem finalidade educacional e de monitoramento ambiental, não substituindo uma inspeção técnica para identificar contaminação por fungos.
````
