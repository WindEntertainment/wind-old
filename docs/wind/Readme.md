# Wind Engine

![](/docs/images/01.gif)

⚠️ **Warning: Early Development Stage**
Please be aware that this project is currently in the early stages of development. There may be ongoing changes, improvements, and potential issues.

## Overview

Welcome to my data-driven game engine project! This engine is designed to empower game developers with a flexible and extensible architecture centered around data-driven principles.

## Features

- **Entity-Component-System (EnTT ECS):** Utilizing EnTT ECS, the engine follows a modular and efficient architecture, enabling developers to design complex and scalable game entities.

- **Asset Pipeline:** The engine includes a robust asset pipeline system, simplifying the management and loading of game assets. This ensures a streamlined workflow for handling various types of resources.

- **OpenGL: Renderer Module:** The renderer module leverages the power of OpenGL for high-performance graphics rendering, providing a solid foundation for visually stunning games.

- **Nested Prefab System:** A nested prefab system is implemented. This allows developers to compose and reuse complex game objects through a hierarchical structure, enhancing scene organization and development efficiency.

## Getting Started

To get started with the Data-Driven Game Engine, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/neutrinozh/chaos.git
    ```
2. Install dependencies:
    ```bash
    cd chaos
    conan install . --build=missing
    ```
3. Build project:
    ```bash
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cmake --build .
    ```
4. See [Documentation](./Documentation.md)