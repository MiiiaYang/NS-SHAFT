# Instructions

## Create New Page
Replace `<PageName>` with your desired page name.

1. **Add to Phase Enum**
   - Modify `Enum.hpp` as follows:
   ```c++
   enum class PhaseEnum { HomePage = 0, <PageName> = 1 };
   ```

2. **Create PageName.hpp**
   Use the following template:
   ```c++
   #ifndef <PAGENAME>_HPP
   #define <PAGENAME>_HPP

   #include "App.hpp"
   #include "BackgroundImage.hpp"
   #include "Character.hpp"

   class <PageName> : public App {
   public:
       explicit <PageName>() { phase = Enum::PhaseEnum::<PageName>; }

       // TODO: Add your game objects here
       // Example: std::shared_ptr<Character> m_Giraffe;

       void Start() override;
       void Update() override;
       void End() override;
   };

   #endif // <PAGENAME>_HPP
   ```

3. **Create PageName.cpp**
   Use the following template:
   ```c++
   void <PageName>::Start() {
       m_Background = std::make_shared<BackgroundImage>();
       m_Background->SetBackground("/background/menu_bg.png"); // Set phase background
       m_Root.AddChild(m_Background);

       // TODO: Add your game objects here
       // Example:
       // m_Giraffe = std::make_shared<Character>(GA_RESOURCE_DIR"/Image/Character/giraffe.png");
       // m_Giraffe->SetPosition({-60.5f, -140.5f});
       // m_Giraffe->SetZIndex(50);
       // m_Root.AddChild(m_Giraffe);

       m_CurrentState = State::UPDATE;
   };

   void <PageName>::Update() {
       // TODO: Control your game objects here
       m_Root.Update();
   };

   void <PageName>::End() {};
   ```

4. **Add Your Phase Page in main.cpp**
   Do it like this:
   ```c++
   phases.push_back(std::make_shared<PageName>(PageName()));
   ```
   Remember to include your `.hpp` file.

5. **Delete the build folder in the root directory and rebuild.**

## Navigate to Other Phase
- Use the `NavigationTo()` function like this:
```c++
NavigationTo(Enum::PhaseEnum::<PageName>);
```