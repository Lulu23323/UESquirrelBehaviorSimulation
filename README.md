# Niagara Squirrel Simulation

## Requirements

### Basic Requirements
- ✔ Control the number and distribution of the squirrel crowd.
- ✔ Squirrels must be able to move on uneven surfaces.
- ✔ Niagara must use GPU Simulation.
- ✔ Include at least three movement states: **Idle - Walk - Run**.
- ✔ Skeletal Mesh and Skeletal Animation cannot be used in Niagara.
- ✔ Interaction with the player:
  - Use the official third-person demo character.
  - Squirrels should avoid the player when approached.

### Advanced Requirements
- ✔ Parameter Control:
  - Body size, speed, and interaction range.
  - Animation playback speed should correspond to movement speed.
- ✔ Additional movement states with logical transitions, such as:
  - Switch to **Climbing State** when encountering steep slopes.
  - Automatically transition between **Walk** and **Run** based on speed.
  - More diverse idle states with different animations.
- ❌ Expanded interactions:
  - Players can eliminate squirrels within a certain range.
  - Squirrels drop effects or small objects upon elimination.

## Implementation

### Development Roadmap
1. Drive VAT animations and animation playback.
2. Implement animation state machine and transition logic.
3. Resolve animation flickering issues caused by GPU simulation collision.
4. Fix inconsistencies between directly setting `Particles.Velocity` and expected values by switching to parameter passing.
5. Implement logic for avoiding the player.
6. Expose additional parameters.
7. Expand animation states.

### Key Functional Implementation

#### VAT Animation

##### Material Setup
1. **Bake VAT using the Flock plugin.**
   ![Image]
2. **Modify the plugin driver:** The original method used `time + fmod` looping instead of frame-based logic. Modified to calculate the current frame's time using `AnimationFrame` and `AnimationFrameRate` for sampling.
   ![Image]
   ![Image]
3. **Material receives Dynamic Parameter from Niagara for frame sampling.**
   ![Image]
   ![Image]

##### Animation Playback in Niagara
1. Developed a **Niagara Function Script** to calculate animation parameters, including **current frame, elapsed frames, and animation state**.
   ![Image]
   ![Image]

   ```cpp
   AnimationFrame = StartFrame + ElapsedFrames + AnimationSpeed * (DeltaTime * FrameRate)
   ```
   - **If the animation reaches `EndFrame`, it loops back to `StartFrame`.**
   - **If the animation changes, it resets to the new animation's `StartFrame`.**
   - **If in the initial state, it does not reset (useful for random time offsets).**

##### Animation States:
| FPS | State | Frame Range | Animation |
|----|------|-------------|-----------|
| 30 | 0 | 15-178 | Squirrel_Idle2 |
| 30 | 1 | 470-497 | Squirrel_Walk |
| 30 | 2 | 498-524 | Squirrel_Run |
| 30 | 3 | 180-227 | Squirrel_Idle3 |
| 30 | 4 | 230-346 | Squirrel_Idle4 |
| 30 | 5 | 531-563 | Squirrel_Climbing |

### Particle State Control
Particle parameters are mainly calculated using a **Scratch Script**.
   ![Image]
   ![Image]

1. **Three Main Conditions:**
   - **Timer:** Determines if the particle should switch states.
   - **Position Distance Calculation:** Determines if the particle should avoid the player or move back when out of range.
   ![Image]
2. **General Logic:**
   - Randomize animation state first.
   - Based on the animation state, randomly assign movement speed.
   ![Image]

## References

- ❌ **Houdini UE Practical Techniques** - VAT Vertex Animation Texture (Not suitable for intended logic)
  - [Video Link](https://www.bilibili.com/video/BV1p34y1G7Po)
- ❌ **Vertex Animation Manager Plugin** (Poor rendering results)
  - [Download Link](https://drive.google.com/file/d/1_ekKL2hLWzBcOC0TmH1_fbrOSarwhhn0/view)
- ❌ **AnimToTextureHelpers** (Unsupported in UE5.5)
  - [GitHub Link](https://github.com/kromond/AnimToTextureHelpers)
- ✔ **Flocks Plugin for UE5** (VAT animation driving)
  - [Video Link](https://www.bilibili.com/video/BV1te411G7T5)

### Additional Resources
- ⭐ **Unreal Engine 5 Large-Scale Crowd Simulation with Niagara**
  - [CSDN Article](https://blog.csdn.net/qq_30100043/article/details/131502503)
  - [Bilibili Video](https://www.bilibili.com/video/BV1FX4y1T7z2)
- ⭐ **UE5 Vertex Animation Tool**
  - [Documentation](https://dev.epicgames.com/documentation/zh-cn/unreal-engine/vertex-animation-tool-in-unreal-engine?application_version=5.5)
- ⭐ **[UOD2022] Physics Simulation in Niagara | Epic Games**
  - [Bilibili Video](https://www.bilibili.com/video/BV1324y1m7nA/)
- **Unreal Engine 5 Swarm of Rats with Niagara**
  - [YouTube Video](https://www.youtube.com/watch?v=NilyMiB1fos)
- **Creating Ambient Birds with Niagara and Vertex Animations**
  - [Blog Post](https://www.chrismccole.com/blog/creating-ambient-birds-in-unreal-with-niagara-and-vertex-animations-continued-advanced#common-issues)
- **A Deep Dive into Boids using Niagara in Unreal Engine**
  - [YouTube Video](https://www.youtube.com/watch?v=9iDA6WMqEyQ)
- **UE5 Niagara Swarm Particles Tutorials**
  - [Bilibili Video 1](https://www.bilibili.com/video/BV11T421i7Az/)
  - [Bilibili Video 2](https://www.bilibili.com/video/BV1XyUXYYEQa)
- **Unreal Engine 5 - Bird Flock System**
  - [Patreon Link](https://www.patreon.com/posts/69414954)
- **Valley of the Ancient Sample Game for UE5**
  - [Documentation](https://dev.epicgames.com/documentation/zh-cn/unreal-engine/valley-of-the-ancient-sample-game-for-unreal-engine)
- **UE5 Niagara Interactive Fireflies**
  - [Zhihu Article](https://zhuanlan.zhihu.com/p/558135767)
- **How To Make A Line Trace in UE5**
  - [YouTube Tutorial](https://www.youtube.com/watch?v=iNXAPs_Xlu8)

