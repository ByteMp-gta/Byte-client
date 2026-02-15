# Source Code Overview

## ENGLISH


## Overview

The `src` folder contains all the source code for the **Byte Multiplayer GTA SA** project.  
It is organized into modules that separate responsibilities, making maintenance, scalability, and future expansion easier.

---

## Main Structure
```plaintext
src
├── events/
│   ├── onPlayerDamage/
│   │   ├── onPlayerDamage.cpp 
│   │   └── onPlayerDamage.hpp 
│   ├── onPlayerDead/
│   │   ├── onPlayerDead.cpp 
│   │   └── onPlayerDead.hpp 
│   ├── onPlayerJump/
│   │   ├── onPlayerJump.cpp 
│   │   └── onPlayerJump.hpp 
│   ├── ProcessEvent.cpp 
│   └── ProcessEvent.hpp 
├── network/
│   ├── client/
│   │   ├── set_anim/
│   │   │   ├── set_anim.cpp 
│   │   │   └── set_anim.hpp 
│   │   └── set_healh/
│   │       ├── set_health.cpp 
│   │       └── set_health.hpp 
│   ├── server/
│   │   └── onPlayerDamage/
│   │       ├── onPlayerDamegeServer.cpp 
│   │       └── onPlayerDamegeServer.hpp
│   ├── connectServer.hpp 
│   └── connection.hpp 
└── Main.cpp 
```
---

## Purpose

This folder represents **the core of the multiplayer system**:

- Detects in-game events (`events/`)
- Manages network communication (`network/`)
- Applies client-side state and logic (`network/client/`)
- Validates and monitors server-side inconsistencies (`network/server/`)
- Provides utilities and support to facilitate development (`utils/`)

---

## Standards

- Each module is isolated in its own folder for easy maintenance
- Uses classes to encapsulate events and logic
- Communication is based on discrete events
- Client applies changes locally, server monitors and validates
- Code is organized for future scalability

---

## Next Steps

- Add new events (`onPlayerShoot`, `onVehicleEnter`, etc.)
- Expand multiplayer integration (NPCs, weapons, vehicles)
- Improve inconsistency validation
- Create a centralized event dispatcher to optimize the workflow

---

## Note

This README serves as **a general overview of the `src` folder**.  
For detailed documentation of each module, see the READMEs inside:

- `network/client/`  
- `network/server/`  
- `events/`  



## PT-BR


## Visão Geral

A pasta `src` contém todo o código-fonte do projeto **Byte Multiplayer GTA SA**.  
Ela é organizada em módulos que separam responsabilidades, facilitando manutenção, escalabilidade e expansão futura.

---

## Estrutura Principal

```plaintext
src
├── events/
│   ├── onPlayerDamage/
│   │   ├── onPlayerDamage.cpp 
│   │   └── onPlayerDamage.hpp 
│   ├── onPlayerDead/
│   │   ├── onPlayerDead.cpp 
│   │   └── onPlayerDead.hpp 
│   ├── onPlayerJump/
│   │   ├── onPlayerJump.cpp 
│   │   └── onPlayerJump.hpp 
│   ├── ProcessEvent.cpp 
│   └── ProcessEvent.hpp 
├── network/
│   ├── client/
│   │   ├── set_anim/
│   │   │   ├── set_anim.cpp 
│   │   │   └── set_anim.hpp 
│   │   └── set_healh/
│   │       ├── set_health.cpp 
│   │       └── set_health.hpp 
│   ├── server/
│   │   └── onPlayerDamage/
│   │       ├── onPlayerDamegeServer.cpp 
│   │       └── onPlayerDamegeServer.hpp
│   ├── connectServer.hpp 
│   └── connection.hpp 
└── Main.cpp 
```
---

## Objetivo

Esta pasta representa **a base do sistema multiplayer**:

- Detecta eventos no jogo (`events/`)
- Gerencia comunicação de rede (`network/`)
- Aplica estados e lógica do cliente (`network/client/`)
- Valida e monitora inconsistências do servidor (`network/server/`)
- Suporte e utilitários para facilitar o desenvolvimento (`utils/`)

---

## Padrões

- Cada módulo é isolado em sua própria pasta para fácil manutenção
- Uso de classes para encapsular eventos e lógica
- Comunicação baseada em eventos discretos
- Cliente aplica mudanças localmente, servidor monitora e valida
- Código organizado visando escalabilidade futura

---

## Próximos Passos

- Adicionar novos eventos (`onPlayerShoot`, `onVehicleEnter`, etc.)
- Expandir integração com multiplayer (NPCs, armas, veículos)
- Melhorar validação de inconsistências
- Criar event dispatcher centralizado para otimizar fluxo

---

## Observação

Este README serve como **apresentação geral da pasta `src`**.  
Para documentação detalhada de cada módulo, veja os READMEs dentro de:

- `network/client/`  
- `network/server/`  
- `events/`  

