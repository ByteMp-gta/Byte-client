# Network Module - CLIENT

## ENGLISH

## Overview

The directory `src/network/client` is responsible for all
client-side network actions.

The client:

- Receives data from the server
- Applies state changes locally
- Updates player attributes
- Handles visual/state synchronization
- DOES NOT contain authoritative game logic

The client should only reflect server state.
All validation and game rules must remain on the server.

--------------------------------------------------

## Base Path
src\network\client

Current structure:
```
client/
├── set_anim/
│   ├── set_anim.cpp
│   └── set_anim.hpp
│
└── set_healh/
    ├── set_health.cpp
    └── set_health.hpp
```
--------------------------------------------------

## Folder Pattern Standard

Each network action must follow this structure:
```
client/
└── feature_name/
    ├── feature_name.cpp
    └── feature_name.hpp
```
Rules:

1. One folder per responsibility.
2. Folder name must match the feature.
3. Header (.hpp) must contain:
   - #pragma once
   - Required includes
   - Activation macro
   - Function declaration
4. Source (.cpp) must contain:
   - Include of its own header
   - Implementation
   - Macro guard (#if FEATURE)

This keeps the module scalable and clean.

--------------------------------------------------

## Macro Pattern

Each module must use a toggle macro.

Example:
```cpp
#define SETHEALTH 1

#if SETHEALTH
void set_health(float health);
#endif
```
Benefits:

- Enable/disable features easily
- Easier debugging
- Modular builds
- Cleaner feature control

--------------------------------------------------

## Module: set_health

Location:
client/set_healh/

Files:
- set_health.hpp
- set_health.cpp

### Purpose

Updates the local player's health using a value received from the server.

### Header (set_health.hpp)

Responsibilities:

- Define activation macro
- Declare function

Structure example:
```cpp
#pragma once

#include <plugin.h>

#define SETHEALTH 1

#if SETHEALTH
void set_health(float health);
#endif
```
--------------------------------------------------

### Implementation (set_health.cpp)

Responsibilities:

- Get player pointer
- Update health value
- Adjust internal game flags

Internal flow:

1. Get player CPed:
   CPed* playerPed = FindPlayerPed();

2. Set health:
   playerPed->m_fHealth = health;

3. Force internal state update:
   *(int *)((DWORD)playerPed + 0x530) = 1;

4. Update internal player data:
   DWORD pPlayerData = *(DWORD *)0xB7CD98;
   if (pPlayerData)
   {
       *(BYTE *)(pPlayerData + 0x3) = 0;
   }

--------------------------------------------------

## Client Best Practices

1. Never trust local values.
2. Never calculate damage on the client.
3. Only apply state received from server.
4. Do not mix server logic inside client modules.
5. Keep each network action isolated in its own folder.

--------------------------------------------------

## Naming Conventions

Functions:
set_actionName

Folders:
snake_case

Files:
feature_name.cpp
feature_name.hpp

Macros:
FEATURE_NAME (uppercase)

--------------------------------------------------

## Future Expansion Example

When adding a new feature:

1. Create new folder inside client
2. Create .hpp and .cpp
3. Add activation macro
4. Implement isolated logic
5. Register call inside main network handler

Example:

client/
└── set_armor/
    ├── set_armor.cpp
    └── set_armor.hpp

--------------------------------------------------

## Important Note

The client is only responsible for reflecting the server state.

All:

- Damage calculation
- Game rules
- Validation
- Anti-cheat logic

Must remain exclusively on the server.

# Network Module - CLIENT

## PT-BR


## Visão Geral

O diretório `src/network/client` é responsável por todas as ações
executadas localmente no cliente relacionadas à comunicação com o servidor.

O client:

- Recebe dados do servidor
- Aplica alterações no jogador local
- Executa mudanças visuais e estados internos
- NÃO deve conter lógica autoritativa (isso é responsabilidade do servidor)

A lógica do cliente deve ser apenas de aplicação de estado.

--------------------------------------------------

## Caminho Base

src\network\client

Estrutura atual:
```
client/
├── set_anim/
│   ├── set_anim.cpp
│   └── set_anim.hpp
│
└── set_healh/
    ├── set_health.cpp
    └── set_health.hpp
```
--------------------------------------------------

## Padrão de Organização de Pastas

Cada funcionalidade de rede deve seguir o seguinte padrão:
```
client/
└── nome_da_funcionalidade/
    ├── nome_da_funcionalidade.cpp
    └── nome_da_funcionalidade.hpp
```
Regras:

1. Uma pasta por responsabilidade.
2. Nome da pasta igual ao nome da funcionalidade.
3. Arquivo .hpp deve conter:
   - #pragma once
   - includes necessários
   - definição de macro de controle
   - declaração da função
4. Arquivo .cpp deve conter:
   - include do próprio .hpp
   - implementação da função
   - proteção via macro (#if)

--------------------------------------------------

## Padrão de Macro

Cada módulo deve possuir uma macro para ativação:

Exemplo:
```cpp
#define SETHEALTH 1

#if SETHEALTH
void set_health(float health);
#endif
```
Benefícios:

- Permite ativar/desativar funcionalidades rapidamente
- Facilita debug
- Permite builds customizadas

--------------------------------------------------

## Módulo: set_health

Local:
client/set_healh/

Arquivos:
- set_health.hpp
- set_health.cpp

### Objetivo

Atualizar a vida do jogador local com base em um valor recebido.

### Header (set_health.hpp)

Responsável por:

- Definir macro de ativação
- Declarar a função

Exemplo estrutural:
```cpp
#pragma once

#include <plugin.h>

#define SETHEALTH 1

#if SETHEALTH
void set_health(float health);
#endif
```
--------------------------------------------------

### Implementação (set_health.cpp)

Responsável por:

- Obter o ponteiro do jogador
- Alterar a vida
- Ajustar flags internas do jogo

Fluxo interno:

1. Obtém o CPed do jogador:
   CPed* playerPed = FindPlayerPed();

2. Atualiza a vida:
   playerPed->m_fHealth = health;

3. Força atualização de estado interno:
   *(int *)((DWORD)playerPed + 0x530) = 1;

4. Ajusta dados internos do player:
   DWORD pPlayerData = *(DWORD *)0xB7CD98;
   if (pPlayerData)
   {
       *(BYTE *)(pPlayerData + 0x3) = 0;
   }

--------------------------------------------------

## Boas Práticas do Client

1. Nunca confiar nos valores locais.
2. Nunca calcular dano no cliente.
3. Apenas aplicar estados recebidos.
4. Não misturar lógica de servidor no client.
5. Cada ação de rede deve estar isolada em seu próprio módulo.

--------------------------------------------------

## Convenção de Nomes

Funções:
set_nomeDaAcao

Pastas:
snake_case

Arquivos:
nome_da_acao.cpp
nome_da_acao.hpp

Macros:
NOMEDAACAO em maiúsculo

--------------------------------------------------

## Expansão Futura

Ao adicionar nova funcionalidade:

1. Criar nova pasta dentro de client
2. Criar .hpp e .cpp
3. Definir macro
4. Implementar função isolada
5. Registrar chamada no handler de rede principal

Exemplo futuro:
```
client/
└── set_armor/
    ├── set_armor.cpp
    └── set_armor.hpp
```
--------------------------------------------------

## Observação Importante

O client apenas reflete o estado enviado pelo servidor.

Toda validação, cálculo de dano, regras de jogo e segurança
devem permanecer exclusivamente no servidor.


