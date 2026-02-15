# Network Module - README

## Overview

The `network` module is responsible for handling communication between the client and the server.

- The `client` side handles events and updates that affect the local player.
  Examples: player health, animations, skins, etc.

- The `server` side handles data received from clients and processes it on the server.

---

## Folder Structure
```
network/
├── client/
│   ├── set_anim/
│   │   ├── set_anim.cpp
│   │   └── set_anim.hpp
│   └── set_health/
│       ├── set_health.cpp
│       └── set_health.hpp
│
├── server/
│   └── onPlayerDamage/
│       ├── onPlayerDamageServer.cpp
│       └── onPlayerDamageServer.hpp
│
├── connectServer.hpp
└── connection.hpp
```
---

## Responsibilities

### Client

The client is responsible for:

- Updating player 
- Setting animations
- Handling visual/player-side changes

#### Functions

set_health(float health);

Description:
Receives a float value representing the player's health and updates the player's health locally.

---

### Server

The server is responsible for:

- Receiving data from clients
- Processing damage events
- Broadcasting or handling server-side logic

#### Functions

onPlayerDamageServer(float health, ServerSocket server, std::string name);

Description:
Receives:
- health: The updated health value after damage
- server: The ServerSocket instance
- name: The player's name

Sends a formatted message to the server in the following format:

onPlayerDamage::name::damage

Example:
onPlayerDamage::Player1::25

---

## Headers

connectServer.hpp
- Responsible for handling server connection setup.

connection.hpp
- Handles low-level connection and socket management.

---

## Notes

- All client-to-server communication follows a structured string format.
- Server processes the message and applies the necessary game logic.
- Client is responsible only for local updates and sending events.

# Network Module - README


## PT-BR


## Visão Geral

O módulo `network` é responsável pela comunicação entre o cliente e o servidor.

- O lado `client` é responsável por tudo que acontece localmente no jogador.
  Exemplos: vida do player, animações, skins e atualizações visuais.

- O lado `server` é responsável por processar as informações enviadas pelo cliente,
  aplicar a lógica do jogo no servidor e tratar os eventos recebidos.

--------------------------------------------------

## Estrutura de Pastas
```
network/
├── client/
│   ├── set_anim/
│   │   ├── set_anim.cpp
│   │   └── set_anim.hpp
│   └── set_health/
│       ├── set_health.cpp
│       └── set_health.hpp
│
├── server/
│   └── onPlayerDamage/
│       ├── onPlayerDamageServer.cpp
│       └── onPlayerDamageServer.hpp
│
├── connectServer.hpp
└── connection.hpp
```
--------------------------------------------------

## Responsabilidades

### Client

O client é responsável por:

- Atualizar o jogador
- Definir animações
- Aplicar alterações visuais no jogador
- Enviar eventos para o servidor

#### Funções

set_health(float vida);

Descrição:
Recebe um valor do tipo float representando a vida do jogador
e atualiza a vida localmente com base no valor passado como parâmetro.

--------------------------------------------------

### Server

O server é responsável por:

- Receber dados enviados pelo cliente
- Processar eventos de dano
- Executar a lógica do jogo no servidor

#### Funções

onPlayerDamageServer(float vida, ServerSocket server, std::string name);

Descrição:
Recebe:
- vida: valor da vida após receber dano
- server: instância do ServerSocket
- name: nome do jogador

Envia uma mensagem formatada para o servidor no seguinte padrão:

onPlayerDamage::nome::dano

Exemplo:
onPlayerDamage::Player1::25

--------------------------------------------------

## Arquivos de Conexão

connectServer.hpp
Responsável por iniciar e configurar a conexão com o servidor.

connection.hpp
Responsável pelo gerenciamento da conexão e manipulação de sockets.

--------------------------------------------------

## Observações

- A comunicação entre client e server utiliza mensagens formatadas em string.
- O servidor é responsável por validar e processar os dados recebidos.
- O cliente apenas envia eventos e aplica atualizações locais.
- A lógica principal do jogo deve permanecer no servidor por segurança.
