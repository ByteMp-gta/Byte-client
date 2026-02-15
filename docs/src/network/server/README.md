# Network Module - SERVER

## ENGLISH


## Overview

The directory `src/network/server` is responsible for
handling outgoing and incoming server-side network events.

Unlike the client, the server:

- Processes authoritative game logic
- Validates data
- Sends structured events
- Controls synchronization

The server is the source of truth.

--------------------------------------------------

## Base Path

src\network\server

Current structure:
```
server/
└── onPlayerDamage/
    ├── onPlayerDamegeServer.cpp
    └── onPlayerDamegeServer.hpp
```
--------------------------------------------------

## Folder Pattern Standard

Each server network event must follow this structure:
```
server/
└── event_name/
    ├── event_nameServer.cpp
    └── event_nameServer.hpp
```
Rules:

1. One folder per event.
2. Folder name describes the event.
3. Header contains:
   - #pragma once
   - Includes
   - Activation macro
   - Function declaration
4. Source file contains:
   - Include of its own header
   - Implementation
   - Macro guard (#if EVENT)

--------------------------------------------------

## Macro Pattern

Each server event must have an activation macro.

Example:
```cpp
#define ONPLAYERDAMAGESERVER 1

#if ONPLAYERDAMAGESERVER
void onPlayerDamageServer(float damage, ServerSocket* server, std::string name);
#endif
```
Benefits:

- Feature toggling
- Cleaner builds
- Easier debugging
- Modular architecture

--------------------------------------------------

## Module: onPlayerDamageServer

Location:
server/onPlayerDamage/

Files:
- onPlayerDamegeServer.hpp
- onPlayerDamegeServer.cpp

--------------------------------------------------

## Purpose

Sends a formatted damage event to the server connection layer.

This module does NOT calculate damage.
It only formats and sends the event.

--------------------------------------------------

## Header (onPlayerDamegeServer.hpp)

Responsibilities:

- Define macro
- Declare function
- Include required dependencies

Structure:
```cpp
#pragma once
#include <string>
#include "../../connection.hpp"

#define ONPLAYERDAMAGESERVER 1

#if ONPLAYERDAMAGESERVER
void onPlayerDamageServer(float damage, ServerSocket* server, std::string name);
#endif
```
--------------------------------------------------

## Implementation (onPlayerDamegeServer.cpp)

Responsibilities:

- Build event string
- Send event through ServerSocket
- Optional logging

Internal flow:

1. Build formatted string:

   "onPlayerDamage::" + name + "::" + damage

2. Send to server:

   server->sendEventServer(str.c_str());

3. Write log:

   writeLog("aqui passou !");

--------------------------------------------------

## Event Format Standard

All server events follow this pattern:

eventName::playerName::value

Example:

onPlayerDamage::Player1::25

Rules:

- Double colon "::" used as separator
- First token = event name
- Second token = player name
- Third token = value/data

This keeps parsing simple and predictable.

--------------------------------------------------

## Responsibilities Separation

SERVER:
- Authoritative logic
- Validation
- Rule enforcement
- Data broadcasting

CLIENT:
- Apply state
- Render changes
- Reflect server updates

--------------------------------------------------

## Naming Conventions

Folders:
snake_case or camelCase (keep consistent)

Files:
eventNameServer.cpp
eventNameServer.hpp

Functions:
onEventNameServer

Macros:
EVENTNAMESERVER (uppercase)

--------------------------------------------------

## Improvements Recommended

1. Fix typo:
   onPlayerDamegeServer → onPlayerDamageServer

2. Avoid using:
   using namespace std;

   Prefer:
   std::string

3. Pass string by const reference:

   void onPlayerDamageServer(float damage,
                             ServerSocket* server,
                             const std::string& name);

4. Centralize event formatting into a helper function
   for better scalability.

--------------------------------------------------

## Scalability Example

Future event:
```
server/
└── onPlayerHeal/
    ├── onPlayerHealServer.cpp
    └── onPlayerHealServer.hpp
```
--------------------------------------------------

## Important Architecture Rule

Server modules must never:

- Trust client raw values
- Execute client-only logic
- Depend on visual state

Server controls everything.

# Network Module - SERVER

## PT-BR


## Visão Geral

O diretório `src/network/server` é responsável por
gerenciar os eventos de rede do lado do servidor.

Diferente do client, o servidor:

- Processa lógica autoritativa
- Valida dados
- Formata eventos
- Controla sincronização
- Envia informações estruturadas

O servidor é a fonte da verdade do sistema.

--------------------------------------------------

## Caminho Base
src\network\server

Estrutura atual:
```
server/
└── onPlayerDamage/
    ├── onPlayerDamegeServer.cpp
    └── onPlayerDamegeServer.hpp
```
--------------------------------------------------

## Padrão de Organização de Pastas

Cada evento de rede no servidor deve seguir este padrão:
```
server/
└── nome_do_evento/
    ├── nomeDoEventoServer.cpp
    └── nomeDoEventoServer.hpp
```
Regras:

1. Uma pasta por evento.
2. O nome da pasta deve representar o evento.
3. O arquivo .hpp deve conter:
   - #pragma once
   - Includes necessários
   - Macro de ativação
   - Declaração da função
4. O arquivo .cpp deve conter:
   - Include do próprio header
   - Implementação
   - Proteção com macro (#if EVENTO)

Esse padrão mantém o código modular e escalável.

--------------------------------------------------

## Padrão de Macro

Cada módulo do servidor deve possuir uma macro de ativação.

Exemplo:
```cpp
#define ONPLAYERDAMAGESERVER 1

#if ONPLAYERDAMAGESERVER
void onPlayerDamageServer(float damage, ServerSocket* server, std::string name);
#endif
```
Benefícios:

- Ativar/desativar funcionalidades facilmente
- Melhor controle de build
- Debug mais simples
- Arquitetura modular

--------------------------------------------------

## Módulo: onPlayerDamageServer

Local:
server/onPlayerDamage/

Arquivos:
- onPlayerDamegeServer.hpp
- onPlayerDamegeServer.cpp

--------------------------------------------------

## Objetivo

Formatar e enviar um evento de dano para a camada de conexão do servidor.

Esse módulo NÃO calcula o dano.
Ele apenas formata e envia o evento.

--------------------------------------------------

## Header (onPlayerDamegeServer.hpp)

Responsabilidades:

- Definir macro
- Declarar função
- Incluir dependências necessárias

Estrutura:
```cpp
#pragma once
#include <string>
#include "../../connection.hpp"

#define ONPLAYERDAMAGESERVER 1

#if ONPLAYERDAMAGESERVER
void onPlayerDamageServer(float damage, ServerSocket* server, std::string name);
#endif
```
--------------------------------------------------

## Implementação (onPlayerDamegeServer.cpp)

Responsabilidades:

- Construir a string do evento
- Enviar via ServerSocket
- Registrar log opcional

Fluxo interno:

1. Construção da mensagem:

   "onPlayerDamage::" + name + "::" + damage

2. Envio para o servidor:

   server->sendEventServer(str.c_str());

3. Registro de log:

   writeLog("aqui passou !");

--------------------------------------------------

## Padrão de Formato de Evento

Todos os eventos seguem o padrão:

nomeDoEvento::nomeDoPlayer::valor

Exemplo:

onPlayerDamage::Player1::25

Regras:

- "::" é o separador padrão
- Primeiro campo = nome do evento
- Segundo campo = nome do jogador
- Terceiro campo = valor/dado

Esse padrão facilita o parsing no receptor.

--------------------------------------------------

## Separação de Responsabilidades

SERVER:
- Lógica autoritativa
- Validação
- Regras do jogo
- Controle de estados globais

CLIENT:
- Aplicação visual
- Atualização local
- Reflexo do estado do servidor

--------------------------------------------------

## Convenção de Nomes

Pastas:
snake_case ou camelCase (manter padrão consistente)

Arquivos:
nomeDoEventoServer.cpp
nomeDoEventoServer.hpp

Funções:
onNomeDoEventoServer

Macros:
NOMEDOEVENTOSERVER (maiúsculo)

--------------------------------------------------

## Melhorias Recomendadas

1. Corrigir erro de digitação:
   onPlayerDamegeServer → onPlayerDamageServer

2. Evitar usar:
   using namespace std;

   Preferir:
   std::string

3. Passar string por referência constante:

   void onPlayerDamageServer(float damage,
                             ServerSocket* server,
                             const std::string& name);

4. Criar um helper central para formatação de eventos
   para evitar repetição de código.

--------------------------------------------------

## Exemplo de Expansão

Novo evento:
```
server/
└── onPlayerHeal/
    ├── onPlayerHealServer.cpp
    └── onPlayerHealServer.hpp
```
--------------------------------------------------

## Regra Arquitetural Importante

O servidor nunca deve:

- Confiar diretamente em valores do cliente
- Delegar validação ao cliente
- Executar lógica visual

O servidor controla toda a lógica do jogo.


