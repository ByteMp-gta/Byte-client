# Byte Multiplayer GTA SA - Documentation Overview

## Introduction

Welcome to the official documentation for the **Byte Multiplayer GTA SA** project.  
This documentation provides a structured overview of the project’s source code, events, network communication, and utilities.

The goal is to make it easier for developers to:

- Understand the architecture
- Navigate the codebase
- Extend and maintain modules
- Follow best practices for client-server communication

---

## Documentation Structure

The documentation is organized in a way that mirrors the `src` folder structure:

```plaintext
docs
├── src/
│   ├── events/
│   │   └── README.MD 
│   ├── network/
│   │   ├── client/
│   │   │   └── README.md 
│   │   ├── server/
│   │   │   └── README.md 
│   │   └── README.md 
│   └── README.md 
├── utils/
└── README.md 
```

Each module contains a dedicated `README.md` file that explains:

- Purpose of the module
- Folder and file structure
- Coding standards and naming conventions
- Function and class responsibilities
- Event formats (for network communication)
- Recommended improvements and scalability tips

---

## How to Use This Documentation

1. Start by reading this **introduction**.
2. Navigate to `docs/src` to explore:

   - `network/` – Learn how client and server communicate and handle events.
   - `events/` – See how in-game actions are detected and processed.
   - `utils/` – Understand logging and helper functions.

3. Each submodule README contains **code examples**, **file structure**, and **usage instructions**.

---

## Notes

- Documentation is bilingual (English / PT-BR) to support a wider audience.
- Naming conventions, macro patterns, and folder organization are highlighted in each module.
- Server modules always represent the **authoritative source of truth**, while clients handle local state and rendering.

---

## Goal of This Documentation

- Help new developers onboard quickly.
- Maintain a consistent coding standard across the project.
- Provide a reference for extending multiplayer functionality.
- Explain the client-server separation and event handling clearly.
# Byte Multiplayer GTA SA - Visão Geral da Documentação

## Introdução

Bem-vindo à documentação oficial do projeto **Byte Multiplayer GTA SA**.  
Esta documentação fornece uma visão estruturada do código-fonte do projeto, eventos, comunicação de rede e utilitários.

O objetivo é facilitar para os desenvolvedores:

- Compreender a arquitetura
- Navegar no código-fonte
- Estender e manter os módulos
- Seguir boas práticas de comunicação cliente-servidor

---

## Estrutura da Documentação

A documentação está organizada de forma a espelhar a estrutura da pasta `src`:

```plaintext
docs
├── src/
│   ├── events/
│   │   └── README.MD 
│   ├── network/
│   │   ├── client/
│   │   │   └── README.md 
│   │   ├── server/
│   │   │   └── README.md 
│   │   └── README.md 
│   └── README.md 
├── utils/
└── README.md 
```

Cada módulo contém um arquivo `README.md` dedicado que explica:

- Objetivo do módulo
- Estrutura de pastas e arquivos
- Padrões de codificação e convenções de nomes
- Responsabilidades de funções e classes
- Formatos de eventos (para comunicação de rede)
- Recomendações de melhorias e dicas de escalabilidade

---

## Como Utilizar Esta Documentação

1. Comece lendo esta **introdução**.
2. Navegue até `docs/src` para explorar:

   - `network/` – Aprenda como cliente e servidor se comunicam e processam eventos.
   - `events/` – Veja como ações do jogo são detectadas e processadas.
   - `utils/` – Entenda funções auxiliares e sistema de logs.

3. Cada README de submódulo contém **exemplos de código**, **estrutura de arquivos** e **instruções de uso**.

---

## Observações

- A documentação é bilíngue (Inglês / PT-BR) para atender a uma audiência maior.
- Convenções de nomes, padrões de macro e organização de pastas são destacadas em cada módulo.
- Os módulos do servidor representam sempre a **fonte autoritária de verdade**, enquanto os clientes aplicam estado local e renderização.

---

## Objetivo da Documentação

- Ajudar novos desenvolvedores a se familiarizarem rapidamente com o projeto.
- Manter um padrão consistente de codificação em todo o projeto.
- Servir como referência para expansão das funcionalidades multiplayer.
- Explicar claramente a separação cliente-servidor e o processamento de eventos.
