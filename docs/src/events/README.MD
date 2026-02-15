# Events Module

## ENGLISH


## Overview

The directory `src/events` is responsible for:

- Monitoring player state
- Detecting in-game changes (damage, death, jump, etc.)
- Triggering events when changes occur
- Delegating network communication to the network/server layer

This layer DOES NOT send data directly.
It only detects state changes and calls the appropriate network module.

--------------------------------------------------

## Current Structure
```
events/
├── onPlayerDamage/
│   ├── onPlayerDamage.cpp
│   └── onPlayerDamage.hpp
│
├── onPlayerDead/
│   ├── onPlayerDead.cpp
│   └── onPlayerDead.hpp
│
├── onPlayerJump/
│   ├── onPlayerJump.cpp
│   └── onPlayerJump.hpp
│
├── ProcessEvent.cpp
└── ProcessEvent.hpp
```
--------------------------------------------------

## Overall Architecture

Full flow:

[GAME ENGINE]
     ↓
[events/]
     ↓
[network/server/]
     ↓
[External Server]

--------------------------------------------------

## ProcessEvent

Central class responsible for:

- Creating event objects
- Executing events every frame
- Managing lifecycle of events

### create()

Instantiates:

- CEventOnPlayerJump
- onPlayerDead
- onPlayerDamage

### execute()

Continuously executed.

Current order:

1. Execute death event
2. Execute damage event
3. Update player reference
4. Process jump event

This ensures all monitored states are checked continuously.

--------------------------------------------------

## Event: onPlayerDamage

Location:
events/onPlayerDamage/

Purpose:

Detect when the player loses health.

--------------------------------------------------

### Internal Behavior

Constructor:

- Stores player pointer
- Stores previous health value (wasVida)
- Stores ServerSocket pointer

Method execute():

1. Check if player is alive
2. Calculate:

   damage = previousHealth - currentHealth

3. If damage > 0.1f:
   call onPlayerDamageServer()

4. Update previousHealth

--------------------------------------------------

## Responsibility Separation

events/
- Detect changes
- No string formatting
- No socket handling

network/server/
- Format event
- Send through socket

External server:
- Apply authoritative logic

--------------------------------------------------

## Event Pattern Standard

Each event must:

1. Have its own folder
2. Have its own class
3. Implement execute()
4. Be registered in ProcessEvent

Standard structure:

events/
└── onEventName/
    ├── onEventName.cpp
    └── onEventName.hpp

Class pattern:
```cpp
class onEventName {
private:
    CPed* cj;
    ServerSocket* server;
public:
    void execute();
};
```
--------------------------------------------------

## Best Practices

1. Do not place network logic inside event classes
2. Do not implement complex game rules here
3. Only detect state changes
4. Avoid heavy allocations per frame
5. Properly manage object destruction
6. Keep headers lightweight

--------------------------------------------------

## Recommended Improvements

1. Replace manual new/delete with smart pointers (std::unique_ptr)
2. Implement an EventManager instead of direct instantiation
3. Standardize naming (PascalCase for classes)
4. Remove unnecessary macros
5. Reduce include dependencies in headers

--------------------------------------------------

## Architecture Summary

✔ Clear layer separation  
✔ Modular structure  
✔ Scalable design  
✔ Easy to extend  

Future example:
```
events/
└── onPlayerShoot/
    ├── onPlayerShoot.cpp
    └── onPlayerShoot.hpp
```
Just register it inside ProcessEvent.

--------------------------------------------------

## Important Rule

events/ = DETECTION layer  
network/ = COMMUNICATION layer  
Server = AUTHORITY layer  

Never mix these responsibilities.

 

# Events Module

## PT-BR


## Visão Geral

O diretório `src/events` é responsável por:

- Monitorar estados do jogador
- Detectar mudanças (vida, morte, pulo, etc.)
- Disparar eventos quando necessário
- Delegar envio para a camada network/server

Essa camada NÃO envia dados diretamente.
Ela apenas detecta mudanças e chama o módulo de rede apropriado.

--------------------------------------------------

## Estrutura Atual
```
events/
├── onPlayerDamage/
│   ├── onPlayerDamage.cpp
│   └── onPlayerDamage.hpp
│
├── onPlayerDead/
│   ├── onPlayerDead.cpp
│   └── onPlayerDead.hpp
│
├── onPlayerJump/
│   ├── onPlayerJump.cpp
│   └── onPlayerJump.hpp
│
├── ProcessEvent.cpp
└── ProcessEvent.hpp
```
--------------------------------------------------

## Arquitetura Geral

Fluxo completo:

[JOGO]
   ↓
[events/]
   ↓
[network/server/]
   ↓
[Servidor externo]

--------------------------------------------------

## ProcessEvent

Classe central responsável por:

- Criar os eventos
- Executar os eventos a cada frame
- Gerenciar ciclo de vida dos eventos

### create()

Instancia:

- CEventOnPlayerJump
- onPlayerDead
- onPlayerDamage

### execute()

Executado continuamente.

Ordem atual:

1. Executa morte
2. Executa dano
3. Atualiza referência do player
4. Processa pulo

Isso garante que todos os eventos sejam verificados constantemente.

--------------------------------------------------

## Evento: onPlayerDamage

Local:
events/onPlayerDamage/

Objetivo:

Detectar quando o jogador perde vida.

--------------------------------------------------

### Funcionamento

No construtor:

- Salva ponteiro do jogador
- Armazena vida anterior (wasVida)
- Guarda ponteiro do ServerSocket

No método execute():

1. Verifica se o jogador está vivo
2. Calcula:

   dano = wasVida - vidaAtual

3. Se dano > 0.1f:
   chama onPlayerDamageServer()

4. Atualiza wasVida

--------------------------------------------------

## Separação de Responsabilidades

events/
- Detecta mudanças
- Não formata strings
- Não gerencia conexão

network/server/
- Formata evento
- Envia via socket

Servidor real:
- Processa lógica autoritativa

--------------------------------------------------

## Padrão de Evento

Cada evento deve:

1. Ter sua própria pasta
2. Ter classe própria
3. Ter método execute()
4. Ser registrado no ProcessEvent

Estrutura padrão:
```
events/
└── onEventName/
    ├── onEventName.cpp
    └── onEventName.hpp
```
Classe:
```cpp
class onEventName {
private:
    CPed* cj;
    ServerSocket* server;
public:
    void execute();
};
```
--------------------------------------------------

## Boas Práticas

1. Não colocar lógica de rede dentro do evento
2. Não calcular regras complexas aqui
3. Apenas detectar mudanças
4. Evitar alocação desnecessária por frame
5. Garantir destrutores corretos

--------------------------------------------------

## Melhorias Recomendadas

1. Criar um EventManager ao invés de usar new manual
2. Usar smart pointers (std::unique_ptr)
3. Padronizar nomes (PascalCase para classes)
4. Remover macros desnecessárias
5. Evitar includes pesados nos headers

--------------------------------------------------

## Arquitetura Atual (Resumo)

✔ Boa separação em camadas  
✔ Modular  
✔ Escalável  
✔ Fácil adicionar novos eventos  

Exemplo futuro:

```
events/
└── onPlayerShoot/
    ├── onPlayerShoot.cpp
    └── onPlayerShoot.hpp
```
Basta registrar no ProcessEvent.

--------------------------------------------------

## Regra Importante

events/ é camada de DETECÇÃO.

network/ é camada de COMUNICAÇÃO.

Servidor é camada de AUTORIDADE.

Nunca misturar essas responsabilidades.

