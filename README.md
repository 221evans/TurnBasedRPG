Turn-Based RPG Game Engine
A custom 2D game engine built from scratch in C++ using SDL3, featuring entity management, state systems, and real-time debugging capabilities.
🎮 Features
Core Engine

Custom Entity System: Object-oriented hierarchy with base Entity class supporting inheritance for different character types
State Management: Clean game state system (Free Roam, Combat, Menu) with seamless transitions
Animation Framework: Flexible sprite animation system with configurable frame timing and texture switching
Real-time Debugging: Integrated ImGui interface for live debugging and state manipulation

Gameplay Systems

Player Character: Full directional movement with animation states (idle, running in 4 directions)
Enemy AI: Autonomous enemy behavior with patrol patterns and combat state awareness
Combat System: Turn-based combat framework with position management and state transitions

🛠️ Technical Implementation
Architecture

Entity-Component System: Modular design allowing easy addition of new enemy types
State Pattern: Clean separation of game states with appropriate behavior per state
Resource Management: Proper SDL texture loading, management, and cleanup
Debug Infrastructure: Professional debugging tools integrated into development workflow

Key Technologies

C++20: Modern C++ standards with RAII principles
SDL3: Cross-platform multimedia library for rendering and input
ImGui: Immediate mode GUI for debugging and development tools
CMake: Cross-platform build system

📁 Project Structure
Core/
├── Entities/           # Entity system and character classes
│   ├── Entity.h/cpp   # Base entity class with common functionality
│   ├── Player.h/cpp   # Player character with input handling
│   ├── Boar.h/cpp     # Enemy AI implementation
│   └── ZombieBase.h/cpp # Additional enemy type
├── Game.h/cpp         # Main game management and state coordination
├── GameState.h        # State enumeration and management
└── AnimationData.h    # Animation configuration structures
🚀 Building and Running
Prerequisites

C++20 compatible compiler
SDL3 development libraries
SDL3_image development libraries
CMake 3.25 or higher

Build Instructions
bash# Clone the repository
git clone [your-repo-url]
cd TurnBasedRPG

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run the executable
./TurnBasedRPG
Debug Mode
The project includes comprehensive debugging features available in debug builds:

Real-time entity state monitoring
Position and animation frame tracking
Interactive state switching (Combat/Free Roam)
Memory usage monitoring

🎯 Development Highlights
Problem-Solving Approach

Clean Code Practices: Maintained readable, documented code throughout development
Debugging-First: Integrated debugging tools early to support rapid development
Architectural Evolution: Evolved from simple rendering to complex entity systems

Key Technical Achievements

Memory Management: Zero memory leaks with proper RAII implementation
Performance Optimization: Efficient rendering at 60 FPS with minimal resource usage
Modular Design: Easy to extend with new enemy types and game features
Cross-Platform Compatibility: Builds and runs on multiple operating systems

🔧 Development Process
This project represents a journey from basic C++ concepts to advanced game engine architecture:

Foundation Phase: SDL3 setup, basic rendering, and input handling
Animation System: Frame-based animation with texture management
Architecture Phase: Entity system design and state management implementation
Polish Phase: Debugging tools, performance optimization, and code cleanup

📈 Future Enhancements

Combat Mechanics: Full turn-based combat implementation
Level System: Map loading and progression systems
Audio Integration: Sound effects and background music
Save/Load System: Game state persistence
Additional Enemy Types: Expanded bestiary using the entity framework

💻 Technical Skills Demonstrated

Object-Oriented Programming: Inheritance, polymorphism, and encapsulation
Memory Management: Manual resource handling and cleanup
System Architecture: Modular, extensible design patterns
Performance Optimization: Efficient resource usage and real-time rendering
Development Tools: Integrated debugging and development workflow
Version Control: Structured development with clear commit history

Status: Active development, core systems complete
License: Personal project for portfolio demonstration
